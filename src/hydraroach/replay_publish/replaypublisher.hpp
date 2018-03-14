#import <grpc++/grpc++.h>
#import "hydraroach/proto/hydraroach.grpc.pb.h"

namespace hydraroach {

class ReplayPublisher {
private:
  static const std::string publish_target;

public:
  ReplayPublisher()
      : stub_(HydraRoach::NewStub(grpc::CreateChannel(
            publish_target, grpc::InsecureChannelCredentials()))) {}

  void PublishReplay(const std::string &path);

private:
  std::unique_ptr<HydraRoach::Stub> stub_;
};

} // namespace hydraroach
