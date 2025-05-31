# Gestione Avanzata della Memoria in C

## Introduzione

La gestione avanzata della memoria è un aspetto cruciale della programmazione in C, soprattutto per applicazioni che richiedono elevate prestazioni o che operano in ambienti con risorse limitate. Questo documento esplora tecniche sofisticate per ottimizzare l'allocazione, l'utilizzo e il rilascio della memoria.

## Implementazione di Allocatori di Memoria Personalizzati

### Allocatori a Blocchi Fissi

```c
// Implementazione di un allocatore a blocchi fissi
typedef struct {
    void* memoria;           // Puntatore all'area di memoria
    size_t dimensione_blocco; // Dimensione di ciascun blocco
    size_t num_blocchi;      // Numero totale di blocchi
    unsigned char* mappa;    // Mappa dei blocchi liberi/occupati
} AllocatoreBlocchi;

// Inizializzazione dell'allocatore
AllocatoreBlocchi* inizializza_allocatore(size_t dimensione_blocco, size_t num_blocchi) {
    AllocatoreBlocchi* alloc = (AllocatoreBlocchi*)malloc(sizeof(AllocatoreBlocchi));
    if (!alloc) return NULL;
    
    // Allocazione della memoria per tutti i blocchi
    alloc->memoria = malloc(dimensione_blocco * num_blocchi);
    if (!alloc->memoria) {
        free(alloc);
        return NULL;
    }
    
    // Allocazione della mappa dei blocchi (1 bit per blocco, arrotondato a byte)
    size_t dimensione_mappa = (num_blocchi + 7) / 8;
    alloc->mappa = (unsigned char*)calloc(dimensione_mappa, 1);
    if (!alloc->mappa) {
        free(alloc->memoria);
        free(alloc);
        return NULL;
    }
    
    alloc->dimensione_blocco = dimensione_blocco;
    alloc->num_blocchi = num_blocchi;
    
    return alloc;
}

// Allocazione di un blocco
void* alloca_blocco(AllocatoreBlocchi* alloc) {
    if (!alloc) return NULL;
    
    // Cerca un blocco libero
    for (size_t i = 0; i < alloc->num_blocchi; i++) {
        size_t byte_index = i / 8;
        size_t bit_index = i % 8;
        unsigned char mask = 1 << bit_index;
        
        // Se il bit è 0, il blocco è libero
        if (!(alloc->mappa[byte_index] & mask)) {
            // Marca il blocco come occupato
            alloc->mappa[byte_index] |= mask;
            
            // Calcola l'indirizzo del blocco
            return (char*)alloc->memoria + (i * alloc->dimensione_blocco);
        }
    }
    
    return NULL; // Nessun blocco disponibile
}

// Liberazione di un blocco
void libera_blocco(AllocatoreBlocchi* alloc, void* ptr) {
    if (!alloc || !ptr) return;
    
    // Verifica che il puntatore appartenga all'allocatore
    if (ptr < alloc->memoria || 
        ptr >= (char*)alloc->memoria + (alloc->num_blocchi * alloc->dimensione_blocco)) {
        return; // Puntatore non valido
    }
    
    // Calcola l'indice del blocco
    size_t offset = (char*)ptr - (char*)alloc->memoria;
    if (offset % alloc->dimensione_blocco != 0) {
        return; // Puntatore non allineato a un blocco
    }
    
    size_t indice_blocco = offset / alloc->dimensione_blocco;
    size_t byte_index = indice_blocco / 8;
    size_t bit_index = indice_blocco % 8;
    unsigned char mask = 1 << bit_index;
    
    // Marca il blocco come libero
    alloc->mappa[byte_index] &= ~mask;
}

// Distruzione dell'allocatore
void distruggi_allocatore(AllocatoreBlocchi* alloc) {
    if (alloc) {
        free(alloc->mappa);
        free(alloc->memoria);
        free(alloc);
    }
}
```

### Allocatori a Pool di Memoria

