# Inclusione Condizionale nel Preprocessore C

## Introduzione

L'inclusione condizionale è una caratteristica potente del preprocessore C che permette di compilare selettivamente parti di codice in base a determinate condizioni. Questo meccanismo è fondamentale per creare codice portabile, gestire diverse configurazioni e implementare funzionalità opzionali.

## Direttive di Compilazione Condizionale

### La Direttiva #if, #else, #elif e #endif

#### Sintassi e Funzionamento

```c
#if espressione
    // Codice compilato se espressione è diversa da zero
#elif altra_espressione
    // Codice compilato se altra_espressione è diversa da zero e le precedenti sono false
#else
    // Codice compilato se tutte le espressioni precedenti sono false
#endif
```

Le espressioni nelle direttive `#if` e `#elif` devono essere costanti intere o espressioni che possono essere valutate durante la fase di preprocessore.

#### Esempi di Utilizzo

```c
#include <stdio.h>

#define VERSIONE 2

int main() {
#if VERSIONE == 1
    printf("Versione 1 del programma\n");
#elif VERSIONE == 2
    printf("Versione 2 del programma\n");
#else
    printf("Versione sconosciuta del programma\n");
#endif
    return 0;
}
```

### La Direttiva #ifdef e #ifndef

#### Sintassi e Funzionamento

```c
#ifdef MACRO
    // Codice compilato se MACRO è definita
#endif

#ifndef MACRO
    // Codice compilato se MACRO non è definita
#endif
```

Queste direttive sono equivalenti a:

```c
#if defined(MACRO)
    // ...
#endif

#if !defined(MACRO)
    // ...
#endif
```

#### Esempi di Utilizzo

```c
#include <stdio.h>

// Definizione condizionale per sistemi operativi
#ifdef _WIN32
    #define SISTEMA "Windows"
#elif defined(__APPLE__)
    #define SISTEMA "macOS"
#elif defined(__linux__)
    #define SISTEMA "Linux"
#else
    #define SISTEMA "Sconosciuto"
#endif

int main() {
    printf("Sistema operativo: %s\n", SISTEMA);
    return 0;
}
```

## Protezione degli Header File

Uno degli usi più comuni dell'inclusione condizionale è la protezione degli header file dalle inclusioni multiple, nota anche come "include guard".

### Esempio di Include Guard

```c
// file: mio_header.h
#ifndef MIO_HEADER_H
#define MIO_HEADER_H

// Contenuto dell'header file
typedef struct {
    int x;
    int y;
} Punto;

void sposta_punto(Punto *p, int dx, int dy);

#endif // MIO_HEADER_H
```

Questo meccanismo garantisce che il contenuto dell'header venga incluso una sola volta, anche se il file viene incluso più volte in diversi punti del programma.

### Alternativa Moderna: #pragma once

Molti compilatori moderni supportano la direttiva `#pragma once` che svolge la stessa funzione degli include guard tradizionali, ma in modo più conciso:

```c
// file: mio_header.h
#pragma once

// Contenuto dell'header file
typedef struct {
    int x;
    int y;
} Punto;

void sposta_punto(Punto *p, int dx, int dy);
```

Nota: `#pragma once` non fa parte dello standard C, ma è supportato dalla maggior parte dei compilatori moderni.

## Compilazione Condizionale per Debug

La compilazione condizionale è spesso utilizzata per includere codice di debug solo nelle build di sviluppo.

```c
#include <stdio.h>

#define DEBUG 1

#ifdef DEBUG
    #define LOG_DEBUG(msg) printf("[DEBUG] %s\n", msg)
#else
    #define LOG_DEBUG(msg) /* nulla */
#endif

int main() {
    LOG_DEBUG("Inizializzazione del programma");
    int x = 10;
    LOG_DEBUG("Variabile x inizializzata");
    
    // Resto del programma
    return 0;
}
```

## Compilazione Condizionale per Portabilità

La compilazione condizionale è fondamentale per scrivere codice portabile che funzioni su diverse piattaforme.

```c
#include <stdio.h>

// Definizioni specifiche per la piattaforma
#ifdef _WIN32
    #include <windows.h>
    #define PAUSA() Sleep(1000)  // Pausa di 1 secondo su Windows
#else
    #include <unistd.h>
    #define PAUSA() sleep(1)     // Pausa di 1 secondo su sistemi UNIX
#endif

int main() {
    printf("Inizio\n");
    PAUSA();
    printf("Fine\n");
    return 0;
}
```

## Macro Predefinite per la Compilazione Condizionale

I compilatori C definiscono automaticamente diverse macro che possono essere utilizzate per la compilazione condizionale:

### Macro Specifiche del Sistema Operativo

| Macro | Sistema Operativo |
|-------|-------------------|
| `_WIN32` | Windows (32 o 64 bit) |
| `_WIN64` | Windows 64 bit |
| `__APPLE__` | macOS |
| `__linux__` | Linux |
| `__unix__` | Unix o Unix-like |
| `__FreeBSD__` | FreeBSD |

