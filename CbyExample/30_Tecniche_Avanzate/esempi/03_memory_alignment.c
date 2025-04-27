/**
 * File: 03_memory_alignment.c
 * Descrizione: Esempio di ottimizzazione della memoria tramite allineamento dei dati
 * 
 * Questo esempio dimostra come l'allineamento dei dati e il padding delle strutture
 * possono influenzare le prestazioni e l'utilizzo della memoria in C.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

// Numero di elementi da elaborare
#define NUM_ELEMENTS 10000000
// Numero di iterazioni per i test
#define NUM_ITERATIONS 100

/**
 * Struttura non ottimizzata con padding automatico del compilatore
 * Il compilatore inserirà automaticamente del padding tra i campi
 * per garantire l'allineamento, ma non in modo ottimale.
 */
typedef struct {
    char a;       // 1 byte
    int b;        // 4 byte (tipicamente allineato a 4 byte)
    char c;       // 1 byte
    double d;     // 8 byte (tipicamente allineato a 8 byte)
    short e;      // 2 byte
} UnalignedStruct;

/**
 * Struttura ottimizzata con campi ordinati per dimensione decrescente
 * Questo riduce il padding automatico inserito dal compilatore.
 */
typedef struct {
    double d;     // 8 byte
    int b;        // 4 byte
    short e;      // 2 byte
    char a;       // 1 byte
    char c;       // 1 byte
    // Nessun padding necessario alla fine
} OptimizedStruct;

/**
 * Struttura con allineamento forzato a 16 byte (utile per SIMD)
 * Questo garantisce che ogni istanza della struttura inizi a un indirizzo
 * multiplo di 16, ottimale per operazioni SIMD.
 */
typedef struct {
    double d;     // 8 byte
    int b;        // 4 byte
    short e;      // 2 byte
    char a;       // 1 byte
    char c;       // 1 byte
    char padding[16 - (8 + 4 + 2 + 1 + 1) % 16]; // Padding esplicito per allineamento a 16 byte
} __attribute__((aligned(16))) AlignedStruct;

/**
 * Funzione che accede ai campi di un array di strutture non ottimizzate
 */
double process_unaligned(UnalignedStruct *array, int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += array[i].a + array[i].b + array[i].c + array[i].d + array[i].e;
    }
    return sum;
}

/**
 * Funzione che accede ai campi di un array di strutture ottimizzate
 */
double process_optimized(OptimizedStruct *array, int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += array[i].a + array[i].b + array[i].c + array[i].d + array[i].e;
    }
    return sum;
}

/**
 * Funzione che accede ai campi di un array di strutture allineate
 */
double process_aligned(AlignedStruct *array, int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += array[i].a + array[i].b + array[i].c + array[i].d + array[i].e;
    }
    return sum;
}

/**
 * Funzione principale che confronta le prestazioni delle diverse strutture
 */
