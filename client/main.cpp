#include <future>
#include <unistd.h>
#include <iostream>
#include <capnp/ez-rpc.h>

#include "../interface/sample.cap.h"
#include "sample_client.h"

/**
 * @fn dummy_internal_function
 * @brief A dummy function for running any client features.
 */
void dummy_internal_function(SampleClient* client){
  while(1){
    client->initialize();
    sleep(1);
  }
}

/**
 * @fn main
 * @brief Entry point.
 */
int main(){
    auto client = new SampleClient();
    std::thread another_thread([client](){dummy_internal_function(client);});
    client->start();
    another_thread.join();
    delete client;
    return 0;
}