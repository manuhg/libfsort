#!/bin/zsh
#set -x #echo each command before executing
#for cmake https://github.com/BVLC/caffe/pull/1667
#cd ../bhtsne
#./build.sh
#cd ../src
set -x
var=1
flags=""
exec_flag=-DBUILD_EXECUTABLE=ON
if [[ $# -gt 0 ]]; then
    rm -rf build
    mkdir build
    cd build
    ((var=var+1))
    [ -f libfsort.a ] && rm libfsort.a
    [ $1 = "exec" ] && flags=$exec_flag
    cmake .. $flags && make -j8 #let make create upto 8 threads
else
    cd build
    ((var=var+1))
    make -j8
fi
[ $var -gt 1 ] && cd ..
