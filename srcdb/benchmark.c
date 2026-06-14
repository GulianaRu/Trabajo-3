#include "../incs/piloto.h"

// ====================== VARIABLE PARA EL INFORME ======================
// ¡CAMBIAR ESTE NUMERO PARA ANALIZAR EL IMPACTO DEL UMBRAL EN MERGE SORT OPTIMIZADO!
// Prueben cambiando a 5, 10, 15, 30 y 50 para redactar la comparacion en el informe.
int UMBRAL_ACTUAL_MERGE = 15; 
// ======================================================================

// ====================== FUNCIONES AUXILIARES ======================

// Crea el PEOR CASO para ordenamiento (arreglo ordenado al reves)
void invertir_arreglo(piloto p[], int tamano) {
    int inicio = 0;
    int fin = tamano - 1;
    while (inicio < fin) {
        piloto temp = p[inicio];
        p[inicio] = p[fin];
        p[fin] = temp;
        inicio++;
        fin--;
    }
}

int esta_ordenado(piloto p[], int tamano, int campo){
    for(int i = 0; i < tamano - 1; i++){
        if(comparar(p[i], p[i + 1], campo) > 0){
            return 0;
        }
    }
    return 1;
}

// ====================== MEDICION DE TIEMPOS ======================

typedef void (*func_sort)(piloto[], int, int);

double medir_tiempo_sort(func_sort fn, piloto p[], int tamano, int campo, int *ok){
    double tiempo_acumulado = 0.0;
    int repeticiones = 0;
    *ok = 1;
    
    do {
        piloto* copia = (piloto*)malloc(tamano * sizeof(piloto));
        
        if (copia == NULL){
            *ok = 0;
            return -1.0;
        }

        memcpy(copia, p, tamano * sizeof(piloto));

        
        clock_t inicio = clock();
        fn(copia, tamano, campo);
        clock_t fin = clock();

        if (!esta_ordenado(copia, tamano, campo)){
            *ok = 0;
        }
        
        tiempo_acumulado += (double)(fin - inicio) / CLOCKS_PER_SEC;
        
        free(copia); 
        repeticiones++;
        
    } while (tiempo_acumulado < 0.5 && repeticiones < 50);

    return tiempo_acumulado / (double)repeticiones;
}

typedef int (*func_busqueda)(piloto[], int, int);

// Medicion ADAPTATIVA para busquedas
double medir_tiempo_busqueda(func_busqueda fn, piloto p[], int tamano, int id){
    clock_t inicio = clock();
    clock_t fin;
    long long repeticiones = 0;
    
    do {
        fn(p, tamano, id);
        repeticiones++;
        fin = clock();
    } while ((fin - inicio) < (CLOCKS_PER_SEC / 10)); 
    
    double tiempo_total = (double)(fin - inicio) / CLOCKS_PER_SEC;
    return tiempo_total / (double)repeticiones;
}

double medir_tiempo_busqueda_binaria_opt(piloto p[], int tamano, int id){
    clock_t inicio = clock();
    clock_t fin;
    long long repeticiones = 0;
    
    do {
        busqueda_binaria_recursiva(p, id, 0, tamano - 1);
        repeticiones++;
        fin = clock();
    } while ((fin - inicio) < (CLOCKS_PER_SEC / 10)); 
    
    double tiempo_total = (double)(fin - inicio) / CLOCKS_PER_SEC;
    return tiempo_total / (double)repeticiones;
}

double medir_tiempo_qs(piloto p[], int izq, int der, int id, int campo){
    clock_t inicio = clock();
    quick_select(p, izq, der, id, campo);
    clock_t fin = clock();
    return (double)(fin - inicio) / CLOCKS_PER_SEC;
}

// Wrappers para algoritmos de la Tarea 2
void merge_benchmark(piloto p[], int tamano, int campo){
    merge_recursivo(p, 0, tamano - 1, campo);
}

void merge_optimizado_benchmark(piloto p[], int tamano, int campo){
    // Utiliza la variable global para facilitar la redaccion del informe
    merge_optimizado_recursivo(p, 0, tamano - 1, campo, UMBRAL_ACTUAL_MERGE);
}

void quick_ultimo_benchmark(piloto p[], int tamano, int campo){
    quick_sort_recursivo(p, 0, tamano - 1, campo, 1);
}

void quick_mediana_benchmark(piloto p[], int tamano, int campo){
    quick_sort_recursivo(p, 0, tamano - 1, campo, 4);
}

// ====================== BENCHMARK DE ORDENAMIENTO ======================

