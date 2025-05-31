# Definizione e dichiarazione di funzioni in C

Le funzioni sono blocchi di codice che eseguono un compito specifico e possono essere riutilizzati all'interno di un programma. Sono fondamentali per creare programmi modulari, leggibili e manutenibili. In C, ogni programma contiene almeno una funzione: la funzione `main()`, che rappresenta il punto di ingresso del programma.

## Struttura di una funzione

Una funzione in C è composta da:

1. **Tipo di ritorno**: specifica il tipo di dato che la funzione restituirà
2. **Nome della funzione**: identificatore che permette di richiamare la funzione
3. **Parametri**: valori di input che la funzione riceve (opzionali)
4. **Corpo della funzione**: blocco di codice racchiuso tra parentesi graffe che contiene le istruzioni da eseguire
5. **Istruzione return**: specifica il valore da restituire (obbligatoria per funzioni non void)

### Sintassi di base

```c
tipo_ritorno nome_funzione(tipo_parametro1 parametro1, tipo_parametro2 parametro2, ...) {
    // Corpo della funzione
    // Istruzioni da eseguire
    
    return valore;  // Valore da restituire (del tipo specificato)
}
```

### Esempio di funzione semplice

```c
#include <stdio.h>

// Funzione che calcola la somma di due interi
int somma(int a, int b) {
    int risultato = a + b;
    return risultato;
}

int main() {
    int x = 5, y = 3;
    int z = somma(x, y);  // Chiamata della funzione
    
    printf("La somma di %d e %d è %d\n", x, y, z);
    
    return 0;
}
```

## Dichiarazione vs. Definizione

In C, è importante distinguere tra dichiarazione e definizione di una funzione:

- **Dichiarazione** (o prototipo): informa il compilatore dell'esistenza di una funzione, specificando il suo nome, tipo di ritorno e parametri, ma senza fornire il corpo della funzione. Termina con un punto e virgola.
- **Definizione**: contiene il corpo della funzione con le istruzioni da eseguire.

### Dichiarazione (prototipo)

```c
tipo_ritorno nome_funzione(tipo_parametro1, tipo_parametro2, ...);  // Nota il punto e virgola
```

### Definizione

```c
tipo_ritorno nome_funzione(tipo_parametro1 parametro1, tipo_parametro2 parametro2, ...) {
    // Corpo della funzione
    return valore;
}
```

### Esempio di dichiarazione e definizione

```c
#include <stdio.h>

// Dichiarazione (prototipo)
int calcola_quadrato(int numero);

int main() {
    int n = 5;
    int risultato = calcola_quadrato(n);  // Chiamata della funzione
    
    printf("Il quadrato di %d è %d\n", n, risultato);
    
    return 0;
}

// Definizione
int calcola_quadrato(int numero) {
    return numero * numero;
}
```

## Perché usare i prototipi?

I prototipi di funzione sono utili per:

1. **Permettere chiamate forward**: consentono di chiamare una funzione prima che sia definita nel codice
2. **Controllo dei tipi**: permettono al compilatore di verificare che le chiamate di funzione utilizzino i tipi corretti
3. **Organizzazione del codice**: consentono di separare le dichiarazioni dalle implementazioni

## Tipi di ritorno

Una funzione può restituire un valore di qualsiasi tipo di dato valido in C, oppure può non restituire alcun valore (tipo `void`).

### Funzioni che restituiscono un valore

```c
#include <stdio.h>

// Funzione che restituisce un intero
int somma(int a, int b) {
    return a + b;
}

// Funzione che restituisce un float
float media(float a, float b) {
    return (a + b) / 2.0f;
}

// Funzione che restituisce un carattere
char primo_carattere(char *stringa) {
    return stringa[0];
}

int main() {
    int s = somma(10, 20);
    float m = media(10.5f, 20.5f);
    char c = primo_carattere("Hello");
    
    printf("Somma: %d\n", s);
    printf("Media: %.2f\n", m);
    printf("Primo carattere: %c\n", c);
    
    return 0;
}
```

### Funzioni void (senza valore di ritorno)

Le funzioni di tipo `void` non restituiscono alcun valore e vengono utilizzate principalmente per eseguire operazioni senza produrre un risultato diretto.

```c
#include <stdio.h>

// Funzione void che stampa un messaggio
void saluta(char *nome) {
    printf("Ciao, %s!\n", nome);
    // Non c'è istruzione return (o si può usare 'return;' senza valore)
}

int main() {
    saluta("Mario");  // Chiamata della funzione void
    return 0;
}
```

## Parametri di funzione

I parametri sono valori che vengono passati a una funzione quando viene chiamata. In C, i parametri sono passati per valore di default, il che significa che la funzione riceve una copia del valore originale.

