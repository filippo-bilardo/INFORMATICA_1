/**
 * File: 02_simd_optimization.c
 * Descrizione: Esempio di ottimizzazione SIMD (Single Instruction Multiple Data) in C
 * 
 * Questo esempio dimostra come utilizzare le istruzioni SIMD attraverso le intrinsics
 * di x86 (SSE/AVX) per accelerare operazioni vettoriali parallelizzabili.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <immintrin.h> // Per le intrinsics AVX/SSE

#define ARRAY_SIZE 10000
#define NUM_TESTS 5

/**
 * Funzione di utilità per generare un array di float casuali
 */
void generate_random_array(float arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = (float)rand() / RAND_MAX * 100.0f;
    }
}

/**
 * Implementazione standard (scalare) della somma di array
 */
float sum_array_scalar(float arr[], int size) {
    float sum = 0.0f;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

/**
 * Implementazione standard (scalare) della moltiplicazione elemento per elemento di array
 */
void multiply_arrays_scalar(float a[], float b[], float result[], int size) {
    for (int i = 0; i < size; i++) {
        result[i] = a[i] * b[i];
    }
}

#ifdef __AVX__
/**
 * Implementazione SIMD (AVX) della somma di array
 * Utilizza istruzioni AVX per elaborare 8 float alla volta
 */
float sum_array_simd_avx(float arr[], int size) {
    int i;
    __m256 sum_vec = _mm256_setzero_ps(); // Vettore di 8 float inizializzati a 0
    
    // Elabora 8 elementi alla volta
    for (i = 0; i <= size - 8; i += 8) {
        __m256 data_vec = _mm256_loadu_ps(&arr[i]);
        sum_vec = _mm256_add_ps(sum_vec, data_vec);
    }
    
    // Somma orizzontale degli 8 elementi nel vettore
    float sum = 0.0f;
    float temp[8];
    _mm256_storeu_ps(temp, sum_vec);
    for (int j = 0; j < 8; j++) {
        sum += temp[j];
    }
    
    // Gestisci gli elementi rimanenti
    for (; i < size; i++) {
        sum += arr[i];
    }
    
    return sum;
}

/**
 * Implementazione SIMD (AVX) della moltiplicazione elemento per elemento di array
 * Utilizza istruzioni AVX per elaborare 8 float alla volta
 */
void multiply_arrays_simd_avx(float a[], float b[], float result[], int size) {
    int i;
    
    // Elabora 8 elementi alla volta
    for (i = 0; i <= size - 8; i += 8) {
        __m256 a_vec = _mm256_loadu_ps(&a[i]);
        __m256 b_vec = _mm256_loadu_ps(&b[i]);
        __m256 result_vec = _mm256_mul_ps(a_vec, b_vec);
        _mm256_storeu_ps(&result[i], result_vec);
    }
    
    // Gestisci gli elementi rimanenti
    for (; i < size; i++) {
        result[i] = a[i] * b[i];
    }
}
#elif defined(__SSE__)
/**
 * Implementazione SIMD (SSE) della somma di array
 * Utilizza istruzioni SSE per elaborare 4 float alla volta
 */
float sum_array_simd_sse(float arr[], int size) {
    int i;
    __m128 sum_vec = _mm_setzero_ps(); // Vettore di 4 float inizializzati a 0
    
    // Elabora 4 elementi alla volta
    for (i = 0; i <= size - 4; i += 4) {
        __m128 data_vec = _mm_loadu_ps(&arr[i]);
        sum_vec = _mm_add_ps(sum_vec, data_vec);
    }
    
    // Somma orizzontale dei 4 elementi nel vettore
    float sum = 0.0f;
    float temp[4];
    _mm_storeu_ps(temp, sum_vec);
    for (int j = 0; j < 4; j++) {
        sum += temp[j];
    }
    
    // Gestisci gli elementi rimanenti
    for (; i < size; i++) {
        sum += arr[i];
    }
    
    return sum;
}

/**
 * Implementazione SIMD (SSE) della moltiplicazione elemento per elemento di array
 * Utilizza istruzioni SSE per elaborare 4 float alla volta
 */
void multiply_arrays_simd_sse(float a[], float b[], float result[], int size) {
    int i;
    
    // Elabora 4 elementi alla volta
    for (i = 0; i <= size - 4; i += 4) {
        __m128 a_vec = _mm_loadu_ps(&a[i]);
        __m128 b_vec = _mm_loadu_ps(&b[i]);
        __m128 result_vec = _mm_mul_ps(a_vec, b_vec);
        _mm_storeu_ps(&result[i], result_vec);
    }
    
    // Gestisci gli elementi rimanenti
    for (; i < size; i++) {
        result[i] = a[i] * b[i];
    }
}
#endif

/**
 * Funzione principale che confronta le prestazioni delle implementazioni
 */
int main() {
    // Inizializza il generatore di numeri casuali
    srand(time(NULL));
    
    // Alloca e inizializza gli array
    float *array_a = (float*)malloc(ARRAY_SIZE * sizeof(float));
    float *array_b = (float*)malloc(ARRAY_SIZE * sizeof(float));
    float *result_scalar = (float*)malloc(ARRAY_SIZE * sizeof(float));
    float *result_simd = (float*)malloc(ARRAY_SIZE * sizeof(float));
    
    if (!array_a || !array_b || !result_scalar || !result_simd) {
        printf("Errore: Impossibile allocare memoria\n");
        return 1;
    }
    
    generate_random_array(array_a, ARRAY_SIZE);
    generate_random_array(array_b, ARRAY_SIZE);
    
    // Array per memorizzare i tempi di esecuzione
    double scalar_sum_times[NUM_TESTS];
    double simd_sum_times[NUM_TESTS];
    double scalar_mul_times[NUM_TESTS];
    double simd_mul_times[NUM_TESTS];
    
    printf("Confronto delle prestazioni tra implementazioni scalari e SIMD\n");
    printf("Dimensione dell'array: %d elementi\n\n", ARRAY_SIZE);
    
    // Esegui più test per ottenere risultati più affidabili
    for (int test = 0; test < NUM_TESTS; test++) {
        printf("Test %d di %d...\n", test + 1, NUM_TESTS);
        
        // Test somma scalare
        clock_t start = clock();
        float sum_scalar = sum_array_scalar(array_a, ARRAY_SIZE);
        clock_t end = clock();
        scalar_sum_times[test] = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        // Test somma SIMD
        start = clock();
#ifdef __AVX__
        float sum_simd = sum_array_simd_avx(array_a, ARRAY_SIZE);
#elif defined(__SSE__)
        float sum_simd = sum_array_simd_sse(array_a, ARRAY_SIZE);
#else
        float sum_simd = sum_array_scalar(array_a, ARRAY_SIZE); // Fallback
#endif
        end = clock();
        simd_sum_times[test] = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        // Verifica che i risultati siano simili (considerando errori di arrotondamento)
        if (fabs(sum_scalar - sum_simd) > 0.1f) {
            printf("Avviso: Risultati diversi tra implementazioni scalare e SIMD\n");
            printf("  Scalare: %f, SIMD: %f\n", sum_scalar, sum_simd);
        }
        
        // Test moltiplicazione scalare
        start = clock();
        multiply_arrays_scalar(array_a, array_b, result_scalar, ARRAY_SIZE);
        end = clock();
        scalar_mul_times[test] = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        // Test moltiplicazione SIMD
        start = clock();
#ifdef __AVX__
        multiply_arrays_simd_avx(array_a, array_b, result_simd, ARRAY_SIZE);
#elif defined(__SSE__)
        multiply_arrays_simd_sse(array_a, array_b, result_simd, ARRAY_SIZE);
#else
        multiply_arrays_scalar(array_a, array_b, result_simd, ARRAY_SIZE); // Fallback
#endif
        end = clock();
        simd_mul_times[test] = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        // Verifica che i risultati siano simili
        for (int i = 0; i < ARRAY_SIZE; i++) {
            if (fabs(result_scalar[i] - result_simd[i]) > 0.001f) {
                printf("Avviso: Risultati diversi all'indice %d\n", i);
                printf("  Scalare: %f, SIMD: %f\n", result_scalar[i], result_simd[i]);
                break;
            }
        }
    }
    
    // Calcola e stampa i tempi medi
    double scalar_sum_avg = 0, simd_sum_avg = 0;
    double scalar_mul_avg = 0, simd_mul_avg = 0;
    
    for (int i = 0; i < NUM_TESTS; i++) {
        scalar_sum_avg += scalar_sum_times[i];
        simd_sum_avg += simd_sum_times[i];
        scalar_mul_avg += scalar_mul_times[i];
        simd_mul_avg += simd_mul_times[i];
    }
    
    scalar_sum_avg /= NUM_TESTS;
    simd_sum_avg /= NUM_TESTS;
    scalar_mul_avg /= NUM_TESTS;
    simd_mul_avg /= NUM_TESTS;
    
    printf("\nRisultati (tempo medio su %d test):\n", NUM_TESTS);
    printf("Somma di array (scalare):    %.6f secondi\n", scalar_sum_avg);
#if defined(__AVX__) || defined(__SSE__)
    printf("Somma di array (SIMD):       %.6f secondi\n", simd_sum_avg);
    printf("Speedup (somma):             %.2fx\n", scalar_sum_avg / simd_sum_avg);
#else
    printf("Somma di array (SIMD):       Non supportata su questa piattaforma\n");
#endif
    
    printf("\nMoltiplicazione array (scalare): %.6f secondi\n", scalar_mul_avg);
#if defined(__AVX__) || defined(__SSE__)
    printf("Moltiplicazione array (SIMD):  %.6f secondi\n", simd_mul_avg);
    printf("Speedup (moltiplicazione):     %.2fx\n", scalar_mul_avg / simd_mul_avg);
#else
    printf("Moltiplicazione array (SIMD):  Non supportata su questa piattaforma\n");
#endif
    
    printf("\nAnalisi delle prestazioni:\n");
    printf("- Le istruzioni SIMD permettono di eseguire la stessa operazione su più dati contemporaneamente\n");
    printf("- AVX può elaborare 8 float alla volta, SSE può elaborare 4 float alla volta\n");
    printf("- L'accelerazione dipende dal tipo di operazione e dal pattern di accesso alla memoria\n");
    printf("- Le operazioni vettoriali come somma e moltiplicazione beneficiano molto del SIMD\n");
    printf("- Il codice SIMD è meno portabile e richiede supporto hardware specifico\n");
    
    // Libera la memoria
    free(array_a);
    free(array_b);
    free(result_scalar);
    free(result_simd);
    
    return 0;
}

/**
 * Istruzioni per la compilazione ed esecuzione:
 * 
 * Per compilare con supporto AVX (processori più recenti):
 * gcc -Wall -O2 -mavx 02_simd_optimization.c -o 02_simd_optimization
 * 
 * Per compilare con supporto SSE (processori meno recenti):
 * gcc -Wall -O2 -msse4.2 02_simd_optimization.c -o 02_simd_optimization
 * 
 * Per compilare senza estensioni SIMD (fallback scalare):
 * gcc -Wall -O2 02_simd_optimization.c -o 02_simd_optimization
 * 
 * Esecuzione:
 * ./02_simd_optimization
 */