# Operatori e Tecniche Avanzate del Preprocessore in C

## Introduzione

Oltre alle direttive di inclusione e compilazione condizionale, il preprocessore C offre operatori speciali e tecniche avanzate che permettono manipolazioni sofisticate del codice sorgente. Questa guida esplora queste funzionalità avanzate e il loro utilizzo pratico.

## Operatori del Preprocessore

### L'Operatore # (Stringification)

L'operatore `#` converte un parametro di macro in una stringa letterale.

```c
#define STRINGIFY(x) #x

int main() {
    printf("%s\n", STRINGIFY(Hello World));  // Stampa: "Hello World"
    return 0;
}
```

#### Esempi di Utilizzo

```c
#define PRINT_VAR(var) printf(#var " = %d\n", var)

int main() {
    int count = 42;
    PRINT_VAR(count);  // Espande a: printf("count" " = %d\n", count);
                      // Che equivale a: printf("count = %d\n", count);
    return 0;
}
```

### L'Operatore ## (Token Pasting o Concatenazione)

L'operatore `##` concatena due token per formarne uno nuovo.

```c
#define CONCAT(a, b) a ## b

int main() {
    int xy = 10;
    printf("%d\n", CONCAT(x, y));  // Espande a: printf("%d\n", xy);
    return 0;
}
```

#### Esempi di Utilizzo

```c
// Generazione di nomi di variabili
#define MAKE_VAR(name, num) name ## num

int main() {
    int MAKE_VAR(count, 1) = 100;  // Espande a: int count1 = 100;
    int MAKE_VAR(count, 2) = 200;  // Espande a: int count2 = 200;
    
    printf("%d %d\n", count1, count2);
    return 0;
}
```

```c
// Generazione di nomi di funzioni
#define HANDLER(type) handle_ ## type

void handle_mouse() { printf("Gestione mouse\n"); }
void handle_keyboard() { printf("Gestione tastiera\n"); }

int main() {
    HANDLER(mouse)();  // Espande a: handle_mouse();
    HANDLER(keyboard)();  // Espande a: handle_keyboard();
    return 0;
}
```

## Macro Predefinite

Il preprocessore C fornisce diverse macro predefinite che possono essere utili per il debugging e la compilazione condizionale.

### Macro Standard

- `__FILE__`: Nome del file sorgente corrente (stringa)
- `__LINE__`: Numero di riga corrente nel file sorgente (intero)
- `__DATE__`: Data di compilazione in formato "Mmm dd yyyy" (stringa)
- `__TIME__`: Ora di compilazione in formato "hh:mm:ss" (stringa)
- `__STDC__`: 1 se il compilatore è conforme allo standard C (intero)
- `__func__`: Nome della funzione corrente (C99 e successivi)

### Esempi di Utilizzo

```c
#define LOG_ERROR(msg) fprintf(stderr, "Errore in %s, linea %d: %s\n", \
                              __FILE__, __LINE__, msg)

int divide(int a, int b) {
    if (b == 0) {
        LOG_ERROR("Divisione per zero");
        return 0;
    }
    return a / b;
}
```

### Macro Specifiche del Compilatore

Molti compilatori forniscono macro aggiuntive:

- GCC: `__GNUC__`, `__GNUC_MINOR__`, `__GNUC_PATCHLEVEL__`
- MSVC: `_MSC_VER`, `_MSC_FULL_VER`
- Clang: `__clang__`, `__clang_major__`, `__clang_minor__`

```c
#ifdef __GNUC__
    #define DEPRECATED(func) func __attribute__((deprecated))
#elif defined(_MSC_VER)
    #define DEPRECATED(func) __declspec(deprecated) func
#else
    #define DEPRECATED(func) func
#endif

// Utilizzo
DEPRECATED(void old_function()) {
    // Implementazione
}
```

## Tecniche Avanzate

### Macro con Numero Variabile di Argomenti

A partire da C99, è possibile definire macro con un numero variabile di argomenti utilizzando l'ellissi (`...`) e il token speciale `__VA_ARGS__`.

```c
#define DEBUG_PRINT(...) printf("Debug: " __VA_ARGS__)

int main() {
    int x = 10, y = 20;
    DEBUG_PRINT("x = %d, y = %d\n", x, y);
    // Espande a: printf("Debug: " "x = %d, y = %d\n", x, y);
    return 0;
}
```

### Macro X-Macros

