#! /bin/bash

 
arr=$(ls ./src/CF_folder/ | wc -l)
for i in $(seq 0 3);
        do
        mv ./src/CF_folder/${i}* ./src/
        make clean
        make
        perf stat -d  -r 3  --output perf_data_${i}.txt  make check_c
        mv ./src/${i}*  ./src/CF_folder/
        done
