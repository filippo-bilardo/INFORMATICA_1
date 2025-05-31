# Concetti Base della Memoria Dinamica in C

## Introduzione alla Memoria Dinamica

In C, la memoria può essere allocata in due modi principali: staticamente (in fase di compilazione) o dinamicamente (durante l'esecuzione del programma). L'allocazione dinamica della memoria è un concetto fondamentale che permette ai programmi di utilizzare la memoria in modo più flessibile ed efficiente.

### Memoria Statica vs Memoria Dinamica

#### Memoria Statica

La memoria statica viene allocata durante la compilazione del programma e ha una dimensione fissa che non può essere modificata durante l'esecuzione. Esempi di allocazione statica includono:

```c
int array[100];  // Array statico di 100 interi
char buffer[1024];  // Buffer statico di 1024 caratteri
```

Limitazioni della memoria statica:
- Dimensione fissa determinata in fase di compilazione
- Non può essere ridimensionata durante l'esecuzione
- Può portare a spreco di memoria se la dimensione allocata è maggiore di quella necessaria
- Può causare errori se la dimensione allocata è insufficiente

#### Memoria Dinamica

La memoria dinamica viene allocata durante l'esecuzione del programma e può essere ridimensionata o liberata secondo necessità. Questo offre maggiore flessibilità e un utilizzo più efficiente della memoria.

```c
int *array = malloc(100 * sizeof(int));  // Array dinamico di 100 interi
// Uso dell'array
free(array);  // Liberazione della memoria quando non è più necessaria
```

Vantaggi della memoria dinamica:
- Allocazione di memoria in base alle esigenze effettive del programma
- Possibilità di ridimensionare le strutture dati durante l'esecuzione
- Utilizzo più efficiente della memoria disponibile
- Creazione di strutture dati complesse la cui dimensione non è nota in anticipo

## Lo Stack e lo Heap

In C, la memoria è organizzata principalmente in due aree: lo stack e lo heap.

### Lo Stack

Lo stack è un'area di memoria gestita automaticamente dal sistema operativo, utilizzata per:
- Variabili locali
- Parametri delle funzioni
- Indirizzi di ritorno delle funzioni
- Gestione delle chiamate di funzione

Caratteristiche dello stack:
- Allocazione e deallocazione automatica (LIFO - Last In, First Out)
- Dimensione limitata (può causare stack overflow)
- Accesso molto veloce
- Gestito dal compilatore

### Lo Heap

Lo heap è un'area di memoria più grande utilizzata per l'allocazione dinamica:
- Memoria allocata con `malloc()`, `calloc()`, `realloc()`
- Gestita manualmente dal programmatore
- Persiste fino a quando non viene esplicitamente deallocata con `free()`

Caratteristiche dello heap:
- Allocazione e deallocazione manuale
- Dimensione molto più grande rispetto allo stack
- Accesso leggermente più lento rispetto allo stack
- Soggetto a frammentazione
- Richiede una gestione attenta per evitare memory leak

## Funzioni di Allocazione e Deallocazione della Memoria

Il linguaggio C fornisce diverse funzioni per la gestione della memoria dinamica, tutte definite nell'header `<stdlib.h>`.

### `malloc()`

La funzione `malloc()` (memory allocation) alloca un blocco di memoria di dimensione specificata e restituisce un puntatore al primo byte del blocco:

```c
void *malloc(size_t size);
```

Dove:
- `size` è la dimensione in byte del blocco di memoria da allocare
- Il valore restituito è un puntatore di tipo `void *` che può essere convertito a qualsiasi tipo di puntatore

Esempio:

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p;
    
    // Allocazione di memoria per un intero
    p = (int *)malloc(sizeof(int));
    
    if (p == NULL) {
        printf("Errore: memoria insufficiente\n");
        return 1;
    }
    
    // Utilizzo della memoria allocata
    *p = 42;
    printf("Valore: %d\n", *p);
    
    // Deallocazione della memoria
    free(p);
    
    return 0;
}
```

Importante:
- `malloc()` non inizializza la memoria allocata, quindi contiene valori casuali
- Restituisce `NULL` in caso di fallimento dell'allocazione
- È necessario controllare sempre il valore restituito prima di utilizzare la memoria

### `calloc()`

La funzione `calloc()` (contiguous allocation) alloca memoria per un array di elementi, inizializzando tutti i byte a zero:

```c
void *calloc(size_t nmemb, size_t size);
```

Dove:
- `nmemb` è il numero di elementi
- `size` è la dimensione in byte di ciascun elemento

Esempio:

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *array;
    int n = 5;
    
    // Allocazione di memoria per un array di 5 interi, inizializzati a zero
    array = (int *)calloc(n, sizeof(int));
    
    if (array == NULL) {
        printf("Errore: memoria insufficiente\n");
        return 1;
    }
    
    // Stampa dei valori (tutti zero)
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    // Deallocazione della memoria
    free(array);
    
    return 0;
}
```

