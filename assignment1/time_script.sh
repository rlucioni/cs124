#!/bin/sh

rm data/time0.txt

echo "TIMING KRUSKALS, 0 DIMENSIONS..."
./randmst 4 16 2 0 >> data/time0.txt
wait
./randmst 4 32 2 0 >> data/time0.txt
wait
./randmst 4 64 2 0 >> data/time0.txt
wait
./randmst 4 128 2 0 >> data/time0.txt
wait
./randmst 4 256 2 0 >> data/time0.txt
wait
./randmst 4 212 2 0 >> data/time0.txt
wait
./randmst 4 1024 2 0 >> data/time0.txt
wait
./randmst 4 2048 2 0 >> data/time0.txt
wait
./randmst 4 4096 2 0 >> data/time0.txt
wait
./randmst 4 8192 2 0 >> data/time0.txt
wait
./randmst 4 16384 2 0 >> data/time0.txt
wait
./randmst 4 32768 2 0 >> data/time0.txt
wait
./randmst 4 65536 2 0 >> data/time0.txt
wait
./randmst 4 131072 2 0 >> data/time0.txt
wait
./randmst 4 262144 2 0 >> data/time0.txt
wait