# Deallocazione della Memoria e Gestione Avanzata in C

## La Funzione free()

### Sintassi e Funzionamento

```c
void free(void *ptr);
```

La funzione `free()` libera un blocco di memoria precedentemente allocato con `malloc()`, `calloc()` o `realloc()`, rendendo quella memoria disponibile per future allocazioni.

### Parametri

- `ptr`: puntatore al blocco di memoria da liberare

### Valore di Ritorno

- Nessuno (tipo `void`)

### Esempi di Utilizzo

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = (int *)malloc(sizeof(int));
    
    if (p == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return 1;
    }
    
    *p = 42;
    printf("Valore: %d\n", *p);
    
    free(p);  // Liberazione della memoria
    p = NULL; // Buona pratica: impostare il puntatore a NULL dopo free
    
    return 0;
}
```

### Comportamento e Regole

1. Se `ptr` è `NULL`, `free()` non fa nulla
2. Se `ptr` non è stato ottenuto da una precedente chiamata a `malloc()`, `calloc()` o `realloc()`, il comportamento è indefinito
3. Se `ptr` è già stato liberato con `free()`, chiamare nuovamente `free()` su di esso causa un comportamento indefinito (double free)
4. Dopo la chiamata a `free()`, il puntatore diventa un "dangling pointer" (puntatore pendente) e non deve essere dereferenziato

## Problemi Comuni nella Gestione della Memoria

### Memory Leak (Perdita di Memoria)

Un memory leak si verifica quando un programma alloca memoria dinamicamente ma non la libera quando non è più necessaria. Questo porta a un consumo progressivo di memoria che può eventualmente esaurire le risorse del sistema.

#### Esempio di Memory Leak

```c
#include <stdlib.h>

void funzione_con_leak() {
    int *p = (int *)malloc(sizeof(int));
    *p = 42;
    // Manca free(p) - Memory leak!
    // La memoria allocata non viene mai liberata
}

int main() {
    for (int i = 0; i < 1000; i++) {
        funzione_con_leak();  // Chiama la funzione 1000 volte
    }
    return 0;
}
```

#### Come Evitare Memory Leak

- Liberare sempre la memoria allocata quando non è più necessaria
- Tenere traccia di tutti i puntatori a memoria allocata dinamicamente
- Utilizzare strumenti come Valgrind per rilevare memory leak
- Seguire il principio "chi alloca, libera"

### Dangling Pointer (Puntatore Pendente)

Un dangling pointer è un puntatore che fa riferimento a una locazione di memoria che è stata liberata o non è più valida.

#### Esempio di Dangling Pointer

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = (int *)malloc(sizeof(int));
    *p = 42;
    
    free(p);  // La memoria viene liberata
    
    // p è ora un dangling pointer
    *p = 100;  // ERRORE: comportamento indefinito
    printf("%d\n", *p);  // ERRORE: comportamento indefinito
    
    return 0;
}
```

#### Come Evitare Dangling Pointer

- Impostare i puntatori a `NULL` dopo averli liberati
- Non dereferenziare puntatori dopo averli liberati
- Utilizzare strumenti di analisi statica per rilevare potenziali dangling pointer

### Double Free (Doppia Liberazione)

Un double free si verifica quando si tenta di liberare la stessa memoria più di una volta.

#### Esempio di Double Free

```c
#include <stdlib.h>

int main() {
    int *p = (int *)malloc(sizeof(int));
    
    free(p);  // Prima liberazione - OK
    free(p);  // Seconda liberazione - ERRORE: double free
    
    return 0;
}
```

#### Come Evitare Double Free

- Impostare i puntatori a `NULL` dopo averli liberati
- Controllare se un puntatore è `NULL` prima di chiamare `free()`
- Seguire una chiara strategia di proprietà della memoria

### Buffer Overflow

Un buffer overflow si verifica quando un programma scrive dati oltre i limiti di un buffer allocato.

#### Esempio di Buffer Overflow

```c
#include <stdlib.h>
#include <string.h>

int main() {
    char *buffer = (char *)malloc(10 * sizeof(char));
    
    // Tentativo di copiare 20 caratteri in un buffer di 10
    strcpy(buffer, "Questa stringa è troppo lunga per il buffer");  // ERRORE: buffer overflow
    
    free(buffer);
    return 0;
}
```

#### Come Evitare Buffer Overflow

- Utilizzare funzioni sicure come `strncpy()` invece di `strcpy()`
- Controllare sempre i limiti degli array e dei buffer
- Allocare memoria sufficiente per i dati previsti
- Utilizzare strumenti di analisi statica e dinamica

## Tecniche Avanzate di Gestione della Memoria

### Smart Pointer in C

Anche se C non supporta nativamente gli smart pointer come C++, è possibile implementare un concetto simile utilizzando strutture e funzioni.

