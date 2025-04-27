/**
 * strutture_base.c
 * Esempi base di definizione e utilizzo delle strutture in C
 */

#include <stdio.h>
#include <string.h>

// Definizione di una struttura senza typedef
struct Punto {
    int x;
    int y;
};

// Definizione di una struttura con typedef
typedef struct {
    char titolo[100];
    char autore[50];
    int anno;
    float prezzo;
} Libro;

// Struttura con inizializzazione designata (C99)
typedef struct {
    char nome[50];
    char cognome[50];
    int eta;
} Persona;

int main() {
    // Dichiarazione e inizializzazione di una struttura Punto
    struct Punto p1 = {10, 20};
    struct Punto p2;
    
    // Accesso e modifica dei membri
    p2.x = 30;
    p2.y = 40;
    
    printf("Punto p1: (%d, %d)\n", p1.x, p1.y);
    printf("Punto p2: (%d, %d)\n", p2.x, p2.y);
    
    // Calcolo della distanza Manhattan tra due punti
    int distanza = abs(p2.x - p1.x) + abs(p2.y - p1.y);
    printf("Distanza Manhattan tra p1 e p2: %d\n\n", distanza);
    
    // Utilizzo della struttura Libro con typedef
    Libro libro1;
    strcpy(libro1.titolo, "Il nome della rosa");
    strcpy(libro1.autore, "Umberto Eco");
    libro1.anno = 1980;
    libro1.prezzo = 12.50;
    
    printf("Libro: %s\n", libro1.titolo);
    printf("Autore: %s\n", libro1.autore);
    printf("Anno: %d\n", libro1.anno);
    printf("Prezzo: %.2f euro\n\n", libro1.prezzo);
    
    // Inizializzazione in ordine di dichiarazione
    Libro libro2 = {"1984", "George Orwell", 1949, 10.00};
    
    printf("Libro: %s\n", libro2.titolo);
    printf("Autore: %s\n", libro2.autore);
    printf("Anno: %d\n", libro2.anno);
    printf("Prezzo: %.2f euro\n\n", libro2.prezzo);
    
    // Utilizzo dell'inizializzazione designata (C99)
    Persona persona1 = {
        .nome = "Mario",
        .cognome = "Rossi",
        .eta = 35
    };
    
    printf("Persona: %s %s, %d anni\n", 
           persona1.nome, persona1.cognome, persona1.eta);
    
    // Copia di strutture
    Persona persona2 = persona1;
    persona2.eta = 40;  // Modifica solo la copia
    
    printf("Persona originale: %s %s, %d anni\n", 
           persona1.nome, persona1.cognome, persona1.eta);
    printf("Persona copiata: %s %s, %d anni\n", 
           persona2.nome, persona2.cognome, persona2.eta);
    
    // Dimensione delle strutture
    printf("\nDimensione di struct Punto: %zu byte\n", sizeof(struct Punto));
    printf("Dimensione di Libro: %zu byte\n", sizeof(Libro));
    printf("Dimensione di Persona: %zu byte\n", sizeof(Persona));
    
    return 0;
}