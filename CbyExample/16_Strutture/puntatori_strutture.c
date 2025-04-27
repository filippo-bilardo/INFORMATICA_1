/**
 * puntatori_strutture.c
 * Esempi di utilizzo di puntatori con le strutture in C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definizione di una struttura per un nodo di una lista collegata
typedef struct Nodo {
    int valore;
    struct Nodo *successivo;  // Puntatore a un altro nodo
} Nodo;

// Definizione di una struttura per un rettangolo
typedef struct {
    float base;
    float altezza;
    float area;
    float perimetro;
} Rettangolo;

// Funzione che calcola area e perimetro di un rettangolo
void calcola_rettangolo(Rettangolo *r) {
    r->area = r->base * r->altezza;
    r->perimetro = 2 * (r->base + r->altezza);
}

// Funzione che crea un nuovo rettangolo allocato dinamicamente
Rettangolo* crea_rettangolo(float base, float altezza) {
    Rettangolo *r = (Rettangolo*)malloc(sizeof(Rettangolo));
    if (r != NULL) {
        r->base = base;
        r->altezza = altezza;
        calcola_rettangolo(r);
    }
    return r;
}

// Funzione che crea un nuovo nodo per la lista collegata
Nodo* crea_nodo(int valore) {
    Nodo *nuovo = (Nodo*)malloc(sizeof(Nodo));
    if (nuovo != NULL) {
        nuovo->valore = valore;
        nuovo->successivo = NULL;
    }
    return nuovo;
}

// Funzione che aggiunge un nodo in testa alla lista
void aggiungi_in_testa(Nodo **testa, int valore) {
    Nodo *nuovo = crea_nodo(valore);
    if (nuovo == NULL) return;
    
    nuovo->successivo = *testa;
    *testa = nuovo;
}

// Funzione che aggiunge un nodo in coda alla lista
void aggiungi_in_coda(Nodo **testa, int valore) {
    Nodo *nuovo = crea_nodo(valore);
    if (nuovo == NULL) return;
    
    if (*testa == NULL) {
        *testa = nuovo;
        return;
    }
    
    Nodo *corrente = *testa;
    while (corrente->successivo != NULL) {
        corrente = corrente->successivo;
    }
    
    corrente->successivo = nuovo;
}

// Funzione che stampa tutti i nodi della lista
void stampa_lista(Nodo *testa) {
    Nodo *corrente = testa;
    while (corrente != NULL) {
        printf("%d -> ", corrente->valore);
        corrente = corrente->successivo;
    }
    printf("NULL\n");
}

// Funzione che libera la memoria di tutti i nodi della lista
void libera_lista(Nodo *testa) {
    Nodo *corrente = testa;
    Nodo *successivo;
    
    while (corrente != NULL) {
        successivo = corrente->successivo;
        free(corrente);
        corrente = successivo;
    }
}

// Definizione di una struttura per una persona
typedef struct {
    char nome[50];
    char cognome[50];
    int eta;
} Persona;

// Funzione che modifica i dati di una persona
void modifica_persona(Persona *p, const char *nome, const char *cognome, int eta) {
    strcpy(p->nome, nome);
    strcpy(p->cognome, cognome);
    p->eta = eta;
}

// Funzione che stampa i dati di una persona
void stampa_persona(const Persona *p) {
    printf("%s %s, %d anni\n", p->nome, p->cognome, p->eta);
}

int main() {
    // Esempio 1: Utilizzo di puntatori a strutture semplici
    Persona p1 = {"Mario", "Rossi", 30};
    Persona *ptr_p1 = &p1;
    
    printf("=== ESEMPIO 1: PUNTATORI A STRUTTURE ===\n");
    printf("Accesso diretto: %s %s, %d anni\n", 
           p1.nome, p1.cognome, p1.eta);
    
    // Accesso tramite puntatore con operatore freccia
    printf("Accesso tramite puntatore: %s %s, %d anni\n", 
           ptr_p1->nome, ptr_p1->cognome, ptr_p1->eta);
    
    // Accesso tramite puntatore con dereferenziazione
    printf("Accesso tramite dereferenziazione: %s %s, %d anni\n", 
           (*ptr_p1).nome, (*ptr_p1).cognome, (*ptr_p1).eta);
    
    // Modifica tramite puntatore
    ptr_p1->eta = 31;
    printf("Dopo la modifica: %s %s, %d anni\n\n", 
           p1.nome, p1.cognome, p1.eta);
    
    // Esempio 2: Passaggio di strutture a funzioni tramite puntatori
    printf("=== ESEMPIO 2: PASSAGGIO A FUNZIONI ===\n");
    Persona p2;
    modifica_persona(&p2, "Laura", "Bianchi", 25);
    printf("Persona dopo la modifica: ");
    stampa_persona(&p2);
    
    // Esempio 3: Allocazione dinamica di strutture
    printf("\n=== ESEMPIO 3: ALLOCAZIONE DINAMICA ===\n");
    Rettangolo *r1 = crea_rettangolo(5.0, 3.0);
    if (r1 != NULL) {
        printf("Rettangolo: base=%.2f, altezza=%.2f, area=%.2f, perimetro=%.2f\n", 
               r1->base, r1->altezza, r1->area, r1->perimetro);
        
        // Modifica tramite puntatore
        r1->base = 6.0;
        r1->altezza = 4.0;
        calcola_rettangolo(r1);
        
        printf("Rettangolo modificato: base=%.2f, altezza=%.2f, area=%.2f, perimetro=%.2f\n", 
               r1->base, r1->altezza, r1->area, r1->perimetro);
        
        // Liberazione della memoria
        free(r1);
    }
    
    // Esempio 4: Array di puntatori a strutture
    printf("\n=== ESEMPIO 4: ARRAY DI PUNTATORI ===\n");
    Persona *persone[3];
    
    for (int i = 0; i < 3; i++) {
        persone[i] = (Persona*)malloc(sizeof(Persona));
        if (persone[i] == NULL) {
            printf("Errore di allocazione memoria\n");
            // Liberazione della memoria già allocata
            for (int j = 0; j < i; j++) {
                free(persone[j]);
            }
            return 1;
        }
    }
    
    // Inizializzazione delle persone
    modifica_persona(persone[0], "Mario", "Rossi", 30);
    modifica_persona(persone[1], "Laura", "Bianchi", 25);
    modifica_persona(persone[2], "Giovanni", "Verdi", 40);
    
    // Stampa delle persone
    for (int i = 0; i < 3; i++) {
        printf("Persona %d: ", i+1);
        stampa_persona(persone[i]);
    }
    
    // Liberazione della memoria
    for (int i = 0; i < 3; i++) {
        free(persone[i]);
    }
    
    // Esempio 5: Liste collegate (strutture autoreferenziali)
    printf("\n=== ESEMPIO 5: LISTE COLLEGATE ===\n");
    Nodo *lista = NULL;
    
    // Aggiunta di nodi in testa
    printf("Aggiunta di nodi in testa:\n");
    aggiungi_in_testa(&lista, 30);
    aggiungi_in_testa(&lista, 20);
    aggiungi_in_testa(&lista, 10);
    stampa_lista(lista);
    
    // Aggiunta di nodi in coda
    printf("Aggiunta di nodi in coda:\n");
    aggiungi_in_coda(&lista, 40);
    aggiungi_in_coda(&lista, 50);
    stampa_lista(lista);
    
    // Accesso diretto ai nodi
    printf("Accesso diretto ai nodi:\n");
    Nodo *secondo = lista->successivo;
    printf("Secondo nodo: %d\n", secondo->valore);
    
    Nodo *terzo = secondo->successivo;
    printf("Terzo nodo: %d\n", terzo->valore);
    
    // Liberazione della memoria della lista
    libera_lista(lista);
    
    return 0;
}