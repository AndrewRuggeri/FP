#! /bin/bash

# match all minutiae files in a directory using BOZORTH3
# Arg1 : directory of 'xyt' files
# Arg2 : result file name

# Match against 1 file (_3 to _4) with a threshold of 20
# ex: bozorth3 -m1 -A outfmt=spg -T 20 -p ../FVC/101_3.xyt ../FVC/101_4.xyt
# ex: bozorth3 -m1 -A outfmt=spg -T 20 -p ../FVC/101_3.xyt ../FVC/*.xyt

echo "Checking files in ${1}"
echo "Output directory is ${2} "

for file in ${1}/*_1.xyt; do
    echo 
    echo " File: ${file}"
    name="$(basename ${file})"  # get filename
    bozorth3 -b -m1 -A outfmt=spg -o ${2}/${name%.*}_results.txt -T 20 -p ${file} ${1}/*.xyt 
done