```c
// Implementazione di un pool di memoria per oggetti di dimensione fissa
typedef struct NodoLibero {
    struct NodoLibero* next;
} NodoLibero;

typedef struct {
    void* memoria;           // Area di memoria del pool
    size_t dimensione_elemento; // Dimensione di ciascun elemento
    size_t num_elementi;     // Numero totale di elementi
    NodoLibero* lista_liberi; // Lista degli elementi liberi
} PoolMemoria;

// Inizializzazione del pool
PoolMemoria* inizializza_pool(size_t dimensione_elemento, size_t num_elementi) {
    // La dimensione dell'elemento deve essere almeno quella di un puntatore
    if (dimensione_elemento < sizeof(NodoLibero*)) {
        dimensione_elemento = sizeof(NodoLibero*);
    }
    
    PoolMemoria* pool = (PoolMemoria*)malloc(sizeof(PoolMemoria));
    if (!pool) return NULL;
    
    // Allocazione della memoria per tutti gli elementi
    pool->memoria = malloc(dimensione_elemento * num_elementi);
    if (!pool->memoria) {
        free(pool);
        return NULL;
    }
    
    pool->dimensione_elemento = dimensione_elemento;
    pool->num_elementi = num_elementi;
    
    // Inizializzazione della lista degli elementi liberi
    pool->lista_liberi = NULL;
    char* ptr = (char*)pool->memoria;
    
    // Collega tutti gli elementi in una lista
    for (size_t i = 0; i < num_elementi; i++) {
        NodoLibero* nodo = (NodoLibero*)ptr;
        nodo->next = pool->lista_liberi;
        pool->lista_liberi = nodo;
        ptr += dimensione_elemento;
    }
    
    return pool;
}

// Allocazione di un elemento dal pool
void* alloca_da_pool(PoolMemoria* pool) {
    if (!pool || !pool->lista_liberi) return NULL;
    
    // Prendi il primo elemento libero
    NodoLibero* elemento = pool->lista_liberi;
    pool->lista_liberi = elemento->next;
    
    // Opzionale: azzera la memoria
    memset(elemento, 0, pool->dimensione_elemento);
    
    return elemento;
}

// Liberazione di un elemento e restituzione al pool
void libera_nel_pool(PoolMemoria* pool, void* ptr) {
    if (!pool || !ptr) return;
    
    // Verifica che il puntatore appartenga al pool
    if (ptr < pool->memoria || 
        ptr >= (char*)pool->memoria + (pool->num_elementi * pool->dimensione_elemento)) {
        return; // Puntatore non valido
    }
    
    // Inserisci l'elemento nella lista dei liberi
    NodoLibero* nodo = (NodoLibero*)ptr;
    nodo->next = pool->lista_liberi;
    pool->lista_liberi = nodo;
}

// Distruzione del pool
void distruggi_pool(PoolMemoria* pool) {
    if (pool) {
        free(pool->memoria);
        free(pool);
    }
}
```

## Tecniche di Garbage Collection in C

### Reference Counting

```c
// Implementazione di un sistema di reference counting
typedef struct {
    void* dato;           // Puntatore ai dati
    size_t contatore_ref; // Contatore dei riferimenti
    void (*distruttore)(void*); // Funzione per liberare i dati
} OggettoRC;

// Creazione di un nuovo oggetto con reference counting
OggettoRC* crea_oggetto_rc(void* dato, void (*distruttore)(void*)) {
    OggettoRC* oggetto = (OggettoRC*)malloc(sizeof(OggettoRC));
    if (oggetto) {
        oggetto->dato = dato;
        oggetto->contatore_ref = 1; // Inizia con un riferimento
        oggetto->distruttore = distruttore;
    }
    return oggetto;
}

// Incrementa il contatore dei riferimenti
void incrementa_ref(OggettoRC* oggetto) {
    if (oggetto) {
        oggetto->contatore_ref++;
    }
}

// Decrementa il contatore e libera l'oggetto se necessario
void decrementa_ref(OggettoRC* oggetto) {
    if (oggetto && --oggetto->contatore_ref == 0) {
        if (oggetto->distruttore) {
            oggetto->distruttore(oggetto->dato);
        }
        free(oggetto);
    }
}

// Esempio di utilizzo
void esempio_reference_counting() {
    // Funzione distruttore per un array dinamico
    void distruggi_array(void* ptr) {
        free(ptr);
        printf("Array distrutto\n");
    }
    
    // Crea un array dinamico
    int* array = (int*)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) array[i] = i;
    
    // Crea un oggetto RC che gestisce l'array
    OggettoRC* oggetto = crea_oggetto_rc(array, distruggi_array);
    
    // Simula più riferimenti all'oggetto
    incrementa_ref(oggetto); // ora contatore_ref = 2
    
    // Simula la fine dell'uso da parte di un riferimento
    decrementa_ref(oggetto); // ora contatore_ref = 1
    
    // L'ultimo riferimento viene rimosso, l'oggetto viene distrutto
    decrementa_ref(oggetto); // contatore_ref = 0, l'oggetto viene liberato
}
```

