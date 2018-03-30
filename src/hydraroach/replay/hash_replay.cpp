#include "hash_replay.hpp"
#include "picosha2.h"
#include <iterator>
#include <sstream>

namespace hydraroach {
namespace replay {

namespace {

unsigned int kSha256DigestSize = 32;
}

std::string HashReplay(filesystem::path replayPath) {
  filesystem::ifstream replayStream;
  replayStream.open(replayPath, std::ios_base::binary);

  std::vector<unsigned char> hash(kSha256DigestSize);
  picosha2::hash256(std::istreambuf_iterator<char>(replayStream),
                    std::istreambuf_iterator<char>(),
                    hash.begin(),
                    hash.end());

  return picosha2::bytes_to_hex_string(hash);
}

} // namespace replay
} // namespace hydraroach
