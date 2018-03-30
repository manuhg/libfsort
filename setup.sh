#!/usr/bin/zsh
pacaur -S cblas
pacaur -S google-glog gflags lmdb hdf5 opencv2 atlas-lapack boost boost-libs ilmbase
#if atlast-lapack pacaur insstall doesnt work 
#git clone https://aur.archlinux.org/atlas-lapack.git
#cd atlas-lapack
#nano PKGBUILD
# add --cripple-atlas-performance to ./configure command
#makepkg -si 
cd /usr/lib64
sudo ln -s libcblas.so libcblas.so.3
sudo ln -s libIlmImf-2_2.so.23 libIlmImf-2_2.so.22
sudo ln -s libIex-2_2.so.23 libIex-2_2.so.12
sudo ln -s libHalf.so.23.0.0 libHalf.so.12
sudo ln -s libIlmThread-2_2.so.23 libIlmThread-2_2.so.12