### Mark and Sweep (semplificato)

```c
// Implementazione semplificata di un garbage collector mark-and-sweep
#define MAX_OGGETTI 1000

typedef struct Oggetto {
    void* dato;
    int marcato;
    void (*distruttore)(void*);
    // Puntatori ad altri oggetti che questo oggetto referenzia
    struct Oggetto** riferimenti;
    int num_riferimenti;
} Oggetto;

typedef struct {
    Oggetto* oggetti[MAX_OGGETTI];
    int num_oggetti;
} GarbageCollector;

// Inizializzazione del garbage collector
GarbageCollector* inizializza_gc() {
    GarbageCollector* gc = (GarbageCollector*)malloc(sizeof(GarbageCollector));
    if (gc) {
        gc->num_oggetti = 0;
        memset(gc->oggetti, 0, sizeof(gc->oggetti));
    }
    return gc;
}

// Registrazione di un nuovo oggetto
Oggetto* registra_oggetto(GarbageCollector* gc, void* dato, void (*distruttore)(void*)) {
    if (!gc || gc->num_oggetti >= MAX_OGGETTI) return NULL;
    
    Oggetto* oggetto = (Oggetto*)malloc(sizeof(Oggetto));
    if (!oggetto) return NULL;
    
    oggetto->dato = dato;
    oggetto->marcato = 0;
    oggetto->distruttore = distruttore;
    oggetto->riferimenti = NULL;
    oggetto->num_riferimenti = 0;
    
    gc->oggetti[gc->num_oggetti++] = oggetto;
    return oggetto;
}

// Aggiunta di un riferimento tra oggetti
void aggiungi_riferimento(Oggetto* da, Oggetto* a) {
    if (!da || !a) return;
    
    // Alloca o rialloca l'array dei riferimenti
    da->riferimenti = (Oggetto**)realloc(da->riferimenti, 
                                       (da->num_riferimenti + 1) * sizeof(Oggetto*));
    if (da->riferimenti) {
        da->riferimenti[da->num_riferimenti++] = a;
    }
}

// Fase di marcatura (ricorsiva)
void marca(Oggetto* oggetto) {
    if (!oggetto || oggetto->marcato) return;
    
    oggetto->marcato = 1;
    
    // Marca ricorsivamente tutti gli oggetti referenziati
    for (int i = 0; i < oggetto->num_riferimenti; i++) {
        marca(oggetto->riferimenti[i]);
    }
}

// Esecuzione del garbage collection
void esegui_gc(GarbageCollector* gc, Oggetto** radici, int num_radici) {
    if (!gc) return;
    
    // Fase 1: Azzera tutti i marcatori
    for (int i = 0; i < gc->num_oggetti; i++) {
        if (gc->oggetti[i]) {
            gc->oggetti[i]->marcato = 0;
        }
    }
    
    // Fase 2: Marca a partire dalle radici
    for (int i = 0; i < num_radici; i++) {
        marca(radici[i]);
    }
    
    // Fase 3: Sweep - libera gli oggetti non marcati
    for (int i = 0; i < gc->num_oggetti; i++) {
        if (gc->oggetti[i] && !gc->oggetti[i]->marcato) {
            if (gc->oggetti[i]->distruttore) {
                gc->oggetti[i]->distruttore(gc->oggetti[i]->dato);
            }
            free(gc->oggetti[i]->riferimenti);
            free(gc->oggetti[i]);
            gc->oggetti[i] = NULL;
        }
    }
    
    // Compatta l'array degli oggetti (opzionale)
    int j = 0;
    for (int i = 0; i < gc->num_oggetti; i++) {
        if (gc->oggetti[i]) {
            gc->oggetti[j++] = gc->oggetti[i];
        }
    }
    gc->num_oggetti = j;
}
```

## Strategie per Evitare la Frammentazione della Memoria

### Compattazione della Memoria

