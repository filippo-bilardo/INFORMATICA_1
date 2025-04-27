# Typedef Avanzato

## Typedef con Puntatori a Funzione

Uno degli usi più potenti di `typedef` in C è la creazione di alias per i puntatori a funzione. La sintassi dei puntatori a funzione può essere complessa e difficile da leggere, ma `typedef` può semplificarla notevolmente.

### Sintassi Base

```c
// Senza typedef
int (*funzione_ptr)(int, int);

// Con typedef
typedef int (*FunzioneOperazione)(int, int);
FunzioneOperazione operazione;
```

### Esempio Completo

```c
#include <stdio.h>

// Definizione del tipo di puntatore a funzione
typedef int (*OperazioneBinaria)(int, int);

// Funzioni che possono essere assegnate al puntatore
int somma(int a, int b) {
    return a + b;
}

int sottrazione(int a, int b) {
    return a - b;
}

int moltiplicazione(int a, int b) {
    return a * b;
}

int divisione(int a, int b) {
    if (b != 0) return a / b;
    return 0; // Gestione semplificata della divisione per zero
}

// Funzione che utilizza il puntatore a funzione
int calcola(int a, int b, OperazioneBinaria operazione) {
    return operazione(a, b);
}

int main() {
    int a = 10, b = 5;
    
    // Utilizzo della funzione calcola con diverse operazioni
    printf("Somma: %d\n", calcola(a, b, somma));
    printf("Sottrazione: %d\n", calcola(a, b, sottrazione));
    printf("Moltiplicazione: %d\n", calcola(a, b, moltiplicazione));
    printf("Divisione: %d\n", calcola(a, b, divisione));
    
    return 0;
}
```

### Callback e Event Handling

I puntatori a funzione sono spesso utilizzati per implementare callback e gestori di eventi. `typedef` rende questo pattern più leggibile:

```c
#include <stdio.h>
#include <stdlib.h>

// Definizione del tipo di callback
typedef void (*EventCallback)(const char* evento, void* dati);

// Struttura per un gestore di eventi
typedef struct {
    EventCallback callback;
    void* dati_utente;
} GestoreEventi;

// Funzione per creare un gestore di eventi
GestoreEventi* creaGestore(EventCallback callback, void* dati) {
    GestoreEventi* gestore = (GestoreEventi*)malloc(sizeof(GestoreEventi));
    if (gestore) {
        gestore->callback = callback;
        gestore->dati_utente = dati;
    }
    return gestore;
}

// Funzione per attivare un evento
void attivaEvento(GestoreEventi* gestore, const char* nome_evento) {
    if (gestore && gestore->callback) {
        gestore->callback(nome_evento, gestore->dati_utente);
    }
}

// Esempio di callback
void mioCallback(const char* evento, void* dati) {
    int* contatore = (int*)dati;
    (*contatore)++;
    printf("Evento '%s' ricevuto! Contatore: %d\n", evento, *contatore);
}

int main() {
    int contatore = 0;
    
    // Creazione del gestore di eventi
    GestoreEventi* gestore = creaGestore(mioCallback, &contatore);
    
    // Attivazione di alcuni eventi
    attivaEvento(gestore, "click");
    attivaEvento(gestore, "mouseover");
    attivaEvento(gestore, "keypress");
    
    // Pulizia
    free(gestore);
    
    return 0;
}
```

## Tipi Astratti di Dati (TAD) con Typedef

Un'applicazione avanzata di `typedef` è la creazione di tipi astratti di dati (TAD), che nascondono i dettagli di implementazione e forniscono un'interfaccia pulita per l'utilizzo.

### Esempio: Implementazione di una Pila (Stack)

```c
// In stack.h
#ifndef STACK_H
#define STACK_H

// Definizione del tipo opaco
typedef struct Stack* StackPtr;

// Funzioni di interfaccia
StackPtr stack_create(int capacity);
void stack_destroy(StackPtr stack);
int stack_push(StackPtr stack, int value);
int stack_pop(StackPtr stack, int* value);
int stack_is_empty(StackPtr stack);
int stack_is_full(StackPtr stack);

#endif
```

```c
// In stack.c
#include <stdlib.h>
#include "stack.h"

// Implementazione effettiva della struttura
struct Stack {
    int* data;
    int top;
    int capacity;
};

StackPtr stack_create(int capacity) {
    StackPtr stack = (StackPtr)malloc(sizeof(struct Stack));
    if (stack) {
        stack->data = (int*)malloc(capacity * sizeof(int));
        if (!stack->data) {
            free(stack);
            return NULL;
        }
        stack->top = -1;
        stack->capacity = capacity;
    }
    return stack;
}

void stack_destroy(StackPtr stack) {
    if (stack) {
        free(stack->data);
        free(stack);
    }
}

int stack_push(StackPtr stack, int value) {
    if (!stack || stack_is_full(stack)) return 0;
    stack->data[++stack->top] = value;
    return 1;
}

int stack_pop(StackPtr stack, int* value) {
    if (!stack || stack_is_empty(stack)) return 0;
    *value = stack->data[stack->top--];
    return 1;
}

int stack_is_empty(StackPtr stack) {
    return stack ? stack->top == -1 : 1;
}

int stack_is_full(StackPtr stack) {
    return stack ? stack->top == stack->capacity - 1 : 1;
}
```

