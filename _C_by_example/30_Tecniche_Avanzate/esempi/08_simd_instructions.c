/**
 * File: 08_simd_instructions.c
 * Descrizione: Esempio di ottimizzazione con istruzioni SIMD (Single Instruction Multiple Data)
 * 
 * Questo esempio dimostra come utilizzare le istruzioni SIMD (tramite intrinsics) per
 * accelerare le operazioni vettoriali rispetto al codice scalare tradizionale.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>

// Verifica se le estensioni SSE sono disponibili
#if defined(__SSE__) || defined(_M_IX86) || defined(_M_X64)
#include <emmintrin.h>  // SSE2
#include <pmmintrin.h>  // SSE3
#define HAVE_SSE 1
#else
#define HAVE_SSE 0
#endif

// Verifica se le estensioni AVX sono disponibili
#if defined(__AVX__)
#include <immintrin.h>  // AVX, AVX2
#define HAVE_AVX 1
#else
#define HAVE_AVX 0
#endif

// Dimensione degli array per i test
#define ARRAY_SIZE 10000000
#define NUM_ITERATIONS 10

/**
 * Funzione scalare standard per sommare due array
 */
void somma_array_scalare(const float* a, const float* b, float* result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = a[i] + b[i];
    }
}

/**
 * Funzione che utilizza SSE per sommare due array (4 float alla volta)
 */
#if HAVE_SSE
void somma_array_sse(const float* a, const float* b, float* result, int size) {
    int i = 0;
    
    // Processa 4 float alla volta usando SSE
    for (; i <= size - 4; i += 4) {
        __m128 va = _mm_loadu_ps(&a[i]);  // Carica 4 float da a
        __m128 vb = _mm_loadu_ps(&b[i]);  // Carica 4 float da b
        __m128 vresult = _mm_add_ps(va, vb);  // Somma vettoriale
        _mm_storeu_ps(&result[i], vresult);  // Memorizza il risultato
    }
    
    // Processa i rimanenti elementi in modo scalare
    for (; i < size; i++) {
        result[i] = a[i] + b[i];
    }
}
#endif

/**
 * Funzione che utilizza AVX per sommare due array (8 float alla volta)
 */
#if HAVE_AVX
void somma_array_avx(const float* a, const float* b, float* result, int size) {
    int i = 0;
    
    // Processa 8 float alla volta usando AVX
    for (; i <= size - 8; i += 8) {
        __m256 va = _mm256_loadu_ps(&a[i]);  // Carica 8 float da a
        __m256 vb = _mm256_loadu_ps(&b[i]);  // Carica 8 float da b
        __m256 vresult = _mm256_add_ps(va, vb);  // Somma vettoriale
        _mm256_storeu_ps(&result[i], vresult);  // Memorizza il risultato
    }
    
    // Processa i rimanenti elementi in modo scalare
    for (; i < size; i++) {
        result[i] = a[i] + b[i];
    }
}
#endif

/**
 * Funzione scalare standard per moltiplicare due array
 */
void moltiplica_array_scalare(const float* a, const float* b, float* result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = a[i] * b[i];
    }
}

/**
 * Funzione che utilizza SSE per moltiplicare due array (4 float alla volta)
 */
#if HAVE_SSE
void moltiplica_array_sse(const float* a, const float* b, float* result, int size) {
    int i = 0;
    
    // Processa 4 float alla volta usando SSE
    for (; i <= size - 4; i += 4) {
        __m128 va = _mm_loadu_ps(&a[i]);
        __m128 vb = _mm_loadu_ps(&b[i]);
        __m128 vresult = _mm_mul_ps(va, vb);
        _mm_storeu_ps(&result[i], vresult);
    }
    
    // Processa i rimanenti elementi in modo scalare
    for (; i < size; i++) {
        result[i] = a[i] * b[i];
    }
}
#endif

/**
 * Funzione che utilizza AVX per moltiplicare due array (8 float alla volta)
 */
#if HAVE_AVX
void moltiplica_array_avx(const float* a, const float* b, float* result, int size) {
    int i = 0;
    
    // Processa 8 float alla volta usando AVX
    for (; i <= size - 8; i += 8) {
        __m256 va = _mm256_loadu_ps(&a[i]);
        __m256 vb = _mm256_loadu_ps(&b[i]);
        __m256 vresult = _mm256_mul_ps(va, vb);
        _mm256_storeu_ps(&result[i], vresult);
    }
    
    // Processa i rimanenti elementi in modo scalare
    for (; i < size; i++) {
        result[i] = a[i] * b[i];
    }
}
#endif

