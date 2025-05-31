# Operatori e Tecniche Avanzate del Preprocessore in C

## Operatori Speciali del Preprocessore

Il preprocessore C offre alcuni operatori speciali che permettono manipolazioni avanzate delle macro.

### L'Operatore di Stringificazione (#)

#### Sintassi e Funzionamento

L'operatore `#` converte un parametro di una macro in una stringa letterale.

```c
#define STRINGIFICA(x) #x
```

#### Esempi di Utilizzo

```c
#include <stdio.h>

#define STRINGIFICA(x) #x

int main() {
    printf("%s\n", STRINGIFICA(Hello World));  // Stampa: "Hello World"
    
    int a = 42;
    printf("%s = %d\n", STRINGIFICA(a), a);  // Stampa: "a = 42"
    
    return 0;
}
```

### L'Operatore di Concatenazione (##)

#### Sintassi e Funzionamento

L'operatore `##` concatena due token per formarne uno nuovo.

```c
#define CONCATENA(x, y) x##y
```

#### Esempi di Utilizzo

```c
#include <stdio.h>

#define CONCATENA(x, y) x##y

int main() {
    int var1 = 10;
    int var2 = 20;
    int var12 = 30;
    
    printf("%d\n", CONCATENA(var, 1));  // Stampa il valore di var1 (10)
    printf("%d\n", CONCATENA(var, 2));  // Stampa il valore di var2 (20)
    printf("%d\n", CONCATENA(var, 12)); // Stampa il valore di var12 (30)
    
    return 0;
}
```

### Combinazione degli Operatori

```c
#include <stdio.h>

#define DEBUG_PRINT(var) printf(#var " = %d\n", var)
#define GENERA_FUNZIONE(tipo, nome) tipo nome##_funzione(tipo x) { return x * 2; }

// Genera una funzione int raddoppia_funzione(int x) { return x * 2; }
GENERA_FUNZIONE(int, raddoppia)

int main() {
    int valore = 21;
    DEBUG_PRINT(valore);  // Stampa: "valore = 21"
    
    int risultato = raddoppia_funzione(valore);
    DEBUG_PRINT(risultato);  // Stampa: "risultato = 42"
    
    return 0;
}
```

## Macro Variadic

Le macro variadic accettano un numero variabile di argomenti, simile alle funzioni variadic.

### Sintassi e Funzionamento

```c
#define MACRO(...)      // Tutti gli argomenti in __VA_ARGS__
#define MACRO(x, ...)   // Primo argomento in x, resto in __VA_ARGS__
```

### Esempi di Utilizzo

```c
#include <stdio.h>

#define DEBUG_LOG(...) printf("[DEBUG] " __VA_ARGS__)
#define PRINT_VALUES(formato, ...) printf(formato, __VA_ARGS__)

int main() {
    DEBUG_LOG("Valore: %d\n", 42);  // Stampa: "[DEBUG] Valore: 42"
    
    int a = 10, b = 20, c = 30;
    PRINT_VALUES("Valori: %d, %d, %d\n", a, b, c);  // Stampa: "Valori: 10, 20, 30"
    
    return 0;
}
```

### Gestione del Caso Senza Argomenti Variadic

In C99, se `__VA_ARGS__` è vuoto, la virgola che lo precede può causare errori di sintassi. C++20 e GCC forniscono soluzioni:

```c
// Soluzione GCC (estensione)
#define DEBUG_LOG(formato, ...) printf("[DEBUG] " formato, ##__VA_ARGS__)

// Soluzione C++20 e alcuni compilatori C moderni
#define DEBUG_LOG(formato, ...) printf("[DEBUG] " formato __VA_OPT__(,) __VA_ARGS__)
```

## Tecniche Avanzate

### Macro Ricorsive

Il preprocessore C non supporta direttamente la ricorsione nelle macro, ma è possibile simulare comportamenti ricorsivi con tecniche avanzate.

```c
#include <stdio.h>

// Definizione di una sequenza di numeri
#define SEQ_1 1
#define SEQ_2 2, SEQ_1
#define SEQ_3 3, SEQ_2
#define SEQ_4 4, SEQ_3
#define SEQ_5 5, SEQ_4

// Macro per contare gli argomenti
#define CONTA_ARGS(...) CONTA_ARGS_IMPL(__VA_ARGS__, 5, 4, 3, 2, 1, 0)
#define CONTA_ARGS_IMPL(_1, _2, _3, _4, _5, N, ...) N

int main() {
    printf("SEQ_5: %d, %d, %d, %d, %d\n", SEQ_5);  // Stampa: "SEQ_5: 5, 4, 3, 2, 1"
    
    int count = CONTA_ARGS(1, 2, 3);  // count = 3
    printf("Numero di argomenti: %d\n", count);
    
    return 0;
}
```

