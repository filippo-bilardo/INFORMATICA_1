# Esercitazione 3: Operatori in C

## Descrizione

Questa esercitazione introduce i vari tipi di operatori disponibili nel linguaggio C. Imparerai a utilizzare operatori aritmetici, relazionali, logici, di assegnazione, bit a bit e altri operatori speciali. Comprenderai anche le regole di precedenza e associatività che determinano l'ordine di valutazione delle espressioni.

## Obiettivi di apprendimento

- Conoscere e utilizzare correttamente i diversi tipi di operatori in C
- Comprendere la precedenza e l'associatività degli operatori
- Scrivere espressioni complesse utilizzando vari operatori
- Evitare errori comuni nell'uso degli operatori
- Ottimizzare le espressioni per migliorare la leggibilità e l'efficienza

## Indice degli argomenti teorici

1. [Operatori aritmetici](./teoria/01_Operatori_Aritmetici.md)
   - Addizione, sottrazione, moltiplicazione, divisione
   - Modulo (resto della divisione)
   - Incremento e decremento

2. [Operatori relazionali e di uguaglianza](./teoria/02_Operatori_Relazionali.md)
   - Maggiore, minore, maggiore o uguale, minore o uguale
   - Uguale a, diverso da
   - Utilizzo nelle strutture condizionali

3. [Operatori logici](./teoria/03_Operatori_Logici.md)
   - AND logico (&&)
   - OR logico (||)
   - NOT logico (!)
   - Short-circuit evaluation

4. [Operatori di assegnazione](./teoria/04_Operatori_Assegnazione.md)
   - Assegnazione semplice (=)
   - Assegnazioni composte (+=, -=, *=, /=, %=, ecc.)

5. [Operatori bit a bit](./teoria/05_Operatori_Bit_a_Bit.md)
   - AND, OR, XOR, NOT bit a bit
   - Shift a sinistra e a destra
   - Applicazioni pratiche

6. [Altri operatori](./teoria/06_Altri_Operatori.md)
   - Operatore condizionale (ternario)
   - Operatore virgola
   - Operatori di dimensione e indirizzo (sizeof, &, *)

7. [Precedenza e associatività](./teoria/07_Precedenza_Associativita.md)
   - Tabella di precedenza degli operatori
   - Regole di associatività
   - Uso delle parentesi per controllare l'ordine di valutazione

## Esercitazione pratica

### Esercizio 3.1: Operatori aritmetici

Scrivi un programma che utilizzi tutti gli operatori aritmetici per eseguire calcoli su due numeri inseriti dall'utente.

```c
#include <stdio.h>

int main() {
    int a, b;
    
    printf("Inserisci due numeri interi: ");
    scanf("%d %d", &a, &b);
    
    printf("Somma: %d\n", a + b);
    printf("Differenza: %d\n", a - b);
    printf("Prodotto: %d\n", a * b);
    printf("Quoziente: %d\n", a / b);
    printf("Resto: %d\n", a % b);
    
    return 0;
}
```

### Esercizio 3.2: Operatori relazionali e logici

Scrivi un programma che verifichi se un numero è compreso in un determinato intervallo utilizzando operatori relazionali e logici.

```c
#include <stdio.h>

int main() {
    int numero, min, max;
    
    printf("Inserisci un numero: ");
    scanf("%d", &numero);
    
    printf("Inserisci l'intervallo (min max): ");
    scanf("%d %d", &min, &max);
    
    if (numero >= min && numero <= max) {
        printf("%d è compreso nell'intervallo [%d, %d]\n", numero, min, max);
    } else {
        printf("%d NON è compreso nell'intervallo [%d, %d]\n", numero, min, max);
    }
    
    return 0;
}
```

### Esercizio 3.3: Operatori bit a bit

Scrivi un programma che mostri il risultato delle operazioni bit a bit su due numeri.

```c
#include <stdio.h>

int main() {
    unsigned int a, b;
    
    printf("Inserisci due numeri positivi: ");
    scanf("%u %u", &a, &b);
    
    printf("AND bit a bit: %u\n", a & b);
    printf("OR bit a bit: %u\n", a | b);
    printf("XOR bit a bit: %u\n", a ^ b);
    printf("NOT bit a bit di a: %u\n", ~a);
    printf("Shift a sinistra di a di 2 posizioni: %u\n", a << 2);
    printf("Shift a destra di a di 2 posizioni: %u\n", a >> 2);
    
    return 0;
}
```

## Domande di autovalutazione

1. Qual è la differenza tra gli operatori di incremento prefisso (++i) e postfisso (i++)?
2. Cosa succede quando si divide un numero intero per zero in C?
3. Spiega il concetto di "short-circuit evaluation" negli operatori logici.
4. Perché è importante conoscere la precedenza degli operatori?
5. In quali situazioni è preferibile utilizzare gli operatori di assegnazione composta?
6. Come si può utilizzare l'operatore ternario per semplificare il codice?
7. Quali sono le applicazioni pratiche degli operatori bit a bit?

## Suggerimenti e best practice

- Utilizzare le parentesi per rendere esplicito l'ordine di valutazione delle espressioni complesse.
- Evitare effetti collaterali nelle espressioni, specialmente quando si utilizzano operatori di incremento/decremento.
- Prestare attenzione alla divisione tra interi, che tronca il risultato verso zero.
- Utilizzare gli operatori bit a bit solo quando necessario, poiché possono rendere il codice meno leggibile.
- Ricordare che l'operatore di assegnazione (=) è diverso dall'operatore di uguaglianza (==).
- Sfruttare la short-circuit evaluation degli operatori logici per ottimizzare il codice.

## Esercizi proposti

1. Scrivi un programma che calcoli il valore assoluto di un numero senza utilizzare funzioni di libreria.
2. Implementa un programma che verifichi se un numero è pari o dispari utilizzando operatori bit a bit.
3. Crea un programma che converta un numero da decimale a binario utilizzando operatori bit a bit.
4. Scrivi un programma che implementi una calcolatrice semplice utilizzando l'operatore switch.
5. Implementa un programma che verifichi se un anno è bisestile utilizzando operatori logici.