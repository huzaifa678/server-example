#include "grpc-server.h"
#include <iostream>

GRPCServer::GRPCServer(const std::string& address)
    : server_address(address) {}

void GRPCServer::start() {
    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "gRPC server listening on " << server_address << std::endl;

    server->Wait();
}
