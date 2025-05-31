# Esercitazione 4: Input e Output

## Descrizione

Questa esercitazione si concentra sulle operazioni di input e output in C, con particolare attenzione alle funzioni della libreria standard come printf e scanf. Imparerai a formattare correttamente l'output e a gestire l'input da tastiera, competenze fondamentali per creare programmi interattivi.

## Obiettivi di apprendimento

- Comprendere le funzioni di input/output della libreria standard
- Padroneggiare la funzione printf per la visualizzazione dei dati
- Utilizzare la funzione scanf per l'acquisizione di input
- Applicare i specificatori di formato per diversi tipi di dati
- Gestire correttamente l'input/output di caratteri, stringhe e numeri

## Indice degli argomenti teorici

1. [Introduzione all'I/O in C](./teoria/01_Introduzione_IO.md)
   - Concetti di stream
   - File standard: stdin, stdout, stderr
   - Libreria stdio.h

2. [La funzione printf](./teoria/02_Funzione_Printf.md)
   - Sintassi e utilizzo
   - Specificatori di formato (%d, %f, %c, %s, ecc.)
   - Modificatori di formato
   - Esempi pratici

3. [La funzione scanf](./teoria/03_Funzione_Scanf.md)
   - Sintassi e utilizzo
   - Specificatori di formato
   - Gestione dell'input
   - Problemi comuni e soluzioni

4. [Formattazione avanzata dell'output](./teoria/04_Formattazione_Avanzata.md)
   - Controllo della larghezza e precisione
   - Allineamento del testo
   - Formattazione di numeri e valute
   - Caratteri di escape

## Esercitazione pratica

### Esercizio 4.1: Calcolatrice semplice

Scrivi un programma che chieda all'utente due numeri e un'operazione da eseguire (+, -, *, /), quindi mostri il risultato formattato correttamente.

```c
#include <stdio.h>

int main() {
    float num1, num2, risultato;
    char operazione;
    
    printf("Inserisci il primo numero: ");
    scanf("%f", &num1);
    
    printf("Inserisci il secondo numero: ");
    scanf("%f", &num2);
    
    printf("Inserisci l'operazione (+, -, *, /): ");
    scanf(" %c", &operazione);
    
    switch(operazione) {
        case '+':
            risultato = num1 + num2;
            break;
        case '-':
            risultato = num1 - num2;
            break;
        case '*':
            risultato = num1 * num2;
            break;
        case '/':
            if(num2 != 0)
                risultato = num1 / num2;
            else {
                printf("Errore: divisione per zero!\n");
                return 1;
            }
            break;
        default:
            printf("Operazione non valida!\n");
            return 1;
    }
    
    printf("%.2f %c %.2f = %.2f\n", num1, operazione, num2, risultato);
    return 0;
}
```

### Esercizio 4.2: Formattazione tabellare

Scrivi un programma che mostri una tabella di conversione da Celsius a Fahrenheit, formattata in modo che i numeri siano allineati correttamente.

```c
#include <stdio.h>

int main() {
    int celsius;
    float fahrenheit;
    
    // Intestazione della tabella
    printf("+--------+------------+\n");
    printf("| %-6s | %-10s |\n", "Celsius", "Fahrenheit");
    printf("+--------+------------+\n");
    
    // Generazione della tabella di conversione
    for(celsius = 0; celsius <= 100; celsius += 10) {
        fahrenheit = (celsius * 9.0 / 5.0) + 32.0;
        printf("| %6d | %10.2f |\n", celsius, fahrenheit);
    }
    
    // Piè di pagina della tabella
    printf("+--------+------------+\n");
    
    return 0;
}
```

Questo programma genera una tabella ben formattata che mostra la conversione da gradi Celsius a Fahrenheit, con temperature da 0°C a 100°C con incrementi di 10°C. La formattazione assicura che i numeri siano allineati correttamente nelle colonne.

## Domande di autovalutazione

1. Qual è la differenza principale tra printf e scanf?
2. Come si può leggere una stringa con spazi utilizzando scanf?
3. Quali sono i problemi più comuni nell'uso di scanf e come si possono evitare?
4. Come si può controllare la precisione dei numeri decimali in output?
5. Quali caratteri di escape sono disponibili in C e a cosa servono?

## Approfondimenti

- Esplora altre funzioni di I/O come getchar(), putchar(), gets(), puts()
- Studia come gestire l'input/output su file
- Approfondisci la gestione degli errori nelle operazioni di I/O

## Risorse aggiuntive

- Kernighan, B. W., & Ritchie, D. M. (1988). The C Programming Language (2nd ed.). Prentice Hall.
- Kochan, S. G. (2014). Programming in C (4th ed.). Addison-Wesley Professional.
- [Documentazione della libreria stdio.h](https://en.cppreference.com/w/c/io)