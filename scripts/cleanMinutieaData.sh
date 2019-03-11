#! /bin/bash

# Convert all match output files into a single csv file
# Arg1 : directory of matcher output text files *.txt
# Arg2 : output file name *.csv

echo "Checking files in ${1}"
echo "Output file is ${2}"

echo "value, match_from, match_to" > ${2}
echo "SetName, TrueMatch, falseMatch" > condensed_${2}
for file in ${1}/*.txt; do
    echo " File: ${file}"
    
    trueMatch=0
    falseMatch=0
    name=""
    while IFS= read -r var
    do
        stringArray=($var)
        echo "${stringArray[0]}, $(basename ${stringArray[1]}), $(basename ${stringArray[2]})"  >> ${2}
        
        matchPrintName=$(basename ${stringArray[1]})
        matchPrintSeries=${matchPrintName:0:4}
        
        currentPrintName=$(basename ${stringArray[2]})
        currentPrintSeries=${currentPrintName:0:4}
        
        name=${matchPrintSeries}
        
        if [[ "$matchPrintSeries" == "$currentPrintSeries" ]]; then
            trueMatch=$((trueMatch + 1))
        else
            falseMatch=$((falseMatch + 1))
        fi
        
    done < $file
    
    echo "${name},${trueMatch},${falseMatch}"  >> condensed_${2}
  
    
    echo "" >> ${2}
done


