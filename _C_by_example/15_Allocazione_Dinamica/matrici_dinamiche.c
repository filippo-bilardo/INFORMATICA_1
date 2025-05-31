/**
 * @file matrici_dinamiche.c
 * @brief Allocazione dinamica di matrici bidimensionali
 * @details Questo programma dimostra come allocare, manipolare e liberare matrici dinamiche
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Funzione per allocare una matrice dinamica (approccio array di puntatori)
int** alloca_matrice(int righe, int colonne) {
    // Allocazione dell'array di puntatori alle righe
    int **matrice = (int **)malloc(righe * sizeof(int *));
    
    // Verifica se l'allocazione è avvenuta con successo
    if (matrice == NULL) {
        return NULL;
    }
    
    // Allocazione di ogni riga
    for (int i = 0; i < righe; i++) {
        matrice[i] = (int *)malloc(colonne * sizeof(int));
        
        // Se l'allocazione di una riga fallisce, liberiamo la memoria già allocata
        if (matrice[i] == NULL) {
            // Liberazione delle righe già allocate
            for (int j = 0; j < i; j++) {
                free(matrice[j]);
            }
            // Liberazione dell'array di puntatori
            free(matrice);
            return NULL;
        }
    }
    
    return matrice;
}

// Funzione per allocare una matrice in memoria contigua
int** alloca_matrice_contigua(int righe, int colonne) {
    // Allocazione dell'array di puntatori alle righe
    int **matrice = (int **)malloc(righe * sizeof(int *));
    
    // Verifica se l'allocazione è avvenuta con successo
    if (matrice == NULL) {
        return NULL;
    }
    
    // Allocazione di un unico blocco per tutti gli elementi della matrice
    int *dati = (int *)malloc(righe * colonne * sizeof(int));
    
    // Se l'allocazione fallisce, liberiamo la memoria già allocata
    if (dati == NULL) {
        free(matrice);
        return NULL;
    }
    
    // Impostazione dei puntatori alle righe
    for (int i = 0; i < righe; i++) {
        matrice[i] = dati + (i * colonne);
    }
    
    return matrice;
}

// Funzione per inizializzare una matrice con valori casuali
void inizializza_matrice(int **matrice, int righe, int colonne, int min, int max) {
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            matrice[i][j] = min + rand() % (max - min + 1);
        }
    }
}

// Funzione per stampare una matrice
void stampa_matrice(int **matrice, int righe, int colonne) {
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            printf("%4d ", matrice[i][j]);
        }
        printf("\n");
    }
}

// Funzione per liberare la memoria di una matrice (approccio array di puntatori)
void libera_matrice(int **matrice, int righe) {
    if (matrice == NULL) {
        return;
    }
    
    // Liberazione di ogni riga
    for (int i = 0; i < righe; i++) {
        free(matrice[i]);
    }
    
    // Liberazione dell'array di puntatori
    free(matrice);
}

// Funzione per liberare la memoria di una matrice contigua
void libera_matrice_contigua(int **matrice) {
    if (matrice == NULL) {
        return;
    }
    
    // Liberazione del blocco di dati (prima riga)
    free(matrice[0]);
    
    // Liberazione dell'array di puntatori
    free(matrice);
}

// Funzione per calcolare il prodotto matrice-vettore
int* prodotto_matrice_vettore(int **matrice, int *vettore, int righe, int colonne) {
    // Allocazione del vettore risultato
    int *risultato = (int *)malloc(righe * sizeof(int));
    
    // Verifica se l'allocazione è avvenuta con successo
    if (risultato == NULL) {
        return NULL;
    }
    
    // Calcolo del prodotto matrice-vettore
    for (int i = 0; i < righe; i++) {
        risultato[i] = 0;
        for (int j = 0; j < colonne; j++) {
            risultato[i] += matrice[i][j] * vettore[j];
        }
    }
    
    return risultato;
}

int main() {
    int righe, colonne, min, max;
    int **matrice = NULL;
    int *vettore = NULL;
    int *risultato = NULL;
    int tipo_allocazione;
    
    // Inizializzazione del generatore di numeri casuali
    srand(time(NULL));
    
    // Richiesta all'utente dei parametri per la matrice
    printf("Inserisci il numero di righe: ");
    scanf("%d", &righe);
    
    printf("Inserisci il numero di colonne: ");
    scanf("%d", &colonne);
    
    printf("Inserisci il valore minimo: ");
    scanf("%d", &min);
    
    printf("Inserisci il valore massimo: ");
    scanf("%d", &max);
    
    printf("Scegli il tipo di allocazione (1: standard, 2: contigua): ");
    scanf("%d", &tipo_allocazione);
    
    // Allocazione della matrice in base alla scelta dell'utente
    if (tipo_allocazione == 1) {
        matrice = alloca_matrice(righe, colonne);
    } else {
        matrice = alloca_matrice_contigua(righe, colonne);
    }
    
    // Verifica se l'allocazione è avvenuta con successo
    if (matrice == NULL) {
        printf("Errore: Allocazione della matrice fallita\n");
        return 1;
    }
    
    // Inizializzazione della matrice con valori casuali
    inizializza_matrice(matrice, righe, colonne, min, max);
    
    // Stampa della matrice
    printf("\nMatrice generata:\n");
    stampa_matrice(matrice, righe, colonne);
    
    // Allocazione e inizializzazione del vettore
    vettore = (int *)malloc(colonne * sizeof(int));
    if (vettore == NULL) {
        printf("Errore: Allocazione del vettore fallita\n");
        // Liberazione della matrice in base al tipo di allocazione
        if (tipo_allocazione == 1) {
            libera_matrice(matrice, righe);
        } else {
            libera_matrice_contigua(matrice);
        }
        return 1;
    }
    
    // Inizializzazione del vettore con valori casuali
    printf("\nVettore generato:\n");
    for (int i = 0; i < colonne; i++) {
        vettore[i] = min + rand() % (max - min + 1);
        printf("%d ", vettore[i]);
    }
    printf("\n");
    
    // Calcolo del prodotto matrice-vettore
    risultato = prodotto_matrice_vettore(matrice, vettore, righe, colonne);
    
    // Verifica se il calcolo è avvenuto con successo
    if (risultato == NULL) {
        printf("Errore: Calcolo del prodotto matrice-vettore fallito\n");
        free(vettore);
        // Liberazione della matrice in base al tipo di allocazione
        if (tipo_allocazione == 1) {
            libera_matrice(matrice, righe);
        } else {
            libera_matrice_contigua(matrice);
        }
        return 1;
    }
    
    // Stampa del risultato
    printf("\nRisultato del prodotto matrice-vettore:\n");
    for (int i = 0; i < righe; i++) {
        printf("%d ", risultato[i]);
    }
    printf("\n");
    
    // Liberazione della memoria allocata
    free(vettore);
    free(risultato);
    
    // Liberazione della matrice in base al tipo di allocazione
    if (tipo_allocazione == 1) {
        libera_matrice(matrice, righe);
    } else {
        libera_matrice_contigua(matrice);
    }
    
    printf("\nMemoria liberata con successo!\n");
    
    return 0;
}