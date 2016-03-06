#include "Connection.h"

class Server
{
public:
    Server(int port, int lisp_port);
    virtual ~Server(){}

    void run();
private:
    IncomingConnection server_conn;  // connect to the outside world
    OutgoingConnection lisp_conn; // connect to Lisp server as a client

    std::string compose_response();
};
