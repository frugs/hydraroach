#include "hydraroach/client/externalclient.hpp"
#include <grpc++/grpc++.h>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {

  hydraroach::ExternalClient client;
  client.TagReplay("hello", "world");

  return 0;
}
