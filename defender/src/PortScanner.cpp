//
// RELOP PortScanner Implementation
// @file:PortScanner.cpp
// @author:Abhishek Jha
// Created by abhi17 on 19/08/20.
//

#include "PortScanner.h"
#include <filesystem>
#include <fstream>
#include "utils.cpp"

// scans a directory and returns a list of process ids
// @returns a vector of std::string of process ids
std::vector<std::string> PortScanner::getProcesses() {

     std::vector<std::string> processes;
     for(const auto & entry: std::filesystem::directory_iterator(this->procdir)){
         std::string process_id = entry.path().string();
         std::string id = process_id.substr(6,process_id.length());
         if(is_number(id))
            processes.push_back(entry.path().string());
     }
     return processes;
}

// scans the proc/net/tcp* and collects the port->inode pairs
void PortScanner::getPortInodes() {

    std::string filenames[2] = {"tcp","tcp6"};

    // read the /proc/net/tcp* files
    for (const auto &file:filenames) {
        std::string tcp_file = "/proc/net/"+file;
        std::fstream ftcp;
        ftcp.open(tcp_file, std::ios::in);
        if (ftcp.is_open()) {
            std::string port;
            ftcp.ignore(1);
            int count=0;
            while (getline(ftcp, port)) {
                //extract port number and inode value
                count++;
                if(count==1) continue;
                vector<std::string> port_info = split(port, ' ');

                    std::string inode = port_info[20];
                    std::string port_num = hex2decimal(split(port_info[4], ':')[1]);
                    if (inode.length() > 0 && port_num > "1024") {

                        this->port_inode[inode] = port_num;
                    }

            }
        }
        ftcp.close();
    }
}

// extracts a process information from process id into Port Structure
// @params : process path to be extracted
// @returns a Port object with process information
Port* PortScanner::extractProcessInfo(const std::string &process_path) {

     Port* port = new Port();

     std::string uid;
     fstream uid_fs;
     uid_fs.open(process_path+"/loginuid");
     uid_fs>>uid;
     uid_fs.close();

     if(uid!="1000"){
         return nullptr;
     }


     // extract process id
     int len = process_path.length();
     std::string process_id = process_path.substr(6,len);
     port->pid = process_id;


     // extract process name (service)
     std::string process_name = process_path+"/comm";
     std::fstream fs;
     fs.open(process_name,std::ios::in);
     std::string service;
     fs>>process_name;
     fs.close();
     port->service=process_name;
     port->type="tcp";

     //search the ports map for process inodes
     std::string fd_path = process_path+"/fd";

         for (const auto &entry: std::filesystem::directory_iterator(fd_path)) {

             std::string fd = split(entry.path().string(),'/')[4];

             if (is_number(fd) && stoi(fd)>2){

                 std::string cmd = "stat " + fd_path + "/" + fd;
                 const char *cmd_c = cmd.c_str();
                 // extract inode for fds
                 std::string out = exec(cmd_c);
                     std::string init_part = split(split(out,' ')[5],':')[0];
                     if(init_part.substr(0,3)!="soc") return nullptr;
                     std::string socket = split(split(out, ' ')[5], ':')[1];
                     std::string socket_inode = socket.substr(1, socket.length() - 3);

                     // check for membership in inode->port map
                     if (is_number(socket_inode) && this->port_inode.find(socket_inode) != this->port_inode.end()) {
                         port->port = this->port_inode[socket_inode];

                         return port;
                     }
             }
     }


     return nullptr;
}

// driver function to initiate port scanning
// @params: list of process_ids
// @return: list of open ports
std::vector<Port *> PortScanner::scanProcessPorts() {
    std::vector<Port *> ports;
    std::vector<std::string> processes = getProcesses();

    // reset inode->port map
    this->port_inode.clear();
    this->getPortInodes();



    for(const auto &process:processes){
        Port *port = this->extractProcessInfo(process);
        if(port!= nullptr){
            ports.push_back(port);
        }
    }
    

    return ports;
}