```c
// Implementazione di un heap compattabile
typedef struct Blocco {
    void* inizio;         // Indirizzo di inizio del blocco
    size_t dimensione;    // Dimensione del blocco in byte
    int libero;           // Flag che indica se il blocco è libero
    struct Blocco* next;  // Puntatore al blocco successivo
} Blocco;

typedef struct {
    void* memoria;        // Puntatore all'area di memoria
    size_t dimensione;    // Dimensione totale in byte
    Blocco* lista_blocchi; // Lista dei blocchi
} HeapCompattabile;

// Inizializzazione dell'heap
HeapCompattabile* inizializza_heap(size_t dimensione) {
    HeapCompattabile* heap = (HeapCompattabile*)malloc(sizeof(HeapCompattabile));
    if (!heap) return NULL;
    
    heap->memoria = malloc(dimensione);
    if (!heap->memoria) {
        free(heap);
        return NULL;
    }
    
    heap->dimensione = dimensione;
    
    // Inizialmente c'è un solo blocco libero che copre tutto l'heap
    heap->lista_blocchi = (Blocco*)malloc(sizeof(Blocco));
    if (!heap->lista_blocchi) {
        free(heap->memoria);
        free(heap);
        return NULL;
    }
    
    heap->lista_blocchi->inizio = heap->memoria;
    heap->lista_blocchi->dimensione = dimensione;
    heap->lista_blocchi->libero = 1;
    heap->lista_blocchi->next = NULL;
    
    return heap;
}

// Allocazione di memoria dall'heap
void* alloca_da_heap(HeapCompattabile* heap, size_t dimensione) {
    if (!heap || dimensione == 0) return NULL;
    
    Blocco* corrente = heap->lista_blocchi;
    Blocco* migliore = NULL;
    size_t spazio_minimo = heap->dimensione + 1; // Valore impossibile
    
    // Cerca il blocco libero più piccolo che può contenere la richiesta (best fit)
    while (corrente) {
        if (corrente->libero && corrente->dimensione >= dimensione) {
            if (corrente->dimensione < spazio_minimo) {
                spazio_minimo = corrente->dimensione;
                migliore = corrente;
            }
        }
        corrente = corrente->next;
    }
    
    if (!migliore) return NULL; // Nessun blocco adatto trovato
    
    // Se il blocco è molto più grande del necessario, dividiamolo
    if (migliore->dimensione > dimensione + sizeof(Blocco) + 32) { // 32 è una soglia arbitraria
        Blocco* nuovo = (Blocco*)malloc(sizeof(Blocco));
        if (nuovo) {
            nuovo->dimensione = migliore->dimensione - dimensione;
            nuovo->inizio = (char*)migliore->inizio + dimensione;
            nuovo->libero = 1;
            nuovo->next = migliore->next;
            
            migliore->dimensione = dimensione;
            migliore->next = nuovo;
        }
    }
    
    migliore->libero = 0; // Marca come occupato
    return migliore->inizio;
}

// Liberazione di memoria
void libera_in_heap(HeapCompattabile* heap, void* ptr) {
    if (!heap || !ptr) return;
    
    Blocco* corrente = heap->lista_blocchi;
    
    // Trova il blocco corrispondente al puntatore
    while (corrente && corrente->inizio != ptr) {
        corrente = corrente->next;
    }
    
    if (!corrente) return; // Puntatore non valido
    
    corrente->libero = 1; // Marca come libero
    
    // Unisci con il blocco successivo se è libero
    if (corrente->next && corrente->next->libero) {
        corrente->dimensione += corrente->next->dimensione;
        Blocco* temp = corrente->next;
        corrente->next = temp->next;
        free(temp);
    }
    
    // Cerca il blocco precedente e uniscilo se è libero
    Blocco* precedente = heap->lista_blocchi;
    while (precedente && precedente->next != corrente) {
        precedente = precedente->next;
    }
    
    if (precedente && precedente->libero) {
        precedente->dimensione += corrente->dimensione;
        precedente->next = corrente->next;
        free(corrente);
    }
}

// Compattazione dell'heap
void compatta_heap(HeapCompattabile* heap) {
    if (!heap) return;
    
    Blocco* corrente = heap->lista_blocchi;
    char* dest = (char*)heap->memoria; // Destinazione per la compattazione
    
    while (corrente) {
        if (!corrente->libero) { // Solo i blocchi occupati vengono spostati
            if (corrente->inizio != dest) {
                // Sposta i dati
                memmove(dest, corrente->inizio, corrente->dimensione);
                corrente->inizio = dest;
            }
            dest += corrente->dimensione;
        }
        corrente = corrente->next;
    }
    
    // Dopo aver spostato tutti i blocchi occupati, crea un unico blocco libero alla fine
    corrente = heap->lista_blocchi;
    Blocco* ultimo_occupato = NULL;
    
    // Trova l'ultimo blocco occupato
    while (corrente) {
        if (!corrente->libero) {
            ultimo_occupato = corrente;
        }
        corrente = corrente->next;
    }
    
    // Se non ci sono blocchi occupati, l'intero heap è libero
    if (!ultimo_occupato) {
        heap->lista_blocchi->inizio = heap->memoria;
        heap->lista_blocchi->dimensione = heap->dimensione;
        heap->lista_blocchi->libero = 1;
        heap->lista_blocchi->next = NULL;
        return;
    }
    
    // Crea un unico blocco libero dopo l'ultimo blocco occupato
    Blocco* blocco_libero = (Blocco*)malloc(sizeof(Blocco));
    if (blocco_libero) {
        blocco_libero->inizio = (char*)ultimo_occupato->inizio + ultimo_occupato->dimensione;
        blocco_libero->dimensione = (char*)heap->memoria + heap->dimensione - 
                                  (char*)blocco_libero->inizio;
        blocco_libero->libero = 1;
        blocco_libero->next = NULL;
        
        ultimo_occupato->next = blocco_libero;
        
        // Rimuovi tutti gli altri blocchi liberi
        corrente = heap->lista_blocchi;
        Blocco* precedente = NULL;
        
        while (corrente != blocco_libero) {
            if (corrente->libero) {
                if (precedente) {
                    precedente->next = corrente->next;
                    free(corrente);
                    corrente = precedente->next;
                } else {
                    heap->lista_blocchi = corrente->next;
                    free(corrente);
                    corrente = heap->lista_blocchi;
                }
            } else {
                precedente = corrente;
                corrente = corrente->next;
            }
        }
    }
}
```