void ejecutar_test_sorts(const char* nombre_archivo, int tamanios[], int n_tamanios, int escenario) {
    FILE* f = fopen(nombre_archivo, "w");
    if(!f) return;

    fprintf(f, "Tamano,Bubble,Insertion,Selection,Cocktail,Merge,MergeOpt,QuickUlt,QuickMed\n");
    printf("\nGenerando: %s (Umbral MergeOpt: %d)\n", nombre_archivo, UMBRAL_ACTUAL_MERGE);
    printf("%-10s %-10s %-10s %-10s %-10s\n", "N", "Bubble", "Merge", "QuickM", "Status");

    for(int t=0; t < n_tamanios; t++){
        int tam = tamanios[t];
        piloto* lista = crear_lista(tam);

        if (escenario == 1) { // MEJOR CASO
            buble_sort(lista, tam, 4); 
        } else if (escenario == 2) { // PEOR CASO
            buble_sort(lista, tam, 4);
            invertir_arreglo(lista, tam);
        } else { // PROMEDIO
            fisher_yates(lista, tam);
        }

        int ok_bubble, ok_insertion, ok_selection, ok_cocktail;
        int ok_merge, ok_mergeopt, ok_qult, ok_qmed;
        
        double tb = medir_tiempo_sort(buble_sort, lista, tam, 4, &ok_bubble);
        double ti = medir_tiempo_sort(insertion_sort, lista, tam, 4, &ok_insertion);
        double ts = medir_tiempo_sort(selection_sort, lista, tam, 4, &ok_selection);
        double tc = medir_tiempo_sort(cocktail_shaker_sort, lista, tam, 4, &ok_cocktail);
        double tm = medir_tiempo_sort(merge_benchmark, lista, tam, 4, &ok_merge);
        double tmo = medir_tiempo_sort(merge_optimizado_benchmark, lista, tam, 4, &ok_mergeopt);
        double tq1 = medir_tiempo_sort(quick_ultimo_benchmark, lista, tam, 4, &ok_qult);
        double tq4 = medir_tiempo_sort(quick_mediana_benchmark, lista, tam, 4, &ok_qmed);

        int ok_general = ok_bubble && ok_insertion && ok_selection && ok_cocktail &&
                         ok_merge && ok_mergeopt && ok_qult && ok_qmed;
    
        fprintf(f, "%d,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f\n", 
                tam, tb, ti, ts, tc, tm, tmo, tq1, tq4);
        
        printf("%-10d %-10.8f %-10.8f %-10.8f [%s]\n", tam, tb, tm, tq4, ok_general ? "OK" : "ERROR");
        free(lista);
    }
    fclose(f);
}

void benchmark_sorts(int tamanios[], int n_tamanios){
    ejecutar_test_sorts("docs/sorts_promedio.csv", tamanios, n_tamanios, 0);
    ejecutar_test_sorts("docs/sorts_mejor.csv", tamanios, n_tamanios, 1);
    ejecutar_test_sorts("docs/sorts_peor.csv", tamanios, n_tamanios, 2);
}

// ====================== BENCHMARK DE BUSQUEDAS ======================

void benchmark_busquedas(int tamanios[], int n_tamanios){
    printf("\n=== BENCHMARK BUSQUEDA (Escenarios Adaptativos) ===\n");
    printf("%-12s %-15s %-15s %-15s %-15s\n", "Tamano", "Secuencial", "Binaria", "QuickSelect", "Status");

    FILE* f = fopen("docs/benchmark_busquedas.csv", "w");
    if(!f) return;
    
    fprintf(f, "Tamano,Secuencial(peor),Binaria(peor),BinariaOPT,QuickSelect(k),exponencial,interpolacion\n");

    for(int t=0; t < n_tamanios; t++){
        int tam = tamanios[t];
        piloto* lista = crear_lista(tam);
        buble_sort(lista, tam, 1); 

        double ts = medir_tiempo_busqueda(busqueda_secuencial, lista, tam, -1);
        double tb = medir_tiempo_busqueda(busqueda_binaria_id, lista, tam, -1);
        double tb2 = medir_tiempo_busqueda_binaria_opt(lista, tam, -1);
        double qs = medir_tiempo_qs(lista, 0, tam - 1, (tam/2), 1);
        double exp = medir_tiempo_busqueda(busqueda_exponencial, lista, tam, -1);
        double inter = medir_tiempo_busqueda(busqueda_interpolacion, lista, tam, -1);

        printf("%-12d %-15.8f %-15.8f %-15.4f [OK]\n", tam, ts, tb, qs);

        fprintf(f, "%d,%e,%e,%e,%e,%e,%e\n", tam, ts, tb, tb2, qs, exp, inter);

        free(lista);
    }
    fclose(f);
    printf("\nResultados de busqueda guardados en docs/benchmark_busquedas.csv\n");
}

