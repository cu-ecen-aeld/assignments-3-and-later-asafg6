#! /bin/bash

writefile=$1
writestr=$2



if [[ "$writefile" == "" ]] || [[ "$writestr" == "" ]]; then
    echo "Please enter the file path and the string to write"
    exit 1
fi

mkdir -p $(dirname "$writefile")

if [ $? != 0 ]; then
    echo "Error creating file"
    exit 1
fi

echo "$writestr" > "$writefile"

if [ $? != 0 ]; then
    echo "Error writing to file"
    exit 1
fi
