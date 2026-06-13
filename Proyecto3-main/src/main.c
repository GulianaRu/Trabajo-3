#include <stdio.h>
#include "../incs/piloto.h"

int main(){
    srand(time(NULL));
    int opcion;
    int tamano = 0;
    piloto* p = NULL;

    do {
        printf("\n===== MENU =====\n");
        printf("1. Generar datos\n");
        printf("2. Ordenar (con justificacion de algoritmos)\n");
        printf("3. Busquedas\n");
        printf("4. Ranking top N (aislado con Quick Select)\n");
        printf("5. Benchmark algoritmos\n");
        printf("6. Quick select (busqueda k-esimo)\n");
        printf("7. Conformar Equipo (Proyecto 3 - DP & Greedy)\n");
        printf("8. Salir\n");
        printf("9. Estructura de un deportista\n");
        printf("Opcion: ");
        
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n'); 
            opcion = -1; 
        }
        
        switch(opcion){
            case 1: {
                printf("Cuantos deportistas generar: ");
                scanf("%d", &tamano);
                if(p != NULL) free(p);
                p = crear_lista(tamano);
                fisher_yates(p, tamano);
                guardar_en_csv(p, tamano, "db/a.csv");
                break;
            }
            case 2: {
                if(p == NULL){
                    printf("Primero genera los datos (opcion 1)\n");
                    break;
                }
                int algoritmo, campo;
                printf("\n--- MENU DE ORDENAMIENTO ---\n");
                printf("Seleccione el campo a ordenar:\n");
                printf("1. ID\n2. Nombre\n3. Equipo\n4. Puntaje\n5. Competencias\n");
                printf("Opcion: ");
                scanf("%d", &campo);
                
                if(campo < 1 || campo > 5) {
                    printf("Campo invalido, ordenando por Puntaje por defecto.\n");
                    campo = 4; 
                }

                printf("\nSeleccione el Algoritmo:\n");
                printf("  -- Algoritmos Tarea 1 --\n");
                printf("1. Bubble Sort\n");
                printf("2. Insertion Sort\n");
                printf("3. Selection Sort\n");
                printf("4. Cocktail Shaker Sort\n");
                printf("  -- Algoritmos Tarea 2 --\n");
                printf("5. Merge sort (Estable, O(N log N))\n");
                printf("6. Quick sort (Eficiente en memoria in-place)\n");
                printf("Opcion: ");
                scanf("%d", &algoritmo);
                
                switch(algoritmo){
                    case 1: 
                        printf("-> Ordenando con Bubble Sort...\n");
                        buble_sort(p, tamano, campo); 
                        break;
                    case 2: 
                        printf("-> Ordenando con Insertion Sort...\n");
                        insertion_sort(p, tamano, campo); 
                        break;
                    case 3: 
                        printf("-> Ordenando con Selection Sort...\n");
                        selection_sort(p, tamano, campo); 
                        break;
                    case 4: 
                        printf("-> Ordenando con Cocktail Shaker Sort...\n");
                        cocktail_shaker_sort(p, tamano, campo); 
                        break;
                    case 5: 
                        printf("-> Ordenando con Merge Sort...\n");
                        merge(p, tamano, campo); 
                        break;
                    case 6: 
                        printf("-> Ordenando con Quick Sort...\n");
                        quick_sort(p, tamano, campo); 
                        break;
                    default: 
                        printf("Algoritmo invalido\n");
                        continue; // Salta al menu sin guardar si eligio mal
                }
                printf("Ordenado correctamente en la memoria.\n");
                
                guardar_en_csv(p, tamano, "db/ordenado.csv");
                printf("-> ¡Listo! Abre el archivo 'db/ordenado.csv' para verificar que se ordeno bien.\n");
                break;
            }
            case 3: {
                if(p == NULL){
                    printf("Primero genera los datos (opcion 1)\n");
                    break;
                }
                
                int tipo_busqueda;
                printf("\n--- MENU DE BUSQUEDAS ---\n");
                printf("  -- Algoritmos Tarea 1 --\n");
                printf("1. Busqueda Secuencial\n");
                printf("2. Busqueda Binaria Iterativa\n");
                printf("  -- Algoritmos Tarea 2 --\n");
                printf("3. Busqueda Binaria Recursiva\n");
                printf("4. Busqueda por Interpolacion\n");
                printf("5. Busqueda Exponencial\n");
                printf("6. Busqueda de Rangos (Por Puntaje)\n");
                printf("Opcion: ");
                scanf("%d", &tipo_busqueda);

                // Opciones del 1 al 5 buscan por ID
                if (tipo_busqueda >= 1 && tipo_busqueda <= 5) {
                    int id;
                    printf("Ingrese el ID a buscar: ");
                    if (scanf("%d", &id) != 1) {
                        while (getchar() != '\n');
                        printf("Entrada invalida. Debe ser un numero.\n");
                        continue; 
                    }
                    
                    int resultado = -1;

                    // AQUI ESTA LA PROTECCION: Si no es la secuencial, debe estar ordenado
                    if (tipo_busqueda != 1) { 
                         printf("-> [Info] Ordenando datos por ID con Quick Sort antes de buscar...\n");
                         quick_sort_recursivo(p, 0, tamano - 1, 1, 4); // Ordena por Campo 1 (ID)
                    }

                    switch(tipo_busqueda) {
                        case 1: resultado = busqueda_secuencial(p, tamano, id); break;
                        case 2: resultado = busqueda_binaria_id(p, tamano, id); break; // Tarea 1
                        case 3: resultado = busqueda_binaria_recursiva(p, id, 0, tamano - 1); break; // Tarea 2
                        case 4: resultado = busqueda_interpolacion(p, tamano, id); break;
                        case 5: resultado = busqueda_exponencial(p, tamano, id); break;
                    }

                    if(resultado == -1){
                        printf("\nNo se encontro a ningun deportista con el ID %d.\n", id);
                    } else {
                        printf("\n[DEPORTISTA ENCONTRADO]\n");
                        printf("ID: %d | Nombre: %s | Equipo: %s | Puntaje: %.2f | Competencias: %d\n",
                            p[resultado].Id, p[resultado].Nombre, p[resultado].Equipo, p[resultado].Puntaje, p[resultado].Competencias);
                    }
                } 
                // La opcion 6 (Rangos) busca por Puntaje
                else if (tipo_busqueda == 6) {
                    float minimo, maximo;

                    printf("Ingrese el puntaje minimo a buscar: ");
                    scanf("%f", &minimo);
                    printf("Ingrese el puntaje maximo a buscar: ");
                    scanf("%f", &maximo);
                    
                    if(minimo > maximo){
                        float aux = minimo;
                        minimo = maximo;
                        maximo = aux;
                    }

                    // datos ordenados por puntaje para mostrar los resultados en orden
                    printf("-> [Info] Ordenando datos por PUNTAJE con Merge Sort optimizado antes de buscar rangos...\n");
                    merge_optimizado_recursivo(p, 0, tamano - 1, 4, 15);
                    busqueda_rango_puntaje(p, tamano, minimo, maximo);
                }
                else {
                    printf("Opcion de busqueda invalida.\n");
                }
                break;
            }
            case 4: {
                if(p == NULL){
                    printf("Primero genera los datos (opcion 1)\n");
                    break;
                }
                int n;
                printf("Cuantos deportistas mostrar en el Top: ");
                scanf("%d", &n);
                if(n > tamano) n = tamano;
                
                // Usamos quick select para mover los Top N al final de la lista sin ordenar lo demas (O(N))
                int indice_corte = tamano - n;
                quick_select(p, 0, tamano - 1, indice_corte + 1, 4); 
                
                // Luego ordenamos unicamente a esos N mejores para listarlos bonito (O(N log N) pero solo para los mejores)
                merge_optimizado_recursivo(p, indice_corte, tamano - 1, 4, 15);
                
                printf("\n=== TOP %d MEJORES DEPORTISTAS ===\n", n);
                printf("(Generado optimizadamente usando Quick Select para aislamiento)\n");
                for(int i = tamano - 1; i >= tamano - n; i--){
                    printf("%d. %s | Puntaje: %.2f\n",
                        tamano - i, p[i].Nombre, p[i].Puntaje);
                }
                break;
            }
            case 5: {
                int tamanios[] = {1000, 5000, 10000, 50000}; 
                int n_tamanios = 4; 
                
                benchmark_sorts(tamanios, n_tamanios);
                benchmark_busquedas(tamanios, n_tamanios);
                break;
            }
            case 6: {
                if(p == NULL){
                    printf("Primero genera los datos (opcion 1)\n");
                    break;
                }
                int k, aux;
                printf("Buscar el k-esimo deportista por puntaje\n");
                printf("Ingresa k: ");
                scanf("%d", &k);
                
                if (k < 1 || k > tamano) {
                    printf("k debe estar entre 1 y %d\n", tamano);
                    break;
                }
                
                aux = quick_select(p, 0, tamano - 1, tamano - k + 1, 4);
                
                if (aux != -1) {
                    printf("El %d-esimo deportista por puntaje es:\n", k);
                    printf("ID: %d | Nombre: %s | Equipo: %s | Puntaje: %.2f | Competencias: %d (En indice %d)\n",
                            p[aux].Id, p[aux].Nombre, p[aux].Equipo, p[aux].Puntaje, p[aux].Competencias, aux);
                }
                break;
            }
          case 7: {
            if(p == NULL){
                printf("Primero genera los datos (opcion 1)\n");
                break;
            }
            int sub_opcion;
            printf("\n--- CONFORMAR EQUIPO (PROYECTO 3) ---\n");
            printf("1. Estrategias Greedy (Con restriccion de presupuesto)\n");
            printf("2. Estrategia Greedy (Sin restriccion)\n");
            printf("3. Programacion Dinamica (Top-Down / Bottom-Up)\n");
            printf("Opcion: ");
            scanf("%d", &sub_opcion);
            
            if (sub_opcion == 1) {
                int presu;
                printf("Ingrese el presupuesto maximo disponible: ");
                scanf("%d", &presu);
                printf("\n-> Ejecutando algoritmos Greedy...\n");
                greedy_con_restriccion(p, tamano, presu, 1); // 1 = Mayor Puntaje
                greedy_con_restriccion(p, tamano, presu, 2); // 2 = Menor Costo
                greedy_con_restriccion(p, tamano, presu, 3); // 3 = Mejor Ratio (Puntaje/Costo)
            } 
            else if (sub_opcion == 2) {
                int cantidad;
                printf("Cuantos deportistas desea seleccionar: ");
                scanf("%d", &cantidad);
                greedy_sin_restriccion(p, tamano, cantidad);
            } 
            else if (sub_opcion == 3) {
                int presu, dp_opcion;
                printf("Ingrese el presupuesto maximo disponible: ");
                scanf("%d", &presu);
                printf("Seleccione el metodo DP:\n");
                printf("1. Top-Down (Memoization recursivo)\n");
                printf("2. Bottom-Up (Tabulation iterativo)\n");
                printf("Opcion: ");
                scanf("%d", &dp_opcion);
                
                if (dp_opcion == 1) dp_top_down(p, tamano, presu);
                else if (dp_opcion == 2) dp_bottom_up(p, tamano, presu);
                else printf("Metodo invalido.\n");
            } 
            else {
                printf("Opcion invalida.\n");
            }
            break;
        }
        case 8:
                printf("Saliendo...\n");
                break;
        case 9:
                printf("Estructura de un deportista (Ejemplo)\n");
            printf("Id,Nombre,Equipo,Puntaje,Competencias,Costo\n");
            printf("33440,UFKMTAPEI,Ford,171.00,135,5000\n");
                break;
            default:
                printf("Opcion invalida\n");
                break;
        }
    } while(opcion != 8);

    if(p != NULL) free(p);
    return 0;
}
