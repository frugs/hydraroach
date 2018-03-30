#pragma once

#include <boost/filesystem.hpp>

namespace filesystem = boost::filesystem;

namespace hydraroach {
namespace replay {

std::string HashReplay(filesystem::path replayPath);

} // namespace replay
} // namespace hydraroach