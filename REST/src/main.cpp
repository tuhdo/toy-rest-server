#include <iostream>
#include "Server.h"

int main(int argc, char *argv[])
{
    if (argc < 3) {
        std::cerr << "ERROR, no server port and Lisp server pot provided\n";
        exit(1);
    }

    int port = atoi(argv[1]);
    int lisp_port = atoi(argv[2]);

    Server s(port, lisp_port);
    s.run();

    return 0;
}
