/**
 * File: 07_compiler_optimization.c
 * Descrizione: Esempio di ottimizzazioni a livello di compilatore in C
 * 
 * Questo esempio dimostra come le diverse opzioni di ottimizzazione del compilatore
 * possono influenzare le prestazioni del codice e quali tecniche possiamo utilizzare
 * per aiutare il compilatore a generare codice più efficiente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Dimensione degli array per i test
#define ARRAY_SIZE 50000000
#define NUM_ITERATIONS 10

/**
 * Funzione che può beneficiare dell'ottimizzazione di loop unrolling
 * Il compilatore potrebbe trasformare questo ciclo per elaborare
 * più elementi contemporaneamente.
 */
void somma_array(const int* array, int size, long long* result) {
    long long sum = 0;
    
    // Ciclo che il compilatore potrebbe ottimizzare con loop unrolling
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    
    *result = sum;
}

/**
 * Versione manuale di loop unrolling
 * Elaboriamo 4 elementi per iterazione per ridurre l'overhead del ciclo
 */
void somma_array_unrolled(const int* array, int size, long long* result) {
    long long sum = 0;
    int i = 0;
    
    // Elabora 4 elementi per iterazione
    for (; i < size - 3; i += 4) {
        sum += array[i] + array[i+1] + array[i+2] + array[i+3];
    }
    
    // Elabora gli elementi rimanenti
    for (; i < size; i++) {
        sum += array[i];
    }
    
    *result = sum;
}

/**
 * Funzione che può beneficiare dell'ottimizzazione di function inlining
 * Il compilatore potrebbe inserire il codice di questa funzione
 * direttamente nel punto di chiamata.
 */
inline int quadrato(int x) {
    return x * x;
}

/**
 * Funzione che utilizza la funzione quadrato
 */
void calcola_quadrati(const int* input, int* output, int size) {
    for (int i = 0; i < size; i++) {
        output[i] = quadrato(input[i]);
    }
}

/**
 * Funzione che può beneficiare dell'ottimizzazione di constant folding
 * Il compilatore potrebbe calcolare questa espressione durante la compilazione
 */
double calcola_costante() {
    return 3.14159265358979323846 * 2.0 * 10.0;
}

/**
 * Funzione che dimostra l'uso di restrict per aiutare il compilatore
 * Il qualificatore restrict indica che i puntatori non si sovrappongono
 */
void copia_array(const int* restrict src, int* restrict dst, int size) {
    for (int i = 0; i < size; i++) {
        dst[i] = src[i];
    }
}

/**
 * Funzione che può beneficiare dell'ottimizzazione SIMD automatica
 * Il compilatore potrebbe utilizzare istruzioni vettoriali per questa operazione
 */
void moltiplica_array(const int* a, const int* b, int* result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = a[i] * b[i];
    }
}

/**
 * Funzione per misurare il tempo di esecuzione
 */
double misura_tempo(void (*func)(), void* args) {
    clock_t inizio, fine;
    double tempo_totale = 0.0;
    
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        inizio = clock();
        func(args);
        fine = clock();
        
        tempo_totale += ((double)(fine - inizio)) / CLOCKS_PER_SEC;
    }
    
    return tempo_totale / NUM_ITERATIONS;
}

// Struttura per passare argomenti alle funzioni di test
typedef struct {
    int* array1;
    int* array2;
    int* array_output;
    int size;
    long long result;
} TestArgs;

// Wrapper per le funzioni di test
void test_somma_array(void* args) {
    TestArgs* test_args = (TestArgs*)args;
    somma_array(test_args->array1, test_args->size, &test_args->result);
}

void test_somma_array_unrolled(void* args) {
    TestArgs* test_args = (TestArgs*)args;
    somma_array_unrolled(test_args->array1, test_args->size, &test_args->result);
}

void test_calcola_quadrati(void* args) {
    TestArgs* test_args = (TestArgs*)args;
    calcola_quadrati(test_args->array1, test_args->array_output, test_args->size);
}

void test_copia_array(void* args) {
    TestArgs* test_args = (TestArgs*)args;
    copia_array(test_args->array1, test_args->array_output, test_args->size);
}

void test_moltiplica_array(void* args) {
    TestArgs* test_args = (TestArgs*)args;
    moltiplica_array(test_args->array1, test_args->array2, test_args->array_output, test_args->size);
}

/**
 * Funzione principale
 */
