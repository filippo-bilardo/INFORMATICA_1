# Gestione Avanzata della Memoria in C

## Introduzione

La gestione della memoria è uno degli aspetti più critici della programmazione in C. A differenza di linguaggi con garbage collection automatico, C richiede che il programmatore gestisca esplicitamente l'allocazione e la deallocazione della memoria. Questa responsabilità offre grande potenza e controllo, ma comporta anche sfide significative.

## Oltre le Basi: Tecniche Avanzate

### Allocatori di Memoria Personalizzati

In applicazioni complesse, gli allocatori di memoria standard (`malloc`, `free`) potrebbero non essere ottimali. Implementare allocatori personalizzati può migliorare significativamente le prestazioni.

```c
// Esempio di un semplice memory pool
#define POOL_SIZE 1024 * 1024  // 1MB pool

typedef struct {
    char buffer[POOL_SIZE];
    size_t used;
} MemoryPool;

MemoryPool* create_pool() {
    MemoryPool* pool = (MemoryPool*)malloc(sizeof(MemoryPool));
    if (pool) {
        pool->used = 0;
    }
    return pool;
}

void* pool_alloc(MemoryPool* pool, size_t size) {
    // Allineamento a 8 byte
    size = (size + 7) & ~7;
    
    if (pool->used + size > POOL_SIZE) {
        return NULL;  // Pool esaurito
    }
    
    void* ptr = &pool->buffer[pool->used];
    pool->used += size;
    return ptr;
}

void destroy_pool(MemoryPool* pool) {
    free(pool);
}
```

### Memory Mapping

Per grandi blocchi di memoria o per la condivisione di memoria tra processi, le funzioni di memory mapping come `mmap` offrono alternative potenti.

```c
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

// Esempio di memory mapping di un file
void* map_file(const char* filename, size_t* size) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) return NULL;
    
    // Ottieni dimensione del file
    *size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    
    // Mappa il file in memoria
    void* mapped = mmap(NULL, *size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    
    if (mapped == MAP_FAILED) return NULL;
    return mapped;
}

void unmap_file(void* mapped, size_t size) {
    munmap(mapped, size);
}
```

### Gestione di Memoria Non Contigua

Per strutture dati complesse, potrebbe essere necessario gestire memoria non contigua in modo efficiente.

```c
// Implementazione di una lista di blocchi di memoria
typedef struct MemBlock {
    void* data;
    size_t size;
    struct MemBlock* next;
} MemBlock;

MemBlock* create_block(size_t size) {
    MemBlock* block = (MemBlock*)malloc(sizeof(MemBlock));
    if (!block) return NULL;
    
    block->data = malloc(size);
    if (!block->data) {
        free(block);
        return NULL;
    }
    
    block->size = size;
    block->next = NULL;
    return block;
}

void free_blocks(MemBlock* head) {
    while (head) {
        MemBlock* temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}
```

## Tecniche di Debugging della Memoria

### Rilevamento di Memory Leak

I memory leak (perdite di memoria) si verificano quando la memoria allocata non viene mai liberata. Strumenti come Valgrind possono aiutare a identificarli.

```c
// Esempio di codice con memory leak
void function_with_leak() {
    int* array = (int*)malloc(10 * sizeof(int));
    // Manca free(array)
}

// Correzione
void function_without_leak() {
    int* array = (int*)malloc(10 * sizeof(int));
    // Operazioni con array
    free(array);
}
```

### Rilevamento di Accessi Invalidi

Gli accessi a memoria non valida possono causare comportamenti imprevedibili o crash.

```c
// Esempio di accesso invalido
void invalid_access() {
    int* array = (int*)malloc(5 * sizeof(int));
    array[10] = 42;  // Accesso fuori dai limiti
    free(array);
}
```

### Tecniche di Guardia

Inserire "guardie" attorno ai blocchi di memoria può aiutare a rilevare overflow.

