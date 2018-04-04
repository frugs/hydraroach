#pragma once

#include "boost/variant/variant.hpp"
#include <string>

namespace hydraroach {
namespace event {

enum EventType { EMPTY, SHUTDOWN, LOG };

struct EmptyEventData {};

struct LogEventData {
  std::string message;
};

struct Event {

  using EventData = boost::variant<EmptyEventData, LogEventData>;

 public:
  static const Event shutDownEvent();
  static const Event logEvent(std::string message);

  Event();
  explicit Event(const EventType& eventType);
  Event(const EventType& eventType, const EventData& eventData);

  EventType eventType;
  EventData eventData;
};

} // namespace event
} // namespace hydraroach
