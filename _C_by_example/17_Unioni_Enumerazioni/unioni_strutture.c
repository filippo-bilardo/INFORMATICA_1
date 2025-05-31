/**
 * File: unioni_strutture.c
 * Descrizione: Esempi di combinazione di unioni e strutture in C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definizione di un'enumerazione per identificare il tipo di dato
enum TipoDato {
    INTERO,
    FLOAT,
    STRINGA
};

// Struttura con un'unione per rappresentare diversi tipi di dati
struct Variante {
    enum TipoDato tipo;
    union {
        int i;
        float f;
        char* s;
    } valore;
};

// Struttura con un'unione anonima (C11)
struct VarianteAnonima {
    enum TipoDato tipo;
    union {
        int i;
        float f;
        char* s;
    }; // Unione anonima
};

// Funzione per creare una variante di tipo intero
struct Variante crea_intero(int val) {
    struct Variante v;
    v.tipo = INTERO;
    v.valore.i = val;
    return v;
}

// Funzione per creare una variante di tipo float
struct Variante crea_float(float val) {
    struct Variante v;
    v.tipo = FLOAT;
    v.valore.f = val;
    return v;
}

// Funzione per creare una variante di tipo stringa
struct Variante crea_stringa(const char* val) {
    struct Variante v;
    v.tipo = STRINGA;
    v.valore.s = strdup(val); // Alloca memoria per la stringa
    return v;
}

// Funzione per stampare una variante
void stampa_variante(struct Variante v) {
    switch (v.tipo) {
        case INTERO:
            printf("Intero: %d\n", v.valore.i);
            break;
        case FLOAT:
            printf("Float: %f\n", v.valore.f);
            break;
        case STRINGA:
            printf("Stringa: %s\n", v.valore.s);
            break;
        default:
            printf("Tipo sconosciuto\n");
    }
}

// Funzione per liberare la memoria allocata (se necessario)
void libera_variante(struct Variante* v) {
    if (v->tipo == STRINGA && v->valore.s != NULL) {
        free(v->valore.s);
        v->valore.s = NULL;
    }
}

// Esempio di unione per rappresentare un pacchetto di rete
struct Pacchetto {
    unsigned char tipo;      // Tipo di pacchetto
    unsigned short lunghezza; // Lunghezza del payload
    union {
        int comando;         // Per pacchetti di comando
        struct {
            float x, y, z;   // Per pacchetti di posizione
        } posizione;
        char messaggio[256]; // Per pacchetti di messaggio
    } dati;
};

int main() {
    // Esempio 1: Utilizzo di struct Variante
    printf("\n=== Esempio 1: Utilizzo di struct Variante ===\n");
    
    struct Variante v1 = crea_intero(42);
    struct Variante v2 = crea_float(3.14159f);
    struct Variante v3 = crea_stringa("Hello, Union!");
    
    stampa_variante(v1);
    stampa_variante(v2);
    stampa_variante(v3);
    
    // Liberare la memoria allocata per la stringa
    libera_variante(&v3);
    
    // Esempio 2: Utilizzo di unione anonima (C11)
    printf("\n=== Esempio 2: Utilizzo di unione anonima (C11) ===\n");
    
    struct VarianteAnonima va;
    va.tipo = INTERO;
    va.i = 100; // Accesso diretto senza il nome dell'unione
    
    printf("Valore intero: %d\n", va.i);
    
    va.tipo = FLOAT;
    va.f = 2.71828f;
    
    printf("Valore float: %f\n", va.f);
    
    // Esempio 3: Utilizzo di struct Pacchetto
    printf("\n=== Esempio 3: Utilizzo di struct Pacchetto ===\n");
    
    struct Pacchetto p1;
    p1.tipo = 1; // Comando
    p1.lunghezza = sizeof(int);
    p1.dati.comando = 0x1234;
    
    printf("Pacchetto di comando:\n");
    printf("Tipo: %d\n", p1.tipo);
    printf("Lunghezza: %d\n", p1.lunghezza);
    printf("Comando: 0x%X\n", p1.dati.comando);
    
    struct Pacchetto p2;
    p2.tipo = 2; // Posizione
    p2.lunghezza = sizeof(float) * 3;
    p2.dati.posizione.x = 10.5f;
    p2.dati.posizione.y = 20.7f;
    p2.dati.posizione.z = 30.9f;
    
    printf("\nPacchetto di posizione:\n");
    printf("Tipo: %d\n", p2.tipo);
    printf("Lunghezza: %d\n", p2.lunghezza);
    printf("Posizione: (%.1f, %.1f, %.1f)\n", 
           p2.dati.posizione.x, 
           p2.dati.posizione.y, 
           p2.dati.posizione.z);
    
    struct Pacchetto p3;
    p3.tipo = 3; // Messaggio
    strcpy(p3.dati.messaggio, "Questo è un messaggio di test");
    p3.lunghezza = strlen(p3.dati.messaggio) + 1;
    
    printf("\nPacchetto di messaggio:\n");
    printf("Tipo: %d\n", p3.tipo);
    printf("Lunghezza: %d\n", p3.lunghezza);
    printf("Messaggio: %s\n", p3.dati.messaggio);
    
    return 0;
}