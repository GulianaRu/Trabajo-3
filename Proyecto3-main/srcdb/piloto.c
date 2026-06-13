#include "../incs/piloto.h"

// ====================== COMPARADOR POR CAMPO ======================
// compara dos pilotos segun el campo indicado:
// 1=Id, 2=Nombre, 3=Equipo, 4=Puntaje, 5=Competencias
// retorna negativo si a < b, 0 si iguales, positivo si a > b
int comparar(piloto a, piloto b, int campo){
    switch(campo){
        case 1: return a.Id - b.Id;
        case 2: return strcmp(a.Nombre, b.Nombre);
        case 3: return strcmp(a.Equipo, b.Equipo);
        case 4: return (a.Puntaje > b.Puntaje) - (a.Puntaje < b.Puntaje);
        case 5: return a.Competencias - b.Competencias;
        default: return 0;
    }
}

// ====================== INICIALIZAR PILOTO ======================
// informacion de escoger nombre al azar sacada de https://www.forosdelweb.com/f96/seleccionar-elemento-aleatorio-array-con-c-912843/
piloto inicializar_piloto(int registro, piloto a){
    a.Id = registro;
    int i;

    // generamos nombre solo con letras A-Z (antes incluia caracteres especiales como [, \, ])
    for(i = 0; i < 9; i++){
        // rand() % 26 da un numero entre 0 y 25, + 65 da A-Z
        a.Nombre[i] = (rand() % 26) + 65;
    }
    a.Nombre[9] = '\0';

    const char *equipos[] = {"Red Bull", "Monster", "Castrol", "Shell", "Mobil 1", "Pirelli", "Michelin", "Goodyear", "Bridgestone", "Ferrari", "Lamborghini", "Porsche", 
        "McLaren", "Aston Martin", "Bugatti", "Pagani", "Koenigsegg", "BMW", "Audi", "Mercedes-Benz", "Honda", "Toyota", "Nissan", "Subaru", "Mazda", "Ford", "Chevrolet", 
        "Dodge", "Jeep", "Hyundai", "Kia", "Peugeot", "Renault", "Citroën", "Volkswagen", "Volvo", "Jaguar", "Land Rover", "Alfa Romeo", "Maserati", "Lotus", "Sauber", 
        "Haas", "Williams", "Oracle", "Petronas", "Aramco", "Texaco", "Bosch", "Brembo"};

    int indice = rand() % 50;
    strcpy(a.Equipo, equipos[indice]);

    // puntaje entre 0.0 y 10000.0
    a.Puntaje = (float)(rand() % 1000000) / 100.0f;
    // competencias entre 1 y 200
    a.Competencias = (rand() % 200) + 1;
    // costo entre 1000 y 100000
    a.costo = (rand() % 99001) + 1000; 
    return a;
}

piloto* crear_lista(int tamano){
    int i;
    piloto* carrera = (piloto*)malloc(tamano * sizeof(piloto));
    if(carrera == NULL){
        printf("Error: No se pudo reservar memoria\n");
        return NULL;
    }
    for(i=0; i<tamano; i++){
        carrera[i] = inicializar_piloto(i, carrera[i]);
    }
    return carrera;
}

// ====================== MEZCLAR ======================
void fisher_yates(piloto p[], int tamano){
    int i, j;
    piloto paux;
    for(i = tamano - 1; i > 0; i--){
        j = rand() % (i + 1);
        paux = p[i];
        p[i] = p[j];
        p[j] = paux;
    }
}

// ====================== CSV ======================
// el guardar csv y el leer csv fueron hechos por grok
void guardar_en_csv(piloto lista[], int tamano, const char* nombre_archivo){
    FILE *archivo = fopen(nombre_archivo, "w");
    if(archivo == NULL){
        printf("Error: No se pudo abrir %s para escritura\n", nombre_archivo);
        return;
    }

    // encabezado del CSV
    fprintf(archivo, "Id,Nombre,Equipo,Puntaje,Competencias,Costo\n");

    // escribir cada piloto en una linea
    for(int i = 0; i < tamano; i++){
        fprintf(archivo, "%d,%s,%s,%.2f,%d,%d\n",
                lista[i].Id,
                lista[i].Nombre,
                lista[i].Equipo,
                lista[i].Puntaje,
                lista[i].Competencias,
                lista[i].costo);
    }

    fclose(archivo);
    printf("Datos guardados correctamente en %s (%d pilotos)\n", nombre_archivo, tamano);
}

