#!/usr/bin/env bash

WORKDIR=$(pwd)

function generate_cap_files (){
  cd ${WORKDIR}
  capnp compile -o c++ interface/sample.cap
  cd ${WORKDIR}
}

function build (){
  cd ${WORKDIR}
  rm -rf build
  mkdir build
  cd build
  cmake ..
  make
  cd ${WORKDIR}
}

function run_test (){
    build/server/cpp/server &
    SERVER_PID=$!
    sleep 1
    timeout 5s build/client/cpp/client
    kill ${SERVER_PID}
}

if [ -z "$1" ]; then
  generate_cap_files 
  build
fi

if [ "$1" = "test" ]; then
  rm sample.sock
  run_test 
  rm sample.sock
fi


