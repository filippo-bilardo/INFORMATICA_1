# Operazioni Avanzate con le Strutture in C

## Passaggio di Strutture alle Funzioni

In C, le strutture possono essere passate alle funzioni in diversi modi:

### 1. Passaggio per Valore

Quando una struttura viene passata per valore, viene creata una copia della struttura originale. Qualsiasi modifica apportata alla struttura all'interno della funzione non influisce sulla struttura originale.

```c
#include <stdio.h>

struct Punto {
    int x;
    int y;
};

void modificaPunto(struct Punto p) {
    p.x = 100;  // Questa modifica non influisce sulla struttura originale
    p.y = 200;
    printf("All'interno della funzione: (%d, %d)\n", p.x, p.y);
}

int main() {
    struct Punto punto = {10, 20};
    
    printf("Prima della chiamata: (%d, %d)\n", punto.x, punto.y);
    modificaPunto(punto);
    printf("Dopo la chiamata: (%d, %d)\n", punto.x, punto.y);  // I valori non cambiano
    
    return 0;
}
```

### 2. Passaggio per Riferimento (usando puntatori)

Per modificare una struttura all'interno di una funzione, è necessario passarla per riferimento utilizzando un puntatore.

```c
#include <stdio.h>

struct Punto {
    int x;
    int y;
};

void modificaPunto(struct Punto *p) {
    p->x = 100;  // Questa modifica influisce sulla struttura originale
    p->y = 200;
    printf("All'interno della funzione: (%d, %d)\n", p->x, p->y);
}

int main() {
    struct Punto punto = {10, 20};
    
    printf("Prima della chiamata: (%d, %d)\n", punto.x, punto.y);
    modificaPunto(&punto);  // Passaggio dell'indirizzo della struttura
    printf("Dopo la chiamata: (%d, %d)\n", punto.x, punto.y);  // I valori cambiano
    
    return 0;
}
```

## Array di Strutture

Gli array di strutture sono utili quando si devono gestire collezioni di dati strutturati, come elenchi di persone, prodotti, ecc.

```c
#include <stdio.h>
#include <string.h>

struct Studente {
    char nome[50];
    int matricola;
    float media;
};

int main() {
    struct Studente classe[3];  // Array di 3 strutture Studente
    
    // Inizializzazione degli studenti
    strcpy(classe[0].nome, "Mario Rossi");
    classe[0].matricola = 12345;
    classe[0].media = 27.5;
    
    strcpy(classe[1].nome, "Laura Bianchi");
    classe[1].matricola = 12346;
    classe[1].media = 29.0;
    
    strcpy(classe[2].nome, "Giovanni Verdi");
    classe[2].matricola = 12347;
    classe[2].media = 26.0;
    
    // Stampa dei dati degli studenti
    printf("Elenco degli studenti:\n");
    for (int i = 0; i < 3; i++) {
        printf("Nome: %s, Matricola: %d, Media: %.1f\n", 
               classe[i].nome, classe[i].matricola, classe[i].media);
    }
    
    return 0;
}
```

## Puntatori a Strutture

I puntatori a strutture sono fondamentali in C, specialmente quando si lavora con strutture dati dinamiche come liste collegate, alberi, ecc.

### Dichiarazione e Inizializzazione

```c
#include <stdio.h>

struct Persona {
    char nome[50];
    int eta;
};

int main() {
    struct Persona persona = {"Mario", 30};
    struct Persona *ptrPersona = &persona;  // Puntatore a struttura
    
    // Accesso ai membri tramite puntatore
    printf("Nome: %s\n", ptrPersona->nome);  // Usando l'operatore freccia
    printf("Età: %d\n", (*ptrPersona).eta);  // Usando la dereferenziazione e il punto
    
    return 0;
}
```

### Operatore Freccia (->)

L'operatore freccia (`->`) è una scorciatoia per accedere ai membri di una struttura tramite un puntatore. È equivalente a `(*ptr).membro`.

## Allocazione Dinamica di Strutture

Le strutture possono essere allocate dinamicamente usando `malloc()`, `calloc()` e liberate con `free()`.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Persona {
    char *nome;
    int eta;
};