piloto* leer_csv(const char* nombre_archivo, int tamano_esperado){
    FILE* archivo = fopen(nombre_archivo, "r");
    if(archivo == NULL){
        printf("Error: No se pudo abrir %s\n", nombre_archivo);
        return NULL;
    }

    char linea[256];

    // saltar encabezado de forma segura (evita la advertencia de gcc)
    if(fgets(linea, sizeof(linea), archivo) == NULL){
        printf("El archivo esta vacio o no tiene encabezado\n");
        fclose(archivo);
        return NULL;
    }

    // reservamos exactamente la memoria que necesitamos
    piloto* lista = (piloto*)malloc(tamano_esperado * sizeof(piloto));
    if(lista == NULL){
        printf("Error: No se pudo reservar memoria\n");
        fclose(archivo);
        return NULL;
    }

    int tamano = 0;
    while(fgets(linea, sizeof(linea), archivo) && tamano < tamano_esperado){
        int id, competencias, costo;
        char nombre[20], equipo[15];
        float puntaje;

        if(sscanf(linea, "%d,%19[^,],%14[^,],%f,%d,%d",
                   &id, nombre, equipo, &puntaje, &competencias, &costo) == 6){
            lista[tamano].Id           = id;
            strcpy(lista[tamano].Nombre, nombre);
            strcpy(lista[tamano].Equipo, equipo);
            lista[tamano].Puntaje      = puntaje;
            lista[tamano].Competencias = competencias;
            lista[tamano].costo        = costo;
            tamano++;
        }
    }

    fclose(archivo);
    printf("Cargados %d pilotos desde %s (esperados: %d)\n", tamano, nombre_archivo, tamano_esperado);
    return lista;    
}

// ====================== PROGRAMACION DINAMICA (MOCHILA 0/1) ======================

