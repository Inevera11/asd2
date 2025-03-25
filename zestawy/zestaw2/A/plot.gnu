set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set output 'dict_operations.png'

set title "Czas wykonania mapDoubleLetter()"
set xlabel "Rozmiar problemu (index napisu)"
set ylabel "Czas wykonania (microsekundy)"
plot "data.txt" using 1:2 with lines title "Czas vs Rozmiar", \
     0.12 with lines linewidth 2 title "O(1)"