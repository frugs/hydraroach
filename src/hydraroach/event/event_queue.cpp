#include "event_queue.hpp"

namespace hydraroach {
namespace event {

EventQueue::EventQueue(std::unique_ptr<IEventHandler> eventHandler)
    : eventHandler_(std::move(eventHandler)) {}

void EventQueue::StartProcessing() {
  eventHandlerThread_ = std::thread([this]() {
    Event event;
    do {
      queue_.wait_dequeue(event);

      eventHandler_->HandleEvent(event);
    } while (event.eventType != EventType::SHUTDOWN);
  });
}

void EventQueue::SubmitEvent(const Event& event) {
  queue_.enqueue(event);
}

} // namespace event
} // namespace hydraroach
