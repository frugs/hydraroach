#pragma once

namespace hydraroach {
namespace sc2_watcher {

class ISc2WatcherSubscriber {

 public:
  virtual ~ISc2WatcherSubscriber() = default;

  virtual void OnNewReplay() = 0;
};

} // namespace sc2_watcher
} // namespace hydraroach
