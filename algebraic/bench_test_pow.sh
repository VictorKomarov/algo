#!/bin/bash

benchmark() {
    time ./pow $pow_name $base $pow
}

test() {
    IN=$(./pow $pow_name $base $pow)
    echo "Expected $result Actual $IN"
}

bench_for_screen() {
    echo "ITERATION"
    time ./pow iter_pow $base $pow

    echo "APPROXIMATE_POW2"
    time ./pow approximate_pow2 $base $pow

    echo "FAST_POW"
    time ./pow fast_pow $base $pow
}

pow_name=$1
base=$(sed -n '1 p' $2)
pow=$(sed -n '2 p' $2)
result=$(sed -n '1 p' $3)

if [ "$4" = "bench" ]
then
benchmark
elif [ "$4" = "screen" ]
then
bench_for_screen
else
test
fi