## Best Practices

- **Evitare la frammentazione**: Utilizzare allocatori specializzati per oggetti di dimensioni simili.
- **Riutilizzare la memoria**: Implementare pool di memoria per oggetti con ciclo di vita breve.
- **Monitorare l'uso della memoria**: Tenere traccia delle allocazioni e dei pattern di utilizzo.
- **Limitare le allocazioni dinamiche**: Preferire allocazioni statiche o sullo stack quando possibile.
- **Gestire correttamente le risorse**: Seguire il pattern RAII (Resource Acquisition Is Initialization) anche in C.
- **Evitare memory leak**: Implementare sistemi di reference counting o garbage collection quando appropriato.
- **Ottimizzare l'accesso alla memoria**: Organizzare i dati per massimizzare la località spaziale e temporale.

## Esercizi Proposti

1. **Implementare un allocatore a slab**: Creare un allocatore che gestisca efficientemente oggetti di dimensione fissa.
2. **Sistema di reference counting**: Implementare un sistema completo di reference counting per gestire oggetti complessi.
3. **Analizzatore di memory leak**: Sviluppare uno strumento che tenga traccia delle allocazioni e rilevi potenziali memory leak.
4. **Pool di memoria thread-safe**: Estendere l'implementazione del pool di memoria per renderla sicura in ambiente multi-thread.
5. **Compattazione di memoria con puntatori aggiornabili**: Implementare un sistema che permetta la compattazione della memoria aggiornando automaticamente i puntatori agli oggetti spostati.

## Domande di Autovalutazione

1. Quali sono i vantaggi e gli svantaggi di implementare un allocatore di memoria personalizzato?
2. Come si può implementare un sistema di garbage collection in C?
3. Quali tecniche si possono utilizzare per ridurre la frammentazione della memoria?
4. Come si può ottimizzare un pool di memoria per diversi pattern di allocazione?
5. Quali sono le sfide nell'implementare un sistema di gestione della memoria thread-safe?

## Conclusione

La gestione avanzata della memoria è un aspetto fondamentale per sviluppare applicazioni C di alta qualità, soprattutto in contesti con risorse limitate o requisiti di prestazioni elevate. Le tecniche presentate in questo documento consentono di implementare soluzioni personalizzate che ottimizzano l'utilizzo della memoria, riducono la frammentazione e prevengono memory leak, contribuendo a creare software più robusto ed efficiente.