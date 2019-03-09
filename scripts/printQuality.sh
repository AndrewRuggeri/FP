#! /bin/bash

# Export print quality for all images based on NBIS NFIQ
# 1 = high quality, 5 = low quality
# Arg1 : directory of 'wsq' images
# Arg2 : output file for result csv

echo "Checking files in ${1}"

echo "name,rate" > ${2}

for file in ${1}/*.wsq; do
    result=$(nfiq ${file})
    echo "$(basename ${file}),${result}" >> ${2}
    echo " File: ${file} : ${result}"
done
