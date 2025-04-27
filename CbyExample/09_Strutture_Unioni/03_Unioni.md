# Unioni in C

Le unioni sono un tipo di dato composto in C che, come le strutture, permettono di raggruppare membri di tipi diversi. Tuttavia, a differenza delle strutture, tutti i membri di un'unione condividono lo stesso spazio di memoria. Questo significa che i membri si sovrappongono in memoria e solo uno di essi può contenere un valore valido in un dato momento.

## Definizione di un'Unione

La sintassi per definire un'unione è simile a quella di una struttura, ma si usa la parola chiave `union`:

```c
union [Nome_Unione] {
    tipo_1 membro_1;
    tipo_2 membro_2;
    /* ... */
    tipo_n membro_n;
};
```

Esempio:

```c
union Dato {
    int i;
    float f;
    char str[20];
};
```

In questo esempio, `Dato` è un'unione che può contenere un intero, un float o una stringa, ma solo uno di questi alla volta.

## Dichiarazione di Variabili Unione

Le unioni si dichiarano in modo simile alle strutture:

```c
union Dato dato1, dato2;
```

Oppure con inizializzazione:

```c
union Dato dato1 = {10};  // Inizializza il primo membro (i)
```

È importante notare che si può inizializzare solo il primo membro dell'unione durante la dichiarazione.

## Accesso ai Membri di un'Unione

L'accesso ai membri di un'unione avviene come per le strutture, usando l'operatore punto (`.`) o l'operatore freccia (`->`) per i puntatori:

```c
union Dato dato;

dato.i = 10;
printf("dato.i: %d\n", dato.i);

dato.f = 220.5;
printf("dato.f: %.1f\n", dato.f);

strcpy(dato.str, "C Programming");
printf("dato.str: %s\n", dato.str);
```

In questo esempio, ogni assegnazione sovrascrive il valore precedente, poiché tutti i membri condividono lo stesso spazio di memoria.

## Dimensione di un'Unione

La dimensione di un'unione è determinata dal suo membro più grande, poiché deve essere in grado di contenere qualsiasi membro:

```c
#include <stdio.h>

union Dato {
    int i;        // 4 byte
    float f;      // 4 byte
    char str[20]; // 20 byte
};

int main() {
    union Dato dato;
    
    printf("Dimensione di dato.i: %zu byte\n", sizeof(dato.i));
    printf("Dimensione di dato.f: %zu byte\n", sizeof(dato.f));
    printf("Dimensione di dato.str: %zu byte\n", sizeof(dato.str));
    printf("Dimensione dell'unione Dato: %zu byte\n", sizeof(union Dato));
    
    return 0;
}
```

L'output mostrerà che la dimensione dell'unione è uguale alla dimensione del suo membro più grande (in questo caso, 20 byte per `str`).

## Differenze tra Strutture e Unioni

| Caratteristica | Struttura | Unione |
|----------------|-----------|--------|
| Allocazione memoria | Ogni membro ha il proprio spazio | Tutti i membri condividono lo stesso spazio |
| Dimensione | Somma delle dimensioni dei membri (più padding) | Dimensione del membro più grande |
| Accesso ai membri | Tutti i membri sono validi contemporaneamente | Solo un membro è valido alla volta |
| Uso tipico | Raggruppare dati correlati | Risparmiare memoria o rappresentare dati alternativi |

## Casi d'Uso delle Unioni

### 1. Risparmio di Memoria

Le unioni sono utili quando si ha bisogno di risparmiare memoria e si sa che solo uno dei membri sarà utilizzato alla volta:

```c
#include <stdio.h>

// Definizione di un tipo di veicolo
typedef enum {
    AUTO,
    MOTO,
    CAMION
} TipoVeicolo;

// Informazioni specifiche per ogni tipo di veicolo
union InfoVeicolo {
    struct {
        int numero_porte;
        int cilindrata;
    } auto_info;
    
    struct {
        int cilindrata;
        int ha_sidecar;
    } moto_info;
    
    struct {
        int capacità_carico;
        int numero_assi;
    } camion_info;
};

// Struttura che combina il tipo e le informazioni specifiche
struct Veicolo {
    TipoVeicolo tipo;
    union InfoVeicolo info;
};

int main() {
    struct Veicolo veicolo;
    
    // Inizializzazione di un'auto
    veicolo.tipo = AUTO;
    veicolo.info.auto_info.numero_porte = 4;
    veicolo.info.auto_info.cilindrata = 1600;
    
    // Stampa delle informazioni
    if(veicolo.tipo == AUTO) {
        printf("Auto con %d porte e cilindrata %d cc\n", 
               veicolo.info.auto_info.numero_porte, 
               veicolo.info.auto_info.cilindrata);
    }
    
    // Cambio a moto
    veicolo.tipo = MOTO;
    veicolo.info.moto_info.cilindrata = 750;
    veicolo.info.moto_info.ha_sidecar = 0;
    
    // Stampa delle informazioni
    if(veicolo.tipo == MOTO) {
        printf("Moto con cilindrata %d cc%s\n", 
               veicolo.info.moto_info.cilindrata, 
               veicolo.info.moto_info.ha_sidecar ? " e sidecar" : "");
    }
    
    return 0;
}
```