// ====================== BENCHMARK PROYECTO 3 (GREEDY & DP) ======================

// Función auxiliar para medir Greedy (7 repeticiones)
double medir_tiempo_greedy(void (*funcion_greedy)(piloto[], int, int, int), piloto p[], int tamano, int presupuesto, int criterio) {
    double tiempo_acumulado = 0.0;
    int repeticiones = 7;
    
    for (int i = 0; i < repeticiones; i++) {
        // Creamos una copia para que cada repeticion trabaje con los mismos datos base
        piloto* copia = (piloto*)malloc(tamano * sizeof(piloto));
        memcpy(copia, p, tamano * sizeof(piloto));
        
        clock_t inicio = clock();
        funcion_greedy(copia, tamano, presupuesto, criterio);
        clock_t fin = clock();
        
        tiempo_acumulado += (double)(fin - inicio) / CLOCKS_PER_SEC;
        free(copia);
    }
    return tiempo_acumulado / repeticiones;
}

// Función auxiliar para medir DP (7 repeticiones)
double medir_tiempo_dp(void (*funcion_dp)(piloto[], int, int), piloto p[], int tamano, int presupuesto) {
    double tiempo_acumulado = 0.0;
    int repeticiones = 7;
    
    for (int i = 0; i < repeticiones; i++) {
        piloto* copia = (piloto*)malloc(tamano * sizeof(piloto));
        memcpy(copia, p, tamano * sizeof(piloto));
        
        clock_t inicio = clock();
        funcion_dp(copia, tamano, presupuesto);
        clock_t fin = clock();
        
        tiempo_acumulado += (double)(fin - inicio) / CLOCKS_PER_SEC;
        free(copia);
    }
    return tiempo_acumulado / repeticiones;
}

void benchmark_proyecto3() {
    
    int tamanios_greedy[] = {10, 1000, 5000, 10000, 20000, 30000, 40000, 50000};
    int n_greedy = 8;

   
    int tamanios_dp[] = {10, 50, 100, 500, 1000, 2000, 5000};
    int n_dp = 7;

    int presupuesto = 50000;

    printf("\n=== BENCHMARK PROYECTO 3: GREEDY VS DP ===\n");
    printf("Nota: Los 'printf' internos de los algoritmos generaran mucho texto.\n");
    printf("Para un benchmark limpio, comenta los printf en dp_top_down y greedy_con_restriccion.\n\n");

    FILE* fg = fopen("docs/benchmark_greedy.csv", "w");
    if(fg) {
        fprintf(fg, "Tamano,Greedy_Puntaje,Greedy_Costo,Greedy_Ratio\n");
        printf("Ejecutando Benchmark Greedy (7 repeticiones por tamano)...\n");
        
        for (int t = 0; t < n_greedy; t++) {
            int tam = tamanios_greedy[t];
            piloto* lista = crear_lista(tam);

            double t_g1 = medir_tiempo_greedy(greedy_con_restriccion, lista, tam, presupuesto, 1);
            double t_g2 = medir_tiempo_greedy(greedy_con_restriccion, lista, tam, presupuesto, 2);
            double t_g3 = medir_tiempo_greedy(greedy_con_restriccion, lista, tam, presupuesto, 3);

            fprintf(fg, "%d,%.8f,%.8f,%.8f\n", tam, t_g1, t_g2, t_g3);
            printf("Greedy N=%-6d completado.\n", tam);
            free(lista);
        }
        fclose(fg);
    }

    FILE* fdp = fopen("docs/benchmark_dp.csv", "w");
    if(fdp) {
        fprintf(fdp, "Tamano,DP_TopDown,DP_BottomUp\n");
        printf("\nEjecutando Benchmark Programacion Dinamica (7 repeticiones por tamano)...\n");
        printf("ADVERTENCIA: Si se cae por Segmentation Fault, encontraste el limite de tu RAM.\n");

        for (int t = 0; t < n_dp; t++) {
            int tam = tamanios_dp[t];
            piloto* lista = crear_lista(tam);

            double t_td = medir_tiempo_dp(dp_top_down, lista, tam, presupuesto);
            double t_bu = medir_tiempo_dp(dp_bottom_up, lista, tam, presupuesto);

            fprintf(fdp, "%d,%.8f,%.8f\n", tam, t_td, t_bu);
            printf("DP N=%-6d completado.\n", tam);
            free(lista);
        }
        fclose(fdp);
    }
    printf("\n¡Benchmarks completados! Resultados en docs/benchmark_greedy.csv y docs/benchmark_dp.csv\n");
}
// ====================== BENCHMARK DE CALIDAD (OPTIMALIDAD) ======================

