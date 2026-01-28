#include "signal_handler.h"
#include "server.h"
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

Server::Server(int port) : port(port), server_fd(-1) {}

Server::~Server() {
    if (server_fd != -1) close(server_fd);
}

void Server::start() {
    sockaddr_in address{};
    int opt = 1;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) { perror("failed to create socket"); return; }

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(port);

    if (bind(server_fd, (sockaddr*)&address, sizeof(address)) < 0) { perror("bind"); return; }
    if (listen(server_fd, 10) < 0) { perror("listen"); return; }

    std::cout << "Server listening on port " << port << std::endl;

    while (!SignalHandler::stop.load()) {   
        socklen_t addrlen = sizeof(address);
        int client_fd = accept(server_fd, (sockaddr*)&address, &addrlen);
        if (client_fd < 0) {
            if (SignalHandler::stop.load()) break; 
            perror("accept");
            continue;
        }

        // handle client in thread
        pthread_t thread;
        ThreadArg* arg = new ThreadArg{client_fd, this};
        pthread_create(&thread, nullptr,
            [](void* voidArg) -> void* {
                ThreadArg* arg = static_cast<ThreadArg*>(voidArg);
                arg->server->handleClient(arg->client_fd);
                close(arg->client_fd);
                delete arg;
                return nullptr;
            },
            arg
        );
        pthread_detach(thread); // detach the thread
    }

    std::cout << "Server on port " << port << " shutting down gracefully." << std::endl;
    close(server_fd);
}
