

# include "util.cpp"
# include "PortScanner.cpp"

# include "RSA.cpp"

const std::string PROCDIR = "/proc/";


int main(){

    PortScanner portScanner(PROCDIR);
    string ports = portScanner.scanProcessPorts();
    cout<<ports;
    RSA rsa;



    boost::asio::io_service io_service;
    tcp::acceptor acceptor(io_service,tcp::endpoint(tcp::v4(),8000));
    tcp::socket socket(io_service);
    acceptor.accept(socket);

    // read operation
    string message = _read(socket);
    cout<<message;
    
    //string ports = portScanner.scanProcessPorts();
    //cout<<ports;

    // write operation
    send(socket,rsa.encrypt(ports));

    return 0; 
}