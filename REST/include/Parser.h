#include <string>
#include "HttpMessage.h"

// forward declartion
class HttpMessage;

// Responsible for parsing HTML messages received from the client
// It accepts a HttpMessage object with only raw content, then fills
// the object with parsed information.
class Parser
{
public:
    Parser(){}

    // General interface for parsing all kinds of HTTP messages.
    // The function fills general information that all messages have,
    // like method (GET, POST, PUT, DELETE), URI...
    static void parse(HttpMessage &msg);

    virtual ~Parser() {}
private:
    static std::size_t pos; // current position in raw string the parser is stopping

    // internal parse routine for GET message
    // This function is called by parse() above,
    // to continue parsing GET specific information
    static void parse_get(HttpMessage &msg);

    // internal parse routine for POST message
    // This function is called by parse() above,
    // to continue parsing POST specific information
    static void parse_post(HttpMessage &msg);
};
