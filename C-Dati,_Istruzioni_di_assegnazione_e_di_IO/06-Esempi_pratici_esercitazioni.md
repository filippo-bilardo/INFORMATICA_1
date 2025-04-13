# Esempi pratici e esercitazioni in C

Questa sezione contiene esempi pratici ed esercitazioni che illustrano l'applicazione dei concetti teorici di programmazione in C relativi a dati, istruzioni di assegnazione e operazioni di input/output.

## Esempio 1: Calcolo dell'area e del perimetro di un rettangolo

Questo esempio mostra come utilizzare variabili, operazioni aritmetiche e funzioni di input/output per calcolare l'area e il perimetro di un rettangolo.

```c
#include <stdio.h>

int main() {
    // Dichiarazione delle variabili
    float base, altezza, area, perimetro;
    
    // Input dei dati
    printf("Calcolo dell'area e del perimetro di un rettangolo\n");
    printf("Inserisci la base del rettangolo: ");
    scanf("%f", &base);
    printf("Inserisci l'altezza del rettangolo: ");
    scanf("%f", &altezza);
    
    // Calcolo dell'area e del perimetro
    area = base * altezza;
    perimetro = 2 * (base + altezza);
    
    // Output dei risultati
    printf("\nRisultati:\n");
    printf("Area: %.2f unità quadrate\n", area);
    printf("Perimetro: %.2f unità\n", perimetro);
    
    return 0;
}
```

## Esempio 2: Conversione di temperatura da Celsius a Fahrenheit e Kelvin

Questo esempio illustra l'uso di costanti, operazioni aritmetiche e casting per convertire una temperatura da Celsius a Fahrenheit e Kelvin.

```c
#include <stdio.h>

#define ZERO_ASSOLUTO -273.15  // Zero assoluto in Celsius

int main() {
    // Dichiarazione delle variabili
    float celsius, fahrenheit, kelvin;
    
    // Input della temperatura in Celsius
    printf("Conversione di temperatura\n");
    printf("Inserisci la temperatura in gradi Celsius: ");
    scanf("%f", &celsius);
    
    // Verifica che la temperatura non sia inferiore allo zero assoluto
    if (celsius < ZERO_ASSOLUTO) {
        printf("Errore: La temperatura inserita è inferiore allo zero assoluto (%.2f°C)\n", ZERO_ASSOLUTO);
        return 1;
    }
    
    // Conversione in Fahrenheit: F = (C * 9/5) + 32
    fahrenheit = (celsius * 9.0 / 5.0) + 32.0;
    
    // Conversione in Kelvin: K = C + 273.15
    kelvin = celsius + 273.15;
    
    // Output dei risultati
    printf("\nRisultati:\n");
    printf("%.2f gradi Celsius corrispondono a:\n", celsius);
    printf("%.2f gradi Fahrenheit\n", fahrenheit);
    printf("%.2f Kelvin\n", kelvin);
    
    return 0;
}
```

## Esempio 3: Calcolo del valore medio e della deviazione standard

Questo esempio mostra come calcolare il valore medio e la deviazione standard di un insieme di numeri, utilizzando array, cicli e la libreria matematica.

```c
#include <stdio.h>
#include <math.h>  // Per la funzione sqrt()

#define MAX_NUMERI 100

int main() {
    // Dichiarazione delle variabili
    float numeri[MAX_NUMERI];
    int n, i;
    float somma = 0, media, somma_scarti_quadrati = 0, deviazione_standard;
    
    // Input del numero di elementi
    printf("Calcolo della media e della deviazione standard\n");
    printf("Quanti numeri vuoi inserire? (max %d): ", MAX_NUMERI);
    scanf("%d", &n);
    
    // Verifica che n sia valido
    if (n <= 0 || n > MAX_NUMERI) {
        printf("Errore: Il numero di elementi deve essere compreso tra 1 e %d\n", MAX_NUMERI);
        return 1;
    }
    
    // Input dei numeri
    printf("\nInserisci i %d numeri:\n", n);
    for (i = 0; i < n; i++) {
        printf("Numero %d: ", i + 1);
        scanf("%f", &numeri[i]);
        somma += numeri[i];
    }
    
    // Calcolo della media
    media = somma / n;
    
    // Calcolo della somma degli scarti quadratici
    for (i = 0; i < n; i++) {
        somma_scarti_quadrati += pow(numeri[i] - media, 2);
    }
    
    // Calcolo della deviazione standard
    deviazione_standard = sqrt(somma_scarti_quadrati / n);
    
    // Output dei risultati
    printf("\nRisultati:\n");
    printf("Media: %.2f\n", media);
    printf("Deviazione standard: %.2f\n", deviazione_standard);
    
    return 0;
}
```

## Esempio 4: Manipolazione di caratteri e stringhe

Questo esempio illustra l'uso di caratteri, stringhe e funzioni di input/output per manipolare testo.

