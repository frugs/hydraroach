#pragma once

#include "blockingconcurrentqueue.h"
#include "event.hpp"
#include "event_handler.hpp"

namespace hydraroach {
namespace event {

class EventQueue {

private:
  moodycamel::BlockingConcurrentQueue<Event> queue_;
  const std::unique_ptr<IEventHandler> eventHandler_;
  std::thread eventHandlerThread_;

public:
  explicit EventQueue(std::unique_ptr<IEventHandler> eventHandler);

  void SubmitEvent(const Event& event);
  void StartProcessing();
};

} // namespace event
} // namespace hydraroach
