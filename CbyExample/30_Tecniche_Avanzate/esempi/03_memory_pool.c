/**
 * File: 03_memory_pool.c
 * Descrizione: Esempio di implementazione di un memory pool in C
 * 
 * Questo esempio dimostra come implementare un allocatore di memoria personalizzato
 * basato sul pattern "memory pool", che preallocca un blocco di memoria e lo gestisce
 * in modo efficiente per ridurre la frammentazione e migliorare le prestazioni.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * Definizione della struttura del memory pool
 */
typedef struct {
    void* memory;         // Puntatore al blocco di memoria allocato
    size_t block_size;    // Dimensione di ciascun blocco
    size_t num_blocks;    // Numero totale di blocchi
    unsigned char* used;  // Array di bit per tenere traccia dei blocchi utilizzati
} MemoryPool;

/**
 * Inizializza un nuovo memory pool
 * @param pool Puntatore alla struttura del pool da inizializzare
 * @param block_size Dimensione di ciascun blocco in bytes
 * @param num_blocks Numero di blocchi da preallocare
 * @return 1 se l'inizializzazione ha successo, 0 altrimenti
 */
int pool_init(MemoryPool* pool, size_t block_size, size_t num_blocks) {
    // Allineamento della dimensione del blocco a 8 byte per migliori prestazioni
    if (block_size % 8 != 0) {
        block_size = ((block_size / 8) + 1) * 8;
    }
    
    // Allocazione del blocco di memoria principale
    pool->memory = malloc(block_size * num_blocks);
    if (pool->memory == NULL) {
        return 0; // Fallimento nell'allocazione
    }
    
    // Allocazione dell'array di bit per tenere traccia dei blocchi utilizzati
    pool->used = (unsigned char*)calloc((num_blocks + 7) / 8, sizeof(unsigned char));
    if (pool->used == NULL) {
        free(pool->memory);
        return 0; // Fallimento nell'allocazione
    }
    
    pool->block_size = block_size;
    pool->num_blocks = num_blocks;
    
    return 1; // Successo
}

/**
 * Verifica se un blocco è utilizzato
 */
int is_block_used(MemoryPool* pool, size_t block_index) {
    size_t byte_index = block_index / 8;
    size_t bit_index = block_index % 8;
    return (pool->used[byte_index] & (1 << bit_index)) != 0;
}

/**
 * Marca un blocco come utilizzato
 */
void set_block_used(MemoryPool* pool, size_t block_index) {
    size_t byte_index = block_index / 8;
    size_t bit_index = block_index % 8;
    pool->used[byte_index] |= (1 << bit_index);
}

/**
 * Marca un blocco come libero
 */
void set_block_free(MemoryPool* pool, size_t block_index) {
    size_t byte_index = block_index / 8;
    size_t bit_index = block_index % 8;
    pool->used[byte_index] &= ~(1 << bit_index);
}

/**
 * Alloca un blocco dal memory pool
 * @param pool Puntatore al memory pool
 * @return Puntatore al blocco allocato, o NULL se non ci sono blocchi disponibili
 */
void* pool_alloc(MemoryPool* pool) {
    // Cerca un blocco libero
    for (size_t i = 0; i < pool->num_blocks; i++) {
        if (!is_block_used(pool, i)) {
            // Marca il blocco come utilizzato
            set_block_used(pool, i);
            // Calcola l'indirizzo del blocco e lo restituisce
            return (char*)pool->memory + (i * pool->block_size);
        }
    }
    
    return NULL; // Nessun blocco disponibile
}

/**
 * Libera un blocco precedentemente allocato
 * @param pool Puntatore al memory pool
 * @param ptr Puntatore al blocco da liberare
 * @return 1 se l'operazione ha successo, 0 altrimenti
 */
