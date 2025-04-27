# Variabili in C

Le variabili sono uno dei concetti fondamentali in qualsiasi linguaggio di programmazione. In C, una variabile è un nome simbolico associato a una posizione di memoria che contiene un valore di un determinato tipo.

## Dichiarazione e inizializzazione

### Dichiarazione di variabili

In C, tutte le variabili devono essere dichiarate prima di essere utilizzate. La dichiarazione specifica il tipo di dato e il nome della variabile.

Sintassi base:
```c
tipo nome_variabile;
```

Esempi:
```c
int eta;           // Dichiara una variabile intera chiamata "eta"
float temperatura; // Dichiara una variabile in virgola mobile
char iniziale;     // Dichiara una variabile carattere
```

### Inizializzazione di variabili

L'inizializzazione è il processo di assegnazione di un valore iniziale a una variabile al momento della sua dichiarazione.

Sintassi:
```c
tipo nome_variabile = valore_iniziale;
```

Esempi:
```c
int eta = 25;             // Dichiara e inizializza una variabile intera
float temperatura = 36.5;  // Dichiara e inizializza un float
char iniziale = 'M';       // Dichiara e inizializza un carattere
```

### Dichiarazioni multiple

È possibile dichiarare più variabili dello stesso tipo in un'unica istruzione:

```c
int a, b, c;           // Dichiara tre variabili intere
float x = 1.0, y = 2.0; // Dichiara e inizializza due float
```

### Assegnazione dopo la dichiarazione

Dopo aver dichiarato una variabile, è possibile assegnarle un valore utilizzando l'operatore di assegnazione `=`:

```c
int contatore;      // Dichiarazione
contatore = 0;      // Assegnazione

float prezzo;       // Dichiarazione
prezzo = 19.99;     // Assegnazione
```

## Regole per i nomi delle variabili

In C, i nomi delle variabili (identificatori) devono seguire alcune regole specifiche:

1. **Caratteri consentiti**: lettere (a-z, A-Z), cifre (0-9) e underscore (_)
2. **Primo carattere**: deve essere una lettera o un underscore, non può essere una cifra
3. **Case-sensitive**: `contatore`, `Contatore` e `CONTATORE` sono tre variabili diverse
4. **Lunghezza**: tecnicamente illimitata, ma solo i primi 31 caratteri sono significativi in alcuni compilatori
5. **Parole riservate**: non si possono usare parole chiave del linguaggio C (come `int`, `for`, `while`, ecc.)

### Esempi validi:
```c
int numero;
float temperatura_celsius;
char _carattere;
long int numeroGrande;
int valore_1;
```

### Esempi non validi:
```c
int 1numero;        // Inizia con una cifra
float valore-medio;  // Contiene un trattino
char for;           // Usa una parola riservata
```

### Convenzioni di nomenclatura

Sebbene non siano imposte dal linguaggio, esistono convenzioni comuni per la nomenclatura delle variabili:

- **snake_case**: parole separate da underscore (comune in C)
  ```c
  int numero_studenti;
  float temperatura_massima;
  ```

- **camelCase**: prima parola minuscola, le successive iniziano con maiuscola
  ```c
  int numeroStudenti;
  float temperaturaMaxima;
  ```

- **Costanti**: spesso in maiuscolo con underscore
  ```c
  #define PI 3.14159
  const int MAX_TENTATIVI = 3;
  ```

## Scope e durata delle variabili

Lo "scope" (ambito di visibilità) di una variabile definisce dove nel codice la variabile può essere utilizzata. La "durata" definisce per quanto tempo la variabile esiste in memoria.

### Variabili locali

Le variabili dichiarate all'interno di un blocco (delimitato da `{}`) sono locali a quel blocco.

```c
#include <stdio.h>

int main() {
    int x = 10;  // Variabile locale a main()
    
    {
        int y = 20;  // Variabile locale a questo blocco
        printf("x = %d, y = %d\n", x, y);  // Può accedere sia a x che a y
    }
    
    // printf("y = %d\n", y);  // Errore: y non è visibile qui
    printf("x = %d\n", x);    // OK: x è ancora visibile
    
    return 0;
}
```

