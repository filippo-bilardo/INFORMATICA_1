# Funzioni di libreria in C

Le funzioni di libreria sono componenti predefiniti del linguaggio C che forniscono funzionalità comuni e riutilizzabili. Queste funzioni sono organizzate in diverse librerie standard e possono essere utilizzate nei programmi includendo gli appropriati file header.

## Libreria standard del C

La libreria standard del C (libc) è una collezione di funzioni, costanti e tipi di dati che forniscono funzionalità di base come input/output, manipolazione di stringhe, operazioni matematiche, gestione della memoria e molto altro.

## Header file

Gli header file sono file con estensione `.h` che contengono dichiarazioni di funzioni, definizioni di costanti e tipi di dati. Per utilizzare le funzioni di una libreria, è necessario includere il relativo header file nel programma utilizzando la direttiva `#include`.

### Sintassi per includere gli header file

```c
// Per header file standard (della libreria C)
#include <nome_header.h>

// Per header file personalizzati o locali
#include "nome_header.h"
```

## Principali header file della libreria standard

### 1. `<stdio.h>` - Input/Output standard

Contiene funzioni per operazioni di input/output come `printf()`, `scanf()`, `fopen()`, `fclose()`, `fread()`, `fwrite()`, ecc.

```c
#include <stdio.h>

int main() {
    printf("Hello, World!\n");  // Output su console
    
    FILE *file = fopen("esempio.txt", "w");  // Apertura file in scrittura
    if (file != NULL) {
        fprintf(file, "Testo scritto nel file\n");  // Scrittura su file
        fclose(file);  // Chiusura file
    }
    
    return 0;
}
```

### 2. `<stdlib.h>` - Utilità generali

Contiene funzioni per allocazione di memoria, conversione di stringhe, generazione di numeri casuali, ordinamento e ricerca.

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Allocazione dinamica di memoria
    int *array = (int *)malloc(5 * sizeof(int));
    if (array != NULL) {
        for (int i = 0; i < 5; i++) {
            array[i] = i * 10;
            printf("%d ", array[i]);
        }
        printf("\n");
        free(array);  // Liberazione della memoria allocata
    }
    
    // Conversione di stringa in numero
    char numero_str[] = "123";
    int numero = atoi(numero_str);
    printf("Stringa convertita in intero: %d\n", numero);
    
    // Generazione di numeri casuali
    srand(time(NULL));  // Inizializzazione del generatore
    for (int i = 0; i < 5; i++) {
        printf("%d ", rand() % 100);  // Numeri casuali tra 0 e 99
    }
    printf("\n");
    
    return 0;
}
```

### 3. `<string.h>` - Manipolazione di stringhe

Contiene funzioni per operazioni su stringhe come copia, concatenazione, confronto, ricerca.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str1[50] = "Hello";
    char str2[] = "World";
    
    // Lunghezza di una stringa
    printf("Lunghezza di str1: %lu\n", strlen(str1));
    
    // Concatenazione di stringhe
    strcat(str1, " ");
    strcat(str1, str2);
    printf("Dopo concatenazione: %s\n", str1);
    
    // Copia di stringhe
    char str3[50];
    strcpy(str3, str1);
    printf("Stringa copiata: %s\n", str3);
    
    // Confronto di stringhe
    if (strcmp(str1, str3) == 0) {
        printf("str1 e str3 sono uguali\n");
    }
    
    // Ricerca di sottostringhe
    char *ptr = strstr(str1, "World");
    if (ptr != NULL) {
        printf("Sottostringa trovata alla posizione: %ld\n", ptr - str1);
    }
    
    return 0;
}
```

### 4. `<math.h>` - Funzioni matematiche

Contiene funzioni per operazioni matematiche come radice quadrata, potenze, funzioni trigonometriche, logaritmi.

