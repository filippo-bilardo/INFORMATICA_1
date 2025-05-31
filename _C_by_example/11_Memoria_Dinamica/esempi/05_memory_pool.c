/**
 * Esempio di implementazione di un Memory Pool
 * Questo esempio mostra come implementare un allocatore di memoria personalizzato
 * basato sul concetto di memory pool per migliorare le prestazioni e ridurre la frammentazione.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definizione della struttura del memory pool
typedef struct {
    void* memoria;           // Puntatore all'area di memoria
    size_t dimensione_blocco; // Dimensione di ciascun blocco
    size_t num_blocchi;      // Numero totale di blocchi
    unsigned char* mappa;    // Mappa dei blocchi liberi/occupati
    size_t blocchi_liberi;   // Contatore dei blocchi liberi
} MemoryPool;

/**
 * Inizializza un nuovo memory pool
 * @param dimensione_blocco Dimensione di ciascun blocco in byte
 * @param num_blocchi Numero di blocchi nel pool
 * @return Puntatore al memory pool inizializzato o NULL in caso di errore
 */
MemoryPool* inizializza_pool(size_t dimensione_blocco, size_t num_blocchi) {
    // Allocazione della struttura del pool
    MemoryPool* pool = (MemoryPool*)malloc(sizeof(MemoryPool));
    if (!pool) return NULL;
    
    // Allocazione della memoria per tutti i blocchi
    pool->memoria = malloc(dimensione_blocco * num_blocchi);
    if (!pool->memoria) {
        free(pool);
        return NULL;
    }
    
    // Allocazione della mappa dei blocchi (1 bit per blocco, arrotondato a byte)
    size_t dimensione_mappa = (num_blocchi + 7) / 8;
    pool->mappa = (unsigned char*)calloc(dimensione_mappa, 1);
    if (!pool->mappa) {
        free(pool->memoria);
        free(pool);
        return NULL;
    }
    
    // Inizializzazione dei parametri
    pool->dimensione_blocco = dimensione_blocco;
    pool->num_blocchi = num_blocchi;
    pool->blocchi_liberi = num_blocchi;
    
    return pool;
}

/**
 * Verifica se un blocco è libero
 * @param pool Puntatore al memory pool
 * @param indice Indice del blocco da verificare
 * @return 1 se il blocco è libero, 0 se è occupato
 */
int blocco_libero(MemoryPool* pool, size_t indice) {
    if (!pool || indice >= pool->num_blocchi) return 0;
    
    size_t byte_indice = indice / 8;
    size_t bit_indice = indice % 8;
    
    return !(pool->mappa[byte_indice] & (1 << bit_indice));
}

/**
 * Imposta lo stato di un blocco (libero o occupato)
 * @param pool Puntatore al memory pool
 * @param indice Indice del blocco da modificare
 * @param occupato 1 per impostare come occupato, 0 per impostare come libero
 */
void imposta_stato_blocco(MemoryPool* pool, size_t indice, int occupato) {
    if (!pool || indice >= pool->num_blocchi) return;
    
    size_t byte_indice = indice / 8;
    size_t bit_indice = indice % 8;
    
    if (occupato) {
        // Imposta il bit a 1 (blocco occupato)
        pool->mappa[byte_indice] |= (1 << bit_indice);
        pool->blocchi_liberi--;
    } else {
        // Imposta il bit a 0 (blocco libero)
        pool->mappa[byte_indice] &= ~(1 << bit_indice);
        pool->blocchi_liberi++;
    }
}

/**
 * Alloca un blocco dal memory pool
 * @param pool Puntatore al memory pool
 * @return Puntatore al blocco allocato o NULL se non ci sono blocchi disponibili
 */
void* pool_alloc(MemoryPool* pool) {
    if (!pool || pool->blocchi_liberi == 0) return NULL;
    
    // Cerca un blocco libero
    for (size_t i = 0; i < pool->num_blocchi; i++) {
        if (blocco_libero(pool, i)) {
            // Blocco trovato, lo marca come occupato
            imposta_stato_blocco(pool, i, 1);
            
            // Calcola l'indirizzo del blocco e lo restituisce
            return (char*)pool->memoria + (i * pool->dimensione_blocco);
        }
    }
    
    return NULL; // Non dovrebbe mai arrivare qui se blocchi_liberi > 0
}

/**
 * Libera un blocco precedentemente allocato
 * @param pool Puntatore al memory pool
 * @param ptr Puntatore al blocco da liberare
 * @return 1 se l'operazione è riuscita, 0 altrimenti
 */
