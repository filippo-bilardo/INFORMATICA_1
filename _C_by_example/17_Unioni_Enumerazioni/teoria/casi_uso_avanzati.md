# Casi d'Uso Avanzati di Unioni ed Enumerazioni in C

## Combinazione di Unioni e Strutture

Una delle applicazioni più potenti delle unioni in C è la loro combinazione con le strutture per creare tipi di dati varianti. Questo pattern è particolarmente utile quando si ha bisogno di gestire dati di tipi diversi in modo uniforme.

### Tipi di Dati Varianti

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Enumerazione per identificare il tipo di dato
enum TipoDato {
    INTERO,
    FLOAT,
    STRINGA
};

// Struttura con un'unione per rappresentare diversi tipi di dati
struct Variante {
    enum TipoDato tipo;
    union {
        int i;
        float f;
        char* s;
    } valore;
};

// Funzione per creare una variante di tipo intero
struct Variante crea_intero(int val) {
    struct Variante v;
    v.tipo = INTERO;
    v.valore.i = val;
    return v;
}

// Funzione per creare una variante di tipo float
struct Variante crea_float(float val) {
    struct Variante v;
    v.tipo = FLOAT;
    v.valore.f = val;
    return v;
}

// Funzione per creare una variante di tipo stringa
struct Variante crea_stringa(const char* val) {
    struct Variante v;
    v.tipo = STRINGA;
    v.valore.s = strdup(val); // Alloca memoria per la stringa
    return v;
}

// Funzione per stampare una variante
void stampa_variante(struct Variante v) {
    switch (v.tipo) {
        case INTERO:
            printf("Intero: %d\n", v.valore.i);
            break;
        case FLOAT:
            printf("Float: %f\n", v.valore.f);
            break;
        case STRINGA:
            printf("Stringa: %s\n", v.valore.s);
            break;
        default:
            printf("Tipo sconosciuto\n");
    }
}

// Funzione per liberare la memoria allocata (se necessario)
void libera_variante(struct Variante* v) {
    if (v->tipo == STRINGA && v->valore.s != NULL) {
        free(v->valore.s);
        v->valore.s = NULL;
    }
}
```

Questo pattern è molto utile per implementare strutture dati eterogenee come liste o alberi che possono contenere elementi di tipi diversi.

## Unioni Anonime

In C11, è possibile utilizzare unioni anonime all'interno di strutture, il che può rendere il codice più pulito:

```c
struct Variante {
    enum TipoDato tipo;
    union { // Unione anonima
        int i;
        float f;
        char* s;
    }; // Nessun nome per l'unione
};

// Utilizzo
struct Variante v;
v.tipo = INTERO;
v.i = 42; // Accesso diretto senza il nome dell'unione
```

## Enumerazioni come Generatori di Costanti

Le enumerazioni possono essere utilizzate per generare sequenze di costanti correlate:

```c
enum PorteServizi {
    PORTA_FTP = 21,
    PORTA_SSH = 22,
    PORTA_TELNET = 23,
    PORTA_SMTP = 25,
    PORTA_DNS = 53,
    PORTA_HTTP = 80,
    PORTA_HTTPS = 443
};
```

## Enumerazioni per Macchine a Stati

Le enumerazioni sono ideali per implementare macchine a stati finiti:

```c
#include <stdio.h>

enum StatoConnessione {
    DISCONNESSO,
    CONNESSIONE_IN_CORSO,
    CONNESSO,
    DISCONNESSIONE_IN_CORSO,
    ERRORE
};

void gestisci_stato(enum StatoConnessione stato) {
    switch (stato) {
        case DISCONNESSO:
            printf("Tentativo di connessione...\n");
            // Logica per iniziare la connessione
            break;
        case CONNESSIONE_IN_CORSO:
            printf("Connessione in corso...\n");
            // Logica per verificare lo stato della connessione
            break;
        case CONNESSO:
            printf("Connesso. Inizio trasmissione dati...\n");
            // Logica per la trasmissione dati
            break;
        case DISCONNESSIONE_IN_CORSO:
            printf("Disconnessione in corso...\n");
            // Logica per completare la disconnessione
            break;
        case ERRORE:
            printf("Errore di connessione. Riavvio procedura...\n");
            // Logica per gestire l'errore
            break;
    }
}
```

## Unioni per Manipolazione di Bit

Le unioni possono essere utilizzate per manipolare i bit di un valore senza ricorrere a operazioni bit a bit esplicite:

```c
#include <stdio.h>

union IntBytes {
    int valore;
    unsigned char bytes[sizeof(int)];
};

