#include "hydraroach/service/external/external_service.hpp"

int main() {
  std::string server_address("0.0.0.0:50051");
  hydraroach::ExternalService externalService;

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&externalService);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  (*server).Wait();
  return 0;
}
