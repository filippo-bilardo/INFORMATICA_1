#include <stdio.h>

#define RIGHE 3
#define COLONNE 4

// Funzione che accetta una matrice come array appiattito
void modificaMatrice(int *matrice, int righe, int colonne) {
    // Aggiungi gli indici di riga e colonna a ogni elemento
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            matrice[i*colonne + j] += (i + j);
        }
    }
}

// Funzione per stampare la matrice
void stampaMatrice(int *matrice, int righe, int colonne) {
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            printf("%3d ", matrice[i*colonne + j]);
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
    stampaMatrice((int *)miaMatrice, RIGHE, COLONNE);
    
    // Modifica la matrice
    modificaMatrice((int *)miaMatrice, RIGHE, COLONNE);
    
    printf("\nMatrice modificata (ogni elemento aumentato della somma dei suoi indici):\n");
    stampaMatrice((int *)miaMatrice, RIGHE, COLONNE);
    
    return 0;
}
