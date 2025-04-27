# Strutture

## Introduzione

Benvenuti all'esercitazione 16 dedicata alle strutture in C. In questa lezione, esploreremo come definire e utilizzare le strutture, che rappresentano uno dei meccanismi fondamentali per creare tipi di dati personalizzati in C, permettendo di raggruppare variabili di tipi diversi sotto un unico nome.

## Argomenti Trattati

- Definizione e dichiarazione di strutture
- Accesso ai membri di una struttura
- Strutture annidate
- Array di strutture
- Puntatori a strutture e l'operatore ->
- Passaggio di strutture alle funzioni
- Allocazione dinamica di strutture

## Materiale Teorico

- [Introduzione alle Strutture](./teoria/introduzione_strutture.md)
- [Strutture Avanzate](./teoria/strutture_avanzate.md)
- [Strutture e Funzioni](./teoria/strutture_funzioni.md)

## Esempi Pratici

In questa esercitazione troverete diversi esempi pratici:

1. `strutture_base.c` - Esempi base di definizione e utilizzo delle strutture
2. `strutture_annidate.c` - Esempi di strutture annidate
3. `array_strutture.c` - Creazione e gestione di array di strutture
4. `puntatori_strutture.c` - Utilizzo di puntatori con le strutture

## Best Practices

- Utilizzare nomi significativi per le strutture e i loro membri
- Organizzare i membri delle strutture in modo logico
- Considerare l'allineamento dei membri per ottimizzare l'uso della memoria
- Utilizzare typedef per creare alias più semplici per i tipi di struttura
- Inizializzare sempre le strutture prima dell'uso
- Preferire il passaggio per indirizzo quando si passano strutture grandi alle funzioni

## Esercizi Proposti

1. Creare una struttura per rappresentare un libro (titolo, autore, anno, ecc.) e implementare funzioni per gestire una biblioteca
2. Implementare una rubrica telefonica utilizzando un array di strutture
3. Creare una struttura per rappresentare una data e implementare funzioni per confrontare date e calcolare la differenza in giorni
4. Sviluppare un programma che gestisca un inventario di prodotti utilizzando strutture allocate dinamicamente

## Domande di Autovalutazione

1. Qual è la differenza tra una struttura e un array?
2. Come si accede ai membri di una struttura tramite un puntatore?
3. Perché è utile utilizzare typedef con le strutture?
4. Come si può allocare dinamicamente un array di strutture?
5. Quali sono i vantaggi del passaggio di strutture per riferimento rispetto al passaggio per valore?

## Approfondimenti

Per approfondire ulteriormente questi concetti, consultate:

- K&R C Programming Language, Capitolo 6
- C: A Reference Manual, Sezione sulle strutture
- Advanced C Programming by Example, Capitolo sulle strutture e tipi di dati personalizzati

Proseguite con l'esercitazione [17 - Unioni ed Enumerazioni](../17_Unioni_Enumerazioni/) per apprendere altri tipi di dati personalizzati in C.