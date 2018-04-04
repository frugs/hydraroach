#include "external_service.hpp"

namespace hydraroach {
namespace external {

ExternalService::ExternalService(std::unique_ptr<IRequestHandler> requestHandler)
    : requestHandler_(std::move(requestHandler)) {}

grpc::Status ExternalService::TagReplay(grpc::ServerContext*,
                                        const TagReplayRequest* request,
                                        Empty*) {
  (*requestHandler_).TagReplay(request->replayhash(), request->tags());

  return grpc::Status::OK;
}

} // namespace external
} // namespace hydraroach
