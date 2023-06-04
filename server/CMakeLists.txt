cmake_minimum_required(VERSION 3.16)

find_package(Threads REQUIRED)

add_compile_options(-fpermissive -pthread)
add_executable(server main.cpp ../interface/sample.cap.c++ impl/sample_server.cpp impl/rpc_event.cpp)
target_include_directories(server PUBLIC impl)
target_link_libraries(server capnp kj kj-async capnp-rpc pthread Threads::Threads)