#!/bin/sh
export CC=~/personal/git/clang-p2996/clang-custom/bin/clang
export CXX=~/personal/git/clang-p2996/clang-custom/bin/clang++
mkdir build
cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..
