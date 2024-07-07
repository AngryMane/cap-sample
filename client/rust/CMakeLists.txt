
unset(RUST_CLIENT_COMPILE_FLAG)
set(RUST_CLIENT_OUTPUT_TARGET "debug")
if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(RUST_CLIENT_COMPILE_FLAG "--release")
    set(RUST_CLIENT_OUTPUT_TARGET "release")
endif()

add_custom_target(
    client_rust
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    COMMAND cargo build --manifest-path ${CMAKE_CURRENT_LIST_DIR}/Cargo.toml ${RUST_CLIENT_COMPILE_FLAG}
    COMMAND mkdir -p ${CMAKE_BINARY_DIR}/client/rust
    COMMAND cp ${CMAKE_CURRENT_LIST_DIR}/target/${RUST_CLIENT_OUTPUT_TARGET}/client_rust ${CMAKE_BINARY_DIR}/client/rust
)