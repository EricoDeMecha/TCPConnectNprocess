#include "tcp_client.hpp"
#include <boost/program_options.hpp>

namespace opt = boost::program_options;

int main(int argc, char* argv[])
{
    // parse command line args
    opt::options_description desc("Usage");
    desc.add_options()
            ("host_ip,h", opt::value<std::string>(), "The host/server ip")
            ("port,p", opt::value<unsigned short>(), "The host/server port")
            ("help", "Show help message");
    opt::variables_map vm;
    opt::store(opt::parse_command_line(argc, argv, desc), vm);
    opt::notify(vm);
    if(vm.count("help")){
        std::cout << desc << '\n';
        return 1;
    }

    std::string raw_ip_addr  = vm["host_ip"].as<std::string>();
    unsigned short port_num = vm["port"].as<unsigned short>();
    try{
        TCPClient tcpp(raw_ip_addr, port_num);
        for(;;) {
            boost::system::error_code ec;
            std::string message = tcpp.readMessage(ec);
            // find hex string
            boost::regex expr{"^(0x|0X)?[a-fA-F0-9]+$"};
            boost::smatch match;
            if(boost::regex_search(message, match, expr)) {
                std::string msg = match[0];
                // HEX decode message
                std::string d_msg;
                TCPClient::hexDecodeMessage(msg, d_msg);
                // GZIP decompress message
                std::string decompressed_msg = TCPClient::decompressMessage(d_msg);
                std::cout << decompressed_msg << '\n';
                // write message
                tcpp.writeMessage(decompressed_msg, ec);
                std::cout << "Has written" << '\n';
                std::string  final_message = tcpp.readResponse(ec);
                // read response
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