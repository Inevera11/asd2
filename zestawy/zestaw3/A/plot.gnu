set terminal png
set output 'performance.png'
set title 'Performance of PriorityQueue Operations'
set xlabel 'Number of elements'
set ylabel 'Time (nanoseconds)'
plot 'performance.dat' using 1:2 with lines title 'Push', \
     'performance.dat' using 1:3 with lines title 'Pop min' lw 2, \
