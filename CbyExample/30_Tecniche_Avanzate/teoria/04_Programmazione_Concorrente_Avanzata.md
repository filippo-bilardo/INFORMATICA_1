# Programmazione Concorrente Avanzata in C

## Introduzione

La programmazione concorrente è un paradigma che permette l'esecuzione simultanea di più processi o thread, migliorando l'efficienza e la reattività delle applicazioni. In C, esistono diverse tecniche avanzate per implementare la concorrenza, che vanno oltre l'uso base dei thread POSIX. Questo documento esplora approcci sofisticati alla programmazione concorrente, con particolare attenzione alle prestazioni, alla sincronizzazione e alla gestione delle risorse condivise.

## Modelli di Concorrenza Avanzati

### Programmazione Asincrona con Callback

```c
// Implementazione di un sistema di callback asincrono
typedef struct {
    void (*funzione)(void* dati);
    void* dati;
} Task;

typedef struct {
    Task* coda;
    size_t capacita;
    size_t dimensione;
    size_t testa;
    size_t coda_idx;
    pthread_mutex_t mutex;
    pthread_cond_t non_vuota;
    pthread_cond_t non_piena;
    int attivo;
} CodaTask;

// Inizializzazione della coda di task
CodaTask* inizializza_coda(size_t capacita) {
    CodaTask* coda = (CodaTask*)malloc(sizeof(CodaTask));
    if (!coda) return NULL;
    
    coda->coda = (Task*)malloc(capacita * sizeof(Task));
    if (!coda->coda) {
        free(coda);
        return NULL;
    }
    
    coda->capacita = capacita;
    coda->dimensione = 0;
    coda->testa = 0;
    coda->coda_idx = 0;
    coda->attivo = 1;
    
    pthread_mutex_init(&coda->mutex, NULL);
    pthread_cond_init(&coda->non_vuota, NULL);
    pthread_cond_init(&coda->non_piena, NULL);
    
    return coda;
}

// Aggiunta di un task alla coda
int aggiungi_task(CodaTask* coda, void (*funzione)(void*), void* dati) {
    if (!coda || !funzione) return -1;
    
    pthread_mutex_lock(&coda->mutex);
    
    // Attendi finché la coda non è piena
    while (coda->dimensione == coda->capacita && coda->attivo) {
        pthread_cond_wait(&coda->non_piena, &coda->mutex);
    }
    
    // Se la coda è stata disattivata
    if (!coda->attivo) {
        pthread_mutex_unlock(&coda->mutex);
        return -1;
    }
    
    // Aggiungi il task alla coda
    coda->coda[coda->coda_idx].funzione = funzione;
    coda->coda[coda->coda_idx].dati = dati;
    coda->coda_idx = (coda->coda_idx + 1) % coda->capacita;
    coda->dimensione++;
    
    // Segnala che la coda non è più vuota
    pthread_cond_signal(&coda->non_vuota);
    pthread_mutex_unlock(&coda->mutex);
    
    return 0;
}

// Funzione eseguita dai thread worker
void* worker(void* arg) {
    CodaTask* coda = (CodaTask*)arg;
    Task task;
    
    while (1) {
        pthread_mutex_lock(&coda->mutex);
        
        // Attendi finché la coda non è vuota
        while (coda->dimensione == 0 && coda->attivo) {
            pthread_cond_wait(&coda->non_vuota, &coda->mutex);
        }
        
        // Se la coda è vuota e non attiva, termina
        if (coda->dimensione == 0 && !coda->attivo) {
            pthread_mutex_unlock(&coda->mutex);
            break;
        }
        
        // Preleva un task dalla coda
        task = coda->coda[coda->testa];
        coda->testa = (coda->testa + 1) % coda->capacita;
        coda->dimensione--;
        
        // Segnala che la coda non è più piena
        pthread_cond_signal(&coda->non_piena);
        pthread_mutex_unlock(&coda->mutex);
        
        // Esegui il task
        task.funzione(task.dati);
    }
    
    return NULL;
}

// Creazione di un pool di thread
pthread_t* crea_thread_pool(CodaTask* coda, size_t num_thread) {
    pthread_t* threads = (pthread_t*)malloc(num_thread * sizeof(pthread_t));
    if (!threads) return NULL;
    
    for (size_t i = 0; i < num_thread; i++) {
        pthread_create(&threads[i], NULL, worker, coda);
    }
    
    return threads;
}

// Terminazione del pool di thread
void termina_thread_pool(CodaTask* coda, pthread_t* threads, size_t num_thread) {
    if (!coda || !threads) return;
    
    pthread_mutex_lock(&coda->mutex);
    coda->attivo = 0;
    pthread_cond_broadcast(&coda->non_vuota);
    pthread_cond_broadcast(&coda->non_piena);
    pthread_mutex_unlock(&coda->mutex);
    
    for (size_t i = 0; i < num_thread; i++) {
        pthread_join(threads[i], NULL);
    }
    
    free(threads);
}

// Distruzione della coda di task
void distruggi_coda(CodaTask* coda) {
    if (!coda) return;
    
    pthread_mutex_destroy(&coda->mutex);
    pthread_cond_destroy(&coda->non_vuota);
    pthread_cond_destroy(&coda->non_piena);
    
    free(coda->coda);
    free(coda);
}
```