```c
#include <stdio.h>
#include <stdlib.h>

// Struttura per uno smart pointer
typedef struct {
    int *ptr;
    int *ref_count;
} SmartPointer;

// Funzione per creare uno smart pointer
SmartPointer create_smart_pointer(int value) {
    SmartPointer sp;
    sp.ptr = (int *)malloc(sizeof(int));
    sp.ref_count = (int *)malloc(sizeof(int));
    
    if (sp.ptr != NULL && sp.ref_count != NULL) {
        *sp.ptr = value;
        *sp.ref_count = 1;
    }
    
    return sp;
}

// Funzione per copiare uno smart pointer
SmartPointer copy_smart_pointer(SmartPointer sp) {
    if (sp.ref_count != NULL) {
        (*sp.ref_count)++;
    }
    return sp;
}

// Funzione per liberare uno smart pointer
void free_smart_pointer(SmartPointer *sp) {
    if (sp->ref_count != NULL) {
        (*sp->ref_count)--;
        
        if (*sp->ref_count == 0) {
            free(sp->ptr);
            free(sp->ref_count);
        }
        
        sp->ptr = NULL;
        sp->ref_count = NULL;
    }
}

int main() {
    // Creazione di uno smart pointer
    SmartPointer sp1 = create_smart_pointer(42);
    printf("Valore: %d, Conteggio riferimenti: %d\n", *sp1.ptr, *sp1.ref_count);
    
    // Copia dello smart pointer
    SmartPointer sp2 = copy_smart_pointer(sp1);
    printf("Valore: %d, Conteggio riferimenti: %d\n", *sp2.ptr, *sp2.ref_count);
    
    // Liberazione del primo smart pointer
    free_smart_pointer(&sp1);
    printf("Conteggio riferimenti dopo free di sp1: %d\n", *sp2.ref_count);
    
    // Liberazione del secondo smart pointer
    free_smart_pointer(&sp2);
    
    return 0;
}
```

### Pool di Memoria

Un pool di memoria è una tecnica che pre-alloca un grande blocco di memoria e lo gestisce internamente per allocazioni più piccole, riducendo la frammentazione e migliorando le prestazioni.

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define POOL_SIZE 1024
#define BLOCK_SIZE 16

typedef struct {
    char memory[POOL_SIZE];
    bool used[POOL_SIZE / BLOCK_SIZE];
} MemoryPool;

// Inizializza il pool di memoria
void init_pool(MemoryPool *pool) {
    for (int i = 0; i < POOL_SIZE / BLOCK_SIZE; i++) {
        pool->used[i] = false;
    }
}

// Alloca memoria dal pool
void *pool_alloc(MemoryPool *pool, size_t size) {
    if (size > BLOCK_SIZE) {
        return NULL;  // Dimensione troppo grande per un blocco
    }
    
    for (int i = 0; i < POOL_SIZE / BLOCK_SIZE; i++) {
        if (!pool->used[i]) {
            pool->used[i] = true;
            return &pool->memory[i * BLOCK_SIZE];
        }
    }
    
    return NULL;  // Pool pieno
}

// Libera memoria nel pool
void pool_free(MemoryPool *pool, void *ptr) {
    if (ptr == NULL) return;
    
    // Calcola l'indice del blocco
    ptrdiff_t offset = (char *)ptr - pool->memory;
    int index = offset / BLOCK_SIZE;
    
    if (index >= 0 && index < POOL_SIZE / BLOCK_SIZE) {
        pool->used[index] = false;
    }
}

int main() {
    MemoryPool pool;
    init_pool(&pool);
    
    // Allocazione di memoria dal pool
    int *p1 = (int *)pool_alloc(&pool, sizeof(int));
    int *p2 = (int *)pool_alloc(&pool, sizeof(int));
    
    if (p1 != NULL && p2 != NULL) {
        *p1 = 42;
        *p2 = 100;
        
        printf("p1: %d, p2: %d\n", *p1, *p2);
        
        // Liberazione della memoria
        pool_free(&pool, p1);
        pool_free(&pool, p2);
    }
    
    return 0;
}
```

## Strumenti per il Debug della Memoria

### Valgrind

Valgrind è uno strumento potente per il debug della memoria che può rilevare memory leak, accessi a memoria non valida, utilizzo di memoria non inizializzata e altro ancora.

```bash
# Compilazione con informazioni di debug
gcc -g mio_programma.c -o mio_programma

# Esecuzione con Valgrind
valgrind --leak-check=full ./mio_programma
```

### AddressSanitizer

AddressSanitizer è uno strumento di rilevamento degli errori di memoria integrato nei compilatori moderni come GCC e Clang.

```bash
# Compilazione con AddressSanitizer
gcc -fsanitize=address -g mio_programma.c -o mio_programma

# Esecuzione normale (gli errori verranno segnalati automaticamente)
./mio_programma
```

## Conclusione

La gestione corretta della memoria è fondamentale per scrivere programmi C robusti ed efficienti. La funzione `free()` è essenziale per evitare memory leak, ma deve essere utilizzata con attenzione per evitare problemi come dangling pointer e double free.

Le tecniche avanzate come smart pointer e pool di memoria possono aiutare a gestire la memoria in modo più sicuro ed efficiente, mentre strumenti come Valgrind e AddressSanitizer sono preziosi per identificare e risolvere problemi di memoria.

Ricorda sempre di:
1. Liberare tutta la memoria allocata dinamicamente quando non è più necessaria
2. Impostare i puntatori a `NULL` dopo averli liberati
3. Controllare i valori restituiti dalle funzioni di allocazione
4. Utilizzare strumenti di debug della memoria per identificare problemi
5. Seguire pratiche di programmazione sicure per evitare buffer overflow e altri errori di memoria

Con queste pratiche, potrai scrivere programmi C che gestiscono la memoria in modo efficiente e affidabile.