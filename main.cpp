#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/hex.hpp>
#include "gzip.h"

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
            boost::array<char, 1024> buf{};
            boost::system::error_code ec;
            size_t len = sock.read_some(boost::asio::buffer(buf), ec);
            if(ec == boost::asio::error::eof)
                break;
            else if(ec)
                throw boost::system::system_error(ec);
            std::stringstream message_stream;
            message_stream.write(buf.data(), len);
            std::string message  = message_stream.str();
            std::cout << message << '\n';
            boost::regex expr{"^(0x|0X)?[a-fA-F0-9]+$"};
            boost::smatch match;
            if(boost::regex_search(message, match, expr)){
                std::cout << "This is what is found" <<'\n';
                std::string m_str  = match[0];
                std::cout << m_str << '\n';
                std::string o_str;
                boost::algorithm::unhex(m_str, std::back_inserter(o_str));
                std::string f_str = Gzip::decompress(o_str);
                std::cout << f_str << '\n';
                break;
            }
        }
    }catch(boost::system::system_error& e){
        std::cout << "Error occured!" << \
        "Error code: "<<e.code() << \
        "Error Message: " << e.what() << '\n';
        return e.code().value();
    }
    return 0;
}