#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "Parser.h"
#include <iostream>

TEST_CASE ("Parser for HttpMessage" ) {
    SECTION("Parsing GET message") {
        HttpMessage get_msg = HttpMessage("GET /question HTTP/1.1\n");

        std::string get_str = "GET";

        Parser::parse(get_msg);

        REQUIRE(get_msg.get_method().compare("GET") == 0);
        REQUIRE(get_msg.get_uri().compare("/question") == 0);
    }

    SECTION("Parsing POST message") {
        HttpMessage post_msg = HttpMessage("POST /answer HTTP/1.1\nHost: localhost:8080\ncaptcha_result=5");

        Parser::parse(post_msg);

        REQUIRE(post_msg.get_method().compare("POST") == 0);
        REQUIRE(post_msg.get_answer().compare("captcha_result=5") == 0);
    }

}
