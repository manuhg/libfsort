#!/bin/sh
echo "$# files"
for v in "$@"
do
./fsort_fe ../models/bvlc_googlenet/deploy.prototxt ../models/bvlc_googlenet/bvlc_googlenet.caffemodel \
../data/ilsvrc12/imagenet_mean.binaryproto ../data/ilsvrc12/synset_words.txt $v
done