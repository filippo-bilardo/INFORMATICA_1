# Operatori in C

Gli operatori in C sono simboli speciali che eseguono operazioni specifiche su uno, due o tre operandi e restituiscono un risultato. Comprendere gli operatori è fondamentale per scrivere espressioni e algoritmi efficaci.

## Operatori aritmetici

Gli operatori aritmetici eseguono operazioni matematiche di base come addizione, sottrazione, moltiplicazione e divisione.

| Operatore | Descrizione | Esempio |
|-----------|-------------|--------|
| `+` | Addizione | `a + b` |
| `-` | Sottrazione | `a - b` |
| `*` | Moltiplicazione | `a * b` |
| `/` | Divisione | `a / b` |
| `%` | Modulo (resto della divisione) | `a % b` |
| `++` | Incremento | `a++` o `++a` |
| `--` | Decremento | `a--` o `--a` |

### Esempi di operatori aritmetici

```c
#include <stdio.h>

int main() {
    int a = 10, b = 3;
    float c;
    
    printf("a + b = %d\n", a + b);  // Stampa 13
    printf("a - b = %d\n", a - b);  // Stampa 7
    printf("a * b = %d\n", a * b);  // Stampa 30
    
    // Divisione tra interi (il risultato è troncato)
    printf("a / b = %d\n", a / b);  // Stampa 3
    
    // Divisione con risultato float
    c = (float)a / b;
    printf("a / b = %.2f\n", c);  // Stampa 3.33
    
    printf("a %% b = %d\n", a % b);  // Stampa 1 (resto della divisione 10/3)
    
    // Operatori di incremento e decremento
    int x = 5;
    printf("x = %d\n", x);    // Stampa 5
    printf("x++ = %d\n", x++); // Stampa 5, poi incrementa x a 6
    printf("x = %d\n", x);    // Stampa 6
    printf("++x = %d\n", ++x); // Incrementa x a 7, poi stampa 7
    
    return 0;
}
```

### Differenza tra incremento prefisso e postfisso

- **Incremento prefisso** (`++x`): incrementa la variabile e poi restituisce il valore
- **Incremento postfisso** (`x++`): restituisce il valore attuale e poi incrementa la variabile

```c
int a = 5, b, c;

b = ++a;  // a diventa 6, b diventa 6
c = a++;  // c diventa 6, poi a diventa 7
```

## Operatori di assegnazione

Gli operatori di assegnazione assegnano valori alle variabili.

| Operatore | Descrizione | Esempio | Equivalente a |
|-----------|-------------|---------|---------------|
| `=` | Assegnazione semplice | `a = b` | `a = b` |
| `+=` | Assegnazione con addizione | `a += b` | `a = a + b` |
| `-=` | Assegnazione con sottrazione | `a -= b` | `a = a - b` |
| `*=` | Assegnazione con moltiplicazione | `a *= b` | `a = a * b` |
| `/=` | Assegnazione con divisione | `a /= b` | `a = a / b` |
| `%=` | Assegnazione con modulo | `a %= b` | `a = a % b` |
| `<<=` | Assegnazione con shift a sinistra | `a <<= b` | `a = a << b` |
| `>>=` | Assegnazione con shift a destra | `a >>= b` | `a = a >> b` |
| `&=` | Assegnazione con AND bit a bit | `a &= b` | `a = a & b` |
| `^=` | Assegnazione con XOR bit a bit | `a ^= b` | `a = a ^ b` |
| `\|=` | Assegnazione con OR bit a bit | `a \|= b` | `a = a \| b` |

### Esempi di operatori di assegnazione

```c
#include <stdio.h>

int main() {
    int a = 10;
    
    a += 5;  // Equivalente a: a = a + 5
    printf("a dopo a += 5: %d\n", a);  // Stampa 15
    
    a -= 3;  // Equivalente a: a = a - 3
    printf("a dopo a -= 3: %d\n", a);  // Stampa 12
    
    a *= 2;  // Equivalente a: a = a * 2
    printf("a dopo a *= 2: %d\n", a);  // Stampa 24
    
    a /= 4;  // Equivalente a: a = a / 4
    printf("a dopo a /= 4: %d\n", a);  // Stampa 6
    
    a %= 4;  // Equivalente a: a = a % 4
    printf("a dopo a %%= 4: %d\n", a);  // Stampa 2
    
    return 0;
}
```

