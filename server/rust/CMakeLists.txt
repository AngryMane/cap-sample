
unset(RUST_SERVER_COMPILE_FLAG)
set(RUST_SERVER_OUTPUT_TARGET "debug")
if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(RUST_SERVER_COMPILE_FLAG "--release")
    set(RUST_SERVER_OUTPUT_TARGET "release")
endif()

add_custom_target(
    server_rust
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    COMMAND cargo build --manifest-path ${CMAKE_CURRENT_LIST_DIR}/Cargo.toml ${RUST_SERVER_COMPILE_FLAG}
    COMMAND mkdir -p ${CMAKE_BINARY_DIR}/server/rust
    COMMAND cp ${CMAKE_CURRENT_LIST_DIR}/target/${RUST_SERVER_OUTPUT_TARGET}/server_rust ${CMAKE_BINARY_DIR}/server/rust
)