```c
#include <stdio.h>
#include <math.h>

int main() {
    double x = 16.0;
    double y = 2.0;
    
    // Radice quadrata
    printf("sqrt(%.1f) = %.1f\n", x, sqrt(x));
    
    // Potenza
    printf("pow(%.1f, %.1f) = %.1f\n", x, y, pow(x, y));
    
    // Funzioni trigonometriche (argomenti in radianti)
    double angolo = M_PI / 4.0;  // 45 gradi in radianti
    printf("sin(%.2f) = %.2f\n", angolo, sin(angolo));
    printf("cos(%.2f) = %.2f\n", angolo, cos(angolo));
    printf("tan(%.2f) = %.2f\n", angolo, tan(angolo));
    
    // Logaritmi
    printf("log(%.1f) = %.2f\n", x, log(x));    // Logaritmo naturale (base e)
    printf("log10(%.1f) = %.2f\n", x, log10(x));  // Logaritmo in base 10
    
    // Valore assoluto
    double z = -5.7;
    printf("fabs(%.1f) = %.1f\n", z, fabs(z));
    
    return 0;
}
```

**Nota**: Per utilizzare le funzioni matematiche, potrebbe essere necessario collegare la libreria matematica durante la compilazione con l'opzione `-lm`:

```
gcc programma.c -o programma -lm
```

### 5. `<time.h>` - Funzioni per la gestione del tempo

Contiene funzioni per ottenere e manipolare data e ora.

```c
#include <stdio.h>
#include <time.h>

int main() {
    // Ottiene il tempo corrente (secondi da Epoch: 1 gennaio 1970)
    time_t tempo_corrente = time(NULL);
    printf("Secondi da Epoch: %ld\n", tempo_corrente);
    
    // Converte il tempo in una struttura tm (tempo locale)
    struct tm *tempo_locale = localtime(&tempo_corrente);
    
    // Formatta e stampa la data e l'ora
    char buffer[80];
    strftime(buffer, 80, "%d/%m/%Y %H:%M:%S", tempo_locale);
    printf("Data e ora corrente: %s\n", buffer);
    
    // Componenti individuali della data e ora
    printf("Anno: %d\n", tempo_locale->tm_year + 1900);  // Anno (dal 1900)
    printf("Mese: %d\n", tempo_locale->tm_mon + 1);      // Mese (0-11)
    printf("Giorno: %d\n", tempo_locale->tm_mday);       // Giorno (1-31)
    printf("Ora: %d\n", tempo_locale->tm_hour);          // Ora (0-23)
    printf("Minuti: %d\n", tempo_locale->tm_min);        // Minuti (0-59)
    printf("Secondi: %d\n", tempo_locale->tm_sec);       // Secondi (0-59)
    
    return 0;
}
```

### 6. `<ctype.h>` - Classificazione e manipolazione di caratteri

Contiene funzioni per verificare e manipolare singoli caratteri.

```c
#include <stdio.h>
#include <ctype.h>

int main() {
    char c = 'A';
    
    // Verifica del tipo di carattere
    printf("'%c' è una lettera? %s\n", c, isalpha(c) ? "Sì" : "No");
    printf("'%c' è una cifra? %s\n", c, isdigit(c) ? "Sì" : "No");
    printf("'%c' è alfanumerico? %s\n", c, isalnum(c) ? "Sì" : "No");
    printf("'%c' è uno spazio? %s\n", c, isspace(c) ? "Sì" : "No");
    
    // Conversione di caratteri
    printf("'%c' in minuscolo: '%c'\n", c, tolower(c));
    
    c = 'b';
    printf("'%c' in maiuscolo: '%c'\n", c, toupper(c));
    
    return 0;
}
```

### 7. `<stdarg.h>` - Gestione di argomenti variabili

Contiene macro per lavorare con funzioni che accettano un numero variabile di argomenti.

```c
#include <stdio.h>
#include <stdarg.h>

// Funzione con numero variabile di argomenti
double media(int count, ...) {
    va_list args;
    double sum = 0.0;
    
    va_start(args, count);  // Inizializza la lista di argomenti
    
    for (int i = 0; i < count; i++) {
        sum += va_arg(args, double);  // Estrae il prossimo argomento come double
    }
    
    va_end(args);  // Pulisce la lista di argomenti
    
    return (count > 0) ? (sum / count) : 0;
}

int main() {
    printf("Media di 2.5, 3.5, 4.5: %.2f\n", media(3, 2.5, 3.5, 4.5));
    printf("Media di 1.0, 2.0, 3.0, 4.0, 5.0: %.2f\n", media(5, 1.0, 2.0, 3.0, 4.0, 5.0));
    
    return 0;
}
```

