# Script de Gnuplot para Análisis Experimental - Tarea 2
set datafile separator ","
set terminal pngcairo size 900,600 enhanced font "Arial,12"
set grid
set key top left
set style data linespoints

# ==============================================================================
# 1. COMPARATIVOS GENERALES
# ==============================================================================

set output "plots/comparatives/sorts_comparativo_promedio.png"
set title "Comparacion General de Algoritmos (Caso Promedio)"
set xlabel "Tamano del arreglo (n)"
set ylabel "Tiempo (segundos)"
plot "docs/sorts_promedio.csv" skip 1 using 1:2 title "Bubble Sort" lw 2, \
     "docs/sorts_promedio.csv" skip 1 using 1:3 title "Insertion Sort" lw 2, \
     "docs/sorts_promedio.csv" skip 1 using 1:4 title "Selection Sort" lw 2, \
     "docs/sorts_promedio.csv" skip 1 using 1:5 title "Cocktail Shaker" lw 2, \
     "docs/sorts_promedio.csv" skip 1 using 1:6 title "Merge Sort" lw 2, \
     "docs/sorts_promedio.csv" skip 1 using 1:7 title "Merge Sort Optimizado" lw 2, \
     "docs/sorts_promedio.csv" skip 1 using 1:8 title "Quick Sort Ultimo Pivote" lw 2, \
     "docs/sorts_promedio.csv" skip 1 using 1:9 title "Quick Sort Mediana de Tres" lw 2

# ==============================================================================
# 2. BUBBLE SORT
# ==============================================================================
set output "plots/bubblesort/bubble_sort_combinado.png"
set title "Bubble Sort - Comparacion de Casos"
plot "docs/sorts_mejor.csv" skip 1 using 1:2 title "Mejor Caso" lw 2 lc rgb "green", \
     "docs/sorts_peor.csv" skip 1 using 1:2 title "Peor Caso" lw 2 lc rgb "red", \
     "docs/sorts_promedio.csv" skip 1 using 1:2 title "Caso Promedio" lw 2 lc rgb "blue"

set output "plots/bubblesort/bubble_sort_mejor.png"
set title "Bubble Sort - Mejor Caso"
plot "docs/sorts_mejor.csv" skip 1 using 1:2 title "Mejor Caso" lw 2 lc rgb "green"

set output "plots/bubblesort/bubble_sort_peor.png"
set title "Bubble Sort - Peor Caso"
plot "docs/sorts_peor.csv" skip 1 using 1:2 title "Peor Caso" lw 2 lc rgb "red"

set output "plots/bubblesort/bubble_sort_promedio.png"
set title "Bubble Sort - Caso Promedio"
plot "docs/sorts_promedio.csv" skip 1 using 1:2 title "Caso Promedio" lw 2 lc rgb "blue"

# ==============================================================================
# 3. INSERTION SORT
# ==============================================================================
set output "plots/insertionsort/insertion_sort_combinado.png"
set title "Insertion Sort - Comparacion de Casos"
plot "docs/sorts_mejor.csv" skip 1 using 1:3 title "Mejor Caso" lw 2 lc rgb "green", \
     "docs/sorts_peor.csv" skip 1 using 1:3 title "Peor Caso" lw 2 lc rgb "red", \
     "docs/sorts_promedio.csv" skip 1 using 1:3 title "Caso Promedio" lw 2 lc rgb "blue"

set output "plots/insertionsort/insertion_sort_mejor.png"
set title "Insertion Sort - Mejor Caso"
plot "docs/sorts_mejor.csv" skip 1 using 1:3 title "Mejor Caso" lw 2 lc rgb "green"

set output "plots/insertionsort/insertion_sort_peor.png"
set title "Insertion Sort - Peor Caso"
plot "docs/sorts_peor.csv" skip 1 using 1:3 title "Peor Caso" lw 2 lc rgb "red"

set output "plots/insertionsort/insertion_sort_promedio.png"
set title "Insertion Sort - Caso Promedio"
plot "docs/sorts_promedio.csv" skip 1 using 1:3 title "Caso Promedio" lw 2 lc rgb "blue"

