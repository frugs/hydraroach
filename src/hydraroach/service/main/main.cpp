#include "boost/variant/get.hpp"
#include "hydraroach/event/event_queue.hpp"
#include "hydraroach/service/external/external_service.hpp"

class EventHandler : public hydraroach::event::IEventHandler {
 public:
  void HandleEvent(const hydraroach::event::Event& event) override {
    switch (event.eventType) {
    case hydraroach::event::EMPTY:
      break;
    case hydraroach::event::SHUTDOWN:
      break;
    case hydraroach::event::LOG:
      std::cout << boost::get<hydraroach::event::LogEventData>(event.eventData).message
                << std::endl;
      break;
    }
  }
};

class RequestHandler : public hydraroach::external::IRequestHandler {

  std::shared_ptr<hydraroach::event::EventQueue> eventQueue_{};

 public:
  explicit RequestHandler(std::shared_ptr<hydraroach::event::EventQueue> eventQueue)
      : eventQueue_(std::move(eventQueue)) {}

  void TagReplay(std::string replayHash, std::string tags) override {
    (*eventQueue_).SubmitEvent(hydraroach::event::Event::logEvent(replayHash + ":" + tags));
  }
};

int main() {
  auto eventQueue =
      std::make_shared<hydraroach::event::EventQueue>(std::make_unique<EventHandler>());
  hydraroach::external::ExternalService externalService(
      std::make_unique<RequestHandler>(eventQueue));

  std::string server_address("0.0.0.0:50051");
  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&externalService);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  (*eventQueue).StartProcessing();
  (*server).Wait();
  return 0;
}
