#include "hydraroach/proto/hydraroach.grpc.pb.h"
#include <grpc++/grpc++.h>

namespace hydraroach {

class ExternalClient {
private:
  static const std::string kExternalServiceAddress;

public:
  ExternalClient() : stub_(HydraRoachRPC::NewStub(grpc::CreateChannel(
      kExternalServiceAddress,
      grpc::InsecureChannelCredentials()))) {};

  void TagReplay(const std::string &replayHash, const std::string &tags);

private:
  std::unique_ptr<HydraRoachRPC::Stub> stub_;
};

} // namespace hydraroach
