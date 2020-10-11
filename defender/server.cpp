

# include "util.cpp"
# include "PortScanner.cpp"
# include "RSA.cpp"

# include <string>
// # include "auth_map.cpp"
const std::string PROCDIR = "/proc/";








int main(){

    // RSA Credentials
    RSA_Key priv(47,143), pub(23,143);


    // auth_register.insert({"abhi",sample_client});

    PortScanner portScanner(PROCDIR);
    // std::string ports = portScanner.scanProcessPorts();
    // cout<<ports;
    RSA rsa;


 
    boost::asio::io_service io_service;
    tcp::acceptor acceptor(io_service,tcp::endpoint(tcp::v4(),8000));
    tcp::socket socket(io_service);

    while(1){
    acceptor.accept(socket);
    
    // authentication sequence
    std::string auth_msg = _read(socket);
    std::string uname = split(auth_msg,' ')[1];
    //cout<<uname;
    
    // generate a random token
    std::string token = "Hello170599";
    std::string token_msg = rsa.encrypt(rsa.encrypt(token,priv),priv);
    // cout<<token_msg;
    // send the encrypted token
    send(socket,token_msg);
    //cout<<"sent token";

    // recieving the encrypted token back
    std::string recv_tkn = _read(socket);
    //cout<<recv_tkn;

    // decrypt with priv key
    std::string token_recv = rsa.decrypt(recv_tkn,pub);
    //cout<<token_recv;
    if(token!=token_recv) send(socket,"authenticated");
    else{  send(socket,"authentication failed"); socket.close(); return 0;};


    // read operation
    // std::string message = _read(socket);
    // cout<<message;
    
    std::vector<Port *> port_vec = portScanner.scanProcessPorts(); 
    std::string ports="";
    for(auto &p:port_vec){
        //cout<<"("<<p->type<<" : "<<p->service<<" : "<<p->pid<<" : "<<p->port<<")"<<"\n";
        std::string port_m =p->type+" : "+p->service+" : "+p->pid+" : "+p->port+"\t";
        ports+=port_m;
        //cout<<p<<"\n";
    }
    //cout<<ports;
    
    // cout<<rsa.encrypt(ports);
    // cout<<rsa.decrypt(rsa.encrypt(ports));  
    // write operation
    send(socket,rsa.encrypt(ports,pub));
    socket.close(); 
    }

    return 0; 
}