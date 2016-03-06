#include "Connection.h"

Connection::Connection(const std::string address, int port):address(address), port(port) {}

int Connection::listen() {
    return ::listen(socket, 5);
}

void Connection::error(const std::string &msg) {
    ::perror(msg.c_str());
    exit(1);
}

int IncomingConnection::bind() {
    if (::bind(socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    return 0;
}

int IncomingConnection::accept() {
    cli_len = sizeof(cli_addr);

    client_socket = ::accept(socket, (struct sockaddr *) &cli_addr, &cli_len);

    if (client_socket < 0)
        error("ERROR on accept");

    memset(&buffer, 0, BUF_SIZE);

    if (read(client_socket,buffer,BUF_SIZE) < 0)
        error("ERROR reading from socket");

    recv_msg.set_raw_msg(buffer);
    Parser::parse(recv_msg);

    printf("Here is the message: %s\n\n",buffer);

    return 0;
}

int IncomingConnection::respond(const std::string &response) {
    int n;

    if (recv_msg.get_uri().compare("/question") == 0) {

        n = write(client_socket, response.c_str(), response.length());

        if (n < 0)
            error("ERROR writing to socket");
    }

    return ::close(client_socket);
}

int IncomingConnection::close() {
    int n;

    n = ::close(socket);
    if (n) return n;

    n = ::close(client_socket);
    if (n) return n;

    return 0;
}

IncomingConnection::IncomingConnection(std::string message, int port) {
    socket = ::socket(AF_INET, SOCK_STREAM, 0);

    if (socket < 0)
        error("ERROR opening socket");

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
}

int OutgoingConnection::connect() {
    //Create socket
    socket = ::socket(AF_INET , SOCK_STREAM , 0);

    printf("lisp port: %d\n", port);

    if (socket == -1) {
        printf("Could not create socket");
    }

    serv_addr.sin_addr.s_addr = inet_addr(address.c_str());
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    //Connect to remote server
    if (::connect(socket , (struct sockaddr *)&serv_addr , sizeof(serv_addr)) < 0) {
        ::perror("connect failed. Error");
        return 1;
    }

    return 0;
}

int OutgoingConnection::send(const std::string &msg) {
    if (!write(socket, msg.c_str(), msg.length())){
        ::perror("cannot send request to Lisp server. Error");
        return 1;
    }

    return 0;
}

std::string OutgoingConnection::receive() {
    if (read(socket,buffer,255) < 0)
        error("ERROR reading from socket");

    ::close(socket);

    std::string res(buffer);

    return res;
}

OutgoingConnection::OutgoingConnection(const std::string address, int port) {
    this->address = address;
    this->port = port;
}

int OutgoingConnection::close() {
    return ::close(socket);
}
