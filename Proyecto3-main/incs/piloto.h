#ifndef piloto_H
#define piloto_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct 
{
    int Id;
    char Nombre[20];
    char Equipo[15];
    float Puntaje;
    int Competencias;
    int costo;
} piloto;

// Pilotos y utilidades
int comparar(piloto a, piloto b, int campo);
piloto inicializar_piloto(int registro, piloto a);
piloto* crear_lista(int tamano);
void fisher_yates(piloto p[], int tamano);
void guardar_en_csv(piloto lista[], int tamano, const char* nombre_archivo);
piloto* leer_csv(const char* nombre_archivo, int tamano_esperado);
int esta_ordenado(piloto p[], int tamano, int campo);

// Ordenamientos
void buble_sort(piloto p[], int tamano, int campo);
void insertion_sort(piloto p[], int tamano, int campo);
void selection_sort(piloto p[], int tamano, int campo);
void cocktail_shaker_sort(piloto p[], int tamano, int campo);
void merge(piloto p[], int tamano, int campo);
void quick_sort(piloto p[], int tamano, int campo);

// Quick Select
int partition(piloto p[], int izq, int der, int campo);
int quick_select(piloto p[], int izq, int der, int k, int campo);

// Busquedas
int busqueda_secuencial(piloto p[], int tamano, int id_buscado);
int busqueda_binaria_id(piloto p[], int tamano, int id_buscado);
int busqueda_binaria_recursiva(piloto p[], int id_buscado, int bajo, int alto);
int busqueda_interpolacion(piloto p[], int tamano, int id_buscado);
int busqueda_exponencial(piloto p[], int tamano, int id_buscado);
void busqueda_rango_puntaje(piloto p[], int tamano, float minimo, float maximo);

// Benchmarks
void benchmark_sorts(int tamanios[], int n_tamanios);
void benchmark_busquedas(int tamanios[], int n_tamanios);

void merge_benchmark(piloto p[], int tamano, int campo);
void merge_optimizado_benchmark(piloto p[], int tamano, int campo);
void quick_ultimo_benchmark(piloto p[], int tamano, int campo);
void quick_mediana_benchmark(piloto p[], int tamano, int campo);

// Funciones recursivas internas
void merge_recursivo(piloto p[], int izq, int der, int campo);
void merge_optimizado_recursivo(piloto p[], int izq, int der, int campo, int umbral);
void quick_sort_recursivo(piloto p[], int izq, int der, int campo, int tipo_pivote);

// Greedy
void greedy_con_restriccion(piloto p[], int tamano, int presupuesto, int estrategia);
void greedy_sin_restriccion(piloto p[], int tamano, int cantidad_a_seleccionar);

// Programacion Dinamica
void dp_bottom_up(piloto p[], int tamano, int presupuesto);
void dp_top_down(piloto p[], int tamano, int presupuesto);

#endif