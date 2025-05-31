# Direttive di Inclusione e Definizione in C

## Introduzione

Il preprocessore C è una fase del processo di compilazione che manipola il codice sorgente prima che venga effettivamente compilato. Le direttive del preprocessore iniziano con il simbolo `#` e non sono istruzioni C, ma comandi per il preprocessore stesso. In questa guida, esploreremo le direttive di inclusione (`#include`) e definizione (`#define`, `#undef`).

## La Direttiva #include

La direttiva `#include` permette di inserire il contenuto di un file all'interno di un altro file. È fondamentale per l'organizzazione del codice e il riutilizzo delle funzionalità.

### Sintassi

Esistono due forme principali:

```c
#include <nome_file>   // Cerca nei percorsi standard del sistema
#include "nome_file"   // Cerca prima nella directory corrente, poi nei percorsi standard
```

### Esempi di Utilizzo

```c
#include <stdio.h>     // Inclusione di una libreria standard
#include <stdlib.h>    // Altra libreria standard
#include "myheader.h"  // Inclusione di un header file personalizzato
```

### Guardie di Inclusione

Per evitare problemi di inclusioni multiple dello stesso file, si utilizzano le guardie di inclusione:

```c
// myheader.h
#ifndef MYHEADER_H
#define MYHEADER_H

// Contenuto del file header

#endif // MYHEADER_H
```

Alternativamente, molti compilatori moderni supportano la direttiva `#pragma once`:

```c
// myheader.h
#pragma once

// Contenuto del file header
```

### Organizzazione dei File Header

Una buona pratica è organizzare i file header in modo che contengano:

1. Guardie di inclusione
2. Inclusioni di altri header necessari
3. Dichiarazioni di costanti e macro
4. Dichiarazioni di tipi (struct, enum, typedef)
5. Prototipi di funzioni

```c
// math_utils.h
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <math.h>  // Inclusione necessaria

// Costanti e macro
#define PI 3.14159265358979323846
#define SQUARE(x) ((x) * (x))

// Dichiarazioni di tipi
typedef struct {
    double x;
    double y;
} Point2D;

// Prototipi di funzioni
double distance(Point2D p1, Point2D p2);
double area_of_circle(double radius);

#endif // MATH_UTILS_H
```

## La Direttiva #define

La direttiva `#define` permette di definire macro, che sono sostituzioni di testo effettuate dal preprocessore.

### Sintassi di Base

```c
#define NOME_MACRO valore_sostituzione
```

### Esempi di Macro Semplici

```c
#define PI 3.14159265358979323846
#define MAX_BUFFER_SIZE 1024
#define DEBUG_MODE

int main() {
    double area = PI * radius * radius;
    char buffer[MAX_BUFFER_SIZE];
    
    #ifdef DEBUG_MODE
    printf("Debug: area = %f\n", area);
    #endif
    
    return 0;
}
```

### Macro con Parametri

Le macro possono anche accettare parametri:

```c
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define SQUARE(x) ((x) * (x))

int main() {
    int max_value = MAX(10, 20);  // Diventa ((10) > (20) ? (10) : (20))
    int squared = SQUARE(5);       // Diventa ((5) * (5))
    
    return 0;
}
```

### Importanza delle Parentesi nelle Macro

È fondamentale utilizzare parentesi nelle macro per evitare problemi di precedenza degli operatori:

```c
// Macro errata
#define SQUARE_BAD(x) x * x

// Macro corretta
#define SQUARE_GOOD(x) ((x) * (x))

int main() {
    int a = SQUARE_BAD(2 + 3);  // Diventa 2 + 3 * 2 + 3 = 2 + 6 + 3 = 11
    int b = SQUARE_GOOD(2 + 3);  // Diventa ((2 + 3) * (2 + 3)) = 25
    
    return 0;
}
```

### Macro Multi-linea

Per definire macro su più righe, si utilizza il carattere di continuazione `\`:

```c
#define COMPLEX_OPERATION(x, y) do { \
    int temp = (x) + (y); \
    (x) = temp * 2; \
    (y) = temp - (y); \
} while(0)

int main() {
    int a = 5, b = 10;
    COMPLEX_OPERATION(a, b);
    return 0;
}
```

L'utilizzo di `do { ... } while(0)` permette di utilizzare la macro come una normale istruzione C, inclusa la possibilità di terminarla con un punto e virgola.

## La Direttiva #undef

La direttiva `#undef` permette di rimuovere una definizione di macro precedentemente creata con `#define`.

```c
#define DEBUG_MODE

// Codice che utilizza DEBUG_MODE

#undef DEBUG_MODE  // Rimuove la definizione di DEBUG_MODE

// Codice in cui DEBUG_MODE non è più definito
```

Questo è utile quando si vuole limitare l'ambito di una macro a una specifica sezione di codice.

## Operatori del Preprocessore

### L'Operatore # (Stringification)

L'operatore `#` converte un parametro di macro in una stringa letterale:

```c
#define STRINGIFY(x) #x

int main() {
    printf("%s\n", STRINGIFY(Hello));  // Stampa "Hello"
    return 0;
}
```

### L'Operatore ## (Concatenazione)

L'operatore `##` concatena due token:

```c
#define CONCAT(a, b) a ## b

int main() {
    int xy = 42;
    printf("%d\n", CONCAT(x, y));  // Accede alla variabile xy
    return 0;
}
```

## Macro Predefinite

Il preprocessore C fornisce alcune macro predefinite utili:

```c
#include <stdio.h>

int main() {
    printf("File: %s\n", __FILE__);           // Nome del file corrente
    printf("Linea: %d\n", __LINE__);          // Numero di linea corrente
    printf("Data di compilazione: %s\n", __DATE__);  // Data di compilazione
    printf("Ora di compilazione: %s\n", __TIME__);   // Ora di compilazione
    printf("Standard C: %ld\n", __STDC__);      // 1 se il compilatore è conforme allo standard C
    
    return 0;
}
```

## Best Practices

1. **Utilizzare le guardie di inclusione** per prevenire inclusioni multiple.

2. **Preferire le funzioni inline alle macro** per operazioni complesse, quando possibile:

```c
// Preferire questo
inline int max(int a, int b) {
    return a > b ? a : b;
}

// A questo
#define MAX(a, b) ((a) > (b) ? (a) : (b))
```

3. **Utilizzare parentesi nelle macro** per evitare problemi di precedenza.

4. **Documentare chiaramente il comportamento delle macro**, specialmente quelle complesse.

5. **Utilizzare nomi maiuscoli per le macro** per distinguerle dalle funzioni e variabili.

6. **Limitare l'uso di macro** a casi in cui offrono un chiaro vantaggio rispetto alle alternative.

## Conclusione

Le direttive di inclusione e definizione sono strumenti potenti del preprocessore C che permettono di organizzare il codice, creare astrazioni e implementare funzionalità che sarebbero difficili o impossibili con il linguaggio C standard. Tuttavia, è importante utilizzarle con attenzione, seguendo le best practices per evitare problemi comuni.

## Esercizi

1. Crea un file header con guardie di inclusione che definisca strutture e funzioni per la gestione di una lista concatenata.

2. Implementa una macro `DEBUG_PRINT` che stampi informazioni di debug (file, linea, messaggio) solo quando è definita la macro `DEBUG_MODE`.

3. Crea una macro `SWAP(type, a, b)` che scambi i valori di due variabili dello stesso tipo, utilizzando gli operatori del preprocessore per gestire diversi tipi di dati.