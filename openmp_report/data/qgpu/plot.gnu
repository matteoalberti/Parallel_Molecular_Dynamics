set terminal png size 800,600 
set font 'Helvetica,16'
set output 'openmp_timebenchmark.png'
set title "Openmp scaling\n{/*0.8 (gpu queue on ulysses cluster)}"
set xlabel 'Number of Threads'
set ylabel 'Elapsed Time (seconds)'

set key top right
set xrange[1:20]
set xtics 1

set style line 1 lt 2 lw 2 pt 7 ps 0.5
set style line 2 lt 6 lw 2 pt 7 ps 0.5

plot 'omptimes108.dat' u 1:2 w lp ls 1 t 'Argon 108', 'omptimes2916.dat' u 1:2 w lp ls 2 t 'Argon 2916'