Le X-Macros sono una tecnica avanzata che permette di generare codice ripetitivo in modo elegante.

```c
// Definizione delle costanti di errore
#define ERROR_CODES \
    X(OK,                0, "Nessun errore") \
    X(FILE_NOT_FOUND,    1, "File non trovato") \
    X(ACCESS_DENIED,     2, "Accesso negato") \
    X(OUT_OF_MEMORY,     3, "Memoria insufficiente")

// Generazione dell'enumerazione
enum ErrorCode {
#define X(name, code, desc) name = code,
    ERROR_CODES
#undef X
};

// Generazione dell'array di descrizioni
const char* error_descriptions[] = {
#define X(name, code, desc) [code] = desc,
    ERROR_CODES
#undef X
};

// Utilizzo
int main() {
    enum ErrorCode error = FILE_NOT_FOUND;
    printf("Errore: %s\n", error_descriptions[error]);
    return 0;
}
```

### Macro Ricorsive

Il preprocessore C non supporta direttamente la ricorsione nelle macro, ma è possibile simulare comportamenti ricorsivi con tecniche avanzate.

```c
// Implementazione del FOR_EACH per applicare una macro a ogni elemento di una lista
#define EXPAND(...) __VA_ARGS__
#define FIRST(a, ...) a
#define REST(a, ...) __VA_ARGS__

#define FOR_EACH_1(macro, a) macro(a)
#define FOR_EACH_2(macro, a, ...) macro(a), EXPAND(FOR_EACH_1(macro, __VA_ARGS__))
#define FOR_EACH_3(macro, a, ...) macro(a), EXPAND(FOR_EACH_2(macro, __VA_ARGS__))
#define FOR_EACH_4(macro, a, ...) macro(a), EXPAND(FOR_EACH_3(macro, __VA_ARGS__))

#define COUNT_ARGS(...) COUNT_ARGS_(__VA_ARGS__, 4, 3, 2, 1)
#define COUNT_ARGS_(a1, a2, a3, a4, count, ...) count

#define FOR_EACH_(count, macro, ...) EXPAND(FOR_EACH_ ## count(macro, __VA_ARGS__))
#define FOR_EACH(macro, ...) FOR_EACH_(COUNT_ARGS(__VA_ARGS__), macro, __VA_ARGS__)

// Esempio di utilizzo
#define SQUARE(x) ((x) * (x))

int main() {
    int values[] = { FOR_EACH(SQUARE, 1, 2, 3, 4) };
    // Espande a: int values[] = { ((1) * (1)), ((2) * (2)), ((3) * (3)), ((4) * (4)) };
    
    for (int i = 0; i < 4; i++) {
        printf("%d ", values[i]);
    }
    return 0;
}
```

## La Direttiva #pragma

La direttiva `#pragma` fornisce istruzioni specifiche al compilatore. Il suo comportamento varia tra i diversi compilatori.

### Esempi Comuni

```c
// Disabilitare avvisi specifici (MSVC)
#pragma warning(disable: 4996)

// Allineamento di strutture (GCC)
#pragma pack(push, 1)
struct CompactStruct {
    char a;
    int b;
    short c;
};
#pragma pack(pop)

// Ottimizzazione di sezioni di codice
#pragma optimize("t", on)  // Ottimizza per velocità (MSVC)
void performance_critical_function() {
    // Codice ottimizzato per velocità
}
#pragma optimize("", on)  // Ripristina le impostazioni predefinite
```

### #pragma once

Come visto nella lezione precedente, `#pragma once` è un'alternativa alle guardie di inclusione tradizionali:

```c
#pragma once

// Contenuto del file header
```

## La Direttiva #error

La direttiva `#error` causa un errore di compilazione con un messaggio specificato.

```c
#if !defined(__cplusplus) && !defined(__STDC_VERSION__)
    #error "Questo codice richiede un compilatore C o C++"
#endif

#if __STDC_VERSION__ < 201112L
    #error "Questo codice richiede C11 o versioni successive"
#endif
```

## La Direttiva #line

La direttiva `#line` modifica il numero di riga e il nome del file riportati dal compilatore per gli errori e gli avvisi.

```c
#line 1000 "file_virtuale.c"
// Da questo punto, il compilatore riporterà gli errori come se fossero nel file "file_virtuale.c" alla riga 1000+

int funzione_con_errore() {
    // Un errore qui sarà riportato come in "file_virtuale.c" alla riga 1002
    return x;  // Errore: 'x' non dichiarato
}
```

