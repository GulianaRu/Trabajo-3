set datafile separator ","
set terminal pngcairo size 900,600 enhanced font "Arial,12"
set grid
set key top left
set style data linespoints

# ==========================================
# 1. Gráfico de Algoritmos Greedy
# ==========================================
set output "plots/comparatives/greedy_comparativo.png"
set title "Comparacion Algoritmos Greedy (Proyecto 3)"
set xlabel "Tamano del arreglo (n)"
set ylabel "Tiempo (segundos)"

plot "docs/benchmark_greedy.csv" skip 1 using 1:2 title "Greedy: Mayor Puntaje" lw 2 lc rgb "red", \
     "docs/benchmark_greedy.csv" skip 1 using 1:3 title "Greedy: Menor Costo" lw 2 lc rgb "blue", \
     "docs/benchmark_greedy.csv" skip 1 using 1:4 title "Greedy: Mejor Ratio" lw 2 lc rgb "green"

# ==========================================
# 2. Gráfico de Programación Dinámica
# ==========================================
set output "plots/comparatives/dp_comparativo.png"
set title "Comparacion Programacion Dinamica (Proyecto 3)"
set xlabel "Tamano del arreglo (n)"
set ylabel "Tiempo (segundos)"

plot "docs/benchmark_dp.csv" skip 1 using 1:2 title "DP: Top-Down (Memoization)" lw 2 lc rgb "purple", \
     "docs/benchmark_dp.csv" skip 1 using 1:3 title "DP: Bottom-Up (Tabulation)" lw 2 lc rgb "orange"
     