# Gestione dell'input e dell'output in C

La gestione dell'input e dell'output (I/O) è fondamentale in qualsiasi linguaggio di programmazione. In C, l'I/O è gestito principalmente attraverso la libreria standard `stdio.h` (standard input/output), che fornisce funzioni per leggere dati dall'input (tipicamente la tastiera) e scrivere dati sull'output (tipicamente lo schermo).

## Input e output standard

In C, ci sono tre stream standard predefiniti:

1. **stdin** (standard input): utilizzato per l'input, di solito associato alla tastiera
2. **stdout** (standard output): utilizzato per l'output normale, di solito associato allo schermo
3. **stderr** (standard error): utilizzato per i messaggi di errore, di solito associato allo schermo

## Funzioni di output

### `printf()`

La funzione `printf()` è utilizzata per stampare dati formattati sullo standard output. La sua sintassi è:

```c
int printf(const char *format, ...);
```

Dove `format` è una stringa di formato che può contenere testo normale e specificatori di formato che iniziano con `%`.

#### Specificatori di formato comuni

| Specificatore | Tipo di dato |
|--------------|-------------|
| `%d` o `%i` | Intero con segno |
| `%u` | Intero senza segno |
| `%f` | Floating-point (float o double) |
| `%e` o `%E` | Notazione scientifica |
| `%g` o `%G` | Usa `%f` o `%e` a seconda di quale è più breve |
| `%c` | Carattere |
| `%s` | Stringa di caratteri |
| `%p` | Puntatore |
| `%x` o `%X` | Intero in esadecimale |
| `%o` | Intero in ottale |
| `%%` | Stampa il carattere % |

#### Modificatori di formato

I specificatori di formato possono essere modificati per controllare la larghezza, la precisione e l'allineamento:

- `%5d`: stampa un intero con larghezza minima di 5 caratteri (allineato a destra)
- `%-5d`: stampa un intero con larghezza minima di 5 caratteri (allineato a sinistra)
- `%.2f`: stampa un float con 2 cifre decimali
- `%10.2f`: stampa un float con larghezza minima di 10 caratteri e 2 cifre decimali

#### Esempi di `printf()`

```c
#include <stdio.h>

int main() {
    int intero = 42;
    float decimale = 3.14159;
    char carattere = 'A';
    char stringa[] = "Hello, World!";
    
    // Stampa di base
    printf("Intero: %d\n", intero);  // Stampa: Intero: 42
    printf("Decimale: %f\n", decimale);  // Stampa: Decimale: 3.141590
    printf("Carattere: %c\n", carattere);  // Stampa: Carattere: A
    printf("Stringa: %s\n", stringa);  // Stampa: Stringa: Hello, World!
    
    // Formattazione avanzata
    printf("Decimale con 2 cifre: %.2f\n", decimale);  // Stampa: Decimale con 2 cifre: 3.14
    printf("Intero con padding: %5d\n", intero);  // Stampa: Intero con padding:    42
    printf("Intero allineato a sinistra: %-5d\n", intero);  // Stampa: Intero allineato a sinistra: 42   
    
    // Stampa di più valori
    printf("Intero: %d, Decimale: %.2f, Carattere: %c\n", intero, decimale, carattere);
    
    return 0;
}
```

### `putchar()`

La funzione `putchar()` è utilizzata per scrivere un singolo carattere sullo standard output:

```c
int putchar(int c);
```

#### Esempio di `putchar()`

```c
#include <stdio.h>

int main() {
    char c = 'A';
    putchar(c);  // Stampa: A
    putchar('\n');  // Stampa una nuova riga
    
    // Stampa l'alfabeto
    for (char lettera = 'A'; lettera <= 'Z'; lettera++) {
        putchar(lettera);
    }
    putchar('\n');
    
    return 0;
}
```

### `puts()`

La funzione `puts()` è utilizzata per scrivere una stringa sullo standard output, seguita da una nuova riga:

```c
int puts(const char *str);
```

#### Esempio di `puts()`

```c
#include <stdio.h>

int main() {
    char stringa[] = "Hello, World!";
    puts(stringa);  // Stampa: Hello, World! seguito da una nuova riga
    
    // Equivalente a:
    printf("%s\n", stringa);
    
    return 0;
}
```

## Funzioni di input

### `scanf()`

La funzione `scanf()` è utilizzata per leggere dati formattati dallo standard input. La sua sintassi è:

```c
int scanf(const char *format, ...);
```

Dove `format` è una stringa di formato simile a quella di `printf()`, e gli argomenti successivi sono puntatori alle variabili in cui memorizzare i dati letti.

#### Esempi di `scanf()`

```c
#include <stdio.h>

int main() {
    int intero;
    float decimale;
    char carattere;
    char stringa[50];  // Array di caratteri per memorizzare una stringa
    
    // Lettura di un intero
    printf("Inserisci un numero intero: ");
    scanf("%d", &intero);  // Nota l'operatore & per ottenere l'indirizzo della variabile
    
    // Lettura di un float
    printf("Inserisci un numero decimale: ");
    scanf("%f", &decimale);
    
    // Lettura di un carattere
    printf("Inserisci un carattere: ");
    scanf(" %c", &carattere);  // Nota lo spazio prima di %c per ignorare eventuali whitespace
    
    // Lettura di una stringa
    printf("Inserisci una stringa: ");
    scanf("%s", stringa);  // Nota: per gli array non serve &
    
    // Stampa dei valori letti
    printf("\nHai inserito:\n");
    printf("Intero: %d\n", intero);
    printf("Decimale: %f\n", decimale);
    printf("Carattere: %c\n", carattere);
    printf("Stringa: %s\n", stringa);
    
    return 0;
}
```

