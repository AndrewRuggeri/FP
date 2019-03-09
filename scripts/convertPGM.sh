#! /bin/bash

# Convert all tif images in a given directory to pgm files placed in a output
# Arg1 : directory of 'tif' images
# Arg2 : output directory

echo "Checking files in ${1}"
echo "Output directory is ${2}"

for file in ${1}/*.tif; do
    echo " File: ${file}"
    name="$(basename ${file})"  # get filename
    convert ${file} -colorspace GRAY ${2}/${name%.*}.pgm
done


