# Campi di Bit ed Enumerazioni in C

In questa sezione, esploreremo due concetti importanti in C che ci permettono di organizzare e rappresentare i dati in modi specifici: i campi di bit e le enumerazioni.

## Campi di Bit

I campi di bit sono membri di strutture o unioni che occupano solo un numero specificato di bit. Sono utili quando si vuole risparmiare memoria o quando si lavora con hardware o protocolli che richiedono una manipolazione a livello di bit.

### Definizione dei Campi di Bit

Per definire un campo di bit, si specifica il tipo (solitamente `unsigned int`) seguito dal nome del membro e dal numero di bit, separati da due punti:

```c
struct [Nome_Struttura] {
    tipo membro_1 : numero_di_bit;
    tipo membro_2 : numero_di_bit;
    /* ... */
};
```

Esempio:

```c
struct Flags {
    unsigned int flag1 : 1;  // 1 bit
    unsigned int flag2 : 1;  // 1 bit
    unsigned int count : 4;  // 4 bit (valori da 0 a 15)
    unsigned int stato : 2;  // 2 bit (valori da 0 a 3)
};
```

In questo esempio, la struttura `Flags` contiene quattro campi di bit che occupano in totale 8 bit (1 byte).

### Accesso ai Campi di Bit

I campi di bit si accedono come normali membri di strutture:

```c
#include <stdio.h>

struct Flags {
    unsigned int flag1 : 1;
    unsigned int flag2 : 1;
    unsigned int count : 4;
    unsigned int stato : 2;
};

int main() {
    struct Flags f = {0}; // Inizializza tutti i bit a 0
    
    f.flag1 = 1;      // Imposta il primo flag
    f.count = 7;      // Imposta count a 7 (0111 in binario)
    f.stato = 2;      // Imposta stato a 2 (10 in binario)
    
    printf("flag1 = %u\n", f.flag1);
    printf("flag2 = %u\n", f.flag2);
    printf("count = %u\n", f.count);
    printf("stato = %u\n", f.stato);
    
    printf("Dimensione della struttura: %zu byte\n", sizeof(struct Flags));
    
    return 0;
}
```

### Limitazioni dei Campi di Bit

1. **Dimensione massima**: Un campo di bit non può essere più grande del tipo di base (solitamente `int`).
2. **Indirizzamento**: Non è possibile prendere l'indirizzo di un campo di bit (`&f.flag1` non è valido).
3. **Ordine dei bit**: L'ordine dei bit all'interno di un byte può variare tra diverse implementazioni.
4. **Allineamento**: Il compilatore può inserire padding tra i campi di bit per ottimizzare l'accesso.

### Casi d'Uso dei Campi di Bit

#### 1. Flags e Stati

I campi di bit sono ideali per rappresentare flag e stati che richiedono solo pochi valori:

```c
#include <stdio.h>

struct FilePermissions {
    unsigned int read : 1;    // Permesso di lettura
    unsigned int write : 1;   // Permesso di scrittura
    unsigned int execute : 1; // Permesso di esecuzione
};

int main() {
    struct FilePermissions perm = {1, 1, 0}; // r+w
    
    printf("Permessi: %c%c%c\n",
           perm.read ? 'r' : '-',
           perm.write ? 'w' : '-',
           perm.execute ? 'x' : '-');
    
    // Modifica dei permessi
    perm.execute = 1;
    
    printf("Nuovi permessi: %c%c%c\n",
           perm.read ? 'r' : '-',
           perm.write ? 'w' : '-',
           perm.execute ? 'x' : '-');
    
    return 0;
}
```

#### 2. Protocolli di Comunicazione

I campi di bit sono utili quando si lavora con protocolli di rete o hardware che definiscono formati di pacchetti specifici:

```c
#include <stdio.h>

// Struttura di un header IPv4 (versione semplificata)
struct IPv4Header {
    unsigned int version : 4;      // Versione IP (4 per IPv4)
    unsigned int ihl : 4;          // Internet Header Length
    unsigned int dscp : 6;         // Differentiated Services Code Point
    unsigned int ecn : 2;          // Explicit Congestion Notification
    unsigned short total_length;   // Lunghezza totale
    // Altri campi...
};

int main() {
    struct IPv4Header header = {0};
    
    header.version = 4;      // IPv4
    header.ihl = 5;          // 5 * 4 = 20 byte (dimensione minima)
    header.dscp = 0;
    header.ecn = 0;
    header.total_length = 1500;
    
    printf("IPv%u Header:\n", header.version);
    printf("Header Length: %u bytes\n", header.ihl * 4);
    printf("Total Length: %u bytes\n", header.total_length);
    
    return 0;
}
```

