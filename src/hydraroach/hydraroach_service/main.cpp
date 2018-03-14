#include "hydraroach/proto/greeter.grpc.pb.h"
#include "hydraroachservice.hpp"
#include <grpc++/grpc++.h>
#include <iostream>
#include <string>

class GreeterServiceImpl final : public greeter::Greeter::Service {
  grpc::Status SayHello(grpc::ServerContext *context,
                        const greeter::HelloRequest *request,
                        greeter::HelloReply *reply) override {
    std::string hello("Hello, ");
    reply->set_message(hello + request->name());
    return grpc::Status::OK;
  }
};

int main() {
  std::string server_address("0.0.0.0:50051");
  GreeterServiceImpl service;
  hydraroach::HydraRoachService hydraroachService;

  grpc::ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  builder.RegisterService(&hydraroachService);
  // Finally assemble the server.
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
  return 0;
}
