/**
 * File: typedef_puntatori_funzione.c
 * Descrizione: Esempi di utilizzo di typedef con puntatori a funzione in C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definizione di tipi di puntatori a funzione
typedef int (*OperazioneBinaria)(int, int);
typedef void (*ProcessaElemento)(void*);
typedef int (*ComparatoreFn)(const void*, const void*);
typedef void (*EventCallback)(const char*, void*);

// Funzioni di operazioni binarie
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
    printf("Errore: divisione per zero!\n");
    return 0;
}

// Funzione che utilizza un puntatore a funzione
int calcola(int a, int b, OperazioneBinaria operazione) {
    return operazione(a, b);
}

// Struttura per memorizzare operazioni
typedef struct {
    char nome[20];
    OperazioneBinaria operazione;
} OperazioneRegistrata;

// Esempio di callback per eventi
void onClickCallback(const char* elemento, void* dati) {
    printf("Click su '%s'\n", elemento);
    if (dati) {
        int* contatore = (int*)dati;
        (*contatore)++;
        printf("Contatore click: %d\n", *contatore);
    }
}

void onHoverCallback(const char* elemento, void* dati) {
    printf("Hover su '%s'\n", elemento);
}

// Struttura per un gestore di eventi semplice
typedef struct {
    char nome[50];
    EventCallback onClick;
    EventCallback onHover;
    void* dati;
} Elemento;

// Funzione per creare un elemento
Elemento* creaElemento(const char* nome, EventCallback onClick, EventCallback onHover, void* dati) {
    Elemento* elem = (Elemento*)malloc(sizeof(Elemento));
    if (elem) {
        strncpy(elem->nome, nome, 49);
        elem->nome[49] = '\0';
        elem->onClick = onClick;
        elem->onHover = onHover;
        elem->dati = dati;
    }
    return elem;
}

// Funzione per simulare un click su un elemento
void simulaClick(Elemento* elem) {
    if (elem && elem->onClick) {
        elem->onClick(elem->nome, elem->dati);
    }
}

// Funzione per simulare un hover su un elemento
void simulaHover(Elemento* elem) {
    if (elem && elem->onHover) {
        elem->onHover(elem->nome, elem->dati);
    }
}

// Esempio di funzioni per ordinamento
int confrontaInteri(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int confrontaStringhe(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

// Funzione generica di ordinamento che utilizza un comparatore
void ordinaArray(void* array, size_t num_elementi, size_t dimensione_elemento, ComparatoreFn comparatore) {
    qsort(array, num_elementi, dimensione_elemento, comparatore);
}

int main() {
    // Esempio 1: Utilizzo di puntatori a funzione per operazioni matematiche
    int a = 10, b = 5;
    
    printf("\n=== Esempio 1: Operazioni Matematiche ===\n");
    printf("Somma: %d\n", calcola(a, b, somma));
    printf("Sottrazione: %d\n", calcola(a, b, sottrazione));
    printf("Moltiplicazione: %d\n", calcola(a, b, moltiplicazione));
    printf("Divisione: %d\n", calcola(a, b, divisione));
    
    // Esempio 2: Array di puntatori a funzione
    OperazioneBinaria operazioni[] = {somma, sottrazione, moltiplicazione, divisione};
    char* nomi_operazioni[] = {"Somma", "Sottrazione", "Moltiplicazione", "Divisione"};
    
    printf("\n=== Esempio 2: Array di Puntatori a Funzione ===\n");
    for (int i = 0; i < 4; i++) {
        printf("%s: %d\n", nomi_operazioni[i], operazioni[i](a, b));
    }
    
    // Esempio 3: Struttura con puntatori a funzione
    OperazioneRegistrata operazioni_registrate[] = {
        {"Somma", somma},
        {"Sottrazione", sottrazione},
        {"Moltiplicazione", moltiplicazione},
        {"Divisione", divisione}
    };
    
    printf("\n=== Esempio 3: Struttura con Puntatori a Funzione ===\n");
    for (int i = 0; i < 4; i++) {
        printf("%s: %d\n", 
               operazioni_registrate[i].nome, 
               operazioni_registrate[i].operazione(a, b));
    }
    
    // Esempio 4: Callback per eventi
    int contatore_click = 0;
    
    Elemento* bottone = creaElemento("Bottone", onClickCallback, onHoverCallback, &contatore_click);
    Elemento* immagine = creaElemento("Immagine", onClickCallback, onHoverCallback, &contatore_click);
    
    printf("\n=== Esempio 4: Callback per Eventi ===\n");
    simulaHover(bottone);
    simulaClick(bottone);
    simulaClick(immagine);
    
    // Esempio 5: Ordinamento con puntatori a funzione
    int numeri[] = {5, 2, 8, 1, 9, 3};
    const char* parole[] = {"mela", "banana", "arancia", "kiwi", "fragola"};
    
    printf("\n=== Esempio 5: Ordinamento con Puntatori a Funzione ===\n");
    
    // Ordinamento di interi
    ordinaArray(numeri, 6, sizeof(int), confrontaInteri);
    printf("Numeri ordinati: ");
    for (int i = 0; i < 6; i++) {
        printf("%d ", numeri[i]);
    }
    printf("\n");
    
    // Ordinamento di stringhe
    ordinaArray(parole, 5, sizeof(char*), confrontaStringhe);
    printf("Parole ordinate: ");
    for (int i = 0; i < 5; i++) {
        printf("%s ", parole[i]);
    }
    printf("\n");
    
    // Pulizia memoria
    free(bottone);
    free(immagine);
    
    return 0;
}

/**
 * Esercizi proposti:
 * 
 * 1. Implementare un sistema di gestione eventi più complesso con più tipi di callback
 *    (onClick, onHover, onKeyPress, ecc.) utilizzando typedef per i puntatori a funzione.
 * 
 * 2. Creare una libreria di algoritmi di ordinamento (bubble sort, insertion sort, quick sort)
 *    che utilizzi puntatori a funzione per la comparazione degli elementi.
 * 
 * 3. Implementare un sistema di filtri per array che utilizzi puntatori a funzione
 *    per determinare quali elementi includere nel risultato.
 */