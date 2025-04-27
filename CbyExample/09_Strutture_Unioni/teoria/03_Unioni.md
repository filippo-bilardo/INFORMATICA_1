# Unioni in C

## Cos'è un'Unione?

Un'**unione** in C è un tipo di dato composto che, come una struttura, può contenere membri di tipi diversi. Tuttavia, a differenza delle strutture, in un'unione tutti i membri condividono la stessa area di memoria. Questo significa che un'unione può contenere un solo valore alla volta, e questo valore può essere interpretato in modi diversi a seconda del membro a cui si accede.

La dimensione di un'unione è determinata dal membro più grande, poiché deve essere in grado di contenere qualsiasi membro dell'unione.

## Definizione di un'Unione

La sintassi per definire un'unione è simile a quella per definire una struttura, ma si utilizza la parola chiave `union` invece di `struct`.

### Sintassi

```c
union NomeUnione {
    tipo1 membro1;
    tipo2 membro2;
    // ...
    tipoN membroN;
};
```

### Esempio

```c
union Dato {
    int i;
    float f;
    char c;
};
```

In questo esempio, abbiamo definito un'unione chiamata `Dato` che può contenere un intero, un float o un carattere, ma solo uno di questi alla volta.

## Dichiarazione di Variabili Unione

Come per le strutture, ci sono diversi modi per dichiarare variabili di tipo unione:

### 1. Dichiarazione dopo la definizione

```c
union Dato dato1, dato2;
```

### 2. Dichiarazione e definizione combinate

```c
union Dato {
    int i;
    float f;
    char c;
} dato1, dato2;
```

### 3. Dichiarazione con inizializzazione

```c
union Dato dato1 = {42};  // Inizializza il primo membro (int i)
```

È importante notare che quando si inizializza un'unione, solo il primo membro viene inizializzato, a meno che non si utilizzi un inizializzatore designato (C99 e successivi).

```c
union Dato dato2 = {.f = 3.14};  // Inizializza il membro float
```

## Accesso ai Membri di un'Unione

Per accedere ai membri di un'unione, si utilizza l'operatore punto (`.`) come per le strutture.

```c
#include <stdio.h>

int main() {
    union Dato {
        int i;
        float f;
        char c;
    };
    
    union Dato dato;
    
    dato.i = 42;
    printf("dato.i: %d\n", dato.i);
    
    dato.f = 3.14;
    printf("dato.f: %f\n", dato.f);
    printf("dato.i: %d\n", dato.i);  // Il valore di i è ora indefinito
    
    dato.c = 'A';
    printf("dato.c: %c\n", dato.c);
    printf("dato.f: %f\n", dato.f);  // Il valore di f è ora indefinito
    
    return 0;
}
```

Come si può vedere dall'esempio, quando si assegna un valore a un membro dell'unione, i valori degli altri membri diventano indefiniti, poiché tutti i membri condividono la stessa area di memoria.

## Dimensione di un'Unione

La dimensione di un'unione è determinata dal membro più grande, poiché deve essere in grado di contenere qualsiasi membro dell'unione.

```c
#include <stdio.h>

int main() {
    union Dato {
        int i;       // 4 byte
        float f;     // 4 byte
        char c;      // 1 byte
        double d;    // 8 byte
    };
    
    printf("Dimensione di int: %zu byte\n", sizeof(int));
    printf("Dimensione di float: %zu byte\n", sizeof(float));
    printf("Dimensione di char: %zu byte\n", sizeof(char));
    printf("Dimensione di double: %zu byte\n", sizeof(double));
    printf("Dimensione dell'unione Dato: %zu byte\n", sizeof(union Dato));
    
    return 0;
}
```

In questo esempio, la dimensione dell'unione `Dato` sarà di 8 byte, che è la dimensione del membro più grande (`double`).

## Applicazioni delle Unioni

Le unioni sono utili in diverse situazioni:

### 1. Risparmio di memoria

Quando si sa che una variabile può contenere solo uno di diversi tipi di dati alla volta, un'unione può risparmiare memoria rispetto a una struttura.

