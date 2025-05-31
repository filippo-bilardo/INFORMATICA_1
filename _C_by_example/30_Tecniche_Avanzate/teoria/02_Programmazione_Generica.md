# Programmazione Generica in C

## Introduzione

La programmazione generica permette di scrivere codice che funziona con diversi tipi di dati. Sebbene C non supporti nativamente i template come C++ o i generics come Java, esistono tecniche avanzate che consentono di implementare strutture dati e algoritmi generici anche in C.

## Implementazione di Strutture Dati e Algoritmi Generici

### Utilizzo di void*

Il puntatore generico `void*` è lo strumento principale per implementare strutture dati generiche in C:

```c
// Implementazione di una lista generica
typedef struct Nodo {
    void* dato;           // Puntatore a dati di qualsiasi tipo
    struct Nodo* next;
} Nodo;

typedef struct {
    Nodo* testa;
    size_t dimensione_elemento; // Dimensione in byte di ogni elemento
    int (*compara)(const void*, const void*); // Funzione di confronto
} Lista;

// Creazione di una nuova lista
Lista* crea_lista(size_t dimensione_elemento, int (*compara)(const void*, const void*)) {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    if (lista) {
        lista->testa = NULL;
        lista->dimensione_elemento = dimensione_elemento;
        lista->compara = compara;
    }
    return lista;
}

// Inserimento di un elemento
int inserisci(Lista* lista, void* dato) {
    Nodo* nuovo = (Nodo*)malloc(sizeof(Nodo));
    if (!nuovo) return 0;
    
    // Allocazione e copia del dato
    nuovo->dato = malloc(lista->dimensione_elemento);
    if (!nuovo->dato) {
        free(nuovo);
        return 0;
    }
    
    memcpy(nuovo->dato, dato, lista->dimensione_elemento);
    nuovo->next = lista->testa;
    lista->testa = nuovo;
    return 1;
}

// Ricerca di un elemento
Nodo* cerca(Lista* lista, void* dato) {
    Nodo* corrente = lista->testa;
    while (corrente) {
        if (lista->compara(corrente->dato, dato) == 0) {
            return corrente;
        }
        corrente = corrente->next;
    }
    return NULL;
}
```

### Esempio di Utilizzo

```c
// Funzione di confronto per interi
int compara_int(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Utilizzo della lista generica con interi
int main() {
    Lista* lista_interi = crea_lista(sizeof(int), compara_int);
    
    int valori[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        inserisci(lista_interi, &valori[i]);
    }
    
    int cerca_valore = 30;
    Nodo* trovato = cerca(lista_interi, &cerca_valore);
    if (trovato) {
        printf("Trovato: %d\n", *(int*)trovato->dato);
    } else {
        printf("Valore non trovato\n");
    }
    
    // Liberare la memoria...
    return 0;
}
```

## Uso Avanzato di Macro e Preprocessore

### Macro per Strutture Dati Generiche

```c
// Definizione di un vettore generico usando macro
#define DICHIARA_VETTORE(tipo) \
    typedef struct { \
        tipo* elementi; \
        size_t capacita; \
        size_t dimensione; \
    } Vettore_##tipo; \
    \
    Vettore_##tipo* crea_vettore_##tipo(size_t capacita_iniziale) { \
        Vettore_##tipo* v = (Vettore_##tipo*)malloc(sizeof(Vettore_##tipo)); \
        if (v) { \
            v->elementi = (tipo*)malloc(capacita_iniziale * sizeof(tipo)); \
            if (!v->elementi) { \
                free(v); \
                return NULL; \
            } \
            v->capacita = capacita_iniziale; \
            v->dimensione = 0; \
        } \
        return v; \
    } \
    \
    int aggiungi_##tipo(Vettore_##tipo* v, tipo elemento) { \
        if (v->dimensione >= v->capacita) { \
            size_t nuova_capacita = v->capacita * 2; \
            tipo* nuovi_elementi = (tipo*)realloc(v->elementi, nuova_capacita * sizeof(tipo)); \
            if (!nuovi_elementi) return 0; \
            v->elementi = nuovi_elementi; \
            v->capacita = nuova_capacita; \
        } \
        v->elementi[v->dimensione++] = elemento; \
        return 1; \
    } \
    \
    tipo ottieni_##tipo(Vettore_##tipo* v, size_t indice) { \
        if (indice < v->dimensione) \
            return v->elementi[indice]; \
        /* Gestione errore: indice fuori range */ \
        tipo valore_default; \
        memset(&valore_default, 0, sizeof(tipo)); \
        return valore_default; \
    }

// Utilizzo della macro per creare vettori di tipi specifici
DICHIARA_VETTORE(int)
DICHIARA_VETTORE(double)
DICHIARA_VETTORE(char)
```

### Macro per Algoritmi Generici

