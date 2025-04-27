# Il Sistema errno e le Funzioni Correlate in C

## Introduzione

Il sistema `errno` è uno dei meccanismi fondamentali per la gestione degli errori in C. Fornisce un modo standardizzato per comunicare informazioni dettagliate sugli errori che si verificano durante l'esecuzione delle funzioni della libreria standard. In questa guida, esploreremo il funzionamento di `errno` e le funzioni correlate per la gestione degli errori.

## La Variabile errno

La variabile `errno` è definita nell'header `<errno.h>` e viene utilizzata dalle funzioni della libreria standard per indicare il tipo di errore che si è verificato. Originariamente era una semplice variabile globale, ma nelle implementazioni moderne è generalmente definita come una macro che espande in un'espressione thread-local, per garantire la sicurezza in ambienti multi-thread.

```c
#include <errno.h>

// In implementazioni moderne, errno potrebbe essere definita come:
// #define errno (*__errno_location())
```

### Caratteristiche Importanti di errno

1. **Valore iniziale**: Il valore iniziale di `errno` è zero, che indica "nessun errore".
2. **Impostazione**: Le funzioni della libreria standard impostano `errno` solo in caso di errore, non lo resettano a zero in caso di successo.
3. **Thread-safety**: Nelle implementazioni moderne, `errno` è thread-local, quindi ogni thread ha la propria copia.
4. **Persistenza**: Il valore di `errno` persiste finché non viene esplicitamente modificato o finché non viene chiamata un'altra funzione che lo modifica.

## Codici di Errore Standard

L'header `<errno.h>` definisce una serie di macro per i codici di errore standard. Alcuni dei più comuni sono:

| Macro | Descrizione |
|-------|-------------|
| `EACCES` | Permesso negato |
| `EBADF` | File descriptor non valido |
| `EEXIST` | Il file esiste già |
| `EINVAL` | Argomento non valido |
| `EIO` | Errore di input/output |
| `ENOENT` | File o directory non esistente |
| `ENOMEM` | Memoria insufficiente |
| `ENOSPC` | Spazio insufficiente sul dispositivo |

Esempio di utilizzo:

```c
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    FILE *file = fopen("file_inesistente.txt", "r");
    
    if (file == NULL) {
        if (errno == ENOENT) {
            printf("Errore: il file non esiste\n");
        } else {
            printf("Errore: %s\n", strerror(errno));
        }
        return 1;
    }
    
    fclose(file);
    return 0;
}
```

## Funzioni per la Gestione di errno

### perror()

La funzione `perror()` stampa un messaggio di errore sullo standard error, basato sul valore corrente di `errno`:

```c
#include <stdio.h>

void perror(const char *s);
```

Il messaggio stampato è composto dal parametro `s`, seguito da due punti, uno spazio e la descrizione dell'errore corrispondente al valore di `errno`.

```c
#include <stdio.h>
#include <errno.h>

int main() {
    FILE *file = fopen("file_inesistente.txt", "r");
    
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        // Stampa: "Errore nell'apertura del file: No such file or directory"
        return 1;
    }
    
    fclose(file);
    return 0;
}
```

### strerror()

La funzione `strerror()` restituisce una stringa che descrive l'errore corrispondente al codice di errore specificato:

```c
#include <string.h>

char *strerror(int errnum);
```

```c
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    FILE *file = fopen("file_inesistente.txt", "r");
    
    if (file == NULL) {
        printf("Errore: %s\n", strerror(errno));
        // Stampa: "Errore: No such file or directory"
        return 1;
    }
    
    fclose(file);
    return 0;
}
```

### strerror_r()

La funzione `strerror_r()` è una versione thread-safe di `strerror()`. Esistono due varianti: la versione POSIX e la versione GNU.

#### Versione POSIX

```c
#include <string.h>

int strerror_r(int errnum, char *buf, size_t buflen);
```

#### Versione GNU

```c
#include <string.h>

char *strerror_r(int errnum, char *buf, size_t buflen);
```

Esempio di utilizzo (versione POSIX):

```c
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    FILE *file = fopen("file_inesistente.txt", "r");
    
    if (file == NULL) {
        char error_buf[100];
        strerror_r(errno, error_buf, sizeof(error_buf));
        printf("Errore: %s\n", error_buf);
        return 1;
    }
    
    fclose(file);
    return 0;
}
```

## Utilizzo Avanzato di errno

### Salvataggio e Ripristino di errno

In alcune situazioni, potrebbe essere necessario salvare e ripristinare il valore di `errno`, ad esempio quando si chiamano funzioni che potrebbero modificarlo all'interno di un gestore di errori:

```c
#include <stdio.h>
#include <errno.h>
#include <string.h>

void log_error(const char *message) {
    int saved_errno = errno;  // Salva il valore corrente di errno
    
    // Operazioni che potrebbero modificare errno
    fprintf(stderr, "Errore: %s - %s\n", message, strerror(saved_errno));
    
    errno = saved_errno;  // Ripristina il valore originale di errno
}

int main() {
    FILE *file = fopen("file_inesistente.txt", "r");
    
    if (file == NULL) {
        log_error("Impossibile aprire il file");
        return 1;
    }
    
    fclose(file);
    return 0;
}
```

