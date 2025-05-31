# Introduzione all'I/O in C

## Concetti di stream

In C, l'input e l'output sono gestiti attraverso il concetto di **stream**. Uno stream è una sequenza di dati che fluisce da una sorgente a una destinazione. Questo concetto astratto permette di trattare in modo uniforme diverse fonti di dati, come la tastiera, il monitor, i file o le connessioni di rete.

Un programma C può leggere dati da uno stream di input o scrivere dati su uno stream di output. Questa astrazione consente di scrivere codice che funziona indipendentemente dalla sorgente o dalla destinazione effettiva dei dati.

## File standard: stdin, stdout, stderr

Quando un programma C viene avviato, il sistema operativo apre automaticamente tre stream standard:

1. **stdin** (Standard Input): è lo stream di input predefinito, generalmente associato alla tastiera. Le funzioni come `scanf()` e `getchar()` leggono dati da questo stream.

2. **stdout** (Standard Output): è lo stream di output predefinito, generalmente associato al monitor. Le funzioni come `printf()` e `putchar()` scrivono dati su questo stream.

3. **stderr** (Standard Error): è lo stream di output dedicato ai messaggi di errore, anch'esso generalmente associato al monitor. Viene utilizzato per separare i messaggi di errore dall'output normale del programma.

Questi stream sono rappresentati in C come puntatori a file di tipo `FILE*` e sono definiti nella libreria `stdio.h`:

```c
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;
```

La separazione tra stdout e stderr permette di reindirizzare l'output normale e i messaggi di errore in destinazioni diverse, una caratteristica particolarmente utile nei sistemi operativi Unix/Linux.

## Libreria stdio.h

La libreria standard `stdio.h` (Standard Input/Output Header) fornisce le funzioni e le definizioni necessarie per le operazioni di input/output in C. Questa libreria è parte dello standard ANSI C e quindi è disponibile in tutti gli ambienti di sviluppo C conformi allo standard.

Le principali categorie di funzioni fornite da `stdio.h` includono:

1. **Funzioni di input formattato**: come `scanf()`, `fscanf()`, `sscanf()`

2. **Funzioni di output formattato**: come `printf()`, `fprintf()`, `sprintf()`

3. **Funzioni di input/output a carattere**: come `getchar()`, `putchar()`, `fgetc()`, `fputc()`

4. **Funzioni di input/output a riga**: come `gets()` (deprecata per motivi di sicurezza), `fgets()`, `puts()`, `fputs()`

5. **Funzioni di gestione dei file**: come `fopen()`, `fclose()`, `fread()`, `fwrite()`, `fseek()`

6. **Funzioni di controllo degli errori**: come `ferror()`, `clearerr()`, `feof()`

Per utilizzare queste funzioni, è necessario includere la libreria all'inizio del programma:

```c
#include <stdio.h>
```

## Esempio di utilizzo base

Ecco un semplice esempio che mostra l'uso di base delle funzioni di input/output:

```c
#include <stdio.h>

int main() {
    int numero;
    char nome[50];
    
    // Output su stdout
    printf("Inserisci il tuo nome: ");
    
    // Input da stdin
    scanf("%s", nome);
    
    printf("Inserisci un numero: ");
    scanf("%d", &numero);
    
    // Output formattato
    printf("Ciao %s! Hai inserito il numero %d.\n", nome, numero);
    
    // Output su stderr
    if(numero < 0) {
        fprintf(stderr, "Attenzione: hai inserito un numero negativo!\n");
    }
    
    return 0;
}
```

Nelle prossime sezioni, esploreremo in dettaglio le funzioni `printf()` e `scanf()`, che sono le più utilizzate per l'input e l'output formattato in C.