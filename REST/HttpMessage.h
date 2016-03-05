#include <string>

class HttpMessage
{
public:
    HttpMessage() {}
    HttpMessage(const char *msg) {
        std::string s(msg);
        this->raw_msg = s;
    }

    virtual ~HttpMessage() {}

    const std::string get_captcha() const {
        return captcha;
    }

    void set_captcha(const std::string captcha) {
        this->captcha = captcha;
    }

    const std::string get_uri() const {
        return uri;
    }

    void set_uri(const std::string uri) {
        this->uri = uri;
    }

    const std::string get_method() const {
        return method;
    }

    void set_method(const std::string method) {
        this->method = method;
    }

    const std::string get_raw_msg() const {
        return raw_msg;
    }

    void set_raw_msg(const std::string raw_msg) {
        this->raw_msg = raw_msg;
    }
private:
    std::string raw_msg;
    std::string method;
    std::string uri;
    std::string captcha;
};
