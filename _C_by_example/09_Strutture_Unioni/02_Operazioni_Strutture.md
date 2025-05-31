# Operazioni con le Strutture in C

Dopo aver imparato a definire e utilizzare le strutture di base, esploriamo ora operazioni più avanzate che possiamo eseguire con esse.

## Assegnazione di Strutture

In C, è possibile assegnare direttamente una struttura a un'altra dello stesso tipo. Questo crea una copia completa di tutti i membri della struttura.

```c
#include <stdio.h>
#include <string.h>

struct Persona {
    char nome[50];
    int età;
    float altezza;
};

int main() {
    struct Persona persona1 = {"Marco", 30, 1.75};
    struct Persona persona2;
    
    // Assegnazione di una struttura
    persona2 = persona1;
    
    // Modifica di persona2 non influisce su persona1
    strcpy(persona2.nome, "Paolo");
    persona2.età = 25;
    
    printf("Persona 1: %s, %d anni, %.2f m\n", persona1.nome, persona1.età, persona1.altezza);
    printf("Persona 2: %s, %d anni, %.2f m\n", persona2.nome, persona2.età, persona2.altezza);
    
    return 0;
}
```

È importante notare che l'assegnazione crea una copia indipendente. Modificare i membri di una struttura non influisce sull'altra.

## Strutture come Parametri di Funzione

Le strutture possono essere passate alle funzioni in due modi principali:

### 1. Passaggio per Valore

Quando una struttura viene passata per valore, viene creata una copia completa della struttura:

```c
void modifica_persona_valore(struct Persona p) {
    strcpy(p.nome, "Nome Modificato");  // Modifica solo la copia locale
    p.età = 99;                        // Non influisce sulla struttura originale
}

int main() {
    struct Persona persona = {"Marco", 30, 1.75};
    
    modifica_persona_valore(persona);
    printf("%s, %d anni\n", persona.nome, persona.età);  // Stampa "Marco, 30 anni"
    
    return 0;
}
```

### 2. Passaggio per Riferimento (tramite puntatore)

Per modificare la struttura originale, è necessario passarla per riferimento usando un puntatore:

```c
void modifica_persona_riferimento(struct Persona *p) {
    strcpy(p->nome, "Nome Modificato");  // Modifica la struttura originale
    p->età = 99;                        // Influisce sulla struttura originale
}

int main() {
    struct Persona persona = {"Marco", 30, 1.75};
    
    modifica_persona_riferimento(&persona);
    printf("%s, %d anni\n", persona.nome, persona.età);  // Stampa "Nome Modificato, 99 anni"
    
    return 0;
}
```

### Considerazioni sulle Prestazioni

Per strutture di grandi dimensioni, il passaggio per valore può essere inefficiente poiché richiede la copia di tutti i membri. In questi casi, è preferibile il passaggio per riferimento.

## Array di Strutture

È possibile creare array di strutture per gestire collezioni di dati strutturati:

```c
#include <stdio.h>
#include <string.h>

struct Studente {
    char nome[50];
    int matricola;
    float media_voti;
};

int main() {
    struct Studente classe[3];
    int i;
    
    // Inizializzazione degli studenti
    strcpy(classe[0].nome, "Mario Rossi");
    classe[0].matricola = 12345;
    classe[0].media_voti = 27.5;
    
    strcpy(classe[1].nome, "Luigi Verdi");
    classe[1].matricola = 23456;
    classe[1].media_voti = 29.0;
    
    strcpy(classe[2].nome, "Anna Bianchi");
    classe[2].matricola = 34567;
    classe[2].media_voti = 28.5;
    
    // Alternativa: inizializzazione diretta
    struct Studente altra_classe[2] = {
        {"Carlo Neri", 45678, 26.0},
        {"Elena Gialli", 56789, 30.0}
    };
    
    // Stampa degli studenti
    printf("Elenco studenti della classe:\n");
    for(i = 0; i < 3; i++) {
        printf("%s, Matricola: %d, Media: %.1f\n", 
               classe[i].nome, classe[i].matricola, classe[i].media_voti);
    }
    
    return 0;
}
```

## Strutture Annidate

Le strutture possono contenere altre strutture come membri, creando strutture annidate:

