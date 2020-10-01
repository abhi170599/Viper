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

int main() {

     RSA rsa;
     boost::asio::io_service io_service;
//socket creation
     tcp::socket socket(io_service);
//connection
     socket.connect( tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 8000 ));
// request/message from client
     const string msg = "Relop 127.0.0.1 !\n";
     boost::system::error_code error;
     boost::asio::write( socket, boost::asio::buffer(msg), error );
     if( !error ) {
        // cout << "Client sent hello message!" << endl;
     }
     else {
        cout << "send failed: " << error.message() << endl;
     }
 // getting response from server
    boost::asio::streambuf receive_buffer;
    boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
    if( error && error != boost::asio::error::eof ) {
        cout << "receive failed: " << error.message() << endl;
    }
    else {
        const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
        string msg(data);
        string decypt = rsa.decrypt(msg);
        cout << data << endl;
    }
    return 0;
}