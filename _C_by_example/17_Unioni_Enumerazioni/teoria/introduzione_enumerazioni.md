# Introduzione alle Enumerazioni in C

## Cos'è un'Enumerazione?

Un'enumerazione (o enum) in C è un tipo di dato definito dall'utente che consiste in un insieme di costanti integrali denominate. Le enumerazioni forniscono un modo per definire e raggruppare costanti correlate, migliorando la leggibilità e la manutenibilità del codice.

Le enumerazioni sono particolarmente utili quando si ha bisogno di rappresentare un insieme finito di valori distinti, come giorni della settimana, mesi dell'anno, stati di un sistema, opzioni di configurazione, ecc.

## Dichiarazione di un'Enumerazione

La sintassi per dichiarare un'enumerazione è la seguente:

```c
enum nome_enumerazione {
    enumeratore_1,
    enumeratore_2,
    // ...
    enumeratore_n
};
```

Esempio di un'enumerazione per i giorni della settimana:

```c
enum Giorno {
    LUNEDI,
    MARTEDI,
    MERCOLEDI,
    GIOVEDI,
    VENERDI,
    SABATO,
    DOMENICA
};
```

## Assegnazione di Valori agli Enumeratori

Per default, il primo enumeratore ha valore 0, e ogni enumeratore successivo ha un valore incrementato di 1 rispetto al precedente. Tuttavia, è possibile assegnare valori espliciti agli enumeratori:

```c
enum Mese {
    GENNAIO = 1,  // Inizia da 1 invece che da 0
    FEBBRAIO,      // Automaticamente 2
    MARZO,         // Automaticamente 3
    APRILE,
    MAGGIO,
    GIUGNO,
    LUGLIO,
    AGOSTO,
    SETTEMBRE,
    OTTOBRE,
    NOVEMBRE,
    DICEMBRE
};
```

È anche possibile assegnare lo stesso valore a più enumeratori o valori non sequenziali:

```c
enum Stato {
    INATTIVO = 0,
    ATTIVO = 1,
    IN_PAUSA = 1,  // Stesso valore di ATTIVO
    ERRORE = 10,   // Salto a 10
    CRITICO = 20   // Salto a 20
};
```

## Definizione di Variabili Enum

Dopo aver dichiarato un'enumerazione, è possibile definire variabili di quel tipo:

```c
enum Giorno oggi;
today = LUNEDI;
```

È anche possibile combinare la dichiarazione dell'enumerazione con la definizione di variabili:

```c
enum Giorno {
    LUNEDI,
    MARTEDI,
    MERCOLEDI,
    GIOVEDI,
    VENERDI,
    SABATO,
    DOMENICA
} oggi, domani;
```

## Enumerazioni e Tipi Interi

In C, le enumerazioni sono essenzialmente tipi interi. Gli enumeratori sono costanti intere, e le variabili enum possono contenere qualsiasi valore intero, non solo quelli definiti nell'enumerazione:

```c
enum Booleano { FALSO, VERO };

enum Booleano b = VERO;   // OK
b = 42;                   // Legale in C, ma non consigliato
```

Questo significa che è possibile eseguire operazioni aritmetiche sulle variabili enum, anche se questo può portare a valori che non corrispondono a nessun enumeratore definito.

## Dimensione di un'Enumerazione

La dimensione di un'enumerazione dipende dall'implementazione, ma è generalmente la stessa di un int. Lo standard C garantisce che un'enumerazione sia abbastanza grande da contenere tutti i valori enumerati.

## Vantaggi delle Enumerazioni

1. **Leggibilità del Codice**: Le enumerazioni rendono il codice più leggibile usando nomi significativi invece di numeri magici.

2. **Manutenibilità**: Se è necessario modificare il valore di una costante, è sufficiente cambiarlo nella dichiarazione dell'enumerazione.

3. **Documentazione**: Le enumerazioni documentano le possibili opzioni o stati direttamente nel codice.

4. **Controllo del Compilatore**: Alcune implementazioni del compilatore possono fornire controlli aggiuntivi quando si usano enumerazioni.

## Enumerazioni vs #define

Le enumerazioni offrono diversi vantaggi rispetto all'uso di #define per definire costanti:

1. Le enumerazioni hanno un ambito (scope) e seguono le regole di visibilità del C.

2. Gli enumeratori possono essere utilizzati dal debugger, mentre le costanti #define vengono sostituite dal preprocessore prima della compilazione.

3. Le enumerazioni raggruppano logicamente costanti correlate.

## Esempi di Utilizzo

### Esempio 1: Menu di Opzioni

```c
#include <stdio.h>

enum Opzione {
    ESCI,
    APRI_FILE,
    SALVA_FILE,
    MODIFICA_TESTO
};

int main() {
    enum Opzione scelta;
    
    printf("Seleziona un'opzione (0-3): ");
    scanf("%d", (int*)&scelta);
    
    switch (scelta) {
        case ESCI:
            printf("Uscita dal programma...\n");
            break;
        case APRI_FILE:
            printf("Apertura file...\n");
            break;
        case SALVA_FILE:
            printf("Salvataggio file...\n");
            break;
        case MODIFICA_TESTO:
            printf("Modifica testo...\n");
            break;
        default:
            printf("Opzione non valida!\n");
    }
    
    return 0;
}
```

### Esempio 2: Flags e Bitwise Operations

```c
#include <stdio.h>

enum Flag {
    NESSUNO = 0,
    LETTURA = 1,        // 001 in binario
    SCRITTURA = 2,      // 010 in binario
    ESECUZIONE = 4      // 100 in binario
};

int main() {
    int permessi = LETTURA | SCRITTURA;  // Combinazione di flags: 011 in binario
    
    if (permessi & LETTURA) {
        printf("Permesso di lettura attivo\n");
    }
    
    if (permessi & SCRITTURA) {
        printf("Permesso di scrittura attivo\n");
    }
    
    if (permessi & ESECUZIONE) {
        printf("Permesso di esecuzione attivo\n");
    }
    
    return 0;
}
```

## Limitazioni delle Enumerazioni in C

1. **Nessun Controllo di Tipo Forte**: In C, le enumerazioni non sono tipi fortemente tipizzati. È possibile assegnare qualsiasi valore intero a una variabile enum.

2. **Nessuna Iterazione Integrata**: Non esiste un modo integrato per iterare attraverso tutti i valori di un'enumerazione.

3. **Nessuna Conversione da Stringa**: Non c'è un meccanismo integrato per convertire stringhe nei corrispondenti valori enum.

## Esercizi Proposti

1. Crea un'enumerazione per rappresentare i colori di base (ROSSO, VERDE, BLU, ecc.) e scrivi una funzione che prenda un colore come parametro e restituisca il suo nome come stringa.

2. Implementa un'enumerazione per rappresentare le direzioni (NORD, EST, SUD, OVEST) e scrivi una funzione che simuli il movimento in una griglia 2D basato sulla direzione.

3. Crea un'enumerazione per i livelli di log (DEBUG, INFO, WARNING, ERROR, CRITICAL) e implementa una funzione di logging che filtri i messaggi in base al livello corrente.

4. Implementa un sistema di flags usando un'enumerazione per rappresentare diverse opzioni di configurazione che possono essere combinate.

5. Crea un'enumerazione per rappresentare le carte da gioco (ASSO, DUE, ..., RE) e un'altra per i semi (CUORI, QUADRI, FIORI, PICCHE). Usa queste enumerazioni per implementare una semplice funzione che generi un mazzo di carte.