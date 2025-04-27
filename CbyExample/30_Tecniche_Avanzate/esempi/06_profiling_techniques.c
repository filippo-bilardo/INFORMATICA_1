/**
 * File: 06_profiling_techniques.c
 * Descrizione: Esempio di tecniche di profiling in C
 * 
 * Questo esempio dimostra diverse tecniche per profilare il codice C,
 * misurare le prestazioni e identificare i colli di bottiglia.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Definizione delle dimensioni per i test
#define ARRAY_SIZE 50000000
#define NUM_ITERATIONS 5

// Struttura per memorizzare i risultati del profiling
typedef struct {
    const char* nome_funzione;
    double tempo_esecuzione;
    long long operazioni;
    double operazioni_al_secondo;
} ProfilingResult;

/**
 * Funzione inefficiente per ordinare un array (bubble sort)
 */
void bubble_sort(int* array, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                // Scambio degli elementi
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

/**
 * Funzione più efficiente per ordinare un array (quick sort)
 */
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void quick_sort(int* array, int size) {
    qsort(array, size, sizeof(int), compare);
}

/**
 * Funzione inefficiente per la ricerca di un elemento
 */
int ricerca_lineare(int* array, int size, int target) {
    for (int i = 0; i < size; i++) {
        if (array[i] == target) {
            return i;
        }
    }
    return -1;
}

/**
 * Funzione più efficiente per la ricerca di un elemento
 */
int ricerca_binaria(int* array, int size, int target) {
    int left = 0;
    int right = size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (array[mid] == target) {
            return mid;
        }
        
        if (array[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

/**
 * Funzione per profilare l'esecuzione di una funzione
 */
ProfilingResult profila_funzione(const char* nome, void (*func)(int*, int), int* array, int size) {
    ProfilingResult result;
    result.nome_funzione = nome;
    
    // Crea una copia dell'array per non modificare l'originale
    int* array_copia = (int*)malloc(size * sizeof(int));
    if (!array_copia) {
        fprintf(stderr, "Errore: Impossibile allocare memoria\n");
        exit(1);
    }
    
    // Misura il tempo di esecuzione
    clock_t inizio, fine;
    double tempo_totale = 0.0;
    
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        // Copia l'array originale
        memcpy(array_copia, array, size * sizeof(int));
        
        // Misura il tempo di esecuzione
        inizio = clock();
        func(array_copia, size);
        fine = clock();
        
        tempo_totale += ((double)(fine - inizio)) / CLOCKS_PER_SEC;
    }
    
    // Calcola il tempo medio
    result.tempo_esecuzione = tempo_totale / NUM_ITERATIONS;
    
    // Stima del numero di operazioni (per bubble sort: circa n²/2, per quick sort: circa n log n)
    if (strcmp(nome, "Bubble Sort") == 0) {
        result.operazioni = (long long)size * (long long)size / 2;
    } else if (strcmp(nome, "Quick Sort") == 0) {
        // Approssimazione di n log n
        double n_log_n = (double)size * log2((double)size);
        result.operazioni = (long long)n_log_n;
    } else {
        result.operazioni = size; // Default per altre funzioni
    }
    
    // Calcola operazioni al secondo
    result.operazioni_al_secondo = result.operazioni / result.tempo_esecuzione;
    
    // Libera la memoria
    free(array_copia);
    
    return result;
}

/**
 * Funzione per profilare la ricerca
 */
ProfilingResult profila_ricerca(const char* nome, int (*func)(int*, int, int), int* array, int size, int target) {
    ProfilingResult result;
    result.nome_funzione = nome;
    
    // Misura il tempo di esecuzione
    clock_t inizio, fine;
    double tempo_totale = 0.0;
    int indice;
    
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        inizio = clock();
        indice = func(array, size, target);
        fine = clock();
        
        tempo_totale += ((double)(fine - inizio)) / CLOCKS_PER_SEC;
    }
    
    // Calcola il tempo medio
    result.tempo_esecuzione = tempo_totale / NUM_ITERATIONS;
    
    // Stima del numero di operazioni (per ricerca lineare: circa n/2 in media, per ricerca binaria: circa log n)
    if (strcmp(nome, "Ricerca Lineare") == 0) {
        result.operazioni = size / 2; // Media caso
    } else if (strcmp(nome, "Ricerca Binaria") == 0) {
        // Approssimazione di log n
        result.operazioni = (long long)log2((double)size);
    } else {
        result.operazioni = size; // Default per altre funzioni
    }
    
    // Calcola operazioni al secondo
    result.operazioni_al_secondo = result.operazioni / result.tempo_esecuzione;
    
    return result;
}

/**
 * Funzione per stampare i risultati del profiling
 */
void stampa_risultati(ProfilingResult* results, int count) {
    printf("\n%-20s %-20s %-20s %-20s\n", "Funzione", "Tempo (sec)", "Operazioni", "Op/sec");
    printf("------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-20s %-20.6f %-20lld %.2e\n", 
               results[i].nome_funzione, 
               results[i].tempo_esecuzione,
               results[i].operazioni,
               results[i].operazioni_al_secondo);
    }
    printf("------------------------------------------------------------------------------------------\n");
}

/**
 * Funzione principale
 */
int main() {
    // Alloca memoria per gli array
    int* array_grande = (int*)malloc(ARRAY_SIZE * sizeof(int));
    int* array_piccolo = (int*)malloc(10000 * sizeof(int));
    
    if (!array_grande || !array_piccolo) {
        fprintf(stderr, "Errore: Impossibile allocare memoria\n");
        return 1;
    }
    
    // Inizializza gli array con valori casuali
    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (i < 10000) {
            array_piccolo[i] = rand() % 10000;
        }
        array_grande[i] = rand() % ARRAY_SIZE;
    }
    
    printf("=== PROFILING DI ALGORITMI DI ORDINAMENTO ===\n");
    printf("Dimensione array: %d elementi\n", 10000);
    printf("Numero di iterazioni: %d\n", NUM_ITERATIONS);
    
    // Profila gli algoritmi di ordinamento su array piccolo
    ProfilingResult sort_results[2];
    sort_results[0] = profila_funzione("Bubble Sort", bubble_sort, array_piccolo, 10000);
    sort_results[1] = profila_funzione("Quick Sort", quick_sort, array_piccolo, 10000);
    
    // Stampa i risultati
    stampa_risultati(sort_results, 2);
    
    // Ordina l'array grande con quick sort per il test di ricerca
    quick_sort(array_grande, ARRAY_SIZE);
    
    printf("\n=== PROFILING DI ALGORITMI DI RICERCA ===\n");
    printf("Dimensione array: %d elementi\n", ARRAY_SIZE);
    printf("Numero di iterazioni: %d\n", NUM_ITERATIONS);
    
    // Elemento da cercare (presente nell'array)
    int target = array_grande[ARRAY_SIZE / 2];
    
    // Profila gli algoritmi di ricerca
    ProfilingResult search_results[2];
    search_results[0] = profila_ricerca("Ricerca Lineare", ricerca_lineare, array_grande, ARRAY_SIZE, target);
    search_results[1] = profila_ricerca("Ricerca Binaria", ricerca_binaria, array_grande, ARRAY_SIZE, target);
    
    // Stampa i risultati
    stampa_risultati(search_results, 2);
    
    // Calcola e stampa il miglioramento percentuale
    double miglioramento_sort = (sort_results[0].tempo_esecuzione - sort_results[1].tempo_esecuzione) / 
                               sort_results[0].tempo_esecuzione * 100.0;
    
    double miglioramento_search = (search_results[0].tempo_esecuzione - search_results[1].tempo_esecuzione) / 
                                 search_results[0].tempo_esecuzione * 100.0;
    
    printf("\nMiglioramento percentuale:\n");
    printf("Quick Sort vs Bubble Sort: %.2f%%\n", miglioramento_sort);
    printf("Ricerca Binaria vs Ricerca Lineare: %.2f%%\n", miglioramento_search);
    
    printf("\nNote sul profiling:\n");
    printf("1. Il profiling è essenziale per identificare i colli di bottiglia nel codice\n");
    printf("2. La complessità algoritmica influisce drasticamente sulle prestazioni\n");
    printf("3. Per array grandi, la differenza di prestazioni diventa ancora più significativa\n");
    printf("4. Strumenti esterni come Valgrind, gprof o perf offrono analisi più dettagliate\n");
    printf("5. L'ottimizzazione prematura è la radice di tutti i mali (Donald Knuth)\n");
    
    // Libera la memoria
    free(array_grande);
    free(array_piccolo);
    
    return 0;
}

/**
 * Istruzioni per la compilazione ed esecuzione:
 * 
 * gcc -Wall -O2 06_profiling_techniques.c -o 06_profiling_techniques -lm
 * ./06_profiling_techniques
 * 
 * Per un profiling più dettagliato con gprof:
 * gcc -Wall -pg 06_profiling_techniques.c -o 06_profiling_techniques -lm
 * ./06_profiling_techniques
 * gprof 06_profiling_techniques gmon.out > analysis.txt
 * 
 * Per un'analisi con Valgrind/Callgrind:
 * valgrind --tool=callgrind ./06_profiling_techniques
 * callgrind_annotate callgrind.out.XXXX
 */