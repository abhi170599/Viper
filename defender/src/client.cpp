#include <iostream>
#include <boost/asio.hpp>


# include "RSA.cpp"

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

// function to read from a socket 
string _read(tcp::socket & socket){
    boost::asio::streambuf buf;
    boost::asio::read_until(socket,buf,"\n");
    string data = boost::asio::buffer_cast<const char *>(buf.data());
    return data;
}

// function to write to a socket
void send(tcp::socket & socket,const string & message){
    const string msg = message+"\n";
    boost::asio::write(socket,boost::asio::buffer(msg));
}

// RSA Credentials
RSA_Key priv(47,143),pub(23,143);

int main() {

     RSA rsa;
     boost::asio::io_service io_service;
//socket creation
     tcp::socket socket(io_service);
//connection
     socket.connect( tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 8000 ));

// request auth message from client
     const string msg = "Relop abhi";
     
     // send request
     send(socket,msg);
     
     // recieve auth token
     string data = _read(socket);
     //cout<<data;
     std::string token = rsa.decrypt(rsa.decrypt(data,pub),pub);
     //cout<<token;
     // resend encrypted token
     std::string tkn_back = rsa.encrypt(token,priv);
     send(socket,tkn_back);

     // read authentication result
     string auth_res = _read(socket);
     cout<<auth_res;

     string ports_en = _read(socket);
     string ports = rsa.decrypt(ports_en,priv);
     cout<<ports;
     
     
    return 0;
}