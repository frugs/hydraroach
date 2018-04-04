#pragma once
namespace hydraroach {
namespace external {

class IRequestHandler {

 public:
  virtual ~IRequestHandler() = default;

  virtual void TagReplay(std::string replayHash, std::string tags) = 0;
};

} // namespace external
} // namespace hydraroach
