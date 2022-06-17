# cap-sample

cap-sample is a sample rpc client and server using capnproto, EzPRCServer.  

## Directory structure

```bash
$ tree -L 1
.
├── CMakeLists.txt  # CMake config file
├── README.md       # the file you are now reading right now
├── client          # client project dir
├── docs            # doxygen document 
├── doxygen.conf    # doxygen config
├── interface       # capnproto schema and generated sources
└── server          # server project dir
```

## RPC patterns

There are only only 2 patterns.

1. The client requests `initialize` event to the server
1. The client requests `subscribe` event to the server, and the server periodically pushes back `push_message` event.


## Build capnproto interface

Basically, you don't need to do this because generated files are commited.

```bash
$ cd interface
$ capn compile -o c++ sample.cap
$ ls
sample.cap  sample.cap.c++  sample.cap.h
```

## Build client and server

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Usage

You can launch the server like below.  

```bash
$ cd build/server
$ ./server
```

You can run the client like below.  

```bash
$ cd build/client
$ ./client
```

## License
[MIT](https://choosealicense.com/licenses/mit/)