## Esempi Pratici Avanzati

### Implementazione di un Mini-Framework di Logging

```c
#define LOG_LEVEL_ERROR 3
#define LOG_LEVEL_WARNING 2
#define LOG_LEVEL_INFO 1
#define LOG_LEVEL_DEBUG 0

#ifndef CURRENT_LOG_LEVEL
    #define CURRENT_LOG_LEVEL LOG_LEVEL_INFO
#endif

#define LOG_FMT(level, fmt, ...) \
    fprintf(stderr, level " [%s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#if CURRENT_LOG_LEVEL <= LOG_LEVEL_DEBUG
    #define LOG_DEBUG(fmt, ...) LOG_FMT("DEBUG", fmt, ##__VA_ARGS__)
#else
    #define LOG_DEBUG(fmt, ...) ((void)0)
#endif

#if CURRENT_LOG_LEVEL <= LOG_LEVEL_INFO
    #define LOG_INFO(fmt, ...) LOG_FMT("INFO", fmt, ##__VA_ARGS__)
#else
    #define LOG_INFO(fmt, ...) ((void)0)
#endif

#if CURRENT_LOG_LEVEL <= LOG_LEVEL_WARNING
    #define LOG_WARNING(fmt, ...) LOG_FMT("WARNING", fmt, ##__VA_ARGS__)
#else
    #define LOG_WARNING(fmt, ...) ((void)0)
#endif

#if CURRENT_LOG_LEVEL <= LOG_LEVEL_ERROR
    #define LOG_ERROR(fmt, ...) LOG_FMT("ERROR", fmt, ##__VA_ARGS__)
#else
    #define LOG_ERROR(fmt, ...) ((void)0)
#endif

// Utilizzo
int main() {
    LOG_DEBUG("Valore: %d", 42);  // Visibile solo se CURRENT_LOG_LEVEL <= LOG_LEVEL_DEBUG
    LOG_INFO("Applicazione avviata");  // Visibile se CURRENT_LOG_LEVEL <= LOG_LEVEL_INFO
    LOG_WARNING("Risorsa non trovata: %s", "config.ini");  // Visibile se CURRENT_LOG_LEVEL <= LOG_LEVEL_WARNING
    LOG_ERROR("Errore critico: %s", "Connessione persa");  // Visibile se CURRENT_LOG_LEVEL <= LOG_LEVEL_ERROR
    return 0;
}
```

### Generazione Automatica di Funzioni di Serializzazione

```c
#define FIELD_INFO(type, name) { #name, offsetof(struct Person, name), sizeof(type) }

typedef struct {
    const char* name;
    size_t offset;
    size_t size;
} FieldInfo;

typedef struct Person {
    int id;
    char name[50];
    int age;
} Person;

const FieldInfo person_fields[] = {
    FIELD_INFO(int, id),
    FIELD_INFO(char[50], name),
    FIELD_INFO(int, age)
};

// Funzione che utilizza le informazioni generate per serializzare la struttura
void serialize_person(const Person* person, FILE* file) {
    for (size_t i = 0; i < sizeof(person_fields) / sizeof(FieldInfo); i++) {
        const FieldInfo* field = &person_fields[i];
        const void* field_addr = (const char*)person + field->offset;
        fwrite(field_addr, 1, field->size, file);
    }
}
```

## Esercizi Pratici

1. Implementa una macro `ASSERT` che stampi informazioni dettagliate (file, riga, espressione) quando una condizione non è soddisfatta.

2. Crea un sistema di "trace" che registri l'ingresso e l'uscita dalle funzioni, utilizzando le macro predefinite.

3. Implementa un mini-framework di unit testing utilizzando le tecniche di preprocessore avanzate.

4. Sviluppa una macro `ENUM_TO_STRING` che converta automaticamente i valori di un'enumerazione in stringhe.

## Domande di Autovalutazione

1. Qual è la differenza tra gli operatori `#` e `##` del preprocessore?

2. Come si può implementare una macro che accetta un numero variabile di argomenti?

3. Quali sono i vantaggi e gli svantaggi dell'utilizzo delle X-Macros?

4. Come si può utilizzare `#pragma` per ottimizzare sezioni critiche del codice?

5. In che modo le macro predefinite come `__FILE__` e `__LINE__` possono essere utili per il debugging?