# Storia del linguaggio C

Il linguaggio C è uno dei linguaggi di programmazione più influenti nella storia dell'informatica. La sua evoluzione ha plasmato lo sviluppo software moderno e ha influenzato numerosi linguaggi successivi.

## Origini del C

Il linguaggio C fu sviluppato nei primi anni '70 presso i Bell Laboratories da **Dennis Ritchie**, con il contributo di **Ken Thompson**. La sua creazione è strettamente legata allo sviluppo del sistema operativo UNIX.

### Cronologia essenziale:

- **1969-1970**: Ken Thompson sviluppa il linguaggio B, un linguaggio semplificato derivato da BCPL
- **1971-1973**: Dennis Ritchie evolve il linguaggio B creando il C
- **1973**: La maggior parte del kernel UNIX viene riscritta in C
- **1978**: Brian Kernighan e Dennis Ritchie pubblicano "The C Programming Language" (noto come K&R C)

## Evoluzione degli standard

### K&R C (1978)

La prima descrizione informale del linguaggio C apparve nel libro "The C Programming Language" di Kernighan e Ritchie. Questa versione è conosciuta come "K&R C" o "C classico".

### ANSI C / C89 (1989)

Il primo standard ufficiale del C fu pubblicato dall'American National Standards Institute (ANSI) nel 1989, noto come "ANSI C" o "C89".

Principali novità:
- Prototipi di funzione
- Qualificatori `const` e `volatile`
- Tipo `void`
- Standardizzazione della libreria standard

### C90 (1990)

L'International Organization for Standardization (ISO) adottò l'ANSI C con minime modifiche, creando lo standard ISO/IEC 9899:1990, o "C90".

### C99 (1999)

Lo standard C99 (ISO/IEC 9899:1999) introdusse numerose nuove funzionalità.

Principali novità:
- Commenti in stile C++ (`//`)
- Dichiarazione di variabili in qualsiasi punto del blocco
- Array a lunghezza variabile
- Tipo `long long int`
- Tipo booleano (`_Bool` e `<stdbool.h>`)
- Supporto migliorato per i numeri complessi
- Intestazioni aggiuntive (`<complex.h>`, `<tgmath.h>`, ecc.)

### C11 (2011)

Lo standard C11 (ISO/IEC 9899:2011) aggiunse ulteriori funzionalità e miglioramenti.

Principali novità:
- Supporto per il multithreading (`<threads.h>`)
- Specifiche di allineamento (`_Alignas`, `_Alignof`)
- Funzioni generiche (`_Generic`)
- Miglioramenti alla libreria standard
- Specifiche di atomicità (`<stdatomic.h>`)

### C17 (2018)

Lo standard C17 (ISO/IEC 9899:2018) è principalmente una versione di manutenzione che corregge difetti in C11 senza aggiungere nuove funzionalità.

### C23 (in sviluppo)

Lo standard C23 è in fase di sviluppo e introdurrà nuove funzionalità come:
- Attributi standard
- Miglioramenti ai tipi di dati
- Funzionalità per la programmazione parallela

## Influenza su altri linguaggi

Il C ha influenzato direttamente o indirettamente numerosi linguaggi di programmazione, tra cui:

- **C++**: un'estensione del C che aggiunge funzionalità di programmazione orientata agli oggetti
- **Java**: sintassi simile al C ma con un modello di memoria diverso
- **C#**: sviluppato da Microsoft, combina elementi di C++ e Java
- **Objective-C**: aggiunge messaggistica in stile Smalltalk al C
- **PHP**: sintassi influenzata dal C
- **JavaScript**: sintassi ispirata al C
- **Perl, Python, Ruby**: influenzati in vari aspetti dal C

## Esempi storici

### Primo programma "Hello, World!" in K&R C

```c
main()
{
    printf("Hello, World!\n");
}
```

### Lo stesso programma in ANSI C

```c
#include <stdio.h>

int main(void)
{
    printf("Hello, World!\n");
    return 0;
}
```

## Best Practice

