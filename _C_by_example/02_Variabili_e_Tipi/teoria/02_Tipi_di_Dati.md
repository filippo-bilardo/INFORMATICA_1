# Tipi di dati fondamentali in C

I tipi di dati in C definiscono il tipo di valore che una variabile può memorizzare, la quantità di memoria occupata e le operazioni che possono essere eseguite su di essa. Comprendere i tipi di dati è fondamentale per scrivere programmi C efficienti e corretti.

## Tipi interi

I tipi interi in C sono utilizzati per memorizzare numeri interi (senza parte decimale). Esistono diversi tipi interi, che differiscono principalmente per la dimensione e il range di valori che possono rappresentare.

### char

Il tipo `char` è il tipo intero più piccolo in C, tipicamente occupa 1 byte (8 bit) di memoria.

```c
char c = 'A';  // Può memorizzare un carattere ASCII
char n = 65;   // Equivalente, poiché 'A' ha valore ASCII 65
```

Caratteristiche:
- Dimensione: 1 byte (tipicamente)
- Range: -128 a 127 (signed) o 0 a 255 (unsigned)
- Utilizzato principalmente per rappresentare caratteri ASCII

### int

Il tipo `int` è il tipo intero standard, la cui dimensione dipende dall'architettura del sistema (tipicamente 4 byte su sistemi moderni).

```c
int numero = 42;
int negativo = -100;
```

Caratteristiche:
- Dimensione: tipicamente 4 byte (32 bit) su sistemi moderni
- Range: -2,147,483,648 a 2,147,483,647 (su sistemi a 32 bit)

### short

Il tipo `short` (o `short int`) è un tipo intero che occupa meno spazio rispetto a `int`.

```c
short s = 30000;
short int si = -10000;
```

Caratteristiche:
- Dimensione: tipicamente 2 byte (16 bit)
- Range: -32,768 a 32,767

### long

Il tipo `long` (o `long int`) è un tipo intero che può memorizzare valori più grandi rispetto a `int`.

```c
long l = 2000000000;
long int li = -1000000000;
```

Caratteristiche:
- Dimensione: tipicamente 4 byte (32 bit) o 8 byte (64 bit), a seconda del sistema
- Range: su sistemi a 32 bit, uguale a `int`; su sistemi a 64 bit, molto più ampio

### long long

Il tipo `long long` (o `long long int`), introdotto in C99, è garantito per memorizzare valori interi molto grandi.

```c
long long ll = 9000000000000000000LL;
long long int lli = -5000000000000000000LL;
```

Caratteristiche:
- Dimensione: almeno 8 byte (64 bit)
- Range: almeno -9,223,372,036,854,775,808 a 9,223,372,036,854,775,807

## Tipi in virgola mobile

I tipi in virgola mobile sono utilizzati per rappresentare numeri con parte decimale.

### float

Il tipo `float` rappresenta numeri in virgola mobile a precisione singola.

```c
float f = 3.14f;  // La 'f' alla fine indica un letterale float
float negativo = -2.5f;
```

Caratteristiche:
- Dimensione: tipicamente 4 byte (32 bit)
- Precisione: circa 7 cifre decimali
- Range: circa ±3.4 × 10^38

### double

Il tipo `double` rappresenta numeri in virgola mobile a precisione doppia.

```c
double d = 3.14159265359;
double scientifico = 6.022e23;  // Notazione scientifica
```

Caratteristiche:
- Dimensione: tipicamente 8 byte (64 bit)
- Precisione: circa 15-16 cifre decimali
- Range: circa ±1.8 × 10^308

### long double

Il tipo `long double` può offrire una precisione ancora maggiore rispetto a `double`, ma la sua implementazione varia significativamente tra i compilatori.

```c
long double ld = 3.14159265359L;  // La 'L' alla fine indica un letterale long double
```

Caratteristiche:
- Dimensione: tipicamente 8, 10, 12 o 16 byte, a seconda del compilatore
- Precisione e range: dipendono dall'implementazione

## Modificatori di tipo

I modificatori di tipo possono essere applicati ai tipi interi per modificarne il range di valori.

### signed

Il modificatore `signed` indica che il tipo può rappresentare sia valori positivi che negativi. È il comportamento predefinito per la maggior parte dei tipi interi.

```c
signed int i = -42;  // Equivalente a 'int i = -42;'
signed char c = -10;
```

### unsigned

Il modificatore `unsigned` indica che il tipo può rappresentare solo valori non negativi (da 0 in su), raddoppiando il range massimo positivo.

```c
unsigned int ui = 4000000000U;  // La 'U' indica un letterale unsigned
unsigned char uc = 255;
```

Caratteristiche:
- `unsigned char`: 0 a 255
- `unsigned int`: 0 a 4,294,967,295 (su sistemi a 32 bit)
- `unsigned short`: 0 a 65,535
- `unsigned long`: dipende dal sistema

## Dimensioni e limiti dei tipi

Le dimensioni esatte dei tipi di dati possono variare a seconda dell'architettura e del compilatore. Per conoscere le dimensioni effettive, si può utilizzare l'operatore `sizeof`:

```c
#include <stdio.h>

int main() {
    printf("Dimensione di char: %zu byte\n", sizeof(char));
    printf("Dimensione di int: %zu byte\n", sizeof(int));
    printf("Dimensione di float: %zu byte\n", sizeof(float));
    printf("Dimensione di double: %zu byte\n", sizeof(double));
    return 0;
}
```

