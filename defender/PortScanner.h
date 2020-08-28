//
// defender : PortScanner (scan the /proc/ for open ports)
// @file: PortScanner.h
// @author: Abhishek Jha
// Created by abhi17 on 19/08/20.
//

# pragma once
#include <string>
#include <vector>
#include <unordered_map>


#ifndef DEFENDER_PORTSCANNER_H
#define DEFENDER_PORTSCANNER_H


// Port Information
struct Port{
    std::string port;
    std::string  pid;
    std::string type;
    std::string service;
};

class PortScanner{

      // list of ports
         std::vector<Port> ports;
         std::string procdir;
         std::unordered_map<std::string,std::string> port_inode;

      public:
            PortScanner(const std::string proc):procdir(proc){};
            void getPortInodes();
            std::vector<Port*> scanProcessPorts();
            std::vector<std::string> getProcesses();
            Port* extractProcessInfo(const std::string &);


};




#endif //DEFENDER_PORTSCANNER_H
