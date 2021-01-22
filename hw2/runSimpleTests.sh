#!/bin/bash

if [[ $# < 1 ]]
then
    sourceFile=primes.c
else
    sourceFile="$1"
fi

gcc -g $sourceFile -o primes -lm -Wall -std=c99

for bounds in "1 1" "1 2" "1 5" "2 100" "50 51" "50 200" "7 7" "17 12" "73 127" "160 162" "40000 45000"
do
    echo "Running with bounds" ${bounds}"..."
    ./primes ${bounds} | ./primesCheckOutput ${bounds}
done