# Compilazione Separata e Linking

La compilazione separata e il linking sono concetti fondamentali nella programmazione modulare in C, che permettono di suddividere un programma in più file sorgente, compilarli indipendentemente e poi collegarli insieme per creare un eseguibile.

## Il Processo di Compilazione in C

Il processo di compilazione in C si compone di diverse fasi:

1. **Preprocessore**: Elabora le direttive come `#include` e `#define`
2. **Compilazione**: Traduce il codice C in codice oggetto
3. **Linking**: Collega i file oggetto e le librerie per creare l'eseguibile

### Preprocessore

Il preprocessore elabora le direttive come:
- `#include`: Inserisce il contenuto di altri file
- `#define`: Definisce macro e costanti
- `#ifdef`, `#ifndef`, `#endif`: Controlla la compilazione condizionale

### Compilazione

Il compilatore traduce il codice C in codice oggetto (file `.o` o `.obj`). Ogni file sorgente (`.c`) viene compilato separatamente, generando un file oggetto corrispondente.

### Linking

Il linker prende i file oggetto generati e le librerie necessarie e li collega insieme per creare un eseguibile. Durante questa fase:
- Risolve i riferimenti a simboli esterni (funzioni e variabili definite in altri moduli)
- Combina le sezioni di codice e dati
- Gestisce le librerie statiche e dinamiche

## Vantaggi della Compilazione Separata

1. **Riduzione dei Tempi di Compilazione**: Solo i file modificati devono essere ricompilati
2. **Sviluppo Parallelo**: Diversi sviluppatori possono lavorare su moduli diversi contemporaneamente
3. **Riutilizzo del Codice**: I moduli compilati possono essere riutilizzati in progetti diversi
4. **Gestione della Complessità**: Suddividere un programma grande in parti più piccole e gestibili

## Esempio Pratico

Consideriamo un semplice progetto con tre file:

### matematica.h

```c
#ifndef MATEMATICA_H
#define MATEMATICA_H

int somma(int a, int b);
int sottrazione(int a, int b);

#endif // MATEMATICA_H
```

### matematica.c

```c
#include "matematica.h"

int somma(int a, int b) {
    return a + b;
}

int sottrazione(int a, int b) {
    return a - b;
}
```

### main.c

```c
#include <stdio.h>
#include "matematica.h"

int main() {
    int a = 10, b = 5;
    
    printf("Somma: %d\n", somma(a, b));
    printf("Sottrazione: %d\n", sottrazione(a, b));
    
    return 0;
}
```

## Processo di Compilazione e Linking

### 1. Compilazione Separata

Compiliamo separatamente i file sorgente per generare i file oggetto:

```bash
# Compila matematica.c in matematica.o
gcc -c matematica.c -o matematica.o

# Compila main.c in main.o
gcc -c main.c -o main.o
```

L'opzione `-c` indica al compilatore di generare solo il file oggetto senza procedere al linking.

### 2. Linking

Colleghiamo i file oggetto per creare l'eseguibile:

```bash
gcc matematica.o main.o -o programma
```

### 3. Esecuzione

```bash
./programma
```

Output:
```
Somma: 15
Sottrazione: 5
```

## Gestione delle Dipendenze con Make

Per progetti più grandi, è comune utilizzare strumenti come `make` per automatizzare il processo di compilazione e gestire le dipendenze. Un semplice `Makefile` per l'esempio precedente potrebbe essere:

```makefile
CC = gcc
CFLAGS = -Wall -Wextra

programma: main.o matematica.o
	$(CC) $(CFLAGS) main.o matematica.o -o programma

main.o: main.c matematica.h
	$(CC) $(CFLAGS) -c main.c

matematica.o: matematica.c matematica.h
	$(CC) $(CFLAGS) -c matematica.c

clean:
	rm -f *.o programma
```

Con questo Makefile, è possibile compilare il progetto semplicemente eseguendo il comando `make`. Make ricompilerà automaticamente solo i file che sono stati modificati o le cui dipendenze sono cambiate.

## Errori Comuni nel Linking

### 1. Simboli Non Definiti

Se si tenta di utilizzare una funzione o una variabile che è dichiarata ma non definita, il linker genererà un errore di "simbolo non definito".

```
undefined reference to 'funzione_mancante'
```

### 2. Simboli Duplicati

Se la stessa funzione o variabile è definita in più file, il linker genererà un errore di "simbolo duplicato".

```
multiple definition of 'funzione_duplicata'
```

### 3. Librerie Mancanti

Se il programma utilizza funzioni da librerie esterne che non sono state specificate durante il linking, si otterrà un errore di simbolo non definito.

## Variabili Esterne e Linkage

In C, le variabili possono avere diversi tipi di linkage:

### 1. Linkage Esterno

Le variabili globali hanno linkage esterno per default, il che significa che sono accessibili da altri file.

```c
// In file1.c
int variabile_globale = 10; // Linkage esterno
```

```c
// In file2.c
extern int variabile_globale; // Dichiarazione di una variabile esterna
```

### 2. Linkage Interno

Le variabili globali dichiarate con `static` hanno linkage interno, il che significa che sono accessibili solo all'interno del file in cui sono definite.

```c
// In file1.c
static int variabile_interna = 20; // Linkage interno
```

### 3. Nessun Linkage

Le variabili locali non hanno linkage, il che significa che sono accessibili solo all'interno del blocco in cui sono definite.

```c
void funzione() {
    int variabile_locale = 30; // Nessun linkage
}
```

## Conclusione

La compilazione separata e il linking sono concetti fondamentali nella programmazione modulare in C. Permettono di suddividere un programma in moduli indipendenti, compilarli separatamente e poi collegarli insieme per creare un eseguibile. Questo approccio offre numerosi vantaggi in termini di gestione della complessità, riutilizzo del codice e tempi di compilazione.

Comprendere il processo di compilazione e linking è essenziale per sviluppare progetti C di grandi dimensioni e per risolvere efficacemente gli errori che possono verificarsi durante queste fasi.