- **Conoscere la storia**: Comprendere l'evoluzione del C aiuta a capire perché certe funzionalità esistono e altre no
- **Specificare lo standard**: Quando si sviluppa in C, è utile specificare quale standard si sta seguendo (es. `-std=c99` in GCC)
- **Compatibilità**: Per massima portabilità, considerare la compatibilità con gli standard più diffusi (C89/C90)
- **Modernizzazione**: Per nuovi progetti, utilizzare gli standard più recenti per sfruttare le funzionalità moderne

## Tips & Tricks

- Molti compilatori moderni supportano estensioni specifiche oltre agli standard ufficiali
- È possibile utilizzare strumenti come `gcc -Wall -pedantic` per assicurarsi che il codice sia conforme allo standard
- Conoscere le differenze tra gli standard può aiutare a diagnosticare problemi di portabilità
- I libri e le risorse più datate potrebbero riferirsi a versioni precedenti del C, quindi è importante verificare a quale standard si riferiscono

## Domande di Autovalutazione

1. **Chi è considerato il creatore principale del linguaggio C?**
   a) Ken Thompson
   b) Dennis Ritchie
   c) Brian Kernighan
   d) Bjarne Stroustrup

2. **In quale anno è stato pubblicato il primo standard ANSI C?**
   a) 1978
   b) 1983
   c) 1989
   d) 1999

3. **Quale delle seguenti caratteristiche è stata introdotta nello standard C99?**
   a) Supporto per il multithreading
   b) Commenti in stile C++ (//)
   c) Prototipi di funzione
   d) Specifiche di atomicità

4. **Quale sistema operativo è strettamente legato allo sviluppo del linguaggio C?**
   a) MS-DOS
   b) UNIX
   c) Windows
   d) Linux

5. **Quale libro ha formalizzato per la prima volta il linguaggio C?**
   a) "The C Programming Language"
   b) "The Art of Computer Programming"
   c) "Programming in C"
   d) "C: A Reference Manual"

## Proposte di Esercizi

1. Crea una timeline visuale dell'evoluzione del linguaggio C, evidenziando gli standard principali e le loro caratteristiche distintive.

2. Scrivi un programma "Hello, World!" conforme a ciascuno degli standard principali del C (K&R, ANSI C, C99, C11) e commenta le differenze.

3. Ricerca e documenta tre esempi di funzionalità che erano estensioni proprietarie prima di essere incorporate negli standard ufficiali.

4. Analizza un programma C esistente e identifica quali funzionalità richiedono uno standard specifico (es. C99 o superiore).

5. Compila lo stesso programma con diversi flag di standard (`-std=c89`, `-std=c99`, ecc.) e osserva se ci sono differenze nel comportamento o avvisi del compilatore.

## Risposte alle Domande di Autovalutazione

1. **Risposta: b) Dennis Ritchie**
   Dennis Ritchie è universalmente riconosciuto come il creatore principale del linguaggio C, sviluppato nei Bell Laboratories nei primi anni '70.

2. **Risposta: c) 1989**
   Il primo standard ANSI C (X3.159-1989) fu pubblicato nel 1989, seguito poco dopo dallo standard ISO (ISO/IEC 9899:1990).

3. **Risposta: b) Commenti in stile C++ (//)** 
   I commenti in stile C++ (//), insieme ad altre caratteristiche come la dichiarazione di variabili in qualsiasi punto del blocco e gli array a lunghezza variabile, furono introdotti nello standard C99.

4. **Risposta: b) UNIX**
   Il linguaggio C fu sviluppato principalmente per riscrivere il sistema operativo UNIX, che in precedenza era scritto in assembly.

5. **Risposta: a) "The C Programming Language"**
   Il libro "The C Programming Language" di Brian Kernighan e Dennis Ritchie, pubblicato nel 1978, fornì la prima descrizione formale del linguaggio, diventando noto come "K&R C".

---

[Indice degli argomenti](./README.md) | [Prossimo argomento: Caratteristiche del linguaggio C](./02_Caratteristiche_del_C.md) | [Indice del corso](../../README.md)