# ==============================================================================
# 4. SELECTION SORT
# ==============================================================================
set output "plots/selectionsort/selection_sort_combinado.png"
set title "Selection Sort - Comparacion de Casos"
plot "docs/sorts_mejor.csv" skip 1 using 1:4 title "Mejor Caso" lw 2 lc rgb "green", \
     "docs/sorts_peor.csv" skip 1 using 1:4 title "Peor Caso" lw 2 lc rgb "red", \
     "docs/sorts_promedio.csv" skip 1 using 1:4 title "Caso Promedio" lw 2 lc rgb "blue"

set output "plots/selectionsort/selection_sort_mejor.png"
set title "Selection Sort - Mejor Caso"
plot "docs/sorts_mejor.csv" skip 1 using 1:4 title "Mejor Caso" lw 2 lc rgb "green"

set output "plots/selectionsort/selection_sort_peor.png"
set title "Selection Sort - Peor Caso"
plot "docs/sorts_peor.csv" skip 1 using 1:4 title "Peor Caso" lw 2 lc rgb "red"

set output "plots/selectionsort/selection_sort_promedio.png"
set title "Selection Sort - Caso Promedio"
plot "docs/sorts_promedio.csv" skip 1 using 1:4 title "Caso Promedio" lw 2 lc rgb "blue"

# ==============================================================================
# 5. COCKTAIL SHAKER SORT
# ==============================================================================
set output "plots/cocktail_shaker_sort/cocktail_shaker_combinado.png"
set title "Cocktail Shaker Sort - Comparacion de Casos"
plot "docs/sorts_mejor.csv" skip 1 using 1:5 title "Mejor Caso" lw 2 lc rgb "green", \
     "docs/sorts_peor.csv" skip 1 using 1:5 title "Peor Caso" lw 2 lc rgb "red", \
     "docs/sorts_promedio.csv" skip 1 using 1:5 title "Caso Promedio" lw 2 lc rgb "blue"

set output "plots/cocktail_shaker_sort/cocktail_shaker_mejor.png"
set title "Cocktail Shaker Sort - Mejor Caso"
plot "docs/sorts_mejor.csv" skip 1 using 1:5 title "Mejor Caso" lw 2 lc rgb "green"

set output "plots/cocktail_shaker_sort/cocktail_shaker_peor.png"
set title "Cocktail Shaker Sort - Peor Caso"
plot "docs/sorts_peor.csv" skip 1 using 1:5 title "Peor Caso" lw 2 lc rgb "red"

set output "plots/cocktail_shaker_sort/cocktail_shaker_promedio.png"
set title "Cocktail Shaker Sort - Caso Promedio"
plot "docs/sorts_promedio.csv" skip 1 using 1:5 title "Caso Promedio" lw 2 lc rgb "blue"

# ==============================================================================
# 6. MERGE SORT CLASICO
# ==============================================================================
set output "plots/mergesort/merge_sort_combinado.png"
set title "Merge Sort Clasico - Comparacion de Casos"
plot "docs/sorts_mejor.csv" skip 1 using 1:6 title "Mejor Caso" lw 2 lc rgb "green", \
     "docs/sorts_peor.csv" skip 1 using 1:6 title "Peor Caso" lw 2 lc rgb "red", \
     "docs/sorts_promedio.csv" skip 1 using 1:6 title "Caso Promedio" lw 2 lc rgb "blue"

set output "plots/mergesort/merge_sort_mejor.png"
set title "Merge Sort Clasico - Mejor Caso"
plot "docs/sorts_mejor.csv" skip 1 using 1:6 title "Mejor Caso" lw 2 lc rgb "green"

set output "plots/mergesort/merge_sort_peor.png"
set title "Merge Sort Clasico - Peor Caso"
plot "docs/sorts_peor.csv" skip 1 using 1:6 title "Peor Caso" lw 2 lc rgb "red"

set output "plots/mergesort/merge_sort_promedio.png"
set title "Merge Sort Clasico - Caso Promedio"
plot "docs/sorts_promedio.csv" skip 1 using 1:6 title "Caso Promedio" lw 2 lc rgb "blue"

# ==============================================================================
# 7. MERGE SORT OPTIMIZADO
# ==============================================================================
set output "plots/mergesort/merge_sort_opt_combinado.png"
set title "Merge Sort Optimizado - Comparacion de Casos"
plot "docs/sorts_mejor.csv" skip 1 using 1:7 title "Mejor Caso" lw 2 lc rgb "green", \
     "docs/sorts_peor.csv" skip 1 using 1:7 title "Peor Caso" lw 2 lc rgb "red", \
     "docs/sorts_promedio.csv" skip 1 using 1:7 title "Caso Promedio" lw 2 lc rgb "blue"

