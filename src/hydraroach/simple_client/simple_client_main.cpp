#include "hydraroach/replay_publish/replaypublisher.hpp"
#include <grpc++/grpc++.h>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {

  if (argc < 2) {
    return 0;
  }

  if (std::strcmp(argv[1], "announcereplay") == 0) {
    hydraroach::ReplayPublisher replayPublisher;
    replayPublisher.PublishReplay(std::string("Hello, World"));
  }

  return 0;
}
