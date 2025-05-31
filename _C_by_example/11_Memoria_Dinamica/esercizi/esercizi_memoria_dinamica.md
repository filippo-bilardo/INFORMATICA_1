# Esercizi sulla Memoria Dinamica in C

Questi esercizi ti aiuteranno a mettere in pratica i concetti di gestione della memoria dinamica che hai appreso in questa sezione. Ogni esercizio è accompagnato da una breve descrizione e da suggerimenti per la soluzione.

## Esercizio 1: Allocazione e Manipolazione di Array Dinamici

**Obiettivo**: Scrivere un programma che alloca dinamicamente un array di interi, lo riempie con valori inseriti dall'utente, calcola la somma e la media degli elementi, e infine libera la memoria.

**Requisiti**:
1. Chiedere all'utente quanti numeri vuole inserire
2. Allocare dinamicamente un array di dimensione appropriata
3. Leggere i numeri inseriti dall'utente
4. Calcolare e visualizzare la somma e la media dei numeri
5. Liberare la memoria allocata

**Suggerimenti**:
- Usa `malloc()` per allocare l'array
- Controlla sempre se l'allocazione è riuscita
- Ricordati di liberare la memoria con `free()` alla fine

## Esercizio 2: Gestione di una Matrice Dinamica

**Obiettivo**: Implementare un programma che alloca dinamicamente una matrice di dimensioni specificate dall'utente, la riempie con valori casuali, calcola la somma di ogni riga e colonna, e infine libera la memoria.

**Requisiti**:
1. Chiedere all'utente le dimensioni della matrice (righe e colonne)
2. Allocare dinamicamente la matrice
3. Riempire la matrice con numeri casuali tra 1 e 100
4. Calcolare e visualizzare la somma di ogni riga e colonna
5. Liberare correttamente tutta la memoria allocata

**Suggerimenti**:
- Usa un approccio a due fasi per allocare la matrice:
  - Prima alloca un array di puntatori (uno per ogni riga)
  - Poi alloca ogni riga separatamente
- Usa la funzione `rand()` per generare numeri casuali
- Ricordati di liberare la memoria nell'ordine inverso rispetto all'allocazione

## Esercizio 3: Implementazione di una Lista Concatenata

**Obiettivo**: Implementare una lista concatenata semplice con funzioni per inserire, cercare, eliminare elementi e liberare la memoria.

**Requisiti**:
1. Definire una struttura `Nodo` con un valore intero e un puntatore al nodo successivo
2. Implementare le seguenti funzioni:
   - `inserisci_in_testa`: inserisce un nuovo nodo all'inizio della lista
   - `inserisci_in_coda`: inserisce un nuovo nodo alla fine della lista
   - `cerca`: cerca un valore nella lista e restituisce 1 se trovato, 0 altrimenti
   - `elimina`: elimina la prima occorrenza di un valore dalla lista
   - `stampa_lista`: visualizza tutti gli elementi della lista
   - `libera_lista`: libera tutta la memoria allocata per la lista
3. Scrivere un programma main che testa tutte queste funzioni

**Suggerimenti**:
- Usa `malloc()` per allocare ogni nuovo nodo
- Gestisci correttamente i casi speciali (lista vuota, eliminazione del primo elemento, ecc.)
- Fai attenzione ai dangling pointers quando elimini elementi

## Esercizio 4: Gestione di una Rubrica Telefonica

**Obiettivo**: Implementare una rubrica telefonica che memorizza nomi e numeri di telefono utilizzando allocazione dinamica della memoria.

**Requisiti**:
1. Definire una struttura `Contatto` con campi per nome e numero di telefono
2. Implementare funzioni per:
   - Aggiungere un nuovo contatto
   - Cercare un contatto per nome
   - Modificare un contatto esistente
   - Eliminare un contatto
   - Visualizzare tutti i contatti
   - Liberare tutta la memoria allocata
3. I nomi e i numeri di telefono devono essere allocati dinamicamente con la dimensione esatta necessaria

**Suggerimenti**:
- Usa `malloc()` e `strlen()` per allocare la memoria esatta per le stringhe
- Considera di utilizzare `realloc()` per ridimensionare l'array di contatti quando necessario
- Gestisci correttamente i casi di errore nell'allocazione della memoria

## Esercizio 5: Rilevamento di Memory Leak

**Obiettivo**: Identificare e correggere i memory leak in un programma dato.

**Codice con memory leak**:
```c
#include <stdio.h>
#include <stdlib.h>

void funzione1() {
    int *p = (int *)malloc(sizeof(int) * 10);
    // Uso di p...
    // Manca free(p)
}

void funzione2() {
    char *str = (char *)malloc(100);
    // Uso di str...
    str = NULL; // Perso il riferimento alla memoria allocata
}

int* funzione3() {
    int *array = (int *)malloc(sizeof(int) * 5);
    return array;
    // La responsabilità di liberare la memoria passa al chiamante
}

int main() {
    funzione1();
    funzione2();
    
    int *risultato = funzione3();
    // Uso di risultato...
    // Manca free(risultato)
    
    return 0;
}
```

**Requisiti**:
1. Identificare tutti i memory leak nel codice
2. Correggere il codice per eliminare tutti i memory leak
3. Aggiungere commenti che spiegano dove erano i memory leak e come li hai corretti

**Suggerimenti**:
- Cerca allocazioni di memoria (`malloc`, `calloc`, `realloc`) senza corrispondenti `free`
- Fai attenzione ai puntatori che vengono sovrascritti prima di liberare la memoria
- Considera chi ha la responsabilità di liberare la memoria quando viene restituito un puntatore

## Domande di Autovalutazione

1. Qual è la differenza principale tra memoria statica e memoria dinamica?
2. Quali sono le differenze tra `malloc()`, `calloc()` e `realloc()`?
3. Cosa succede se si tenta di accedere a memoria già liberata con `free()`?
4. Cosa sono i memory leak e come possono essere evitati?
5. Cosa sono i dangling pointers e come possono essere evitati?
6. Perché è importante controllare il valore di ritorno di `malloc()` e funzioni simili?
7. Quali sono i vantaggi e gli svantaggi dell'allocazione dinamica della memoria?
8. Come si può implementare un array dinamico che si ridimensiona automaticamente quando necessario?
9. Quali strumenti possono essere utilizzati per rilevare memory leak in un programma C?
10. Quali sono le best practices per la gestione della memoria dinamica in C?

## Soluzioni

Le soluzioni a questi esercizi sono disponibili nella cartella `soluzioni`. Ti consigliamo di provare a risolvere gli esercizi da solo prima di consultare le soluzioni.