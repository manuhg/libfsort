#!/bin/sh
#echo "$# files"
#for v in "$@"
#do
#./fsort_fe ../models/bvlc_googlenet/deploy.prototxt ../models/bvlc_googlenet/bvlc_googlenet.caffemodel \
#../data/ilsvrc12/imagenet_mean.binaryproto ../data/ilsvrc12/synset_words.txt $v
[ -f "temp.txt" ] && rm "temp.txt"
find "$1" -type f -exec echo {} \; > temp.txt
sed "s/$/ 0/" temp.txt > file_list.txt
./fsort_fe $(wc -l file_list.txt | cut -f 1 -d ' ')
#done