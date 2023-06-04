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
    build/server/server &
    SERVER_PID=$!
    timeout 5s build/client/client
    kill ${SERVER_PID}
}

generate_cap_files 
build
run_test 
rm sample.sock