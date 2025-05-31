# Unioni ed Enumerazioni

## Introduzione

Benvenuti all'esercitazione 17 dedicata alle unioni ed enumerazioni in C. In questa lezione, esploreremo questi due importanti tipi di dati che completano le possibilità di creazione di strutture dati personalizzate in C, offrendo funzionalità specifiche per casi d'uso particolari.

## Argomenti Trattati

### Unioni
- Definizione e dichiarazione di unioni
- Differenze tra unioni e strutture
- Accesso ai membri di un'unione
- Casi d'uso tipici delle unioni
- Unioni anonime e unioni all'interno di strutture

### Enumerazioni
- Definizione e dichiarazione di enumerazioni
- Assegnazione di valori espliciti agli enumeratori
- Utilizzo delle enumerazioni per migliorare la leggibilità del codice
- Enumerazioni come alternativa alle #define
- Limiti e caratteristiche delle enumerazioni in C

## Materiale Teorico

- [Introduzione alle Unioni](./teoria/introduzione_unioni.md)
- [Introduzione alle Enumerazioni](./teoria/introduzione_enumerazioni.md)
- [Casi d'Uso Avanzati](./teoria/casi_uso_avanzati.md)

## Esempi Pratici

In questa esercitazione troverete diversi esempi pratici:

1. `unioni_base.c` - Esempi base di definizione e utilizzo delle unioni
2. `enumerazioni_base.c` - Esempi base di definizione e utilizzo delle enumerazioni
3. `unioni_strutture.c` - Combinazione di unioni e strutture
4. `enum_applicazioni.c` - Applicazioni pratiche delle enumerazioni

## Best Practices

### Per le Unioni
- Utilizzare le unioni solo quando necessario per risparmiare memoria
- Tenere traccia del tipo di dato attualmente memorizzato nell'unione
- Evitare di accedere a un membro diverso da quello utilizzato per l'ultimo assegnamento
- Considerare l'uso di una struttura con un campo tipo e un'unione per creare tipi di dati varianti

### Per le Enumerazioni
- Utilizzare nomi significativi per gli enumeratori
- Preferire le enumerazioni alle #define per costanti correlate
- Essere consapevoli che gli enumeratori sono interi e possono essere utilizzati in espressioni aritmetiche
- Documentare il significato di ogni enumeratore

## Esercizi Proposti

1. Creare una struttura che utilizzi un'unione per rappresentare diversi tipi di dati (int, float, char*)
2. Implementare un sistema di gestione di forme geometriche utilizzando enumerazioni per i tipi di forma
3. Sviluppare un parser semplice che utilizzi unioni per gestire diversi tipi di token
4. Creare un programma che utilizzi enumerazioni per rappresentare i giorni della settimana e i mesi dell'anno

## Domande di Autovalutazione

1. Qual è la differenza principale tra una struttura e un'unione?
2. Come si può determinare quale membro di un'unione è stato utilizzato per l'ultimo assegnamento?
3. Perché le enumerazioni sono preferibili alle #define per definire costanti correlate?
4. Come si può assegnare valori specifici agli enumeratori?
5. Quali sono i limiti delle enumerazioni in C?

## Approfondimenti

Per approfondire ulteriormente questi concetti, consultate:

- K&R C Programming Language, Capitolo 6
- C: A Reference Manual, Sezioni sulle unioni ed enumerazioni
- Advanced C Programming by Example, Capitolo sui tipi di dati personalizzati

Proseguite con l'esercitazione [18 - Typedef e Tipi Definiti dall'Utente](../18_Typedef/) per apprendere come creare alias per i tipi e definire tipi personalizzati in C.