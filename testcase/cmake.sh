#!/bin/bash

# cmake
cmake -DCMAKE_PREFIX_PATH=./libtorch

# make
make

# run
./testcase