#### 3. Ottimizzazione della Memoria

I campi di bit possono essere utilizzati per risparmiare memoria quando si hanno molti valori booleani o piccoli numeri interi:

```c
#include <stdio.h>

// Senza campi di bit
struct ConfigSenzaBit {
    int opzione1;  // 4 byte
    int opzione2;  // 4 byte
    int opzione3;  // 4 byte
    int livello;   // 4 byte (valori da 0 a 15)
}; // Totale: 16 byte

// Con campi di bit
struct ConfigConBit {
    unsigned int opzione1 : 1;  // 1 bit
    unsigned int opzione2 : 1;  // 1 bit
    unsigned int opzione3 : 1;  // 1 bit
    unsigned int livello : 4;   // 4 bit
}; // Totale: 1 byte (8 bit)

int main() {
    printf("Dimensione senza campi di bit: %zu byte\n", sizeof(struct ConfigSenzaBit));
    printf("Dimensione con campi di bit: %zu byte\n", sizeof(struct ConfigConBit));
    
    return 0;
}
```

## Enumerazioni

Le enumerazioni sono un modo per definire un insieme di costanti intere con nomi significativi. Rendono il codice più leggibile e manutenibile.

### Definizione di un'Enumerazione

Per definire un'enumerazione, si usa la parola chiave `enum`:

```c
enum [Nome_Enum] {
    COSTANTE_1,
    COSTANTE_2,
    /* ... */
    COSTANTE_N
};
```

Esempio:

```c
enum Giorno {
    LUNEDI,    // 0
    MARTEDI,   // 1
    MERCOLEDI, // 2
    GIOVEDI,   // 3
    VENERDI,   // 4
    SABATO,    // 5
    DOMENICA   // 6
};
```

Per default, il primo valore è 0 e ogni valore successivo è incrementato di 1.

### Assegnazione di Valori Espliciti

È possibile assegnare valori espliciti alle costanti di un'enumerazione:

```c
enum Mese {
    GENNAIO = 1,  // Inizia da 1 invece che da 0
    FEBBRAIO,      // 2
    MARZO,         // 3
    APRILE,        // 4
    MAGGIO,        // 5
    GIUGNO,        // 6
    LUGLIO,        // 7
    AGOSTO,        // 8
    SETTEMBRE,     // 9
    OTTOBRE,       // 10
    NOVEMBRE,      // 11
    DICEMBRE       // 12
};
```

I valori possono anche essere non sequenziali:

```c
enum Codice {
    OK = 0,
    ERROR = -1,
    NOT_FOUND = 404,
    SERVER_ERROR = 500
};
```

### Utilizzo delle Enumerazioni

Le enumerazioni si utilizzano come tipi normali:

```c
#include <stdio.h>

enum Giorno {
    LUNEDI,
    MARTEDI,
    MERCOLEDI,
    GIOVEDI,
    VENERDI,
    SABATO,
    DOMENICA
};

void stampa_giorno(enum Giorno g) {
    switch(g) {
        case LUNEDI: printf("Lunedì\n"); break;
        case MARTEDI: printf("Martedì\n"); break;
        case MERCOLEDI: printf("Mercoledì\n"); break;
        case GIOVEDI: printf("Giovedì\n"); break;
        case VENERDI: printf("Venerdì\n"); break;
        case SABATO: printf("Sabato\n"); break;
        case DOMENICA: printf("Domenica\n"); break;
        default: printf("Giorno non valido\n");
    }
}

int main() {
    enum Giorno oggi = MERCOLEDI;
    enum Giorno domani = GIOVEDI;
    
    printf("Oggi è: ");
    stampa_giorno(oggi);
    
    printf("Domani è: ");
    stampa_giorno(domani);
    
    // Le enumerazioni sono in realtà interi
    printf("LUNEDI = %d, DOMENICA = %d\n", LUNEDI, DOMENICA);
    
    return 0;
}
```

### Enumerazioni e Tipo

In C, le enumerazioni sono essenzialmente interi. Il compilatore tratta le costanti enum come interi e le variabili enum come variabili intere. Tuttavia, forniscono un controllo di tipo più forte rispetto ai semplici `#define`.

