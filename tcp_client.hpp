#ifndef _TCP_CLIENT_H
#define _TCP_CLIENT_H

#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/hex.hpp>
#include "gzip.h"

struct TCPClient{
    TCPClient(std::string& raw_ip_address, unsigned short& port_num):
            socket(ios,ep.protocol()),
            ep(boost::asio::ip::address::from_string(raw_ip_address), port_num){
        try {
            socket.connect(ep);
            std::cout << "Connection successful" << '\n';
        }catch(boost::system::system_error& e){
            throw boost::system::system_error(e.code());
        }
    }
    ~TCPClient(){
        socket.close();
    };
    std::string readMessage(boost::system::error_code& ec){
            boost::array<char, 1024> buf{};
            long len = socket.read_some(boost::asio::buffer(buf), ec);
            if(ec == boost::asio::error::eof)
                throw boost::system::system_error(ec);
            std::stringstream message_stream;
            message_stream.write(buf.data(), len);
            std::string message = message_stream.str();
            std::cout << message << '\n';
            return message;
    }
    static void hexDecodeMessage(std::string& msg, std::string& decoded_msg){
        boost::algorithm::unhex(msg, std::back_inserter(decoded_msg));
    }
    static std::string decompressMessage(std::string& d_msg){
        return Gzip::decompress(d_msg);
    }
    void writeMessage(std::string& message, boost::system::error_code& ec){
        socket.write_some(boost::asio::buffer(message.data(), message.size()), ec);
    }
    std::string readResponse(boost::system::error_code& ec){
        std::string r_message;
        std::stringstream message_stream;
        boost::asio::streambuf  buffer;
        size_t len = boost::asio::read_until(socket, buffer, '\n', ec);
        if(len){
            message_stream.write(boost::asio::buffer_cast<const char*>(buffer.data()), len);
            r_message = message_stream.str();
        }
        return r_message;
    }

private:
    boost::asio::ip::tcp::endpoint ep;
    boost::asio::io_service ios;
    boost::asio::ip::tcp::socket socket;
};

#endif