## Operatori relazionali

Gli operatori relazionali confrontano due valori e restituiscono un valore booleano (in C, 1 per vero e 0 per falso).

| Operatore | Descrizione | Esempio |
|-----------|-------------|--------|
| `==` | Uguale a | `a == b` |
| `!=` | Diverso da | `a != b` |
| `>` | Maggiore di | `a > b` |
| `<` | Minore di | `a < b` |
| `>=` | Maggiore o uguale a | `a >= b` |
| `<=` | Minore o uguale a | `a <= b` |

### Esempi di operatori relazionali

```c
#include <stdio.h>

int main() {
    int a = 10, b = 5, c = 10;
    
    printf("a == b: %d\n", a == b);  // Stampa 0 (falso)
    printf("a == c: %d\n", a == c);  // Stampa 1 (vero)
    printf("a != b: %d\n", a != b);  // Stampa 1 (vero)
    printf("a > b: %d\n", a > b);    // Stampa 1 (vero)
    printf("a < b: %d\n", a < b);    // Stampa 0 (falso)
    printf("a >= c: %d\n", a >= c);  // Stampa 1 (vero)
    printf("a <= c: %d\n", a <= c);  // Stampa 1 (vero)
    
    return 0;
}
```

## Operatori logici

Gli operatori logici eseguono operazioni logiche booleane e restituiscono un valore booleano.

| Operatore | Descrizione | Esempio |
|-----------|-------------|--------|
| `&&` | AND logico | `a && b` |
| `\|\|` | OR logico | `a \|\| b` |
| `!` | NOT logico | `!a` |

### Esempi di operatori logici

```c
#include <stdio.h>

int main() {
    int a = 1, b = 0;  // In C, 1 è vero e 0 è falso
    
    printf("a && b: %d\n", a && b);  // Stampa 0 (falso)
    printf("a || b: %d\n", a || b);  // Stampa 1 (vero)
    printf("!a: %d\n", !a);         // Stampa 0 (falso)
    printf("!b: %d\n", !b);         // Stampa 1 (vero)
    
    // Esempio con espressioni più complesse
    int x = 5, y = 10;
    printf("(x > 3) && (y < 15): %d\n", (x > 3) && (y < 15));  // Stampa 1 (vero)
    printf("(x > 7) || (y < 15): %d\n", (x > 7) || (y < 15));  // Stampa 1 (vero)
    
    return 0;
}
```

### Valutazione a corto circuito

Gli operatori `&&` e `||` utilizzano la valutazione a corto circuito:

- Per `a && b`, se `a` è falso, `b` non viene valutato perché il risultato sarà comunque falso
- Per `a || b`, se `a` è vero, `b` non viene valutato perché il risultato sarà comunque vero

```c
int a = 0, b = 5;
if (a != 0 && b / a > 2) {  // b / a non viene valutato se a è 0, evitando la divisione per zero
    printf("Condizione vera\n");
}
```

## Operatori bit a bit

Gli operatori bit a bit eseguono operazioni sui singoli bit dei valori interi.

| Operatore | Descrizione | Esempio |
|-----------|-------------|--------|
| `&` | AND bit a bit | `a & b` |
| `\|` | OR bit a bit | `a \| b` |
| `^` | XOR bit a bit | `a ^ b` |
| `~` | NOT bit a bit (complemento a uno) | `~a` |
| `<<` | Shift a sinistra | `a << n` |
| `>>` | Shift a destra | `a >> n` |

### Esempi di operatori bit a bit

```c
#include <stdio.h>

int main() {
    unsigned int a = 60;  // 00111100 in binario
    unsigned int b = 13;  // 00001101 in binario
    
    printf("a & b = %u\n", a & b);    // Stampa 12 (00001100 in binario)
    printf("a | b = %u\n", a | b);    // Stampa 61 (00111101 in binario)
    printf("a ^ b = %u\n", a ^ b);    // Stampa 49 (00110001 in binario)
    printf("~a = %u\n", ~a);         // Stampa 4294967235 (11111111111111111111111111000011 in binario)
    
    printf("a << 2 = %u\n", a << 2);  // Stampa 240 (11110000 in binario)
    printf("a >> 2 = %u\n", a >> 2);  // Stampa 15 (00001111 in binario)
    
    return 0;
}
```

