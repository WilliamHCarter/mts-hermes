#!/bin/sh

mkdir -p ./build
cd ./build
make clean
cmake ..
make -j
./hermes