### X-Macros

Le X-Macros sono un pattern avanzato che permette di generare codice ripetitivo in modo conciso.

```c
#include <stdio.h>

// Definizione della lista di elementi
#define LISTA_ELEMENTI \
    X(MELA,  "mela",  1) \
    X(PERA,  "pera",  2) \
    X(BANANA, "banana", 3) \
    X(ARANCIA, "arancia", 4)

// Generazione dell'enumerazione
#define X(nome, stringa, valore) nome = valore,
enum Frutta {
    LISTA_ELEMENTI
};
#undef X

// Generazione dell'array di stringhe
#define X(nome, stringa, valore) stringa,
const char* nomi_frutta[] = {
    LISTA_ELEMENTI
};
#undef X

int main() {
    // Utilizzo dell'enumerazione e dell'array
    enum Frutta f = BANANA;
    printf("Frutta: %s (valore: %d)\n", nomi_frutta[f-1], f);
    
    return 0;
}
```

### Generazione di Codice con Macro

```c
#include <stdio.h>

// Macro per generare funzioni getter e setter
#define GENERA_ACCESSORI(tipo, struttura, campo) \
    tipo get_##struttura##_##campo(struttura* s) { \
        return s->campo; \
    } \
    void set_##struttura##_##campo(struttura* s, tipo valore) { \
        s->campo = valore; \
    }

// Definizione della struttura
typedef struct {
    int x;
    int y;
} Punto;

// Generazione degli accessori
GENERA_ACCESSORI(int, Punto, x)
GENERA_ACCESSORI(int, Punto, y)

int main() {
    Punto p = {10, 20};
    
    printf("Punto: (%d, %d)\n", get_Punto_x(&p), get_Punto_y(&p));
    
    set_Punto_x(&p, 30);
    set_Punto_y(&p, 40);
    
    printf("Punto modificato: (%d, %d)\n", get_Punto_x(&p), get_Punto_y(&p));
    
    return 0;
}
```

## Direttive Avanzate

### La Direttiva #error

#### Sintassi e Funzionamento

```c
#error messaggio
```

La direttiva `#error` causa un errore di compilazione con il messaggio specificato.

#### Esempi di Utilizzo

```c
#include <stdio.h>

#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L
    #error "Questo programma richiede C99 o versioni successive"
#endif

int main() {
    // Codice che utilizza caratteristiche C99
    return 0;
}
```

### La Direttiva #pragma

#### Sintassi e Funzionamento

```c
#pragma nome [argomenti]
```

La direttiva `#pragma` fornisce istruzioni specifiche al compilatore. I pragma sono specifici del compilatore e non sono standardizzati.

#### Esempi di Utilizzo

```c
#include <stdio.h>

// Disabilita avvisi specifici (GCC)
#pragma GCC diagnostic ignored "-Wunused-variable"

// Ottimizzazione specifica per una funzione (GCC)
#pragma GCC optimize ("O3")
void funzione_ottimizzata() {
    // Codice ottimizzato
}

// Allineamento dei dati (comune)
#pragma pack(1)  // Allineamento a 1 byte
struct Pacchetto {
    char tipo;
    int dati;
    short checksum;
};
#pragma pack()  // Ripristina l'allineamento predefinito

int main() {
    printf("Dimensione struct: %zu\n", sizeof(struct Pacchetto));
    return 0;
}
```

### La Direttiva #line

#### Sintassi e Funzionamento

```c
#line numero ["file"]
```

La direttiva `#line` modifica il numero di linea e opzionalmente il nome del file riportati dal compilatore nei messaggi di errore e nelle macro `__LINE__` e `__FILE__`.

#### Esempi di Utilizzo

```c
#include <stdio.h>

int main() {
    printf("Linea: %d, File: %s\n", __LINE__, __FILE__);
    
    #line 100 "file_virtuale.c"
    printf("Linea: %d, File: %s\n", __LINE__, __FILE__);
    
    return 0;
}
```

## Interazione con il Compilatore

### Attributi e Estensioni

Molti compilatori moderni supportano attributi e estensioni che possono essere utilizzati insieme al preprocessore.

