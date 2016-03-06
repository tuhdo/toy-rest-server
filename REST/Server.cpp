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
    std::string send_msg, method = server_conn.get_recv_msg().get_method();
    std::string response;

    lisp_conn.connect();

    if (method.compare("GET") == 0) {
        send_msg = server_conn.get_recv_msg().get_method();
        lisp_conn.send(send_msg + "\n");

        response = "HTTP/1.0 200 OK\r\n"
            "Content-Length: 100\r\n"
            "Content-Type: text/html\r\n\r\n"
            "<html><body>Question: "
            + lisp_conn.receive()  +
            "<form method=\"post\" action=\"/answer\">"
            "Answer: <input type=\"text\" name=\"captcha_result\" /> <br/>"
            "<input type=\"submit\" />"
            "</form></body></html>";

        return response;
    }
    else
        send_msg = server_conn.get_recv_msg().get_answer();

    lisp_conn.send(send_msg + "\n");
    std::string result = lisp_conn.receive();

    std::cout << "Result: " << result[0] << "\n";

    if (result[0] == 'T')
        response = "HTTP/1.0 200 OK\r\n"
            "Content-Length: 100\r\n"
            "Content-Type: text/html\r\n\r\n"
            "<html><body><h1>Correct</h1>"
            "</body></html>";
    else
        response = "HTTP/1.0 400 Bad Answer\r\n"
            "Content-Length: 100\r\n"
            "Content-Type: text/html\r\n\r\n"
            "<html><body><h1>Bad Answer</h1>"
            "</body></html>";

    return response;
}
