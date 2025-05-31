/**
 * File: 01_algoritmi_ottimizzati.c
 * Descrizione: Esempio di ottimizzazione a livello di algoritmo in C
 * 
 * Questo esempio confronta diverse implementazioni di algoritmi di ordinamento
 * per dimostrare come la scelta dell'algoritmo può avere un impatto significativo
 * sulle prestazioni, indipendentemente dalle ottimizzazioni a basso livello.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ARRAY_SIZE 10000
#define NUM_TESTS 5

/**
 * Funzione di utilità per generare un array di interi casuali
 */
void generate_random_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % (size * 10);
    }
}

/**
 * Funzione di utilità per verificare se un array è ordinato
 */
int is_sorted(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i-1]) {
            return 0; // Non ordinato
        }
    }
    return 1; // Ordinato
}

/**
 * Implementazione dell'algoritmo Bubble Sort
 * Complessità temporale: O(n²) in tutti i casi
 */
void bubble_sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                // Scambio degli elementi
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

/**
 * Implementazione dell'algoritmo Insertion Sort
 * Complessità temporale: O(n²) nel caso peggiore, ma efficiente per array quasi ordinati
 */
void insertion_sort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Sposta gli elementi maggiori di key una posizione avanti
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

/**
 * Funzione di partizione per Quick Sort
 */
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Scelta del pivot (ultimo elemento)
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            // Scambio degli elementi
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    // Posiziona il pivot nella sua posizione finale
    int temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;
    
    return i + 1;
}

/**
 * Implementazione dell'algoritmo Quick Sort
 * Complessità temporale: O(n log n) nel caso medio, O(n²) nel caso peggiore
 */
void quick_sort_recursive(int arr[], int low, int high) {
    if (low < high) {
        // Trova l'indice di partizione
        int pi = partition(arr, low, high);
        
        // Ordina ricorsivamente gli elementi prima e dopo la partizione
        quick_sort_recursive(arr, low, pi - 1);
        quick_sort_recursive(arr, pi + 1, high);
    }
}

void quick_sort(int arr[], int size) {
    quick_sort_recursive(arr, 0, size - 1);
}

/**
 * Funzione di fusione per Merge Sort
 */
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Crea array temporanei
    int L[n1], R[n2];
    
    // Copia i dati negli array temporanei
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // Fondi gli array temporanei nell'array originale
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copia gli elementi rimanenti di L[], se presenti
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copia gli elementi rimanenti di R[], se presenti
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/**
 * Implementazione dell'algoritmo Merge Sort
 * Complessità temporale: O(n log n) in tutti i casi
 */
void merge_sort_recursive(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // Ordina la prima e la seconda metà
        merge_sort_recursive(arr, left, mid);
        merge_sort_recursive(arr, mid + 1, right);
        
        // Fondi le metà ordinate
        merge(arr, left, mid, right);
    }
}

void merge_sort(int arr[], int size) {
    merge_sort_recursive(arr, 0, size - 1);
}

/**
 * Funzione principale che confronta le prestazioni degli algoritmi
 */
