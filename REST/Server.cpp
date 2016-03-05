#include "Server.h"

Server::Server(int port, int lisp_port) : server_conn("127.0.0.1", port),
                                          lisp_conn("127.0.0.1", lisp_port) {

    lisp_conn.connect();
}

void Server::run() {
    server_conn.bind();
    server_conn.listen();

    for (;; ) {
        server_conn.accept(get_response);
    }
}
