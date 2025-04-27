# Direttive e Macro del Preprocessore in C

## Introduzione al Preprocessore

Il preprocessore è uno strumento che elabora il codice sorgente prima della compilazione vera e propria. Non fa parte del compilatore C, ma è un passo separato nel processo di compilazione. Le direttive del preprocessore iniziano sempre con il simbolo `#` e non terminano con il punto e virgola.

## Direttive Principali

### La Direttiva #include

#### Sintassi e Funzionamento

```c
#include <nome_file>    // Per file di sistema
#include "nome_file"    // Per file locali
```

La direttiva `#include` inserisce il contenuto di un file nel punto in cui appare la direttiva stessa.

#### Esempi di Utilizzo

```c
#include <stdio.h>      // Include la libreria standard di input/output
#include "mio_header.h" // Include un file header locale
```

#### Best Practices

1. Utilizzare `<>` per le librerie standard e `""` per i file locali
2. Includere solo i file necessari per ridurre i tempi di compilazione
3. Organizzare le inclusioni in ordine logico (prima le librerie standard, poi quelle locali)

### La Direttiva #define

#### Sintassi e Funzionamento

```c
#define NOME valore
```

La direttiva `#define` crea una macro, che è un identificatore che viene sostituito con un valore o un'espressione durante la fase di preprocessore.

#### Esempi di Utilizzo

```c
#define PI 3.14159
#define QUADRATO(x) ((x) * (x))

int main() {
    double raggio = 5.0;
    double area = PI * QUADRATO(raggio);
    return 0;
}
```

In questo esempio, `PI` viene sostituito con `3.14159` e `QUADRATO(raggio)` viene sostituito con `((raggio) * (raggio))`.

#### Tipi di Macro

1. **Macro Oggetto**: Definiscono costanti simboliche
   ```c
   #define BUFFER_SIZE 1024
   #define VERSIONE "1.0.0"
   ```

2. **Macro Funzione**: Definiscono operazioni parametrizzate
   ```c
   #define MAX(a, b) ((a) > (b) ? (a) : (b))
   #define ABS(x) ((x) < 0 ? -(x) : (x))
   ```

#### Precauzioni con le Macro Funzione

```c
#define ERRATO(x) x * x
#define CORRETTO(x) ((x) * (x))

int main() {
    int a = ERRATO(2 + 3);    // Diventa 2 + 3 * 2 + 3 = 2 + 6 + 3 = 11
    int b = CORRETTO(2 + 3);  // Diventa ((2 + 3) * (2 + 3)) = 25
    return 0;
}
```

#### Best Practices

1. Utilizzare parentesi attorno ai parametri e all'intera espressione nelle macro funzione
2. Preferire funzioni inline alle macro quando possibile (C99 e successivi)
3. Utilizzare nomi in maiuscolo per le macro per distinguerle dalle variabili e funzioni
4. Evitare effetti collaterali nei parametri delle macro

### La Direttiva #undef

#### Sintassi e Funzionamento

```c
#undef NOME
```

La direttiva `#undef` rimuove una definizione di macro precedentemente creata con `#define`.

#### Esempi di Utilizzo

```c
#define DEBUG 1

// Codice con debug attivo

#undef DEBUG

// Codice senza debug
```

### Macro Predefinite

Il preprocessore C fornisce alcune macro predefinite che possono essere utili per il debug e la compilazione condizionale:

```c
#include <stdio.h>

int main() {
    printf("File: %s\n", __FILE__);
    printf("Linea: %d\n", __LINE__);
    printf("Data di compilazione: %s\n", __DATE__);
    printf("Ora di compilazione: %s\n", __TIME__);
    printf("Standard C: %ld\n", __STDC_VERSION__);
    return 0;
}
```

#### Macro Predefinite Comuni

| Macro | Descrizione |
|-------|-------------|
| `__FILE__` | Nome del file sorgente corrente |
| `__LINE__` | Numero di linea corrente nel file sorgente |
| `__DATE__` | Data di compilazione (formato "Mmm dd yyyy") |
| `__TIME__` | Ora di compilazione (formato "hh:mm:ss") |
| `__STDC__` | 1 se il compilatore è conforme allo standard C |
| `__STDC_VERSION__` | Versione dello standard C (es. 201710L per C17) |
| `__func__` | Nome della funzione corrente (C99 e successivi) |

