/**
 * strutture_annidate.c
 * Esempi di strutture annidate in C
 */

#include <stdio.h>
#include <string.h>

// Definizione di strutture per l'indirizzo
typedef struct {
    char via[50];
    int numero_civico;
    char citta[30];
    char provincia[3];
    int cap;
} Indirizzo;

// Definizione di struttura per la data
typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

// Struttura persona che contiene strutture annidate
typedef struct {
    char nome[50];
    char cognome[50];
    Data data_nascita;       // Struttura annidata
    Indirizzo residenza;     // Struttura annidata
    Indirizzo domicilio;     // Struttura annidata
} Persona;

// Struttura per un corso universitario
typedef struct {
    char nome[100];
    int crediti;
    char docente[50];
} Corso;

// Struttura per uno studente universitario
typedef struct {
    char nome[50];
    char cognome[50];
    int matricola;
    Data data_immatricolazione;  // Struttura annidata
    Indirizzo residenza;         // Struttura annidata
    Corso corsi[10];             // Array di strutture
    int num_corsi;
} Studente;

// Funzione per stampare un indirizzo
void stampa_indirizzo(const Indirizzo *ind) {
    printf("%s, %d - %d %s (%s)\n", 
           ind->via, ind->numero_civico, ind->cap, 
           ind->citta, ind->provincia);
}

// Funzione per stampare una data
void stampa_data(const Data *data) {
    printf("%02d/%02d/%04d", data->giorno, data->mese, data->anno);
}

int main() {
    // Inizializzazione di una persona con strutture annidate
    Persona p1;
    
    // Inizializzazione dei dati base
    strcpy(p1.nome, "Mario");
    strcpy(p1.cognome, "Rossi");
    
    // Inizializzazione della data di nascita (struttura annidata)
    p1.data_nascita.giorno = 15;
    p1.data_nascita.mese = 5;
    p1.data_nascita.anno = 1985;
    
    // Inizializzazione dell'indirizzo di residenza (struttura annidata)
    strcpy(p1.residenza.via, "Via Roma");
    p1.residenza.numero_civico = 123;
    strcpy(p1.residenza.citta, "Milano");
    strcpy(p1.residenza.provincia, "MI");
    p1.residenza.cap = 20100;
    
    // Inizializzazione dell'indirizzo di domicilio (struttura annidata)
    // In questo caso, il domicilio è diverso dalla residenza
    strcpy(p1.domicilio.via, "Via Verdi");
    p1.domicilio.numero_civico = 456;
    strcpy(p1.domicilio.citta, "Roma");
    strcpy(p1.domicilio.provincia, "RM");
    p1.domicilio.cap = 00100;
    
    // Stampa delle informazioni della persona
    printf("Persona: %s %s\n", p1.nome, p1.cognome);
    printf("Data di nascita: ");
    stampa_data(&p1.data_nascita);
    printf("\n");
    
    printf("Indirizzo di residenza: ");
    stampa_indirizzo(&p1.residenza);
    
    printf("Indirizzo di domicilio: ");
    stampa_indirizzo(&p1.domicilio);
    
    printf("\n");
    
    // Esempio di inizializzazione di una struttura annidata in un'unica istruzione
    Persona p2 = {
        "Laura", "Bianchi",
        {10, 8, 1990},                                // Data di nascita
        {"Corso Italia", 789, "Napoli", "NA", 80100},  // Residenza
        {"Corso Italia", 789, "Napoli", "NA", 80100}   // Domicilio (uguale alla residenza)
    };
    
    printf("Persona: %s %s\n", p2.nome, p2.cognome);
    printf("Data di nascita: ");
    stampa_data(&p2.data_nascita);
    printf("\n");
    
    printf("Indirizzo di residenza: ");
    stampa_indirizzo(&p2.residenza);
    
    printf("\n");
    
    // Esempio di studente con corsi (array di strutture)
    Studente s1;
    strcpy(s1.nome, "Giovanni");
    strcpy(s1.cognome, "Verdi");
    s1.matricola = 12345;
    
    // Data di immatricolazione
    s1.data_immatricolazione.giorno = 1;
    s1.data_immatricolazione.mese = 10;
    s1.data_immatricolazione.anno = 2020;
    
    // Residenza
    strcpy(s1.residenza.via, "Via Garibaldi");
    s1.residenza.numero_civico = 42;
    strcpy(s1.residenza.citta, "Torino");
    strcpy(s1.residenza.provincia, "TO");
    s1.residenza.cap = 10100;
    
    // Corsi (array di strutture)
    s1.num_corsi = 3;
    
    strcpy(s1.corsi[0].nome, "Programmazione");
    s1.corsi[0].crediti = 12;
    strcpy(s1.corsi[0].docente, "Prof. Bianchi");
    
    strcpy(s1.corsi[1].nome, "Matematica");
    s1.corsi[1].crediti = 9;
    strcpy(s1.corsi[1].docente, "Prof. Rossi");
    
    strcpy(s1.corsi[2].nome, "Fisica");
    s1.corsi[2].crediti = 6;
    strcpy(s1.corsi[2].docente, "Prof. Verdi");
    
    // Stampa delle informazioni dello studente
    printf("Studente: %s %s (Matricola: %d)\n", 
           s1.nome, s1.cognome, s1.matricola);
    
    printf("Data di immatricolazione: ");
    stampa_data(&s1.data_immatricolazione);
    printf("\n");
    
    printf("Residenza: ");
    stampa_indirizzo(&s1.residenza);
    
    printf("Corsi:\n");
    for (int i = 0; i < s1.num_corsi; i++) {
        printf("  %d. %s (%d CFU) - Docente: %s\n", 
               i+1, s1.corsi[i].nome, s1.corsi[i].crediti, s1.corsi[i].docente);
    }
    
    return 0;
}