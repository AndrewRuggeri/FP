#! /bin/bash

# Convert fingerprint images from into wsq format using NBIS's cwsq
# Arg1 : directory of 'raw' images

#cwsq .75 wsq $FILE -r width,height,8


echo "Converting files in ${1}"

for file in ${1}/*.*; do
    imgInfo=$(identify -format "%[fx:w],%[fx:h],%[bit-depth]" "${file}")
    echo " File: ${file} : ${imgInfo}"
    cwsq 2.25 wsq ${file} -r ${imgInfo}
done