```c
#include <stdio.h>

// Definizione con #define
#define ROSSO 0
#define VERDE 1
#define BLU 2

// Definizione con enum
enum Colore {
    ROSSO_ENUM,
    VERDE_ENUM,
    BLU_ENUM
};

void funzione_colore(enum Colore c) {
    // Il compilatore può verificare che c sia un enum Colore
    printf("Colore: %d\n", c);
}

int main() {
    enum Colore c = VERDE_ENUM;
    funzione_colore(c);  // OK
    
    // funzione_colore(VERDE);  // Errore: VERDE non è di tipo enum Colore
    funzione_colore(1);  // Funziona, ma non è type-safe
    
    return 0;
}
```

### Casi d'Uso delle Enumerazioni

#### 1. Stati e Modalità

Le enumerazioni sono ideali per rappresentare stati, modalità o categorie:

```c
#include <stdio.h>

enum StatoConnessione {
    DISCONNESSO,
    CONNESSIONE_IN_CORSO,
    CONNESSO,
    ERRORE_CONNESSIONE
};

void gestisci_connessione(enum StatoConnessione stato) {
    switch(stato) {
        case DISCONNESSO:
            printf("Tentativo di connessione...\n");
            break;
        case CONNESSIONE_IN_CORSO:
            printf("Connessione in corso, attendere...\n");
            break;
        case CONNESSO:
            printf("Connessione stabilita!\n");
            break;
        case ERRORE_CONNESSIONE:
            printf("Errore di connessione. Riprovare.\n");
            break;
    }
}

int main() {
    enum StatoConnessione stato = DISCONNESSO;
    
    gestisci_connessione(stato);
    stato = CONNESSIONE_IN_CORSO;
    gestisci_connessione(stato);
    stato = CONNESSO;
    gestisci_connessione(stato);
    
    return 0;
}
```

#### 2. Codici di Errore

Le enumerazioni sono utili per definire codici di errore o di stato:

```c
#include <stdio.h>

enum CodiceErrore {
    SUCCESS = 0,
    FILE_NOT_FOUND = -1,
    PERMISSION_DENIED = -2,
    OUT_OF_MEMORY = -3,
    INVALID_ARGUMENT = -4
};

enum CodiceErrore apri_file(const char* nome_file) {
    // Simulazione
    if(nome_file == NULL) {
        return INVALID_ARGUMENT;
    }
    
    // Supponiamo che il file non esista
    return FILE_NOT_FOUND;
}

int main() {
    enum CodiceErrore risultato = apri_file("documento.txt");
    
    switch(risultato) {
        case SUCCESS:
            printf("File aperto con successo!\n");
            break;
        case FILE_NOT_FOUND:
            printf("Errore: File non trovato\n");
            break;
        case PERMISSION_DENIED:
            printf("Errore: Permesso negato\n");
            break;
        case OUT_OF_MEMORY:
            printf("Errore: Memoria insufficiente\n");
            break;
        case INVALID_ARGUMENT:
            printf("Errore: Argomento non valido\n");
            break;
    }
    
    return 0;
}
```

#### 3. Opzioni di Menu

Le enumerazioni sono utili per rappresentare opzioni di menu o comandi:

```c
#include <stdio.h>

enum OpzioneMenu {
    NUOVO_FILE = 1,
    APRI_FILE,
    SALVA_FILE,
    CHIUDI_FILE,
    ESCI
};

void esegui_comando(enum OpzioneMenu opzione) {
    switch(opzione) {
        case NUOVO_FILE:
            printf("Creazione di un nuovo file...\n");
            break;
        case APRI_FILE:
            printf("Apertura di un file esistente...\n");
            break;
        case SALVA_FILE:
            printf("Salvataggio del file...\n");
            break;
        case CHIUDI_FILE:
            printf("Chiusura del file...\n");
            break;
        case ESCI:
            printf("Uscita dal programma...\n");
            break;
        default:
            printf("Opzione non valida!\n");
    }
}

int main() {
    int scelta;
    enum OpzioneMenu opzione;
    
    printf("Menu:\n");
    printf("1. Nuovo file\n");
    printf("2. Apri file\n");
    printf("3. Salva file\n");
    printf("4. Chiudi file\n");
    printf("5. Esci\n");
    printf("Scelta: ");
    scanf("%d", &scelta);
    
    if(scelta >= NUOVO_FILE && scelta <= ESCI) {
        opzione = (enum OpzioneMenu)scelta;
        esegui_comando(opzione);
    } else {
        printf("Opzione non valida!\n");
    }
    
    return 0;
}
```

