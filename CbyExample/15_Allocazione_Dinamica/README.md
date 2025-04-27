# Allocazione Dinamica della Memoria

## Introduzione

Benvenuti all'esercitazione 15 dedicata all'allocazione dinamica della memoria in C. In questa lezione, esploreremo come gestire la memoria in modo dinamico, permettendo ai programmi di allocare e liberare memoria durante l'esecuzione in base alle necessità effettive.

## Argomenti Trattati

- Concetti di memoria statica vs dinamica
- Funzioni per l'allocazione dinamica: malloc, calloc, realloc
- Liberazione della memoria con free
- Gestione degli errori nell'allocazione
- Tecniche per evitare memory leak e dangling pointers
- Strutture dati dinamiche (introduzione)

## Materiale Teorico

- [Introduzione all'Allocazione Dinamica](./teoria/introduzione_allocazione_dinamica.md)
- [Funzioni di Allocazione e Liberazione](./teoria/funzioni_allocazione.md)
- [Gestione degli Errori e Best Practices](./teoria/gestione_errori_best_practices.md)

## Esempi Pratici

In questa esercitazione troverete diversi esempi pratici:

1. `malloc_esempio.c` - Utilizzo base di malloc e free
2. `calloc_realloc_esempio.c` - Esempi di utilizzo di calloc e realloc
3. `array_dinamici.c` - Creazione e gestione di array con dimensione determinata a runtime
4. `matrici_dinamiche.c` - Allocazione dinamica di matrici bidimensionali

## Best Practices

- Controllare sempre il valore di ritorno delle funzioni di allocazione
- Liberare sempre la memoria allocata quando non è più necessaria
- Evitare di accedere a memoria già liberata (dangling pointers)
- Tenere traccia di tutte le allocazioni in programmi complessi
- Utilizzare strumenti come Valgrind per identificare memory leak
- Inizializzare sempre la memoria allocata prima dell'uso

## Esercizi Proposti

1. Implementare una funzione che crei un array dinamico di interi, lo riempia con valori casuali e lo restituisca
2. Creare un programma che gestisca una rubrica telefonica con allocazione dinamica
3. Implementare una funzione che ridimensioni un array dinamico preservando i dati esistenti
4. Sviluppare un programma che allochi dinamicamente una matrice e la utilizzi per un prodotto matrice-vettore

## Domande di Autovalutazione

1. Qual è la differenza tra malloc e calloc?
2. Cosa succede se malloc non riesce ad allocare la memoria richiesta?
3. Perché è importante liberare la memoria allocata dinamicamente?
4. Come si può ridimensionare un array allocato dinamicamente?
5. Cosa sono i memory leak e come si possono prevenire?

## Approfondimenti

Per approfondire ulteriormente questi concetti, consultate:

- K&R C Programming Language, Capitolo 7
- C: A Reference Manual, Sezione sulla gestione della memoria
- Advanced C Programming by Example, Capitolo sull'allocazione dinamica

Proseguite con l'esercitazione [16 - Strutture](../16_Strutture/) per apprendere come definire e utilizzare strutture dati personalizzate in C.