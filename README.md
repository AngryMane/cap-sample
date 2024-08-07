# cap-sample

cap-sample is a sample rpc client and server using capnproto, TwoPartyClent and TwoPartyServer.  
If you need a sample of EzRpcServer and Client, see older version of this repository.

## Directory structure

```bash
$ tree -L 1
.
├── CMakeLists.txt  # CMake config file
├── README.md       # the file you are now reading right now
├── client          # client project dir
│   ├── cpp
│   └── rust
├── docs            # doxygen document 
├── doxygen.conf    # doxygen config
├── interface       # capnproto schema and generated sources
└── server          # server project dir
    ├── cpp
    └── rust
```

## RPC patterns

There are only only 2 patterns.

1. The client requests `initialize` event to the server
1. The client requests `subscribe` event to the server, and the server periodically pushes back `push_message` event.


## Build capnproto interface, client and server

```bash
$ mkdir build
$ cd build
$ cmake .. 
$ make
```

## Usage

You can launch the server and connect client like below.

```bash
# run server implemented by cpp
$ ./build/server/cpp/server
# run server implemented by rust
$ ./build/server/rust/server_rust
# run client implemented by cpp
$ ./build/client/cpp/client
# run client implemented by rust
$ ./build/client/rust/client_rust
```

## License
[MIT](https://choosealicense.com/licenses/mit/)