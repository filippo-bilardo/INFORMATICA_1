# Esercitazione 2: Variabili e Tipi di Dati in C

## Descrizione

Questa esercitazione introduce i concetti fondamentali di variabili e tipi di dati in C. Imparerai a dichiarare variabili, utilizzare diversi tipi di dati, comprendere il concetto di costanti e come effettuare conversioni tra tipi diversi.

## Obiettivi di apprendimento

- Comprendere il concetto di variabile e come dichiararla in C
- Conoscere i tipi di dati fondamentali del linguaggio C
- Utilizzare correttamente le costanti
- Effettuare operazioni di casting e conversione tra tipi
- Comprendere i limiti e le caratteristiche dei diversi tipi di dati

## Indice degli argomenti teorici

1. [Variabili in C](./teoria/01_Variabili.md)
   - Dichiarazione e inizializzazione
   - Regole per i nomi delle variabili
   - Scope e durata delle variabili

2. [Tipi di dati fondamentali](./teoria/02_Tipi_di_Dati.md)
   - Tipi interi (char, int, short, long)
   - Tipi in virgola mobile (float, double)
   - Modificatori di tipo (signed, unsigned)
   - Dimensioni e limiti dei tipi

3. [Costanti e letterali](./teoria/03_Costanti.md)
   - Definizione di costanti con #define
   - Costanti con const
   - Letterali numerici e di carattere
   - Sequenze di escape

4. [Conversioni di tipo](./teoria/04_Conversioni.md)
   - Conversioni implicite
   - Casting esplicito
   - Promozione e demozione di tipo
   - Potenziali problemi nelle conversioni

## Esercitazione pratica

### Esercizio 2.1: Dichiarazione e inizializzazione di variabili

Scrivi un programma che dichiari e inizializzi variabili di diversi tipi (int, float, char, double) e ne stampi i valori.

```c
#include <stdio.h>

int main() {
    int numero = 42;
    float decimale = 3.14f;
    char carattere = 'A';
    double precisione = 2.71828;
    
    printf("Intero: %d\n", numero);
    printf("Float: %f\n", decimale);
    printf("Carattere: %c\n", carattere);
    printf("Double: %lf\n", precisione);
    
    return 0;
}
```

### Esercizio 2.2: Limiti dei tipi di dati

Scrivi un programma che utilizzi la libreria `<limits.h>` per stampare i valori minimi e massimi dei principali tipi interi.

### Esercizio 2.3: Conversioni di tipo

Crea un programma che dimostri diverse conversioni di tipo, sia implicite che esplicite, e mostri i risultati.

## Risorse aggiuntive

- [C Data Types](https://en.wikipedia.org/wiki/C_data_types) su Wikipedia
- [C Programming/Variables](https://en.wikibooks.org/wiki/C_Programming/Variables) su Wikibooks
- [Type Conversion in C](https://www.geeksforgeeks.org/type-conversion-in-c/) su GeeksforGeeks

---

[Indice del corso](../README.md) | [Esercitazione precedente](../01_Introduzione/README.md) | [Prossima esercitazione](../03_Operatori/README.md)