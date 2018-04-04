#include "event.hpp"

namespace hydraroach {
namespace event {

Event::Event(const EventType& eventType, const EventData& eventData)
    : eventType(eventType), eventData(eventData) {}

Event::Event(const EventType& eventType) : eventType(eventType) {}

Event::Event() : Event(EMPTY) {}

const Event Event::shutDownEvent() { return Event(SHUTDOWN); }

const Event Event::logEvent(std::string message) {
  LogEventData eventData = {std::move(message)};
  return Event(LOG, eventData);
}

} // namespace event
} // namespace hydraroach
