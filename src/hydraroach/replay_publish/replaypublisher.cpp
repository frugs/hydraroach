#include "replaypublisher.hpp"

namespace hydraroach {

void ReplayPublisher::PublishReplay(const std::string &path) {
  grpc::ClientContext context;
  hydraroach::ReplayAnnouncement request;
  request.set_path(path);
  hydraroach::Empty reply;

  stub_->AnnounceReplay(&context, request, &reply);
}

const std::string ReplayPublisher::publish_target = std::string("localhost:50051");

}