### 8. `<assert.h>` - Asserzioni per il debugging

Contiene la macro `assert()` che verifica una condizione e termina il programma se la condizione è falsa.

```c
#include <stdio.h>
#include <assert.h>

int dividi(int a, int b) {
    // Verifica che il divisore non sia zero
    assert(b != 0 && "Divisione per zero!");
    return a / b;
}

int main() {
    printf("10 / 2 = %d\n", dividi(10, 2));
    
    // Questa chiamata causerà un errore di asserzione
    // printf("10 / 0 = %d\n", dividi(10, 0));
    
    return 0;
}
```

**Nota**: Le asserzioni sono generalmente utilizzate durante lo sviluppo e il debugging. In una build di rilascio, possono essere disabilitate definendo la macro `NDEBUG` prima di includere `<assert.h>`.

## Creazione di librerie personalizzate

Oltre a utilizzare le librerie standard, è possibile creare librerie personalizzate per organizzare e riutilizzare il proprio codice.

### Creazione di un header file personalizzato

File: `matematica.h`

```c
#ifndef MATEMATICA_H
#define MATEMATICA_H

// Dichiarazioni di funzioni
int somma(int a, int b);
int sottrazione(int a, int b);
int moltiplicazione(int a, int b);
float divisione(int a, int b);

#endif // MATEMATICA_H
```

### Implementazione delle funzioni

File: `matematica.c`

```c
#include "matematica.h"

int somma(int a, int b) {
    return a + b;
}

int sottrazione(int a, int b) {
    return a - b;
}

int moltiplicazione(int a, int b) {
    return a * b;
}

float divisione(int a, int b) {
    if (b != 0) {
        return (float)a / b;
    } else {
        return 0;  // Gestione dell'errore (divisione per zero)
    }
}
```

### Utilizzo della libreria personalizzata

File: `main.c`

```c
#include <stdio.h>
#include "matematica.h"

int main() {
    int x = 10, y = 5;
    
    printf("%d + %d = %d\n", x, y, somma(x, y));
    printf("%d - %d = %d\n", x, y, sottrazione(x, y));
    printf("%d * %d = %d\n", x, y, moltiplicazione(x, y));
    printf("%d / %d = %.2f\n", x, y, divisione(x, y));
    
    return 0;
}
```

### Compilazione di un progetto con più file

```
gcc -c matematica.c -o matematica.o
gcc -c main.c -o main.o
gcc matematica.o main.o -o programma
```

## Guardie di inclusione

Le guardie di inclusione (include guards) sono un meccanismo per evitare che un header file venga incluso più volte nello stesso file di compilazione, il che potrebbe causare errori di ridefinizione.

```c
#ifndef NOME_HEADER_H
#define NOME_HEADER_H

// Contenuto del header file

#endif // NOME_HEADER_H
```

## Funzioni di libreria comuni e loro utilizzo

### Funzioni di input/output

| Funzione | Header | Descrizione |
|----------|--------|-------------|
| `printf()` | `<stdio.h>` | Stampa formattata su stdout |
| `scanf()` | `<stdio.h>` | Legge input formattato da stdin |
| `fprintf()` | `<stdio.h>` | Stampa formattata su un file |
| `fscanf()` | `<stdio.h>` | Legge input formattato da un file |
| `fopen()` | `<stdio.h>` | Apre un file |
| `fclose()` | `<stdio.h>` | Chiude un file |
| `fread()` | `<stdio.h>` | Legge dati binari da un file |
| `fwrite()` | `<stdio.h>` | Scrive dati binari su un file |
| `fgets()` | `<stdio.h>` | Legge una riga da un file |
| `fputs()` | `<stdio.h>` | Scrive una stringa su un file |

