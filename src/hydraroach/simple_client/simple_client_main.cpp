#include <iostream>
#include <string>
#include <grpc++/grpc++.h>
#include "hydraroach/proto/greeter.grpc.pb.h"

class GreeterClient {
public:
  GreeterClient(const std::shared_ptr<grpc::Channel> channel)
      : stub_(greeter::Greeter::NewStub(channel)){};
  // Assambles the client's payload, sends it and presents the
  // response back from the server.
  std::string SayHello(const std::string &user) {
    // Data we are sending to the server.
    greeter::HelloRequest request;
    request.set_name(user);

    // Container for the data we expect from the server.
    greeter::HelloReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    grpc::ClientContext context;

    // The actual RPC.
    grpc::Status status = stub_->SayHello(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.message();
    } else {
      return "RPC failed";
    }
  }

private:
  std::unique_ptr<greeter::Greeter::Stub> stub_;
};

int main() {

  // Instantiate the client. It requires a channel, out of which the
  // actual RPCs are created. This channel models a connection to an
  // endpoint (in this case, localhost at port 50051). We indicate
  // that the channel isn't authenticated (use of
  // InsecureCredentials()).
  GreeterClient greeter(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));
  std::string user("frugs");
  std::string reply = greeter.SayHello(user);
  std::cout << "Greeter received: " << reply << std::endl;

  return 0;
}
