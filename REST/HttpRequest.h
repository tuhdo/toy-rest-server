class HttpRequest
{
public:
    HttpRequest();
    virtual ~HttpRequest(){}
};

class GetRequest:public HttpRequest
{
public:
    GetRequest();
    virtual ~GetRequest(){}
};

class PostRequest:public HttpRequest
{
public:
    PostRequest();
    virtual ~PostRequest();
};
