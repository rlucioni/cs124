#!/bin/bash

# takes dimension as an argument!!

echo "TESTING CUTOFF VALUES ON 012 MATRICES OF DIMENSION $1..."
for ((i=0; i<=1000; i++))
do
    echo -n $i
    time ./strassen 0 $1 matrices_012.txt $i
done