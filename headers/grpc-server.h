#pragma once
#include <grpcpp/grpcpp.h>
#include "grpc-service.h"
#include <string>

class GRPCServer {
public:
    GRPCServer(const std::string& address);
    void start();

private:
    std::string server_address;
    GreeterServiceImpl service;
};
