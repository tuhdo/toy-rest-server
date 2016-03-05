#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include <string>
#include <errno.h>
#include <signal.h>

#include "Parser.h"

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
    char buffer[256];
    struct sockaddr_in serv_addr;

    void error(const std::string &msg);
// private:
    // static void sigint_handler(int signo);
};

class ServerConnection: public Connection
{
public:
    ServerConnection() {}
    ServerConnection(const std::string address, int port);
    virtual ~ServerConnection(){}

    int bind();
    int accept();
    int respond(const std::string &response);
    int close();

    int process_captcha_input();
private:
    int client_socket;
    socklen_t cli_len;
    struct sockaddr_in cli_addr;
    HttpMessage recv_msg;
};

class LispServerConnection: public Connection
{
public:
    LispServerConnection() {}
    LispServerConnection(const std::string address, int port);
    virtual ~LispServerConnection(){}

    int connect();
    int close();
};
