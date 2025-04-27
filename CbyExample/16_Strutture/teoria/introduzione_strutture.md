# Introduzione alle Strutture in C

## Cos'è una Struttura?

Una struttura in C è un tipo di dato composto che permette di raggruppare variabili di tipi diversi sotto un unico nome. A differenza degli array, che possono contenere solo elementi dello stesso tipo, le strutture possono contenere elementi di tipi diversi (interi, float, caratteri, array, puntatori e persino altre strutture).

Le strutture sono fondamentali nella programmazione C perché permettono di:

- Organizzare dati correlati in un'unica entità logica
- Creare tipi di dati personalizzati adatti alle specifiche esigenze del programma
- Rappresentare entità del mondo reale in modo più naturale nel codice

## Definizione di una Struttura

La sintassi per definire una struttura in C è la seguente:

```c
struct nome_struttura {
    tipo_1 membro_1;
    tipo_2 membro_2;
    // ...
    tipo_n membro_n;
};
```

Esempio di definizione di una struttura per rappresentare uno studente:

```c
struct Studente {
    char nome[50];
    char cognome[50];
    int matricola;
    float media_voti;
};
```

## Dichiarazione di Variabili Struttura

Dopo aver definito una struttura, è possibile dichiarare variabili di quel tipo in diversi modi:

### 1. Dichiarazione separata dalla definizione

```c
struct Studente studente1, studente2;
```

### 2. Dichiarazione contestuale alla definizione

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

## Accesso ai Membri di una Struttura

Per accedere ai membri di una struttura si utilizza l'operatore punto (`.`):

```c
studente1.matricola = 12345;
studente1.media_voti = 27.5;
strcpy(studente1.nome, "Mario");
strcpy(studente1.cognome, "Rossi");

printf("Studente: %s %s, Matricola: %d, Media: %.2f\n", 
       studente1.nome, studente1.cognome, 
       studente1.matricola, studente1.media_voti);
```

## Strutture e Typedef

È comune in C utilizzare `typedef` per creare un alias più semplice per i tipi di struttura:

```c
typedef struct {
    char nome[50];
    char cognome[50];
    int matricola;
    float media_voti;
} Studente;
```

Con questa definizione, è possibile dichiarare variabili di tipo `Studente` direttamente, senza usare la parola chiave `struct`:

```c
Studente studente1, studente2;
```

## Inizializzazione di Strutture

Le strutture possono essere inizializzate in diversi modi:

### 1. Inizializzazione in ordine di dichiarazione

```c
Studente studente1 = {"Mario", "Rossi", 12345, 27.5};
```

### 2. Inizializzazione designata (C99 e successivi)

```c
Studente studente2 = {
    .nome = "Laura",
    .cognome = "Bianchi",
    .matricola = 67890,
    .media_voti = 29.0
};
```

### 3. Inizializzazione membro per membro

```c
Studente studente3;
strcpy(studente3.nome, "Giovanni");
strcpy(studente3.cognome, "Verdi");
studente3.matricola = 54321;
studente3.media_voti = 26.0;
```

## Dimensione di una Struttura

La dimensione di una struttura non è necessariamente uguale alla somma delle dimensioni dei suoi membri. Il compilatore può inserire del padding (riempimento) tra i membri per garantire un allineamento corretto in memoria:

```c
struct Esempio {
    char c;     // 1 byte
    int i;      // 4 byte
    char d;     // 1 byte
};

// sizeof(struct Esempio) potrebbe essere 12 invece di 6
```

Per ottimizzare l'uso della memoria, è consigliabile ordinare i membri della struttura dal più grande al più piccolo.

## Esempio Completo

Ecco un esempio completo che dimostra l'uso delle strutture:

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[50];
    char cognome[50];
    int matricola;
    float media_voti;
} Studente;

int main() {
    // Dichiarazione e inizializzazione
    Studente studente1 = {"Mario", "Rossi", 12345, 27.5};
    
    // Accesso e modifica dei membri
    studente1.media_voti = 28.0;
    
    // Dichiarazione e inizializzazione membro per membro
    Studente studente2;
    strcpy(studente2.nome, "Laura");
    strcpy(studente2.cognome, "Bianchi");
    studente2.matricola = 67890;
    studente2.media_voti = 29.0;
    
    // Stampa delle informazioni
    printf("Studente 1: %s %s, Matricola: %d, Media: %.2f\n", 
           studente1.nome, studente1.cognome, 
           studente1.matricola, studente1.media_voti);
    
    printf("Studente 2: %s %s, Matricola: %d, Media: %.2f\n", 
           studente2.nome, studente2.cognome, 
           studente2.matricola, studente2.media_voti);
    
    // Dimensione della struttura
    printf("Dimensione della struttura Studente: %zu byte\n", sizeof(Studente));
    
    return 0;
}
```

## Conclusione

Le strutture sono uno strumento potente in C che permette di creare tipi di dati personalizzati e organizzare informazioni correlate in modo logico. Sono alla base di molte tecniche di programmazione avanzate e sono essenziali per la creazione di programmi ben strutturati e manutenibili.

Nel prossimo capitolo, esploreremo concetti più avanzati come le strutture annidate, gli array di strutture e i puntatori a strutture.