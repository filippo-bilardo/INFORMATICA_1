/**
 * Soluzione Esercizio 1: Allocazione e Manipolazione di Array Dinamici
 *
 * Questo programma alloca dinamicamente un array di interi, lo riempie con valori
 * inseriti dall'utente, calcola la somma e la media degli elementi, e infine
 * libera la memoria.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    int *numeri;
    int somma = 0;
    float media;
    
    // Chiedi all'utente quanti numeri vuole inserire
    printf("Quanti numeri vuoi inserire? ");
    scanf("%d", &n);
    
    // Verifica che il numero sia valido
    if (n <= 0) {
        printf("Il numero deve essere positivo.\n");
        return 1;
    }
    
    // Allocazione dinamica dell'array
    numeri = (int *)malloc(n * sizeof(int));
    
    // Verifica se l'allocazione è riuscita
    if (numeri == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return 1;
    }
    
    // Lettura dei numeri inseriti dall'utente
    printf("Inserisci %d numeri:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Numero %d: ", i + 1);
        scanf("%d", &numeri[i]);
        somma += numeri[i]; // Calcolo della somma durante l'inserimento
    }
    
    // Calcolo della media
    media = (float)somma / n;
    
    // Visualizzazione dei risultati
    printf("\nNumeri inseriti: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", numeri[i]);
    }
    printf("\n");
    
    printf("Somma: %d\n", somma);
    printf("Media: %.2f\n", media);
    
    // Liberazione della memoria
    free(numeri);
    numeri = NULL; // Buona pratica: impostare il puntatore a NULL dopo free
    
    return 0;
}