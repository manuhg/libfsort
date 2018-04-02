#!/usr/bin/zsh
set -x 
[ -d build ] && rm -rf build
mkdir build  && cd build
cmake .. && make -j8
cp libbhtsne.a ../../lib/ && rm -rf build
cd ..
incl_dir=../include/bhtsne
rm -rf $incl_dir
mkdir -p $incl_dir
cp *.h $incl_dir/
