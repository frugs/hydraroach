#include "externalclient.hpp"

namespace hydraroach {

void ExternalClient::TagReplay(const std::string &replayHash, const std::string &tags) {
  grpc::ClientContext context;
  hydraroach::TagReplayRequest request;
  request.set_replayhash(replayHash);
  request.set_tags(tags);
  hydraroach::Empty reply;

  stub_->TagReplay(&context, request, &reply);
}

const std::string ExternalClient::kExternalServiceAddress =
    std::string("localhost:50051");

} // namespace hydraroach
