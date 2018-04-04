#include "hydraroach/proto/hydraroach.grpc.pb.h"
#include "hydraroach/service/external/request_handler.hpp"
#include <grpc++/grpc++.h>

namespace hydraroach {
namespace external {

class ExternalService final : public HydraRoachRPC::Service {

private:
  std::unique_ptr<IRequestHandler> requestHandler_;

 public:
  explicit ExternalService(std::unique_ptr<IRequestHandler>);

  grpc::Status TagReplay(grpc::ServerContext* context,
                         const TagReplayRequest* request,
                         Empty* reply) override;
};

} // namespace external
} // namespace hydraroach
