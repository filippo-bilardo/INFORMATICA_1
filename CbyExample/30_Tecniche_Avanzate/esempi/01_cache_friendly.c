/**
 * File: 01_cache_friendly.c
 * Descrizione: Esempio di programmazione cache-friendly in C
 * 
 * Questo esempio dimostra come l'accesso sequenziale alla memoria può migliorare
 * significativamente le prestazioni rispetto all'accesso casuale, grazie a un
 * migliore utilizzo della cache della CPU.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000
#define ITERATIONS 1000

/**
 * Funzione che accede alla matrice per righe (cache-friendly)
 * Questo approccio sfrutta la località spaziale della cache
 */
double access_by_rows(int matrix[SIZE][SIZE]) {
    double sum = 0.0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            sum += matrix[i][j];
        }
    }
    return sum;
}

/**
 * Funzione che accede alla matrice per colonne (non cache-friendly)
 * Questo approccio causa molti cache miss
 */
double access_by_columns(int matrix[SIZE][SIZE]) {
    double sum = 0.0;
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE; i++) {
            sum += matrix[i][j];
        }
    }
    return sum;
}

/**
 * Funzione principale che confronta i tempi di esecuzione
 * delle due diverse strategie di accesso alla memoria
 */
int main() {
    // Nota: per semplicità, utilizziamo una matrice più piccola
    // rispetto a quella dichiarata. In un caso reale, si userebbe
    // allocazione dinamica per matrici così grandi.
    int matrix[100][100];
    clock_t start, end;
    double cpu_time_used;
    
    // Inizializzazione della matrice con valori casuali
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
    
    // Test accesso per righe (cache-friendly)
    start = clock();
    for (int k = 0; k < ITERATIONS; k++) {
        double sum = 0.0;
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                sum += matrix[i][j];
            }
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tempo di accesso per righe: %f secondi\n", cpu_time_used);
    
    // Test accesso per colonne (non cache-friendly)
    start = clock();
    for (int k = 0; k < ITERATIONS; k++) {
        double sum = 0.0;
        for (int j = 0; j < 100; j++) {
            for (int i = 0; i < 100; i++) {
                sum += matrix[i][j];
            }
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tempo di accesso per colonne: %f secondi\n", cpu_time_used);
    
    printf("\nNota: L'accesso per righe è generalmente più veloce perché\n");
    printf("sfrutta la località spaziale della cache. Gli elementi di una riga\n");
    printf("sono memorizzati in posizioni contigue in memoria, quindi quando\n");
    printf("un elemento viene caricato nella cache, anche gli elementi vicini\n");
    printf("vengono caricati, riducendo i cache miss nelle iterazioni successive.\n");
    
    return 0;
}

/**
 * Istruzioni per la compilazione ed esecuzione:
 * 
 * gcc -O2 01_cache_friendly.c -o 01_cache_friendly
 * ./01_cache_friendly
 * 
 * Nota: L'opzione -O2 abilita le ottimizzazioni del compilatore.
 * Provate anche senza ottimizzazioni per vedere la differenza:
 * 
 * gcc 01_cache_friendly.c -o 01_cache_friendly_no_opt
 * ./01_cache_friendly_no_opt
 */