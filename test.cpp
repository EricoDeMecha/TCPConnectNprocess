#include <boost/regex.hpp>
#include <string>
#include <iostream>


int main(){
    std::string s = "1f8b080032f7d85f02ff55cac10980400c04c056b602abb18153721a249b2309dabe873fbfc3aca760932c0c89ee618dbb406d84df62c282266a9e8ac6d452277ab87d46e7e371290f64b59ac93fffe1f202fcefa41e62000000\n";
    boost::regex expr{"^(0x|0X)?[a-fA-F0-9]+$\n"};
    std::cout << std::boolalpha << boost::regex_match(s, expr) << '\n';
}