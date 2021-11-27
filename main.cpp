#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>


int main(int argc, char* argv[])
{
    std::string raw_ip_addr  = "20.108.244.219";
    unsigned short port_num = 5050;
    try{
        boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(raw_ip_addr), port_num);
        boost::asio::io_service ios;
        boost::asio::ip::tcp::socket sock(ios,ep.protocol());
        sock.connect(ep);
        std::cout << "Connection successful" << '\n';
        // read from the connected socket
    }catch(boost::system::system_error& e){
        std::cout << "Error occured!" << \
        "Error code: "<<e.code() << \
        "Error Message: " << e.what() << '\n';
        return e.code().value();
    }
    return 0;
}