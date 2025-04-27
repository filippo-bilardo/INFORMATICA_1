# Memoria Condivisa tra Thread in C

## Introduzione

Una delle caratteristiche fondamentali dei thread è la capacità di condividere lo stesso spazio di memoria all'interno di un processo. Questa caratteristica offre vantaggi significativi in termini di efficienza e comunicazione, ma introduce anche sfide importanti legate alla sincronizzazione e alla coerenza dei dati.

## Concetti Fondamentali

### Spazio di Memoria Condiviso

A differenza dei processi, che hanno spazi di memoria isolati, i thread all'interno dello stesso processo condividono:

- **Segmento di codice**: tutti i thread eseguono lo stesso codice del programma
- **Segmento dati**: variabili globali e statiche
- **Heap**: memoria allocata dinamicamente
- **Risorse di sistema**: file aperti, socket, ecc.

Ogni thread ha però il proprio:

- **Stack**: variabili locali e parametri di funzione
- **Registri del processore**: incluso il contatore di programma

## Tipi di Dati Condivisi

### Variabili Globali

Le variabili globali sono accessibili da tutti i thread del programma.

```c
#include <pthread.h>
#include <stdio.h>

// Variabile globale condivisa tra tutti i thread
int counter = 0;

void* increment_counter(void* arg) {
    for (int i = 0; i < 1000; i++) {
        counter++; // Accesso non sincronizzato (problematico)
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    
    pthread_create(&thread1, NULL, increment_counter, NULL);
    pthread_create(&thread2, NULL, increment_counter, NULL);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    printf("Valore finale: %d\n", counter); // Probabilmente < 2000
    return 0;
}
```

### Memoria Allocata Dinamicamente

La memoria allocata con `malloc()`, `calloc()` o funzioni simili è condivisa tra i thread se il puntatore è accessibile a più thread.

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* shared_array;

void* write_to_array(void* arg) {
    int thread_id = *((int*)arg);
    int* array = (int*)shared_array;
    
    for (int i = 0; i < 100; i++) {
        array[thread_id * 100 + i] = thread_id;
    }
    return NULL;
}

int main() {
    pthread_t threads[5];
    int thread_ids[5];
    
    // Allocazione di memoria condivisa
    shared_array = malloc(5 * 100 * sizeof(int));
    
    for (int i = 0; i < 5; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, write_to_array, &thread_ids[i]);
    }
    
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Uso della memoria condivisa
    int* array = (int*)shared_array;
    for (int i = 0; i < 5; i++) {
        printf("Thread %d ha scritto: %d\n", i, array[i * 100]);
    }
    
    free(shared_array);
    return 0;
}
```

## Sfide della Memoria Condivisa

### Race Condition

Le race condition si verificano quando più thread accedono e modificano contemporaneamente gli stessi dati condivisi, portando a risultati imprevedibili.

### Coerenza della Cache

I processori moderni utilizzano cache per migliorare le prestazioni. Quando più core modificano gli stessi dati, possono verificarsi problemi di coerenza della cache.

### False Sharing

Il false sharing si verifica quando thread diversi accedono a variabili diverse che si trovano nella stessa linea di cache, causando un degrado delle prestazioni dovuto alla continua invalidazione della cache.

## Tecniche per la Gestione Sicura della Memoria Condivisa

### Sincronizzazione Esplicita

Utilizzo di mutex, semafori o altre primitive di sincronizzazione per proteggere l'accesso ai dati condivisi.

```c
#include <pthread.h>
#include <stdio.h>

int counter = 0;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void* safe_increment(void* arg) {
    for (int i = 0; i < 1000; i++) {
        pthread_mutex_lock(&counter_mutex);
        counter++;
        pthread_mutex_unlock(&counter_mutex);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    
    pthread_create(&thread1, NULL, safe_increment, NULL);
    pthread_create(&thread2, NULL, safe_increment, NULL);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    printf("Valore finale: %d\n", counter); // Esattamente 2000
    return 0;
}
```

### Variabili Thread-Local

Le variabili thread-local sono copie private di una variabile per ogni thread, evitando così la condivisione.

```c
#include <pthread.h>
#include <stdio.h>

// Dichiarazione di una variabile thread-local
__thread int thread_local_counter = 0;

void* increment_local_counter(void* arg) {
    for (int i = 0; i < 1000; i++) {
        thread_local_counter++; // Ogni thread ha la propria copia
    }
    printf("Thread %ld: contatore locale = %d\n", 
           pthread_self(), thread_local_counter);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    
    pthread_create(&thread1, NULL, increment_local_counter, NULL);
    pthread_create(&thread2, NULL, increment_local_counter, NULL);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    return 0;
}
```

### Operazioni Atomiche

Le operazioni atomiche garantiscono che un'operazione venga completata senza interruzioni da parte di altri thread.

```c
#include <pthread.h>
#include <stdio.h>
#include <stdatomic.h>

// Dichiarazione di una variabile atomica
atomic_int atomic_counter = 0;

void* atomic_increment(void* arg) {
    for (int i = 0; i < 1000; i++) {
        atomic_fetch_add(&atomic_counter, 1); // Incremento atomico
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    
    pthread_create(&thread1, NULL, atomic_increment, NULL);
    pthread_create(&thread2, NULL, atomic_increment, NULL);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    printf("Valore finale: %d\n", atomic_counter); // Esattamente 2000
    return 0;
}
```

## Modelli di Programmazione per la Memoria Condivisa

### Modello di Memoria Sequentially Consistent

In questo modello, tutte le operazioni di memoria appaiono come se fossero eseguite in un ordine sequenziale coerente con l'ordine del programma.

### Modello di Memoria Rilassato

I modelli di memoria rilassati permettono riordinamenti delle operazioni di memoria per migliorare le prestazioni, ma richiedono barriere di memoria esplicite per garantire la coerenza quando necessario.

## Best Practices

1. **Minimizzare i dati condivisi**: limitare la quantità di dati condivisi tra thread.
2. **Proteggere sempre i dati condivisi**: utilizzare meccanismi di sincronizzazione appropriati.
3. **Evitare il false sharing**: allineare i dati per evitare che variabili indipendenti condividano la stessa linea di cache.
4. **Preferire operazioni atomiche**: quando possibile, utilizzare operazioni atomiche invece di lock.
5. **Documentare l'accesso condiviso**: documentare chiaramente quali dati sono condivisi e come sono protetti.

## Conclusione

La memoria condivisa è una caratteristica potente della programmazione multi-thread, ma richiede attenzione e disciplina per essere utilizzata correttamente. Una buona comprensione dei meccanismi di sincronizzazione e dei modelli di memoria è essenziale per sviluppare applicazioni multi-thread robuste ed efficienti.

## Esercizi di Autovalutazione

1. Quali sono le differenze tra variabili globali e variabili thread-local?
2. Perché le race condition sono problematiche e come possono essere evitate?
3. Spiega il concetto di false sharing e come può influire sulle prestazioni.
4. Implementa un contatore thread-safe utilizzando (a) mutex, (b) operazioni atomiche, e confronta le prestazioni.
5. Descrivi un caso d'uso in cui la memoria condivisa tra thread offre vantaggi significativi rispetto ad altre forme di comunicazione tra processi.