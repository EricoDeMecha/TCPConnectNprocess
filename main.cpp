#include "tcp_client.hpp"

int main(int argc, char* argv[])
{
    std::string raw_ip_addr  = "20.108.244.219";
    unsigned short port_num = 5050;
    try{
        TCPClient tcpp(raw_ip_addr, port_num);
        for(;;) {
            boost::system::error_code ec;
            std::string message = tcpp.readMessage(ec);
            boost::regex expr{"^(0x|0X)?[a-fA-F0-9]+$"};
            boost::smatch match;
            if(boost::regex_search(message, match, expr)) {
                std::string msg = match[0];
                std::string d_msg;
                TCPClient::hexDecodeMessage(msg, d_msg);
                std::string decompressed_msg = TCPClient::decompressMessage(d_msg);
                std::cout << decompressed_msg << '\n';
                tcpp.writeMessage(decompressed_msg, ec);
                std::cout << "Has written" << '\n';
                std::string  final_message = tcpp.readResponse(ec);
                std::cout << "Has read" << '\n';
                std::cout << final_message << '\n';
                break;
            }
        }
    }catch(boost::system::system_error& e){
        std::cerr << "Error! Error code: " << e.code() << \
                        " Message: " << e.what();
    }
    return 0;
}