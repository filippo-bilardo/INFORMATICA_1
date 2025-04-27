/**
 * Esempio di allocazione dinamica di una matrice
 * Questo esempio mostra come allocare dinamicamente una matrice bidimensionale,
 * inizializzarla, utilizzarla e infine liberare la memoria.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int righe, colonne;
    int **matrice;
    
    printf("Inserisci il numero di righe: ");
    scanf("%d", &righe);
    printf("Inserisci il numero di colonne: ");
    scanf("%d", &colonne);
    
    // Allocazione dinamica della matrice
    // Prima allocazione dell'array di puntatori (righe)
    matrice = (int **)malloc(righe * sizeof(int *));
    
    if (matrice == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return 1;
    }
    
    // Poi allocazione di ogni riga
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
    
    // Inizializzazione della matrice
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            matrice[i][j] = i * colonne + j;
        }
    }
    
    // Utilizzo della matrice
    printf("Elementi della matrice:\n");
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            printf("%3d ", matrice[i][j]);
        }
        printf("\n");
    }
    
    // Liberazione della memoria
    // Prima libera ogni riga
    for (int i = 0; i < righe; i++) {
        free(matrice[i]);
    }
    // Poi libera l'array di puntatori
    free(matrice);
    matrice = NULL; // Buona pratica
    
    return 0;
}