#pragma once

#include <string>
#include <boost/filesystem.hpp>

namespace hydraroach {
namespace replay {

std::pair<std::string, boost::filesystem::path> FindMostRecentReplay();

} // replay
} // hydraroach

