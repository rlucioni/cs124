#!/bin/bash

# usage: ./run.sh [dimension] [filename]
#count=0
#echo "TESTING CUTOFF VALUES ON MATRICES IN $2 OF DIMENSION $1..."
#for ((i=1; i<=1000; i=$i+2))
for ((i=1; i<=500; i++))
do
    #count=$(($count+1))
    #echo $i
    ./strassen 1 $1 $2 $i
done
#echo $count
