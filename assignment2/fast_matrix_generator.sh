#!/bin/sh
 
# to be used with a pipe: ./big_matrix_generator [dim] > file.txt
d=$1
 
# check if the provided argument is an integer
if ! [[ $d =~ ^[0-9]+$ ]] ; then
   echo "usage: ./big_matrix_generator [integer]"; exit 1
fi
 
limit=$((2*($d*$d)))
 
# generate matrices where entries are randomly 0, 1, or 2
for ((i=1; i<=$limit; i++))
do
    echo "$((RANDOM%3))"
done