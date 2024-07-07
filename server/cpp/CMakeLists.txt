cmake_minimum_required(VERSION 3.16)

find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")

add_executable(server main.cpp ${CMAKE_SOURCE_DIR}/interface/sample.cap.c++ impl/sample_server.cpp impl/rpc_event.cpp )
target_include_directories(server PUBLIC impl ${CMAKE_SOURCE_DIR}/interface)
target_link_libraries(server capnp kj kj-async capnp-rpc pthread Threads::Threads)
