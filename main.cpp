#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/regex.hpp>


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
        for(;;){
            boost::array<char, 128> buf{};
            boost::system::error_code ec;
            size_t len = sock.read_some(boost::asio::buffer(buf), ec);
            if(ec == boost::asio::error::eof)
                break;
            else if(ec)
                throw boost::system::system_error(ec);
            std::cout.write(buf.data(), len);
        }
    }catch(boost::system::system_error& e){
        std::cout << "Error occured!" << \
        "Error code: "<<e.code() << \
        "Error Message: " << e.what() << '\n';
        return e.code().value();
    }
    return 0;
}