# Introduzione alle Unioni in C

## Cos'è un'Unione?

Un'unione in C è un tipo di dato speciale che permette di memorizzare diversi tipi di dati nella stessa area di memoria. A differenza delle strutture, dove ogni membro ha la propria area di memoria dedicata, in un'unione tutti i membri condividono la stessa area di memoria.

Questo significa che un'unione può contenere un solo valore alla volta, e questo valore può essere interpretato come uno qualsiasi dei tipi di dati dichiarati nell'unione.

## Dichiarazione di un'Unione

La sintassi per dichiarare un'unione è simile a quella delle strutture:

```c
union nome_unione {
    tipo_1 membro_1;
    tipo_2 membro_2;
    // ...
    tipo_n membro_n;
};
```

Esempio di un'unione che può contenere diversi tipi di dati numerici:

```c
union Numero {
    int intero;
    float reale;
    double precisione_doppia;
};
```

## Dimensione di un'Unione

La dimensione di un'unione è determinata dal membro con la dimensione maggiore. Questo perché l'unione deve essere abbastanza grande da contenere qualsiasi dei suoi membri.

```c
union Esempio {
    char c;       // 1 byte
    int i;        // 4 byte
    double d;     // 8 byte
};
// La dimensione dell'unione sarà 8 byte (la dimensione del double)
```

## Definizione di Variabili Unione

Dopo aver dichiarato un'unione, è possibile definire variabili di quel tipo in diversi modi:

### 1. Definizione dopo la dichiarazione dell'unione

```c
union Numero num1, num2;
```

### 2. Definizione e dichiarazione contemporanea

```c
union Numero {
    int intero;
    float reale;
    double precisione_doppia;
} num1, num2;
```

### 3. Definizione con inizializzazione

```c
union Numero num1 = {42}; // Inizializza il primo membro (intero)
```

## Accesso ai Membri di un'Unione

Per accedere ai membri di un'unione, si utilizza l'operatore punto (`.`) o l'operatore freccia (`->`) per i puntatori, proprio come con le strutture:

```c
union Numero num1;

num1.intero = 42;
// Ora num1.intero contiene 42, ma num1.reale e num1.precisione_doppia
// contengono valori non definiti se interpretati come float o double

printf("%d\n", num1.intero);  // Stampa 42

num1.reale = 3.14;
// Ora num1.reale contiene 3.14, ma num1.intero e num1.precisione_doppia
// non contengono più valori validi se interpretati come int o double

printf("%f\n", num1.reale);  // Stampa 3.14
```

## Casi d'Uso delle Unioni

### 1. Risparmio di memoria

Le unioni sono utili quando si ha bisogno di memorizzare uno di diversi tipi di dati, ma non tutti contemporaneamente, risparmiando così memoria.

### 2. Tipi di dati varianti

Spesso le unioni vengono utilizzate insieme alle strutture per creare "tipi varianti", dove un campo della struttura indica quale membro dell'unione è attualmente valido:

```c
enum TipoDato { INTERO, REALE, STRINGA };

struct Variante {
    enum TipoDato tipo;
    union {
        int i;
        float f;
        char* s;
    } valore;
};

struct Variante v;
v.tipo = INTERO;
v.valore.i = 42;

// Uso sicuro dell'unione
if (v.tipo == INTERO) {
    printf("Valore intero: %d\n", v.valore.i);
}
```

### 3. Interpretazione dei dati in modi diversi

Le unioni permettono di interpretare lo stesso dato in modi diversi senza conversioni esplicite:

```c
union Conversione {
    int i;
    float f;
};

union Conversione conv;
conv.i = 0x40490FDB; // Rappresentazione esadecimale di 3.14159 in IEEE 754
printf("%f\n", conv.f); // Stampa 3.14159
```

## Limitazioni e Considerazioni

1. **Sicurezza dei tipi**: L'uso delle unioni può portare a errori difficili da individuare se non si tiene traccia di quale membro è attualmente valido.

2. **Portabilità**: L'interpretazione dei bit può variare tra diverse architetture e compilatori.

3. **Aliasing**: L'accesso a un membro di un'unione dopo aver scritto in un altro membro può causare problemi di aliasing e comportamenti non definiti in alcune situazioni.

## Unioni Anonime (C11)

A partire dallo standard C11, è possibile dichiarare unioni anonime all'interno di strutture, semplificando l'accesso ai membri:

```c
struct Dato {
    enum TipoDato tipo;
    union { // Unione anonima
        int i;
        float f;
        char* s;
    }; // Nessun nome per l'unione
};

struct Dato d;
d.tipo = INTERO;
d.i = 42; // Accesso diretto al membro dell'unione anonima
```

## Esercizi Proposti

1. Crea un'unione che possa contenere un intero, un float e un carattere. Scrivi un programma che mostri come i valori si sovrappongono in memoria.

2. Implementa una struttura `Variante` che possa contenere diversi tipi di dati (int, float, char*, bool) con un campo che indica il tipo attualmente memorizzato.

3. Crea un'unione per convertire tra diversi tipi di dati numerici senza usare cast espliciti.

4. Implementa una funzione che utilizzi un'unione per esaminare la rappresentazione in memoria di un float (segno, esponente, mantissa).

5. Crea una struttura dati per un sistema di messaggistica che utilizzi un'unione per rappresentare diversi tipi di messaggi (testo, immagine, audio) in modo efficiente.