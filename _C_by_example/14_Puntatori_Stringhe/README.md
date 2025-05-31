# Puntatori e Stringhe

## Introduzione

Benvenuti all'esercitazione 14 dedicata all'uso dei puntatori con le stringhe in C. In questa lezione, esploreremo come i puntatori possono essere utilizzati per manipolare stringhe in modo efficiente, approfondendo le tecniche avanzate di gestione delle stringhe attraverso i puntatori.

## Argomenti Trattati

- Rappresentazione delle stringhe in C come array di caratteri
- Manipolazione di stringhe tramite puntatori
- Funzioni standard della libreria string.h e loro implementazione con puntatori
- Tecniche avanzate di elaborazione delle stringhe
- Gestione efficiente della memoria con stringhe dinamiche

## Materiale Teorico

- [Stringhe e Puntatori: Concetti Base](./teoria/stringhe_puntatori_base.md)
- [Funzioni Avanzate per Stringhe](./teoria/funzioni_avanzate_stringhe.md)
- [Gestione Dinamica delle Stringhe](./teoria/gestione_dinamica_stringhe.md)

## Esempi Pratici

In questa esercitazione troverete diversi esempi pratici:

1. `stringhe_puntatori_base.c` - Esempi base di manipolazione di stringhe con puntatori
2. `implementazione_funzioni_string.c` - Implementazione di alcune funzioni della libreria string.h
3. `stringhe_dinamiche.c` - Gestione di stringhe con allocazione dinamica della memoria

## Best Practices

- Utilizzare sempre il carattere terminatore '\0' quando si manipolano stringhe manualmente
- Verificare sempre che ci sia spazio sufficiente nelle stringhe di destinazione
- Preferire funzioni sicure come strncpy invece di strcpy quando possibile
- Liberare sempre la memoria allocata dinamicamente per le stringhe
- Utilizzare const per i puntatori a stringhe che non devono essere modificate

## Esercizi Proposti

1. Implementare una funzione che inverta una stringa utilizzando esclusivamente puntatori
2. Creare una funzione che rimuova tutti gli spazi da una stringa usando i puntatori
3. Implementare una versione sicura della funzione strcat che controlli lo spazio disponibile
4. Sviluppare un programma che utilizzi puntatori per contare le occorrenze di ogni carattere in una stringa

## Domande di Autovalutazione

1. Qual è la differenza tra un array di caratteri e un puntatore a char in C?
2. Come si può implementare la funzione strlen utilizzando i puntatori?
3. Perché è importante il carattere terminatore '\0' nelle stringhe C?
4. Come si può allocare dinamicamente una stringa di lunghezza variabile?
5. Quali sono i rischi più comuni nella manipolazione delle stringhe con puntatori?

## Approfondimenti

Per approfondire ulteriormente questi concetti, consultate:

- K&R C Programming Language, Capitolo 5
- C: A Reference Manual, Sezione sulle stringhe e puntatori
- Advanced C Programming by Example, Capitolo sulla manipolazione delle stringhe

Proseguite con l'esercitazione [15 - Allocazione Dinamica della Memoria](../15_Allocazione_Dinamica/) per apprendere come gestire la memoria in modo dinamico in C.