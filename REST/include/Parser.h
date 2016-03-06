#include <string>
#include "HttpMessage.h"

class HttpMessage;

class Parser
{
public:
    Parser(){}

    static void parse(HttpMessage &msg);

    virtual ~Parser() {}
private:
    static std::size_t pos; // current position in raw string the parser is stopping
    static void parse_get(HttpMessage &msg);
    static void parse_post(HttpMessage &msg);
};
