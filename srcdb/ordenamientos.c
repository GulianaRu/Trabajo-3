#include "../incs/piloto.h"

// ====================== ALGORITMOS DE ORDENAMIENTO ======================
// los algoritmos de busqueda , ordenamientos y quick select fueron inspirados de https://www.geeksforgeeks.org/
// todos reciben el campo a ordenar: 1=Id, 2=Nombre, 3=Equipo, 4=Puntaje, 5=Competencias

// bubble sort con optimizacion para detectar arreglos ya ordenados
void buble_sort(piloto p[], int tamano, int campo){
    piloto paux;
    int i;
    int j;
    int swap;
    for(i=0; i<tamano-1; i++){
        swap = 0;
        for(j=0; j<tamano-1-i; j++){
            if(comparar(p[j], p[j+1], campo) > 0){
                paux = p[j];
                p[j] = p[j+1];
                p[j+1] = paux;
                swap = 1;
            }
        }
        if(swap == 0){
            break;
        }
    }
}

// insertion sort estandar
void insertion_sort(piloto p[], int tamano, int campo){
    piloto key;
    int i;
    int j;
    for(i=1; i<tamano; i++){
        key = p[i];
        j = i - 1;
        while(j >= 0 && comparar(p[j], key, campo) > 0){
            p[j+1] = p[j];
            j--;
        }
        p[j+1] = key;
    }
}

// selection sort con optimizacion para evitar intercambios innecesarios
void selection_sort(piloto p[], int tamano, int campo){
    piloto paux;
    int min_index;
    int i;
    int j;
    for(i=0; i<tamano-1; i++){
        min_index = i;
        for(j = i + 1; j < tamano; j++){
            if(comparar(p[j], p[min_index], campo) < 0){
                min_index = j;
            }
        }
        // optimizacion: solo intercambia si el minimo no esta en su lugar
        if(min_index != i){       
            paux = p[i];          
            p[i] = p[min_index];
            p[min_index] = paux;
        }
    }
}

// cocktail_shaker_sort fue basado en un ejemplo dado por grok ia
void cocktail_shaker_sort(piloto p[], int tamano, int campo){
    piloto paux;
    int i;
    int izq = 0;
    int der = tamano - 1;
    int swap;
    do {
        swap = 0;
        for(i=izq; i<der; i++){
            if(comparar(p[i], p[i+1], campo) > 0){
                paux = p[i];
                p[i] = p[i+1];
                p[i+1] = paux;
                swap = 1;
            }
        }
        der--;
        for(i=der; i>izq; i--){
            if(comparar(p[i], p[i-1], campo) < 0){
                paux = p[i];
                p[i] = p[i-1];
                p[i-1] = paux;
                swap = 1;
            }
        }
        izq++;
    } while(swap && izq < der);
}

