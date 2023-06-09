cmake_minimum_required(VERSION 3.16)

find_package(Threads REQUIRED)

add_executable(client main.cpp impl/sample_client.cpp ../interface/sample.cap.c++ )
target_compile_options(client PUBLIC -O0 -g)

target_include_directories(client PUBLIC impl ../custom)
target_link_libraries(client capnp kj kj-async capnp-rpc Threads::Threads)
