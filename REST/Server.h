#include "Connection.h"

static const char *html_form =
    "<html><body>POST example."
    "<form method=\"PUT\" action=\"/answer\">"
    "Answer: <input type=\"text\" name=\"answer\" /> <br/>"
    "<input type=\"submit\" />"
    "</form></body></html>";

static const 

class Server
{
public:
    Server(int port, int lisp_port);
    virtual ~Server(){}

    void run();
private:
    ServerConnection server_conn;  // connect to the outside world
    LispServerConnection lisp_conn; // connect to Lisp server as a client

    std::string compose_response();
};
