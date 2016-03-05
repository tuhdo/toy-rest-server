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
            server_conn.respond(compose_response());
    }
}

std::string Server::compose_response() {
    lisp_conn.connect();
    lisp_conn.send(server_conn.get_recv_msg().get_method() + "\n");
    std::string response =
        "HTTP/1.0 200 OK\r\n"
        "Content-Length: 5\r\n"
        "Content-Type: text/html\r\n\r\n"
        "<html><body>Question: "
        +  lisp_conn.receive() +
        "<form method=\"PUT\" action=\"/answer\">"
        "Input 2: <input type=\"text\" name=\"input_2\" /> <br/>"
        "<input type=\"submit\" />"
        "</form></body></html>";

    return response;
}
