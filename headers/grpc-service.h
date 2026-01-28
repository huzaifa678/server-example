#pragma once
#include <grpcpp/grpcpp.h>
#include "greeter.grpc.pb.h"

class GreeterServiceImpl final : public hello::Greeter::Service {
public:
    grpc::Status SayHello(grpc::ServerContext* context,
                          const hello::HelloRequest* request,
                          hello::HelloReply* reply) override;

    grpc::Status StreamGreetings(grpc::ServerContext* context,
                                 const hello::HelloRequest* request,
                                 grpc::ServerWriter<hello::HelloReply>* writer) override;
};
