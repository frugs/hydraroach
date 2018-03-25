#include "hydraroach/client/external_client.hpp"
#include <grpc++/grpc++.h>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {

  hydraroach::ExternalClient client;
  client.TagReplay("hello", "world");

  return 0;
}
