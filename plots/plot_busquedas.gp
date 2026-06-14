set datafile separator ","
set terminal pngcairo size 900,600 enhanced font "Arial,12"
set grid
set key top left
set style data linespoints

set output "plots/comparatives/busquedas_comparativo.png"
set title "Comparacion General de Busquedas"
set xlabel "Tamano del arreglo (n)"
set ylabel "Tiempo (segundos)"
plot "docs/benchmark_busquedas.csv" skip 1 using 1:2 title "Secuencial" lw 2 lc rgb "red", \
     "docs/benchmark_busquedas.csv" skip 1 using 1:3 title "Binaria Iter" lw 2 lc rgb "blue", \
     "docs/benchmark_busquedas.csv" skip 1 using 1:4 title "Binaria Rec" lw 2 lc rgb "green", \
     "docs/benchmark_busquedas.csv" skip 1 using 1:5 title "QuickSelect" lw 2 lc rgb "purple", \
     "docs/benchmark_busquedas.csv" skip 1 using 1:6 title "Exponencial" lw 2 lc rgb "brown", \
     "docs/benchmark_busquedas.csv" skip 1 using 1:7 title "Interpolacion" lw 2 lc rgb "orange"

# Individuales
set output "plots/sequentialsearch/busqueda_secuencial_peor.png"
set title "Busqueda Secuencial - Peor Caso O(N)"
plot "docs/benchmark_busquedas.csv" skip 1 using 1:2 title "Secuencial" lw 2 lc rgb "red"

set output "plots/binarysearch/busqueda_binaria_iterativa.png"
set title "Busqueda Binaria Iterativa - Peor Caso O(log N)"
plot "docs/benchmark_busquedas.csv" skip 1 using 1:3 title "Binaria Iterativa" lw 2 lc rgb "blue"

set output "plots/binarysearch/busqueda_binaria_recursiva.png"
set title "Busqueda Binaria Recursiva - Peor Caso O(log N)"
plot "docs/benchmark_busquedas.csv" skip 1 using 1:4 title "Binaria Recursiva" lw 2 lc rgb "green"

set output "plots/quickselect/quickselect_analisis.png"
set title "QuickSelect(k) - Analisis de Rendimiento"
plot "docs/benchmark_busquedas.csv" skip 1 using 1:5 title "QuickSelect" lw 2 lc rgb "purple"

set output "plots/exponencial/busqueda_exponencial_analisis.png"
set title "Busqueda Exponencial - Analisis de Rendimiento"
plot "docs/benchmark_busquedas.csv" skip 1 using 1:6 title "Exponencial" lw 2 lc rgb "brown"

set output "plots/interpolacion/busqueda_interpolacion_analisis.png"
set title "Busqueda Interpolacion - Analisis de Rendimiento"
plot "docs/benchmark_busquedas.csv" skip 1 using 1:7 title "Interpolacion" lw 2 lc rgb "orange"