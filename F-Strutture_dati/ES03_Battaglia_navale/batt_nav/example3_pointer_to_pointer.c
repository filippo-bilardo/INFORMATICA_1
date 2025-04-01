#include <stdio.h>
#include <stdlib.h>

// Funzione che accetta una matrice come puntatore a puntatore
void modificaMatrice(int **matrice, int righe, int colonne) {
    // Sottrai il numero di colonna da ogni elemento
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            matrice[i][j] -= j;
        }
    }
}

// Funzione per stampare la matrice
void stampaMatrice(int **matrice, int righe, int colonne) {
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            printf("%3d ", matrice[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int righe = 3;
    int colonne = 4;
    
    // Alloca dinamicamente una matrice
    int **miaMatrice = (int **)malloc(righe * sizeof(int *));
    for (int i = 0; i < righe; i++) {
        miaMatrice[i] = (int *)malloc(colonne * sizeof(int));
        // Inizializza con valori
        for (int j = 0; j < colonne; j++) {
            miaMatrice[i][j] = i * colonne + j + 1;
        }
    }
    
    printf("Matrice originale:\n");
    stampaMatrice(miaMatrice, righe, colonne);
    
    // Modifica la matrice
    modificaMatrice(miaMatrice, righe, colonne);
    
    printf("\nMatrice modificata (ogni elemento diminuito del suo numero di colonna):\n");
    stampaMatrice(miaMatrice, righe, colonne);
    
    // Libera la memoria allocata
    for (int i = 0; i < righe; i++) {
        free(miaMatrice[i]);
    }
    free(miaMatrice);
    
    return 0;
}
