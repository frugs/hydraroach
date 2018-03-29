#include "find_replay.hpp"
#include <cstdlib>

namespace hydraroach {
namespace replay {

namespace {

const char *kSc2ReplaysPath(
    "/Library/Application Support/Blizzard/StarCraft II/Accounts");
}

namespace filesystem = boost::filesystem;

std::pair<std::string, filesystem::path> FindMostRecentReplay() {
  auto home = std::getenv("HOME");

  auto fullSc2ReplaysPath = filesystem::path(home);
  fullSc2ReplaysPath += kSc2ReplaysPath;
  std::time_t mostRecentWrite = 0;
  filesystem::path replayPath;
  for (filesystem::recursive_directory_iterator it(fullSc2ReplaysPath), end;
       it != end; ++it) {
    if (filesystem::is_regular_file(it->path()) &&
        it->path().filename().extension().string() == "SC2Replay") {
      auto lastModified = filesystem::last_write_time(it->path());

      if (lastModified > mostRecentWrite) {
        mostRecentWrite = lastModified;
        replayPath = it->path();
      }
    }
  }

  auto replayHash = "";
  return std::pair<std::string, filesystem::path>(replayHash, replayPath);
}

} // namespace replay
} // namespace hydraroach
