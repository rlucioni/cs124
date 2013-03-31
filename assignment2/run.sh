#!/bin/bash

# usage: ./run.sh [dimension] [filename]

echo "TESTING CUTOFF VALUES ON MATRICES IN $2 OF DIMENSION $1..."
for ((i=1; i<=200; i++))
do
    #echo -n $i
    time ./strassen 0 $1 $2 $i
done
