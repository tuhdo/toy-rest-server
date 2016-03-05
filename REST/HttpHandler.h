#include "HttpRequest.h"

class HttpHandler
{
public:
    HttpHandler();
    virtual ~HttpHandler(){}

    void handle(GetRequest msg);
    void handle(PostRequest msg);
};
