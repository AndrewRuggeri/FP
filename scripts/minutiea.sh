#! /bin/bash

# Create minutiae files for all wsq files in directory using MIDTCT
# Arg1 : directory of 'wsq' images
# Arg2 : output directory

echo "Checking files in ${1}"
echo "Output directory is ${2}"

for file in ${1}/*.wsq; do
    echo " File: ${file}"
    name="$(basename ${file})"  # get filename
    mindtct -m1 ${file} ${2}/${name%.*}
done