### Modello Actor

```c
// Implementazione semplificata del modello Actor
typedef struct {
    void* stato;
    void (*ricevi_messaggio)(void* stato, void* messaggio);
    CodaTask* coda_messaggi;
    pthread_t thread;
} Actor;

// Funzione wrapper per l'elaborazione dei messaggi
typedef struct {
    Actor* actor;
    void* messaggio;
} DatiMessaggio;

// Funzione di callback per l'elaborazione dei messaggi
void elabora_messaggio(void* arg) {
    DatiMessaggio* dati = (DatiMessaggio*)arg;
    dati->actor->ricevi_messaggio(dati->actor->stato, dati->messaggio);
    free(dati);
}

// Funzione eseguita dal thread dell'actor
void* actor_thread(void* arg) {
    // Questa funzione è vuota perché il thread worker
    // della coda di task si occupa dell'elaborazione
    return NULL;
}

// Creazione di un nuovo actor
Actor* crea_actor(void* stato_iniziale, 
                 void (*ricevi_messaggio)(void* stato, void* messaggio)) {
    Actor* actor = (Actor*)malloc(sizeof(Actor));
    if (!actor) return NULL;
    
    actor->stato = stato_iniziale;
    actor->ricevi_messaggio = ricevi_messaggio;
    
    // Crea una coda di messaggi dedicata
    actor->coda_messaggi = inizializza_coda(100);
    if (!actor->coda_messaggi) {
        free(actor);
        return NULL;
    }
    
    // Crea un thread worker per la coda
    pthread_create(&actor->thread, NULL, worker, actor->coda_messaggi);
    
    return actor;
}

// Invio di un messaggio a un actor
int invia_messaggio(Actor* actor, void* messaggio) {
    if (!actor) return -1;
    
    // Crea una copia dei dati del messaggio
    DatiMessaggio* dati = (DatiMessaggio*)malloc(sizeof(DatiMessaggio));
    if (!dati) return -1;
    
    dati->actor = actor;
    dati->messaggio = messaggio;
    
    // Aggiungi il messaggio alla coda dell'actor
    return aggiungi_task(actor->coda_messaggi, elabora_messaggio, dati);
}

// Terminazione di un actor
void termina_actor(Actor* actor) {
    if (!actor) return;
    
    pthread_mutex_lock(&actor->coda_messaggi->mutex);
    actor->coda_messaggi->attivo = 0;
    pthread_cond_broadcast(&actor->coda_messaggi->non_vuota);
    pthread_mutex_unlock(&actor->coda_messaggi->mutex);
    
    pthread_join(actor->thread, NULL);
    
    distruggi_coda(actor->coda_messaggi);
    free(actor);
}
```