Differenze tra `malloc()` e `calloc()`:
- `calloc()` inizializza la memoria a zero, `malloc()` no
- `calloc()` prende due parametri, `malloc()` uno solo
- `calloc()` può essere leggermente più lento a causa dell'inizializzazione

### `realloc()`

La funzione `realloc()` (reallocation) modifica la dimensione di un blocco di memoria precedentemente allocato:

```c
void *realloc(void *ptr, size_t size);
```

Dove:
- `ptr` è un puntatore al blocco di memoria da ridimensionare
- `size` è la nuova dimensione in byte

Esempio:

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *array;
    int n = 5;
    
    // Allocazione iniziale
    array = (int *)malloc(n * sizeof(int));
    
    if (array == NULL) {
        printf("Errore: memoria insufficiente\n");
        return 1;
    }
    
    // Inizializzazione dell'array
    for (int i = 0; i < n; i++) {
        array[i] = i + 1;
    }
    
    // Stampa dell'array originale
    printf("Array originale: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    // Ridimensionamento dell'array a 10 elementi
    n = 10;
    array = (int *)realloc(array, n * sizeof(int));
    
    if (array == NULL) {
        printf("Errore: memoria insufficiente\n");
        return 1;
    }
    
    // Inizializzazione dei nuovi elementi
    for (int i = 5; i < n; i++) {
        array[i] = i + 1;
    }
    
    // Stampa dell'array ridimensionato
    printf("Array ridimensionato: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    // Deallocazione della memoria
    free(array);
    
    return 0;
}
```

Comportamento di `realloc()`:
- Se `ptr` è NULL, funziona come `malloc()`
- Se `size` è 0 e `ptr` non è NULL, funziona come `free(ptr)` e restituisce NULL
- Se la nuova dimensione è maggiore, il contenuto originale viene preservato e i nuovi byte non sono inizializzati
- Se la nuova dimensione è minore, i dati in eccesso vengono persi
- Può spostare il blocco di memoria in una nuova posizione se necessario

### `free()`

La funzione `free()` dealloca un blocco di memoria precedentemente allocato con `malloc()`, `calloc()` o `realloc()`:

```c
void free(void *ptr);
```

Dove:
- `ptr` è un puntatore al blocco di memoria da deallocare

Esempio:

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = (int *)malloc(sizeof(int));
    
    if (p == NULL) {
        printf("Errore: memoria insufficiente\n");
        return 1;
    }
    
    *p = 42;
    printf("Valore: %d\n", *p);
    
    // Deallocazione della memoria
    free(p);
    
    // Importante: impostare il puntatore a NULL dopo free
    p = NULL;
    
    return 0;
}
```

Importante:
- Chiamare `free()` solo su puntatori restituiti da `malloc()`, `calloc()` o `realloc()`
- Non chiamare `free()` due volte sullo stesso puntatore (double free)
- Dopo aver chiamato `free()`, è buona pratica impostare il puntatore a NULL per evitare dangling pointers
- Non chiamare `free()` su puntatori NULL (è sicuro, ma inutile)

## Errori Comuni nella Gestione della Memoria

### Memory Leak (Perdita di Memoria)

Un memory leak si verifica quando si alloca memoria dinamicamente ma non la si dealloca quando non è più necessaria. Questo porta a un consumo progressivo di memoria che può esaurire le risorse del sistema.

Esempio di memory leak:

```c
#include <stdlib.h>

void funzione_con_leak() {
    int *p = (int *)malloc(sizeof(int));
    *p = 42;
    // Manca free(p) - memory leak!
}

int main() {
    for (int i = 0; i < 1000000; i++) {
        funzione_con_leak();  // Chiamata ripetuta causa un grande memory leak
    }
    return 0;
}
```

### Dangling Pointer (Puntatore Pendente)

Un dangling pointer è un puntatore che fa riferimento a una locazione di memoria che è stata deallocata o che non è più valida.

Esempio:

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = (int *)malloc(sizeof(int));
    *p = 42;
    
    free(p);  // p ora è un dangling pointer
    
    // Accesso pericoloso a memoria deallocata
    *p = 100;  // Comportamento indefinito!
    printf("%d\n", *p);  // Comportamento indefinito!
    
    return 0;
}
```

### Double Free (Doppia Deallocazione)

Il double free si verifica quando si chiama `free()` due volte sullo stesso puntatore, causando comportamenti indefiniti o crash.

Esempio:

```c
#include <stdlib.h>

