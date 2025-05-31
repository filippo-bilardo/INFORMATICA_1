/**
 * File: enumerazioni_base.c
 * Descrizione: Esempi base di definizione e utilizzo delle enumerazioni in C
 */

#include <stdio.h>

// Definizione di un'enumerazione semplice
enum Giorno {
    LUNEDI,     // 0
    MARTEDI,    // 1
    MERCOLEDI,  // 2
    GIOVEDI,    // 3
    VENERDI,    // 4
    SABATO,     // 5
    DOMENICA    // 6
};

// Enumerazione con valori espliciti
enum Mese {
    GENNAIO = 1,  // Inizia da 1 invece che da 0
    FEBBRAIO,      // 2
    MARZO,         // 3
    APRILE,        // 4
    MAGGIO,        // 5
    GIUGNO,        // 6
    LUGLIO,        // 7
    AGOSTO,        // 8
    SETTEMBRE,     // 9
    OTTOBRE,       // 10
    NOVEMBRE,      // 11
    DICEMBRE       // 12
};

// Enumerazione con valori non sequenziali
enum Codice {
    OK = 0,
    ERRORE_GENERICO = -1,
    ERRORE_FILE = 100,
    ERRORE_RETE = 200,
    ERRORE_MEMORIA = 300
};

// Funzione che prende un giorno come parametro
const char* nome_giorno(enum Giorno g) {
    switch (g) {
        case LUNEDI:    return "Lunedì";
        case MARTEDI:   return "Martedì";
        case MERCOLEDI: return "Mercoledì";
        case GIOVEDI:   return "Giovedì";
        case VENERDI:   return "Venerdì";
        case SABATO:    return "Sabato";
        case DOMENICA:  return "Domenica";
        default:        return "Giorno non valido";
    }
}

int main() {
    // Esempio 1: Utilizzo base di un'enumerazione
    printf("\n=== Esempio 1: Utilizzo base di un'enumerazione ===\n");
    
    enum Giorno oggi = MERCOLEDI;
    enum Giorno domani = GIOVEDI;
    
    printf("Oggi è %s\n", nome_giorno(oggi));
    printf("Domani è %s\n", nome_giorno(domani));
    
    // Esempio 2: Enumerazioni e operazioni aritmetiche
    printf("\n=== Esempio 2: Enumerazioni e operazioni aritmetiche ===\n");
    
    enum Giorno dopodomani = domani + 1;
    printf("Dopodomani è %s\n", nome_giorno(dopodomani));
    
    // Ciclo attraverso tutti i giorni della settimana
    printf("\nGiorni della settimana:\n");
    for (enum Giorno g = LUNEDI; g <= DOMENICA; g++) {
        printf("%d: %s\n", g, nome_giorno(g));
    }
    
    // Esempio 3: Enumerazioni con valori espliciti
    printf("\n=== Esempio 3: Enumerazioni con valori espliciti ===\n");
    
    enum Mese mese_corrente = OTTOBRE;
    printf("Mese corrente: %d\n", mese_corrente);
    
    // Esempio 4: Enumerazioni in istruzioni switch
    printf("\n=== Esempio 4: Enumerazioni in istruzioni switch ===\n");
    
    enum Codice risultato = ERRORE_FILE;
    
    switch (risultato) {
        case OK:
            printf("Operazione completata con successo.\n");
            break;
        case ERRORE_GENERICO:
            printf("Si è verificato un errore generico.\n");
            break;
        case ERRORE_FILE:
            printf("Si è verificato un errore durante l'accesso al file.\n");
            break;
        case ERRORE_RETE:
            printf("Si è verificato un errore di rete.\n");
            break;
        case ERRORE_MEMORIA:
            printf("Si è verificato un errore di allocazione memoria.\n");
            break;
        default:
            printf("Errore sconosciuto.\n");
    }
    
    // Esempio 5: Dimensione di un'enumerazione
    printf("\n=== Esempio 5: Dimensione di un'enumerazione ===\n");
    
    printf("Dimensione di enum Giorno: %zu byte\n", sizeof(enum Giorno));
    printf("Dimensione di enum Mese: %zu byte\n", sizeof(enum Mese));
    printf("Dimensione di enum Codice: %zu byte\n", sizeof(enum Codice));
    // Tipicamente, le enumerazioni hanno la stessa dimensione di un int
    
    return 0;
}