### Funzioni di manipolazione di stringhe

| Funzione | Header | Descrizione |
|----------|--------|-------------|
| `strlen()` | `<string.h>` | Restituisce la lunghezza di una stringa |
| `strcpy()` | `<string.h>` | Copia una stringa in un'altra |
| `strncpy()` | `<string.h>` | Copia un numero specificato di caratteri |
| `strcat()` | `<string.h>` | Concatena due stringhe |
| `strncat()` | `<string.h>` | Concatena un numero specificato di caratteri |
| `strcmp()` | `<string.h>` | Confronta due stringhe |
| `strncmp()` | `<string.h>` | Confronta un numero specificato di caratteri |
| `strchr()` | `<string.h>` | Trova la prima occorrenza di un carattere |
| `strrchr()` | `<string.h>` | Trova l'ultima occorrenza di un carattere |
| `strstr()` | `<string.h>` | Trova la prima occorrenza di una sottostringa |

### Funzioni di gestione della memoria

| Funzione | Header | Descrizione |
|----------|--------|-------------|
| `malloc()` | `<stdlib.h>` | Alloca memoria dinamicamente |
| `calloc()` | `<stdlib.h>` | Alloca e inizializza memoria a zero |
| `realloc()` | `<stdlib.h>` | Ridimensiona un blocco di memoria allocato |
| `free()` | `<stdlib.h>` | Libera memoria allocata dinamicamente |
| `memcpy()` | `<string.h>` | Copia un blocco di memoria |
| `memmove()` | `<string.h>` | Copia un blocco di memoria (sicuro per sovrapposizioni) |
| `memset()` | `<string.h>` | Imposta un blocco di memoria a un valore specifico |
| `memcmp()` | `<string.h>` | Confronta due blocchi di memoria |

## Best practice per l'utilizzo delle funzioni di libreria

1. **Includere solo gli header necessari**: Includere troppi header può aumentare il tempo di compilazione e potenzialmente causare conflitti di nomi.

2. **Controllare i valori di ritorno**: Molte funzioni di libreria restituiscono valori che indicano il successo o il fallimento dell'operazione. È importante controllare questi valori per gestire correttamente gli errori.

3. **Gestire la memoria correttamente**: Quando si utilizzano funzioni di allocazione dinamica della memoria (`malloc()`, `calloc()`, `realloc()`), assicurarsi di liberare la memoria con `free()` quando non è più necessaria.

4. **Utilizzare funzioni sicure**: Quando disponibili, preferire le versioni sicure delle funzioni (ad esempio, `strncpy()` invece di `strcpy()`) per evitare buffer overflow.

5. **Documentare l'uso delle librerie esterne**: Se il programma dipende da librerie non standard, documentare queste dipendenze e come installarle.

6. **Verificare la compatibilità**: Alcune funzioni potrebbero non essere disponibili su tutte le piattaforme o versioni del compilatore. Verificare la compatibilità se il codice deve essere portabile.

## Domande di autovalutazione

1. Qual è la differenza tra `#include <header.h>` e `#include "header.h"`?

2. Perché è importante utilizzare le guardie di inclusione negli header file?

3. Quali sono le principali funzioni per la manipolazione di stringhe in C?

4. Come si gestisce correttamente la memoria dinamica in C?

5. Quali sono i vantaggi di creare librerie personalizzate?

## Esercizi proposti

1. Crea una libreria personalizzata per la gestione di un array di interi, con funzioni per aggiungere, rimuovere, cercare e ordinare elementi.

2. Scrivi un programma che utilizzi le funzioni della libreria `<time.h>` per creare un orologio digitale che si aggiorna ogni secondo.

3. Implementa una funzione personalizzata `my_printf()` che simuli il comportamento di base della funzione `printf()` utilizzando `<stdarg.h>` e `<stdio.h>`.

4. Crea un programma che utilizzi le funzioni di `<string.h>` per analizzare un testo e contare le occorrenze di ogni parola.

5. Implementa una libreria per la gestione di una lista concatenata, con funzioni per inserire, eliminare e cercare elementi.