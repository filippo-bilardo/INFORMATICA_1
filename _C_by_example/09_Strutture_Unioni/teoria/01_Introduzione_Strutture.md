# Introduzione alle Strutture in C

## Cos'è una Struttura?

Una **struttura** in C è un tipo di dato composto che permette di raggruppare variabili di tipi diversi sotto un unico nome. A differenza degli array, che possono contenere solo elementi dello stesso tipo, le strutture possono contenere elementi di tipi diversi (interi, float, caratteri, array, puntatori, e persino altre strutture).

Le strutture sono fondamentali nella programmazione in C perché permettono di organizzare dati correlati in un'unica entità, migliorando la leggibilità e la manutenibilità del codice.

## Definizione di una Struttura

Per definire una struttura in C, si utilizza la parola chiave `struct` seguita dal nome della struttura e da un blocco di dichiarazioni di variabili (chiamate membri o campi) racchiuse tra parentesi graffe.

### Sintassi

```c
struct NomeStruttura {
    tipo1 membro1;
    tipo2 membro2;
    // ...
    tipoN membroN;
};
```

### Esempio

```c
struct Persona {
    char nome[50];
    char cognome[50];
    int eta;
    float altezza;
    char sesso;
};
```

In questo esempio, abbiamo definito una struttura chiamata `Persona` che contiene cinque membri: due array di caratteri (`nome` e `cognome`), un intero (`eta`), un float (`altezza`) e un carattere (`sesso`).

## Dichiarazione di Variabili Struttura

Dopo aver definito una struttura, è possibile dichiarare variabili di quel tipo di struttura. Ci sono diversi modi per farlo:

### 1. Dichiarazione dopo la definizione

```c
struct Persona persona1, persona2;
```

### 2. Dichiarazione e definizione combinate

```c
struct Persona {
    char nome[50];
    char cognome[50];
    int eta;
    float altezza;
    char sesso;
} persona1, persona2;
```

### 3. Dichiarazione con inizializzazione

```c
struct Persona persona1 = {"Mario", "Rossi", 30, 1.75, 'M'};
```

### 4. Dichiarazione di struttura anonima

```c
struct {
    char nome[50];
    char cognome[50];
    int eta;
} persona1;
```

In questo caso, la struttura non ha un nome e può essere utilizzata solo per dichiarare le variabili specificate.

## Accesso ai Membri di una Struttura

Per accedere ai membri di una struttura, si utilizza l'operatore punto (`.`) seguito dal nome del membro.

```c
#include <stdio.h>
#include <string.h>

int main() {
    struct Persona {
        char nome[50];
        char cognome[50];
        int eta;
        float altezza;
        char sesso;
    };
    
    struct Persona persona1;
    
    // Assegnazione di valori ai membri
    strcpy(persona1.nome, "Mario");
    strcpy(persona1.cognome, "Rossi");
    persona1.eta = 30;
    persona1.altezza = 1.75;
    persona1.sesso = 'M';
    
    // Accesso ai membri per la stampa
    printf("Nome: %s\n", persona1.nome);
    printf("Cognome: %s\n", persona1.cognome);
    printf("Età: %d\n", persona1.eta);
    printf("Altezza: %.2f m\n", persona1.altezza);
    printf("Sesso: %c\n", persona1.sesso);
    
    return 0;
}
```

## Strutture e Typedef

È comune in C utilizzare `typedef` con le strutture per creare un nuovo nome di tipo, rendendo più semplice la dichiarazione delle variabili.

```c
typedef struct {
    char nome[50];
    char cognome[50];
    int eta;
    float altezza;
    char sesso;
} Persona;

// Ora possiamo dichiarare variabili senza usare la parola chiave 'struct'
Persona persona1, persona2;
```

Con `typedef`, possiamo dichiarare variabili di tipo `Persona` direttamente, senza dover usare la parola chiave `struct`.

## Dimensione di una Struttura

La dimensione di una struttura in memoria non è necessariamente uguale alla somma delle dimensioni dei suoi membri. Questo perché il compilatore può inserire del "padding" (riempimento) tra i membri per allineare i dati in memoria, migliorando l'efficienza di accesso.

Per conoscere la dimensione esatta di una struttura, si può utilizzare l'operatore `sizeof`:

```c
printf("Dimensione della struttura Persona: %zu byte\n", sizeof(struct Persona));
```

## Strutture Annidate

Una struttura può contenere membri che sono a loro volta strutture, creando così strutture annidate.

```c
struct Indirizzo {
    char via[100];
    char citta[50];
    char provincia[3];
    char cap[6];
};

struct Persona {
    char nome[50];
    char cognome[50];
    int eta;
    struct Indirizzo residenza;
};

struct Persona persona1;
strcpy(persona1.residenza.citta, "Roma");
```

## Conclusione

Le strutture in C sono uno strumento potente per organizzare dati correlati in un'unica entità. Permettono di creare tipi di dati personalizzati che riflettono meglio la natura dei dati che il programma deve gestire, migliorando la leggibilità e la manutenibilità del codice.

Nelle prossime sezioni, esploreremo operazioni più avanzate con le strutture, come il passaggio di strutture alle funzioni, l'utilizzo di array di strutture e l'uso di puntatori a strutture.

## Esercizi

1. Definisci una struttura `Studente` con campi per nome, cognome, matricola e media dei voti.

2. Scrivi un programma che dichiari un array di 3 strutture `Studente`, chieda all'utente di inserire i dati per ogni studente e poi stampi un report con tutti i dati inseriti.

3. Modifica il programma precedente per calcolare e stampare la media dei voti di tutti gli studenti.

4. Definisci una struttura `Data` con campi per giorno, mese e anno. Poi definisci una struttura `Persona` che includa, oltre a nome e cognome, anche una struttura `Data` per la data di nascita. Scrivi un programma che utilizzi queste strutture.

5. Scrivi una funzione che accetti come parametro una struttura `Studente` e ne stampi i dati. Utilizza questa funzione nel programma dell'esercizio 2 per stampare i dati degli studenti.