### 2. Interpretazione dei Dati in Modi Diversi

Le unioni permettono di interpretare lo stesso dato in modi diversi:

```c
#include <stdio.h>

union Conversione {
    int i;
    float f;
    unsigned char bytes[4];
};

int main() {
    union Conversione conv;
    int i;
    
    conv.i = 1234567890;
    
    printf("Intero: %d\n", conv.i);
    printf("Float: %f\n", conv.f);  // Interpretazione come float
    printf("Bytes: ");
    for(i = 0; i < 4; i++) {
        printf("%02X ", conv.bytes[i]);  // Interpretazione come bytes
    }
    printf("\n");
    
    return 0;
}
```

Questo esempio mostra come lo stesso spazio di memoria possa essere interpretato come un intero, un float o un array di byte.

### 3. Comunicazione con Hardware o Protocolli

Le unioni sono spesso utilizzate per la comunicazione con hardware o protocolli di rete, dove i dati possono avere interpretazioni diverse:

```c
#include <stdio.h>

// Rappresentazione di un pacchetto di rete
union Pacchetto {
    struct {
        unsigned char versione : 4;
        unsigned char ihl : 4;
        unsigned char dscp : 6;
        unsigned char ecn : 2;
        unsigned short lunghezza_totale;
        // Altri campi...
    } header;
    
    unsigned char bytes[20];  // Rappresentazione grezza
};

int main() {
    union Pacchetto pkt;
    int i;
    
    // Inizializzazione tramite campi strutturati
    pkt.header.versione = 4;      // IPv4
    pkt.header.ihl = 5;           // 5 * 4 = 20 byte
    pkt.header.dscp = 0;
    pkt.header.ecn = 0;
    pkt.header.lunghezza_totale = 1500;
    
    // Stampa come bytes
    printf("Pacchetto come bytes: ");
    for(i = 0; i < 4; i++) {
        printf("%02X ", pkt.bytes[i]);
    }
    printf("...\n");
    
    return 0;
}
```

## Unioni Anonime

C99 introduce il concetto di unioni anonime, che possono essere utilizzate all'interno di strutture per accedere direttamente ai membri dell'unione:

```c
#include <stdio.h>

struct Valore {
    int tipo;  // 0 per int, 1 per float
    
    union {    // Unione anonima
        int i;
        float f;
    };
};

int main() {
    struct Valore val;
    
    val.tipo = 0;
    val.i = 42;  // Accesso diretto al membro dell'unione
    
    printf("Valore (int): %d\n", val.i);
    
    val.tipo = 1;
    val.f = 3.14;  // Accesso diretto al membro dell'unione
    
    printf("Valore (float): %.2f\n", val.f);
    
    return 0;
}
```

In questo esempio, i membri dell'unione anonima possono essere acceduti direttamente come se fossero membri della struttura.

## Best Practices

1. **Tracciamento del tipo**: Mantieni sempre traccia di quale membro dell'unione è attualmente valido, spesso usando un campo aggiuntivo in una struttura.
2. **Documentazione**: Documenta chiaramente lo scopo dell'unione e quando ogni membro dovrebbe essere utilizzato.
3. **Evita confusione**: Non accedere a un membro dopo aver scritto in un altro, a meno che non sia intenzionale (come nella conversione di tipi).
4. **Allineamento**: Considera l'allineamento dei membri per garantire un accesso efficiente.

## Domande di Autovalutazione

1. Qual è la principale differenza tra una struttura e un'unione?
2. Come viene determinata la dimensione di un'unione?
3. Perché è importante tenere traccia di quale membro di un'unione è attualmente valido?
4. In quali situazioni è preferibile usare un'unione invece di una struttura?
5. Cosa sono le unioni anonime e quando sono utili?

## Esercizi Proposti

1. Crea un'unione che possa rappresentare un numero in formato decimale, esadecimale o come stringa.
2. Implementa un sistema di gestione di diversi tipi di forme geometriche (cerchio, rettangolo, triangolo) usando una struttura con un campo tipo e un'unione per i dati specifici di ogni forma.
3. Scrivi un programma che utilizzi un'unione per convertire tra diversi tipi di dati (int, float, char).
4. Implementa un parser semplice che possa interpretare valori come numeri o stringhe usando un'unione.

Nel prossimo capitolo, esploreremo i campi di bit e le enumerazioni, che sono altri strumenti utili per organizzare e rappresentare i dati in C.