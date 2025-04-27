/**
 * Esempio di allocazione dinamica di un array
 * Questo esempio mostra come allocare dinamicamente un array di interi,
 * inizializzarlo, utilizzarlo e infine liberare la memoria.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    int *array;
    
    printf("Inserisci la dimensione dell'array: ");
    scanf("%d", &n);
    
    // Allocazione dinamica dell'array
    array = (int *)malloc(n * sizeof(int));
    
    if (array == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return 1;
    }
    
    // Inizializzazione dell'array
    for (int i = 0; i < n; i++) {
        array[i] = i * 10;
    }
    
    // Utilizzo dell'array
    printf("Elementi dell'array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    // Liberazione della memoria
    free(array);
    array = NULL; // Buona pratica: impostare il puntatore a NULL dopo free
    
    return 0;
}