```c
#define GUARD_VALUE 0xDEADBEEF

typedef struct {
    unsigned int guard1;
    size_t size;
    char data[1];  // Flexible array member (C99)
    // La guardia2 sarà posizionata dopo i dati
} GuardedBlock;

void* guarded_malloc(size_t size) {
    GuardedBlock* block = (GuardedBlock*)malloc(sizeof(GuardedBlock) + size + sizeof(unsigned int));
    if (!block) return NULL;
    
    block->guard1 = GUARD_VALUE;
    block->size = size;
    
    // Posiziona la seconda guardia dopo i dati
    unsigned int* guard2 = (unsigned int*)(block->data + size);
    *guard2 = GUARD_VALUE;
    
    return block->data;
}

int check_guards(void* ptr) {
    GuardedBlock* block = (GuardedBlock*)((char*)ptr - offsetof(GuardedBlock, data));
    unsigned int* guard2 = (unsigned int*)(block->data + block->size);
    
    return (block->guard1 == GUARD_VALUE && *guard2 == GUARD_VALUE);
}

void guarded_free(void* ptr) {
    if (!ptr) return;
    
    GuardedBlock* block = (GuardedBlock*)((char*)ptr - offsetof(GuardedBlock, data));
    if (!check_guards(ptr)) {
        fprintf(stderr, "Memory corruption detected!\n");
        abort();
    }
    
    free(block);
}
```

## Gestione della Frammentazione

La frammentazione della memoria può ridurre significativamente l'efficienza di un programma.

### Frammentazione Esterna

Si verifica quando lo spazio libero è diviso in piccoli blocchi non contigui.

### Frammentazione Interna

Si verifica quando viene allocato più spazio di quanto richiesto a causa dell'allineamento o della granularità dell'allocatore.

### Strategie di Mitigazione

- **Compattazione**: Riorganizzare la memoria per consolidare lo spazio libero
- **Allocazione a blocchi fissi**: Utilizzare blocchi di dimensioni predefinite
- **Slab allocation**: Allocare oggetti di dimensioni simili in "slab" dedicati

```c
// Esempio semplificato di slab allocator
#define SLAB_SIZE 4096
#define OBJECT_SIZE 256
#define OBJECTS_PER_SLAB (SLAB_SIZE / OBJECT_SIZE)

typedef struct Slab {
    char memory[SLAB_SIZE];
    unsigned char used[OBJECTS_PER_SLAB];
    struct Slab* next;
} Slab;

typedef struct {
    Slab* slabs;
    size_t object_size;
} SlabAllocator;

SlabAllocator* create_slab_allocator() {
    SlabAllocator* allocator = (SlabAllocator*)malloc(sizeof(SlabAllocator));
    if (!allocator) return NULL;
    
    allocator->slabs = NULL;
    allocator->object_size = OBJECT_SIZE;
    return allocator;
}

void* slab_alloc(SlabAllocator* allocator) {
    // Cerca uno slot libero nelle slab esistenti
    Slab* slab = allocator->slabs;
    while (slab) {
        for (int i = 0; i < OBJECTS_PER_SLAB; i++) {
            if (!slab->used[i]) {
                slab->used[i] = 1;
                return &slab->memory[i * allocator->object_size];
            }
        }
        slab = slab->next;
    }
    
    // Crea una nuova slab se necessario
    Slab* new_slab = (Slab*)malloc(sizeof(Slab));
    if (!new_slab) return NULL;
    
    memset(new_slab->used, 0, OBJECTS_PER_SLAB);
    new_slab->next = allocator->slabs;
    allocator->slabs = new_slab;
    
    // Alloca il primo oggetto nella nuova slab
    new_slab->used[0] = 1;
    return new_slab->memory;
}
```

## Considerazioni sulla Sicurezza

### Vulnerabilità di Memoria

- **Buffer Overflow**: Scrivere oltre i limiti di un buffer
- **Use-After-Free**: Accedere a memoria già liberata
- **Double Free**: Liberare la stessa memoria più volte
- **Memory Leaks**: Non liberare memoria allocata

### Tecniche di Mitigazione

- **Controlli dei limiti**: Verificare sempre i limiti prima di accedere alla memoria
- **Sanitizzazione degli input**: Validare tutti gli input esterni
- **Strumenti di analisi statica**: Utilizzare strumenti come AddressSanitizer

## Conclusione

La gestione avanzata della memoria in C richiede una comprensione approfondita dei meccanismi sottostanti e delle potenziali insidie. Implementando tecniche appropriate e utilizzando strumenti di debugging, è possibile creare applicazioni C che utilizzano la memoria in modo efficiente e sicuro.

Ricorda che la gestione della memoria è un compromesso tra efficienza, complessità e sicurezza. La soluzione ottimale dipende dalle specifiche esigenze dell'applicazione.