# Sincronizzazione tra Thread in C

## Introduzione

La sincronizzazione è un aspetto cruciale della programmazione multi-thread. Quando più thread condividono risorse, è necessario garantire che l'accesso a queste risorse avvenga in modo coordinato per evitare problemi come race condition, deadlock e altri comportamenti imprevedibili.

## Problemi di Sincronizzazione

### Race Condition

Una race condition si verifica quando il risultato di un'operazione dipende dall'ordine di esecuzione dei thread. Consideriamo un esempio:

```c
// Variabile globale condivisa
int counter = 0;

void* increment_counter(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        counter++;  // Operazione non atomica!
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    
    pthread_create(&thread1, NULL, increment_counter, NULL);
    pthread_create(&thread2, NULL, increment_counter, NULL);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    printf("Valore finale del contatore: %d\n", counter);
    // Il valore atteso sarebbe 2000000, ma sarà probabilmente inferiore
    
    return 0;
}
```

### Deadlock

Un deadlock si verifica quando due o più thread si bloccano a vicenda, ognuno in attesa di una risorsa detenuta dall'altro.

```c
pthread_mutex_t mutex1, mutex2;

void* thread_function1(void* arg) {
    pthread_mutex_lock(&mutex1);  // Acquisisce mutex1
    sleep(1);  // Simula un'operazione
    pthread_mutex_lock(&mutex2);  // Tenta di acquisire mutex2
    
    // Codice critico
    
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);
    return NULL;
}

void* thread_function2(void* arg) {
    pthread_mutex_lock(&mutex2);  // Acquisisce mutex2
    sleep(1);  // Simula un'operazione
    pthread_mutex_lock(&mutex1);  // Tenta di acquisire mutex1
    
    // Codice critico
    
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
    return NULL;
}
```

## Meccanismi di Sincronizzazione

### Mutex (Mutual Exclusion)

I mutex sono il meccanismo di sincronizzazione più comune. Garantiscono che solo un thread alla volta possa accedere a una risorsa condivisa.

```c
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int shared_resource = 0;

void* safe_increment(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);  // Acquisisce il mutex
        shared_resource++;  // Sezione critica
        pthread_mutex_unlock(&mutex);  // Rilascia il mutex
    }
    return NULL;
}
```

#### Inizializzazione e Distruzione di Mutex

```c
// Inizializzazione statica
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Inizializzazione dinamica
pthread_mutex_t mutex;
pthread_mutex_init(&mutex, NULL);

// Distruzione
pthread_mutex_destroy(&mutex);
```

#### Tipi di Mutex

POSIX supporta diversi tipi di mutex:

- `PTHREAD_MUTEX_NORMAL`: Mutex standard
- `PTHREAD_MUTEX_ERRORCHECK`: Rileva errori come il doppio lock
- `PTHREAD_MUTEX_RECURSIVE`: Permette lock ricorsivi dallo stesso thread
- `PTHREAD_MUTEX_DEFAULT`: Comportamento predefinito (spesso equivalente a NORMAL)

```c
pthread_mutexattr_t attr;
pthread_mutexattr_init(&attr);
pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

pthread_mutex_t recursive_mutex;
pthread_mutex_init(&recursive_mutex, &attr);

pthread_mutexattr_destroy(&attr);
```

### Variabili di Condizione

Le variabili di condizione permettono ai thread di sincronizzarsi in base a condizioni specifiche.

```c
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int data_ready = 0;

void* producer(void* arg) {
    // Produce dati
    pthread_mutex_lock(&mutex);
    data_ready = 1;
    pthread_cond_signal(&cond);  // Segnala che i dati sono pronti
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* consumer(void* arg) {
    pthread_mutex_lock(&mutex);
    while (!data_ready) {
        pthread_cond_wait(&cond, &mutex);  // Attende il segnale
    }
    // Consuma i dati
    pthread_mutex_unlock(&mutex);
    return NULL;
}
```

#### Funzioni per Variabili di Condizione

