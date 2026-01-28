#include "grpc-service.h"
#include <thread>
#include <chrono>
#include <iostream>

grpc::Status GreeterServiceImpl::SayHello(grpc::ServerContext*,
                                          const hello::HelloRequest* request,
                                          hello::HelloReply* reply) {
    reply->set_message("Hello " + request->name());
    return grpc::Status::OK;
}

grpc::Status GreeterServiceImpl::StreamGreetings(grpc::ServerContext*,
                                                 const hello::HelloRequest* request,
                                                 grpc::ServerWriter<hello::HelloReply>* writer) {
    for (int i = 0; i < 5; ++i) {
        hello::HelloReply reply;
        reply.set_message("Hello " + request->name() + " #" + std::to_string(i+1));
        writer->Write(reply);

        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate streaming delay
    }
    return grpc::Status::OK;
}
