# Introduzione alle Strutture in C

Le strutture sono uno dei concetti più potenti in C, che permettono di raggruppare elementi di dati correlati ma di tipi diversi sotto un unico nome. Questo ci consente di organizzare i dati in modo più logico e gestibile.

## Definizione di una Struttura

In C, una struttura si definisce usando la parola chiave `struct`, seguita da un identificatore (nome della struttura) e un blocco di dichiarazioni di membri racchiuso tra parentesi graffe.

```c
struct [Nome_Struttura] {
    tipo_1 membro_1;
    tipo_2 membro_2;
    /* ... */
    tipo_n membro_n;
};
```

Esempio:

```c
struct Studente {
    char nome[50];
    char cognome[50];
    int matricola;
    float media_voti;
};
```

In questo esempio, abbiamo definito una struttura chiamata `Studente` che contiene informazioni come nome, cognome, matricola e media dei voti.

## Dichiarazione di Variabili Struttura

Dopo aver definito una struttura, possiamo dichiarare variabili di quel tipo in diversi modi:

### 1. Dichiarazione dopo la definizione

```c
struct Studente studente1, studente2;
```

### 2. Dichiarazione e definizione combinate

```c
struct Studente {
    char nome[50];
    char cognome[50];
    int matricola;
    float media_voti;
} studente1, studente2;
```

### 3. Dichiarazione con inizializzazione

```c
struct Studente studente1 = {"Mario", "Rossi", 12345, 27.5};
```

### 4. Dichiarazione con struttura anonima

```c
struct {
    char nome[50];
    char cognome[50];
    int matricola;
    float media_voti;
} studente1;
```

## Accesso ai Membri di una Struttura

Per accedere ai membri di una struttura, utilizziamo l'operatore punto (`.`):

```c
studente1.matricola = 54321;
studente1.media_voti = 28.0;
strcpy(studente1.nome, "Luigi");
strcpy(studente1.cognome, "Verdi");

printf("Studente: %s %s\n", studente1.nome, studente1.cognome);
printf("Matricola: %d\n", studente1.matricola);
printf("Media voti: %.1f\n", studente1.media_voti);
```

## Strutture e Puntatori

Spesso è utile lavorare con puntatori a strutture, specialmente quando si passano strutture alle funzioni. Per accedere ai membri di una struttura attraverso un puntatore, utilizziamo l'operatore freccia (`->`):

```c
struct Studente *ptr_studente;
ptr_studente = &studente1;

// Accesso ai membri tramite puntatore
ptr_studente->matricola = 98765;
printf("Matricola aggiornata: %d\n", ptr_studente->matricola);
```

L'espressione `ptr_studente->matricola` è equivalente a `(*ptr_studente).matricola`.

## Esempio Completo

Ecco un esempio completo che dimostra l'uso delle strutture:

```c
#include <stdio.h>
#include <string.h>

struct Studente {
    char nome[50];
    char cognome[50];
    int matricola;
    float media_voti;
};

void stampa_studente(struct Studente s) {
    printf("Studente: %s %s\n", s.nome, s.cognome);
    printf("Matricola: %d\n", s.matricola);
    printf("Media voti: %.1f\n", s.media_voti);
}

void modifica_studente(struct Studente *s, int nuova_matricola) {
    s->matricola = nuova_matricola;
}

int main() {
    struct Studente studente1 = {"Mario", "Rossi", 12345, 27.5};
    
    printf("Informazioni originali:\n");
    stampa_studente(studente1);
    
    modifica_studente(&studente1, 54321);
    
    printf("\nInformazioni dopo la modifica:\n");
    stampa_studente(studente1);
    
    return 0;
}
```

## Best Practices

1. **Nomi significativi**: Usa nomi descrittivi per le strutture e i loro membri.
2. **Organizzazione logica**: Raggruppa i dati correlati in una struttura.
3. **Allineamento**: Considera l'allineamento dei membri per ottimizzare l'uso della memoria.
4. **Incapsulamento**: Usa le strutture per incapsulare dati correlati e le funzioni che operano su di essi.
5. **Documentazione**: Commenta lo scopo di ogni membro della struttura.

## Domande di Autovalutazione

1. Qual è la differenza tra l'operatore `.` e l'operatore `->`?
2. Come si passa una struttura a una funzione per valore? E per riferimento?
3. Perché potrebbe essere più efficiente passare strutture grandi per riferimento anziché per valore?
4. Come si può inizializzare una struttura al momento della dichiarazione?
5. È possibile confrontare direttamente due strutture con l'operatore `==`? Perché?

## Esercizi Proposti

1. Crea una struttura `Punto` con coordinate x e y, e scrivi funzioni per calcolare la distanza tra due punti.
2. Definisci una struttura `Libro` con titolo, autore, anno di pubblicazione e prezzo. Scrivi un programma che gestisca un catalogo di libri.
3. Implementa una struttura `Data` con giorno, mese e anno, e scrivi funzioni per confrontare due date e calcolare il numero di giorni tra di esse.
4. Crea una struttura `Impiegato` con nome, ID, stipendio e dipartimento. Scrivi un programma che gestisca un database di impiegati e permetta di cercare, aggiungere e modificare record.

Nel prossimo capitolo, esploreremo operazioni più avanzate con le strutture, come l'assegnazione, l'uso come parametri di funzione, gli array di strutture e le strutture annidate.