```c
// Macro per implementare un algoritmo di ordinamento generico
#define DICHIARA_QUICKSORT(tipo, compara) \
    void scambia_##tipo(tipo* a, tipo* b) { \
        tipo temp = *a; \
        *a = *b; \
        *b = temp; \
    } \
    \
    int partizione_##tipo(tipo arr[], int basso, int alto) { \
        tipo pivot = arr[alto]; \
        int i = (basso - 1); \
        \
        for (int j = basso; j <= alto - 1; j++) { \
            if (compara(arr[j], pivot) < 0) { \
                i++; \
                scambia_##tipo(&arr[i], &arr[j]); \
            } \
        } \
        scambia_##tipo(&arr[i + 1], &arr[alto]); \
        return (i + 1); \
    } \
    \
    void quicksort_##tipo(tipo arr[], int basso, int alto) { \
        if (basso < alto) { \
            int pi = partizione_##tipo(arr, basso, alto); \
            quicksort_##tipo(arr, basso, pi - 1); \
            quicksort_##tipo(arr, pi + 1, alto); \
        } \
    }

// Definizione di funzioni di confronto
#define compara_int(a, b) ((a) - (b))
#define compara_double(a, b) ((a) > (b) ? 1 : ((a) < (b) ? -1 : 0))

// Creazione di algoritmi di ordinamento per tipi specifici
DICHIARA_QUICKSORT(int, compara_int)
DICHIARA_QUICKSORT(double, compara_double)
```

## Tecniche di Type-Punning Sicure

Il type-punning consiste nell'accedere a un dato utilizzando un tipo diverso da quello con cui è stato dichiarato. Questa tecnica può essere pericolosa se non utilizzata correttamente.

### Unioni per Type-Punning Sicuro

```c
// Conversione sicura tra float e int
typedef union {
    float f;
    int i;
} FloatIntUnion;

// Esempio: implementazione di fast inverse square root
float fast_inverse_sqrt(float numero) {
    FloatIntUnion u;
    u.f = numero;
    u.i = 0x5f3759df - (u.i >> 1); // Approssimazione iniziale
    u.f = u.f * (1.5f - 0.5f * numero * u.f * u.f); // Iterazione di Newton
    return u.f;
}
```

### Utilizzo di memcpy per Type-Punning

```c
// Conversione sicura tra tipi usando memcpy
double valore_double = 3.14159;
int64_t rappresentazione;
memcpy(&rappresentazione, &valore_double, sizeof(double));

// Riconversione
double valore_originale;
memcpy(&valore_originale, &rappresentazione, sizeof(double));
```

## Emulazione di Polimorfismo in C

### Tabelle di Funzioni Virtuali

```c
// Definizione di una "classe" base
typedef struct {
    void (*distruggi)(void* this);
    void (*stampa)(void* this);
} Forma_VTable;

typedef struct {
    Forma_VTable* vtable;
} Forma;

// "Classe" derivata: Cerchio
typedef struct {
    Forma base;
    double raggio;
} Cerchio;

// Implementazioni delle funzioni virtuali per Cerchio
void cerchio_distruggi(void* this) {
    free(this);
}

void cerchio_stampa(void* this) {
    Cerchio* cerchio = (Cerchio*)this;
    printf("Cerchio con raggio %.2f\n", cerchio->raggio);
}

// Tabella delle funzioni virtuali per Cerchio
Forma_VTable cerchio_vtable = {
    cerchio_distruggi,
    cerchio_stampa
};

// Funzione di costruzione per Cerchio
Cerchio* crea_cerchio(double raggio) {
    Cerchio* cerchio = (Cerchio*)malloc(sizeof(Cerchio));
    if (cerchio) {
        cerchio->base.vtable = &cerchio_vtable;
        cerchio->raggio = raggio;
    }
    return cerchio;
}

// Utilizzo del polimorfismo
int main() {
    Cerchio* c = crea_cerchio(5.0);
    
    // Chiamata polimorfica
    Forma* f = (Forma*)c;
    f->vtable->stampa(f);
    f->vtable->distruggi(f);
    
    return 0;
}
```

## Best Practices

1. **Documentazione chiara**: Documentare attentamente le interfacce generiche e le convenzioni di utilizzo.
2. **Gestione degli errori**: Implementare meccanismi robusti per la gestione degli errori nelle funzioni generiche.
3. **Evitare macro complesse**: Limitare la complessità delle macro per mantenere la leggibilità e la manutenibilità.
4. **Test approfonditi**: Testare le implementazioni generiche con diversi tipi di dati.
5. **Considerare le alternative**: Valutare se C++ o altri linguaggi con supporto nativo per i generici potrebbero essere più adatti per il problema specifico.

## Esercizi Pratici

1. Implementare una tabella hash generica che possa memorizzare qualsiasi tipo di dato.
2. Creare un set di macro per implementare un albero binario di ricerca generico.
3. Sviluppare un sistema di gestione della memoria a pool che possa allocare oggetti di dimensioni diverse.
4. Implementare un sistema di ereditarietà in C con supporto per metodi virtuali.

## Domande di Autovalutazione

1. Quali sono i vantaggi e gli svantaggi dell'utilizzo di `void*` per implementare strutture dati generiche?
2. Come si può garantire la type safety quando si utilizzano tecniche di programmazione generica in C?
3. Quali sono i rischi associati all'uso eccessivo di macro per la programmazione generica?
4. Come si può implementare efficacemente il polimorfismo in C senza il supporto nativo del linguaggio?
5. In quali situazioni è preferibile utilizzare C++ o altri linguaggi con supporto nativo per i generici invece di implementare soluzioni in C?

## Conclusione

La programmazione generica in C, sebbene richieda tecniche più avanzate rispetto ad altri linguaggi, offre potenti strumenti per creare codice riutilizzabile e flessibile. Padroneggiando queste tecniche, è possibile sviluppare librerie e applicazioni che combinano la flessibilità della programmazione generica con l'efficienza e il controllo che caratterizzano il linguaggio C.