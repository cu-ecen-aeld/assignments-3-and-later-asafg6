#! /bin/bash

filedir=$1
searchstr=$2

if [ filedir == "" ]; then
    echo "Please enter the directory path"
    exit 1
fi

if [ searchstr == "" ]; then
    echo "Please enter the string to search"
    exit 1
fi

if [ ! -d "$filedir" ]; then
    echo "Directory does not exist"
    exit 1
fi

num_all_files=$(find $filedir -type f | wc -l)
num_matching_lines=$(grep -r $searchstr $filedir | wc -l)

echo "The number of files are $num_all_files and the number of matching lines are $num_matching_lines"