int main() {
    // Inizializza il generatore di numeri casuali
    srand(time(NULL));
    
    // Array per memorizzare i tempi di esecuzione
    double bubble_times[NUM_TESTS];
    double insertion_times[NUM_TESTS];
    double quick_times[NUM_TESTS];
    double merge_times[NUM_TESTS];
    
    printf("Confronto delle prestazioni degli algoritmi di ordinamento\n");
    printf("Dimensione dell'array: %d elementi\n\n", ARRAY_SIZE);
    
    // Esegui più test per ottenere risultati più affidabili
    for (int test = 0; test < NUM_TESTS; test++) {
        printf("Test %d di %d...\n", test + 1, NUM_TESTS);
        
        // Crea array di test
        int *original_array = (int*)malloc(ARRAY_SIZE * sizeof(int));
        int *test_array = (int*)malloc(ARRAY_SIZE * sizeof(int));
        
        if (!original_array || !test_array) {
            printf("Errore: Impossibile allocare memoria\n");
            return 1;
        }
        
        // Genera array casuale
        generate_random_array(original_array, ARRAY_SIZE);
        
        // Test Bubble Sort
        memcpy(test_array, original_array, ARRAY_SIZE * sizeof(int));
        clock_t start = clock();
        bubble_sort(test_array, ARRAY_SIZE);
        clock_t end = clock();
        bubble_times[test] = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        if (!is_sorted(test_array, ARRAY_SIZE)) {
            printf("Errore: Bubble Sort non ha ordinato correttamente l'array\n");
        }
        
        // Test Insertion Sort
        memcpy(test_array, original_array, ARRAY_SIZE * sizeof(int));
        start = clock();
        insertion_sort(test_array, ARRAY_SIZE);
        end = clock();
        insertion_times[test] = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        if (!is_sorted(test_array, ARRAY_SIZE)) {
            printf("Errore: Insertion Sort non ha ordinato correttamente l'array\n");
        }
        
        // Test Quick Sort
        memcpy(test_array, original_array, ARRAY_SIZE * sizeof(int));
        start = clock();
        quick_sort(test_array, ARRAY_SIZE);
        end = clock();
        quick_times[test] = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        if (!is_sorted(test_array, ARRAY_SIZE)) {
            printf("Errore: Quick Sort non ha ordinato correttamente l'array\n");
        }
        
        // Test Merge Sort
        memcpy(test_array, original_array, ARRAY_SIZE * sizeof(int));
        start = clock();
        merge_sort(test_array, ARRAY_SIZE);
        end = clock();
        merge_times[test] = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        if (!is_sorted(test_array, ARRAY_SIZE)) {
            printf("Errore: Merge Sort non ha ordinato correttamente l'array\n");
        }
        
        // Libera la memoria
        free(original_array);
        free(test_array);
    }
    
    // Calcola e stampa i tempi medi
    double bubble_avg = 0, insertion_avg = 0, quick_avg = 0, merge_avg = 0;
    
    for (int i = 0; i < NUM_TESTS; i++) {
        bubble_avg += bubble_times[i];
        insertion_avg += insertion_times[i];
        quick_avg += quick_times[i];
        merge_avg += merge_times[i];
    }
    
    bubble_avg /= NUM_TESTS;
    insertion_avg /= NUM_TESTS;
    quick_avg /= NUM_TESTS;
    merge_avg /= NUM_TESTS;
    
    printf("\nRisultati (tempo medio su %d test):\n", NUM_TESTS);
    printf("Bubble Sort:    %.6f secondi\n", bubble_avg);
    printf("Insertion Sort: %.6f secondi\n", insertion_avg);
    printf("Quick Sort:     %.6f secondi\n", quick_avg);
    printf("Merge Sort:     %.6f secondi\n", merge_avg);
    
    printf("\nAnalisi delle prestazioni:\n");
    printf("- Bubble Sort è l'algoritmo più semplice ma meno efficiente (O(n²))\n");
    printf("- Insertion Sort è efficiente per array piccoli o quasi ordinati\n");
    printf("- Quick Sort è generalmente il più veloce nella pratica (O(n log n) in media)\n");
    printf("- Merge Sort garantisce prestazioni O(n log n) in tutti i casi ma richiede memoria aggiuntiva\n");
    
    return 0;
}

/**
 * Istruzioni per la compilazione ed esecuzione:
 * 
 * gcc -Wall -O2 01_algoritmi_ottimizzati.c -o 01_algoritmi_ottimizzati
 * ./01_algoritmi_ottimizzati
 * 
 * Nota: L'opzione -O2 abilita le ottimizzazioni del compilatore.
 * Provate anche senza ottimizzazioni per vedere la differenza:
 * 
 * gcc -Wall -O0 01_algoritmi_ottimizzati.c -o 01_algoritmi_ottimizzati_no_opt
 * ./01_algoritmi_ottimizzati_no_opt
 */