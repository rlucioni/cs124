#!/bin/bash

# usage: ./run.sh [dimension] [filename]
#count=0
<<<<<<< HEAD
#echo "TESTING CUTOFF VALUES ON MATRICES IN $2 OF DIMENSION $1..."
=======
echo "TESTING CUTOFF VALUES ON MATRICES IN $2 OF DIMENSION $1..."
>>>>>>> 1e1baf39429a5f707bd5915a01fc35a35bbd7951
#for ((i=1; i<=1000; i=$i+2))
for ((i=1; i<=500; i++))
do
    #count=$(($count+1))
    #echo $i
    ./strassen 1 $1 $2 $i
done
#echo $count
