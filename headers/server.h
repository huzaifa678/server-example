#pragma once
#include <netinet/in.h>

class Server {
    struct ThreadArg {
        int client_fd;
        Server* server;
    };
protected:
    int server_fd;
    int port;

    virtual void handleClient(int client_fd) = 0;

public:
    explicit Server(int port);
    virtual ~Server();

    virtual void start();
};
