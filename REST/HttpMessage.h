#include <string>

class HttpMessage
{
public:
    HttpMessage(std::string msg);
    virtual ~HttpMessage(){}

    const std::string get_uri() const {
        return uri;
    }

    const std::string get_method() const {
        return method;
    }
private:
    std::string method;
    std::string uri;
};

class GetMessage: public HttpMessage
{
public:
    GetMessage(std::string msg);
    virtual ~GetMessage(){}
};

class PostMessage: public HttpMessage
{
public:
    PostMessage(std::string msg);
    virtual ~PostMessage(){}

    const std::string get_data() const {
        return data;
    }
private:
    std::string data;
};
