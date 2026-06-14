set datafile separator ","
set terminal pngcairo size 900,600 enhanced font "Arial,12"
set output "plots/comparatives/calidad_comparativo.png"

set title "Calidad de Solucion: DP vs Greedy (Presupuesto = 50000)"
set xlabel "Tamano del arreglo (n)"
set ylabel "Puntaje Total del Equipo"
set grid y
set key top left

# Configuración para gráfico de barras agrupadas
set style data histograms
set style histogram cluster gap 1
set style fill solid 0.8 border -1
set boxwidth 0.9

plot "docs/benchmark_calidad.csv" skip 1 using 2:xtic(1) title "Optimo Real (DP)" lc rgb "purple", \
     "" skip 1 using 3 title "Greedy: Mayor Puntaje" lc rgb "red", \
     "" skip 1 using 4 title "Greedy: Menor Costo" lc rgb "blue", \
     "" skip 1 using 5 title "Greedy: Mejor Ratio" lc rgb "green"