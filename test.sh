#!/bin/bash

function test {
    for (( count=0; count<10; count++ ))
    do
    FILEIN=$(printf $DIRECTORY/test.%d.in "$count")
    FILEOUT=$(printf $DIRECTORY/test.%d.out "$count")
    n=$(sed -n '1 p' $FILEIN)
    COUNTS=$(sed -n '1 p' $FILEOUT)
    MASK=$(sed -n '2 p' $FILEOUT)
    result=$(./bits $n $TYPE)
    RESULT_ARR=(${result[@]})
    RESULT_COUNTS="${RESULT_ARR[0]}"
    RESULT_MASK="${RESULT_ARR[1]}"

    echo "Expected mask $MASK"
    echo "Actual mask $RESULT_MASK"

    echo "Expected count $COUNTS"
    echo "Actual count $RESULT_COUNTS"
    
    done
}

DIRECTORY=$1
TYPE=$2
test