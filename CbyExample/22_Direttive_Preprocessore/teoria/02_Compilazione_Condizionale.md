# Compilazione Condizionale in C

## Introduzione

La compilazione condizionale è una potente caratteristica del preprocessore C che permette di includere o escludere porzioni di codice durante la fase di compilazione. Questo meccanismo è fondamentale per creare codice portabile, gestire diverse configurazioni e implementare funzionalità di debug.

## Direttive di Compilazione Condizionale

### #if, #else, #elif, #endif

Queste direttive permettono di valutare espressioni costanti e includere o escludere codice in base al risultato.

```c
#if espressione
    // Codice compilato se l'espressione è diversa da zero
#elif altra_espressione
    // Codice compilato se la prima espressione è zero e questa è diversa da zero
#else
    // Codice compilato se tutte le espressioni precedenti sono zero
#endif
```

### Esempio di Utilizzo

```c
#define VERSION 2

#if VERSION == 1
    printf("Versione 1 del software\n");
#elif VERSION == 2
    printf("Versione 2 del software\n");
#else
    printf("Versione non riconosciuta\n");
#endif
```

### #ifdef e #ifndef

Queste direttive verificano se una macro è stata definita o meno.

```c
#ifdef MACRO
    // Codice compilato se MACRO è definita
#endif

#ifndef MACRO
    // Codice compilato se MACRO non è definita
#endif
```

### Esempio di Utilizzo

```c
#ifdef DEBUG
    printf("Debug: valore di x = %d\n", x);
#endif

#ifndef MAX_BUFFER_SIZE
    #define MAX_BUFFER_SIZE 1024
#endif
```

## Utilizzi Comuni della Compilazione Condizionale

### 1. Guardie di Inclusione

Come visto nella lezione precedente, le guardie di inclusione sono un esempio classico di compilazione condizionale:

```c
#ifndef MYHEADER_H
#define MYHEADER_H

// Contenuto del file header

#endif // MYHEADER_H
```

### 2. Codice Specifico per Piattaforma

```c
#ifdef _WIN32
    // Codice specifico per Windows
    #include <windows.h>
    void sleep_ms(int milliseconds) {
        Sleep(milliseconds);
    }
#elif defined(__APPLE__)
    // Codice specifico per macOS
    #include <unistd.h>
    void sleep_ms(int milliseconds) {
        usleep(milliseconds * 1000);
    }
#elif defined(__linux__)
    // Codice specifico per Linux
    #include <unistd.h>
    void sleep_ms(int milliseconds) {
        usleep(milliseconds * 1000);
    }
#else
    #error "Sistema operativo non supportato"
#endif
```

### 3. Modalità Debug

```c
#ifdef DEBUG
    #define LOG(msg) printf("DEBUG: %s\n", msg)
#else
    #define LOG(msg) // Non fa nulla in modalità release
#endif

int main() {
    LOG("Inizializzazione completata");
    // Resto del codice
    return 0;
}
```

### 4. Gestione delle Versioni

```c
#define API_VERSION 2

#if API_VERSION == 1
    // Implementazione API v1
    void process_data(int data) {
        // Vecchia implementazione
    }
#elif API_VERSION == 2
    // Implementazione API v2
    void process_data(int data, int flags) {
        // Nuova implementazione
    }
#endif
```

## La Direttiva #defined

L'operatore `defined` può essere utilizzato nelle espressioni `#if` e `#elif` per verificare se una macro è definita:

```c
#if defined(DEBUG) && defined(VERBOSE)
    // Codice compilato se sia DEBUG che VERBOSE sono definite
#endif

#if !defined(BUFFER_SIZE)
    #define BUFFER_SIZE 1024
#endif
```

## Best Practices

1. **Minimizzare l'Uso**: La compilazione condizionale può rendere il codice difficile da leggere e mantenere. Utilizzarla con moderazione.

2. **Documentare le Macro**: Documentare chiaramente il significato e l'effetto delle macro utilizzate per la compilazione condizionale.

3. **Indentazione Coerente**: Mantenere un'indentazione coerente per rendere visibile la struttura del codice condizionale.

4. **Evitare Nidificazioni Profonde**: Troppe direttive condizionali nidificate rendono il codice illeggibile.

5. **Utilizzare Nomi Significativi**: Scegliere nomi di macro che riflettano chiaramente il loro scopo.

## Esempi Avanzati

### Compilazione Condizionale Basata su Versioni del Compilatore

```c
#ifdef __GNUC__
    // Codice specifico per GCC
    #if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
        // Funzionalità disponibili in GCC 4.6 o superiore
    #endif
#elif defined(_MSC_VER)
    // Codice specifico per Microsoft Visual C++
    #if _MSC_VER >= 1900
        // Funzionalità disponibili in Visual C++ 2015 o superiore
    #endif
#endif
```

### Gestione di Funzionalità Opzionali

```c
// Nel file di configurazione
#define ENABLE_FEATURE_A
//#define ENABLE_FEATURE_B
#define ENABLE_FEATURE_C

// Nel codice
#ifdef ENABLE_FEATURE_A
    // Implementazione della funzionalità A
#endif

#ifdef ENABLE_FEATURE_B
    // Implementazione della funzionalità B
#endif

#ifdef ENABLE_FEATURE_C
    // Implementazione della funzionalità C
#endif
```

## Esercizi Pratici

1. Crea un programma che utilizzi la compilazione condizionale per implementare diverse strategie di ordinamento (bubble sort, quick sort, etc.) selezionabili tramite macro.

2. Implementa un sistema di logging che possa essere configurato per diversi livelli di dettaglio (ERROR, WARNING, INFO, DEBUG) utilizzando la compilazione condizionale.

3. Scrivi un header file che utilizzi la compilazione condizionale per fornire implementazioni diverse di una stessa funzione in base al sistema operativo.

## Domande di Autovalutazione

1. Qual è la differenza tra `#ifdef` e `#if defined()`?

2. Come si può utilizzare la compilazione condizionale per creare codice portabile tra diverse piattaforme?

3. Quali sono i potenziali problemi dell'uso eccessivo della compilazione condizionale?

4. Come si può implementare un sistema di "feature flags" utilizzando la compilazione condizionale?

5. In che modo la compilazione condizionale può essere utile durante lo sviluppo e il debugging di un'applicazione?