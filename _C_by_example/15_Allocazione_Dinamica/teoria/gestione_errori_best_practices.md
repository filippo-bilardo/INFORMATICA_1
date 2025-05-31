# Gestione degli Errori e Best Practices nell'Allocazione Dinamica

La gestione dinamica della memoria è una delle aree più delicate della programmazione in C. Errori nella gestione della memoria possono causare problemi difficili da diagnosticare, come crash improvvisi, comportamenti imprevedibili o degradazione delle prestazioni. In questo capitolo, esploreremo le tecniche per gestire gli errori di allocazione e le best practices per una gestione sicura ed efficiente della memoria dinamica.

## Gestione degli Errori di Allocazione

### Controllo dei Valori di Ritorno

La prima e più importante regola nella gestione della memoria dinamica è controllare sempre i valori restituiti dalle funzioni di allocazione. Tutte le funzioni di allocazione (`malloc()`, `calloc()`, `realloc()`) restituiscono `NULL` in caso di fallimento.

```c
int *p = (int *)malloc(sizeof(int));
if (p == NULL) {
    // Gestione dell'errore
    fprintf(stderr, "Errore: impossibile allocare memoria\n");
    exit(EXIT_FAILURE); // o gestire l'errore in altro modo
}
```

### Strategie di Gestione degli Errori

Esistono diverse strategie per gestire gli errori di allocazione:

1. **Terminazione del programma**:
   ```c
   if (p == NULL) {
       fprintf(stderr, "Errore fatale: memoria insufficiente\n");
       exit(EXIT_FAILURE);
   }
   ```

2. **Propagazione dell'errore**:
   ```c
   int *allocate_array(size_t size, int *error_code) {
       int *array = (int *)malloc(size * sizeof(int));
       if (array == NULL) {
           *error_code = -1; // Imposta un codice di errore
           return NULL;
       }
       *error_code = 0; // Nessun errore
       return array;
   }
   ```

3. **Retry con dimensione ridotta**:
   ```c
   int *p = NULL;
   size_t size = INITIAL_SIZE;
   while (p == NULL && size >= MINIMUM_SIZE) {
       p = (int *)malloc(size * sizeof(int));
       if (p == NULL) {
           size /= 2; // Riduci la dimensione e riprova
       }
   }
   if (p == NULL) {
       // Gestione dell'errore finale
   }
   ```

4. **Liberazione di risorse non essenziali**:
   ```c
   if (p == NULL) {
       // Libera cache o altre risorse non essenziali
       free_cache();
       // Riprova l'allocazione
       p = (int *)malloc(size);
   }
   ```

### Gestione degli Errori con `realloc()`

La funzione `realloc()` richiede particolare attenzione nella gestione degli errori, poiché in caso di fallimento il puntatore originale rimane valido:

```c
int *nuovo_array = (int *)realloc(array, nuovo_size);
if (nuovo_array == NULL) {
    // Gestione dell'errore
    fprintf(stderr, "Errore: impossibile ridimensionare la memoria\n");
    // Importante: array è ancora valido e deve essere liberato
    free(array);
    return NULL;
}
array = nuovo_array; // Aggiorna il puntatore solo in caso di successo
```

## Problemi Comuni e Come Evitarli

### Memory Leak (Perdita di Memoria)

Un memory leak si verifica quando la memoria allocata non viene mai liberata, causando un consumo progressivo di memoria.

**Cause comuni**:
- Perdita del riferimento alla memoria allocata
- Mancata chiamata a `free()` in tutti i percorsi di esecuzione
- Eccezioni o errori che interrompono il flusso normale del programma

**Come evitare**:

```c
// Assicurarsi di liberare la memoria in tutti i percorsi di esecuzione
void funzione() {
    int *p = (int *)malloc(sizeof(int));
    if (p == NULL) {
        return; // Nessun leak qui, p non è stato allocato
    }
    
    if (condizione_errore) {
        free(p); // Importante: liberare la memoria prima di uscire
        return;
    }
    
    // Utilizzo normale
    free(p); // Liberazione alla fine della funzione
}
```

**Pattern RAII (Resource Acquisition Is Initialization) in C**:

