#!/usr/bin/env bash

WORKDIR=$(pwd)

function run_test (){
    build/server/cpp/server &
    SERVER_PID=$!
    sleep 1
    timeout 5s build/client/cpp/client
    kill ${SERVER_PID}
}

rm sample.sock
run_test 
rm sample.sock



