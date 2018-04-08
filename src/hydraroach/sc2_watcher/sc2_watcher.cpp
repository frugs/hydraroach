#include "sc2_watcher.hpp"
#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/ptree.hpp"
#include "httplib.h"
#include <sstream>
#include <vector>

namespace hydraroach {
namespace sc2_watcher {

Sc2Watcher::Sc2Watcher(std::unique_ptr<ISc2WatcherSubscriber> subscriber)
    : subscriber_(std::move(subscriber)) {}

namespace {

boost::property_tree::ptree readJsonResponse(const httplib::Response& resp) {
  boost::property_tree::ptree result;

  if (resp.status == 200) {
    std::stringstream ss;
    ss << resp.body;
    boost::property_tree::read_json(ss, result);
  }

  return result;
}

boost::property_tree::ptree CurrentGameState(httplib::Client& client) {
  auto resp = client.get("/game");
  return resp ? readJsonResponse(*resp) : boost::property_tree::ptree();
}

boost::property_tree::ptree CurrentUiState(httplib::Client& client) {
  auto resp = client.get("/ui");
  return resp ? readJsonResponse(*resp) : boost::property_tree::ptree();
}

bool HasGameFinished(const boost::property_tree::ptree& prev,
                     const boost::property_tree::ptree& cur) {

  if (!prev.get<bool>("isReplay", true) && cur.get<bool>("isReplay", false)) {
    return true;
  }

  std::vector<std::string> prevPlayerResults;
  for (auto& item : prev.get_child("players", boost::property_tree::ptree())) {
    prevPlayerResults.push_back(item.second.get<std::string>("result", "Undecided"));
  }

  std::vector<std::string> curPlayerResults;
  for (auto& item : cur.get_child("players", boost::property_tree::ptree())) {
    curPlayerResults.push_back(item.second.get<std::string>("result", "Undecided"));
  }

  return prevPlayerResults.size() == 2 && curPlayerResults.size() == 2 &&
    prevPlayerResults[0] == "Undecided" && curPlayerResults[0] != "Undecided";

}

bool HasGoneToScoreScreen(const boost::property_tree::ptree& uiState) {

  std::vector<std::string> activeScreens;
  for (auto& item : uiState.get_child("activeScreens", boost::property_tree::ptree())) {
    activeScreens.push_back(item.second.get_value<std::string>());
  }

  return activeScreens.size() > 0;
}
} // namespace

void Sc2Watcher::StartWatchingForReplays() {
  sc2WatchingThread_ = std::thread([this]() {
    httplib::Client client("localhost", 6119);

    auto previousState = CurrentGameState(client);
    while (true) {
      auto currentState = CurrentGameState(client);

      if (HasGameFinished(previousState, currentState)) {
        while (!HasGoneToScoreScreen(CurrentUiState(client))) {
          std::this_thread::sleep_for(std::chrono::seconds(5));
        }

        // Give some time for the game to create the replay
        std::this_thread::sleep_for(std::chrono::seconds(3));

        subscriber_->OnNewReplay();
      }

      previousState = std::move(currentState);
      std::this_thread::sleep_for(std::chrono::seconds(5));
    }
  });
}

} // namespace sc2_watcher
} // namespace hydraroach
