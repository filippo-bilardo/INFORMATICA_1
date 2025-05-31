# Typedef con Strutture e Unioni

## Typedef con Strutture

Uno degli usi più comuni e potenti di `typedef` in C è la sua applicazione con le strutture. Questo approccio semplifica notevolmente la dichiarazione di variabili di tipo struttura e rende il codice più leggibile.

### Sintassi Standard vs Typedef

**Senza typedef:**

```c
struct Persona {
    char nome[50];
    char cognome[50];
    int eta;
};

int main() {
    struct Persona p1; // Necessario specificare 'struct'
    return 0;
}
```

**Con typedef:**

```c
typedef struct {
    char nome[50];
    char cognome[50];
    int eta;
} Persona;

int main() {
    Persona p1; // Non è necessario specificare 'struct'
    return 0;
}
```

### Esempio Completo

```c
#include <stdio.h>
#include <string.h>

// Definizione di una struttura con typedef
typedef struct {
    char nome[50];
    char cognome[50];
    int eta;
} Persona;

// Funzione che utilizza il tipo Persona
void stampaPersona(Persona p) {
    printf("Nome: %s\n", p.nome);
    printf("Cognome: %s\n", p.cognome);
    printf("Età: %d\n", p.eta);
}

int main() {
    // Creazione e inizializzazione di una variabile di tipo Persona
    Persona p1;
    strcpy(p1.nome, "Mario");
    strcpy(p1.cognome, "Rossi");
    p1.eta = 30;
    
    // Utilizzo della funzione
    stampaPersona(p1);
    
    return 0;
}
```

### Strutture con Tag e Typedef

È anche possibile combinare un tag di struttura con typedef:

```c
typedef struct Persona {
    char nome[50];
    char cognome[50];
    int eta;
} Persona;
```

Questo approccio è utile quando si desidera fare riferimento alla struttura all'interno della sua stessa definizione, ad esempio per creare strutture autoreferenziali come liste collegate:

```c
typedef struct Nodo {
    int valore;
    struct Nodo* prossimo; // Riferimento alla stessa struttura
} Nodo;
```

## Typedef con Unioni

Anche le unioni possono beneficiare dell'uso di `typedef`, con una sintassi simile a quella delle strutture.

### Esempio Base

```c
#include <stdio.h>

// Definizione di un'unione con typedef
typedef union {
    int i;
    float f;
    char c;
} Dato;

int main() {
    Dato d;
    
    d.i = 42;
    printf("Intero: %d\n", d.i);
    
    d.f = 3.14;
    printf("Float: %f\n", d.f); // L'intero non è più valido
    
    d.c = 'A';
    printf("Carattere: %c\n", d.c); // Il float non è più valido
    
    return 0;
}
```

### Unioni con Tag

Come per le strutture, è possibile utilizzare un tag con le unioni:

```c
typedef union Valore {
    int intero;
    float reale;
    char carattere;
} Valore;
```

## Combinazione di Strutture e Unioni

Un caso d'uso avanzato è la combinazione di strutture e unioni, spesso utilizzata per implementare varianti di tipi o per ottimizzare l'uso della memoria.

```c
#include <stdio.h>

// Definizione di un tipo di dato che può contenere diversi tipi di valori
typedef struct {
    enum { INT, FLOAT, CHAR } tipo;
    union {
        int i;
        float f;
        char c;
    } valore;
} Variante;

// Funzione per stampare il valore in base al tipo
void stampaVariante(Variante v) {
    switch(v.tipo) {
        case INT:
            printf("Intero: %d\n", v.valore.i);
            break;
        case FLOAT:
            printf("Float: %f\n", v.valore.f);
            break;
        case CHAR:
            printf("Carattere: %c\n", v.valore.c);
            break;
    }
}

int main() {
    // Creazione di varianti di diversi tipi
    Variante v1 = {INT, {42}};
    Variante v2 = {FLOAT, {.f = 3.14}};
    Variante v3 = {CHAR, {.c = 'A'}};
    
    // Stampa dei valori
    stampaVariante(v1);
    stampaVariante(v2);
    stampaVariante(v3);
    
    return 0;
}
```

## Vantaggi dell'Uso di Typedef con Strutture e Unioni

1. **Sintassi Semplificata**: Elimina la necessità di utilizzare le parole chiave `struct` o `union` ogni volta che si dichiara una variabile.

2. **Incapsulamento**: Aiuta a nascondere i dettagli di implementazione, fornendo un'interfaccia più pulita.

3. **Manutenibilità**: Facilita la modifica della definizione di una struttura o unione senza dover cambiare il codice che la utilizza.

4. **Leggibilità**: Rende il codice più conciso e facile da leggere, specialmente con strutture complesse.

## Conclusione

L'uso di `typedef` con strutture e unioni è una pratica molto comune nella programmazione C, che migliora significativamente la leggibilità e la manutenibilità del codice. Questa tecnica è particolarmente utile quando si lavora con strutture dati complesse o quando si desidera creare un'astrazione sui tipi di dati utilizzati nel programma.

Nel prossimo capitolo, esploreremo usi più avanzati di `typedef`, inclusi i puntatori a funzione e la creazione di tipi astratti di dati (TAD).