// ====================== MERGE SORT ======================
void mezclar(piloto p[], int izq, int medio, int der, int campo){
    int n1 = medio - izq + 1;
    int n2 = der - medio;

    piloto *izquierda = (piloto*)malloc(n1 * sizeof(piloto));
    piloto *derecha = (piloto*)malloc(n2 * sizeof(piloto));

    if(izquierda == NULL || derecha == NULL){
        printf("Error al reservar memoria en merge sort\n");
        free(izquierda);
        free(derecha);
        return;
    }

    for(int i = 0; i < n1; i++){
        izquierda[i] = p[izq + i];
    }

    for(int j = 0; j < n2; j++){
        derecha[j] = p[medio + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = izq;

    while(i < n1 && j < n2){
        if(comparar(izquierda[i], derecha[j], campo) <= 0){
            p[k] = izquierda[i];
            i++;
        }
        else{
            p[k] = derecha[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        p[k] = izquierda[i];
        i++;
        k++;
    }

    while(j < n2){
        p[k] = derecha[j];
        j++;
        k++;
    }

    free(izquierda);
    free(derecha);
}

// merge sort clasico recursivo
void merge_recursivo(piloto p[], int izq, int der, int campo){
    if(izq < der){
        int medio = izq + (der - izq) / 2;

        merge_recursivo(p, izq, medio, campo);
        merge_recursivo(p, medio + 1, der, campo);

        mezclar(p, izq, medio, der, campo);
    }
}

// insertion sort aplicado solo a un rango del arreglo
// se usa para el merge sort optimizado
void insertion_sort_rango(piloto p[], int izq, int der, int campo){
    piloto key;
    int i;
    int j;

    for(i = izq + 1; i <= der; i++){
        key = p[i];
        j = i - 1;

        while(j >= izq && comparar(p[j], key, campo) > 0){
            p[j + 1] = p[j];
            j--;
        }

        p[j + 1] = key;
    }
}

// merge sort optimizado con insertion sort para arreglos pequenos
void merge_optimizado_recursivo(piloto p[], int izq, int der, int campo, int umbral){
    if(izq >= der){
        return;
    }

    if((der - izq + 1) <= umbral){
        insertion_sort_rango(p, izq, der, campo);
        return;
    }

    int medio = izq + (der - izq) / 2;

    merge_optimizado_recursivo(p, izq, medio, campo, umbral);
    merge_optimizado_recursivo(p, medio + 1, der, campo, umbral);

    mezclar(p, izq, medio, der, campo);
}

// funcion principal que llama el main
void merge(piloto p[], int tamano, int campo){
    int opcion;
    int umbral;

    printf("\nTipo de Merge Sort:\n");
    printf("1. Clasico\n");
    printf("2. Optimizado con Insertion Sort\n");
    printf("Opcion: ");
    scanf("%d", &opcion);

    if(opcion == 1){
        merge_recursivo(p, 0, tamano - 1, campo);
    }
    else if(opcion == 2){
        printf("Ingrese umbral para usar Insertion Sort, por ejemplo 10, 20 o 30: ");
        scanf("%d", &umbral);

        if(umbral <= 0){
            umbral = 20;
        }

        merge_optimizado_recursivo(p, 0, tamano - 1, campo, umbral);
    }
    else{
        printf("Opcion invalida\n");
    }
}

// ====================== QUICK SORT ======================
// intercambia dos pilotos
void swap_piloto(piloto *a, piloto *b){
    piloto aux = *a;
    *a = *b;
    *b = aux;
}

// seleccion del pivote:
// 1 = ultimo elemento
// 2 = primer elemento
// 3 = aleatorio
// 4 = mediana de tres
int seleccionar_pivote(piloto p[], int izq, int der, int campo, int tipo_pivote){
    if(tipo_pivote == 1){
        return der;
    }
    else if(tipo_pivote == 2){
        return izq;
    }
    else if(tipo_pivote == 3){
        return izq + rand() % (der - izq + 1);
    }
    else if(tipo_pivote == 4){
        int medio = izq + (der - izq) / 2;

        piloto a = p[izq];
        piloto b = p[medio];
        piloto c = p[der];

        if((comparar(a, b, campo) <= 0 && comparar(b, c, campo) <= 0) ||
           (comparar(c, b, campo) <= 0 && comparar(b, a, campo) <= 0)){
            return medio;
        }

        if((comparar(b, a, campo) <= 0 && comparar(a, c, campo) <= 0) ||
           (comparar(c, a, campo) <= 0 && comparar(a, b, campo) <= 0)){
            return izq;
        }

        return der;
    }

    return der;
}

// particion de Lomuto para quick sort
int partition_quick_sort(piloto p[], int izq, int der, int campo, int tipo_pivote){
    int indice_pivote = seleccionar_pivote(p, izq, der, campo, tipo_pivote);

    // Lomuto trabaja con el pivote al final, por eso se mueve el pivote elegido a der
    swap_piloto(&p[indice_pivote], &p[der]);

    piloto pivote = p[der];
    int i = izq - 1;

    for(int j = izq; j <= der - 1; j++){
        if(comparar(p[j], pivote, campo) <= 0){
            i++;
            swap_piloto(&p[i], &p[j]);
        }
    }

    swap_piloto(&p[i + 1], &p[der]);
    return i + 1;
}

// quick sort recursivo
void quick_sort_recursivo(piloto p[], int izq, int der, int campo, int tipo_pivote){
    if(izq < der){
        int pivote = partition_quick_sort(p, izq, der, campo, tipo_pivote);

        quick_sort_recursivo(p, izq, pivote - 1, campo, tipo_pivote);
        quick_sort_recursivo(p, pivote + 1, der, campo, tipo_pivote);
    }
}

// funcion principal que llama el main
void quick_sort(piloto p[], int tamano, int campo){
    int tipo_pivote;

    printf("\nTipo de pivote para Quick Sort:\n");
    printf("1. Ultimo elemento\n");
    printf("2. Primer elemento\n");
    printf("3. Elemento aleatorio\n");
    printf("4. Mediana de tres\n");
    printf("Opcion: ");
    scanf("%d", &tipo_pivote);

    if(tipo_pivote >= 1 && tipo_pivote <= 4){
        quick_sort_recursivo(p, 0, tamano - 1, campo, tipo_pivote);
    }
    else{
        printf("Tipo de pivote invalido\n");
    }
}