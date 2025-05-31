/**
 * Soluzione Esercizio 2: Gestione di una Matrice Dinamica
 *
 * Questo programma alloca dinamicamente una matrice di dimensioni specificate dall'utente,
 * la riempie con valori casuali, calcola la somma di ogni riga e colonna, e infine
 * libera la memoria.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int righe, colonne;
    int **matrice;
    int *somma_righe, *somma_colonne;
    
    // Inizializzazione del generatore di numeri casuali
    srand(time(NULL));
    
    // Chiedi all'utente le dimensioni della matrice
    printf("Inserisci il numero di righe: ");
    scanf("%d", &righe);
    printf("Inserisci il numero di colonne: ");
    scanf("%d", &colonne);
    
    // Verifica che le dimensioni siano valide
    if (righe <= 0 || colonne <= 0) {
        printf("Le dimensioni devono essere positive.\n");
        return 1;
    }
    
    // Allocazione dinamica della matrice
    matrice = (int **)malloc(righe * sizeof(int *));
    if (matrice == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return 1;
    }
    
    // Allocazione di ogni riga
    for (int i = 0; i < righe; i++) {
        matrice[i] = (int *)malloc(colonne * sizeof(int));
        if (matrice[i] == NULL) {
            // Gestione dell'errore: libera la memoria già allocata
            for (int j = 0; j < i; j++) {
                free(matrice[j]);
            }
            free(matrice);
            printf("Errore: allocazione memoria fallita\n");
            return 1;
        }
    }
    
    // Allocazione degli array per le somme
    somma_righe = (int *)calloc(righe, sizeof(int));
    somma_colonne = (int *)calloc(colonne, sizeof(int));
    
    if (somma_righe == NULL || somma_colonne == NULL) {
        // Gestione dell'errore: libera tutta la memoria già allocata
        for (int i = 0; i < righe; i++) {
            free(matrice[i]);
        }
        free(matrice);
        if (somma_righe != NULL) free(somma_righe);
        if (somma_colonne != NULL) free(somma_colonne);
        printf("Errore: allocazione memoria fallita\n");
        return 1;
    }
    
    // Riempimento della matrice con numeri casuali tra 1 e 100
    printf("\nMatrice generata:\n");
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            matrice[i][j] = rand() % 100 + 1; // Numeri tra 1 e 100
            printf("%3d ", matrice[i][j]);
            
            // Aggiornamento delle somme
            somma_righe[i] += matrice[i][j];
            somma_colonne[j] += matrice[i][j];
        }
        printf("\n");
    }
    
    // Visualizzazione delle somme delle righe
    printf("\nSomma delle righe:\n");
    for (int i = 0; i < righe; i++) {
        printf("Riga %d: %d\n", i + 1, somma_righe[i]);
    }
    
    // Visualizzazione delle somme delle colonne
    printf("\nSomma delle colonne:\n");
    for (int j = 0; j < colonne; j++) {
        printf("Colonna %d: %d\n", j + 1, somma_colonne[j]);
    }
    
    // Liberazione della memoria
    // Prima libera gli array delle somme
    free(somma_righe);
    free(somma_colonne);
    
    // Poi libera ogni riga della matrice
    for (int i = 0; i < righe; i++) {
        free(matrice[i]);
    }
    
    // Infine libera l'array di puntatori
    free(matrice);
    
    // Buona pratica: impostare i puntatori a NULL dopo free
    somma_righe = NULL;
    somma_colonne = NULL;
    matrice = NULL;
    
    return 0;
}