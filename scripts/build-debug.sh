#!/bin/env bash

cmake --preset debug

cp build/build-debug/compile_commands.json .

cd build/build-debug 

make 

cd ../..
