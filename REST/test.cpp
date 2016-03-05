#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "Parser.h"

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE("Parser for HttpMessage" ) {
    Parser p;

    SECTION("Parsing GET message") {
        HttpMessage get_msg = HttpMessage("GET /question HTTP/1.1\n");

        std::string get_str = "GET";

        p.parse(get_msg);

        REQUIRE(get_msg.get_method().compare("GET") == 0);
        REQUIRE(get_msg.get_uri().compare("/question") == 0);
    }

    SECTION("Parsing POST message") {
        HttpMessage post_msg = HttpMessage("POST /n");
        std::string post_str = "POST";

        p.parse(post_msg);

        REQUIRE(post_msg.get_method().compare(post_str) == 0);
    }

}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}