### Gestione di Errori Specifici

È possibile implementare comportamenti diversi in base al tipo di errore che si è verificato:

```c
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    FILE *file = fopen("dati.txt", "r");
    
    if (file == NULL) {
        switch (errno) {
            case ENOENT:
                printf("Errore: il file non esiste. Creazione di un nuovo file...\n");
                file = fopen("dati.txt", "w");
                if (file == NULL) {
                    perror("Errore nella creazione del file");
                    return 1;
                }
                break;
                
            case EACCES:
                printf("Errore: permesso negato. Verificare i permessi del file.\n");
                return 1;
                
            default:
                printf("Errore: %s\n", strerror(errno));
                return 1;
        }
    }
    
    // Utilizzo del file...
    
    fclose(file);
    return 0;
}
```

## Limitazioni e Considerazioni

### Limitazioni di errno

1. **Non viene resettato automaticamente**: Le funzioni della libreria standard impostano `errno` solo in caso di errore, non lo resettano a zero in caso di successo. È responsabilità del programmatore resettarlo se necessario.

2. **Può essere sovrascritto**: Il valore di `errno` può essere sovrascritto da chiamate successive a funzioni della libreria standard, anche se queste hanno successo.

3. **Non tutte le funzioni utilizzano errno**: Alcune funzioni della libreria standard comunicano gli errori in altri modi, ad esempio restituendo un codice di errore direttamente.

4. **Valori specifici dell'implementazione**: I valori esatti delle macro dei codici di errore possono variare tra diverse implementazioni.

### Best Practices

1. **Controllare errno solo dopo un errore**: Verificare il valore di `errno` solo dopo aver rilevato un errore (ad esempio, quando una funzione restituisce -1 o NULL).

2. **Resettare errno prima di chiamare una funzione**, se si intende utilizzarlo per rilevare errori:

```c
errno = 0;
long value = strtol(str, &endptr, 10);
if (errno != 0) {
    // Si è verificato un errore durante la conversione
}
```

3. **Utilizzare strerror_r() in ambienti multi-thread** per evitare problemi di concorrenza.

4. **Documentare gli errori possibili** nelle funzioni che si implementano, specificando quali codici di errore possono essere impostati.

## Implementazione di un Sistema di Gestione degli Errori Basato su errno

È possibile implementare un sistema di gestione degli errori personalizzato basato su `errno` per le proprie funzioni:

```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// Definizione di codici di errore personalizzati
#define ERR_CUSTOM_BASE 1000
#define ERR_INVALID_CONFIG (ERR_CUSTOM_BASE + 1)
#define ERR_CONNECTION_FAILED (ERR_CUSTOM_BASE + 2)
#define ERR_TIMEOUT (ERR_CUSTOM_BASE + 3)

// Array di messaggi di errore personalizzati
static const char *custom_error_messages[] = {
    "Configurazione non valida",
    "Connessione fallita",
    "Timeout dell'operazione"
};

// Funzione per ottenere il messaggio di errore
const char *get_error_message(int errnum) {
    if (errnum >= ERR_CUSTOM_BASE && errnum < ERR_CUSTOM_BASE + sizeof(custom_error_messages) / sizeof(char*)) {
        return custom_error_messages[errnum - ERR_CUSTOM_BASE - 1];
    } else {
        return strerror(errnum);
    }
}

// Funzione che può generare errori
int connect_to_server(const char *address) {
    if (address == NULL) {
        errno = ERR_INVALID_CONFIG;
        return -1;
    }
    
    // Simulazione di un errore di connessione
    errno = ERR_CONNECTION_FAILED;
    return -1;
}

int main() {
    if (connect_to_server(NULL) == -1) {
        printf("Errore: %s\n", get_error_message(errno));
        return 1;
    }
    
    return 0;
}
```

## Conclusione

Il sistema `errno` è uno strumento potente per la gestione degli errori in C, che permette di ottenere informazioni dettagliate sugli errori che si verificano durante l'esecuzione delle funzioni della libreria standard. Comprendere il funzionamento di `errno` e delle funzioni correlate è essenziale per implementare una gestione degli errori robusta ed efficace nei programmi C.

## Esercizi

1. Implementa una funzione che tenti di aprire un file e, in caso di errore, fornisca un messaggio dettagliato basato sul valore di `errno`, con suggerimenti specifici per risolvere il problema.

2. Crea un wrapper per le funzioni di allocazione della memoria (`malloc`, `calloc`, `realloc`) che gestisca automaticamente l'errore `ENOMEM` e implementi una strategia di retry.

3. Sviluppa un sistema di logging che registri gli errori in un file, includendo il valore di `errno`, il messaggio corrispondente e informazioni sul contesto in cui si è verificato l'errore.