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