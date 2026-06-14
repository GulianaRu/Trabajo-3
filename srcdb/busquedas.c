#include "../incs/piloto.h"
#include <math.h>

// ====================== ALGORITMOS DE BUSQUEDA ======================

// busqueda secuencial estandar, no requiere orden previo
int busqueda_secuencial(piloto p[], int tamano, int id_buscado){
    int i;
    for(i=0; i<tamano; i++){
        if(p[i].Id == id_buscado){
            return i;
        }
    }
    return -1;
}

// busqueda binaria por id en version iterativa (requiere arreglo ordenado por Id)
int busqueda_binaria_id(piloto p[], int tamano, int id_buscado){
    int abajo = 0;
    int alto = tamano - 1;
    int mid;
    while(abajo <= alto){
        mid = abajo + (alto - abajo) / 2;
        if(p[mid].Id == id_buscado){
            return mid;
        }
        if(p[mid].Id < id_buscado){
            abajo = mid + 1;
        }
        else{
            alto = mid - 1;
        }
    }
    return -1;
}

int busqueda_binaria_recursiva(piloto p[], int id_buscado, int bajo, int alto) {
    if (bajo > alto) {
        return -1; // Si no se encontro
    }
    
    int mid = bajo + (alto - bajo) / 2;
    
    if (p[mid].Id == id_buscado) return mid;
    
    if (p[mid].Id > id_buscado) {
        return busqueda_binaria_recursiva(p, id_buscado, bajo, mid - 1);
    } else {
        return busqueda_binaria_recursiva(p, id_buscado, mid + 1, alto);
    }
}

int busqueda_interpolacion(piloto p[], int tamano, int id_buscado) {
    int bajo = 0, alto = tamano - 1;

    while (bajo <= alto && id_buscado >= p[bajo].Id && id_buscado <= p[alto].Id) {
        if (bajo == alto) {
            if (p[bajo].Id == id_buscado) return bajo;
            return -1;
        }

        // aplicacion de la formula
        int pos = bajo + (((double)(alto - bajo) / (p[alto].Id - p[bajo].Id)) * (id_buscado - p[bajo].Id));

        if (p[pos].Id == id_buscado) return pos;
        if (p[pos].Id < id_buscado) bajo = pos + 1;
        else alto = pos - 1;
    }
    return -1;
}

int busqueda_exponencial(piloto p[], int tamano, int id_buscado) {
    if (p[0].Id == id_buscado) return 0;

    int i = 1;
    while (i < tamano && p[i].Id <= id_buscado) {
        i = i * 2;
    }

    // Llama a la funcion recursiva para el rango encontrado
    // Usamos fmin para no pasarnos del tamaño del arreglo
    return busqueda_binaria_recursiva(p, id_buscado, i / 2, fmin(i, tamano - 1));
}

// ====================== BUSQUEDA DE RANGOS (OPTIMIZADA O(log N)) ======================

int buscar_primera_ocurrencia(piloto p[], int tamano, float puntaje_buscado) {
    int bajo = 0, alto = tamano - 1;
    int resultado = -1;

    while (bajo <= alto) {
        int mid = bajo + (alto - bajo) / 2;
        if (p[mid].Puntaje == puntaje_buscado) {
            resultado = mid; 
            alto = mid - 1; // seguimos buscando hacia la izquierda
        } else if (p[mid].Puntaje < puntaje_buscado) {
            bajo = mid + 1;
        } else {
            alto = mid - 1;
        }
    }
    return resultado;
}

int buscar_ultima_ocurrencia(piloto p[], int tamano, float puntaje_buscado) {
    int bajo = 0, alto = tamano - 1;
    int resultado = -1;

    while (bajo <= alto) {
        int mid = bajo + (alto - bajo) / 2;
        if (p[mid].Puntaje == puntaje_buscado) {
            resultado = mid; 
            bajo = mid + 1; // seguimos buscando hacia la derecha
        } else if (p[mid].Puntaje < puntaje_buscado) {
            bajo = mid + 1;
        } else {
            alto = mid - 1;
        }
    }
    return resultado;
}

void busqueda_rango_puntaje(piloto p[], int tamano, float minimo, float maximo){ 
    int encontrados = 0;
    printf("-> [Info] Mostrando deportistas con puntaje entre %.2f y %.2f:\n", minimo, maximo);

    for(int i = 0; i < tamano; i++){
        if(p[i].Puntaje > maximo){
            break;
        }

        if(p[i].Puntaje >= minimo && p[i].Puntaje <= maximo){
            printf("ID: %d | Nombre: %s | Equipo: %s | Puntaje: %.2f | Competencias: %d\n",
                   p[i].Id, p[i].Nombre, p[i].Equipo, p[i].Puntaje, p[i].Competencias);
            encontrados++;
        }
    }

    if(encontrados == 0){
        printf("No se encontraron deportistas dentro de ese rango.\n");
    }
    else{
        printf("\nTotal encontrados: %d\n", encontrados);
    }
}

// ====================== QUICK SELECT ======================
int partition(piloto p[], int izq, int der, int campo){
    piloto paux;
    piloto par = p[der];
    int i = (izq - 1);
    int j;
    for (j = izq; j <= der; j++){
        if(comparar(p[j], par, campo) < 0){
            i++;
            paux = p[j];
            p[j] = p[i];
            p[i] = paux;
        }
    }
    paux = p[i+1];
    p[i+1] = p[der];
    p[der] = paux;
    return (i + 1);
}

int quick_select(piloto p[], int izq, int der, int k, int campo){
    int pivote = partition(p,izq,der,campo);
    if(pivote == k - 1){
        return pivote;
    }
    else if(pivote > k - 1){
        return quick_select(p,izq,pivote-1,k,campo);
    }
    else{
        return quick_select(p,pivote+1,der,k,campo);
    }
    return -1;
}