int pool_free(MemoryPool* pool, void* ptr) {
    if (!pool || !ptr) return 0;
    
    // Verifica che il puntatore appartenga al pool
    if (ptr < pool->memoria || 
        ptr >= (char*)pool->memoria + (pool->num_blocchi * pool->dimensione_blocco)) {
        return 0;
    }
    
    // Calcola l'indice del blocco
    size_t offset = (char*)ptr - (char*)pool->memoria;
    if (offset % pool->dimensione_blocco != 0) {
        return 0; // Il puntatore non è allineato all'inizio di un blocco
    }
    
    size_t indice = offset / pool->dimensione_blocco;
    
    // Verifica che il blocco sia attualmente occupato
    if (blocco_libero(pool, indice)) {
        return 0; // Tentativo di liberare un blocco già libero
    }
    
    // Imposta il blocco come libero
    imposta_stato_blocco(pool, indice, 0);
    return 1;
}

/**
 * Distrugge un memory pool e libera tutta la memoria associata
 * @param pool Puntatore al memory pool da distruggere
 */
void distruggi_pool(MemoryPool* pool) {
    if (!pool) return;
    
    if (pool->mappa) free(pool->mappa);
    if (pool->memoria) free(pool->memoria);
    free(pool);
}

/**
 * Stampa lo stato attuale del memory pool
 * @param pool Puntatore al memory pool
 */
void stampa_stato_pool(MemoryPool* pool) {
    if (!pool) return;
    
    printf("Stato del Memory Pool:\n");
    printf("Dimensione blocco: %zu byte\n", pool->dimensione_blocco);
    printf("Numero totale di blocchi: %zu\n", pool->num_blocchi);
    printf("Blocchi liberi: %zu\n", pool->blocchi_liberi);
    printf("Blocchi occupati: %zu\n", pool->num_blocchi - pool->blocchi_liberi);
    printf("Utilizzo: %.2f%%\n", 100.0 * (pool->num_blocchi - pool->blocchi_liberi) / pool->num_blocchi);
    
    printf("Mappa dei blocchi: ");
    for (size_t i = 0; i < pool->num_blocchi; i++) {
        printf("%c", blocco_libero(pool, i) ? '.' : 'X');
        if ((i + 1) % 50 == 0 && i + 1 < pool->num_blocchi) printf("\n                ");
    }
    printf("\n");
}

// Esempio di utilizzo del memory pool
int main() {
    // Creazione di un memory pool con 100 blocchi da 32 byte ciascuno
    MemoryPool* pool = inizializza_pool(32, 100);
    if (!pool) {
        printf("Errore: impossibile creare il memory pool\n");
        return 1;
    }
    
    printf("Memory pool creato con successo!\n\n");
    stampa_stato_pool(pool);
    
    // Allocazione di alcuni blocchi
    void* blocchi[10];
    printf("\nAllocazione di 10 blocchi...\n");
    for (int i = 0; i < 10; i++) {
        blocchi[i] = pool_alloc(pool);
        if (blocchi[i]) {
            // Scriviamo qualcosa nel blocco per dimostrare che è utilizzabile
            sprintf((char*)blocchi[i], "Blocco %d", i);
        } else {
            printf("Errore: impossibile allocare il blocco %d\n", i);
        }
    }
    
    stampa_stato_pool(pool);
    
    // Verifichiamo il contenuto dei blocchi
    printf("\nContenuto dei blocchi allocati:\n");
    for (int i = 0; i < 10; i++) {
        printf("Blocco %d: %s\n", i, (char*)blocchi[i]);
    }
    
    // Liberiamo alcuni blocchi
    printf("\nLiberazione dei blocchi pari...\n");
    for (int i = 0; i < 10; i += 2) {
        if (pool_free(pool, blocchi[i])) {
            printf("Blocco %d liberato con successo\n", i);
        } else {
            printf("Errore: impossibile liberare il blocco %d\n", i);
        }
    }
    
    stampa_stato_pool(pool);
    
    // Riallochiamo alcuni blocchi
    printf("\nRiallocazione di 5 nuovi blocchi...\n");
    void* nuovi_blocchi[5];
    for (int i = 0; i < 5; i++) {
        nuovi_blocchi[i] = pool_alloc(pool);
        if (nuovi_blocchi[i]) {
            sprintf((char*)nuovi_blocchi[i], "Nuovo blocco %d", i);
            printf("Nuovo blocco %d allocato con successo\n", i);
        } else {
            printf("Errore: impossibile allocare il nuovo blocco %d\n", i);
        }
    }
    
    stampa_stato_pool(pool);
    
    // Liberiamo tutti i blocchi rimanenti
    printf("\nLiberazione di tutti i blocchi rimanenti...\n");
    for (int i = 1; i < 10; i += 2) {
        pool_free(pool, blocchi[i]);
    }
    for (int i = 0; i < 5; i++) {
        pool_free(pool, nuovi_blocchi[i]);
    }
    
    stampa_stato_pool(pool);
    
    // Distruzione del memory pool
    printf("\nDistruzione del memory pool...\n");
    distruggi_pool(pool);
    printf("Memory pool distrutto con successo!\n");
    
    return 0;
}