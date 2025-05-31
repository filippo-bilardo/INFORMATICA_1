# Campi di Bit ed Enumerazioni in C

## Campi di Bit

### Cos'è un Campo di Bit?

Un **campo di bit** in C è un membro di una struttura o unione a cui viene assegnato un numero specifico di bit. I campi di bit permettono di ottimizzare lo spazio di memoria quando si lavora con valori che richiedono solo pochi bit, come flag, stati o piccoli interi.

I campi di bit possono essere dichiarati solo all'interno di strutture o unioni e devono essere di tipo intero (`int`, `unsigned int`, `signed int`, ecc.).

### Sintassi

```c
struct NomeStruttura {
    tipo nome_campo : numero_di_bit;
};
```

Dove `numero_di_bit` specifica quanti bit allocare per il campo.

### Esempio

```c
struct Flags {
    unsigned int attivo : 1;     // 1 bit per un flag booleano
    unsigned int pronto : 1;     // 1 bit per un altro flag
    unsigned int priorita : 3;   // 3 bit per un valore da 0 a 7
};
```

In questo esempio, la struttura `Flags` contiene tre campi di bit che occupano in totale solo 5 bit. Tuttavia, la dimensione effettiva della struttura dipenderà dall'implementazione del compilatore e dall'allineamento dei dati.

### Utilizzo dei Campi di Bit

```c
#include <stdio.h>

int main() {
    struct Flags {
        unsigned int attivo : 1;
        unsigned int pronto : 1;
        unsigned int priorita : 3;
    };
    
    struct Flags flag = {1, 0, 5};  // attivo=1, pronto=0, priorita=5
    
    printf("Attivo: %d\n", flag.attivo);
    printf("Pronto: %d\n", flag.pronto);
    printf("Priorità: %d\n", flag.priorita);
    
    // Modifica dei campi
    flag.attivo = 0;
    flag.priorita = 7;  // Il valore massimo per 3 bit è 7 (111 in binario)
    
    printf("\nDopo la modifica:\n");
    printf("Attivo: %d\n", flag.attivo);
    printf("Pronto: %d\n", flag.pronto);
    printf("Priorità: %d\n", flag.priorita);
    
    // Tentativo di assegnare un valore troppo grande
    flag.priorita = 10;  // Questo valore è troppo grande per 3 bit
    printf("Priorità dopo assegnazione di 10: %d\n", flag.priorita);  // Il risultato sarà 2 (10 in binario)
    
    return 0;
}
```

### Limitazioni dei Campi di Bit

1. Non è possibile prendere l'indirizzo di un campo di bit usando l'operatore `&`.
2. I campi di bit non possono essere di tipo array.
3. L'ordine dei bit all'interno di una parola di memoria è dipendente dall'implementazione (endianness).
4. La dimensione massima di un campo di bit è generalmente la dimensione del tipo di base (ad esempio, 32 bit per `int` su molte piattaforme).

### Campi di Bit Senza Nome

È possibile dichiarare campi di bit senza nome per creare spazi vuoti o per allineare i campi successivi.

```c
struct Allineamento {
    unsigned int flag1 : 1;
    unsigned int : 2;        // 2 bit non utilizzati
    unsigned int flag2 : 1;
};
```

### Campi di Bit di Dimensione Zero

Un campo di bit di dimensione zero forza l'allineamento del campo successivo al confine della prossima unità di memorizzazione.

```c
struct Allineamento {
    unsigned int flag1 : 1;
    unsigned int : 0;        // Forza l'allineamento al prossimo int
    unsigned int flag2 : 1;
};
```

## Enumerazioni

### Cos'è un'Enumerazione?

Un'**enumerazione** in C è un tipo di dato definito dall'utente che consiste in un insieme di costanti intere con nomi simbolici. Le enumerazioni rendono il codice più leggibile e manutenibile, fornendo nomi significativi a valori che altrimenti sarebbero semplici numeri.

### Sintassi

```c
enum NomeEnum {
    COSTANTE1,
    COSTANTE2,
    // ...
    COSTANTEN
};
```

Per default, il primo enumeratore ha valore 0, e ogni enumeratore successivo ha un valore incrementato di 1 rispetto al precedente. È possibile assegnare valori espliciti agli enumeratori.

### Esempio

```c
enum Giorno {
    LUNEDI,     // 0
    MARTEDI,    // 1
    MERCOLEDI,  // 2
    GIOVEDI,    // 3
    VENERDI,    // 4
    SABATO,     // 5
    DOMENICA    // 6
};
```

### Assegnazione di Valori Espliciti

```c
enum Mese {
    GENNAIO = 1,  // 1
    FEBBRAIO,     // 2
    MARZO,        // 3
    // ...
    DICEMBRE      // 12
};
```