int main() {
    // Alloca memoria per gli array
    int* array1 = (int*)malloc(ARRAY_SIZE * sizeof(int));
    int* array2 = (int*)malloc(ARRAY_SIZE * sizeof(int));
    int* array_output = (int*)malloc(ARRAY_SIZE * sizeof(int));
    
    if (!array1 || !array2 || !array_output) {
        fprintf(stderr, "Errore: Impossibile allocare memoria\n");
        return 1;
    }
    
    // Inizializza gli array con valori casuali
    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array1[i] = rand() % 100;
        array2[i] = rand() % 100;
    }
    
    // Prepara gli argomenti per i test
    TestArgs args;
    args.array1 = array1;
    args.array2 = array2;
    args.array_output = array_output;
    args.size = ARRAY_SIZE;
    
    // Esegui i test e misura i tempi
    printf("=== EFFETTI DELLE OTTIMIZZAZIONI DEL COMPILATORE ===\n");
    printf("Dimensione array: %d elementi\n", ARRAY_SIZE);
    printf("Numero di iterazioni: %d\n\n", NUM_ITERATIONS);
    
    printf("Test di somma array:\n");
    double tempo_somma = misura_tempo(test_somma_array, &args);
    printf("Somma standard: %.6f secondi, Risultato: %lld\n", tempo_somma, args.result);
    
    double tempo_somma_unrolled = misura_tempo(test_somma_array_unrolled, &args);
    printf("Somma con loop unrolling manuale: %.6f secondi, Risultato: %lld\n", tempo_somma_unrolled, args.result);
    
    double miglioramento = (tempo_somma - tempo_somma_unrolled) / tempo_somma * 100.0;
    printf("Miglioramento: %.2f%%\n\n", miglioramento);
    
    printf("Test di calcolo quadrati:\n");
    double tempo_quadrati = misura_tempo(test_calcola_quadrati, &args);
    printf("Tempo: %.6f secondi\n\n", tempo_quadrati);
    
    printf("Test di copia array:\n");
    double tempo_copia = misura_tempo(test_copia_array, &args);
    printf("Tempo: %.6f secondi\n\n", tempo_copia);
    
    printf("Test di moltiplicazione array:\n");
    double tempo_moltiplicazione = misura_tempo(test_moltiplica_array, &args);
    printf("Tempo: %.6f secondi\n\n", tempo_moltiplicazione);
    
    // Calcola e stampa il valore costante
    double costante = calcola_costante();
    printf("Valore costante calcolato: %.10f\n\n", costante);
    
    printf("Note sulle ottimizzazioni del compilatore:\n");
    printf("1. Loop unrolling: riduce l'overhead del ciclo elaborando più elementi per iterazione\n");
    printf("2. Function inlining: sostituisce la chiamata di funzione con il corpo della funzione\n");
    printf("3. Constant folding: calcola espressioni costanti durante la compilazione\n");
    printf("4. Ottimizzazioni SIMD: utilizza istruzioni vettoriali per elaborare più dati contemporaneamente\n");
    printf("5. Qualificatore restrict: aiuta il compilatore a ottimizzare l'accesso ai puntatori\n\n");
    
    printf("Livelli di ottimizzazione del compilatore GCC:\n");
    printf("-O0: Nessuna ottimizzazione (default)\n");
    printf("-O1: Ottimizzazioni di base che non richiedono compromessi spazio-tempo\n");
    printf("-O2: Ottimizzazioni più aggressive senza significativo aumento della dimensione del codice\n");
    printf("-O3: Ottimizzazioni ancora più aggressive, incluse vectorization e inlining\n");
    printf("-Os: Ottimizzazioni per ridurre la dimensione del codice\n");
    printf("-Ofast: Ottimizzazioni che possono violare gli standard IEEE per prestazioni massime\n");
    
    // Libera la memoria
    free(array1);
    free(array2);
    free(array_output);
    
    return 0;
}

/**
 * Istruzioni per la compilazione ed esecuzione con diversi livelli di ottimizzazione:
 * 
 * Senza ottimizzazioni:
 * gcc -Wall -O0 07_compiler_optimization.c -o 07_compiler_optimization_O0
 * ./07_compiler_optimization_O0
 * 
 * Con ottimizzazioni di base:
 * gcc -Wall -O1 07_compiler_optimization.c -o 07_compiler_optimization_O1
 * ./07_compiler_optimization_O1
 * 
 * Con ottimizzazioni aggressive:
 * gcc -Wall -O2 07_compiler_optimization.c -o 07_compiler_optimization_O2
 * ./07_compiler_optimization_O2
 * 
 * Con ottimizzazioni massime:
 * gcc -Wall -O3 07_compiler_optimization.c -o 07_compiler_optimization_O3
 * ./07_compiler_optimization_O3
 * 
 * Con ottimizzazioni per dimensione:
 * gcc -Wall -Os 07_compiler_optimization.c -o 07_compiler_optimization_Os
 * ./07_compiler_optimization_Os
 * 
 * Con ottimizzazioni massime (potenzialmente non standard):
 * gcc -Wall -Ofast 07_compiler_optimization.c -o 07_compiler_optimization_Ofast
 * ./07_compiler_optimization_Ofast
 * 
 * Per vedere il codice assembly generato:
 * gcc -Wall -O3 -S 07_compiler_optimization.c
 */