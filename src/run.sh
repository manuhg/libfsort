#!/bin/sh
#echo "$# files"
#for v in "$@"
#do
#./fsort_fe ../models/bvlc_googlenet/deploy.prototxt ../models/bvlc_googlenet/bvlc_googlenet.caffemodel \
#../data/ilsvrc12/imagenet_mean.binaryproto ../data/ilsvrc12/synset_words.txt $v
./fsort_fe ../models/bvlc_googlenet/bvlc_googlenet.caffemodel \
~/devloka/caffe/examples/_temp/imagenet_val.prototxt fc7 ~/devloka/caffe/examples/_temp/features 10 leveldb
#done