// Comparadores independientes para el benchmark
int bench_cmp_mayor_puntaje(const void *a, const void *b) {
    if (((piloto*)b)->Puntaje > ((piloto*)a)->Puntaje) return 1;
    if (((piloto*)b)->Puntaje < ((piloto*)a)->Puntaje) return -1;
    return 0;
}
int bench_cmp_menor_costo(const void *a, const void *b) {
    return ((piloto*)a)->costo - ((piloto*)b)->costo;
}
int bench_cmp_mejor_ratio(const void *a, const void *b) {
    float ratio_a = ((piloto*)a)->Puntaje / (float)((piloto*)a)->costo;
    float ratio_b = ((piloto*)b)->Puntaje / (float)((piloto*)b)->costo;
    if (ratio_b > ratio_a) return 1;
    if (ratio_b < ratio_a) return -1;
    return 0;
}

// Evaluador Greedy que retorna el puntaje total
float evaluar_calidad_greedy(piloto p[], int tamano, int presupuesto, int criterio) {
    piloto *copia = (piloto *)malloc(tamano * sizeof(piloto));
    memcpy(copia, p, tamano * sizeof(piloto));

    if (criterio == 1) qsort(copia, tamano, sizeof(piloto), bench_cmp_mayor_puntaje);
    else if (criterio == 2) qsort(copia, tamano, sizeof(piloto), bench_cmp_menor_costo);
    else if (criterio == 3) qsort(copia, tamano, sizeof(piloto), bench_cmp_mejor_ratio);

    int costo_total = 0;
    float puntaje_total = 0.0f;
    for (int i = 0; i < tamano; i++) {
        if (costo_total + copia[i].costo <= presupuesto) {
            costo_total += copia[i].costo;
            puntaje_total += copia[i].Puntaje;
        }
    }
    free(copia);
    return puntaje_total;
}

// Evaluador DP Liviano (O(n * W) memoria O(W)) que retorna el puntaje optimo real
float evaluar_calidad_dp(piloto p[], int tamano, int presupuesto) {
    float *dp = (float *)calloc(presupuesto + 1, sizeof(float));
    for (int i = 0; i < tamano; i++) {
        for (int w = presupuesto; w >= p[i].costo; w--) {
            float incluir = p[i].Puntaje + dp[w - p[i].costo];
            if (incluir > dp[w]) dp[w] = incluir;
        }
    }
    float optimo = dp[presupuesto];
    free(dp);
    return optimo;
}

void benchmark_calidad() {
    // Tamaños justos para comparar calidad (Greedy vs DP optimo real)
    int tamanios[] = {10, 50, 100, 500, 1000}; 
    int n_tam = 5;
    int presupuesto = 50000;

    FILE* f = fopen("docs/benchmark_calidad.csv", "w");
    if(f) {
        fprintf(f, "Tamano,Optimo_DP,Greedy_Puntaje,Greedy_Costo,Greedy_Ratio\n");
        printf("\n=== BENCHMARK DE CALIDAD (PUNTAJE OBTENIDO) ===\n");
        
        for (int t = 0; t < n_tam; t++) {
            int tam = tamanios[t];
            piloto* lista = crear_lista(tam);
            
            float p_dp = evaluar_calidad_dp(lista, tam, presupuesto);
            float p_g1 = evaluar_calidad_greedy(lista, tam, presupuesto, 1);
            float p_g2 = evaluar_calidad_greedy(lista, tam, presupuesto, 2);
            float p_g3 = evaluar_calidad_greedy(lista, tam, presupuesto, 3);

            fprintf(f, "%d,%.2f,%.2f,%.2f,%.2f\n", tam, p_dp, p_g1, p_g2, p_g3);
            printf("N=%-4d | Optimo DP: %-8.2f | G_Puntaje: %-8.2f | G_Costo: %-8.2f | G_Ratio: %-8.2f\n", 
                   tam, p_dp, p_g1, p_g2, p_g3);
            
            free(lista);
        }
        fclose(f);
        printf("Resultados guardados en docs/benchmark_calidad.csv\n");
    }
}