#include <stdio.h>

#define COLONNE 3

// Funzione che accetta una matrice con dimensioni fisse
void modificaMatrice(int matrice[][COLONNE], int righe) {
    // Moltiplica ogni elemento per 2
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < COLONNE; j++) {
            matrice[i][j] *= 2;
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
    // Inizializzazione completa
    int matrice1[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Inizializzazione con un valore predefinito (es. tutti zero)
    int matrice2[5][3] = {0};

    // Inizializzazione parziale (gli elementi non specificati vengono inizializzati a zero):
    int matrice3[3][3] = {
        {10, 11},
        {20},
        {30, 31, 32}
    };

    //Inizializzazione lineare (il compilatore riempie l'array per righe):
    int matrice4[3][3] = {10, 11, 12, 13, 14, 15, 16, 17, 18};
    
    printf("Stampa matrice 1:\n");
    stampaMatrice(matrice1, 3);
    printf("\nStampa matrice 2:\n");
    stampaMatrice(matrice2, 5);
    printf("\nStampa matrice 3:\n");
    stampaMatrice(matrice3, 3);
    printf("\nStampa matrice 4:\n");
    stampaMatrice(matrice4, 3);
    printf("\n");
    
    return 0;
}
