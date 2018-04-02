#!/bin/sh
#for cmake https://github.com/BVLC/caffe/pull/1667
[ -f libfsort.a ] && echo "rm libfsort.a" && rm libfsort.a
[ -f libfsort ] && echo "rm libfsort" && rm libfsort
echo "cmake ."
cmake . && echo "make -j8" && make -j8
#/build/examples/cpp_classification/classification.bin \
#  models/bvlc_reference_caffenet/deploy.prototxt \
#  models/bvlc_reference_caffenet/bvlc_reference_caffenet.caffemodel \
#  data/ilsvrc12/imagenet_mean.binaryproto \
#  data/ilsvrc12/synset_words.txt \
#  ~/devloka/tf/njn.jpg
