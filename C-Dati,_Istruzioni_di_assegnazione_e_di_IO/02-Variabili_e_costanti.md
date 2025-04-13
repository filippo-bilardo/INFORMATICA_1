# Variabili e costanti in C

Le variabili e le costanti sono elementi fondamentali in qualsiasi linguaggio di programmazione, incluso il C. Esse permettono di memorizzare e manipolare dati durante l'esecuzione di un programma.

## Variabili

Una **variabile** è un'area di memoria che può contenere un valore che può essere modificato durante l'esecuzione del programma. In C, ogni variabile deve essere dichiarata con un tipo specifico prima di poter essere utilizzata.

### Dichiarazione di variabili

La sintassi generale per dichiarare una variabile in C è:

```c
tipo nome_variabile;
```

Dove:
- `tipo` è il tipo di dato della variabile (int, float, char, ecc.)
- `nome_variabile` è l'identificatore scelto per la variabile

Esempi di dichiarazioni di variabili:

```c
int eta;                // Dichiara una variabile intera chiamata 'eta'
float temperatura;      // Dichiara una variabile float chiamata 'temperatura'
char iniziale;          // Dichiara una variabile carattere chiamata 'iniziale'
```

### Inizializzazione di variabili

È possibile assegnare un valore iniziale a una variabile al momento della dichiarazione:

```c
int eta = 25;           // Dichiara e inizializza 'eta' a 25
float temperatura = 36.5; // Dichiara e inizializza 'temperatura' a 36.5
char iniziale = 'M';     // Dichiara e inizializza 'iniziale' a 'M'
```

### Assegnazione di valori

Dopo la dichiarazione, è possibile assegnare o modificare il valore di una variabile utilizzando l'operatore di assegnazione `=`:

```c
eta = 26;               // Modifica il valore di 'eta' a 26
temperatura = 37.2;     // Modifica il valore di 'temperatura' a 37.2
iniziale = 'L';         // Modifica il valore di 'iniziale' a 'L'
```

### Regole per i nomi delle variabili

In C, i nomi delle variabili devono seguire queste regole:

1. Possono contenere lettere, cifre e underscore (_)
2. Devono iniziare con una lettera o un underscore
3. Sono case-sensitive (maiuscole e minuscole sono considerate diverse)
4. Non possono essere parole chiave riservate del linguaggio (come `int`, `if`, `while`, ecc.)

Esempi validi:
```c
int numero1;
float temperatura_celsius;
char _carattere;
```

Esempi non validi:
```c
int 1numero;        // Non può iniziare con un numero
float temp-celsius;  // Non può contenere il trattino
int if;             // Non può essere una parola chiave
```

### Scope delle variabili

Lo **scope** (ambito di visibilità) di una variabile definisce dove essa può essere utilizzata all'interno del programma:

1. **Variabili locali**: dichiarate all'interno di una funzione o di un blocco, sono accessibili solo all'interno di quella funzione o blocco
2. **Variabili globali**: dichiarate al di fuori di tutte le funzioni, sono accessibili in tutto il programma

```c
#include <stdio.h>

int variabile_globale = 10;  // Variabile globale

int main() {
    int variabile_locale = 5;  // Variabile locale
    
    printf("Globale: %d, Locale: %d\n", variabile_globale, variabile_locale);
    
    {
        int variabile_blocco = 20;  // Variabile di blocco
        printf("Blocco: %d\n", variabile_blocco);
    }
    
    // printf("Blocco: %d\n", variabile_blocco);  // Errore: variabile_blocco non è accessibile qui
    
    return 0;
}
```

## Costanti

Una **costante** è un valore che non può essere modificato durante l'esecuzione del programma. In C, ci sono diversi modi per definire costanti.

### Costanti letterali

Le costanti letterali sono valori fissi scritti direttamente nel codice:

```c
printf("L'età è %d\n", 25);        // 25 è una costante letterale intera
printf("La temperatura è %.1f\n", 36.5);  // 36.5 è una costante letterale float
printf("L'iniziale è %c\n", 'M');      // 'M' è una costante letterale carattere
printf("Il nome è %s\n", "Mario");    // "Mario" è una costante letterale stringa
```

### Costanti simboliche con `#define`

La direttiva del preprocessore `#define` permette di definire costanti simboliche:

```c
#define PI 3.14159
#define MAX_STUDENTI 30

int main() {
    float raggio = 5.0;
    float area = PI * raggio * raggio;
    
    printf("L'area del cerchio è: %.2f\n", area);
    printf("Numero massimo di studenti: %d\n", MAX_STUDENTI);
    
    return 0;
}
```

Le costanti definite con `#define` sono sostituite dal loro valore dal preprocessore prima della compilazione. Non hanno un tipo specifico e non occupano memoria.

### Costanti con `const`

La parola chiave `const` permette di dichiarare variabili il cui valore non può essere modificato:

```c
const float PI = 3.14159;
const int MAX_STUDENTI = 30;

int main() {
    float raggio = 5.0;
    float area = PI * raggio * raggio;
    
    printf("L'area del cerchio è: %.2f\n", area);
    printf("Numero massimo di studenti: %d\n", MAX_STUDENTI);
    
    // PI = 3.14;  // Errore: non è possibile modificare una costante
    
    return 0;
}
```

A differenza delle costanti `#define`, le costanti `const` hanno un tipo specifico e occupano memoria.

### Costanti di enumerazione

Le enumerazioni (`enum`) permettono di definire un insieme di costanti intere con nomi simbolici:

```c
enum Giorni {LUNEDI = 1, MARTEDI, MERCOLEDI, GIOVEDI, VENERDI, SABATO, DOMENICA};

int main() {
    enum Giorni oggi = MERCOLEDI;
    
    printf("Oggi è il giorno %d della settimana\n", oggi);  // Stampa 3
    
    return 0;
}
```

In questo esempio, `LUNEDI` ha valore 1, `MARTEDI` ha valore 2, e così via.

## Vantaggi dell'uso di costanti

L'uso di costanti simboliche (con `#define`, `const` o `enum`) offre diversi vantaggi:

1. **Leggibilità**: i nomi simbolici rendono il codice più comprensibile
2. **Manutenibilità**: se un valore deve essere modificato, basta cambiarlo in un solo punto
3. **Prevenzione degli errori**: impedisce modifiche accidentali di valori che dovrebbero rimanere costanti

## Conclusione

Le variabili e le costanti sono elementi fondamentali nella programmazione in C. Le variabili permettono di memorizzare e manipolare dati durante l'esecuzione del programma, mentre le costanti garantiscono che determinati valori rimangano invariati. La scelta appropriata tra variabili e costanti, e tra i diversi tipi di costanti, è importante per scrivere codice chiaro, efficiente e manutenibile.