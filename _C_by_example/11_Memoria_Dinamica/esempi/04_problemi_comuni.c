/**
 * Esempio di problemi comuni nella gestione della memoria dinamica
 * Questo esempio mostra alcuni problemi comuni come memory leak,
 * dangling pointers e double free, e come evitarli.
 */

#include <stdio.h>
#include <stdlib.h>

// Funzione che dimostra un memory leak
void esempio_memory_leak() {
    printf("\n--- Esempio di Memory Leak ---\n");
    
    int *p = (int *)malloc(sizeof(int));
    if (p == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return;
    }
    
    *p = 42;
    printf("Valore allocato: %d\n", *p);
    
    // Memory leak: la memoria allocata non viene liberata
    // Manca la chiamata a free(p)
    
    printf("PROBLEMA: Memory leak - la memoria allocata non è stata liberata\n");
    printf("SOLUZIONE: Chiamare sempre free() quando la memoria non serve più\n");
}

// Funzione che dimostra un dangling pointer
void esempio_dangling_pointer() {
    printf("\n--- Esempio di Dangling Pointer ---\n");
    
    int *p = (int *)malloc(sizeof(int));
    if (p == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return;
    }
    
    *p = 42;
    printf("Valore allocato: %d\n", *p);
    
    // Liberiamo la memoria
    free(p);
    
    // PROBLEMA: p è ora un dangling pointer (punta a memoria liberata)
    printf("PROBLEMA: p è ora un dangling pointer\n");
    
    // Accesso a memoria liberata - comportamento indefinito!
    // printf("Tentativo di accesso a memoria liberata: %d\n", *p); // Commentato per evitare crash
    
    printf("SOLUZIONE: Impostare il puntatore a NULL dopo free()\n");
    p = NULL; // Soluzione: impostare il puntatore a NULL dopo free
    
    // Ora possiamo controllare se il puntatore è valido
    if (p == NULL) {
        printf("Il puntatore è NULL, non possiamo dereferenziarlo\n");
    }
}

// Funzione che dimostra un double free
void esempio_double_free() {
    printf("\n--- Esempio di Double Free ---\n");
    
    int *p = (int *)malloc(sizeof(int));
    if (p == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return;
    }
    
    *p = 42;
    printf("Valore allocato: %d\n", *p);
    
    // Prima chiamata a free - corretta
    free(p);
    printf("Memoria liberata correttamente\n");
    
    // PROBLEMA: Double free - tentativo di liberare memoria già liberata
    // free(p); // Commentato per evitare crash
    
    printf("PROBLEMA: Tentativo di liberare memoria già liberata (double free)\n");
    printf("SOLUZIONE: Impostare il puntatore a NULL dopo free e controllare\n");
    
    // Soluzione: impostare il puntatore a NULL dopo free
    p = NULL;
    
    // Ora possiamo controllare se il puntatore è già stato liberato
    if (p == NULL) {
        printf("Il puntatore è NULL, non chiamiamo free()\n");
    } else {
        free(p);
    }
}

// Funzione che dimostra un buffer overflow
void esempio_buffer_overflow() {
    printf("\n--- Esempio di Buffer Overflow ---\n");
    
    int *array = (int *)malloc(5 * sizeof(int)); // Allocazione per 5 interi
    if (array == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return;
    }
    
    printf("Allocati 5 interi\n");
    
    // Inizializzazione corretta
    for (int i = 0; i < 5; i++) {
        array[i] = i * 10;
    }
    
    // PROBLEMA: Accesso oltre i limiti dell'array - buffer overflow
    printf("PROBLEMA: Tentativo di accesso oltre i limiti dell'array\n");
    // array[7] = 100; // Commentato per evitare comportamento indefinito
    
    printf("SOLUZIONE: Controllare sempre i limiti degli array\n");
    
    // Soluzione: controllare sempre i limiti
    int indice = 7;
    if (indice >= 0 && indice < 5) {
        array[indice] = 100;
    } else {
        printf("Indice %d fuori dai limiti dell'array (0-4)\n", indice);
    }
    
    free(array);
    array = NULL;
}

int main() {
    printf("Problemi comuni nella gestione della memoria dinamica\n");
    printf("=================================================\n");
    
    esempio_memory_leak();
    esempio_dangling_pointer();
    esempio_double_free();
    esempio_buffer_overflow();
    
    printf("\nRiepilogo delle best practices:\n");
    printf("1. Controllare sempre il valore di ritorno di malloc/calloc/realloc\n");
    printf("2. Liberare sempre la memoria allocata quando non serve più\n");
    printf("3. Impostare i puntatori a NULL dopo averli liberati\n");
    printf("4. Non accedere mai a memoria già liberata\n");
    printf("5. Non liberare mai memoria già liberata (double free)\n");
    printf("6. Controllare sempre i limiti degli array per evitare buffer overflow\n");
    
    return 0;
}