```c
#include <stdio.h>

struct Data {
    int giorno;
    int mese;
    int anno;
};

struct Studente {
    char nome[50];
    int matricola;
    struct Data data_nascita;  // Struttura annidata
    struct Data data_iscrizione;
};

int main() {
    struct Studente studente;
    
    // Inizializzazione
    strcpy(studente.nome, "Mario Rossi");
    studente.matricola = 12345;
    
    studente.data_nascita.giorno = 15;
    studente.data_nascita.mese = 5;
    studente.data_nascita.anno = 1995;
    
    studente.data_iscrizione.giorno = 1;
    studente.data_iscrizione.mese = 9;
    studente.data_iscrizione.anno = 2020;
    
    // Alternativa: inizializzazione diretta
    struct Studente altro_studente = {
        "Luigi Verdi",
        23456,
        {10, 8, 1998},     // data_nascita
        {1, 9, 2020}        // data_iscrizione
    };
    
    // Stampa delle informazioni
    printf("Studente: %s, Matricola: %d\n", studente.nome, studente.matricola);
    printf("Data di nascita: %d/%d/%d\n", 
           studente.data_nascita.giorno, 
           studente.data_nascita.mese, 
           studente.data_nascita.anno);
    printf("Data di iscrizione: %d/%d/%d\n", 
           studente.data_iscrizione.giorno, 
           studente.data_iscrizione.mese, 
           studente.data_iscrizione.anno);
    
    return 0;
}
```

## Strutture Autoreferenziali

Una struttura può contenere un puntatore a una struttura dello stesso tipo, creando strutture autoreferenziali. Questo è utile per implementare strutture dati come liste collegate, alberi, ecc.

```c
#include <stdio.h>
#include <stdlib.h>

struct Nodo {
    int dato;
    struct Nodo *successivo;  // Puntatore a un altro Nodo
};

int main() {
    // Creazione di una lista collegata semplice
    struct Nodo *testa = NULL;
    struct Nodo *secondo = NULL;
    struct Nodo *terzo = NULL;
    
    // Allocazione dei nodi nella heap
    testa = (struct Nodo*)malloc(sizeof(struct Nodo));
    secondo = (struct Nodo*)malloc(sizeof(struct Nodo));
    terzo = (struct Nodo*)malloc(sizeof(struct Nodo));
    
    // Assegnazione dei dati e collegamento dei nodi
    testa->dato = 1;
    testa->successivo = secondo;
    
    secondo->dato = 2;
    secondo->successivo = terzo;
    
    terzo->dato = 3;
    terzo->successivo = NULL;  // Fine della lista
    
    // Attraversamento della lista
    struct Nodo *corrente = testa;
    printf("Lista collegata: ");
    while(corrente != NULL) {
        printf("%d ", corrente->dato);
        corrente = corrente->successivo;
    }
    printf("\n");
    
    // Liberazione della memoria
    free(testa);
    free(secondo);
    free(terzo);
    
    return 0;
}
```

## Allineamento e Padding delle Strutture

Il compilatore C può inserire spazi vuoti (padding) tra i membri di una struttura per garantire un allineamento corretto in memoria. Questo può influire sulla dimensione totale della struttura:

```c
#include <stdio.h>

struct Esempio1 {
    char a;     // 1 byte
    int b;      // 4 byte
    char c;     // 1 byte
};

struct Esempio2 {
    char a;     // 1 byte
    char c;     // 1 byte
    int b;      // 4 byte
};

int main() {
    printf("Dimensione di Esempio1: %zu byte\n", sizeof(struct Esempio1));
    printf("Dimensione di Esempio2: %zu byte\n", sizeof(struct Esempio2));
    
    return 0;
}
```

L'output potrebbe mostrare dimensioni diverse per le due strutture, nonostante contengano gli stessi membri, a causa del diverso allineamento.

## Best Practices

1. **Efficienza della memoria**: Organizza i membri della struttura in modo da minimizzare il padding.
2. **Passaggio per riferimento**: Passa strutture grandi per riferimento per evitare copie inutili.
3. **Inizializzazione**: Inizializza sempre tutti i membri di una struttura.
4. **Liberazione della memoria**: Libera sempre la memoria allocata dinamicamente per le strutture.
5. **Incapsulamento**: Crea funzioni specifiche per operare sulle strutture, simulando un approccio orientato agli oggetti.

## Domande di Autovalutazione

1. Cosa succede quando si assegna una struttura a un'altra in C?
2. Qual è la differenza tra passare una struttura per valore e per riferimento?
3. Come si può ottimizzare l'allineamento dei membri di una struttura?
4. Come si implementa una lista collegata usando strutture autoreferenziali?
5. Perché potrebbe essere utile annidare strutture?

## Esercizi Proposti

1. Crea una struttura `Rettangolo` con larghezza e altezza, e scrivi funzioni per calcolare area e perimetro.
2. Implementa una rubrica telefonica usando un array di strutture `Contatto`.
3. Crea una struttura `Frazione` con numeratore e denominatore, e implementa funzioni per addizione, sottrazione, moltiplicazione e divisione di frazioni.
4. Implementa una lista collegata di strutture `Studente` con funzioni per aggiungere, rimuovere e cercare studenti.

Nel prossimo capitolo, esploreremo le unioni, un altro tipo di dato composto in C che condivide lo spazio di memoria tra i suoi membri.