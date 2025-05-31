/**
 * File: typedef_base.c
 * Descrizione: Esempi base di utilizzo di typedef in C
 */

#include <stdio.h>

// Definizione di nuovi tipi con typedef
typedef int Intero;
typedef float Reale;
typedef char Carattere;
typedef char Stringa[50];
typedef int Vettore[10];

// Esempio di typedef con enum
typedef enum {
    LUNEDI,
    MARTEDI,
    MERCOLEDI,
    GIOVEDI,
    VENERDI,
    SABATO,
    DOMENICA
} GiornoSettimana;

// Funzione che utilizza i tipi definiti
void stampaValori(Intero i, Reale r, Carattere c) {
    printf("Intero: %d\n", i);
    printf("Reale: %f\n", r);
    printf("Carattere: %c\n", c);
}

// Funzione che utilizza il tipo Vettore
void stampaVettore(Vettore v) {
    printf("Contenuto del vettore: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

// Funzione che converte il giorno in stringa
const char* giornoToString(GiornoSettimana giorno) {
    switch(giorno) {
        case LUNEDI: return "Lunedì";
        case MARTEDI: return "Martedì";
        case MERCOLEDI: return "Mercoledì";
        case GIOVEDI: return "Giovedì";
        case VENERDI: return "Venerdì";
        case SABATO: return "Sabato";
        case DOMENICA: return "Domenica";
        default: return "Giorno non valido";
    }
}

int main() {
    // Utilizzo dei tipi definiti
    Intero numero = 42;
    Reale pi = 3.14159;
    Carattere lettera = 'A';
    Stringa nome = "Mario Rossi";
    
    // Chiamata alla funzione con i tipi definiti
    stampaValori(numero, pi, lettera);
    
    // Utilizzo del tipo Stringa
    printf("Nome: %s\n", nome);
    
    // Utilizzo del tipo Vettore
    Vettore numeri = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    stampaVettore(numeri);
    
    // Utilizzo del tipo GiornoSettimana
    GiornoSettimana oggi = MERCOLEDI;
    printf("Oggi è %s\n", giornoToString(oggi));
    
    // Dimostrazione che i tipi definiti sono equivalenti ai tipi originali
    Intero a = 10;
    int b = 20;
    Intero somma = a + b;  // Possiamo sommare un Intero e un int
    printf("Somma: %d\n", somma);
    
    return 0;
}

/**
 * Esercizi proposti:
 * 
 * 1. Aggiungere un typedef per un array bidimensionale (matrice) e scrivere una funzione
 *    che stampi il contenuto della matrice.
 * 
 * 2. Creare un typedef per un tipo booleano (prima dell'introduzione di stdbool.h in C99)
 *    e utilizzarlo in una funzione che verifichi se un numero è primo.
 * 
 * 3. Definire un typedef per un array di stringhe e scrivere una funzione che ordini
 *    alfabeticamente le stringhe.
 */