```c
#include <stdio.h>
#include <string.h>  // Per le funzioni di manipolazione delle stringhe
#include <ctype.h>   // Per le funzioni di classificazione dei caratteri

#define MAX_LUNGHEZZA 100

int main() {
    // Dichiarazione delle variabili
    char stringa[MAX_LUNGHEZZA];
    int lunghezza, i;
    int contatore_lettere = 0, contatore_cifre = 0, contatore_spazi = 0, contatore_altri = 0;
    
    // Input della stringa
    printf("Analisi di una stringa\n");
    printf("Inserisci una stringa (max %d caratteri): ", MAX_LUNGHEZZA - 1);
    fgets(stringa, MAX_LUNGHEZZA, stdin);
    
    // Rimuovi il carattere newline alla fine della stringa, se presente
    lunghezza = strlen(stringa);
    if (stringa[lunghezza - 1] == '\n') {
        stringa[lunghezza - 1] = '\0';
        lunghezza--;
    }
    
    // Analisi dei caratteri nella stringa
    for (i = 0; i < lunghezza; i++) {
        if (isalpha(stringa[i])) {
            contatore_lettere++;
        } else if (isdigit(stringa[i])) {
            contatore_cifre++;
        } else if (isspace(stringa[i])) {
            contatore_spazi++;
        } else {
            contatore_altri++;
        }
    }
    
    // Output dei risultati
    printf("\nAnalisi della stringa \"%s\":\n", stringa);
    printf("Lunghezza: %d caratteri\n", lunghezza);
    printf("Lettere: %d\n", contatore_lettere);
    printf("Cifre: %d\n", contatore_cifre);
    printf("Spazi: %d\n", contatore_spazi);
    printf("Altri caratteri: %d\n", contatore_altri);
    
    // Conversione della stringa in maiuscolo
    printf("\nStringa in maiuscolo: ");
    for (i = 0; i < lunghezza; i++) {
        putchar(toupper(stringa[i]));
    }
    printf("\n");
    
    // Conversione della stringa in minuscolo
    printf("Stringa in minuscolo: ");
    for (i = 0; i < lunghezza; i++) {
        putchar(tolower(stringa[i]));
    }
    printf("\n");
    
    return 0;
}
```

## Esempio 5: Operazioni bit a bit

Questo esempio mostra l'uso degli operatori bit a bit per manipolare i singoli bit di un numero intero.

```c
#include <stdio.h>

void stampa_binario(unsigned int n) {
    // Funzione per stampare la rappresentazione binaria di un numero
    int i;
    unsigned int maschera = 1 << 31;  // Maschera per il bit più significativo (per un int a 32 bit)
    
    for (i = 0; i < 32; i++) {
        // Stampa 1 se il bit corrente è 1, altrimenti stampa 0
        putchar((n & maschera) ? '1' : '0');
        
        // Sposta la maschera di un bit a destra
        maschera >>= 1;
        
        // Aggiungi uno spazio ogni 4 bit per migliorare la leggibilità
        if ((i + 1) % 4 == 0) {
            putchar(' ');
        }
    }
    printf("\n");
}

int main() {
    // Dichiarazione delle variabili
    unsigned int a, b, risultato;
    int shift;
    
    // Input dei numeri
    printf("Operazioni bit a bit\n");
    printf("Inserisci il primo numero (intero non negativo): ");
    scanf("%u", &a);
    printf("Inserisci il secondo numero (intero non negativo): ");
    scanf("%u", &b);
    
    // Stampa la rappresentazione binaria dei numeri
    printf("\nRappresentazione binaria:\n");
    printf("a = %u in binario: ", a);
    stampa_binario(a);
    printf("b = %u in binario: ", b);
    stampa_binario(b);
    
    // Operazioni bit a bit
    printf("\nOperazioni bit a bit:\n");
    
    // AND bit a bit
    risultato = a & b;
    printf("a & b = %u in binario: ", risultato);
    stampa_binario(risultato);
    
    // OR bit a bit
    risultato = a | b;
    printf("a | b = %u in binario: ", risultato);
    stampa_binario(risultato);
    
    // XOR bit a bit
    risultato = a ^ b;
    printf("a ^ b = %u in binario: ", risultato);
    stampa_binario(risultato);
    
    // NOT bit a bit
    risultato = ~a;
    printf("~a = %u in binario: ", risultato);
    stampa_binario(risultato);
    
    // Shift a sinistra
    printf("\nInserisci il numero di posizioni per lo shift (intero non negativo): ");
    scanf("%d", &shift);
    
    risultato = a << shift;
    printf("a << %d = %u in binario: ", shift, risultato);
    stampa_binario(risultato);
    
    // Shift a destra
    risultato = a >> shift;
    printf("a >> %d = %u in binario: ", shift, risultato);
    stampa_binario(risultato);
    
    return 0;
}
```

## Esercitazioni proposte

### Esercizio 1: Calcolatrice semplice
Sviluppa un programma che funzioni come una calcolatrice semplice, in grado di eseguire le quattro operazioni aritmetiche di base (addizione, sottrazione, moltiplicazione e divisione) su due numeri inseriti dall'utente.

### Esercizio 2: Conversione di valuta
Crea un programma che converta un importo da una valuta all'altra (ad esempio, da euro a dollari o viceversa), utilizzando tassi di cambio definiti come costanti.

### Esercizio 3: Calcolo del BMI (Indice di Massa Corporea)
Sviluppa un programma che calcoli l'Indice di Massa Corporea (BMI) di una persona, dato il suo peso in kg e la sua altezza in metri, e che fornisca una valutazione del risultato (sottopeso, normopeso, sovrappeso, obesità).

### Esercizio 4: Generatore di tabelle di moltiplicazione
Crea un programma che generi e visualizzi la tabella di moltiplicazione per un numero inserito dall'utente, fino a un limite specificato.

### Esercizio 5: Analisi di un numero
Sviluppa un programma che, dato un numero intero, determini se è pari o dispari, positivo o negativo, e che calcoli la somma delle sue cifre.

## Conclusione

Gli esempi e le esercitazioni presentati in questa sezione illustrano l'applicazione pratica dei concetti teorici relativi a dati, istruzioni di assegnazione e operazioni di input/output in C. Attraverso questi esempi, è possibile comprendere meglio come utilizzare variabili, costanti, operatori e funzioni di I/O per risolvere problemi concreti.

La pratica è fondamentale per consolidare le conoscenze teoriche e sviluppare competenze di programmazione. Si consiglia di modificare gli esempi proposti e di affrontare le esercitazioni per migliorare la propria comprensione e padronanza del linguaggio C.