/**
 * array_strutture.c
 * Esempi di creazione e gestione di array di strutture in C
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definizione di una struttura per un prodotto
typedef struct {
    int codice;
    char nome[50];
    float prezzo;
    int quantita;
} Prodotto;

// Definizione di una struttura per uno studente
typedef struct {
    int matricola;
    char nome[30];
    char cognome[30];
    int voti[5];  // Array all'interno della struttura
    float media;
} Studente;

// Funzione per stampare un prodotto
void stampa_prodotto(const Prodotto *p) {
    printf("Codice: %d, Nome: %s, Prezzo: %.2f€, Quantità: %d\n",
           p->codice, p->nome, p->prezzo, p->quantita);
}

// Funzione per stampare uno studente
void stampa_studente(const Studente *s) {
    printf("Matricola: %d, Nome: %s %s, Media: %.2f, Voti: ",
           s->matricola, s->nome, s->cognome, s->media);
    
    for (int i = 0; i < 5; i++) {
        printf("%d ", s->voti[i]);
    }
    printf("\n");
}

// Funzione per calcolare la media dei voti di uno studente
void calcola_media(Studente *s) {
    int somma = 0;
    for (int i = 0; i < 5; i++) {
        somma += s->voti[i];
    }
    s->media = (float)somma / 5;
}

// Funzione per cercare un prodotto per codice
Prodotto* cerca_prodotto(Prodotto inventario[], int n, int codice) {
    for (int i = 0; i < n; i++) {
        if (inventario[i].codice == codice) {
            return &inventario[i];
        }
    }
    return NULL; // Prodotto non trovato
}

// Funzione per ordinare l'inventario per prezzo (bubble sort)
void ordina_per_prezzo(Prodotto inventario[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (inventario[j].prezzo > inventario[j+1].prezzo) {
                // Scambio delle strutture
                Prodotto temp = inventario[j];
                inventario[j] = inventario[j+1];
                inventario[j+1] = temp;
            }
        }
    }
}

int main() {
    // Array di strutture con inizializzazione
    Prodotto inventario[5] = {
        {101, "Tastiera", 25.99, 10},
        {102, "Mouse", 15.50, 15},
        {103, "Monitor", 199.99, 5},
        {104, "Cuffie", 49.90, 8},
        {105, "Webcam", 39.99, 12}
    };
    
    // Stampa dell'inventario
    printf("=== INVENTARIO PRODOTTI ===\n");
    for (int i = 0; i < 5; i++) {
        stampa_prodotto(&inventario[i]);
    }
    
    // Ricerca di un prodotto
    int codice_da_cercare = 103;
    Prodotto *trovato = cerca_prodotto(inventario, 5, codice_da_cercare);
    
    printf("\nRicerca prodotto con codice %d: ", codice_da_cercare);
    if (trovato != NULL) {
        printf("Trovato!\n");
        stampa_prodotto(trovato);
        
        // Modifica del prodotto trovato
        trovato->prezzo = 189.99;
        trovato->quantita += 3;
        
        printf("Prodotto aggiornato:\n");
        stampa_prodotto(trovato);
    } else {
        printf("Non trovato!\n");
    }
    
    // Ordinamento dell'inventario per prezzo
    ordina_per_prezzo(inventario, 5);
    
    printf("\n=== INVENTARIO ORDINATO PER PREZZO ===\n");
    for (int i = 0; i < 5; i++) {
        stampa_prodotto(&inventario[i]);
    }
    
    // Array di strutture allocato dinamicamente
    int num_studenti = 3;
    Studente *classe = (Studente *)malloc(num_studenti * sizeof(Studente));
    
    if (classe != NULL) {
        // Inizializzazione degli studenti
        classe[0].matricola = 1001;
        strcpy(classe[0].nome, "Mario");
        strcpy(classe[0].cognome, "Rossi");
        classe[0].voti[0] = 27; classe[0].voti[1] = 30;
        classe[0].voti[2] = 28; classe[0].voti[3] = 25;
        classe[0].voti[4] = 29;
        calcola_media(&classe[0]);
        
        classe[1].matricola = 1002;
        strcpy(classe[1].nome, "Laura");
        strcpy(classe[1].cognome, "Bianchi");
        classe[1].voti[0] = 30; classe[1].voti[1] = 30;
        classe[1].voti[2] = 29; classe[1].voti[3] = 28;
        classe[1].voti[4] = 30;
        calcola_media(&classe[1]);
        
        classe[2].matricola = 1003;
        strcpy(classe[2].nome, "Giovanni");
        strcpy(classe[2].cognome, "Verdi");
        classe[2].voti[0] = 25; classe[2].voti[1] = 24;
        classe[2].voti[2] = 26; classe[2].voti[3] = 27;
        classe[2].voti[4] = 23;
        calcola_media(&classe[2]);
        
        // Stampa degli studenti
        printf("\n=== ELENCO STUDENTI ===\n");
        for (int i = 0; i < num_studenti; i++) {
            stampa_studente(&classe[i]);
        }
        
        // Liberazione della memoria
        free(classe);
    } else {
        printf("Errore nell'allocazione della memoria\n");
    }
    
    return 0;
}