```c
// In main.c
#include <stdio.h>
#include "stack.h"

int main() {
    // Creazione di una pila
    StackPtr pila = stack_create(5);
    
    // Inserimento di elementi
    stack_push(pila, 10);
    stack_push(pila, 20);
    stack_push(pila, 30);
    
    // Estrazione e stampa degli elementi
    int valore;
    while (!stack_is_empty(pila)) {
        stack_pop(pila, &valore);
        printf("Valore estratto: %d\n", valore);
    }
    
    // Pulizia
    stack_destroy(pila);
    
    return 0;
}
```

## Typedef Ricorsivi e Strutture Complesse

È possibile utilizzare `typedef` per creare strutture dati ricorsive e complesse, come alberi e grafi.

### Esempio: Albero Binario

```c
#include <stdio.h>
#include <stdlib.h>

// Definizione del nodo dell'albero
typedef struct NodoAlbero {
    int valore;
    struct NodoAlbero* sinistro;
    struct NodoAlbero* destro;
} NodoAlbero;

// Definizione del tipo albero
typedef NodoAlbero* Albero;

// Funzione per creare un nuovo nodo
NodoAlbero* creaNodo(int valore) {
    NodoAlbero* nodo = (NodoAlbero*)malloc(sizeof(NodoAlbero));
    if (nodo) {
        nodo->valore = valore;
        nodo->sinistro = NULL;
        nodo->destro = NULL;
    }
    return nodo;
}

// Funzione per inserire un valore nell'albero
Albero inserisci(Albero radice, int valore) {
    if (!radice) {
        return creaNodo(valore);
    }
    
    if (valore < radice->valore) {
        radice->sinistro = inserisci(radice->sinistro, valore);
    } else if (valore > radice->valore) {
        radice->destro = inserisci(radice->destro, valore);
    }
    
    return radice;
}

// Funzione per attraversare l'albero in ordine
void attraversaInOrdine(Albero radice) {
    if (radice) {
        attraversaInOrdine(radice->sinistro);
        printf("%d ", radice->valore);
        attraversaInOrdine(radice->destro);
    }
}

// Funzione per liberare la memoria dell'albero
void distruggiAlbero(Albero radice) {
    if (radice) {
        distruggiAlbero(radice->sinistro);
        distruggiAlbero(radice->destro);
        free(radice);
    }
}

int main() {
    Albero albero = NULL;
    
    // Inserimento di valori
    albero = inserisci(albero, 50);
    albero = inserisci(albero, 30);
    albero = inserisci(albero, 70);
    albero = inserisci(albero, 20);
    albero = inserisci(albero, 40);
    albero = inserisci(albero, 60);
    albero = inserisci(albero, 80);
    
    // Attraversamento in ordine
    printf("Attraversamento in ordine: ");
    attraversaInOrdine(albero);
    printf("\n");
    
    // Pulizia
    distruggiAlbero(albero);
    
    return 0;
}
```

## Best Practices nell'Uso di Typedef

1. **Nomi Significativi**: Scegliere nomi che descrivano chiaramente lo scopo del tipo.

2. **Convenzioni di Nomenclatura**: Utilizzare PascalCase per i tipi definiti con typedef per distinguerli dai tipi primitivi.

3. **Documentazione**: Documentare chiaramente il significato e l'uso previsto dei tipi definiti.

4. **Incapsulamento**: Utilizzare typedef per nascondere i dettagli di implementazione e fornire un'interfaccia pulita.

5. **Evitare l'Abuso**: Non creare typedef solo per abbreviare nomi di tipi già semplici.

6. **Coerenza**: Mantenere uno stile coerente nell'uso di typedef in tutto il progetto.

## Conclusione

L'uso avanzato di `typedef` in C permette di creare codice più leggibile, manutenibile e robusto. Attraverso l'astrazione dei tipi di dati, è possibile nascondere i dettagli di implementazione e fornire interfacce pulite per l'utilizzo delle strutture dati e delle funzionalità del programma.

Le tecniche presentate in questo capitolo sono particolarmente utili nello sviluppo di librerie e componenti riutilizzabili, dove l'incapsulamento e la chiarezza dell'interfaccia sono fondamentali per facilitare l'uso da parte di altri sviluppatori.