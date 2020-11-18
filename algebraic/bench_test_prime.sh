#!/bin/bash

benchmark() {
    time ./prime $prime_type $n
}

test() {
    IN=$(./prime $prime_type $n)
    echo "Expected $result Actual $IN"
}

bench_for_screen() {
    echo "prime_heuristic"
    time ./prime prime_heuristic $n

    echo "prime_del_primes"
    #time ./prime prime_del_primes $n
    echo "MORE THAN 40 MIN"

    echo "eratosthenes"
    time ./prime eratosthenes $n 

    echo "eratosthenes_op"
    time ./prime eratosthenes_op $n 
}

prime_type=$1
n=$(sed -n '1 p' $2)
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