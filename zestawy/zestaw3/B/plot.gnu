set terminal png size 800,600
set output 'performance.png'
set title 'Performance of PriorityQueue Operations'
set xlabel 'Number of elements (log scale)'
set ylabel 'Time (nanoseconds)'
set logscale x 10
set grid
plot 'performance.dat' using 1:2 with lines title 'Push min' lc rgb 'blue', \
     'performance.dat' using 1:3 with lines title 'Pop min' lc rgb 'red'