// 1. Bottom-Up (Tabulacion)
void dp_bottom_up(piloto p[], int tamano, int presupuesto) {
    // Reservamos una matriz dp[tamano+1][presupuesto+1] dinamicamente
    float **dp = (float **)malloc((tamano + 1) * sizeof(float *));
    if (!dp) return;
    for (int i = 0; i <= tamano; i++) {
        dp[i] = (float *)calloc(presupuesto + 1, sizeof(float));
        if (!dp[i]) { // Proteccion por si se acaba la RAM con tamaños muy grandes
            printf("[Error] Memoria insuficiente para DP Bottom-Up con presupuesto %d y tamano %d\n", presupuesto, tamano);
            for(int j = 0; j < i; j++) free(dp[j]);
            free(dp);
            return;
        }
    }

    // Rellenar tabla Bottom-Up
    for (int i = 1; i <= tamano; i++) {
        for (int w = 0; w <= presupuesto; w++) {
            if (p[i-1].costo <= w) {
                float incluir = p[i-1].Puntaje + dp[i-1][w - p[i-1].costo];
                float excluir = dp[i-1][w];
                dp[i][w] = (incluir > excluir) ? incluir : excluir;
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    // Reconstruccion de la solucion (Que pilotos fueron elegidos)
    int w = presupuesto, costo_total = 0, seleccionados = 0;
    float puntaje_total = dp[tamano][presupuesto];

    for (int i = tamano; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i-1][w]) { // Si es diferente, significa que lo incluimos
            costo_total += p[i-1].costo;
            seleccionados++;
            w -= p[i-1].costo;
        }
    }

    printf("\n=== EQUIPO SELECCIONADO (DP Bottom-Up) ===\n");
    printf("Estrategia Optima Garantizada\n");
    printf("Total Seleccionados: %d\nCosto Total: %d / %d\nPuntaje Total: %.2f\n", seleccionados, costo_total, presupuesto, puntaje_total);

    for (int i = 0; i <= tamano; i++) free(dp[i]);
    free(dp);
}

// Helper recursivo para Top-Down
float recursivo_top_down(piloto p[], int i, int w, float **memo) {
    if (i < 0 || w <= 0) return 0.0f;
    if (memo[i][w] != -1.0f) return memo[i][w]; // Si ya esta calculado, lo retorna

    if (p[i].costo > w) {
        memo[i][w] = recursivo_top_down(p, i - 1, w, memo);
    } else {
        float incluir = p[i].Puntaje + recursivo_top_down(p, i - 1, w - p[i].costo, memo);
        float excluir = recursivo_top_down(p, i - 1, w, memo);
        memo[i][w] = (incluir > excluir) ? incluir : excluir;
    }
    return memo[i][w];
}

// 2. Top-Down
void dp_top_down(piloto p[], int tamano, int presupuesto) {
    float **memo = (float **)malloc(tamano * sizeof(float *));
    if (!memo) return;
    for (int i = 0; i < tamano; i++) {
        memo[i] = (float *)malloc((presupuesto + 1) * sizeof(float));
        if (!memo[i]) { // Proteccion por si se acaba la memoria
            printf("[Error] Memoria insuficiente para DP Top-Down\n");
            for(int j = 0; j < i; j++) free(memo[j]);
            free(memo);
            return;
        }
        for (int w = 0; w <= presupuesto; w++) memo[i][w] = -1.0f; // Inicializa vacio
    }

    float puntaje_total = recursivo_top_down(p, tamano - 1, presupuesto, memo);

    // Reconstruccion de la solucion Top-Down
    int w = presupuesto, costo_total = 0, seleccionados = 0;

    for (int i = tamano - 1; i >= 0 && w > 0; i--) {
        float actual = memo[i][w];
        float anterior = (i > 0) ? recursivo_top_down(p, i - 1, w, memo) : 0.0f;

        // Si el valor actual es distinto al del elemento anterior, significa que p[i] se uso en el equipo
        if (actual != anterior) {
            costo_total += p[i].costo;
            seleccionados++;
            w -= p[i].costo;
        }
    }

    printf("\n=== EQUIPO SELECCIONADO (DP Top-Down) ===\n");
    printf("Estrategia Optima Garantizada\n");
    printf("Total Seleccionados: %d\nCosto Total: %d / %d\nPuntaje Total: %.2f\n", seleccionados, costo_total, presupuesto, puntaje_total);

    for (int i = 0; i < tamano; i++) free(memo[i]);
    free(memo);
}

// ====================== ALGORITMOS GREEDY ======================

int cmp_mayor_puntaje(const void *a, const void *b) {
    piloto *pa = (piloto*)a;
    piloto *pb = (piloto*)b;
    if (pb->Puntaje > pa->Puntaje) return 1;
    if (pb->Puntaje < pa->Puntaje) return -1;
    return 0;
}

int cmp_menor_costo(const void *a, const void *b) {
    piloto *pa = (piloto*)a;
    piloto *pb = (piloto*)b;
    return pa->costo - pb->costo;
}

int cmp_mejor_ratio(const void *a, const void *b) {
    piloto *pa = (piloto*)a;
    piloto *pb = (piloto*)b;
    float ratio_a = pa->Puntaje / (float)pa->costo;
    float ratio_b = pb->Puntaje / (float)pb->costo;
    if (ratio_b > ratio_a) return 1;
    if (ratio_b < ratio_a) return -1;
    return 0;
}

void greedy_con_restriccion(piloto p[], int tamano, int presupuesto, int criterio) {
    piloto *copia = (piloto *)malloc(tamano * sizeof(piloto));
    if (!copia) return;
    for(int i = 0; i < tamano; i++) copia[i] = p[i];

    if (criterio == 1) {
        qsort(copia, tamano, sizeof(piloto), cmp_mayor_puntaje);
        printf("\n--- Greedy por Mayor Puntaje ---\n");
    } else if (criterio == 2) {
        qsort(copia, tamano, sizeof(piloto), cmp_menor_costo);
        printf("\n--- Greedy por Menor Costo ---\n");
    } else if (criterio == 3) {
        qsort(copia, tamano, sizeof(piloto), cmp_mejor_ratio);
        printf("\n--- Greedy por Mejor Ratio (Puntaje/Costo) ---\n");
    }

    int seleccionados = 0;
    int costo_total = 0;
    float puntaje_total = 0.0f;

    for (int i = 0; i < tamano; i++) {
        if (costo_total + copia[i].costo <= presupuesto) {
            costo_total += copia[i].costo;
            puntaje_total += copia[i].Puntaje;
            seleccionados++;
        }
    }

    printf("Total Seleccionados: %d\nCosto Total: %d / %d\nPuntaje Total: %.2f\n", seleccionados, costo_total, presupuesto, puntaje_total);
    free(copia);
}

void greedy_sin_restriccion(piloto p[], int tamano, int cantidad) {
    if (cantidad > tamano) cantidad = tamano;
    
    piloto *copia = (piloto *)malloc(tamano * sizeof(piloto));
    if (!copia) return;
    for(int i = 0; i < tamano; i++) copia[i] = p[i];
    
    qsort(copia, tamano, sizeof(piloto), cmp_mayor_puntaje);
    
    printf("\n--- Greedy Sin Restriccion (Top %d Mejores por Puntaje) ---\n", cantidad);
    
    int costo_total = 0;
    float puntaje_total = 0.0f;
    
    for (int i = 0; i < cantidad; i++) {
        costo_total += copia[i].costo;
        puntaje_total += copia[i].Puntaje;
    }
    
    printf("Total Seleccionados: %d\nCosto Total: %d\nPuntaje Total: %.2f\n", cantidad, costo_total, puntaje_total);
    free(copia);
}