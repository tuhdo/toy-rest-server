#include "HttpMessage.h"

class Parser
{
public:
    Parser();

    void parse(HttpMessage msg);
    virtual ~Parser();
};

class GetParser
{
public:
    GetParser();
    virtual ~GetParser();

    void parse(HttpMessage msg);
};

class PostParser
{
public:
    PostParser();
    virtual ~PostParser();

    void parse(HttpMessage msg);

    int parse_captcha_data();
};
