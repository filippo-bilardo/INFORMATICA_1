#include <stdio.h>

#define RIGHE 3
#define COLONNE 4

// Funzione che accetta una matrice con dimensioni fisse
void modificaMatrice(int matrice[RIGHE][COLONNE]) {
    // Moltiplica ogni elemento per 2
    for (int i = 0; i < RIGHE; i++) {
        for (int j = 0; j < COLONNE; j++) {
            matrice[i][j] *= 2;
        }
    }
}

// Funzione per stampare la matrice
void stampaMatrice(int matrice[RIGHE][COLONNE]) {
    for (int i = 0; i < RIGHE; i++) {
        for (int j = 0; j < COLONNE; j++) {
            printf("%3d ", matrice[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Inizializza una matrice 3x4
    int miaMatrice[RIGHE][COLONNE] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    printf("Matrice originale:\n");
    stampaMatrice(miaMatrice);
    
    // Modifica la matrice
    modificaMatrice(miaMatrice);
    
    printf("\nMatrice modificata (ogni elemento moltiplicato per 2):\n");
    stampaMatrice(miaMatrice);
    
    return 0;
}