### Funzioni senza parametri

```c
#include <stdio.h>

// Funzione senza parametri
void stampa_intestazione() {
    printf("===================================\n");
    printf("        PROGRAMMA ESEMPIO         \n");
    printf("===================================\n");
}

int main() {
    stampa_intestazione();  // Chiamata della funzione senza parametri
    printf("Contenuto del programma...\n");
    return 0;
}
```

### Funzioni con parametri

```c
#include <stdio.h>

// Funzione con due parametri
void stampa_rettangolo(int larghezza, int altezza) {
    for (int i = 0; i < altezza; i++) {
        for (int j = 0; j < larghezza; j++) {
            printf("* ");
        }
        printf("\n");
    }
}

int main() {
    int l = 5, a = 3;
    
    printf("Rettangolo %dx%d:\n", l, a);
    stampa_rettangolo(l, a);  // Chiamata con due argomenti
    
    return 0;
}
```

## Chiamata di funzione

Per utilizzare una funzione, è necessario chiamarla specificando il suo nome seguito da parentesi tonde che contengono gli argomenti (se presenti).

```c
#include <stdio.h>

int quadrato(int x) {
    return x * x;
}

float area_cerchio(float raggio) {
    float pi = 3.14159f;
    return pi * raggio * raggio;
}

int main() {
    // Chiamata con un valore letterale
    printf("Il quadrato di 4 è %d\n", quadrato(4));
    
    // Chiamata con una variabile
    int numero = 5;
    printf("Il quadrato di %d è %d\n", numero, quadrato(numero));
    
    // Chiamata con un'espressione
    printf("Il quadrato di (2+3) è %d\n", quadrato(2+3));
    
    // Chiamata con il risultato di un'altra funzione
    printf("Il quadrato del quadrato di 2 è %d\n", quadrato(quadrato(2)));
    
    // Chiamata con un tipo diverso (conversione implicita)
    float raggio = 2.5f;
    printf("L'area di un cerchio con raggio %.1f è %.2f\n", raggio, area_cerchio(raggio));
    
    return 0;
}
```

## Funzioni in file multipli

In progetti più grandi, è comune dividere il codice in più file. Le dichiarazioni delle funzioni vengono spesso collocate in file header (`.h`), mentre le definizioni si trovano in file di implementazione (`.c`).

### File header (funzioni.h)

```c
#ifndef FUNZIONI_H
#define FUNZIONI_H

// Dichiarazioni di funzioni
int somma(int a, int b);
int sottrazione(int a, int b);
int moltiplicazione(int a, int b);
float divisione(int a, int b);

#endif // FUNZIONI_H
```

### File di implementazione (funzioni.c)

```c
#include "funzioni.h"

// Definizioni di funzioni
int somma(int a, int b) {
    return a + b;
}

int sottrazione(int a, int b) {
    return a - b;
}

int moltiplicazione(int a, int b) {
    return a * b;
}

float divisione(int a, int b) {
    if (b != 0) {
        return (float)a / b;
    } else {
        return 0;  // Gestione dell'errore (divisione per zero)
    }
}
```

### File principale (main.c)

```c
#include <stdio.h>
#include "funzioni.h"

int main() {
    int x = 10, y = 5;
    
    printf("%d + %d = %d\n", x, y, somma(x, y));
    printf("%d - %d = %d\n", x, y, sottrazione(x, y));
    printf("%d * %d = %d\n", x, y, moltiplicazione(x, y));
    printf("%d / %d = %.2f\n", x, y, divisione(x, y));
    
    return 0;
}
```

## Funzioni inline

In C99 e versioni successive, è possibile dichiarare funzioni inline, che suggeriscono al compilatore di inserire il codice della funzione direttamente nel punto di chiamata, evitando l'overhead di una chiamata di funzione.

```c
#include <stdio.h>

// Funzione inline
inline int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int x = 5, y = 8;
    
    printf("Il massimo tra %d e %d è %d\n", x, y, max(x, y));
    
    return 0;
}
```

**Nota**: L'uso di `inline` è solo un suggerimento per il compilatore, che può scegliere di ignorarlo.

## Funzioni con numero variabile di argomenti

C supporta funzioni con un numero variabile di argomenti attraverso la libreria `<stdarg.h>`.

```c
#include <stdio.h>
#include <stdarg.h>

// Funzione che calcola la media di un numero variabile di interi
float media(int count, ...) {
    va_list args;
    int sum = 0;
    
    va_start(args, count);  // Inizializza la lista di argomenti
    
    for (int i = 0; i < count; i++) {
        sum += va_arg(args, int);  // Estrae il prossimo argomento come int
    }
    
    va_end(args);  // Pulisce la lista di argomenti
    
    return (count > 0) ? (float)sum / count : 0;
}

int main() {
    printf("Media di 2, 4, 6: %.2f\n", media(3, 2, 4, 6));
    printf("Media di 5, 10, 15, 20, 25: %.2f\n", media(5, 5, 10, 15, 20, 25));
    
    return 0;
}
```

