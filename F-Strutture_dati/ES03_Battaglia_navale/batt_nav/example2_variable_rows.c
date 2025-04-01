#include <stdio.h>

#define COLONNE 4

// Funzione che accetta una matrice con righe variabili ma colonne fisse
void modificaMatrice(int matrice[][COLONNE], int righe) {
    // Aggiungi il numero di riga a ogni elemento
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < COLONNE; j++) {
            matrice[i][j] += i;
        }
    }
}

// Funzione per stampare la matrice
void stampaMatrice(int matrice[][COLONNE], int righe) {
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < COLONNE; j++) {
            printf("%3d ", matrice[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Inizializza una matrice 3x4
    int miaMatrice[3][COLONNE] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    printf("Matrice originale:\n");
    stampaMatrice(miaMatrice, 3);
    
    // Modifica la matrice
    modificaMatrice(miaMatrice, 3);
    
    printf("\nMatrice modificata (ogni elemento aumentato del suo numero di riga):\n");
    stampaMatrice(miaMatrice, 3);
    
    return 0;
}