int main() {
    // Allocazione dinamica di una struttura
    struct Persona *persona = (struct Persona *)malloc(sizeof(struct Persona));
    if (persona == NULL) {
        printf("Errore di allocazione memoria\n");
        return 1;
    }
    
    // Allocazione dinamica per il campo nome
    persona->nome = (char *)malloc(50 * sizeof(char));
    if (persona->nome == NULL) {
        printf("Errore di allocazione memoria\n");
        free(persona);
        return 1;
    }
    
    // Inizializzazione dei campi
    strcpy(persona->nome, "Mario Rossi");
    persona->eta = 30;
    
    // Utilizzo della struttura
    printf("Nome: %s, Età: %d\n", persona->nome, persona->eta);
    
    // Liberazione della memoria
    free(persona->nome);
    free(persona);
    
    return 0;
}
```

## Strutture Autoreferenziali

Le strutture possono contenere puntatori a strutture dello stesso tipo, permettendo di creare strutture dati complesse come liste collegate, alberi, ecc.

```c
#include <stdio.h>
#include <stdlib.h>

// Definizione di un nodo per una lista collegata
struct Nodo {
    int dato;
    struct Nodo *successivo;  // Puntatore al nodo successivo
};

int main() {
    // Creazione di una lista con tre nodi
    struct Nodo *testa = (struct Nodo *)malloc(sizeof(struct Nodo));
    testa->dato = 10;
    
    testa->successivo = (struct Nodo *)malloc(sizeof(struct Nodo));
    testa->successivo->dato = 20;
    
    testa->successivo->successivo = (struct Nodo *)malloc(sizeof(struct Nodo));
    testa->successivo->successivo->dato = 30;
    testa->successivo->successivo->successivo = NULL;  // Fine della lista
    
    // Attraversamento della lista
    struct Nodo *corrente = testa;
    printf("Elementi della lista: ");
    while (corrente != NULL) {
        printf("%d ", corrente->dato);
        corrente = corrente->successivo;
    }
    printf("\n");
    
    // Liberazione della memoria
    corrente = testa;
    while (corrente != NULL) {
        struct Nodo *temp = corrente;
        corrente = corrente->successivo;
        free(temp);
    }
    
    return 0;
}
```

## Strutture e File

Le strutture sono particolarmente utili quando si lavora con i file, permettendo di leggere e scrivere record di dati strutturati.

```c
#include <stdio.h>
#include <string.h>

struct Studente {
    char nome[50];
    int matricola;
    float media;
};

int main() {
    struct Studente studenti[3] = {
        {"Mario Rossi", 12345, 27.5},
        {"Laura Bianchi", 12346, 29.0},
        {"Giovanni Verdi", 12347, 26.0}
    };
    
    // Scrittura su file
    FILE *file = fopen("studenti.dat", "wb");
    if (file == NULL) {
        printf("Errore nell'apertura del file\n");
        return 1;
    }
    
    fwrite(studenti, sizeof(struct Studente), 3, file);
    fclose(file);
    
    // Lettura da file
    struct Studente studentiLetti[3];
    file = fopen("studenti.dat", "rb");
    if (file == NULL) {
        printf("Errore nell'apertura del file\n");
        return 1;
    }
    
    fread(studentiLetti, sizeof(struct Studente), 3, file);
    fclose(file);
    
    // Stampa dei dati letti
    printf("Dati letti dal file:\n");
    for (int i = 0; i < 3; i++) {
        printf("Nome: %s, Matricola: %d, Media: %.1f\n", 
               studentiLetti[i].nome, studentiLetti[i].matricola, studentiLetti[i].media);
    }
    
    return 0;
}
```

## Esercizi

1. Scrivi un programma che utilizzi una struttura `Libro` con campi per titolo, autore, anno di pubblicazione e prezzo. Crea un array di 5 libri, inizializzalo con dati a tua scelta e poi implementa una funzione che trovi il libro più costoso.

2. Implementa una lista collegata di strutture `Persona` con campi per nome, cognome ed età. Scrivi funzioni per inserire una nuova persona all'inizio della lista, alla fine della lista e per stampare tutti gli elementi della lista.

3. Crea una struttura `Punto3D` per rappresentare un punto nello spazio tridimensionale. Scrivi una funzione che calcoli la distanza tra due punti e una funzione che determini se tre punti sono allineati.

4. Implementa un sistema di gestione di un'agenda utilizzando un array di strutture. Ogni struttura deve contenere informazioni su un appuntamento (data, ora, descrizione). Scrivi funzioni per aggiungere un appuntamento, eliminare un appuntamento e visualizzare tutti gli appuntamenti di una certa data.

5. Crea un programma che gestisca un database di dipendenti utilizzando strutture allocate dinamicamente. Implementa funzioni per aggiungere un dipendente, rimuovere un dipendente, modificare i dati di un dipendente e salvare/caricare il database su/da file.