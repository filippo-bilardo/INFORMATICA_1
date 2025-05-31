/**
 * @file array_dinamici.c
 * @brief Creazione e gestione di array con dimensione determinata a runtime
 * @details Questo programma dimostra come creare, manipolare e gestire array dinamici
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Funzione per creare un array dinamico di interi casuali
int* crea_array_casuale(int dimensione, int min, int max) {
    // Allocazione dinamica dell'array
    int *array = (int *)malloc(dimensione * sizeof(int));
    
    // Verifica se l'allocazione è avvenuta con successo
    if (array == NULL) {
        return NULL;
    }
    
    // Inizializzazione con numeri casuali
    for (int i = 0; i < dimensione; i++) {
        array[i] = min + rand() % (max - min + 1);
    }
    
    return array;
}

// Funzione per stampare un array
void stampa_array(int *array, int dimensione) {
    for (int i = 0; i < dimensione; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// Funzione per ridimensionare un array preservando i dati esistenti
int* ridimensiona_array(int *array, int vecchia_dim, int nuova_dim) {
    // Utilizzo di realloc per ridimensionare l'array
    int *nuovo_array = (int *)realloc(array, nuova_dim * sizeof(int));
    
    // Verifica se il ridimensionamento è avvenuto con successo
    if (nuovo_array == NULL) {
        return NULL; // L'array originale rimane valido
    }
    
    // Se la nuova dimensione è maggiore, inizializziamo i nuovi elementi
    if (nuova_dim > vecchia_dim) {
        for (int i = vecchia_dim; i < nuova_dim; i++) {
            nuovo_array[i] = 0; // Inizializzazione a 0
        }
    }
    
    return nuovo_array;
}

// Funzione per ordinare un array (algoritmo bubble sort)
void ordina_array(int *array, int dimensione) {
    for (int i = 0; i < dimensione - 1; i++) {
        for (int j = 0; j < dimensione - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                // Scambio degli elementi
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int main() {
    int dimensione, min, max, nuova_dimensione;
    int *array = NULL;
    
    // Inizializzazione del generatore di numeri casuali
    srand(time(NULL));
    
    // Richiesta all'utente dei parametri per l'array
    printf("Inserisci la dimensione dell'array: ");
    scanf("%d", &dimensione);
    
    printf("Inserisci il valore minimo: ");
    scanf("%d", &min);
    
    printf("Inserisci il valore massimo: ");
    scanf("%d", &max);
    
    // Creazione dell'array dinamico
    array = crea_array_casuale(dimensione, min, max);
    
    // Verifica se la creazione è avvenuta con successo
    if (array == NULL) {
        printf("Errore: Creazione dell'array fallita\n");
        return 1;
    }
    
    // Stampa dell'array originale
    printf("\nArray originale:\n");
    stampa_array(array, dimensione);
    
    // Ordinamento dell'array
    ordina_array(array, dimensione);
    
    // Stampa dell'array ordinato
    printf("\nArray ordinato:\n");
    stampa_array(array, dimensione);
    
    // Ridimensionamento dell'array
    printf("\nInserisci la nuova dimensione dell'array: ");
    scanf("%d", &nuova_dimensione);
    
    int *nuovo_array = ridimensiona_array(array, dimensione, nuova_dimensione);
    
    // Verifica se il ridimensionamento è avvenuto con successo
    if (nuovo_array == NULL) {
        printf("Errore: Ridimensionamento fallito\n");
        free(array);
        return 1;
    }
    
    // Aggiornamento del puntatore e della dimensione
    array = nuovo_array;
    dimensione = nuova_dimensione;
    
    // Stampa dell'array ridimensionato
    printf("\nArray ridimensionato:\n");
    stampa_array(array, dimensione);
    
    // Liberazione della memoria allocata
    free(array);
    array = NULL;
    
    printf("\nMemoria liberata con successo!\n");
    
    return 0;
}