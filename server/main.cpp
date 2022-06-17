#include <capnp/ez-rpc.h>
#include <kj/async-io.h>

#include <future>

#include "../interface/sample.cap.h"
#include "sample_server.h"

/**
 * @fn dummy_internal_function
 * @brief A dummy function for running any server features.
 */
void dummy_internal_function(SampleServer* server) {
  while (1) {
    server->push_message_request();
    sleep(1);
  }
}

/**
 * @fn main
 * @brief Entry point.
 */
int main() {
  auto server = new SampleServer("unix:");
  std::thread another_thread([server]() { dummy_internal_function(server); });
  server->start();
  another_thread.join();
  delete server;

  return 0;
}