- `pthread_cond_init()`: Inizializza una variabile di condizione
- `pthread_cond_destroy()`: Distrugge una variabile di condizione
- `pthread_cond_wait()`: Attende un segnale sulla variabile di condizione
- `pthread_cond_timedwait()`: Attende con timeout
- `pthread_cond_signal()`: Sveglia un thread in attesa
- `pthread_cond_broadcast()`: Sveglia tutti i thread in attesa

### Semafori

I semafori sono contatori che controllano l'accesso a risorse condivise.

```c
#include <semaphore.h>

sem_t semaphore;

int main() {
    // Inizializza il semaforo con valore 1 (semaforo binario)
    sem_init(&semaphore, 0, 1);
    
    // Uso del semaforo
    sem_wait(&semaphore);  // Decrementa il semaforo
    // Sezione critica
    sem_post(&semaphore);  // Incrementa il semaforo
    
    // Distruzione del semaforo
    sem_destroy(&semaphore);
    
    return 0;
}
```

#### Tipi di Semafori

- **Semaforo binario**: Può assumere solo i valori 0 e 1, simile a un mutex
- **Semaforo contatore**: Può assumere valori maggiori di 1, utile per gestire pool di risorse

### Read-Write Locks

I read-write locks permettono accessi concorrenti in lettura ma esclusivi in scrittura.

```c
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

void* reader(void* arg) {
    pthread_rwlock_rdlock(&rwlock);  // Lock in lettura
    // Operazioni di lettura
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

void* writer(void* arg) {
    pthread_rwlock_wrlock(&rwlock);  // Lock in scrittura
    // Operazioni di scrittura
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}
```

### Barriere

Le barriere sincronizzano un gruppo di thread in un punto specifico.

```c
pthread_barrier_t barrier;

int main() {
    int num_threads = 5;
    pthread_barrier_init(&barrier, NULL, num_threads);
    
    // Creazione dei thread
    
    pthread_barrier_destroy(&barrier);
    return 0;
}

void* thread_function(void* arg) {
    // Prima fase
    
    pthread_barrier_wait(&barrier);  // Attende che tutti i thread raggiungano questo punto
    
    // Seconda fase
    
    return NULL;
}
```

## Tecniche di Sincronizzazione Avanzate

### Lock-Free Programming

La programmazione lock-free utilizza operazioni atomiche per evitare l'uso di mutex.

```c
#include <stdatomic.h>

atomic_int counter = 0;

void* increment_counter(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        atomic_fetch_add(&counter, 1);  // Incremento atomico
    }
    return NULL;
}
```

### Spinlock

Gli spinlock sono mutex che "girano" in un ciclo invece di bloccare il thread.

```c
pthread_spinlock_t spinlock;

int main() {
    pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);
    
    pthread_spin_lock(&spinlock);
    // Sezione critica (breve!)
    pthread_spin_unlock(&spinlock);
    
    pthread_spin_destroy(&spinlock);
    return 0;
}
```

## Strategie per Evitare Problemi di Sincronizzazione

### Prevenzione del Deadlock

1. **Ordinamento delle risorse**: Acquisire sempre le risorse in un ordine predefinito
2. **Timeout**: Utilizzare funzioni con timeout per l'acquisizione delle risorse
3. **Rilevamento**: Implementare algoritmi di rilevamento del deadlock
4. **Evitare lock nidificati**: Minimizzare l'uso di lock multipli contemporaneamente

### Minimizzazione delle Sezioni Critiche

1. Ridurre al minimo il codice all'interno di sezioni critiche
2. Utilizzare strutture dati thread-safe quando possibile
3. Preferire operazioni atomiche quando appropriate

## Esercizi di Autovalutazione

1. Modifica l'esempio di race condition per utilizzare un mutex e garantire il corretto incremento del contatore.
2. Implementa una soluzione al problema del produttore-consumatore utilizzando variabili di condizione.
3. Scrivi un programma che dimostra come evitare un deadlock utilizzando l'ordinamento delle risorse.
4. Implementa un pool di risorse utilizzando semafori.
5. Crea un programma che utilizza barriere per sincronizzare l'esecuzione di più thread in fasi distinte.