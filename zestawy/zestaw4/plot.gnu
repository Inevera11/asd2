set terminal png
set output 'performance.png'
set title 'Performance of Graph neighbours() operation'
set xlabel 'Number of elements'
set ylabel 'Time (nanoseconds)'
plot 'performance.dat' using 1:2 with lines, \
