#include "Server.h"
#include <iostream>

Server::Server(int port, int lisp_port) : server_conn("127.0.0.1", port),
                                          lisp_conn("127.0.0.1", lisp_port) {
}

void Server::run() {
    server_conn.bind();
    server_conn.listen();

    for (;; ) {
        if (!server_conn.accept())
            server_conn.respond(get_response);
        std::cout << "question: " << compose_response() << std::endl;
    }
}

std::string Server::compose_response() {
    lisp_conn.connect();
    lisp_conn.send(server_conn.get_recv_msg().get_method() + "\n");

    return lisp_conn.receive();
}
