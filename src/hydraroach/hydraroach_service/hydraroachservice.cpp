#import "hydraroachservice.hpp"
#import <iostream>

namespace hydraroach {

grpc::Status
HydraRoachService::AnnounceReplay(grpc::ServerContext *context,
                                  const ReplayAnnouncement *announcement,
                                  Empty *reply) {
  std::cout << "Announcing replay with path: " << announcement->path()
            << std::endl;

  return grpc::Status::OK;
}

} // namespace hydraroach
