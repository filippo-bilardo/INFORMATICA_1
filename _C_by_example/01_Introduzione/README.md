# Esercitazione 1: Introduzione al linguaggio C

## Descrizione

Questa prima esercitazione introduce il linguaggio C, la sua storia, le sue caratteristiche principali e l'ambiente di sviluppo necessario per iniziare a programmare. Imparerai a scrivere, compilare ed eseguire il tuo primo programma "Hello, World!" e comprenderai la struttura base di un programma C.

## Obiettivi di apprendimento

- Conoscere la storia e l'evoluzione del linguaggio C
- Comprendere le caratteristiche fondamentali del C
- Configurare un ambiente di sviluppo C
- Scrivere, compilare ed eseguire un primo programma
- Comprendere la struttura base di un programma C

## Indice degli argomenti teorici

1. [Storia del linguaggio C](./teoria/01_Storia_del_C.md)
   - Origini e sviluppo del C
   - Standard del linguaggio (K&R, ANSI C, C99, C11, C17, C23)
   - Influenza su altri linguaggi

2. [Caratteristiche del linguaggio C](./teoria/02_Caratteristiche_del_C.md)
   - Vantaggi e limitazioni
   - Ambiti di utilizzo
   - Confronto con altri linguaggi

3. [Ambiente di sviluppo](./teoria/03_Ambiente_di_Sviluppo.md)
   - Compilatori (GCC, Clang, MSVC)
   - Editor e IDE
   - Installazione e configurazione

4. [Il primo programma](./teoria/04_Primo_Programma.md)
   - Struttura di un programma C
   - Il programma "Hello, World!"
   - Processo di compilazione ed esecuzione

## Esercitazione pratica

### Esercizio 1.1: Hello, World!

Scrivi un programma che stampi a schermo la frase "Hello, World!".

```c
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
```

### Esercizio 1.2: Informazioni personali

Modifica il programma precedente per stampare il tuo nome, la tua età e il tuo corso di studi su righe separate.

### Esercizio 1.3: ASCII Art

Crea un programma che stampi un disegno semplice (come una faccia sorridente o una casa) utilizzando caratteri ASCII.

## Risorse aggiuntive

- [Standard C17 (ISO/IEC 9899:2018)](https://www.iso.org/standard/74528.html)
- [The C Programming Language](https://en.wikipedia.org/wiki/The_C_Programming_Language) di Brian Kernighan e Dennis Ritchie
- [Learn C Programming](https://www.programiz.com/c-programming) su Programiz

---

[Indice del corso](../README.md) | [Prossima esercitazione](../02_Variabili_e_Tipi/README.md)