## Sincronizzazione Avanzata

### Lock-Free Programming

```c
// Implementazione di una coda lock-free per un singolo produttore e un singolo consumatore
typedef struct {
    void** buffer;
    size_t capacita;
    atomic_size_t testa; // Indice di lettura
    atomic_size_t coda;  // Indice di scrittura
} CodaLockFree;

// Inizializzazione della coda
CodaLockFree* inizializza_coda_lockfree(size_t capacita) {
    CodaLockFree* coda = (CodaLockFree*)malloc(sizeof(CodaLockFree));
    if (!coda) return NULL;
    
    coda->buffer = (void**)malloc(capacita * sizeof(void*));
    if (!coda->buffer) {
        free(coda);
        return NULL;
    }
    
    coda->capacita = capacita;
    atomic_init(&coda->testa, 0);
    atomic_init(&coda->coda, 0);
    
    return coda;
}

// Aggiunta di un elemento alla coda (produttore)
int produci(CodaLockFree* coda, void* elemento) {
    if (!coda) return -1;
    
    size_t coda_corrente = atomic_load(&coda->coda);
    size_t prossima_coda = (coda_corrente + 1) % coda->capacita;
    
    // Verifica se la coda è piena
    if (prossima_coda == atomic_load(&coda->testa)) {
        return -1; // Coda piena
    }
    
    coda->buffer[coda_corrente] = elemento;
    atomic_store(&coda->coda, prossima_coda);
    
    return 0;
}

// Prelievo di un elemento dalla coda (consumatore)
void* consuma(CodaLockFree* coda) {
    if (!coda) return NULL;
    
    size_t testa_corrente = atomic_load(&coda->testa);
    
    // Verifica se la coda è vuota
    if (testa_corrente == atomic_load(&coda->coda)) {
        return NULL; // Coda vuota
    }
    
    void* elemento = coda->buffer[testa_corrente];
    atomic_store(&coda->testa, (testa_corrente + 1) % coda->capacita);
    
    return elemento;
}

// Distruzione della coda
void distruggi_coda_lockfree(CodaLockFree* coda) {
    if (coda) {
        free(coda->buffer);
        free(coda);
    }
}
```

### Barriere di Memoria e Ordinamento

```c
// Esempio di utilizzo di barriere di memoria
#include <stdatomic.h>

// Variabili condivise tra thread
atomic_int flag = 0;
int dati[100];

// Thread produttore
void* thread_produttore(void* arg) {
    // Prepara i dati
    for (int i = 0; i < 100; i++) {
        dati[i] = i * 2;
    }
    
    // Barriera di memoria per garantire che tutte le scritture ai dati
    // siano completate prima di impostare il flag
    atomic_thread_fence(memory_order_release);
    
    // Imposta il flag per indicare che i dati sono pronti
    atomic_store_explicit(&flag, 1, memory_order_release);
    
    return NULL;
}

// Thread consumatore
void* thread_consumatore(void* arg) {
    // Attendi che il flag sia impostato
    while (atomic_load_explicit(&flag, memory_order_acquire) == 0) {
        // Attesa attiva (in un'implementazione reale si potrebbe usare una pausa)
    }
    
    // Barriera di memoria per garantire che tutte le letture dei dati
    // avvengano dopo la lettura del flag
    atomic_thread_fence(memory_order_acquire);
    
    // Ora è sicuro accedere ai dati
    int somma = 0;
    for (int i = 0; i < 100; i++) {
        somma += dati[i];
    }
    
    printf("Somma: %d\n", somma);
    
    return NULL;
}
```

## Parallelismo a Livello di Dati

### SIMD con Intrinsics

