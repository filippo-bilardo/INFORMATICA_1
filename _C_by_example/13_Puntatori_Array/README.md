# Puntatori e Array

## Introduzione

Benvenuti all'esercitazione 13 dedicata alla relazione tra puntatori e array in C. In questa lezione, esploreremo come i puntatori e gli array siano strettamente correlati nel linguaggio C e come questa relazione possa essere sfruttata per creare codice più efficiente e flessibile.

## Argomenti Trattati

- Relazione fondamentale tra puntatori e array
- Aritmetica dei puntatori con gli array
- Accesso agli elementi di un array tramite puntatori
- Passaggio di array alle funzioni tramite puntatori
- Tecniche di ottimizzazione usando puntatori con array

## Materiale Teorico

- [Relazione tra Puntatori e Array](./teoria/relazione_puntatori_array.md)
- [Passaggio di Array alle Funzioni](./teoria/passaggio_array_funzioni.md)
- [Tecniche Avanzate](./teoria/tecniche_avanzate.md)

## Esempi Pratici

In questa esercitazione troverete diversi esempi pratici:

1. `array_puntatori_base.c` - Esempi base della relazione tra array e puntatori
2. `array_puntatori_funzioni.c` - Come passare array alle funzioni usando i puntatori
3. `array_multidimensionali_puntatori.c` - Gestione di array multidimensionali con i puntatori

## Best Practices

- Preferire la notazione puntatore quando si lavora con array di grandi dimensioni
- Utilizzare const per proteggere i dati quando si passano array a funzioni
- Verificare sempre i limiti degli array quando si utilizza l'aritmetica dei puntatori
- Documentare chiaramente l'uso dei puntatori agli array per migliorare la leggibilità

## Esercizi Proposti

1. Implementare una funzione che inverta l'ordine degli elementi di un array usando esclusivamente la notazione puntatore
2. Creare una funzione che concateni due array in un terzo array utilizzando i puntatori
3. Implementare una funzione di ricerca binaria in un array ordinato usando i puntatori

## Domande di Autovalutazione

1. Qual è la differenza principale tra un array e un puntatore in C?
2. Come si può accedere al terzo elemento di un array usando la notazione puntatore?
3. Perché è più efficiente passare un array a una funzione tramite puntatore?
4. Come si gestisce un array bidimensionale usando i puntatori?
5. Quali sono i rischi dell'aritmetica dei puntatori quando si lavora con gli array?

## Approfondimenti

Per approfondire ulteriormente questi concetti, consultate:

- K&R C Programming Language, Capitolo 5
- C: A Reference Manual, Sezione sui puntatori e array
- Advanced C Programming by Example, Capitolo sugli array e puntatori

Proseguite con l'esercitazione [14 - Puntatori e Stringhe](../14_Puntatori_Stringhe/) per apprendere come i puntatori possono essere utilizzati efficacemente con le stringhe in C.