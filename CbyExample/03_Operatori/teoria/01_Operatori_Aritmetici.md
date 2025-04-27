# Operatori aritmetici in C

Gli operatori aritmetici in C permettono di eseguire operazioni matematiche di base sui valori. Questi operatori sono fondamentali per qualsiasi tipo di elaborazione numerica.

## Operatori aritmetici di base

Il C fornisce i seguenti operatori aritmetici di base:

| Operatore | Descrizione | Esempio |
|-----------|-------------|--------|
| `+` | Addizione | `a + b` |
| `-` | Sottrazione | `a - b` |
| `*` | Moltiplicazione | `a * b` |
| `/` | Divisione | `a / b` |
| `%` | Modulo (resto della divisione) | `a % b` |

### Addizione (+)

L'operatore di addizione somma due operandi.

```c
#include <stdio.h>

int main() {
    int a = 5, b = 3;
    int somma = a + b;  // somma = 8
    
    printf("La somma di %d e %d è %d\n", a, b, somma);
    return 0;
}
```

### Sottrazione (-)

L'operatore di sottrazione calcola la differenza tra due operandi.

```c
#include <stdio.h>

int main() {
    int a = 5, b = 3;
    int differenza = a - b;  // differenza = 2
    
    printf("La differenza tra %d e %d è %d\n", a, b, differenza);
    return 0;
}
```

### Moltiplicazione (*)

L'operatore di moltiplicazione calcola il prodotto di due operandi.

```c
#include <stdio.h>

int main() {
    int a = 5, b = 3;
    int prodotto = a * b;  // prodotto = 15
    
    printf("Il prodotto di %d e %d è %d\n", a, b, prodotto);
    return 0;
}
```

### Divisione (/)

L'operatore di divisione calcola il quoziente della divisione tra due operandi.

**Importante**: Il comportamento dell'operatore di divisione dipende dal tipo degli operandi:
- Se entrambi gli operandi sono interi, il risultato sarà un intero (la parte decimale viene troncata)
- Se almeno uno degli operandi è in virgola mobile, il risultato sarà in virgola mobile

```c
#include <stdio.h>

int main() {
    int a = 5, b = 2;
    int divisione_intera = a / b;  // divisione_intera = 2 (la parte decimale viene troncata)
    
    float c = 5.0, d = 2.0;
    float divisione_float = c / d;  // divisione_float = 2.5
    
    printf("Divisione intera: %d / %d = %d\n", a, b, divisione_intera);
    printf("Divisione in virgola mobile: %.1f / %.1f = %.1f\n", c, d, divisione_float);
    
    return 0;
}
```

#### Errore di divisione per zero

La divisione per zero è un'operazione matematicamente indefinita. In C, tentare una divisione per zero causa un comportamento indefinito, che tipicamente porta a un crash del programma.

```c
// Questo codice causerà un errore a runtime
int a = 5;
int b = 0;
int risultato = a / b;  // Errore: divisione per zero
```

È sempre buona pratica verificare che il divisore non sia zero prima di eseguire una divisione:

```c
#include <stdio.h>

int main() {
    int a = 5, b = 0;
    
    if (b != 0) {
        printf("%d / %d = %d\n", a, b, a / b);
    } else {
        printf("Errore: divisione per zero non consentita\n");
    }
    
    return 0;
}
```

### Modulo (%)

L'operatore modulo restituisce il resto della divisione intera tra due operandi.

**Nota**: L'operatore modulo può essere utilizzato solo con operandi interi, non con numeri in virgola mobile.

```c
#include <stdio.h>

int main() {
    int a = 17, b = 5;
    int resto = a % b;  // resto = 2 (17 = 5 * 3 + 2)
    
    printf("%d %% %d = %d\n", a, b, resto);
    return 0;
}
```

L'operatore modulo è particolarmente utile per:
- Verificare se un numero è pari o dispari (`n % 2 == 0` se n è pari)
- Implementare operazioni cicliche (come un orologio)
- Limitare un valore a un certo intervallo

## Operatori di incremento e decremento

Il C fornisce operatori speciali per incrementare o decrementare una variabile di 1:

| Operatore | Descrizione | Esempio |
|-----------|-------------|--------|
| `++` | Incremento | `a++` o `++a` |
| `--` | Decremento | `a--` o `--a` |

Questi operatori possono essere utilizzati in due modi:

### Forma prefissa (++a, --a)

Nella forma prefissa, la variabile viene incrementata/decrementata prima che il suo valore venga utilizzato nell'espressione.

```c
#include <stdio.h>

int main() {
    int a = 5;
    int b = ++a;  // Prima incrementa a a 6, poi assegna 6 a b
    
    printf("a = %d, b = %d\n", a, b);  // Output: a = 6, b = 6
    return 0;
}
```

### Forma postfissa (a++, a--)

Nella forma postfissa, il valore originale della variabile viene utilizzato nell'espressione, e solo dopo la variabile viene incrementata/decrementata.

```c
#include <stdio.h>

int main() {
    int a = 5;
    int b = a++;  // Prima assegna 5 a b, poi incrementa a a 6
    
    printf("a = %d, b = %d\n", a, b);  // Output: a = 6, b = 5
    return 0;
}
```

## Espressioni aritmetiche complesse

