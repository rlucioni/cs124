#!/bin/sh

rm weight0.txt weight2.txt weight3.txt weight4.txt

echo "RUNNING KRUSKALS, 0 DIMENSIONS..."
./randmst 3 16 5 0 >> weight0.txt
wait
./randmst 0 32 5 0 >> weight0.txt
wait
./randmst 0 64 5 0 >> weight0.txt
wait
./randmst 0 128 5 0 >> weight0.txt
wait
./randmst 0 256 5 0 >> weight0.txt
wait
./randmst 0 512 5 0 >> weight0.txt
wait
./randmst 0 1024 5 0 >> weight0.txt
wait
./randmst 0 2048 5 0 >> weight0.txt
wait
./randmst 0 4096 5 0 >> weight0.txt
wait
./randmst 0 8192 5 0 >> weight0.txt
wait
#./randmst 0 16384 5 0 >> weight0.txt
#wait
#./randmst 0 32768 5 0 >> weight0.txt
#wait

echo "RUNNING KRUSKALS, 2 DIMENSIONS..."
./randmst 0 16 5 2 >> weight2.txt
wait
./randmst 0 32 5 2 >> weight2.txt
wait
./randmst 0 64 5 2 >> weight2.txt
wait
./randmst 0 128 5 2 >> weight2.txt
wait
./randmst 0 256 5 2 >> weight2.txt
wait
./randmst 0 512 5 2 >> weight2.txt
wait
./randmst 0 1024 5 2 >> weight2.txt
wait
./randmst 0 2048 5 2 >> weight2.txt
wait
./randmst 0 4096 5 2 >> weight2.txt
wait
./randmst 0 8192 5 2 >> weight2.txt
wait
#./randmst 0 16384 5 2 >> weight2.txt
#wait
#./randmst 0 32768 5 2 >> weight2.txt
#wait

echo "RUNNING KRUSKALS, 3 DIMENSIONS..."
./randmst 0 16 5 3 >> weight3.txt
wait
./randmst 0 32 5 3 >> weight3.txt
wait
./randmst 0 64 5 3 >> weight3.txt
wait
./randmst 0 128 5 3 >> weight3.txt
wait
./randmst 0 256 5 3 >> weight3.txt
wait
./randmst 0 512 5 3 >> weight3.txt
wait
./randmst 0 1024 5 3 >> weight3.txt
wait
./randmst 0 2048 5 3 >> weight3.txt
wait
./randmst 0 4096 5 3 >> weight3.txt
wait
./randmst 0 8192 5 3 >> weight3.txt
wait
#./randmst 0 16384 5 3 >> weight3.txt
#wait
#./randmst 0 32768 5 3 >> weight3.txt
#wait

echo "RUNNING KRUSKALS, 4 DIMENSIONS..."
./randmst 0 16 5 4 >> weight4.txt
wait
./randmst 0 32 5 4 >> weight4.txt
wait
./randmst 0 64 5 4 >> weight4.txt
wait
./randmst 0 128 5 4 >> weight4.txt
wait
./randmst 0 256 5 4 >> weight4.txt
wait
./randmst 0 512 5 4 >> weight4.txt
wait
./randmst 0 1024 5 4 >> weight4.txt
wait
./randmst 0 2048 5 4 >> weight4.txt
wait
./randmst 0 4096 5 4 >> weight4.txt
wait
./randmst 0 8192 5 4 >> weight4.txt
wait
#./randmst 0 16384 5 4 >> weight4.txt
#wait
#./randmst 0 32768 5 4 >> weight4.txt
#wait
