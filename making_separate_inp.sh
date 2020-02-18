#! /bin/bash

for i in $(seq 0 2);
	do
	mv ./src/CF_folder/${i}_c* ./src/

	make clean
	make shared
	cd ./examples
	perf stat -d -r 3 --output ../results/perf_data_c_${i}_108.txt  ../ljmd.x < argon_108.inp
	perf stat -d -r 3 --output ../results/perf_data_c_${i}_2916.txt ../ljmd.x < argon_2916.inp
	
        cd ..
	mv ./src/${i}_c*  ./src/CF_folder/
	done
