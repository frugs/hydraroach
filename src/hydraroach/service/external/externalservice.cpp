#import "externalservice.hpp"
#import <iostream>

namespace hydraroach {

grpc::Status ExternalService::TagReplay(grpc::ServerContext *context,
                                        const TagReplayRequest *request,
                                        Empty *reply) {
  std::cout << "Tagging replay '" << request->replayhash()
            << "' with tags: " << request->tags() << std::endl;

  return grpc::Status::OK;
}

} // namespace hydraroach