È possibile assegnare lo stesso valore a più enumeratori.

```c
enum Booleano {
    FALSO = 0,
    NO = 0,
    VERO = 1,
    SI = 1
};
```

### Utilizzo delle Enumerazioni

```c
#include <stdio.h>

int main() {
    enum Giorno {
        LUNEDI,
        MARTEDI,
        MERCOLEDI,
        GIOVEDI,
        VENERDI,
        SABATO,
        DOMENICA
    };
    
    enum Giorno oggi = MERCOLEDI;
    
    printf("Oggi è il giorno %d\n", oggi);
    
    // Le enumerazioni possono essere usate in istruzioni di controllo
    if (oggi == SABATO || oggi == DOMENICA) {
        printf("È weekend!\n");
    } else {
        printf("Non è ancora weekend...\n");
    }
    
    // Le enumerazioni sono compatibili con i tipi interi
    oggi = 5;  // Equivalente a SABATO
    printf("Ora oggi è il giorno %d\n", oggi);
    
    return 0;
}
```

### Enumerazioni e Typedef

Come per le strutture e le unioni, è comune utilizzare `typedef` con le enumerazioni per creare un nuovo nome di tipo.

```c
typedef enum {
    LUNEDI,
    MARTEDI,
    MERCOLEDI,
    GIOVEDI,
    VENERDI,
    SABATO,
    DOMENICA
} Giorno;

// Ora possiamo dichiarare variabili senza usare la parola chiave 'enum'
Giorno oggi = MERCOLEDI;
```

### Dimensione delle Enumerazioni

La dimensione di un'enumerazione è generalmente la dimensione di un `int`, ma può variare a seconda dell'implementazione del compilatore.

```c
#include <stdio.h>

int main() {
    enum Giorno {
        LUNEDI,
        MARTEDI,
        MERCOLEDI,
        GIOVEDI,
        VENERDI,
        SABATO,
        DOMENICA
    };
    
    printf("Dimensione di enum Giorno: %zu byte\n", sizeof(enum Giorno));
    printf("Dimensione di int: %zu byte\n", sizeof(int));
    
    return 0;
}
```

## Combinazione di Campi di Bit ed Enumerazioni

I campi di bit e le enumerazioni possono essere combinati per creare codice più leggibile e efficiente in termini di memoria.

```c
#include <stdio.h>

typedef enum {
    BASSA,
    MEDIA,
    ALTA
} Priorita;

struct Attivita {
    unsigned int completata : 1;
    unsigned int priorita : 2;  // Può contenere i valori dell'enum Priorita
};

int main() {
    struct Attivita compito = {0, ALTA};
    
    printf("Completata: %s\n", compito.completata ? "Sì" : "No");
    printf("Priorità: ");
    
    switch (compito.priorita) {
        case BASSA:
            printf("Bassa\n");
            break;
        case MEDIA:
            printf("Media\n");
            break;
        case ALTA:
            printf("Alta\n");
            break;
    }
    
    return 0;
}
```

## Conclusione

I campi di bit e le enumerazioni sono strumenti potenti in C che permettono di scrivere codice più leggibile, manutenibile ed efficiente in termini di memoria.

I campi di bit sono particolarmente utili quando si lavora con hardware o protocolli di comunicazione dove ogni bit può avere un significato specifico, mentre le enumerazioni sono ideali per rappresentare un insieme finito di valori con nomi simbolici.

Entrambi questi strumenti contribuiscono a rendere il codice C più espressivo e meno soggetto a errori.

## Esercizi

1. Definisci una struttura `PixelRGB` che utilizzi campi di bit per rappresentare i componenti rosso, verde e blu di un pixel, allocando 8 bit per ciascun componente.

2. Crea un'enumerazione `StatoFile` con valori per rappresentare diversi stati di un file (aperto, chiuso, in lettura, in scrittura, ecc.). Scrivi una funzione che accetti uno `StatoFile` come parametro e stampi una descrizione testuale dello stato.

3. Implementa una struttura `Permessi` che utilizzi campi di bit per rappresentare i permessi di un file in stile Unix (lettura, scrittura, esecuzione per proprietario, gruppo e altri). Scrivi funzioni per impostare e verificare i permessi.

4. Crea un'enumerazione `TipoVeicolo` e una struttura `Veicolo` che includa il tipo di veicolo e altre informazioni come marca, modello e anno. Scrivi una funzione che stampi le informazioni del veicolo in un formato appropriato in base al tipo.

5. Implementa una struttura `DataOra` che utilizzi campi di bit per rappresentare giorno (5 bit), mese (4 bit), anno (12 bit), ore (5 bit), minuti (6 bit) e secondi (6 bit). Scrivi funzioni per impostare e ottenere i vari componenti della data e dell'ora.