/**
 * @file calloc_realloc_esempio.c
 * @brief Esempio di utilizzo di calloc e realloc
 * @details Questo programma dimostra come allocare memoria con calloc e ridimensionarla con realloc
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    // Dichiarazione di un puntatore a int
    int *ptr;
    int n, nuovo_n;
    
    // Richiesta all'utente della dimensione iniziale dell'array
    printf("Inserisci la dimensione iniziale dell'array: ");
    scanf("%d", &n);
    
    // Allocazione dinamica di memoria con calloc
    // calloc alloca n elementi di dimensione sizeof(int) e li inizializza a 0
    ptr = (int *)calloc(n, sizeof(int));
    
    // Verifica se l'allocazione è avvenuta con successo
    if (ptr == NULL) {
        printf("Errore: Allocazione di memoria fallita\n");
        return 1; // Uscita con codice di errore
    }
    
    // Dimostrazione che calloc inizializza la memoria a 0
    printf("\nValori inizializzati da calloc:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", ptr[i]); // Tutti i valori saranno 0
    }
    printf("\n");
    
    // Inizializzazione dell'array con valori
    printf("\nInserisci %d numeri:\n", n);
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
    
    // Ridimensionamento dell'array con realloc
    printf("\nInserisci la nuova dimensione dell'array: ");
    scanf("%d", &nuovo_n);
    
    // Utilizzo di realloc per ridimensionare l'array
    int *nuovo_ptr = (int *)realloc(ptr, nuovo_n * sizeof(int));
    
    // Verifica se il ridimensionamento è avvenuto con successo
    if (nuovo_ptr == NULL) {
        printf("Errore: Ridimensionamento fallito\n");
        free(ptr); // Importante: liberare la memoria originale in caso di errore
        return 1;
    }
    
    // Aggiornamento del puntatore
    ptr = nuovo_ptr;
    
    // Se la nuova dimensione è maggiore, inizializziamo i nuovi elementi
    if (nuovo_n > n) {
        printf("\nInserisci i %d numeri aggiuntivi:\n", nuovo_n - n);
        for (int i = n; i < nuovo_n; i++) {
            printf("Numero %d: ", i+1);
            scanf("%d", &ptr[i]);
        }
    }
    
    // Stampa dell'array ridimensionato
    printf("\nArray ridimensionato:\n");
    for (int i = 0; i < nuovo_n; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");
    
    // Liberazione della memoria allocata
    free(ptr);
    
    // Buona pratica: impostare il puntatore a NULL dopo free
    ptr = NULL;
    
    printf("\nMemoria liberata con successo!\n");
    
    return 0;
}