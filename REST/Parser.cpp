#include <iostream>
#include "Parser.h"

std::size_t Parser::pos = std::string::npos;

void Parser::parse(HttpMessage &msg) {
    std::string msg_str = msg.get_raw_msg();

    pos = msg_str.find("GET");
    if (pos != std::string::npos) {
        std::cout << "Going to set GET" << std::endl;
        msg.set_method("GET");
        parse_get(msg);

        return;
    }

    pos = msg_str.find("POST");
    if (pos != std::string::npos) {
        msg.set_method("POST");
        parse_post(msg);

        return;
    }

    std::string raw_msg = msg.get_raw_msg();
    std::size_t end_pos;
    pos = raw_msg.find("/");
    end_pos = raw_msg.find(" ", pos);
    msg.set_uri(raw_msg.substr(pos, end_pos - pos));
}

void Parser::parse_get(HttpMessage &msg) {
    std::size_t end_pos;

    std::string raw_msg = msg.get_raw_msg();
    int length = raw_msg.length();

    std::cout << "length is " << length << "\n";

    pos = raw_msg.find("/");
    end_pos = raw_msg.find(" ", pos);
    msg.set_uri(raw_msg.substr(pos, end_pos - pos));

    pos = end_pos;
}

void Parser::parse_post(HttpMessage &msg) {
    std::string raw_msg = msg.get_raw_msg();
    int length = raw_msg.length();

    pos = raw_msg.find("captcha_result", pos);
    pos = raw_msg.find("=", pos);
    msg.set_answer(raw_msg.substr(pos + 1));
}
