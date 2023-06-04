#include <capnp/ez-rpc.h>
#include <unistd.h>

#include <future>
#include <iostream>

#include "../interface/sample.cap.h"
#include "sample_client.h"

/**
 * @fn main
 * @brief Entry point.
 */
int main() {
  auto client = new SampleClient();
  client->start();
  while (1) {
    client->initialize();
    sleep(1);
  }
  delete client;
  return 0;
}