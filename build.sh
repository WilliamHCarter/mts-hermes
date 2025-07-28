#!/bin/sh

mkdir -p ./build
cd ./build
make clean
cmake ..
make -j

echo "Running tests..."
./hermes_tests

echo "Running main application..."
./hermes
