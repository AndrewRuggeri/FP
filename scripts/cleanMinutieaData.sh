#! /bin/bash

# Convert all match output files into a single csv file
# Arg1 : directory of matcher output text files *.txt
# Arg2 : output file name *.csv

echo "Checking files in ${1}"
echo "Output file is ${2}"

defaultCSV=${2}.csv
condensedCSV=${2}_condensed.csv

totalTP=0
totalFP=0
echo "value, match_from, match_to" > ${defaultCSV}
echo "SetName, TrueMatch, falseMatch" > ${condensedCSV}
for file in ${1}/*.txt; do
    echo " File: ${file}"
    
    trueMatch=0
    falseMatch=0
    name=""
    while IFS= read -r var
    do
        stringArray=($var)
        echo "${stringArray[0]}, $(basename ${stringArray[1]}), $(basename ${stringArray[2]})"  >> ${defaultCSV}
        
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

    totalTP=$((totalTP + trueMatch))
    totalFP=$((totalFP + falseMatch))

    echo "${name},${trueMatch},${falseMatch}"  >> ${condensedCSV}
    echo "" >> ${defaultCSV}

done


echo "" >> ${condensedCSV}
echo "TP,TN,FP,FN" >> ${condensedCSV}

# For Average it's a divid by 10
totalTN=$((720-totalFP))
totalFN=$((80-totalTP))
echo "${totalTP},${totalTN},${totalFP},${totalFN}" >> ${condensedCSV}

# Values
echo "" >> ${condensedCSV}

accuracy=$( echo "(${totalTP} + ${totalTN}) / 800" | bc -l)
echo "Accuracy, ${accuracy}" >> ${condensedCSV}

tpr=$( echo "${totalTP} / 80" | bc -l)
echo "TPR, ${tpr}" >> ${condensedCSV}

fpr=$( echo "${totalFP} / 720" | bc -l)
echo "FPR, ${fpr}" >> ${condensedCSV}

