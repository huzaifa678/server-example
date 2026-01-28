#pragma once
#include "server.h"

class RESTServer : public Server {
protected:
    void handleClient(int client_fd) override;

public:
    explicit RESTServer(int port);
};
