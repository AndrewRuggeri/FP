#! /bin/bash

# Run all scripts on all DB*_B folders
# Arg1 : directory of db impression images *.tif or *.pgm
# Arg2 : output directory

echo "Checking files in ${1}"
echo "Output Directory: ${2}"


for dirPath in ${1}/*/; do
    dbDir=${dirPath%*/} 
    dbName=${dbDir##*/}
    echo "Processing ${dbName}:"
    
    # Create wavelet files
    mkdir -p ${2}/wsq/${dbName}
    bash convertWSQ.sh ${dbDir} ${2}/wsq/${dbName}
    
    # Get Impression Quality Value
    mkdir -p ${2}/data
    bash printQuality.sh ${2}/wsq/${dbName} ${2}/data/printQuality_${dbName}.csv
    
    # Create Minutiea files
    mkdir -p ${2}/mdb/${dbName}
    bash minutiea.sh ${2}/wsq/${dbName} ${2}/mdb/${dbName}
    
    # Match Minutiea
    mkdir -p ${2}/data/matching/${dbName}
    bash matchPrints.sh ${2}/mdb/${dbName} ${2}/data/matching/${dbName}
    
done

echo "done!"