```c
// Esempio di utilizzo di istruzioni SIMD con intrinsics
#include <immintrin.h>

// Somma di array utilizzando AVX
void somma_array_avx(float* a, float* b, float* risultato, size_t lunghezza) {
    size_t i;
    
    // Elabora 8 elementi alla volta utilizzando AVX
    for (i = 0; i + 7 < lunghezza; i += 8) {
        __m256 va = _mm256_loadu_ps(&a[i]);
        __m256 vb = _mm256_loadu_ps(&b[i]);
        __m256 vr = _mm256_add_ps(va, vb);
        _mm256_storeu_ps(&risultato[i], vr);
    }
    
    // Elabora gli elementi rimanenti
    for (; i < lunghezza; i++) {
        risultato[i] = a[i] + b[i];
    }
}

// Moltiplicazione di array utilizzando AVX
void moltiplica_array_avx(float* a, float* b, float* risultato, size_t lunghezza) {
    size_t i;
    
    // Elabora 8 elementi alla volta utilizzando AVX
    for (i = 0; i + 7 < lunghezza; i += 8) {
        __m256 va = _mm256_loadu_ps(&a[i]);
        __m256 vb = _mm256_loadu_ps(&b[i]);
        __m256 vr = _mm256_mul_ps(va, vb);
        _mm256_storeu_ps(&risultato[i], vr);
    }
    
    // Elabora gli elementi rimanenti
    for (; i < lunghezza; i++) {
        risultato[i] = a[i] * b[i];
    }
}
```

### OpenMP per Parallelismo

```c
// Esempio di utilizzo di OpenMP per parallelizzare cicli
#include <omp.h>

// Moltiplicazione di matrici parallelizzata con OpenMP
void moltiplica_matrici_omp(float** a, float** b, float** c, int n) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            float somma = 0.0f;
            for (int k = 0; k < n; k++) {
                somma += a[i][k] * b[k][j];
            }
            c[i][j] = somma;
        }
    }
}

// Elaborazione di immagini con OpenMP
void applica_filtro_omp(unsigned char* immagine, unsigned char* risultato, 
                       float* kernel, int larghezza, int altezza, int kernel_size) {
    int raggio = kernel_size / 2;
    
    #pragma omp parallel for
    for (int y = raggio; y < altezza - raggio; y++) {
        for (int x = raggio; x < larghezza - raggio; x++) {
            float somma = 0.0f;
            
            for (int ky = -raggio; ky <= raggio; ky++) {
                for (int kx = -raggio; kx <= raggio; kx++) {
                    int idx = (y + ky) * larghezza + (x + kx);
                    int kidx = (ky + raggio) * kernel_size + (kx + raggio);
                    somma += immagine[idx] * kernel[kidx];
                }
            }
            
            // Limita il risultato all'intervallo [0, 255]
            int valore = (int)somma;
            if (valore < 0) valore = 0;
            if (valore > 255) valore = 255;
            
            risultato[y * larghezza + x] = (unsigned char)valore;
        }
    }
}
```

## Tecniche di Comunicazione Inter-Thread

### Code di Messaggi Lock-Free

