#import "hydraroach/proto/hydraroach.grpc.pb.h"
#import <grpc++/grpc++.h>

namespace hydraroach {

class HydraRoachService final : public HydraRoach::Service {
  grpc::Status AnnounceReplay(grpc::ServerContext *context,
                              const ReplayAnnouncement *announcement,
                              Empty *reply) override;
};

} // namespace hydraroach
