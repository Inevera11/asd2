set terminal png
set output "push_results.png"
set title "Czas operacji push"
set xlabel "Liczba elementów"
set ylabel "Czas (ms)"
plot "push_results.dat" using 1:2 with lines title "SimpleDict", \
     "push_results.dat" using 1:3 with lines title "LinkedSet", \
     "push_results.dat" using 1:4 with lines title "SetHashed"

set output "search_results.png"
set title "Czas operacji includes"
plot "search_results.dat" using 1:2 with lines title "SimpleDict", \
     "search_results.dat" using 1:3 with lines title "LinkedSet", \
     "search_results.dat" using 1:4 with lines title "SetHashed"

set output "pop_results.png"
set title "Czas operacji pop"
plot "pop_results.dat" using 1:2 with lines title "SimpleDict", \
     "pop_results.dat" using 1:3 with lines title "LinkedSet", \
     "pop_results.dat" using 1:4 with lines title "SetHashed"