## Best practice

1. **Nomi significativi**: Utilizzare nomi di funzioni che descrivano chiaramente il loro scopo.

2. **Funzioni brevi e focalizzate**: Ogni funzione dovrebbe fare una cosa sola e farla bene. Funzioni troppo lunghe o che fanno troppe cose dovrebbero essere suddivise.

3. **Dichiarare sempre i prototipi**: Anche se non obbligatorio, è una buona pratica dichiarare sempre i prototipi delle funzioni.

4. **Documentare le funzioni**: Aggiungere commenti che spieghino lo scopo della funzione, i parametri e il valore di ritorno.

5. **Gestire i casi limite**: Assicurarsi che la funzione gestisca correttamente i casi limite (ad esempio, divisione per zero).

6. **Coerenza nei tipi**: Evitare conversioni di tipo implicite nei parametri e nei valori di ritorno.

7. **Evitare effetti collaterali**: Le funzioni dovrebbero evitare di modificare variabili globali o stati esterni, a meno che non sia esplicitamente parte del loro scopo.

## Esempi pratici

### Calcolo del fattoriale

```c
#include <stdio.h>

// Calcola il fattoriale di un numero
unsigned long fattoriale(int n) {
    if (n < 0) {
        return 0;  // Errore: fattoriale non definito per numeri negativi
    }
    
    unsigned long risultato = 1;
    
    for (int i = 2; i <= n; i++) {
        risultato *= i;
    }
    
    return risultato;
}

int main() {
    for (int i = 0; i <= 10; i++) {
        printf("%2d! = %lu\n", i, fattoriale(i));
    }
    
    return 0;
}
```

### Conversione di temperatura

```c
#include <stdio.h>

// Converte da Celsius a Fahrenheit
float celsius_to_fahrenheit(float celsius) {
    return (celsius * 9.0f / 5.0f) + 32.0f;
}

// Converte da Fahrenheit a Celsius
float fahrenheit_to_celsius(float fahrenheit) {
    return (fahrenheit - 32.0f) * 5.0f / 9.0f;
}

int main() {
    float temp_c = 25.0f;
    float temp_f = celsius_to_fahrenheit(temp_c);
    
    printf("%.1f°C = %.1f°F\n", temp_c, temp_f);
    printf("%.1f°F = %.1f°C\n", temp_f, fahrenheit_to_celsius(temp_f));
    
    return 0;
}
```

### Verifica di un numero primo

```c
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Verifica se un numero è primo
bool è_primo(int numero) {
    // Gestione casi speciali
    if (numero <= 1) {
        return false;  // 0 e 1 non sono primi
    }
    
    if (numero <= 3) {
        return true;  // 2 e 3 sono primi
    }
    
    if (numero % 2 == 0 || numero % 3 == 0) {
        return false;  // Divisibile per 2 o 3
    }
    
    // Verifica divisibilità per numeri della forma 6k±1
    for (int i = 5; i * i <= numero; i += 6) {
        if (numero % i == 0 || numero % (i + 2) == 0) {
            return false;  // Non è primo
        }
    }
    
    return true;  // È primo
}

int main() {
    printf("Numeri primi fino a 50:\n");
    
    for (int i = 1; i <= 50; i++) {
        if (è_primo(i)) {
            printf("%d ", i);
        }
    }
    
    printf("\n");
    return 0;
}
```

## Domande di autovalutazione

1. Qual è la differenza tra dichiarazione e definizione di una funzione?

2. Cosa succede se una funzione non void non include un'istruzione `return`?

3. Perché è utile dividere un programma in più funzioni?

4. Come si può dichiarare una funzione che non accetta parametri in C?

5. Quali sono i vantaggi dell'utilizzo di prototipi di funzione?

## Esercizi proposti

1. Scrivi una funzione che calcoli la potenza di un numero (base^esponente) senza utilizzare la libreria math.h.

2. Implementa una funzione che verifichi se un numero è palindromo (si legge allo stesso modo da sinistra a destra e da destra a sinistra).

3. Crea una funzione che calcoli il massimo comune divisore (MCD) di due numeri utilizzando l'algoritmo di Euclide.

4. Scrivi una funzione che converta un numero da decimale a binario e lo restituisca come stringa.

5. Implementa una serie di funzioni per calcolare l'area e il perimetro di diverse forme geometriche (cerchio, rettangolo, triangolo) e crea un programma che le utilizzi tutte.