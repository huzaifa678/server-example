#include "rest-server.h"
#include "grpc-server.h"
#include <pthread.h>

void* runREST(void* arg) {
    RESTServer* server = static_cast<RESTServer*>(arg);
    server->start();
    return nullptr;
}

void* runGRPC(void* arg) {
    GRPCServer* server = static_cast<GRPCServer*>(arg);
    server->start();
    return nullptr;
}

int main() {
    RESTServer restServer(8080);
    GRPCServer grpcServer("0.0.0.0:50051");

    pthread_t restThread, grpcThread;
    pthread_create(&restThread, nullptr, runREST, &restServer);
    pthread_create(&grpcThread, nullptr, runGRPC, &grpcServer);

    pthread_join(restThread, nullptr);
    pthread_join(grpcThread, nullptr);

    return 0;
}
