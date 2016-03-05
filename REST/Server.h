#include "Connection.h"

static const char *html_form =
    "<html><body>POST example."
    "<form method=\"PUT\" action=\"/answer\">"
    "Input 2: <input type=\"text\" name=\"input_2\" /> <br/>"
    "<input type=\"submit\" />"
    "</form></body></html>";

static const std::string get_response =
    "HTTP/1.0 200 OK\r\n"
"Content-Length: 5\r\n"
"Content-Type: text/html\r\n\r\n"
"<html><body>POST example."
"<form method=\"POST\" action=\"/handle_post_request\">"
"Input 2: <input type=\"text\" name=\"input_2\" /> <br/>"
"<input type=\"submit\" />"
"</form></body></html>";

class Server
{
public:
    Server(int port, int lisp_port);
    virtual ~Server(){}

    void run();
private:
    ServerConnection server_conn;  // connect to the outside world
    LispServerConnection lisp_conn; // connect to Lisp server as a client
};