```c
struct Resource {
    int *data;
};

struct Resource *create_resource(size_t size) {
    struct Resource *res = (struct Resource *)malloc(sizeof(struct Resource));
    if (res == NULL) {
        return NULL;
    }
    
    res->data = (int *)malloc(size * sizeof(int));
    if (res->data == NULL) {
        free(res);
        return NULL;
    }
    
    return res;
}

void destroy_resource(struct Resource *res) {
    if (res != NULL) {
        free(res->data);
        free(res);
    }
}

// Utilizzo
void funzione() {
    struct Resource *res = create_resource(10);
    if (res == NULL) {
        return;
    }
    
    // Utilizzo della risorsa
    
    destroy_resource(res); // Liberazione di tutte le risorse
}
```

### Dangling Pointer (Puntatore Pendente)

Un dangling pointer si verifica quando si accede a memoria che è stata liberata.

**Cause comuni**:
- Utilizzo di un puntatore dopo aver chiamato `free()`
- Restituzione di un puntatore a memoria locale di una funzione
- Utilizzo di un puntatore dopo che la memoria è stata ridimensionata con `realloc()`

**Come evitare**:

```c
// Impostare i puntatori a NULL dopo free
int *p = (int *)malloc(sizeof(int));
// Utilizzo di p
free(p);
p = NULL; // Previene l'uso accidentale dopo free

// Funzione helper per free sicuro
void safe_free(void **pp) {
    if (pp != NULL && *pp != NULL) {
        free(*pp);
        *pp = NULL;
    }
}

// Utilizzo
int *p = (int *)malloc(sizeof(int));
safe_free((void **)&p); // p sarà NULL dopo questa chiamata
```

### Double Free (Doppia Liberazione)

Un double free si verifica quando si tenta di liberare la stessa memoria più volte.

**Cause comuni**:
- Chiamate multiple a `free()` sullo stesso puntatore
- Liberazione di memoria già liberata da un'altra parte del codice
- Errori logici in strutture dati complesse

**Come evitare**:

```c
// Impostare i puntatori a NULL dopo free previene anche il double free
int *p = (int *)malloc(sizeof(int));
free(p);
p = NULL;

// La funzione safe_free vista sopra previene anche il double free
safe_free((void **)&p);
safe_free((void **)&p); // Non causa problemi, p è già NULL
```

### Buffer Overflow e Underflow

Un buffer overflow si verifica quando si scrive oltre i limiti della memoria allocata.

**Cause comuni**:
- Indici di array non controllati
- Calcoli errati delle dimensioni
- Utilizzo di funzioni di stringa non sicure

**Come evitare**:

```c
// Controllo degli indici
int *array = (int *)malloc(n * sizeof(int));
for (int i = 0; i < n; i++) { // Nota: i < n, non i <= n
    array[i] = i;
}

// Utilizzo di funzioni sicure per le stringhe
char *str = (char *)malloc(size);
strncpy(str, source, size - 1); // Lascia spazio per il terminatore
str[size - 1] = '\0'; // Assicura la terminazione
```

## Strumenti per il Debug della Memoria

### Valgrind

Valgrind è uno strumento potente per il debug della memoria che può rilevare memory leak, accessi a memoria non valida, utilizzo di memoria non inizializzata e altri problemi.

```bash
# Compilazione con informazioni di debug
gcc -g -o mio_programma mio_programma.c

# Esecuzione con Valgrind
valgrind --leak-check=full ./mio_programma
```

### AddressSanitizer (ASan)

AddressSanitizer è uno strumento di rilevamento degli errori di memoria integrato nei compilatori moderni come GCC e Clang.

```bash
# Compilazione con AddressSanitizer
gcc -fsanitize=address -g -o mio_programma mio_programma.c

# Esecuzione normale (gli errori verranno segnalati automaticamente)
./mio_programma
```

### Electric Fence

Electric Fence è una libreria che aiuta a rilevare gli accessi oltre i limiti della memoria allocata.

```bash
# Compilazione
gcc -g -o mio_programma mio_programma.c

# Esecuzione con Electric Fence
LD_PRELOAD=/usr/lib/libefence.so ./mio_programma
```

