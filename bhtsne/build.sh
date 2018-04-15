#!/usr/bin/zsh
set -x
if [[ $# -gt 0 ]]; then
    [ -d build ] && rm -rf build
    mkdir build  && cd build
    cmake .. && make -j8
    cp libbhtsne.* ../../lib/
    cp libbhtsne.* ../
    cd ..
    incl_dir=../include/bhtsne
    rm -rf $incl_dir
    mkdir -p $incl_dir
    cp *.h $incl_dir/
else
    cd build
    make && cp -v libbhtsne.* ../../lib/static/ &&cp -v libbhtsne.* ../../lib/ && sudo cp -v libbhtsne.* /usr/lib/
    cd ..
fi