Per conoscere i limiti esatti dei tipi interi, si può utilizzare la libreria `<limits.h>`:

```c
#include <stdio.h>
#include <limits.h>

int main() {
    printf("Valore minimo di int: %d\n", INT_MIN);
    printf("Valore massimo di int: %d\n", INT_MAX);
    printf("Valore massimo di unsigned int: %u\n", UINT_MAX);
    return 0;
}
```

Per i tipi in virgola mobile, si può utilizzare la libreria `<float.h>`:

```c
#include <stdio.h>
#include <float.h>

int main() {
    printf("Valore minimo di float: %e\n", FLT_MIN);
    printf("Valore massimo di float: %e\n", FLT_MAX);
    printf("Precisione di float: %d cifre decimali\n", FLT_DIG);
    return 0;
}
```

## Tipo void

Il tipo `void` è un tipo speciale che indica l'assenza di valore. Non può essere utilizzato per dichiarare variabili, ma ha diversi usi importanti:

1. **Funzioni senza valore di ritorno**:
   ```c
   void saluta() {
       printf("Ciao!\n");
       // Nessun return necessario
   }
   ```

2. **Puntatori generici**:
   ```c
   void *ptr;  // Può puntare a qualsiasi tipo di dato
   int n = 42;
   ptr = &n;   // Punta a un intero
   ```

3. **Funzioni senza parametri**:
   ```c
   int getRandomNumber(void) {  // 'void' indica esplicitamente nessun parametro
       return 4;  // Scelto da un lancio di dado equo
   }
   ```

## Tipo _Bool (C99)

Il tipo `_Bool`, introdotto in C99, è un tipo intero che può assumere solo i valori 0 (falso) o 1 (vero).

```c
#include <stdbool.h>  // Fornisce bool, true, false

int main() {
    bool flag = true;  // Equivalente a '_Bool flag = 1;'
    if (flag) {
        printf("La condizione è vera\n");
    }
    return 0;
}
```

## Esempi pratici

### Calcolo dell'area di un cerchio

```c
#include <stdio.h>

#define PI 3.14159

int main() {
    float raggio = 5.0f;
    float area = PI * raggio * raggio;
    
    printf("L'area del cerchio con raggio %.2f è %.2f\n", raggio, area);
    return 0;
}
```

### Conversione di temperatura

```c
#include <stdio.h>

int main() {
    double celsius = 25.0;
    double fahrenheit = (celsius * 9.0/5.0) + 32.0;
    
    printf("%.1f°C = %.1f°F\n", celsius, fahrenheit);
    return 0;
}
```

### Calcolo del salario

```c
#include <stdio.h>

int main() {
    unsigned int ore_lavorate = 40;
    float tariffa_oraria = 15.50f;
    float salario_lordo = ore_lavorate * tariffa_oraria;
    
    printf("Ore lavorate: %u\n", ore_lavorate);
    printf("Tariffa oraria: €%.2f\n", tariffa_oraria);
    printf("Salario lordo: €%.2f\n", salario_lordo);
    return 0;
}
```

## Suggerimenti e best practices

1. **Scegli il tipo appropriato**: Usa il tipo più piccolo che può contenere tutti i possibili valori della variabile.

2. **Attenzione all'overflow**: Quando un valore supera il range del tipo, si verifica un overflow che può causare comportamenti imprevisti.

3. **Precisione dei float**: I tipi in virgola mobile possono avere problemi di precisione. Non usare `==` per confrontare valori float.

4. **Usa costanti tipizzate**: Aggiungi suffissi appropriati ai letterali (U, L, F, ecc.) per evitare conversioni implicite.

5. **Controlla i limiti**: Usa `<limits.h>` e `<float.h>` per verificare i limiti dei tipi sul tuo sistema.

6. **Portabilità**: Ricorda che le dimensioni dei tipi possono variare tra sistemi diversi.

## Domande di autovalutazione

1. Qual è la differenza principale tra `int` e `float`?

2. Perché potrebbe essere preferibile usare `unsigned int` invece di `int` in alcuni casi?

3. Quale tipo di dato useresti per memorizzare l'età di una persona? E per il suo peso?

4. Cosa succede quando si assegna il valore 256 a una variabile `unsigned char`?

5. Qual è la differenza tra `float` e `double`? Quando è preferibile usare uno rispetto all'altro?

6. Come puoi determinare la dimensione di un tipo di dato sul tuo sistema?

## Esercizi pratici

1. Scrivi un programma che stampi le dimensioni di tutti i tipi di dati fondamentali sul tuo sistema.

2. Crea un programma che dimostri l'overflow di un tipo `unsigned char` incrementando il valore da 0 fino a quando non torna a 0.

3. Scrivi un programma che calcoli l'area e il perimetro di un rettangolo, utilizzando variabili di tipo appropriato.

4. Crea un programma che converta un importo in euro in dollari, utilizzando un tasso di cambio memorizzato in una variabile `double`.

5. Scrivi un programma che dimostri la perdita di precisione quando si sommano numeri in virgola mobile di ordini di grandezza molto diversi.

---

[Indice dell'esercitazione](../README.md) | [Argomento precedente](./01_Variabili.md) | [Prossimo argomento](./03_Costanti.md)