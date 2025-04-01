set terminal pngcairo size 1200,1200 enhanced font 'Arial,12'
set output 'sets.png'

set multiplot layout 2,2 title "Porównanie operacji" font ",14"

# First plot
set title "Średni czas wykonywania operacji A+A"
set xlabel "Liczba elementów"
set ylabel "Czas (μs)"
plot "sets.dat" using 1:2 with linespoints title "1" lc rgb "#1f77b4", \
     "sets.dat" using 1:6 with linespoints title "500" lc rgb "#ff7f0e", \
     "sets.dat" using 1:10 with linespoints title "1000" lc rgb "#2ca02c"

# Second plot
set title "Średni czas wykonywania operacji A-A"
set xlabel "Liczba elementów"
set ylabel "Czas (μs)"
plot "sets.dat" using 1:3 with linespoints title "1" lc rgb "#d62728", \
     "sets.dat" using 1:7 with linespoints title "500" lc rgb "#9467bd", \
     "sets.dat" using 1:11 with linespoints title "1000" lc rgb "#8c564b"

# Third plot
set title "Średni czas wykonywania operacji A*A"
set xlabel "Liczba elementów"
set ylabel "Czas (μs)"
plot "sets.dat" using 1:4 with linespoints title "1" lc rgb "#d62728", \
     "sets.dat" using 1:8 with linespoints title "500" lc rgb "#9467bd", \
     "sets.dat" using 1:12 with linespoints title "1000" lc rgb "#8c564b"

# Forth plot
set title "Średni czas wykonywania operacji A==A"
set xlabel "Liczba elementów"
set ylabel "Czas (μs)"
plot "sets.dat" using 1:5 with linespoints title "1" lc rgb "#d62728", \
     "sets.dat" using 1:9 with linespoints title "500" lc rgb "#9467bd", \
     "sets.dat" using 1:13 with linespoints title "1000" lc rgb "#8c564b"

unset multiplot
