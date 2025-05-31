# Strutture Avanzate in C

## Strutture Annidate

Una delle caratteristiche più potenti delle strutture in C è la possibilità di annidarle, cioè di includere una struttura all'interno di un'altra. Questo permette di creare strutture dati complesse e gerarchiche.

### Definizione di Strutture Annidate

```c
struct Indirizzo {
    char via[50];
    char citta[30];
    char provincia[3];
    int cap;
};

struct Persona {
    char nome[50];
    char cognome[50];
    int eta;
    struct Indirizzo residenza;  // Struttura annidata
};
```

### Accesso ai Membri di Strutture Annidate

Per accedere ai membri di una struttura annidata, si utilizzano più operatori punto in sequenza:

```c
struct Persona p1;

strcpy(p1.nome, "Mario");
strcpy(p1.cognome, "Rossi");
p1.eta = 30;

// Accesso ai membri della struttura annidata
strcpy(p1.residenza.via, "Via Roma 123");
strcpy(p1.residenza.citta, "Milano");
strcpy(p1.residenza.provincia, "MI");
p1.residenza.cap = 20100;
```

### Inizializzazione di Strutture Annidate

```c
struct Persona p2 = {
    "Laura", "Bianchi", 25,
    {"Via Verdi 456", "Roma", "RM", 00100}  // Inizializzazione della struttura annidata
};

// Oppure con inizializzazione designata (C99)
struct Persona p3 = {
    .nome = "Giovanni",
    .cognome = "Verdi",
    .eta = 40,
    .residenza = {
        .via = "Corso Italia 789",
        .citta = "Napoli",
        .provincia = "NA",
        .cap = 80100
    }
};
```

## Array di Strutture

Gli array di strutture sono particolarmente utili quando si devono gestire collezioni di dati omogenei, come elenchi di persone, prodotti, studenti, ecc.

### Dichiarazione e Inizializzazione

```c
#define MAX_STUDENTI 100

typedef struct {
    char nome[50];
    char cognome[50];
    int matricola;
    float media_voti;
} Studente;

// Dichiarazione di un array di strutture
Studente classe[MAX_STUDENTI];

// Inizializzazione di alcuni elementi
classe[0] = (Studente){"Mario", "Rossi", 12345, 27.5};
classe[1] = (Studente){"Laura", "Bianchi", 67890, 29.0};
```

### Accesso e Manipolazione

```c
// Accesso ai membri di un elemento dell'array
printf("Primo studente: %s %s\n", classe[0].nome, classe[0].cognome);

// Modifica di un membro
classe[0].media_voti = 28.0;

// Iterazione attraverso l'array
for (int i = 0; i < 2; i++) {
    printf("Studente %d: %s %s, Matricola: %d, Media: %.2f\n", 
           i+1, classe[i].nome, classe[i].cognome, 
           classe[i].matricola, classe[i].media_voti);
}
```

## Puntatori a Strutture

I puntatori a strutture sono fondamentali per la gestione efficiente della memoria e per implementare strutture dati dinamiche come liste collegate, alberi, ecc.

### Dichiarazione e Inizializzazione

```c
Studente studente1 = {"Mario", "Rossi", 12345, 27.5};

// Dichiarazione di un puntatore a struttura
Studente *ptr_studente;

// Inizializzazione del puntatore
ptr_studente = &studente1;
```

### Accesso ai Membri tramite Puntatore

Per accedere ai membri di una struttura tramite un puntatore, si può utilizzare l'operatore freccia (`->`):

```c
// Equivalenti:
printf("Nome: %s\n", (*ptr_studente).nome);  // Notare le parentesi
printf("Nome: %s\n", ptr_studente->nome);    // Più comune e leggibile

// Modifica di un membro tramite puntatore
ptr_studente->media_voti = 28.5;
```

### Allocazione Dinamica di Strutture

È possibile allocare dinamicamente strutture utilizzando `malloc()`, `calloc()` o `realloc()`:

