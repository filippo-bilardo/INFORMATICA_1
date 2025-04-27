/**
 * Esempio di utilizzo degli strumenti di debug della memoria
 * Questo esempio mostra come creare programmi con errori di memoria
 * e come utilizzare strumenti come Valgrind e AddressSanitizer per rilevarli.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funzione che dimostra un memory leak
void esempio_memory_leak() {
    printf("\n--- Esempio di Memory Leak ---\n");
    
    // Allocazione di memoria che non viene mai liberata
    int *array = (int *)malloc(10 * sizeof(int));
    if (array == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return;
    }
    
    // Inizializzazione e utilizzo dell'array
    for (int i = 0; i < 10; i++) {
        array[i] = i;
    }
    
    printf("Array inizializzato correttamente\n");
    
    // PROBLEMA: manca free(array)
    // Questo causerà un memory leak che Valgrind rileverà
    
    printf("NOTA: Valgrind mostrerà un memory leak di %lu bytes\n", 10 * sizeof(int));
}

// Funzione che dimostra un uso dopo free (use-after-free)
void esempio_use_after_free() {
    printf("\n--- Esempio di Use-After-Free ---\n");
    
    char *str = (char *)malloc(20);
    if (str == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return;
    }
    
    strcpy(str, "Hello, World!");
    printf("Stringa originale: %s\n", str);
    
    // Liberiamo la memoria
    free(str);
    printf("Memoria liberata\n");
    
    // PROBLEMA: accesso a memoria già liberata
    // Questo è un comportamento indefinito che AddressSanitizer rileverà
    // printf("Tentativo di accesso a memoria liberata: %s\n", str); // Commentato per evitare crash
    
    printf("NOTA: Se decommentata, la riga sopra causerebbe un errore use-after-free\n");
}

// Funzione che dimostra un buffer overflow
void esempio_buffer_overflow() {
    printf("\n--- Esempio di Buffer Overflow ---\n");
    
    int *array = (int *)malloc(5 * sizeof(int)); // Allocazione per 5 interi
    if (array == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return;
    }
    
    printf("Allocati 5 interi (%lu bytes)\n", 5 * sizeof(int));
    
    // PROBLEMA: scrittura oltre i limiti dell'array
    // Questo è un buffer overflow che sia Valgrind che AddressSanitizer rileveranno
    for (int i = 0; i < 10; i++) { // Nota: ciclo fino a 10 invece di 5
        array[i] = i * 10;
        printf("array[%d] = %d\n", i, array[i]);
        
        if (i >= 5) {
            printf("ATTENZIONE: Stiamo scrivendo oltre i limiti dell'array!\n");
        }
    }
    
    free(array);
    printf("NOTA: Valgrind e AddressSanitizer rileveranno un buffer overflow\n");
}

// Funzione che dimostra un accesso a memoria non inizializzata
void esempio_memoria_non_inizializzata() {
    printf("\n--- Esempio di Accesso a Memoria Non Inizializzata ---\n");
    
    int *array = (int *)malloc(5 * sizeof(int));
    if (array == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return;
    }
    
    // PROBLEMA: utilizzo di valori non inizializzati
    // Valgrind rileverà questo problema
    int somma = 0;
    for (int i = 0; i < 5; i++) {
        // Non inizializziamo array[i], ma lo utilizziamo comunque
        somma += array[i];
    }
    
    printf("Somma degli elementi non inizializzati: %d\n", somma);
    printf("NOTA: Valgrind rileverà l'uso di memoria non inizializzata\n");
    
    free(array);
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
    // Questo causerà un errore che sia Valgrind che AddressSanitizer rileveranno
    // free(p); // Commentato per evitare crash
    
    printf("NOTA: Se decommentata, la riga sopra causerebbe un errore double-free\n");
}

// Funzione principale che mostra come compilare ed eseguire con strumenti di debug
int main() {
    printf("=== ESEMPI DI ERRORI DI MEMORIA E COME RILEVARLI ===\n");
    printf("Questo programma contiene diversi errori di memoria comuni.\n");
    printf("Per rilevarli, puoi utilizzare i seguenti strumenti:\n\n");
    
    printf("1. Valgrind (Linux/macOS):\n");
    printf("   $ gcc -g -O0 06_debug_memoria.c -o debug_memoria\n");
    printf("   $ valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./debug_memoria\n\n");
    
    printf("2. AddressSanitizer (Linux/macOS/Windows con Clang):\n");
    printf("   $ gcc -g -fsanitize=address -O0 06_debug_memoria.c -o debug_memoria\n");
    printf("   $ ./debug_memoria\n\n");
    
    printf("3. Dr. Memory (Windows):\n");
    printf("   > gcc -g -O0 06_debug_memoria.c -o debug_memoria.exe\n");
    printf("   > drmemory -light -- debug_memoria.exe\n\n");
    
    // Esecuzione degli esempi
    esempio_memory_leak();
    esempio_use_after_free();
    esempio_buffer_overflow();
    esempio_memoria_non_inizializzata();
    esempio_double_free();
    
    printf("\n=== FINE DEGLI ESEMPI ===\n");
    printf("Nota: alcuni errori sono stati commentati nel codice per evitare crash.\n");
    printf("Esamina il codice sorgente per vedere tutti gli errori e come rilevarli.\n");
    
    return 0;
}