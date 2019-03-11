#! /bin/bash

# Run all scripts on all DB*_B folders
# Arg1 : directory of db impression images *.tif or *.pgm
# Arg2 : output directory

echo "Checking files in ${1}"
echo "Output Directory: ${2}"


for dirPath in ${1}/*/; do
    dbDir=${dirPath%*/} 
    dbName=${dbDir##*/}
    echo "Processing ${dbDir}:"

    mkdir -p ${2}/pgm/${dbName}
    mkdir -p ${2}/data/
    echo ${dbName} >> ${2}/data/timing.txt

    for i in {1..4}
    do
       echo "Test ${i}" >> ${2}/data/timing.txt
       (time ./FP -id ${dirPath} -od ${2}/pgm/${dbName}/) >> ${2}/data/timing.txt 2>&1
    done

done

echo "done!"