int main() {
    union IntBytes ib;
    ib.valore = 0x12345678; // Un valore esadecimale
    
    printf("Valore intero: 0x%X\n", ib.valore);
    printf("Bytes individuali: ");
    
    // Stampa i singoli byte (l'ordine dipende dall'endianness del sistema)
    for (size_t i = 0; i < sizeof(int); i++) {
        printf("0x%02X ", ib.bytes[i]);
    }
    printf("\n");
    
    // Modifica un singolo byte
    ib.bytes[0] = 0xFF;
    printf("Valore dopo la modifica: 0x%X\n", ib.valore);
    
    return 0;
}
```

Questo esempio mostra anche come le unioni possano essere utilizzate per determinare l'endianness (little-endian o big-endian) del sistema.

## Enumerazioni con Valori Espliciti per Protocolli

Quando si lavora con protocolli di comunicazione o formati di file, è comune utilizzare enumerazioni con valori espliciti per rappresentare tipi di messaggi o formati:

```c
enum TipoMessaggio {
    MSG_HELLO = 0x01,
    MSG_ACK = 0x02,
    MSG_DATA = 0x10,
    MSG_ERROR = 0xFF
};

void invia_messaggio(enum TipoMessaggio tipo, const void* dati, size_t lunghezza) {
    // Il primo byte del messaggio è il tipo
    unsigned char header = (unsigned char)tipo;
    
    // Invia l'header seguito dai dati
    // ...
}
```

## Unioni per Conversione di Tipi

Le unioni possono essere utilizzate per convertire tra tipi di dati senza cast espliciti:

```c
#include <stdio.h>

union Conversione {
    int i;
    float f;
};

int main() {
    union Conversione conv;
    
    // Converti da float a rappresentazione intera
    conv.f = 3.14159f;
    printf("Float: %f, Rappresentazione intera: 0x%X\n", conv.f, conv.i);
    
    // Converti da rappresentazione intera a float
    conv.i = 0x40490FDB; // Rappresentazione IEEE 754 di π
    printf("Rappresentazione intera: 0x%X, Float: %f\n", conv.i, conv.f);
    
    return 0;
}
```

## Enumerazioni come Set di Flags

Le enumerazioni possono essere utilizzate per definire set di flags che possono essere combinati con operazioni bit a bit:

```c
#include <stdio.h>

enum Permessi {
    NESSUNO = 0,
    LETTURA = 1 << 0,     // 0001
    SCRITTURA = 1 << 1,   // 0010
    ESECUZIONE = 1 << 2,  // 0100
    TUTTI = LETTURA | SCRITTURA | ESECUZIONE // 0111
};

void imposta_permessi(const char* file, int permessi) {
    printf("Impostazione permessi per %s:\n", file);
    
    if (permessi & LETTURA) {
        printf("- Lettura\n");
    }
    
    if (permessi & SCRITTURA) {
        printf("- Scrittura\n");
    }
    
    if (permessi & ESECUZIONE) {
        printf("- Esecuzione\n");
    }
    
    if (permessi == NESSUNO) {
        printf("- Nessun permesso\n");
    }
}

int main() {
    // Combinazione di flags
    int perm_file1 = LETTURA | SCRITTURA;
    int perm_file2 = TUTTI;
    int perm_file3 = NESSUNO;
    
    imposta_permessi("documento.txt", perm_file1);
    imposta_permessi("programma.exe", perm_file2);
    imposta_permessi("file_protetto.dat", perm_file3);
    
    return 0;
}
```

## Considerazioni sulla Sicurezza e Best Practices

### Per le Unioni

1. **Tracciamento del Tipo**: Quando si utilizzano unioni, è fondamentale tenere traccia del tipo di dato attualmente memorizzato, tipicamente con un campo enum aggiuntivo.

2. **Gestione della Memoria**: Prestare particolare attenzione quando l'unione contiene puntatori o strutture che richiedono una gestione esplicita della memoria.

3. **Portabilità**: L'uso di unioni per manipolare i bit o per conversioni di tipo può non essere portabile tra diverse architetture.

4. **Allineamento**: Essere consapevoli dei requisiti di allineamento dei diversi tipi di dati all'interno dell'unione.

### Per le Enumerazioni

1. **Valori Espliciti**: Quando l'ordine o i valori specifici sono importanti (ad esempio, per protocolli o interfacce esterne), assegnare sempre valori espliciti agli enumeratori.

2. **Documentazione**: Documentare chiaramente il significato di ogni enumeratore, specialmente quando vengono utilizzati come flags.

3. **Controllo di Validità**: Verificare sempre che i valori enum siano validi prima di utilizzarli, poiché in C è possibile assegnare qualsiasi valore intero a una variabile enum.

4. **Prefissi**: Utilizzare prefissi per gli enumeratori per evitare collisioni di nomi in ambiti globali.

## Esercizi Avanzati

1. Implementa un sistema di serializzazione/deserializzazione che possa gestire diversi tipi di dati utilizzando unioni ed enumerazioni.

2. Crea una macchina a stati finiti per un semplice protocollo di comunicazione utilizzando enumerazioni per gli stati e i tipi di messaggi.

3. Implementa un parser di comandi che utilizzi enumerazioni per i tipi di comandi e unioni per i parametri dei comandi.

4. Sviluppa una libreria per la manipolazione di colori che utilizzi un'unione per rappresentare colori in diversi formati (RGB, HSL, CMYK) con un enum per indicare il formato corrente.

5. Crea un sistema di logging configurabile che utilizzi enumerazioni come flags per controllare quali tipi di messaggi vengono registrati e dove vengono inviati.