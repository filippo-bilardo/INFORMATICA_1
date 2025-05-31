/**
 * @file malloc_esempio.c
 * @brief Esempio di utilizzo base di malloc e free
 * @details Questo programma dimostra come allocare e liberare memoria dinamicamente
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    // Dichiarazione di un puntatore a int
    int *ptr;
    int n;
    
    // Richiesta all'utente della dimensione dell'array
    printf("Inserisci la dimensione dell'array: ");
    scanf("%d", &n);
    
    // Allocazione dinamica di memoria per un array di n interi
    ptr = (int *)malloc(n * sizeof(int));
    
    // Verifica se l'allocazione è avvenuta con successo
    if (ptr == NULL) {
        printf("Errore: Allocazione di memoria fallita\n");
        return 1; // Uscita con codice di errore
    }
    
    // Inizializzazione dell'array con valori
    printf("Inserisci %d numeri:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Numero %d: ", i+1);
        scanf("%d", &ptr[i]);
    }
    
    // Stampa dei valori inseriti
    printf("\nValori inseriti:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");
    
    // Calcolo della somma e della media
    int somma = 0;
    for (int i = 0; i < n; i++) {
        somma += ptr[i];
    }
    float media = (float)somma / n;
    
    printf("Somma: %d\n", somma);
    printf("Media: %.2f\n", media);
    
    // Liberazione della memoria allocata
    free(ptr);
    
    // Buona pratica: impostare il puntatore a NULL dopo free
    ptr = NULL;
    
    printf("\nMemoria liberata con successo!\n");
    
    return 0;
}