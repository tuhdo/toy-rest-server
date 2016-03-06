#include <string>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include <stdio.h>
#include <string.h>

#include "Parser.h"

#define BUF_SIZE 4096

// Represent a connection between two sockets.
// Each class has a socket and is responsible for 
class Connection
{
public:
    Connection() {}
    Connection(const std::string address, int port);
    virtual ~Connection(){}

    int listen();
    int close();
protected:
    // later we can support for more ports and clients by using containers
    // instead of simple integer.
    int socket, port;
    std::string address;
    char buffer[BUF_SIZE];
    struct sockaddr_in serv_addr;

    void error(const std::string &msg);
// private:
    // static void sigint_handler(int signo);
};

class IncomingConnection: public Connection
{
public:
    const HttpMessage get_recv_msg() const {
        return recv_msg;
    }

    IncomingConnection() {}
    IncomingConnection(const std::string address, int port);
    virtual ~IncomingConnection(){}

    int bind();
    int accept();
    int respond(const std::string &response);
    int close();
private:
    int client_socket;
    socklen_t cli_len;
    struct sockaddr_in cli_addr;
    HttpMessage recv_msg;
};

class OutgoingConnection: public Connection
{
public:
    OutgoingConnection() {}
    OutgoingConnection(const std::string address, int port);
    virtual ~OutgoingConnection(){}

    int connect();
    int send(const std::string &msg);
    std::string receive();
    int close();
};
