# Funzioni di Allocazione della Memoria in C: malloc, calloc e realloc

## Introduzione

La gestione dinamica della memoria è una delle caratteristiche più potenti del linguaggio C. Permette ai programmi di allocare memoria durante l'esecuzione, consentendo strutture dati flessibili e un utilizzo efficiente delle risorse. In questo documento, esploreremo in dettaglio le tre principali funzioni di allocazione della memoria: `malloc()`, `calloc()` e `realloc()`.

## La Funzione malloc()

### Sintassi e Funzionamento

```c
void *malloc(size_t size);
```

La funzione `malloc()` (memory allocation) alloca un blocco contiguo di memoria non inizializzata di dimensione specificata in byte. Restituisce un puntatore al primo byte del blocco allocato, o `NULL` se l'allocazione fallisce.

### Parametri

- `size`: dimensione in byte del blocco di memoria da allocare

### Valore di Ritorno

- Un puntatore di tipo `void *` al blocco di memoria allocato
- `NULL` in caso di fallimento dell'allocazione

### Esempi di Utilizzo

#### Allocazione di un Singolo Elemento

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p;
    
    // Allocazione di memoria per un intero
    p = (int *)malloc(sizeof(int));
    
    if (p == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return 1;
    }
    
    *p = 42;
    printf("Valore: %d\n", *p);
    
    free(p);  // Importante: liberare la memoria quando non serve più
    return 0;
}
```

#### Allocazione di un Array

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *array;
    int n = 10;
    
    // Allocazione di memoria per un array di n interi
    array = (int *)malloc(n * sizeof(int));
    
    if (array == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return 1;
    }
    
    // Inizializzazione dell'array
    for (int i = 0; i < n; i++) {
        array[i] = i * 10;
    }
    
    // Utilizzo dell'array
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    free(array);
    return 0;
}
```

### Considerazioni Importanti

- La memoria allocata con `malloc()` non è inizializzata e contiene valori casuali
- È fondamentale controllare sempre il valore restituito prima di utilizzare la memoria
- La memoria allocata con `malloc()` deve essere sempre liberata con `free()` quando non è più necessaria
- L'allocazione eccessiva di memoria può causare problemi di prestazioni o errori di esaurimento memoria

## La Funzione calloc()

### Sintassi e Funzionamento

```c
void *calloc(size_t nmemb, size_t size);
```

La funzione `calloc()` (contiguous allocation) alloca memoria per un array di elementi, inizializzando tutti i byte a zero.

### Parametri

- `nmemb`: numero di elementi da allocare
- `size`: dimensione in byte di ciascun elemento

### Valore di Ritorno

- Un puntatore di tipo `void *` al blocco di memoria allocato e inizializzato
- `NULL` in caso di fallimento dell'allocazione

