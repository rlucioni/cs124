#!/bin/sh

rm weight0.txt weight2.txt weight3.txt weight4.txt

echo "RUNNING KRUSKALS, 0 DIMENSIONS..."
./randmst 3 16 5 0 >> weight0.txt
wait
./randmst 3 25 5 0 >> weight0.txt
wait
./randmst 3 32 5 0 >> weight0.txt
wait
./randmst 3 50 5 0 >> weight0.txt
wait
./randmst 3 64 5 0 >> weight0.txt
wait
./randmst 3 90 5 0 >> weight0.txt
wait
./randmst 3 128 5 0 >> weight0.txt
wait
./randmst 3 190 5 0 >> weight0.txt
wait
./randmst 3 256 5 0 >> weight0.txt
wait
./randmst 3 350 5 0 >> weight0.txt
wait
./randmst 3 512 5 0 >> weight0.txt
wait
./randmst 3 750 5 0 >> weight0.txt
wait
./randmst 3 1024 5 0 >> weight0.txt
wait
./randmst 3 1500 5 0 >> weight0.txt
wait
./randmst 3 2048 5 0 >> weight0.txt
wait
./randmst 3 3000 5 0 >> weight0.txt
wait
./randmst 3 4096 5 0 >> weight0.txt
wait
./randmst 3 6000 5 0 >> weight0.txt
wait
./randmst 3 8192 5 0 >> weight0.txt
wait
#./randmst 3 16384 5 0 >> weight0.txt
#wait
#./randmst 3 32768 5 0 >> weight0.txt
#wait

echo "RUNNING KRUSKALS, 2 DIMENSIONS..."
./randmst 3 16 5 2 >> weight2.txt
wait
./randmst 3 25 5 2 >> weight2.txt
wait
./randmst 3 32 5 2 >> weight2.txt
wait
./randmst 3 50 5 2 >> weight2.txt
wait
./randmst 3 64 5 2 >> weight2.txt
wait
./randmst 3 90 5 2 >> weight2.txt
wait
./randmst 3 128 5 2 >> weight2.txt
wait
./randmst 3 190 5 2 >> weight2.txt
wait
./randmst 3 256 5 2 >> weight2.txt
wait
./randmst 3 350 5 2 >> weight2.txt
wait
./randmst 3 512 5 2 >> weight2.txt
wait
./randmst 3 750 5 2 >> weight2.txt
wait
./randmst 3 1024 5 2 >> weight2.txt
wait
./randmst 3 1500 5 2 >> weight2.txt
wait
./randmst 3 2048 5 2 >> weight2.txt
wait
./randmst 3 3000 5 2 >> weight2.txt
wait
./randmst 3 4096 5 2 >> weight2.txt
wait
./randmst 3 6000 5 2 >> weight2.txt
wait
./randmst 3 8192 5 2 >> weight2.txt
wait
#./randmst 3 16384 5 2 >> weight2.txt
#wait
#./randmst 3 32768 5 2 >> weight2.txt
#wait

echo "RUNNING KRUSKALS, 3 DIMENSIONS..."
./randmst 3 16 5 3 >> weight3.txt
wait
./randmst 3 25 5 3 >> weight3.txt
wait
./randmst 3 32 5 3 >> weight3.txt
wait
./randmst 3 50 5 3 >> weight3.txt
wait
./randmst 3 64 5 3 >> weight3.txt
wait
./randmst 3 90 5 3 >> weight3.txt
wait
./randmst 3 128 5 3 >> weight3.txt
wait
./randmst 3 190 5 3 >> weight3.txt
wait
./randmst 3 256 5 3 >> weight3.txt
wait
./randmst 3 350 5 3 >> weight3.txt
wait
./randmst 3 512 5 3 >> weight3.txt
wait
./randmst 3 750 5 3 >> weight3.txt
wait
./randmst 3 1024 5 3 >> weight3.txt
wait
./randmst 3 1500 5 3 >> weight3.txt
wait
./randmst 3 2048 5 3 >> weight3.txt
wait
./randmst 3 3000 5 3 >> weight3.txt
wait
./randmst 3 4096 5 3 >> weight3.txt
wait
./randmst 3 6000 5 3 >> weight3.txt
wait
./randmst 3 8192 5 3 >> weight3.txt
wait
#./randmst 3 16384 5 3 >> weight3.txt
#wait
#./randmst 3 32768 5 3 >> weight3.txt
#wait

echo "RUNNING KRUSKALS, 4 DIMENSIONS..."
./randmst 3 16 5 4 >> weight4.txt
wait
./randmst 3 25 5 4 >> weight4.txt
wait
./randmst 3 32 5 4 >> weight4.txt
wait
./randmst 3 50 5 4 >> weight4.txt
wait
./randmst 3 64 5 4 >> weight4.txt
wait
./randmst 3 90 5 4 >> weight4.txt
wait
./randmst 3 128 5 4 >> weight4.txt
wait
./randmst 3 190 5 4 >> weight4.txt
wait
./randmst 3 256 5 4 >> weight4.txt
wait
./randmst 3 350 5 4 >> weight4.txt
wait
./randmst 3 512 5 4 >> weight4.txt
wait
./randmst 3 750 5 4 >> weight4.txt
wait
./randmst 3 1024 5 4 >> weight4.txt
wait
./randmst 3 1500 5 4 >> weight4.txt
wait
./randmst 3 2048 5 4 >> weight4.txt
wait
./randmst 3 3000 5 4 >> weight4.txt
wait
./randmst 3 4096 5 4 >> weight4.txt
wait
./randmst 3 6000 5 4 >> weight4.txt
wait
./randmst 3 8192 5 4 >> weight4.txt
wait
#./randmst 3 16384 5 4 >> weight4.txt
#wait
#./randmst 3 32768 5 4 >> weight4.txt
#wait
