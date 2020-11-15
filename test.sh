#!/bin/bash

function test {
    for (( count=0; count<10; count++ ))
    do
    FILEIN=$(printf 0.BITS/king/test.%d.in "$count")
    FILEOUT=$(printf 0.BITS/king/test.%d.out "$count")
    n=$(sed -n '1 p' $FILEIN)
    COUNT_STEP=$(sed -n '1 p' $FILEOUT)
    MASK=$(sed -n '2 p' $FILEOUT)

    echo $TYPE
    result=$(./bits n $TYPE)
    echo "$result" 
    done
}

TYPE=$1
test