```c
// Implementazione di una coda di messaggi lock-free per più produttori e più consumatori
typedef struct NodoMessaggio {
    void* messaggio;
    struct NodoMessaggio* next;
} NodoMessaggio;

typedef struct {
    atomic_uintptr_t testa;
    atomic_uintptr_t coda;
} CodaMessaggiLockFree;

// Inizializzazione della coda
CodaMessaggiLockFree* inizializza_coda_messaggi() {
    CodaMessaggiLockFree* coda = (CodaMessaggiLockFree*)malloc(sizeof(CodaMessaggiLockFree));
    if (!coda) return NULL;
    
    // Crea un nodo fittizio
    NodoMessaggio* nodo = (NodoMessaggio*)malloc(sizeof(NodoMessaggio));
    if (!nodo) {
        free(coda);
        return NULL;
    }
    
    nodo->messaggio = NULL;
    nodo->next = NULL;
    
    atomic_init(&coda->testa, (uintptr_t)nodo);
    atomic_init(&coda->coda, (uintptr_t)nodo);
    
    return coda;
}

// Aggiunta di un messaggio alla coda
int invia_messaggio_lockfree(CodaMessaggiLockFree* coda, void* messaggio) {
    if (!coda || !messaggio) return -1;
    
    // Crea un nuovo nodo
    NodoMessaggio* nuovo = (NodoMessaggio*)malloc(sizeof(NodoMessaggio));
    if (!nuovo) return -1;
    
    nuovo->messaggio = messaggio;
    nuovo->next = NULL;
    
    // Aggiungi il nodo alla coda in modo atomico
    NodoMessaggio* coda_corrente;
    uintptr_t coda_ptr;
    
    do {
        coda_ptr = atomic_load(&coda->coda);
        coda_corrente = (NodoMessaggio*)coda_ptr;
    } while (!atomic_compare_exchange_weak(&coda_corrente->next, 
                                         (NodoMessaggio**)&nuovo->next, 
                                         nuovo));
    
    // Aggiorna il puntatore alla coda
    atomic_compare_exchange_strong(&coda->coda, &coda_ptr, (uintptr_t)nuovo);
    
    return 0;
}

// Prelievo di un messaggio dalla coda
void* ricevi_messaggio_lockfree(CodaMessaggiLockFree* coda) {
    if (!coda) return NULL;
    
    NodoMessaggio* testa_corrente;
    NodoMessaggio* prossima_testa;
    void* messaggio = NULL;
    uintptr_t testa_ptr;
    
    do {
        testa_ptr = atomic_load(&coda->testa);
        testa_corrente = (NodoMessaggio*)testa_ptr;
        prossima_testa = testa_corrente->next;
        
        // Se la coda è vuota
        if (!prossima_testa) {
            return NULL;
        }
        
        messaggio = prossima_testa->messaggio;
    } while (!atomic_compare_exchange_weak(&coda->testa, 
                                         &testa_ptr, 
                                         (uintptr_t)prossima_testa));
    
    // Libera il nodo rimosso
    free(testa_corrente);
    
    return messaggio;
}

// Distruzione della coda
void distruggi_coda_messaggi(CodaMessaggiLockFree* coda) {
    if (!coda) return;
    
    // Libera tutti i nodi rimanenti
    NodoMessaggio* corrente = (NodoMessaggio*)atomic_load(&coda->testa);
    while (corrente) {
        NodoMessaggio* prossimo = corrente->next;
        free(corrente);
        corrente = prossimo;
    }
    
    free(coda);
}
```

### Memoria Condivisa con Protezione

```c
// Implementazione di una memoria condivisa con protezione tramite RWLock
typedef struct {
    void* dati;
    size_t dimensione;
    pthread_rwlock_t lock;
} MemoriaCondivisa;

// Inizializzazione della memoria condivisa
MemoriaCondivisa* inizializza_memoria_condivisa(size_t dimensione) {
    MemoriaCondivisa* mem = (MemoriaCondivisa*)malloc(sizeof(MemoriaCondivisa));
    if (!mem) return NULL;
    
    mem->dati = malloc(dimensione);
    if (!mem->dati) {
        free(mem);
        return NULL;
    }
    
    mem->dimensione = dimensione;
    
    if (pthread_rwlock_init(&mem->lock, NULL) != 0) {
        free(mem->dati);
        free(mem);
        return NULL;
    }
    
    return mem;
}

// Lettura dalla memoria condivisa
int leggi_memoria_condivisa(MemoriaCondivisa* mem, void* buffer, 
                          size_t offset, size_t dimensione) {
    if (!mem || !buffer || offset + dimensione > mem->dimensione) {
        return -1;
    }
    
    pthread_rwlock_rdlock(&mem->lock);
    memcpy(buffer, (char*)mem->dati + offset, dimensione);
    pthread_rwlock_unlock(&mem->lock);
    
    return 0;
}

// Scrittura nella memoria condivisa
int scrivi_memoria_condivisa(MemoriaCondivisa* mem, const void* buffer, 
                           size_t offset, size_t dimensione) {
    if (!mem || !buffer || offset + dimensione > mem->dimensione) {
        return -1;
    }
    
    pthread_rwlock_wrlock(&mem->lock);
    memcpy((char*)mem->dati + offset, buffer, dimensione);
    pthread_rwlock_unlock(&mem->lock);
    
    return 0;
}

// Distruzione della memoria condivisa
void distruggi_memoria_condivisa(MemoriaCondivisa* mem) {
    if (!mem) return;
    
    pthread_rwlock_destroy(&mem->lock);
    free(mem->dati);
    free(mem);
}
```

