#!/bin/sh
#for cmake https://github.com/BVLC/caffe/pull/1667
cd ../bhtsne
./build.sh
cd ../src
set -x #echo each command before executing
rm -rf build
mkdir build

[ -f libfsort.a ] && rm libfsort.a
cd build
cmake .. && make -j8 #let make create upto 8 threads