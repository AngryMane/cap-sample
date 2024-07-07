cmake_minimum_required(VERSION 3.16)
find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")

add_executable(client main.cpp impl/sample_client.cpp ${CMAKE_SOURCE_DIR}/interface/sample.cap.c++ )
target_include_directories(client PUBLIC impl ${CMAKE_SOURCE_DIR}/interface)
target_link_libraries(client capnp kj kj-async capnp-rpc Threads::Threads)
