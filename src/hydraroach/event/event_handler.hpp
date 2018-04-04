#pragma once

#include "event.hpp"

namespace hydraroach {
namespace event {

class IEventHandler {

 public:
  virtual ~IEventHandler() = default;

  virtual void HandleEvent(const Event& event) = 0;
};

} // namespace event
} // namespace hydraroach
