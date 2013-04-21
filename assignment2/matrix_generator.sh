#!/bin/sh

d=$1

# check if the provided argument is an integer
if ! [[ $d =~ ^[0-9]+$ ]] ; then
   echo "usage: ./matrix_generator [integer]"; exit 1
fi

# generate two dxd matrices where entries are randomly 0 or 1
rm matrices_binary.txt
for ((i=1; i<=$((2*($d*$d))); i++))
do
    printf "$((RANDOM%2))\n" >> matrices_binary.txt
done

# generate matrix where entries are randomly 0, 1, or 2
#rm matrices_012.txt
#for ((i=1; i<=$((2*($d*$d))); i++))
#do
#    printf "$((RANDOM%3))\n" >> matrices_012.txt
#done

# generate matrix where entries are randomly 0, 1, or -1
#rm matrices_neg.txt
#for ((i=1; i<=$((2*($d*$d))); i++))
#do
#    printf "%d\n" $((RANDOM%3-1)) >> matrices_neg.txt
#done

# generate matrix where entries are randomly a real in [0,1]
#rm matrices_real.txt
#for ((i=1; i<=$((2*($d*$d))); i++))
#do
#    awk -v seed=$RANDOM 'BEGIN { srand(seed); printf("%f\n", rand()) }' >> matrices_real.txt
#done