## Esempi Pratici

### Definizione di Costanti

```c
#include <stdio.h>

#define PI 3.14159
#define GRAVITA 9.81
#define AUTORE "Mario Rossi"
#define VERSIONE_MAGGIORE 1
#define VERSIONE_MINORE 2
#define VERSIONE_COMPLETA VERSIONE_MAGGIORE.VERSIONE_MINORE

int main() {
    printf("Pi greco: %f\n", PI);
    printf("Accelerazione di gravità: %f m/s²\n", GRAVITA);
    printf("Autore: %s\n", AUTORE);
    printf("Versione: %d.%d\n", VERSIONE_MAGGIORE, VERSIONE_MINORE);
    return 0;
}
```

### Macro per Debug

```c
#include <stdio.h>

#define DEBUG 1

#if DEBUG
#define LOG(msg) printf("[DEBUG] %s:%d - %s\n", __FILE__, __LINE__, msg)
#else
#define LOG(msg) /* nulla */
#endif

int main() {
    LOG("Inizio programma");
    int x = 10;
    LOG("Variabile x inizializzata");
    x += 5;
    LOG("Operazione completata");
    return 0;
}
```

### Macro per Gestione Errori

```c
#include <stdio.h>
#include <stdlib.h>

#define GESTISCI_ERRORE(condizione, messaggio) \
    do { \
        if (condizione) { \
            fprintf(stderr, "Errore in %s, linea %d: %s\n", \
                    __FILE__, __LINE__, messaggio); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

int main() {
    FILE *file = fopen("file_inesistente.txt", "r");
    GESTISCI_ERRORE(file == NULL, "Impossibile aprire il file");
    
    // Il codice qui non verrà eseguito se c'è un errore
    fclose(file);
    return 0;
}
```

## Vantaggi e Svantaggi delle Macro

### Vantaggi

1. **Leggibilità**: Utilizzare nomi simbolici invece di valori letterali rende il codice più leggibile
2. **Manutenibilità**: Modificare un valore in un unico punto invece che in tutto il codice
3. **Efficienza**: Le macro vengono espanse inline, evitando il sovraccarico delle chiamate di funzione
4. **Flessibilità**: Possibilità di generare codice in base a condizioni di compilazione

### Svantaggi

1. **Debugging**: Le macro vengono espanse prima della compilazione, rendendo il debug più difficile
2. **Errori Nascosti**: Comportamenti inaspettati dovuti alla sostituzione testuale
3. **Nessun Controllo di Tipo**: Le macro non hanno controllo di tipo come le funzioni
4. **Espansione del Codice**: L'uso eccessivo di macro può aumentare la dimensione del codice compilato

## Conclusione

Le direttive del preprocessore e le macro sono strumenti potenti in C che permettono di manipolare il codice sorgente prima della compilazione. Utilizzate correttamente, possono migliorare la leggibilità, la manutenibilità e l'efficienza del codice. Tuttavia, è importante essere consapevoli dei loro limiti e potenziali problemi.

## Esercizi

1. Scrivi una macro `MIN` che restituisce il minimo tra due valori.
2. Crea una macro `SWAP` che scambia i valori di due variabili dello stesso tipo.
3. Implementa una macro `ALLOCA_ARRAY` che alloca dinamicamente un array e verifica se l'allocazione è riuscita.
4. Scrivi un programma che utilizza le macro predefinite per stampare informazioni sulla compilazione.
5. Crea una macro `ASSERT` che verifica una condizione e stampa un messaggio di errore se la condizione è falsa.

## Domande di Autovalutazione

1. Qual è la differenza tra `#include <file.h>` e `#include "file.h"`?
2. Perché è importante mettere le parentesi attorno ai parametri nelle macro funzione?
3. Cosa succede se si definisce una macro con lo stesso nome di una variabile?
4. Quali sono i vantaggi e gli svantaggi delle macro rispetto alle funzioni?
5. Come si può utilizzare `#undef` per evitare conflitti di nomi?
6. Quali sono le macro predefinite più utili per il debug?
7. Come funziona la sostituzione dei parametri nelle macro funzione?
8. Perché è consigliabile utilizzare il costrutto `do { ... } while (0)` nelle macro che contengono più istruzioni?