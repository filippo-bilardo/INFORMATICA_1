/**
 * File: tipi_personalizzati.c
 * Descrizione: Esempi di creazione e utilizzo di tipi personalizzati complessi in C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// ===== Esempio 1: Sistema di tipi per gestire date e orari =====

// Definizione di tipi per data e ora
typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    int ore;
    int minuti;
    int secondi;
} Ora;

typedef struct {
    Data data;
    Ora ora;
} DataOra;

// Funzioni per la gestione di date e orari
Data creaData(int giorno, int mese, int anno) {
    Data d = {giorno, mese, anno};
    return d;
}

Ora creaOra(int ore, int minuti, int secondi) {
    Ora o = {ore, minuti, secondi};
    return o;
}

DataOra creaDataOra(Data data, Ora ora) {
    DataOra dt = {data, ora};
    return dt;
}

void stampaData(Data d) {
    printf("%02d/%02d/%04d", d.giorno, d.mese, d.anno);
}

void stampaOra(Ora o) {
    printf("%02d:%02d:%02d", o.ore, o.minuti, o.secondi);
}

void stampaDataOra(DataOra dt) {
    stampaData(dt.data);
    printf(" ");
    stampaOra(dt.ora);
}

// ===== Esempio 2: Sistema di tipi per numeri complessi =====

typedef struct {
    double reale;
    double immaginario;
} NumeroComplesso;

// Funzioni per operazioni con numeri complessi
NumeroComplesso creaComplesso(double reale, double immaginario) {
    NumeroComplesso c = {reale, immaginario};
    return c;
}

NumeroComplesso sommaComplessi(NumeroComplesso a, NumeroComplesso b) {
    NumeroComplesso risultato;
    risultato.reale = a.reale + b.reale;
    risultato.immaginario = a.immaginario + b.immaginario;
    return risultato;
}

NumeroComplesso sottrazioneComplessi(NumeroComplesso a, NumeroComplesso b) {
    NumeroComplesso risultato;
    risultato.reale = a.reale - b.reale;
    risultato.immaginario = a.immaginario - b.immaginario;
    return risultato;
}

NumeroComplesso moltiplicazioneComplessi(NumeroComplesso a, NumeroComplesso b) {
    NumeroComplesso risultato;
    risultato.reale = a.reale * b.reale - a.immaginario * b.immaginario;
    risultato.immaginario = a.reale * b.immaginario + a.immaginario * b.reale;
    return risultato;
}

double moduloComplesso(NumeroComplesso c) {
    return sqrt(c.reale * c.reale + c.immaginario * c.immaginario);
}

void stampaComplesso(NumeroComplesso c) {
    if (c.immaginario >= 0) {
        printf("%.2f + %.2fi", c.reale, c.immaginario);
    } else {
        printf("%.2f - %.2fi", c.reale, -c.immaginario);
    }
}

// ===== Esempio 3: Sistema di tipi per geometria =====

typedef struct {
    double x;
    double y;
} Punto2D;

typedef struct {
    Punto2D centro;
    double raggio;
} Cerchio;

typedef struct {
    Punto2D vertici[3];
} Triangolo;

typedef struct {
    Punto2D angolo_sup_sx;
    double larghezza;
    double altezza;
} Rettangolo;

// Funzioni per la geometria
double distanzaPunti(Punto2D p1, Punto2D p2) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return sqrt(dx*dx + dy*dy);
}

double areaCerchio(Cerchio c) {
    return M_PI * c.raggio * c.raggio;
}

double perimetroCerchio(Cerchio c) {
    return 2 * M_PI * c.raggio;
}

double areaTriangolo(Triangolo t) {
    // Formula di Erone
    double a = distanzaPunti(t.vertici[0], t.vertici[1]);
    double b = distanzaPunti(t.vertici[1], t.vertici[2]);
    double c = distanzaPunti(t.vertici[2], t.vertici[0]);
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

double areaRettangolo(Rettangolo r) {
    return r.larghezza * r.altezza;
}

// ===== Esempio 4: Sistema di tipi per una libreria =====

typedef enum {
    ROMANZO,
    SAGGIO,
    BIOGRAFIA,
    TECNICO
} GenereLibro;

typedef struct {
    char nome[50];
    char cognome[50];
} Autore;

typedef struct {
    char titolo[100];
    Autore autore;
    int anno_pubblicazione;
    GenereLibro genere;
    int num_pagine;
    char isbn[14]; // ISBN-13 + terminatore
} Libro;

typedef struct NodoLibro {
    Libro libro;
    struct NodoLibro* prossimo;
} NodoLibro;

typedef struct {
    NodoLibro* testa;
    int num_libri;
} Biblioteca;

// Funzioni per la gestione della biblioteca
Biblioteca* creaBiblioteca() {
    Biblioteca* b = (Biblioteca*)malloc(sizeof(Biblioteca));
    if (b) {
        b->testa = NULL;
        b->num_libri = 0;
    }
    return b;
}

void aggiungiLibro(Biblioteca* b, Libro libro) {
    if (!b) return;
    
    NodoLibro* nuovo = (NodoLibro*)malloc(sizeof(NodoLibro));
    if (!nuovo) return;
    
    nuovo->libro = libro;
    nuovo->prossimo = b->testa;
    b->testa = nuovo;
    b->num_libri++;
}

void stampaLibro(Libro libro) {
    printf("Titolo: %s\n", libro.titolo);
    printf("Autore: %s %s\n", libro.autore.nome, libro.autore.cognome);
    printf("Anno: %d\n", libro.anno_pubblicazione);
    printf("Genere: ");
    
    switch(libro.genere) {
        case ROMANZO: printf("Romanzo"); break;
        case SAGGIO: printf("Saggio"); break;
        case BIOGRAFIA: printf("Biografia"); break;
        case TECNICO: printf("Tecnico"); break;
    }
    
    printf("\nPagine: %d\n", libro.num_pagine);
    printf("ISBN: %s\n", libro.isbn);
}

void stampaBiblioteca(Biblioteca* b) {
    if (!b) return;
    
    printf("=== Biblioteca (%d libri) ===\n", b->num_libri);
    
    NodoLibro* corrente = b->testa;
    while (corrente) {
        stampaLibro(corrente->libro);
        printf("-------------------\n");
        corrente = corrente->prossimo;
    }
}

void liberaBiblioteca(Biblioteca* b) {
    if (!b) return;
    
    NodoLibro* corrente = b->testa;
    NodoLibro* temp;
    
    while (corrente) {
        temp = corrente;
        corrente = corrente->prossimo;
        free(temp);
    }
    
    free(b);
}

int main() {
    // Test del sistema di date e orari
    printf("\n=== Test Sistema Date e Orari ===\n");
    Data oggi = creaData(15, 5, 2023);
    Ora adesso = creaOra(14, 30, 0);
    DataOra dataOraAttuale = creaDataOra(oggi, adesso);
    
    printf("Data: ");
    stampaData(oggi);
    printf("\nOra: ");
    stampaOra(adesso);
    printf("\nData e ora: ");
    stampaDataOra(dataOraAttuale);
    printf("\n");
    
    // Test del sistema di numeri complessi
    printf("\n=== Test Sistema Numeri Complessi ===\n");
    NumeroComplesso c1 = creaComplesso(3.0, 4.0);
    NumeroComplesso c2 = creaComplesso(1.0, -2.0);
    
    printf("c1 = ");
    stampaComplesso(c1);
    printf("\nc2 = ");
    stampaComplesso(c2);
    
    NumeroComplesso somma = sommaComplessi(c1, c2);
    printf("\nc1 + c2 = ");
    stampaComplesso(somma);
    
    NumeroComplesso prodotto = moltiplicazioneComplessi(c1, c2);
    printf("\nc1 * c2 = ");
    stampaComplesso(prodotto);
    
    printf("\n|c1| = %.2f\n", moduloComplesso(c1));
    
    // Test del sistema di geometria
    printf("\n=== Test Sistema Geometria ===\n");
    Punto2D p1 = {0.0, 0.0};
    Punto2D p2 = {3.0, 0.0};
    Punto2D p3 = {0.0, 4.0};
    
    printf("Distanza tra p1 e p3: %.2f\n", distanzaPunti(p1, p3));
    
    Cerchio cerchio = {{1.0, 1.0}, 2.0};
    printf("Area del cerchio: %.2f\n", areaCerchio(cerchio));
    printf("Perimetro del cerchio: %.2f\n", perimetroCerchio(cerchio));
    
    Triangolo triangolo = {{p1, p2, p3}};
    printf("Area del triangolo: %.2f\n", areaTriangolo(triangolo));
    
    Rettangolo rettangolo = {{0.0, 0.0}, 5.0, 3.0};
    printf("Area del rettangolo: %.2f\n", areaRettangolo(rettangolo));
    
    // Test del sistema di biblioteca
    printf("\n=== Test Sistema Biblioteca ===\n");
    Biblioteca* biblioteca = creaBiblioteca();
    
    Libro libro1 = {
        "Il nome della rosa",
        {"Umberto", "Eco"},
        1980,
        ROMANZO,
        512,
        "9788845246340"
    };
    
    Libro libro2 = {
        "Breve storia del tempo",
        {"Stephen", "Hawking"},
        1988,
        SAGGIO,
        256,
        "9788817079327"
    };
    
    aggiungiLibro(biblioteca, libro1);
    aggiungiLibro(biblioteca, libro2);
    
    stampaBiblioteca(biblioteca);
    
    // Pulizia memoria
    liberaBiblioteca(biblioteca);
    
    return 0;
}

/**
 * Esercizi proposti:
 * 
 * 1. Estendere il sistema di date e orari aggiungendo funzioni per calcolare la differenza
 *    tra due date e per aggiungere/sottrarre giorni a una data.
 * 
 * 2. Implementare un sistema di tipi per rappresentare e manipolare polinomi, con funzioni
 *    per somma, sottrazione, moltiplicazione e valutazione in un punto.
 * 
 * 3. Creare un sistema di tipi per gestire un'agenda di appuntamenti, con funzioni per
 *    aggiungere, rimuovere e cercare appuntamenti per data o descrizione.
 * 
 * 4. Implementare un sistema di tipi per gestire un grafo, con funzioni per aggiungere
 *    nodi e archi, e per eseguire algoritmi come la ricerca in ampiezza e in profondità.
 */