int main() {
    // Stampa le dimensioni delle strutture
    printf("Dimensioni delle strutture:\n");
    printf("UnalignedStruct: %zu byte\n", sizeof(UnalignedStruct));
    printf("OptimizedStruct: %zu byte\n", sizeof(OptimizedStruct));
    printf("AlignedStruct:   %zu byte\n\n", sizeof(AlignedStruct));
    
    // Alloca memoria per gli array di strutture
    UnalignedStruct *unaligned_array = (UnalignedStruct*)malloc(NUM_ELEMENTS * sizeof(UnalignedStruct));
    OptimizedStruct *optimized_array = (OptimizedStruct*)malloc(NUM_ELEMENTS * sizeof(OptimizedStruct));
    // Per le strutture allineate, usiamo aligned_alloc se disponibile
#ifdef _ISOC11_SOURCE
    AlignedStruct *aligned_array = (AlignedStruct*)aligned_alloc(16, NUM_ELEMENTS * sizeof(AlignedStruct));
#else
    // Fallback per sistemi senza aligned_alloc
    AlignedStruct *aligned_array = (AlignedStruct*)malloc(NUM_ELEMENTS * sizeof(AlignedStruct));
#endif
    
    if (!unaligned_array || !optimized_array || !aligned_array) {
        printf("Errore: Impossibile allocare memoria\n");
        return 1;
    }
    
    // Inizializza gli array con gli stessi valori
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        // Valori casuali per i campi
        char a_val = (char)(rand() % 100);
        int b_val = rand();
        char c_val = (char)(rand() % 100);
        double d_val = (double)rand() / RAND_MAX;
        short e_val = (short)(rand() % 1000);
        
        // Assegna i valori alle strutture
        unaligned_array[i].a = a_val;
        unaligned_array[i].b = b_val;
        unaligned_array[i].c = c_val;
        unaligned_array[i].d = d_val;
        unaligned_array[i].e = e_val;
        
        optimized_array[i].a = a_val;
        optimized_array[i].b = b_val;
        optimized_array[i].c = c_val;
        optimized_array[i].d = d_val;
        optimized_array[i].e = e_val;
        
        aligned_array[i].a = a_val;
        aligned_array[i].b = b_val;
        aligned_array[i].c = c_val;
        aligned_array[i].d = d_val;
        aligned_array[i].e = e_val;
    }
    
    // Misura le prestazioni
    clock_t start, end;
    double unaligned_time, optimized_time, aligned_time;
    double result;
    
    // Test strutture non ottimizzate
    start = clock();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        result = process_unaligned(unaligned_array, NUM_ELEMENTS);
    }
    end = clock();
    unaligned_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    // Test strutture ottimizzate
    start = clock();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        result = process_optimized(optimized_array, NUM_ELEMENTS);
    }
    end = clock();
    optimized_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    // Test strutture allineate
    start = clock();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        result = process_aligned(aligned_array, NUM_ELEMENTS);
    }
    end = clock();
    aligned_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    // Stampa i risultati
    printf("Risultati (tempo totale per %d iterazioni su %d elementi):\n", 
           NUM_ITERATIONS, NUM_ELEMENTS);
    printf("Strutture non ottimizzate: %.6f secondi\n", unaligned_time);
    printf("Strutture ottimizzate:     %.6f secondi\n", optimized_time);
    printf("Strutture allineate:       %.6f secondi\n\n", aligned_time);
    
    // Calcola e stampa i miglioramenti percentuali
    double opt_improvement = (unaligned_time - optimized_time) / unaligned_time * 100.0;
    double align_improvement = (unaligned_time - aligned_time) / unaligned_time * 100.0;
    
    printf("Miglioramento con strutture ottimizzate: %.2f%%\n", opt_improvement);
    printf("Miglioramento con strutture allineate:   %.2f%%\n\n", align_improvement);
    
    // Calcola e stampa il risparmio di memoria
    size_t unaligned_total = NUM_ELEMENTS * sizeof(UnalignedStruct);
    size_t optimized_total = NUM_ELEMENTS * sizeof(OptimizedStruct);
    size_t aligned_total = NUM_ELEMENTS * sizeof(AlignedStruct);
    
    printf("Utilizzo totale di memoria:\n");
    printf("Strutture non ottimizzate: %zu byte\n", unaligned_total);
    printf("Strutture ottimizzate:     %zu byte\n", optimized_total);
    printf("Strutture allineate:       %zu byte\n\n", aligned_total);
    
    double mem_saving = (double)(unaligned_total - optimized_total) / unaligned_total * 100.0;
    printf("Risparmio di memoria con strutture ottimizzate: %.2f%%\n\n", mem_saving);
    
    printf("Note sull'allineamento e il padding:\n");
    printf("1. L'allineamento dei dati influisce sull'efficienza di accesso alla memoria\n");
    printf("2. Il riordinamento dei campi può ridurre il padding automatico\n");
    printf("3. L'allineamento esplicito può migliorare le prestazioni per operazioni SIMD\n");
    printf("4. Il compilatore inserisce automaticamente padding per garantire l'allineamento\n");
    printf("5. L'ottimizzazione dell'allineamento comporta un compromesso tra memoria e velocità\n");
    
    // Libera la memoria
    free(unaligned_array);
    free(optimized_array);
    free(aligned_array);
    
    return 0;
}

/**
 * Istruzioni per la compilazione ed esecuzione:
 * 
 * gcc -Wall -O2 03_memory_alignment.c -o 03_memory_alignment
 * ./03_memory_alignment
 * 
 * Per visualizzare il padding inserito dal compilatore:
 * gcc -Wall -O2 -S 03_memory_alignment.c
 * 
 * Per visualizzare la dimensione e l'allineamento delle strutture:
 * gcc -Wall -O2 -E 03_memory_alignment.c | grep -A 20 "typedef struct"
 */