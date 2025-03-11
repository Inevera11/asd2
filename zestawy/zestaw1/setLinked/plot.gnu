set terminal png
set output 'performance.png'
set title 'Performance of LinkedSet Operations'
set xlabel 'Number of elements'
set ylabel 'Time (microseconds)'
plot 'performance.dat' using 1:2 with lines title 'Push', \
     'performance.dat' using 1:3 with lines title 'Pop', \
     'performance.dat' using 1:4 with lines title 'Includes'

set output 'operations.png'
set title 'Set Operations Performance'
plot 'operations.dat' using 1:2 with lines title 'Union (A + B)', \
     'operations.dat' using 1:3 with lines title 'Intersection (A * B)', \
     'operations.dat' using 1:4 with lines title 'Difference (A - B)', \
     'operations.dat' using 1:5 with lines title 'Equality (A == B)'