int pool_free(MemoryPool* pool, void* ptr) {
    // Verifica che il puntatore sia all'interno del pool
    if (ptr < pool->memory || 
        ptr >= (char*)pool->memory + (pool->num_blocks * pool->block_size)) {
        return 0; // Puntatore non valido
    }
    
    // Calcola l'indice del blocco
    size_t offset = (char*)ptr - (char*)pool->memory;
    if (offset % pool->block_size != 0) {
        return 0; // Puntatore non allineato a un blocco
    }
    
    size_t block_index = offset / pool->block_size;
    
    // Verifica che il blocco sia effettivamente utilizzato
    if (!is_block_used(pool, block_index)) {
        return 0; // Tentativo di liberare un blocco già libero
    }
    
    // Marca il blocco come libero
    set_block_free(pool, block_index);
    
    return 1; // Successo
}

/**
 * Distrugge il memory pool e libera tutta la memoria
 */
void pool_destroy(MemoryPool* pool) {
    if (pool->memory != NULL) {
        free(pool->memory);
        pool->memory = NULL;
    }
    
    if (pool->used != NULL) {
        free(pool->used);
        pool->used = NULL;
    }
    
    pool->block_size = 0;
    pool->num_blocks = 0;
}

/**
 * Funzione di test che confronta le prestazioni del memory pool
 * con quelle di malloc/free standard
 */
void benchmark_test(size_t num_allocations, size_t block_size) {
    clock_t start, end;
    double time_used;
    void* ptrs[num_allocations];
    
    // Test con malloc/free standard
    printf("Test con malloc/free standard:\n");
    
    // Misura il tempo per le allocazioni
    start = clock();
    for (size_t i = 0; i < num_allocations; i++) {
        ptrs[i] = malloc(block_size);
    }
    end = clock();
    time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("  Tempo per %zu allocazioni: %f secondi\n", num_allocations, time_used);
    
    // Misura il tempo per le deallocazioni
    start = clock();
    for (size_t i = 0; i < num_allocations; i++) {
        free(ptrs[i]);
    }
    end = clock();
    time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("  Tempo per %zu deallocazioni: %f secondi\n\n", num_allocations, time_used);
    
    // Test con memory pool
    printf("Test con memory pool:\n");
    
    MemoryPool pool;
    if (!pool_init(&pool, block_size, num_allocations)) {
        printf("Errore nell'inizializzazione del memory pool\n");
        return;
    }
    
    // Misura il tempo per le allocazioni
    start = clock();
    for (size_t i = 0; i < num_allocations; i++) {
        ptrs[i] = pool_alloc(&pool);
    }
    end = clock();
    time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("  Tempo per %zu allocazioni: %f secondi\n", num_allocations, time_used);
    
    // Misura il tempo per le deallocazioni
    start = clock();
    for (size_t i = 0; i < num_allocations; i++) {
        pool_free(&pool, ptrs[i]);
    }
    end = clock();
    time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("  Tempo per %zu deallocazioni: %f secondi\n", num_allocations, time_used);
    
    // Distruzione del pool
    pool_destroy(&pool);
}

/**
 * Funzione principale
 */
int main() {
    printf("Benchmark di confronto tra memory pool e malloc/free standard\n\n");
    
    // Esegui il benchmark con diversi parametri
    printf("=== Test con blocchi piccoli (64 bytes) ===\n");
    benchmark_test(10000, 64);
    
    printf("\n=== Test con blocchi medi (256 bytes) ===\n");
    benchmark_test(10000, 256);
    
    printf("\n=== Test con blocchi grandi (1024 bytes) ===\n");
    benchmark_test(10000, 1024);
    
    printf("\nNota: Il memory pool è generalmente più veloce per allocazioni\n");
    printf("e deallocazioni frequenti di blocchi di dimensione fissa, poiché\n");
    printf("evita la frammentazione della memoria e le chiamate di sistema.\n");
    printf("Tuttavia, richiede che la dimensione massima dei blocchi e il\n");
    printf("numero di blocchi siano noti in anticipo.\n");
    
    return 0;
}

/**
 * Istruzioni per la compilazione ed esecuzione:
 * 
 * gcc -Wall -O2 03_memory_pool.c -o 03_memory_pool
 * ./03_memory_pool
 * 
 * Nota: L'opzione -O2 abilita le ottimizzazioni del compilatore.
 */