## Best Practices

- **Evitare Race Conditions**: Utilizzare meccanismi di sincronizzazione appropriati per proteggere l'accesso a risorse condivise.
- **Minimizzare il Contention**: Ridurre al minimo la contesa per le risorse condivise, utilizzando tecniche come il lock-free programming o la partizione dei dati.
- **Granularità del Lock**: Utilizzare lock a granularità fine per proteggere solo le risorse necessarie, evitando di bloccare intere sezioni di codice.
- **Evitare Deadlock**: Progettare attentamente l'ordine di acquisizione dei lock per prevenire situazioni di stallo.
- **Bilanciamento del Carico**: Distribuire equamente il lavoro tra i thread per massimizzare l'utilizzo delle risorse.
- **Località dei Dati**: Organizzare i dati per massimizzare la località spaziale e temporale, riducendo i cache miss.
- **Minimizzare la Comunicazione**: Ridurre al minimo la comunicazione tra thread, preferendo approcci che favoriscono l'indipendenza.
- **Profiling e Ottimizzazione**: Utilizzare strumenti di profiling per identificare colli di bottiglia e ottimizzare le parti critiche del codice.

## Esercizi Proposti

1. **Implementazione di un Pool di Thread Avanzato**: Creare un pool di thread con priorità e supporto per task con dipendenze.
2. **Sistema di Attori Distribuito**: Estendere il modello Actor per supportare la comunicazione tra processi su macchine diverse.
3. **Strutture Dati Lock-Free**: Implementare versioni lock-free di strutture dati comuni come liste, alberi o hash table.
4. **Framework per Parallelismo di Dati**: Sviluppare un framework che semplifichi l'applicazione di operazioni SIMD su grandi set di dati.
5. **Sistema di Pipeline Parallela**: Implementare un sistema di elaborazione a pipeline con stadi paralleli e buffer tra gli stadi.

## Domande di Autovalutazione

1. Quali sono i vantaggi e gli svantaggi del lock-free programming rispetto all'uso di mutex?
2. Come si può garantire la correttezza in un sistema concorrente complesso?
3. Quali tecniche si possono utilizzare per migliorare le prestazioni di un'applicazione multi-thread?
4. Come si può implementare un sistema di comunicazione efficiente tra thread?
5. Quali sono le sfide nell'implementare strutture dati thread-safe e come si possono superare?

## Conclusione

La programmazione concorrente avanzata in C offre potenti strumenti per sfruttare al massimo le architetture multi-core moderne. Attraverso l'uso di tecniche sofisticate come il lock-free programming, il parallelismo a livello di dati e modelli di concorrenza avanzati, è possibile sviluppare applicazioni altamente efficienti e scalabili. Tuttavia, queste tecniche richiedono una comprensione approfondita dei meccanismi sottostanti e un'attenta progettazione per evitare problemi come race condition, deadlock e degradazione delle prestazioni dovuta alla contesa. Con la pratica e l'applicazione delle best practices presentate, è possibile padroneggiare queste tecniche e sfruttarle per creare software robusto e performante.