int main() {
    int *p = (int *)malloc(sizeof(int));
    
    free(p);  // Prima deallocazione - corretto
    free(p);  // Seconda deallocazione - errore!
    
    return 0;
}
```

### Buffer Overflow

Il buffer overflow si verifica quando si scrive oltre i limiti di un'area di memoria allocata.

Esempio:

```c
#include <stdlib.h>

int main() {
    int *array = (int *)malloc(5 * sizeof(int));
    
    // Buffer overflow - scrittura oltre i limiti dell'array
    for (int i = 0; i < 10; i++) {
        array[i] = i;  // Accesso non valido per i >= 5
    }
    
    free(array);
    return 0;
}
```

## Best Practices per la Gestione della Memoria

1. **Controllare sempre il valore restituito dalle funzioni di allocazione**
   ```c
   int *p = (int *)malloc(sizeof(int));
   if (p == NULL) {
       // Gestione dell'errore
   }
   ```

2. **Deallocare sempre la memoria allocata dinamicamente quando non è più necessaria**
   ```c
   free(p);
   ```

3. **Impostare i puntatori a NULL dopo la deallocazione**
   ```c
   free(p);
   p = NULL;
   ```

4. **Utilizzare strumenti di debug della memoria** come Valgrind per identificare memory leak e altri problemi

5. **Evitare l'aritmetica dei puntatori complessa** che può portare a errori difficili da individuare

6. **Documentare chiaramente la proprietà della memoria** nei progetti complessi

7. **Utilizzare wrapper o strutture dati che gestiscono automaticamente la memoria** quando possibile

## Domande di Autovalutazione

1. Qual è la differenza principale tra memoria statica e memoria dinamica?
2. Quali sono le funzioni principali per l'allocazione e la deallocazione della memoria in C?
3. Qual è la differenza tra `malloc()` e `calloc()`?
4. Cosa fa la funzione `realloc()` e quando è utile utilizzarla?
5. Cosa sono i memory leak e come possono essere evitati?
6. Cosa sono i dangling pointer e perché sono pericolosi?
7. Perché è importante impostare un puntatore a NULL dopo averlo deallocato con `free()`?
8. Quali sono le best practices per una corretta gestione della memoria in C?

## Esercizi Proposti

1. Scrivi un programma che allochi dinamicamente un array di interi, chieda all'utente quanti elementi inserire, e poi calcoli la somma e la media degli elementi inseriti.

2. Implementa una funzione che crei una copia dinamica di una stringa (simile a `strdup()`).

3. Scrivi un programma che utilizzi `realloc()` per implementare un array dinamico che si espande automaticamente quando necessario.

4. Implementa una semplice struttura dati "stack" utilizzando l'allocazione dinamica della memoria, con funzioni per push, pop e visualizzazione degli elementi.

5. Scrivi un programma che allochi dinamicamente una matrice bidimensionale di dimensioni specificate dall'utente, la riempia con valori casuali e poi calcoli la somma di ogni riga e colonna.

Nella prossima sezione, esploreremo tecniche più avanzate di gestione della memoria e implementeremo strutture dati dinamiche complesse come liste concatenate, alberi e grafi.