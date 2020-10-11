# include <iostream>
# include <boost/asio.hpp>

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