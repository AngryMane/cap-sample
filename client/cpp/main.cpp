#include <unistd.h>

#include <future>
#include <iostream>

#include "sample.cap.h"
#include "sample_client.h"

/**
 * @fn main
 * @brief Entry point.
 */
int main() {
  auto client = new SampleClient();
  client->start();
  sleep(1);
  while (client->is_running()) {
    client->initialize();
    sleep(1);
  }
  delete client;
  return 0;
}