### Esempi di Utilizzo

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *array;
    int n = 10;
    
    // Allocazione di memoria per un array di n interi, inizializzati a zero
    array = (int *)calloc(n, sizeof(int));
    
    if (array == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return 1;
    }
    
    // Stampa dei valori (tutti zero)
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    free(array);
    return 0;
}
```

### Differenze tra malloc() e calloc()

| Caratteristica | malloc() | calloc() |
|----------------|----------|----------|
| Inizializzazione | Non inizializza la memoria | Inizializza tutti i byte a zero |
| Parametri | Un parametro (dimensione totale) | Due parametri (numero di elementi e dimensione di ciascuno) |
| Prestazioni | Leggermente più veloce | Leggermente più lento a causa dell'inizializzazione |
| Uso tipico | Quando l'inizializzazione non è necessaria | Quando è richiesta l'inizializzazione a zero |

## La Funzione realloc()

### Sintassi e Funzionamento

```c
void *realloc(void *ptr, size_t size);
```

La funzione `realloc()` (reallocation) modifica la dimensione di un blocco di memoria precedentemente allocato con `malloc()`, `calloc()` o `realloc()`.

### Parametri

- `ptr`: puntatore al blocco di memoria da ridimensionare
- `size`: nuova dimensione in byte

### Valore di Ritorno

- Un puntatore al blocco di memoria ridimensionato (che può essere diverso da `ptr`)
- `NULL` in caso di fallimento, ma il blocco originale rimane valido

### Comportamento

1. Se `ptr` è `NULL`, `realloc()` si comporta come `malloc(size)`
2. Se `size` è 0 e `ptr` non è `NULL`, `realloc()` si comporta come `free(ptr)` e restituisce `NULL`
3. Se `size` è maggiore della dimensione originale, il blocco viene espanso e i dati originali vengono preservati
4. Se `size` è minore della dimensione originale, il blocco viene ridotto e solo i primi `size` byte vengono preservati
5. Se non è possibile espandere il blocco nella sua posizione attuale, `realloc()` alloca un nuovo blocco, copia i dati e libera il blocco originale

### Esempi di Utilizzo

#### Espansione di un Array

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *array;
    int n = 5;
    
    // Allocazione iniziale
    array = (int *)malloc(n * sizeof(int));
    
    if (array == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return 1;
    }
    
    // Inizializzazione dell'array
    for (int i = 0; i < n; i++) {
        array[i] = i * 10;
    }
    
    // Espansione dell'array a 10 elementi
    int new_n = 10;
    int *new_array = (int *)realloc(array, new_n * sizeof(int));
    
    if (new_array == NULL) {
        printf("Errore: riallocazione memoria fallita\n");
        free(array);  // Importante: liberare la memoria originale in caso di fallimento
        return 1;
    }
    
    array = new_array;  // Aggiornamento del puntatore
    
    // Inizializzazione dei nuovi elementi
    for (int i = n; i < new_n; i++) {
        array[i] = i * 10;
    }
    
    // Stampa dell'array espanso
    for (int i = 0; i < new_n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    free(array);
    return 0;
}
```

### Considerazioni Importanti

- È fondamentale aggiornare sempre il puntatore originale con il valore restituito da `realloc()`
- Se `realloc()` fallisce, restituisce `NULL` ma il blocco originale rimane valido e deve essere liberato
- Evitare di usare il puntatore originale dopo la chiamata a `realloc()`, poiché potrebbe non essere più valido
- `realloc()` non inizializza la memoria aggiuntiva allocata

## Pratiche Consigliate

### Controllo degli Errori

È essenziale controllare sempre il valore restituito dalle funzioni di allocazione della memoria:

```c
int *p = (int *)malloc(sizeof(int));
if (p == NULL) {
    // Gestione dell'errore
    fprintf(stderr, "Errore: allocazione memoria fallita\n");
    exit(EXIT_FAILURE);
}
```

### Calcolo Corretto delle Dimensioni

Utilizzare sempre `sizeof` per calcolare la dimensione corretta:

```c
// Corretto
int *array = (int *)malloc(n * sizeof(int));

// Errato (non portabile)
int *array = (int *)malloc(n * 4);  // Assume che sizeof(int) sia 4
```

### Evitare Memory Leak

Liberare sempre la memoria quando non è più necessaria:

```c
int *p = (int *)malloc(sizeof(int));
// Utilizzo di p
free(p);  // Liberazione della memoria
p = NULL;  // Buona pratica: impostare il puntatore a NULL dopo free
```

### Gestione Sicura di realloc()

Utilizzare un puntatore temporaneo per `realloc()` per evitare memory leak in caso di fallimento:

```c
int *temp = (int *)realloc(array, new_size);
if (temp != NULL) {
    array = temp;
} else {
    // Gestione dell'errore senza perdere il puntatore originale
    free(array);
    array = NULL;
}
```

## Conclusione

Le funzioni `malloc()`, `calloc()` e `realloc()` sono strumenti potenti per la gestione dinamica della memoria in C. Utilizzate correttamente, consentono di creare programmi flessibili ed efficienti. Tuttavia, richiedono attenzione e disciplina per evitare problemi come memory leak, accessi a memoria non valida e frammentazione della memoria.

Ricorda sempre di:
1. Controllare i valori restituiti dalle funzioni di allocazione
2. Liberare la memoria quando non è più necessaria
3. Utilizzare la funzione di allocazione più appropriata per ogni situazione
4. Gestire correttamente gli errori di allocazione

Con queste pratiche, potrai sfruttare al meglio la potenza della gestione dinamica della memoria in C.