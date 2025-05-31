/**
 * Soluzione Esercizio 3: Implementazione di una Lista Concatenata
 *
 * Questo programma implementa una lista concatenata semplice con funzioni per
 * inserire, cercare, eliminare elementi e liberare la memoria.
 */

#include <stdio.h>
#include <stdlib.h>

// Definizione della struttura Nodo
typedef struct Nodo {
    int valore;
    struct Nodo *successivo;
} Nodo;

// Funzione per creare un nuovo nodo
Nodo* crea_nodo(int valore) {
    Nodo *nuovo_nodo = (Nodo *)malloc(sizeof(Nodo));
    
    if (nuovo_nodo == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return NULL;
    }
    
    nuovo_nodo->valore = valore;
    nuovo_nodo->successivo = NULL;
    
    return nuovo_nodo;
}

// Funzione per inserire un nodo in testa alla lista
Nodo* inserisci_in_testa(Nodo *testa, int valore) {
    Nodo *nuovo_nodo = crea_nodo(valore);
    
    if (nuovo_nodo == NULL) {
        return testa; // Ritorna la lista originale in caso di errore
    }
    
    nuovo_nodo->successivo = testa;
    return nuovo_nodo;
}

// Funzione per inserire un nodo in coda alla lista
Nodo* inserisci_in_coda(Nodo *testa, int valore) {
    Nodo *nuovo_nodo = crea_nodo(valore);
    
    if (nuovo_nodo == NULL) {
        return testa; // Ritorna la lista originale in caso di errore
    }
    
    // Se la lista è vuota, il nuovo nodo diventa la testa
    if (testa == NULL) {
        return nuovo_nodo;
    }
    
    // Altrimenti, trova l'ultimo nodo e collega il nuovo nodo
    Nodo *corrente = testa;
    while (corrente->successivo != NULL) {
        corrente = corrente->successivo;
    }
    
    corrente->successivo = nuovo_nodo;
    return testa;
}

// Funzione per cercare un valore nella lista
int cerca(Nodo *testa, int valore) {
    Nodo *corrente = testa;
    
    while (corrente != NULL) {
        if (corrente->valore == valore) {
            return 1; // Valore trovato
        }
        corrente = corrente->successivo;
    }
    
    return 0; // Valore non trovato
}

// Funzione per eliminare la prima occorrenza di un valore dalla lista
Nodo* elimina(Nodo *testa, int valore) {
    // Se la lista è vuota, non c'è nulla da eliminare
    if (testa == NULL) {
        return NULL;
    }
    
    // Se il valore da eliminare è nella testa
    if (testa->valore == valore) {
        Nodo *nuova_testa = testa->successivo;
        free(testa);
        return nuova_testa;
    }
    
    // Cerca il nodo da eliminare
    Nodo *corrente = testa;
    while (corrente->successivo != NULL && corrente->successivo->valore != valore) {
        corrente = corrente->successivo;
    }
    
    // Se il valore è stato trovato
    if (corrente->successivo != NULL) {
        Nodo *da_eliminare = corrente->successivo;
        corrente->successivo = da_eliminare->successivo;
        free(da_eliminare);
    }
    
    return testa;
}

// Funzione per stampare la lista
void stampa_lista(Nodo *testa) {
    Nodo *corrente = testa;
    
    printf("Lista: ");
    while (corrente != NULL) {
        printf("%d -> ", corrente->valore);
        corrente = corrente->successivo;
    }
    printf("NULL\n");
}

// Funzione per liberare la memoria occupata dalla lista
void libera_lista(Nodo *testa) {
    Nodo *corrente = testa;
    Nodo *successivo;
    
    while (corrente != NULL) {
        successivo = corrente->successivo;
        free(corrente);
        corrente = successivo;
    }
}

int main() {
    Nodo *lista = NULL; // Inizializza la lista vuota
    int scelta, valore;
    
    printf("Test della lista concatenata\n");
    
    // Test inserimento in testa
    lista = inserisci_in_testa(lista, 30);
    lista = inserisci_in_testa(lista, 20);
    lista = inserisci_in_testa(lista, 10);
    printf("Dopo inserimento in testa: ");
    stampa_lista(lista);
    
    // Test inserimento in coda
    lista = inserisci_in_coda(lista, 40);
    lista = inserisci_in_coda(lista, 50);
    printf("Dopo inserimento in coda: ");
    stampa_lista(lista);
    
    // Test ricerca
    printf("Ricerca del valore 30: %s\n", cerca(lista, 30) ? "Trovato" : "Non trovato");
    printf("Ricerca del valore 60: %s\n", cerca(lista, 60) ? "Trovato" : "Non trovato");
    
    // Test eliminazione
    lista = elimina(lista, 20);
    printf("Dopo eliminazione del valore 20: ");
    stampa_lista(lista);
    
    lista = elimina(lista, 10);
    printf("Dopo eliminazione del valore 10 (testa): ");
    stampa_lista(lista);
    
    lista = elimina(lista, 50);
    printf("Dopo eliminazione del valore 50 (coda): ");
    stampa_lista(lista);
    
    // Libera la memoria
    libera_lista(lista);
    printf("Memoria liberata con successo\n");
    
    return 0;
}