set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set output 'dict_operations.png'

set title "Średni czas wykonywania operacji w SimpleDict" font ",14"
set xlabel "Numer testu" font ",12"
set ylabel "Czas (μs)" font ",12"
set grid

set style data linespoints
set key outside right
set xtics nomirror rotate by -45
set ytics nomirror

plot "results.dat" using 1:2 with linespoints title "push" lc rgb "#1f77b4", \
     "results.dat" using 1:3 with linespoints title "includes" lc rgb "#ff7f0e", \
     "results.dat" using 1:4 with linespoints title "pop" lc rgb "#2ca02c"