/**
 * Funzione per verificare che i risultati siano corretti
 */
int verifica_risultati(const float* a, const float* b, int size) {
    for (int i = 0; i < size; i++) {
        if (fabsf(a[i] - b[i]) > 0.0001f) {
            printf("Errore: risultati diversi all'indice %d (%.6f vs %.6f)\n", i, a[i], b[i]);
            return 0;
        }
    }
    return 1;
}

/**
 * Funzione per misurare il tempo di esecuzione
 */
double misura_tempo(void (*func)(const float*, const float*, float*, int), 
                    const float* a, const float* b, float* result, int size) {
    clock_t inizio, fine;
    double tempo_totale = 0.0;
    
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        inizio = clock();
        func(a, b, result, size);
        fine = clock();
        
        tempo_totale += ((double)(fine - inizio)) / CLOCKS_PER_SEC;
    }
    
    return tempo_totale / NUM_ITERATIONS;
}

/**
 * Funzione principale
 */
int main() {
    // Alloca memoria per gli array allineati a 32 byte (per AVX)
    float* a = NULL;
    float* b = NULL;
    float* result_scalare = NULL;
    float* result_sse = NULL;
    float* result_avx = NULL;
    
    // Allocazione con allineamento
#if defined(_MSC_VER)
    // Windows (Visual Studio)
    a = (float*)_aligned_malloc(ARRAY_SIZE * sizeof(float), 32);
    b = (float*)_aligned_malloc(ARRAY_SIZE * sizeof(float), 32);
    result_scalare = (float*)_aligned_malloc(ARRAY_SIZE * sizeof(float), 32);
    result_sse = (float*)_aligned_malloc(ARRAY_SIZE * sizeof(float), 32);
    result_avx = (float*)_aligned_malloc(ARRAY_SIZE * sizeof(float), 32);
#elif defined(__GNUC__)
    // Linux/macOS (GCC/Clang)
    posix_memalign((void**)&a, 32, ARRAY_SIZE * sizeof(float));
    posix_memalign((void**)&b, 32, ARRAY_SIZE * sizeof(float));
    posix_memalign((void**)&result_scalare, 32, ARRAY_SIZE * sizeof(float));
    posix_memalign((void**)&result_sse, 32, ARRAY_SIZE * sizeof(float));
    posix_memalign((void**)&result_avx, 32, ARRAY_SIZE * sizeof(float));
#else
    // Fallback per altri compilatori
    a = (float*)malloc(ARRAY_SIZE * sizeof(float));
    b = (float*)malloc(ARRAY_SIZE * sizeof(float));
    result_scalare = (float*)malloc(ARRAY_SIZE * sizeof(float));
    result_sse = (float*)malloc(ARRAY_SIZE * sizeof(float));
    result_avx = (float*)malloc(ARRAY_SIZE * sizeof(float));
#endif
    
    if (!a || !b || !result_scalare || !result_sse || !result_avx) {
        fprintf(stderr, "Errore: Impossibile allocare memoria\n");
        return 1;
    }
    
    // Inizializza gli array con valori casuali
    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        a[i] = (float)rand() / RAND_MAX;
        b[i] = (float)rand() / RAND_MAX;
    }
    
    printf("=== CONFRONTO TRA IMPLEMENTAZIONI SCALARI E VETTORIALI (SIMD) ===\n");
    printf("Dimensione array: %d elementi\n", ARRAY_SIZE);
    printf("Numero di iterazioni: %d\n\n", NUM_ITERATIONS);
    
    // Test di somma
    printf("Test di somma array:\n");
    
    // Versione scalare
    double tempo_somma_scalare = misura_tempo(somma_array_scalare, a, b, result_scalare, ARRAY_SIZE);
    printf("Somma scalare:      %.6f secondi\n", tempo_somma_scalare);
    
    // Versione SSE
