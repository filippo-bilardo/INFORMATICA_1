/**
 * Esempio di lista concatenata con allocazione dinamica
 * Questo esempio mostra come implementare una lista concatenata semplice
 * utilizzando l'allocazione dinamica della memoria.
 */

#include <stdio.h>
#include <stdlib.h>

// Definizione della struttura per un nodo della lista
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
    
    do {
        printf("\nOperazioni disponibili:\n");
        printf("1. Inserisci in testa\n");
        printf("2. Inserisci in coda\n");
        printf("3. Stampa lista\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        
        switch (scelta) {
            case 1:
                printf("Inserisci valore: ");
                scanf("%d", &valore);
                lista = inserisci_in_testa(lista, valore);
                break;
            case 2:
                printf("Inserisci valore: ");
                scanf("%d", &valore);
                lista = inserisci_in_coda(lista, valore);
                break;
            case 3:
                stampa_lista(lista);
                break;
            case 0:
                printf("Uscita...\n");
                break;
            default:
                printf("Scelta non valida!\n");
        }
    } while (scelta != 0);
    
    // Importante: libera la memoria prima di uscire
    libera_lista(lista);
    
    return 0;
}