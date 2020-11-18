#!/bin/bash

benchmark() {
    time ./fibo $fib_type $n
}

test() {
    IN=$(./fibo $fib_type $n)
    echo "Expected $result Actual $IN"
}

bench_for_screen() {
    echo "ITERATION"
    time ./fibo iter $n

    echo "RECUR"
    #time ./fibo rec $n
    echo "SKIP -> CAN'T WAIT TOO LONG"

    echo "GOLD"
    time ./fibo gold $n 

    echo "MATRIX"
    time ./fibo matrix $n 
}

fib_type=$1
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