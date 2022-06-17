cmake_minimum_required(VERSION 3.16)

add_executable(client main.cpp impl/sample_client.cpp ../interface/sample.cap.c++)
target_include_directories(client PUBLIC impl)
target_link_libraries(client capnp kj kj-async capnp-rpc pthread)