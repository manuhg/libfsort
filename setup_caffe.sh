#!/bin/sh
set -x
git clone git@github.com:bvlc/caffe.git
cd caffe
# sed -i '/Flags/a link_libraries("-static")' CMakeLists.txt
# mkdir cmake_build
# cd cmake_build
# cmake .. -DCPU_ONLY=ON -DBUILD_SHARED_LIBS=OFF

# cmake . -DCMAKE_BUILD_TYPE=Debug     # switch to debug
# make -j 12 && make install           # installs by default to build_dir/install
# cmake . -DCMAKE_BUILD_TYPE=Release   # switch to release
# make -j 12 && make install           # doesn’t overwrite debug install
# make symlink
cp Makefile.config.example Makefile.config
make all -j8
make test -j8
make runtest -j8
make distribute -j8