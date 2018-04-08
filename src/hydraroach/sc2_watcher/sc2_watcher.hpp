#pragma once

#include "sc2_watcher_subscriber.hpp"
#include <thread>

namespace hydraroach {
namespace sc2_watcher {

class Sc2Watcher {

  std::thread sc2WatchingThread_;
  std::unique_ptr<ISc2WatcherSubscriber> subscriber_;

 public:
  Sc2Watcher(std::unique_ptr<ISc2WatcherSubscriber> subscriber);

  void StartWatchingForReplays();
};

} // namespace sc2_watcher
} // namespace hydraroach