È possibile combinare più operatori aritmetici in un'unica espressione. In questo caso, l'ordine di valutazione segue le regole di precedenza degli operatori.

```c
#include <stdio.h>

int main() {
    int risultato = 10 + 5 * 2 - 8 / 4;  // 10 + 10 - 2 = 18
    printf("Risultato: %d\n", risultato);
    
    // Uso delle parentesi per modificare l'ordine di valutazione
    int risultato2 = (10 + 5) * (2 - 8) / 4;  // 15 * (-6) / 4 = -22
    printf("Risultato con parentesi: %d\n", risultato2);
    
    return 0;
}
```

## Precedenza degli operatori aritmetici

Gli operatori aritmetici seguono queste regole di precedenza (dall'alto verso il basso):

1. Incremento/decremento prefisso (`++a`, `--a`)
2. Moltiplicazione, divisione e modulo (`*`, `/`, `%`)
3. Addizione e sottrazione (`+`, `-`)
4. Incremento/decremento postfisso (`a++`, `a--`)

Le parentesi possono essere utilizzate per sovrascrivere l'ordine di precedenza predefinito.

## Associatività degli operatori aritmetici

L'associatività determina l'ordine di valutazione quando operatori con la stessa precedenza appaiono in un'espressione:

- Gli operatori `*`, `/` e `%` sono associativi da sinistra a destra: `a / b * c` equivale a `(a / b) * c`
- Gli operatori `+` e `-` sono associativi da sinistra a destra: `a - b + c` equivale a `(a - b) + c`

## Ottimizzazione delle espressioni aritmetiche

Il compilatore C spesso ottimizza le espressioni aritmetiche. Tuttavia, è buona pratica scrivere espressioni chiare e leggibili:

- Utilizzare le parentesi per chiarire l'intento, anche quando non strettamente necessarie
- Suddividere espressioni complesse in passaggi più semplici
- Evitare di fare affidamento su effetti collaterali in espressioni complesse

## Best practice

1. **Evitare la divisione per zero**: Controllare sempre che il divisore non sia zero prima di eseguire una divisione.

2. **Attenzione all'overflow**: Le operazioni aritmetiche possono causare overflow se il risultato è troppo grande per il tipo di dato.

3. **Considerare i tipi di dati**: Prestare attenzione ai tipi di dati quando si eseguono operazioni aritmetiche, specialmente con la divisione.

4. **Usare con cautela gli operatori di incremento/decremento**: Evitare di utilizzare questi operatori più volte sulla stessa variabile in un'unica espressione.

5. **Preferire la chiarezza alla concisione**: Scrivere espressioni chiare e leggibili, anche se richiedono più codice.

## Esempi pratici

### Calcolo della media

```c
#include <stdio.h>

int main() {
    int num1, num2, num3;
    float media;
    
    printf("Inserisci tre numeri: ");
    scanf("%d %d %d", &num1, &num2, &num3);
    
    media = (float)(num1 + num2 + num3) / 3;  // Cast a float per ottenere un risultato decimale
    
    printf("La media è: %.2f\n", media);
    return 0;
}
```

### Conversione da Celsius a Fahrenheit

```c
#include <stdio.h>

int main() {
    float celsius, fahrenheit;
    
    printf("Inserisci la temperatura in Celsius: ");
    scanf("%f", &celsius);
    
    fahrenheit = (celsius * 9 / 5) + 32;
    
    printf("%.2f°C equivale a %.2f°F\n", celsius, fahrenheit);
    return 0;
}
```

### Calcolo del resto e del quoziente

```c
#include <stdio.h>

int main() {
    int dividendo, divisore, quoziente, resto;
    
    printf("Inserisci dividendo e divisore: ");
    scanf("%d %d", &dividendo, &divisore);
    
    if (divisore != 0) {
        quoziente = dividendo / divisore;
        resto = dividendo % divisore;
        
        printf("%d diviso %d dà quoziente %d e resto %d\n", 
               dividendo, divisore, quoziente, resto);
    } else {
        printf("Errore: divisione per zero\n");
    }
    
    return 0;
}
```

## Domande di autovalutazione

1. Qual è il valore di `x` dopo l'esecuzione del seguente codice?
   ```c
   int a = 5, b = 2;
   int x = a * b + a / b;
   ```

2. Cosa stamperà il seguente frammento di codice?
   ```c
   int i = 5;
   printf("%d %d %d\n", i++, i, ++i);
   ```

3. Qual è la differenza tra `7 / 2` e `7.0 / 2` in C?

4. Come si può verificare se un numero è divisibile per un altro numero utilizzando l'operatore modulo?

5. Qual è il risultato di `10 % 3` e perché?

## Esercizi proposti

1. Scrivi un programma che calcoli l'area e il perimetro di un rettangolo, date la base e l'altezza.

2. Implementa un programma che converta un numero di secondi in ore, minuti e secondi.

3. Crea un programma che calcoli l'importo finale di un investimento, dato il capitale iniziale, il tasso di interesse annuo e il numero di anni.

4. Scrivi un programma che verifichi se un anno è bisestile (un anno è bisestile se è divisibile per 4, ma non per 100, a meno che non sia anche divisibile per 400).

5. Implementa un programma che calcoli il resto della divisione di due numeri senza utilizzare l'operatore modulo (%).