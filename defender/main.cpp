/*
 * Defender : Remote Encrypted List Open Ports
 * (list all the open tcp and udp ports in the system)
 * @file:main.cpp
 * @author:Abhishek Jha
 *
 */

# include <iostream>
# include "PortScanner.cpp"
# include "RSA.cpp"

const std::string PROCDIR = "/proc/";



int main(){

    PortScanner portScanner(PROCDIR);
    //vector<string> processes = portScanner.getProcesses();
    //cout<<processes.size();

    vector<Port*> ports = portScanner.scanProcessPorts();

    for(auto &p:ports){
        cout<<"("<<p->type<<" : "<<p->service<<" : "<<p->pid<<" : "<<p->port<<")"<<"\n";
        //cout<<p<<"\n";
    }
    
    string message = "Hello World";
    RSA rsa;
    string cipher = rsa.encrypt(message);
    cout<<"Cipher text = "<<cipher;
    string plain = rsa.decrypt(cipher);
    cout<<"Decipher : "<<plain;



    return 0;

}
