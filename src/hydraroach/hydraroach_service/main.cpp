#include "hydraroachservice.hpp"
#include <grpc++/grpc++.h>
#include <iostream>
#include <string>

int main() {
  std::string server_address("0.0.0.0:50051");
  hydraroach::HydraRoachService hydraroachService;

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&hydraroachService);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();
  return 0;
}
