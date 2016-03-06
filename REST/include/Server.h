#include "Connection.h"


// Server talks to the outside world and to the Lisp backend.
//
// It accepts HTTP requests from the outside and then return response from
// the Lisp server.
class Server
{
public:
    // Server needs 2 ports: its own port and the Lisp app server
    Server(int port, int lisp_port);
    virtual ~Server(){}

    // run() starts the server loop, waiting for new clients
    void run();
private:
    IncomingConnection server_conn;  // connect to the outside world
    OutgoingConnection lisp_conn; // connect to Lisp server as a client

    // Returns HTML status and content to be displayed in client side.
    // The status is either 200 if the user-supplied ansewr is correct, or 400
    // otherwise.
    std::string compose_response();
};
