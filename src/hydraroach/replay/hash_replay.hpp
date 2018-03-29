#pragma once

#include <string>
#include <boost/filesystem.hpp>

namespace hydraroach {
namespace replay {

std::string HashReplay(boost::filesystem::path replayPath);

} // replay
} // hydraroach