#### Problemi comuni con `scanf()`

1. **Lettura di stringhe con spazi**: `scanf("%s", stringa)` legge solo fino al primo spazio. Per leggere una riga intera, usare `fgets()`.
2. **Buffer non svuotato**: dopo la lettura di numeri, il carattere newline (`\n`) rimane nel buffer, influenzando le successive letture di caratteri.
3. **Mancanza del controllo del valore di ritorno**: `scanf()` restituisce il numero di elementi letti con successo, che dovrebbe essere controllato.

### `getchar()`

La funzione `getchar()` è utilizzata per leggere un singolo carattere dallo standard input:

```c
int getchar(void);
```

#### Esempio di `getchar()`

```c
#include <stdio.h>

int main() {
    char c;
    
    printf("Inserisci un carattere: ");
    c = getchar();
    
    printf("Hai inserito: %c\n", c);
    
    // Lettura di una sequenza di caratteri fino a newline
    printf("Inserisci una sequenza di caratteri (termina con Invio): ");
    while ((c = getchar()) != '\n') {
        putchar(c);
    }
    
    return 0;
}
```

### `fgets()`

La funzione `fgets()` è utilizzata per leggere una riga di testo da uno stream (incluso lo standard input):

```c
char *fgets(char *str, int n, FILE *stream);
```

Dove `str` è il buffer in cui memorizzare la stringa, `n` è la dimensione massima del buffer, e `stream` è lo stream da cui leggere (ad esempio, `stdin` per lo standard input).

#### Esempio di `fgets()`

```c
#include <stdio.h>

int main() {
    char stringa[100];
    
    printf("Inserisci una riga di testo: ");
    fgets(stringa, sizeof(stringa), stdin);
    
    printf("Hai inserito: %s", stringa);  // Nota: fgets include il carattere newline
    
    return 0;
}
```

## Formattazione avanzata

### Escape sequences

Le escape sequences sono sequenze di caratteri che iniziano con il carattere backslash (`\`) e rappresentano caratteri speciali:

| Sequenza | Significato |
|----------|-------------|
| `\n` | Nuova riga |
| `\t` | Tabulazione orizzontale |
| `\r` | Ritorno a capo |
| `\\` | Backslash |
| `\'` | Apostrofo |
| `\"` | Virgolette |
| `\0` | Carattere nullo (terminatore di stringa) |

### Colori e formattazione ANSI

È possibile utilizzare le sequenze di escape ANSI per aggiungere colori e formattazione al testo nella console (supportato dalla maggior parte dei terminali moderni):

```c
#include <stdio.h>

int main() {
    // Testo colorato
    printf("\033[31mQuesto testo è rosso\033[0m\n");  // Rosso
    printf("\033[32mQuesto testo è verde\033[0m\n");  // Verde
    printf("\033[34mQuesto testo è blu\033[0m\n");    // Blu
    
    // Formattazione
    printf("\033[1mQuesto testo è in grassetto\033[0m\n");  // Grassetto
    printf("\033[4mQuesto testo è sottolineato\033[0m\n");  // Sottolineato
    
    // Combinazione di colori e formattazione
    printf("\033[1;33mQuesto testo è in grassetto e giallo\033[0m\n");  // Grassetto e giallo
    
    return 0;
}
```

## I/O su file

Oltre all'I/O standard, C permette di leggere e scrivere su file utilizzando funzioni come `fopen()`, `fprintf()`, `fscanf()`, `fread()`, `fwrite()` e `fclose()`.

### Esempio di I/O su file

```c
#include <stdio.h>

int main() {
    FILE *file;
    char nome[50];
    int eta;
    
    // Apertura del file in modalità scrittura
    file = fopen("dati.txt", "w");
    if (file == NULL) {
        printf("Errore nell'apertura del file\n");
        return 1;
    }
    
    // Scrittura su file
    fprintf(file, "Mario Rossi 30\n");
    fprintf(file, "Anna Bianchi 25\n");
    
    // Chiusura del file
    fclose(file);
    
    // Apertura del file in modalità lettura
    file = fopen("dati.txt", "r");
    if (file == NULL) {
        printf("Errore nell'apertura del file\n");
        return 1;
    }
    
    // Lettura dal file
    printf("Contenuto del file:\n");
    while (fscanf(file, "%s %s %d", nome, &nome[strlen(nome)], &eta) == 3) {
        printf("Nome: %s %s, Età: %d\n", nome, &nome[strlen(nome)], eta);
    }
    
    // Chiusura del file
    fclose(file);
    
    return 0;
}
```

## Conclusione

La gestione dell'input e dell'output è un aspetto fondamentale della programmazione in C. Le funzioni della libreria standard `stdio.h` offrono un'ampia gamma di strumenti per leggere dati dall'input e scrivere dati sull'output, sia per l'interazione con l'utente che per la manipolazione di file.

È importante comprendere le caratteristiche e le limitazioni di ciascuna funzione di I/O per scegliere quella più adatta alle proprie esigenze e per evitare errori comuni come buffer overflow o letture incomplete.

La padronanza delle funzioni di I/O in C è essenziale per sviluppare programmi interattivi e per gestire efficacemente i dati in ingresso e in uscita.