### Macro Specifiche del Compilatore

| Macro | Compilatore |
|-------|------------|
| `__GNUC__` | GCC |
| `_MSC_VER` | Microsoft Visual C++ |
| `__clang__` | Clang |
| `__INTEL_COMPILER` | Intel C++ |

### Esempio di Utilizzo

```c
#include <stdio.h>

int main() {
#if defined(__GNUC__)
    printf("Compilato con GCC versione %d.%d.%d\n", 
           __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#elif defined(_MSC_VER)
    printf("Compilato con Microsoft Visual C++ versione %d\n", _MSC_VER);
#elif defined(__clang__)
    printf("Compilato con Clang versione %d.%d.%d\n", 
           __clang_major__, __clang_minor__, __clang_patchlevel__);
#else
    printf("Compilatore sconosciuto\n");
#endif
    return 0;
}
```

## Tecniche Avanzate

### Controllo delle Caratteristiche del Compilatore

```c
#include <stdio.h>

// Verifica se il compilatore supporta C99 o versioni successive
#if __STDC_VERSION__ >= 199901L
    #define SUPPORTA_C99 1
#else
    #define SUPPORTA_C99 0
#endif

int main() {
#if SUPPORTA_C99
    // Utilizzo di caratteristiche C99
    for (int i = 0; i < 10; i++) {
        printf("%d\n", i);
    }
#else
    // Codice compatibile con C89/C90
    int i;
    for (i = 0; i < 10; i++) {
        printf("%d\n", i);
    }
#endif
    return 0;
}
```

### Compilazione Condizionale per Ottimizzazione

```c
#include <stdio.h>

#define OTTIMIZZAZIONE 2  // 0=nessuna, 1=base, 2=avanzata

void elabora_dati(int *dati, int dimensione) {
#if OTTIMIZZAZIONE == 0
    // Versione semplice e leggibile
    for (int i = 0; i < dimensione; i++) {
        dati[i] = dati[i] * 2 + 1;
    }
#elif OTTIMIZZAZIONE == 1
    // Versione con ottimizzazione base
    for (int i = 0; i < dimensione; i += 2) {
        dati[i] = dati[i] * 2 + 1;
        if (i + 1 < dimensione)
            dati[i + 1] = dati[i + 1] * 2 + 1;
    }
#else
    // Versione con ottimizzazione avanzata
    // Potrebbe includere parallelizzazione, istruzioni SIMD, ecc.
    // ...
#endif
}
```

## Vantaggi e Svantaggi della Compilazione Condizionale

### Vantaggi

1. **Portabilità**: Adattare il codice a diverse piattaforme e compilatori
2. **Configurabilità**: Abilitare o disabilitare funzionalità in base alle esigenze
3. **Ottimizzazione**: Utilizzare implementazioni diverse in base al contesto
4. **Debug**: Includere codice di debug solo quando necessario

### Svantaggi

1. **Leggibilità**: L'uso eccessivo di direttive condizionali può rendere il codice difficile da leggere
2. **Manutenibilità**: Più percorsi di codice da testare e mantenere
3. **Complessità**: Possibili interazioni impreviste tra diverse condizioni
4. **Testing**: Difficoltà nel testare tutte le possibili combinazioni di condizioni

## Conclusione

L'inclusione condizionale è uno strumento potente del preprocessore C che permette di adattare il codice a diverse situazioni senza duplicazione. Utilizzata correttamente, può migliorare significativamente la portabilità, la configurabilità e la manutenibilità del codice.

## Esercizi

1. Scrivi un programma che utilizzi la compilazione condizionale per stampare un messaggio diverso in base al sistema operativo.
2. Crea un header file con protezione contro le inclusioni multiple utilizzando sia il metodo tradizionale che `#pragma once`.
3. Implementa un sistema di logging che utilizzi la compilazione condizionale per abilitare o disabilitare diversi livelli di log (debug, info, warning, error).
4. Scrivi un programma che utilizzi la compilazione condizionale per scegliere tra diverse implementazioni di una funzione in base alla versione dello standard C supportata.
5. Crea una macro che utilizzi la compilazione condizionale per gestire le differenze tra le API di file I/O su Windows e sistemi UNIX.

## Domande di Autovalutazione

1. Qual è la differenza tra `#ifdef` e `#if defined()`?
2. Perché è importante proteggere gli header file dalle inclusioni multiple?
3. Quali sono i vantaggi di `#pragma once` rispetto agli include guard tradizionali?
4. Come si può utilizzare la compilazione condizionale per il debug senza modificare il codice sorgente?
5. Quali macro predefinite possono essere utilizzate per rilevare il sistema operativo?
6. Come si può utilizzare la compilazione condizionale per gestire diverse versioni dello standard C?
7. Quali sono i potenziali problemi dell'uso eccessivo della compilazione condizionale?
8. Come si può utilizzare la compilazione condizionale per ottimizzare il codice in base alla piattaforma target?