### 2. Conversione di tipi

Le unioni possono essere utilizzate per convertire tra tipi di dati senza cast espliciti.

```c
#include <stdio.h>

int main() {
    union Conversione {
        int i;
        float f;
    };
    
    union Conversione conv;
    
    conv.f = 3.14;
    printf("float: %f\n", conv.f);
    printf("rappresentazione in int: %d\n", conv.i);
    
    return 0;
}
```

### 3. Accesso a parti di dati

Le unioni possono essere utilizzate per accedere a parti specifiche di un dato più grande.

```c
#include <stdio.h>

int main() {
    union {
        int intero;
        struct {
            unsigned char byte1;
            unsigned char byte2;
            unsigned char byte3;
            unsigned char byte4;
        } bytes;
    } numero;
    
    numero.intero = 0x12345678;
    
    printf("Intero: 0x%X\n", numero.intero);
    printf("Byte 1: 0x%X\n", numero.bytes.byte1);
    printf("Byte 2: 0x%X\n", numero.bytes.byte2);
    printf("Byte 3: 0x%X\n", numero.bytes.byte3);
    printf("Byte 4: 0x%X\n", numero.bytes.byte4);
    
    return 0;
}
```

In questo esempio, l'unione permette di accedere ai singoli byte di un intero.

## Unioni Anonime

Come per le strutture, è possibile definire unioni anonime, che non hanno un nome ma i cui membri sono accessibili direttamente.

```c
#include <stdio.h>

int main() {
    struct {
        int tipo;  // 0 per int, 1 per float
        union {
            int i;
            float f;
        };  // Unione anonima
    } dato;
    
    dato.tipo = 0;
    dato.i = 42;
    printf("Intero: %d\n", dato.i);
    
    dato.tipo = 1;
    dato.f = 3.14;
    printf("Float: %f\n", dato.f);
    
    return 0;
}
```

In questo esempio, i membri `i` e `f` dell'unione anonima sono accessibili direttamente come membri della struttura esterna.

## Unioni e Typedef

Come per le strutture, è comune utilizzare `typedef` con le unioni per creare un nuovo nome di tipo.

```c
typedef union {
    int i;
    float f;
    char c;
} Dato;

// Ora possiamo dichiarare variabili senza usare la parola chiave 'union'
Dato dato1, dato2;
```

## Unioni e Puntatori

Come per le strutture, è possibile utilizzare puntatori a unioni e accedere ai membri utilizzando l'operatore freccia (`->`).

```c
#include <stdio.h>

int main() {
    union Dato {
        int i;
        float f;
        char c;
    };
    
    union Dato dato;
    union Dato *ptrDato = &dato;
    
    ptrDato->i = 42;
    printf("dato.i: %d\n", dato.i);
    
    return 0;
}
```

## Conclusione

Le unioni in C sono un potente strumento per gestire dati che possono essere interpretati in modi diversi. Sono particolarmente utili quando si vuole risparmiare memoria o quando si lavora a basso livello con la rappresentazione dei dati.

Tuttavia, è importante utilizzarle con attenzione, poiché l'accesso a un membro diverso da quello a cui è stato assegnato l'ultimo valore può portare a risultati imprevedibili.

## Esercizi

1. Scrivi un programma che utilizzi un'unione per convertire un intero nella sua rappresentazione in byte e viceversa.

2. Crea un'unione che possa contenere un intero, un float o una stringa. Scrivi una funzione che stampi il valore dell'unione in base a un parametro che indica il tipo di dato contenuto.

3. Implementa una struttura `Variante` che possa contenere un valore di uno dei seguenti tipi: intero, float, carattere o stringa. La struttura deve includere un campo che indichi il tipo di dato contenuto e un'unione per il valore stesso.

4. Scrivi un programma che utilizzi un'unione per accedere ai bit individuali di un intero. Implementa funzioni per impostare, cancellare e verificare un bit specifico.

5. Crea un programma che utilizzi un'unione per convertire tra diversi formati di colore (RGB, HSV, ecc.). Implementa funzioni per la conversione tra questi formati.