set output "plots/mergesort/merge_sort_opt_mejor.png"
set title "Merge Sort Optimizado - Mejor Caso"
plot "docs/sorts_mejor.csv" skip 1 using 1:7 title "Mejor Caso" lw 2 lc rgb "green"

set output "plots/mergesort/merge_sort_opt_peor.png"
set title "Merge Sort Optimizado - Peor Caso"
plot "docs/sorts_peor.csv" skip 1 using 1:7 title "Peor Caso" lw 2 lc rgb "red"

set output "plots/mergesort/merge_sort_opt_promedio.png"
set title "Merge Sort Optimizado - Caso Promedio"
plot "docs/sorts_promedio.csv" skip 1 using 1:7 title "Caso Promedio" lw 2 lc rgb "blue"

# ==============================================================================
# 8. QUICK SORT (MEDIANA DE TRES)
# ==============================================================================
set output "plots/quicksort/quick_sort_mediana_combinado.png"
set title "Quick Sort (Mediana de 3) - Comparacion de Casos"
plot "docs/sorts_mejor.csv" skip 1 using 1:9 title "Mejor Caso" lw 2 lc rgb "green", \
     "docs/sorts_peor.csv" skip 1 using 1:9 title "Peor Caso" lw 2 lc rgb "red", \
     "docs/sorts_promedio.csv" skip 1 using 1:9 title "Caso Promedio" lw 2 lc rgb "blue"

set output "plots/quicksort/quick_sort_mediana_mejor.png"
set title "Quick Sort (Mediana de 3) - Mejor Caso"
plot "docs/sorts_mejor.csv" skip 1 using 1:9 title "Mejor Caso" lw 2 lc rgb "green"

set output "plots/quicksort/quick_sort_mediana_peor.png"
set title "Quick Sort (Mediana de 3) - Peor Caso"
plot "docs/sorts_peor.csv" skip 1 using 1:9 title "Peor Caso" lw 2 lc rgb "red"

set output "plots/quicksort/quick_sort_mediana_promedio.png"
set title "Quick Sort (Mediana de 3) - Caso Promedio"
plot "docs/sorts_promedio.csv" skip 1 using 1:9 title "Caso Promedio" lw 2 lc rgb "blue"

# ==============================================================================
# 9. COMPARACION DE PIVOTES QUICK SORT
# ==============================================================================
set output "plots/quicksort/quick_sort_pivotes_comparativo.png"
set title "Quick Sort - Comparacion de Pivotes"
set xlabel "Tamano del arreglo (n)"
set ylabel "Tiempo (segundos)"
set grid
set key top left
set style data linespoints

plot "docs/sorts_promedio.csv" skip 1 using 1:8 title "QuickUlt - Promedio" lw 2, \
     "docs/sorts_promedio.csv" skip 1 using 1:9 title "QuickMed - Promedio" lw 2, \
     "docs/sorts_mejor.csv" skip 1 using 1:8 title "QuickUlt - Mejor" lw 2, \
     "docs/sorts_mejor.csv" skip 1 using 1:9 title "QuickMed - Mejor" lw 2, \
     "docs/sorts_peor.csv" skip 1 using 1:8 title "QuickUlt - Peor" lw 2, \
     "docs/sorts_peor.csv" skip 1 using 1:9 title "QuickMed - Peor" lw 2

# ==============================================================================
# 10. COMPARACION MERGE VS QUICK - CASO PROMEDIO
# ==============================================================================
set output "plots/comparatives/comp_merge_quick.png"
set title "Comparacion de Merge Sort y Quick Sort - Caso Promedio"
set xlabel "Tamano del arreglo (n)"
set ylabel "Tiempo (segundos)"
set grid
set key top left
set style data linespoints

plot "docs/sorts_promedio.csv" skip 1 using 1:6 title "Merge Sort" lw 2, \
     "docs/sorts_promedio.csv" skip 1 using 1:7 title "Merge Sort Optimizado" lw 2, \
     "docs/sorts_promedio.csv" skip 1 using 1:8 title "Quick Sort Ultimo Pivote" lw 2, \
     "docs/sorts_promedio.csv" skip 1 using 1:9 title "Quick Sort Mediana de Tres" lw 2