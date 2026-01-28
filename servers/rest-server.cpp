#include "rest-server.h"
#include <grpcpp/grpcpp.h>
#include "greeter.grpc.pb.h"
#include <unistd.h>
#include <cstring>
#include <iostream>

RESTServer::RESTServer(int port) : Server(port) {}

void RESTServer::handleClient(int client_fd) {
    const char* header =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Transfer-Encoding: chunked\r\n\r\n";
    write(client_fd, header, strlen(header));

    auto channel = grpc::CreateChannel("127.0.0.1:50051", grpc::InsecureChannelCredentials());
    hello::Greeter::Stub stub(channel);

    hello::HelloRequest request;
    request.set_name("REST Client"); 

    grpc::ClientContext context;
    std::unique_ptr<grpc::ClientReader<hello::HelloReply>> reader(
        stub.StreamGreetings(&context, request)
    );

    hello::HelloReply reply;
    char chunk[1024];

    while (reader->Read(&reply)) {
        std::string msg = reply.message() + "\n";
        snprintf(chunk, sizeof(chunk), "%zx\r\n%s\r\n", msg.size(), msg.c_str());
        write(client_fd, chunk, strlen(chunk));
        fsync(client_fd); // flush immediately
    }

    write(client_fd, "0\r\n\r\n", 5);

    grpc::Status status = reader->Finish();
    if (!status.ok()) {
        std::cerr << "gRPC streaming failed: " << status.error_message() << std::endl;
    }

    close(client_fd);
}