## Best Practices per la Gestione della Memoria

### 1. Controllare Sempre i Valori di Ritorno

```c
int *p = (int *)malloc(sizeof(int));
if (p == NULL) {
    // Gestione dell'errore
}
```

### 2. Liberare Sempre la Memoria Allocata

```c
int *p = (int *)malloc(sizeof(int));
// Utilizzo di p
free(p);
p = NULL;
```

### 3. Utilizzare Funzioni Wrapper

```c
void *safe_malloc(size_t size) {
    void *p = malloc(size);
    if (p == NULL) {
        fprintf(stderr, "Errore: impossibile allocare %zu byte\n", size);
        exit(EXIT_FAILURE);
    }
    return p;
}
```

### 4. Documentare la Proprietà della Memoria

```c
// Questa funzione alloca memoria che deve essere liberata dal chiamante
char *create_string(const char *source) {
    char *str = (char *)malloc(strlen(source) + 1);
    if (str != NULL) {
        strcpy(str, source);
    }
    return str;
}
```

### 5. Utilizzare Strutture Dati con Gestione Automatica

```c
// Implementazione di una lista con gestione automatica della memoria
struct List {
    int *data;
    size_t size;
    size_t capacity;
};

struct List *list_create() {
    struct List *list = (struct List *)malloc(sizeof(struct List));
    if (list == NULL) {
        return NULL;
    }
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
    return list;
}

void list_destroy(struct List *list) {
    if (list != NULL) {
        free(list->data);
        free(list);
    }
}

// Utilizzo
struct List *list = list_create();
// Utilizzo della lista
list_destroy(list);
```

### 6. Evitare Allocazioni e Deallocazioni Frequenti

```c
// Invece di allocare e liberare memoria ad ogni iterazione
for (int i = 0; i < n; i++) {
    int *temp = (int *)malloc(size);
    // Utilizzo di temp
    free(temp);
}

// Allocare una volta sola
int *temp = (int *)malloc(size);
for (int i = 0; i < n; i++) {
    // Utilizzo di temp
}
free(temp);
```

### 7. Utilizzare Tecniche di Pooling per Allocazioni Frequenti

```c
#define POOL_SIZE 100

struct MemoryPool {
    void *blocks[POOL_SIZE];
    int used;
};

struct MemoryPool *create_pool(size_t block_size) {
    struct MemoryPool *pool = (struct MemoryPool *)malloc(sizeof(struct MemoryPool));
    if (pool == NULL) {
        return NULL;
    }
    
    pool->used = 0;
    for (int i = 0; i < POOL_SIZE; i++) {
        pool->blocks[i] = malloc(block_size);
        if (pool->blocks[i] == NULL) {
            // Liberazione dei blocchi già allocati in caso di errore
            for (int j = 0; j < i; j++) {
                free(pool->blocks[j]);
            }
            free(pool);
            return NULL;
        }
    }
    
    return pool;
}

void *pool_alloc(struct MemoryPool *pool) {
    if (pool->used < POOL_SIZE) {
        return pool->blocks[pool->used++];
    }
    return NULL; // Pool esaurito
}

void destroy_pool(struct MemoryPool *pool) {
    for (int i = 0; i < POOL_SIZE; i++) {
        free(pool->blocks[i]);
    }
    free(pool);
}
```

## Conclusione

La gestione corretta della memoria dinamica è fondamentale per creare programmi C robusti ed efficienti. Seguendo le best practices descritte in questo capitolo e utilizzando gli strumenti di debug appropriati, è possibile evitare molti dei problemi comuni associati all'allocazione dinamica.

Ricorda sempre di:
1. Controllare i valori di ritorno delle funzioni di allocazione
2. Liberare la memoria quando non è più necessaria
3. Impostare i puntatori a NULL dopo averli liberati
4. Utilizzare strumenti di debug per identificare problemi di memoria
5. Documentare chiaramente la proprietà e la gestione della memoria nel codice

Con queste pratiche, potrai sfruttare al meglio la potenza dell'allocazione dinamica minimizzando i rischi associati.