#if HAVE_SSE
    double tempo_somma_sse = misura_tempo(somma_array_sse, a, b, result_sse, ARRAY_SIZE);
    printf("Somma SSE:          %.6f secondi\n", tempo_somma_sse);
    
    // Verifica risultati SSE
    if (verifica_risultati(result_scalare, result_sse, ARRAY_SIZE)) {
        double speedup_sse = tempo_somma_scalare / tempo_somma_sse;
        printf("Speedup SSE:        %.2fx\n", speedup_sse);
    }
#else
    printf("SSE non disponibile su questa piattaforma\n");
#endif
    
    // Versione AVX
#if HAVE_AVX
    double tempo_somma_avx = misura_tempo(somma_array_avx, a, b, result_avx, ARRAY_SIZE);
    printf("Somma AVX:          %.6f secondi\n", tempo_somma_avx);
    
    // Verifica risultati AVX
    if (verifica_risultati(result_scalare, result_avx, ARRAY_SIZE)) {
        double speedup_avx = tempo_somma_scalare / tempo_somma_avx;
        printf("Speedup AVX:        %.2fx\n", speedup_avx);
    }
#else
    printf("AVX non disponibile su questa piattaforma\n");
#endif
    
    printf("\n");
    
    // Test di moltiplicazione
    printf("Test di moltiplicazione array:\n");
    
    // Versione scalare
    double tempo_mult_scalare = misura_tempo(moltiplica_array_scalare, a, b, result_scalare, ARRAY_SIZE);
    printf("Moltiplicazione scalare:      %.6f secondi\n", tempo_mult_scalare);
    
    // Versione SSE
#if HAVE_SSE
    double tempo_mult_sse = misura_tempo(moltiplica_array_sse, a, b, result_sse, ARRAY_SIZE);
    printf("Moltiplicazione SSE:          %.6f secondi\n", tempo_mult_sse);
    
    // Verifica risultati SSE
    if (verifica_risultati(result_scalare, result_sse, ARRAY_SIZE)) {
        double speedup_sse = tempo_mult_scalare / tempo_mult_sse;
        printf("Speedup SSE:                  %.2fx\n", speedup_sse);
    }
#endif
    
    // Versione AVX
#if HAVE_AVX
    double tempo_mult_avx = misura_tempo(moltiplica_array_avx, a, b, result_avx, ARRAY_SIZE);
    printf("Moltiplicazione AVX:          %.6f secondi\n", tempo_mult_avx);
    
    // Verifica risultati AVX
    if (verifica_risultati(result_scalare, result_avx, ARRAY_SIZE)) {
        double speedup_avx = tempo_mult_scalare / tempo_mult_avx;
        printf("Speedup AVX:                  %.2fx\n", speedup_avx);
    }
#endif
    
    printf("\nNote sulle istruzioni SIMD:\n");
    printf("1. SIMD (Single Instruction Multiple Data) permette di eseguire la stessa operazione su più dati contemporaneamente\n");
    printf("2. SSE (Streaming SIMD Extensions) opera su registri di 128 bit (4 float alla volta)\n");
    printf("3. AVX (Advanced Vector Extensions) opera su registri di 256 bit (8 float alla volta)\n");
    printf("4. L'allineamento della memoria è importante per le prestazioni ottimali delle istruzioni SIMD\n");
    printf("5. Le istruzioni SIMD sono particolarmente utili per algoritmi che operano su grandi quantità di dati\n");
    
    // Libera la memoria
#if defined(_MSC_VER)
    _aligned_free(a);
    _aligned_free(b);
    _aligned_free(result_scalare);
    _aligned_free(result_sse);
    _aligned_free(result_avx);
#else
    free(a);
    free(b);
    free(result_scalare);
    free(result_sse);
    free(result_avx);
#endif
    
    return 0;
}

/**
 * Istruzioni per la compilazione ed esecuzione:
 * 
 * Per GCC con supporto SSE e AVX:
 * gcc -Wall -O3 -msse2 -mavx 08_simd_instructions.c -o 08_simd_instructions -lm
 * ./08_simd_instructions
 * 
 * Per Visual Studio:
 * cl /O2 /arch:AVX 08_simd_instructions.c
 * 08_simd_instructions.exe
 * 
 * Note:
 * - Su alcune piattaforme potrebbe essere necessario utilizzare flag di compilazione diversi
 * - Il codice verifica automaticamente la disponibilità delle estensioni SIMD
 * - Per ottenere le massime prestazioni, compilare con le ottimizzazioni abilitate (-O2 o -O3)
 */