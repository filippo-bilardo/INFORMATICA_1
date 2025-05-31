# Funzioni di Allocazione e Liberazione della Memoria

In C, la gestione dinamica della memoria viene effettuata attraverso un insieme di funzioni della libreria standard. Queste funzioni permettono di allocare, ridimensionare e liberare memoria durante l'esecuzione del programma.

## La Funzione `malloc()`

### Sintassi e Utilizzo

```c
#include <stdlib.h>
void *malloc(size_t size);
```

La funzione `malloc()` (memory allocation) alloca un blocco di memoria di dimensione specificata in byte e restituisce un puntatore al primo byte del blocco allocato.

### Esempio Base

```c
int *p;
p = (int *)malloc(sizeof(int)); // Alloca memoria per un intero
if (p == NULL) {
    // Gestione dell'errore di allocazione
    fprintf(stderr, "Errore: impossibile allocare memoria\n");
    exit(EXIT_FAILURE);
}
*p = 42; // Utilizzo della memoria allocata
free(p); // Liberazione della memoria quando non più necessaria
```

### Allocazione di Array

```c
int *array;
int n = 10;
array = (int *)malloc(n * sizeof(int)); // Alloca memoria per n interi
if (array == NULL) {
    // Gestione dell'errore
    fprintf(stderr, "Errore: impossibile allocare memoria\n");
    exit(EXIT_FAILURE);
}
// Utilizzo dell'array
for (int i = 0; i < n; i++) {
    array[i] = i * 2;
}
// Liberazione della memoria
free(array);
```

### Caratteristiche di `malloc()`

- Restituisce un puntatore di tipo `void *` che deve essere convertito al tipo appropriato
- La memoria allocata non viene inizializzata (contiene valori casuali)
- Restituisce `NULL` in caso di fallimento dell'allocazione
- La memoria allocata rimane valida fino a quando non viene liberata con `free()`

## La Funzione `calloc()`

### Sintassi e Utilizzo

```c
#include <stdlib.h>
void *calloc(size_t nmemb, size_t size);
```

La funzione `calloc()` (contiguous allocation) alloca memoria per un array di `nmemb` elementi, ciascuno di dimensione `size` byte, e inizializza tutti i byte a zero.

### Esempio Base

```c
int *array;
int n = 10;
array = (int *)calloc(n, sizeof(int)); // Alloca e inizializza a zero n interi
if (array == NULL) {
    // Gestione dell'errore
    fprintf(stderr, "Errore: impossibile allocare memoria\n");
    exit(EXIT_FAILURE);
}
// Tutti gli elementi sono già inizializzati a zero
for (int i = 0; i < n; i++) {
    printf("%d ", array[i]); // Stamperà "0 0 0 0 0 0 0 0 0 0"
}
free(array);
```

### Differenze tra `malloc()` e `calloc()`

1. **Inizializzazione**: `calloc()` inizializza la memoria a zero, `malloc()` no
2. **Parametri**: `calloc()` prende due parametri (numero di elementi e dimensione di ciascuno), `malloc()` prende un singolo parametro (dimensione totale in byte)
3. **Calcolo della dimensione**: `calloc()` calcola internamente la dimensione totale moltiplicando i due parametri
4. **Prestazioni**: `calloc()` può essere più lento di `malloc()` a causa dell'inizializzazione a zero

## La Funzione `realloc()`

### Sintassi e Utilizzo

```c
#include <stdlib.h>
void *realloc(void *ptr, size_t size);
```

La funzione `realloc()` (reallocation) cambia la dimensione del blocco di memoria puntato da `ptr` alla dimensione specificata da `size`.

### Esempio Base

```c
int *array;
int n = 5;
// Allocazione iniziale
array = (int *)malloc(n * sizeof(int));
if (array == NULL) {
    fprintf(stderr, "Errore: impossibile allocare memoria\n");
    exit(EXIT_FAILURE);
}
// Inizializzazione
for (int i = 0; i < n; i++) {
    array[i] = i;
}
// Ridimensionamento
int nuovo_n = 10;
int *nuovo_array = (int *)realloc(array, nuovo_n * sizeof(int));
if (nuovo_array == NULL) {
    fprintf(stderr, "Errore: impossibile ridimensionare la memoria\n");
    free(array); // Importante: liberare la memoria originale in caso di errore
    exit(EXIT_FAILURE);
}
array = nuovo_array; // Aggiorna il puntatore
// I primi n elementi sono preservati, inizializziamo i nuovi
for (int i = n; i < nuovo_n; i++) {
    array[i] = i;
}
// Liberazione della memoria
free(array);
```

### Comportamento di `realloc()`