```c
#include <stdio.h>

// Attributi GCC
#ifdef __GNUC__
    #define FUNZIONE_INLINE __attribute__((always_inline)) inline
    #define FUNZIONE_DEPRECATED __attribute__((deprecated))
    #define PACKED __attribute__((packed))
#else
    #define FUNZIONE_INLINE inline
    #define FUNZIONE_DEPRECATED
    #define PACKED
#endif

// Utilizzo degli attributi
FUNZIONE_INLINE int somma(int a, int b) {
    return a + b;
}

FUNZIONE_DEPRECATED void funzione_vecchia() {
    // Funzione obsoleta
}

typedef struct PACKED {
    char a;
    int b;
    short c;
} StrutturaCompatta;

int main() {
    printf("Dimensione struttura: %zu\n", sizeof(StrutturaCompatta));
    return 0;
}
```

### Integrazione con Build System

Il preprocessore può essere utilizzato per integrare il codice con sistemi di build come Make o CMake.

```c
#include <stdio.h>

// Definizioni che potrebbero venire da un sistema di build
#ifndef VERSIONE
    #define VERSIONE "1.0.0"
#endif

#ifndef DEBUG
    #define DEBUG 0
#endif

#ifndef MAX_ELEMENTI
    #define MAX_ELEMENTI 100
#endif

int main() {
    printf("Versione: %s\n", VERSIONE);
    printf("Debug: %s\n", DEBUG ? "attivo" : "disattivo");
    printf("Massimo numero di elementi: %d\n", MAX_ELEMENTI);
    
    return 0;
}
```

Compilazione:
```bash
gcc -DVERSIONE=\"2.0.0\" -DDEBUG=1 -DMAX_ELEMENTI=200 programma.c -o programma
```

## Vantaggi e Svantaggi delle Tecniche Avanzate

### Vantaggi

1. **Generazione di Codice**: Riduzione della duplicazione e automazione della generazione di codice ripetitivo
2. **Flessibilità**: Adattamento del codice a diverse piattaforme e configurazioni
3. **Ottimizzazione**: Possibilità di ottimizzare il codice in fase di compilazione
4. **Metaprogrammazione**: Implementazione di tecniche di metaprogrammazione in un linguaggio che non le supporta nativamente

### Svantaggi

1. **Complessità**: Le tecniche avanzate possono rendere il codice difficile da comprendere e debuggare
2. **Manutenibilità**: Codice generato da macro complesse può essere difficile da mantenere
3. **Portabilità**: Alcune tecniche avanzate possono dipendere da estensioni specifiche del compilatore
4. **Errori Criptici**: Gli errori nelle macro avanzate possono generare messaggi di errore difficili da interpretare

## Conclusione

Gli operatori e le tecniche avanzate del preprocessore C offrono potenti strumenti per la generazione e manipolazione del codice. Sebbene possano aumentare la complessità, quando utilizzati correttamente possono migliorare significativamente la manutenibilità, la flessibilità e l'efficienza del codice.

È importante utilizzare queste tecniche con giudizio, documentando adeguatamente il codice e considerando l'impatto sulla leggibilità e sulla manutenibilità.

## Esercizi

1. Crea una macro che utilizzi l'operatore di stringificazione per generare automaticamente messaggi di debug con il nome della variabile e il suo valore.
2. Implementa una serie di macro che utilizzino l'operatore di concatenazione per generare nomi di funzioni e variabili.
3. Crea una macro variadic che formatti e stampi messaggi di log con diversi livelli di severità (debug, info, warning, error).
4. Implementa un sistema di X-Macros per generare una tabella di lookup per una funzione hash.
5. Crea una macro che generi automaticamente funzioni getter e setter per i campi di una struttura.

## Domande di Autovalutazione

1. Qual è la differenza tra l'operatore `#` e l'operatore `##` nel preprocessore C?
2. Come funzionano le macro variadic e come si gestisce il caso in cui non ci sono argomenti variabili?
3. Quali sono i vantaggi e gli svantaggi delle X-Macros?
4. Come si può utilizzare il preprocessore per generare codice in modo automatico?
5. Quali sono le limitazioni delle macro ricorsive nel preprocessore C?
6. Come si può utilizzare la direttiva `#pragma` per ottimizzare il codice?
7. Quali sono le applicazioni pratiche della direttiva `#line`?
8. Come si possono combinare gli operatori di stringificazione e concatenazione per creare macro avanzate?