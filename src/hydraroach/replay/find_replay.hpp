#pragma once

#include <boost/filesystem.hpp>
#include <string>

namespace filesystem = boost::filesystem;

namespace hydraroach {
namespace replay {

std::pair<std::string, filesystem::path> FindMostRecentReplay();

} // namespace replay
} // namespace hydraroach