### Applicazioni degli operatori bit a bit

1. **Manipolazione di flag**: utilizzare singoli bit per rappresentare flag booleani
2. **Ottimizzazione della memoria**: memorizzare più valori in un singolo intero
3. **Operazioni matematiche veloci**: moltiplicazione e divisione per potenze di 2 usando shift

```c
// Moltiplicazione per 2 usando shift a sinistra
int a = 5;
int b = a << 1;  // b = 10 (equivalente a a * 2)

// Divisione per 2 usando shift a destra
int c = 10;
int d = c >> 1;  // d = 5 (equivalente a c / 2)
```

## Operatore condizionale (ternario)

L'operatore condizionale `? :` è l'unico operatore ternario in C. Valuta una condizione e restituisce uno di due valori a seconda che la condizione sia vera o falsa.

Sintassi: `condizione ? valore_se_vero : valore_se_falso`

```c
#include <stdio.h>

int main() {
    int a = 10, b = 5;
    int max;
    
    // Trova il valore massimo tra a e b
    max = (a > b) ? a : b;
    printf("Il valore massimo è: %d\n", max);  // Stampa 10
    
    // Equivalente a:
    if (a > b) {
        max = a;
    } else {
        max = b;
    }
    
    // Operatore ternario annidato
    int c = 15;
    int max_di_tre = (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
    printf("Il valore massimo tra %d, %d e %d è: %d\n", a, b, c, max_di_tre);  // Stampa 15
    
    return 0;
}
```

## Precedenza degli operatori

La precedenza degli operatori determina l'ordine in cui le operazioni vengono eseguite in un'espressione. Gli operatori con precedenza più alta vengono valutati prima di quelli con precedenza più bassa.

Ecco una tabella semplificata della precedenza degli operatori in C (dall'alto verso il basso, in ordine decrescente di precedenza):

| Categoria | Operatori |
|-----------|----------|
| Postfisso | `()` `[]` `->` `.` `++` `--` (postfisso) |
| Unario | `++` `--` (prefisso) `+` `-` `!` `~` `(tipo)` `*` `&` `sizeof` |
| Moltiplicativi | `*` `/` `%` |
| Additivi | `+` `-` |
| Shift | `<<` `>>` |
| Relazionali | `<` `<=` `>` `>=` |
| Uguaglianza | `==` `!=` |
| AND bit a bit | `&` |
| XOR bit a bit | `^` |
| OR bit a bit | `\|` |
| AND logico | `&&` |
| OR logico | `\|\|` |
| Condizionale | `?:` |
| Assegnazione | `=` `+=` `-=` `*=` `/=` `%=` `<<=` `>>=` `&=` `^=` `\|=` |
| Virgola | `,` |

### Esempi di precedenza degli operatori

```c
#include <stdio.h>

int main() {
    int a = 5, b = 3, c = 2, risultato;
    
    // Senza parentesi, la moltiplicazione ha precedenza sull'addizione
    risultato = a + b * c;  // Equivalente a: a + (b * c)
    printf("a + b * c = %d\n", risultato);  // Stampa 11
    
    // Con parentesi, l'addizione viene eseguita prima
    risultato = (a + b) * c;
    printf("(a + b) * c = %d\n", risultato);  // Stampa 16
    
    // Esempio più complesso
    risultato = a * b + c * (a - b) + (a + b) / c;
    printf("a * b + c * (a - b) + (a + b) / c = %d\n", risultato);  // Stampa 19
    
    return 0;
}
```

## Conclusione

Gli operatori in C sono strumenti potenti che permettono di eseguire una vasta gamma di operazioni sui dati. La comprensione dei diversi tipi di operatori, del loro comportamento e della loro precedenza è fondamentale per scrivere espressioni corrette ed efficienti.

È importante ricordare che:

1. Gli operatori hanno una precedenza specifica che determina l'ordine di valutazione
2. Le parentesi possono essere utilizzate per modificare l'ordine di valutazione
3. Alcuni operatori hanno effetti collaterali (come gli operatori di incremento e decremento)
4. Gli operatori bit a bit sono utili per manipolazioni a basso livello e ottimizzazioni

Una buona pratica è utilizzare le parentesi per rendere esplicito l'ordine di valutazione desiderato, anche quando non strettamente necessario, per migliorare la leggibilità del codice.