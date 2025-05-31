# Il primo programma in C

Scrivere il primo programma in un nuovo linguaggio di programmazione è un passo fondamentale nel processo di apprendimento. In questa guida, esploreremo la struttura di un programma C, il classico esempio "Hello, World!" e il processo di compilazione ed esecuzione.

## Struttura di un programma C

Un programma C è composto da diversi elementi fondamentali:

### 1. Direttive del preprocessore

Le direttive del preprocessore iniziano con il simbolo `#` e vengono elaborate prima della compilazione vera e propria. La più comune è `#include`, che inserisce il contenuto di un file header nel programma.

```c
#include <stdio.h>  // Include la libreria standard di input/output
```

### 2. Funzione main()

Ogni programma C deve contenere una funzione chiamata `main()`. Questa è il punto di ingresso del programma, ovvero dove inizia l'esecuzione.

```c
int main() {
    // Corpo della funzione
    return 0;  // Valore di ritorno che indica esecuzione completata con successo
}
```

### 3. Dichiarazioni e istruzioni

All'interno della funzione `main()` e di altre funzioni, si trovano dichiarazioni di variabili e istruzioni che eseguono operazioni.

```c
int main() {
    int numero;  // Dichiarazione di una variabile
    numero = 42;  // Assegnazione di un valore
    printf("%d\n", numero);  // Istruzione per stampare il valore
    return 0;
}
```

### 4. Commenti

I commenti sono note nel codice che vengono ignorate dal compilatore. In C esistono due tipi di commenti:

```c
// Questo è un commento su una singola riga (stile C99)

/* Questo è un commento
   su più righe */
```

### 5. Funzioni

Oltre a `main()`, un programma C può contenere altre funzioni che eseguono compiti specifici.

```c
// Dichiarazione di una funzione
int somma(int a, int b) {
    return a + b;
}

int main() {
    int risultato = somma(5, 3);  // Chiamata della funzione
    printf("%d\n", risultato);
    return 0;
}
```

## Il programma "Hello, World!"

Il classico primo programma in qualsiasi linguaggio è "Hello, World!", che semplicemente stampa questa frase sullo schermo.

### Codice completo

```c
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
```

### Spiegazione riga per riga

1. `#include <stdio.h>`: Include la libreria standard di input/output, che contiene la funzione `printf()`.

2. `int main() {`: Definisce la funzione principale che restituisce un intero.

3. `printf("Hello, World!\n");`: Stampa la stringa "Hello, World!" seguita da un carattere di nuova riga (`\n`).

4. `return 0;`: Restituisce il valore 0 al sistema operativo, indicando che il programma è terminato con successo.

5. `}`: Chiude il blocco della funzione `main()`.

### Varianti

#### Versione con argomenti della riga di comando

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Hello, World!\n");
    return 0;
}
```

#### Versione senza valore di ritorno esplicito

```c
#include <stdio.h>

void main() {
    printf("Hello, World!\n");
}
```

Nota: Questa variante non è conforme allo standard C, ma è accettata da alcuni compilatori.

## Processo di compilazione ed esecuzione

Per trasformare il codice sorgente in un programma eseguibile, è necessario seguire un processo di compilazione.

### Passi della compilazione

1. **Scrittura del codice**: Creare un file con estensione `.c` (es. `hello.c`) contenente il codice sorgente.

2. **Compilazione**: Utilizzare un compilatore C per tradurre il codice sorgente in un file eseguibile.

3. **Esecuzione**: Eseguire il programma compilato.

### Esempio pratico

#### In ambiente Unix/Linux/macOS

```bash
# Scrittura del codice (usando un editor di testo)
vi hello.c  # o nano, emacs, ecc.

# Compilazione
gcc hello.c -o hello

# Esecuzione
./hello
```

#### In ambiente Windows con GCC (MinGW)

```bash
# Compilazione
gcc hello.c -o hello.exe

# Esecuzione
hello.exe
```

#### In ambiente Windows con Visual Studio

1. Creare un nuovo progetto C/C++
2. Aggiungere un nuovo file sorgente C
3. Scrivere il codice
4. Premere F5 per compilare ed eseguire

### Errori comuni

#### Errori di sintassi

```c
#include <stdio.h>

int main() {
    printf("Hello, World!\n")  // Manca il punto e virgola
    return 0;
}
```

Messaggio di errore tipico:
```
hello.c:4:31: error: expected ';' before 'return'
```

#### Errori di linking

```c
#include <stdio.h>

int main() {
    printff("Hello, World!\n");  // Nome di funzione errato
    return 0;
}
```

Messaggio di errore tipico:
```
undefined reference to 'printff'
```

#### Errori logici

```c
#include <stdio.h>

int main() {
    printf("Helo, World!\n");  // Errore di ortografia nella stringa
    return 0;
}
```

Questo codice compila ed esegue, ma produce un output non corretto.

## Suggerimenti per il primo programma

1. **Inizia semplice**: Il programma "Hello, World!" è perfetto per iniziare.

2. **Comprendi ogni riga**: Assicurati di capire il significato di ogni riga di codice.

3. **Esperimenta**: Modifica il programma per stampare messaggi diversi o più messaggi.

4. **Usa i commenti**: Aggiungi commenti per spiegare cosa fa il codice.

5. **Impara dagli errori**: Gli errori di compilazione sono utili per imparare la sintassi corretta.

## Domande di autovalutazione

1. Quali sono gli elementi fondamentali di un programma C?

2. Perché la funzione `main()` è speciale in un programma C?

3. Qual è lo scopo della direttiva `#include <stdio.h>`?

4. Cosa significa il valore di ritorno `0` nella funzione `main()`?

5. Descrivi i passi necessari per compilare ed eseguire un programma C.

## Esercizi pratici

1. Scrivi un programma "Hello, World!" e compilalo con successo.

2. Modifica il programma per stampare il tuo nome su una riga e la tua età su un'altra riga.

3. Crea un programma che stampi un semplice disegno ASCII, come una faccia sorridente o una casa.

4. Scrivi un programma che stampi una tabella semplice con intestazioni di colonna.

5. Modifica il programma "Hello, World!" per introdurre deliberatamente diversi tipi di errori (sintassi, linking, logici) e osserva i messaggi di errore generati dal compilatore.

---

[Indice dell'esercitazione](../README.md) | [Argomento precedente](./03_Ambiente_di_Sviluppo.md) | [Prossima esercitazione](../../02_Variabili_e_Tipi/README.md)