## Combinazione di Campi di Bit ed Enumerazioni

I campi di bit e le enumerazioni possono essere combinati per creare codice più leggibile e compatto:

```c
#include <stdio.h>

// Definizione dei tipi di file
enum TipoFile {
    REGOLARE,
    DIRECTORY,
    LINK_SIMBOLICO,
    DISPOSITIVO_BLOCCO,
    DISPOSITIVO_CARATTERE,
    PIPE,
    SOCKET
};

// Struttura per i permessi di file con campi di bit
struct Permessi {
    unsigned int lettura_utente : 1;
    unsigned int scrittura_utente : 1;
    unsigned int esecuzione_utente : 1;
    unsigned int lettura_gruppo : 1;
    unsigned int scrittura_gruppo : 1;
    unsigned int esecuzione_gruppo : 1;
    unsigned int lettura_altri : 1;
    unsigned int scrittura_altri : 1;
    unsigned int esecuzione_altri : 1;
};

// Struttura per le informazioni di un file
struct InfoFile {
    enum TipoFile tipo;
    struct Permessi permessi;
    unsigned int dimensione;
};

void stampa_permessi(struct Permessi p) {
    printf("%c%c%c%c%c%c%c%c%c\n",
           p.lettura_utente ? 'r' : '-',
           p.scrittura_utente ? 'w' : '-',
           p.esecuzione_utente ? 'x' : '-',
           p.lettura_gruppo ? 'r' : '-',
           p.scrittura_gruppo ? 'w' : '-',
           p.esecuzione_gruppo ? 'x' : '-',
           p.lettura_altri ? 'r' : '-',
           p.scrittura_altri ? 'w' : '-',
           p.esecuzione_altri ? 'x' : '-');
}

int main() {
    struct InfoFile file = {
        .tipo = REGOLARE,
        .permessi = {1, 1, 0, 1, 0, 0, 1, 0, 0},  // rw-r--r--
        .dimensione = 1024
    };
    
    printf("Tipo di file: %d\n", file.tipo);
    printf("Permessi: ");
    stampa_permessi(file.permessi);
    printf("Dimensione: %u byte\n", file.dimensione);
    
    return 0;
}
```

## Best Practices

### Per i Campi di Bit

1. **Documentazione**: Documenta chiaramente il significato di ogni bit.
2. **Portabilità**: Fai attenzione all'ordine dei bit quando lavori con hardware o protocolli specifici.
3. **Dimensione**: Usa campi di bit solo quando è necessario risparmiare memoria o quando lavori con formati specifici.
4. **Tipo unsigned**: Usa sempre tipi `unsigned` per i campi di bit per evitare problemi con il bit di segno.

### Per le Enumerazioni

1. **Nomi significativi**: Usa nomi chiari e descrittivi per le costanti enum.
2. **Valori espliciti**: Assegna valori espliciti quando è importante il valore specifico (es. codici di errore, codici di protocollo).
3. **Prefissi**: Considera l'uso di prefissi per evitare conflitti di nomi (es. `COLOR_RED` invece di `RED`).
4. **Documentazione**: Documenta il significato di ogni valore enum, specialmente se i valori hanno un significato specifico.

## Domande di Autovalutazione

1. Qual è la differenza principale tra un campo di bit e un membro normale di una struttura?
2. Perché non è possibile prendere l'indirizzo di un campo di bit?
3. Quali sono i vantaggi dell'uso delle enumerazioni rispetto ai `#define`?
4. Come si può assegnare un valore specifico a una costante enum?
5. In quali situazioni è preferibile usare campi di bit?

## Esercizi Proposti

1. Crea una struttura con campi di bit per rappresentare i permessi di un file in stile UNIX (rwxrwxrwx).
2. Implementa un'enumerazione per i giorni della settimana e scrivi una funzione che determini se un giorno è feriale o festivo.
3. Crea una struttura per rappresentare un colore RGB usando campi di bit per i componenti rosso, verde e blu (8 bit ciascuno).
4. Implementa un sistema di gestione degli stati di un processo usando enumerazioni e una macchina a stati.

Nel prossimo capitolo, metteremo in pratica tutti i concetti appresi con una serie di esercizi pratici sulle strutture, unioni, campi di bit ed enumerazioni.