cmake_minimum_required(VERSION 3.16)

project(cap-sample CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
endif()

add_custom_target(
    compile_schema
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMAND capnp compile -o c++ interface/sample.cap
)

add_subdirectory(client/cpp)
add_subdirectory(client/rust)
add_dependencies(client compile_schema client_rust)

add_subdirectory(server/cpp)
add_subdirectory(server/rust)
add_dependencies(server compile_schema server_rust)
