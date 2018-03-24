#import "hydraroach/proto/hydraroach.grpc.pb.h"
#import <grpc++/grpc++.h>

namespace hydraroach {

class ExternalService final : public HydraRoachRPC::Service {
  grpc::Status TagReplay(grpc::ServerContext *context,
                         const TagReplayRequest *request,
                         Empty *reply) override;
};

} // namespace hydraroach