```c
#include <stdlib.h>

// Allocazione di una singola struttura
Studente *nuovo_studente = (Studente *)malloc(sizeof(Studente));
if (nuovo_studente != NULL) {
    strcpy(nuovo_studente->nome, "Paolo");
    strcpy(nuovo_studente->cognome, "Neri");
    nuovo_studente->matricola = 54321;
    nuovo_studente->media_voti = 26.0;
    
    // Uso della struttura allocata dinamicamente
    printf("Nuovo studente: %s %s\n", nuovo_studente->nome, nuovo_studente->cognome);
    
    // Liberazione della memoria
    free(nuovo_studente);
}
```

### Allocazione Dinamica di Array di Strutture

```c
// Allocazione di un array di strutture
int num_studenti = 10;
Studente *classe_dinamica = (Studente *)malloc(num_studenti * sizeof(Studente));

if (classe_dinamica != NULL) {
    // Inizializzazione e uso dell'array
    for (int i = 0; i < num_studenti; i++) {
        sprintf(classe_dinamica[i].nome, "Studente%d", i+1);
        sprintf(classe_dinamica[i].cognome, "Cognome%d", i+1);
        classe_dinamica[i].matricola = 10000 + i;
        classe_dinamica[i].media_voti = 25.0 + (float)(i) / 2.0;
    }
    
    // Accesso agli elementi (notare la sintassi)
    printf("Studente 3: %s %s\n", 
           classe_dinamica[2].nome, classe_dinamica[2].cognome);
    // oppure
    printf("Studente 5: %s %s\n", 
           (classe_dinamica+4)->nome, (classe_dinamica+4)->cognome);
    
    // Liberazione della memoria
    free(classe_dinamica);
}
```

## Strutture Autoreferenziali

Le strutture possono contenere puntatori a strutture dello stesso tipo, creando così strutture autoreferenziali. Queste sono alla base di molte strutture dati dinamiche come liste collegate, alberi, grafi, ecc.

```c
typedef struct Nodo {
    int valore;
    struct Nodo *successivo;  // Puntatore a una struttura dello stesso tipo
} Nodo;
```

Esempio di implementazione di una lista collegata semplice:

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int valore;
    struct Nodo *successivo;
} Nodo;

// Funzione per creare un nuovo nodo
Nodo *creaNodo(int valore) {
    Nodo *nuovoNodo = (Nodo *)malloc(sizeof(Nodo));
    if (nuovoNodo != NULL) {
        nuovoNodo->valore = valore;
        nuovoNodo->successivo = NULL;
    }
    return nuovoNodo;
}

// Funzione per aggiungere un nodo alla fine della lista
void aggiungiNodo(Nodo **testa, int valore) {
    Nodo *nuovoNodo = creaNodo(valore);
    if (nuovoNodo == NULL) return;
    
    if (*testa == NULL) {
        *testa = nuovoNodo;
        return;
    }
    
    Nodo *corrente = *testa;
    while (corrente->successivo != NULL) {
        corrente = corrente->successivo;
    }
    
    corrente->successivo = nuovoNodo;
}

// Funzione per stampare la lista
void stampaLista(Nodo *testa) {
    Nodo *corrente = testa;
    while (corrente != NULL) {
        printf("%d -> ", corrente->valore);
        corrente = corrente->successivo;
    }
    printf("NULL\n");
}

// Funzione per liberare la memoria della lista
void liberaLista(Nodo *testa) {
    Nodo *corrente = testa;
    Nodo *successivo;
    
    while (corrente != NULL) {
        successivo = corrente->successivo;
        free(corrente);
        corrente = successivo;
    }
}

int main() {
    Nodo *lista = NULL;
    
    // Aggiunta di nodi alla lista
    aggiungiNodo(&lista, 10);
    aggiungiNodo(&lista, 20);
    aggiungiNodo(&lista, 30);
    
    // Stampa della lista
    printf("Lista: ");
    stampaLista(lista);
    
    // Liberazione della memoria
    liberaLista(lista);
    
    return 0;
}
```

## Conclusione

Le strutture avanzate in C offrono potenti strumenti per la creazione di tipi di dati complessi e la gestione efficiente della memoria. Strutture annidate, array di strutture, puntatori a strutture e strutture autoreferenziali sono alla base di molte tecniche di programmazione avanzate e strutture dati fondamentali.

Nel prossimo capitolo, esploreremo come utilizzare le strutture con le funzioni, incluso il passaggio di strutture come parametri e il ritorno di strutture dalle funzioni.