- Se `ptr` è `NULL`, `realloc()` si comporta come `malloc()`
- Se `size` è 0 e `ptr` non è `NULL`, `realloc()` si comporta come `free()`
- Se la nuova dimensione è maggiore, il contenuto originale viene preservato e la memoria aggiuntiva non viene inizializzata
- Se la nuova dimensione è minore, il contenuto viene troncato
- Se non è possibile espandere il blocco esistente, `realloc()` alloca un nuovo blocco, copia il contenuto e libera il blocco originale
- Restituisce `NULL` in caso di fallimento, ma il blocco originale rimane valido

### Casi Speciali di `realloc()`

```c
// Comportamento come malloc()
int *p = (int *)realloc(NULL, sizeof(int));

// Comportamento come free()
realloc(p, 0);
```

## La Funzione `free()`

### Sintassi e Utilizzo

```c
#include <stdlib.h>
void free(void *ptr);
```

La funzione `free()` libera il blocco di memoria puntato da `ptr`, che deve essere stato restituito da una precedente chiamata a `malloc()`, `calloc()` o `realloc()`.

### Esempio Base

```c
int *p = (int *)malloc(sizeof(int));
if (p != NULL) {
    *p = 42;
    // Utilizzo della memoria
    free(p); // Liberazione della memoria
    p = NULL; // Buona pratica: impostare il puntatore a NULL dopo free
}
```

### Comportamento di `free()`

- Non restituisce alcun valore
- Se `ptr` è `NULL`, non fa nulla
- Liberare memoria già liberata (double free) causa comportamenti indefiniti
- Accedere a memoria dopo averla liberata (dangling pointer) causa comportamenti indefiniti
- Non riduce la dimensione del processo, ma rende la memoria disponibile per future allocazioni

## Pattern Comuni di Utilizzo

### Allocazione e Controllo

```c
void *allocate_memory(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Errore: impossibile allocare %zu byte\n", size);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

// Utilizzo
int *array = (int *)allocate_memory(10 * sizeof(int));
```

### Ridimensionamento Sicuro

```c
void *safe_realloc(void *ptr, size_t size) {
    void *new_ptr = realloc(ptr, size);
    if (new_ptr == NULL && size > 0) {
        fprintf(stderr, "Errore: impossibile ridimensionare la memoria\n");
        free(ptr); // Libera la memoria originale
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

// Utilizzo
array = safe_realloc(array, nuovo_n * sizeof(int));
```

### Liberazione e Reset

```c
void safe_free(void **ptr) {
    if (ptr != NULL && *ptr != NULL) {
        free(*ptr);
        *ptr = NULL; // Previene dangling pointer
    }
}

// Utilizzo
int *p = (int *)malloc(sizeof(int));
// Utilizzo di p
safe_free((void **)&p); // p sarà NULL dopo questa chiamata
```

## Allocazione di Strutture Dati Complesse

### Matrici Dinamiche

```c
// Allocazione di una matrice m x n
int **allocate_matrix(int m, int n) {
    int **matrix = (int **)malloc(m * sizeof(int *));
    if (matrix == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < m; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
        if (matrix[i] == NULL) {
            // Liberazione della memoria già allocata in caso di errore
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }
    
    return matrix;
}

// Liberazione di una matrice m x n
void free_matrix(int **matrix, int m) {
    if (matrix == NULL) {
        return;
    }
    
    for (int i = 0; i < m; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
```

### Allocazione Contigua di Matrici

```c
// Allocazione di una matrice m x n in memoria contigua
int **allocate_contiguous_matrix(int m, int n) {
    int **matrix = (int **)malloc(m * sizeof(int *));
    if (matrix == NULL) {
        return NULL;
    }
    
    // Allocazione di un unico blocco per tutti gli elementi
    int *data = (int *)malloc(m * n * sizeof(int));
    if (data == NULL) {
        free(matrix);
        return NULL;
    }
    
    // Impostazione dei puntatori alle righe
    for (int i = 0; i < m; i++) {
        matrix[i] = data + (i * n);
    }
    
    return matrix;
}

// Liberazione di una matrice contigua
void free_contiguous_matrix(int **matrix) {
    if (matrix == NULL) {
        return;
    }
    
    // Libera il blocco di dati (prima riga)
    free(matrix[0]);
    // Libera l'array di puntatori
    free(matrix);
}
```

## Conclusione

Le funzioni `malloc()`, `calloc()`, `realloc()` e `free()` sono strumenti fondamentali per la gestione dinamica della memoria in C. Utilizzate correttamente, permettono di creare programmi flessibili ed efficienti che utilizzano la memoria in modo ottimale.

Tuttavia, è importante ricordare che la gestione manuale della memoria richiede attenzione e disciplina. Errori come memory leak, dangling pointers e double free possono causare problemi difficili da diagnosticare. Nel prossimo capitolo, esploreremo le tecniche per gestire questi errori e le best practices per una gestione sicura ed efficiente della memoria dinamica.