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

    RSA_Key pub(23,143),priv(47,143);

    PortScanner portScanner(PROCDIR);
    //vector<string> processes = portScanner.getProcesses();
    //cout<<processes.size();

    vector<Port*> ports = portScanner.scanProcessPorts();
    
    std::string portStr="";

    for(auto &p:ports){
        cout<<"("<<p->type<<" : "<<p->service<<" : "<<p->pid<<" : "<<p->port<<")"<<"\n";
        portStr +=p->type+" : "+p->service+" : "+p->pid+" : "+p->port;
        //cout<<p<<"\n";
    }
    cout<<portStr;

   // std::string ports = portScanner.scanProcessPorts();
   // cout<<ports;
    
    string message = "Hello World";
    RSA rsa;
    string cipher = rsa.encrypt(portStr,pub);
    // cout<<"Cipher text = "<<cipher;
    string plain = rsa.decrypt(cipher,priv);
    cout<<"\nDecipher = "<<plain;



    return 0;

}
