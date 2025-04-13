# Tipi di dati fondamentali in C

In C, i tipi di dati fondamentali sono utilizzati per definire il tipo di valore che una variabile può memorizzare. Ogni tipo di dato ha una dimensione specifica in memoria e può rappresentare un intervallo di valori. Comprendere i tipi di dati è essenziale per scrivere programmi efficienti e corretti.

## Tipi di dati interi

I tipi di dati interi in C sono utilizzati per memorizzare numeri interi (senza parte decimale).

### `int`

Il tipo `int` è il tipo intero di base in C. La sua dimensione dipende dall'architettura del sistema, ma è generalmente di 4 byte (32 bit) nei sistemi moderni.

```c
int numero = 42;
printf("Il valore è: %d\n", numero);
```

### `short int` (o semplicemente `short`)

Il tipo `short int` è un tipo intero più piccolo, generalmente di 2 byte (16 bit).

```c
short int numero_piccolo = 32767; // Valore massimo per short int
printf("Il valore è: %hd\n", numero_piccolo);
```

### `long int` (o semplicemente `long`)

Il tipo `long int` è un tipo intero più grande, generalmente di 4 byte (32 bit) o 8 byte (64 bit) a seconda dell'architettura.

```c
long int numero_grande = 2147483647L; // Suffisso L per costanti long
printf("Il valore è: %ld\n", numero_grande);
```

### `long long int` (o semplicemente `long long`)

Il tipo `long long int` è un tipo intero ancora più grande, generalmente di 8 byte (64 bit).

```c
long long int numero_molto_grande = 9223372036854775807LL; // Suffisso LL per costanti long long
printf("Il valore è: %lld\n", numero_molto_grande);
```

### Modificatori di segno

I tipi interi possono essere preceduti dai modificatori `signed` (default) o `unsigned`:

- `signed`: può rappresentare sia numeri positivi che negativi
- `unsigned`: può rappresentare solo numeri positivi, ma con un intervallo maggiore

```c
unsigned int solo_positivo = 4294967295U; // Suffisso U per costanti unsigned
printf("Il valore è: %u\n", solo_positivo);
```

## Tipi di dati in virgola mobile

I tipi di dati in virgola mobile sono utilizzati per rappresentare numeri con parte decimale.

### `float`

Il tipo `float` è utilizzato per rappresentare numeri in virgola mobile a precisione singola (generalmente 4 byte).

```c
float pi = 3.14159F; // Suffisso F per costanti float
printf("Il valore è: %f\n", pi);
```

### `double`

Il tipo `double` è utilizzato per rappresentare numeri in virgola mobile a precisione doppia (generalmente 8 byte).

```c
double pi_preciso = 3.141592653589793;
printf("Il valore è: %.15f\n", pi_preciso);
```

### `long double`

Il tipo `long double` offre una precisione ancora maggiore (la dimensione varia a seconda dell'implementazione).

```c
long double pi_molto_preciso = 3.141592653589793238L; // Suffisso L per costanti long double
printf("Il valore è: %.18Lf\n", pi_molto_preciso);
```

## Tipo carattere

### `char`

Il tipo `char` è utilizzato per memorizzare singoli caratteri. In C, i caratteri sono rappresentati utilizzando il codice ASCII.

```c
char lettera = 'A';
printf("Il carattere è: %c\n", lettera);
printf("Il valore ASCII è: %d\n", lettera); // Stampa il valore ASCII (65 per 'A')
```

Il tipo `char` può essere considerato anche come un piccolo intero (generalmente 1 byte):

```c
char valore = 65; // Equivalente a 'A'
printf("Il carattere è: %c\n", valore);
```

Anche `char` può essere preceduto dai modificatori `signed` o `unsigned`.

## Tipo booleano

Nel C standard (C89/C90), non esiste un tipo booleano nativo. Tradizionalmente, i valori booleani sono rappresentati usando interi, dove 0 è considerato falso e qualsiasi valore diverso da 0 è considerato vero.

Nello standard C99, è stato introdotto il tipo `_Bool` e l'header `<stdbool.h>` che definisce il tipo `bool` e le costanti `true` e `false`.

```c
#include <stdbool.h>

bool flag = true;
if (flag) {
    printf("La condizione è vera\n");
}
```

## Dimensioni e intervalli

Le dimensioni esatte e gli intervalli dei tipi di dati possono variare a seconda dell'architettura e del compilatore. Per ottenere informazioni precise, è possibile utilizzare l'operatore `sizeof` e le costanti definite in `<limits.h>` e `<float.h>`.

```c
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    printf("Dimensione di int: %zu byte\n", sizeof(int));
    printf("Intervallo di int: da %d a %d\n", INT_MIN, INT_MAX);
    
    printf("Dimensione di float: %zu byte\n", sizeof(float));
    printf("Precisione di float: %d cifre decimali\n", FLT_DIG);
    
    return 0;
}
```

## Conclusione

La scelta del tipo di dato appropriato è fondamentale per:

1. **Efficienza di memoria**: utilizzare il tipo più piccolo che può contenere i valori necessari
2. **Precisione**: utilizzare tipi in virgola mobile quando è necessaria la parte decimale
3. **Intervallo**: assicurarsi che il tipo scelto possa rappresentare tutti i valori possibili

Una comprensione approfondita dei tipi di dati fondamentali in C è essenziale per scrivere programmi robusti ed efficienti.