Le variabili locali:
- Esistono solo durante l'esecuzione del blocco in cui sono dichiarate
- Vengono create all'ingresso nel blocco e distrutte all'uscita
- Sono memorizzate nello stack
- Non hanno un valore iniziale predefinito (contengono "garbage" se non inizializzate)

### Variabili globali

Le variabili dichiarate al di fuori di qualsiasi funzione sono globali e possono essere utilizzate in tutto il programma.

```c
#include <stdio.h>

int contatore_globale = 0;  // Variabile globale

void incrementa() {
    contatore_globale++;  // Accede alla variabile globale
}

int main() {
    printf("Valore iniziale: %d\n", contatore_globale);
    incrementa();
    printf("Dopo incremento: %d\n", contatore_globale);
    return 0;
}
```

Le variabili globali:
- Esistono per tutta la durata del programma
- Sono accessibili da qualsiasi funzione nel file
- Sono memorizzate nell'area dati del programma
- Sono inizializzate a zero se non specificamente inizializzate

### Variabili statiche

Le variabili statiche mantengono il loro valore tra chiamate successive della funzione.

```c
#include <stdio.h>

void contatore() {
    static int count = 0;  // Variabile statica
    count++;
    printf("Questa funzione è stata chiamata %d volte\n", count);
}

int main() {
    contatore();  // Output: Questa funzione è stata chiamata 1 volte
    contatore();  // Output: Questa funzione è stata chiamata 2 volte
    contatore();  // Output: Questa funzione è stata chiamata 3 volte
    return 0;
}
```

Le variabili statiche:
- Mantengono il loro valore tra le chiamate di funzione
- Sono inizializzate solo la prima volta che il controllo passa attraverso la loro definizione
- Sono memorizzate nell'area dati del programma, non nello stack
- Hanno lo stesso scope di una variabile locale, ma durata per tutto il programma

### Variabili esterne

È possibile accedere a variabili globali definite in altri file utilizzando la parola chiave `extern`.

File1.c:
```c
// File1.c
int contatore_globale = 0;  // Definizione della variabile globale
```

File2.c:
```c
// File2.c
#include <stdio.h>

extern int contatore_globale;  // Dichiarazione di una variabile esterna

void stampa_contatore() {
    printf("Contatore: %d\n", contatore_globale);
}
```

## Suggerimenti e best practices

1. **Inizializza sempre le variabili**: Le variabili non inizializzate contengono valori casuali che possono causare comportamenti imprevisti.

2. **Usa nomi significativi**: Scegli nomi che descrivono chiaramente lo scopo della variabile.

3. **Limita lo scope**: Dichiara le variabili nel blocco più piccolo possibile in cui sono necessarie.

4. **Evita variabili globali**: L'uso eccessivo di variabili globali può rendere il codice difficile da mantenere e soggetto a errori.

5. **Sii coerente**: Usa una convenzione di nomenclatura coerente in tutto il codice.

6. **Commenta le variabili complesse**: Aggiungi commenti per spiegare lo scopo e l'utilizzo di variabili non ovvie.

## Domande di autovalutazione

1. Qual è la differenza tra dichiarazione e inizializzazione di una variabile?

2. Quali sono le regole per i nomi delle variabili in C?

3. Cosa succede se si utilizza una variabile locale non inizializzata?

4. Qual è la differenza tra una variabile locale e una variabile globale?

5. A cosa serve la parola chiave `static` quando applicata a una variabile locale?

6. Come si può accedere a una variabile globale definita in un altro file?

## Esercizi pratici

1. Scrivi un programma che dichiari e inizializzi variabili di diversi tipi e ne stampi i valori.

2. Crea una funzione che utilizzi una variabile statica per contare quante volte è stata chiamata.

3. Scrivi un programma che dimostri la differenza di scope tra variabili locali in blocchi annidati.

4. Crea un programma con una variabile globale e una locale con lo stesso nome, e dimostra quale viene utilizzata in diversi contesti.

5. Scrivi un programma che utilizzi variabili non inizializzate e osserva i risultati. Poi modifica il programma per inizializzare correttamente le variabili.

---

[Indice dell'esercitazione](../README.md) | [Prossimo argomento](./02_Tipi_di_Dati.md)