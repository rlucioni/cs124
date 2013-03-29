#!/bin/sh

# make sure you pass in the right dimension as an argument!

echo "BINARY MATRICES..."
time ./strassen 0 $1 matrices_binary.txt
echo ""
echo "012 MATRICES..."
time ./strassen 0 $1 matrices_012.txt
echo ""
echo "NEG MATRICES..."
time ./strassen 0 $1 matrices_neg.txt
#echo "REAL MATRICES..."
#time ./strassen 0 $1 matrices_real.txt
