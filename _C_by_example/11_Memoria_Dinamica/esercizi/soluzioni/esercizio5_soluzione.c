/**
 * Soluzione Esercizio 5: Rilevamento di Memory Leak
 *
 * Questo programma identifica e corregge i memory leak presenti nel codice originale.
 * Ogni funzione è stata modificata per gestire correttamente la memoria allocata.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funzione 1: Mancava la deallocazione della memoria
void funzione1() {
    int *p = (int *)malloc(sizeof(int) * 10);
    if (p == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return;
    }
    
    // Uso di p...
    for (int i = 0; i < 10; i++) {
        p[i] = i * 2;
    }
    printf("Funzione1: Memoria allocata e inizializzata correttamente\n");
    
    // Correzione: aggiunta la deallocazione della memoria
    free(p);
    printf("Funzione1: Memoria deallocata correttamente\n");
}

// Funzione 2: Perdita del riferimento alla memoria allocata
void funzione2() {
    char *str = (char *)malloc(100);
    if (str == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return;
    }
    
    // Uso di str...
    strcpy(str, "Esempio di stringa");
    printf("Funzione2: Stringa allocata: %s\n", str);
    
    // Correzione: deallocare la memoria prima di perdere il riferimento
    free(str);
    str = NULL; // Ora è sicuro assegnare NULL dopo aver liberato la memoria
    printf("Funzione2: Memoria deallocata correttamente\n");
}

// Funzione 3: Ritorno di memoria allocata senza gestione
int* funzione3_corretta() {
    int *array = (int *)malloc(sizeof(int) * 5);
    if (array == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return NULL;
    }
    
    // Inizializzazione dell'array
    for (int i = 0; i < 5; i++) {
        array[i] = i + 1;
    }
    printf("Funzione3: Array allocato e inizializzato correttamente\n");
    
    // Nota: la memoria allocata deve essere liberata dal chiamante
    return array;
}

// Funzione 4: Allocazione multipla senza deallocazione
void funzione4() {
    int **matrice = (int **)malloc(sizeof(int *) * 3);
    if (matrice == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return;
    }
    
    // Allocazione delle righe
    for (int i = 0; i < 3; i++) {
        matrice[i] = (int *)malloc(sizeof(int) * 4);
        if (matrice[i] == NULL) {
            // Gestione dell'errore: libera la memoria già allocata
            for (int j = 0; j < i; j++) {
                free(matrice[j]);
            }
            free(matrice);
            printf("Errore: allocazione memoria fallita\n");
            return;
        }
        
        // Inizializzazione della riga
        for (int j = 0; j < 4; j++) {
            matrice[i][j] = i * 4 + j;
        }
    }
    
    printf("Funzione4: Matrice allocata e inizializzata correttamente\n");
    
    // Correzione: deallocazione in ordine inverso rispetto all'allocazione
    for (int i = 0; i < 3; i++) {
        free(matrice[i]);
    }
    free(matrice);
    printf("Funzione4: Memoria deallocata correttamente\n");
}

// Funzione 5: Gestione corretta della memoria in caso di errore
void funzione5() {
    char *str1 = (char *)malloc(100);
    if (str1 == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return;
    }
    
    char *str2 = (char *)malloc(200);
    if (str2 == NULL) {
        // Correzione: deallocazione della memoria già allocata in caso di errore
        free(str1);
        printf("Errore: allocazione memoria fallita\n");
        return;
    }
    
    // Uso delle stringhe
    strcpy(str1, "Prima stringa");
    strcpy(str2, "Seconda stringa");
    printf("Funzione5: Stringhe allocate: %s, %s\n", str1, str2);
    
    // Deallocazione corretta
    free(str1);
    free(str2);
    printf("Funzione5: Memoria deallocata correttamente\n");
}

int main() {
    printf("Programma di dimostrazione per la correzione di memory leak\n\n");
    
    // Test delle funzioni corrette
    funzione1();
    printf("\n");
    
    funzione2();
    printf("\n");
    
    // Per funzione3, dobbiamo gestire la memoria restituita
    int *risultato = funzione3_corretta();
    if (risultato != NULL) {
        printf("Main: Risultato ricevuto da funzione3: ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", risultato[i]);
        }
        printf("\n");
        
        // Importante: deallocare la memoria restituita da funzione3
        free(risultato);
        printf("Main: Memoria restituita da funzione3 deallocata correttamente\n");
    }
    printf("\n");
    
    funzione4();
    printf("\n");
    
    funzione5();
    printf("\n");
    
    printf("Tutte le funzioni hanno gestito correttamente la memoria!\n");
    return 0;
}