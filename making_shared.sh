#! /bin/bash

module load testing
module load gnu/6.2.0

arr=$(ls ./src/CF_folder/ | wc -l)
echo $arr
for i in $(seq 0 2);
        do
        mv ./src/CF_folder/${i}* ./src/
        make clean
        perf stat -d  -r 3  --output perf_data_shared_${i}.txt  make shared
        mv ./src/${i}*  ./src/CF_folder/
        done
