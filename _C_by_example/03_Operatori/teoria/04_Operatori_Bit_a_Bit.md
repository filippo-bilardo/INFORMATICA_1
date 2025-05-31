# Operatori bit a bit in C

Gli operatori bit a bit (bitwise) in C permettono di manipolare i singoli bit all'interno di un valore. Questi operatori sono particolarmente utili nella programmazione di basso livello, nell'ottimizzazione delle prestazioni e nella gestione di flag e maschere di bit.

## Operatori bit a bit disponibili

Il C fornisce i seguenti operatori bit a bit:

| Operatore | Descrizione | Esempio |
|-----------|-------------|---------|
| `&` | AND bit a bit | `a & b` |
| `|` | OR bit a bit | `a | b` |
| `^` | XOR bit a bit | `a ^ b` |
| `~` | NOT bit a bit (complemento a uno) | `~a` |
| `<<` | Shift a sinistra | `a << n` |
| `>>` | Shift a destra | `a >> n` |

## Rappresentazione binaria

Per comprendere gli operatori bit a bit, è importante capire come i numeri sono rappresentati in formato binario. In C, i numeri interi sono memorizzati come sequenze di bit (0 e 1).

Per esempio, il numero decimale 13 in binario è rappresentato come 1101 (2^3 + 2^2 + 2^0).

```c
#include <stdio.h>

int main() {
    int num = 13;  // 1101 in binario
    
    printf("%d in binario: ", num);
    
    // Stampa la rappresentazione binaria di num
    for (int i = 7; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
    
    return 0;
}
```

## Utilizzo degli operatori bit a bit

### Operatore AND bit a bit (&)

L'operatore AND bit a bit confronta ciascuna coppia di bit corrispondenti e restituisce 1 solo se entrambi i bit sono 1, altrimenti restituisce 0.

| Bit 1 | Bit 2 | Risultato |
|-------|-------|----------|
| 0 | 0 | 0 |
| 0 | 1 | 0 |
| 1 | 0 | 0 |
| 1 | 1 | 1 |

```c
#include <stdio.h>

int main() {
    int a = 12;  // 1100 in binario
    int b = 10;  // 1010 in binario
    int risultato = a & b;  // 1000 in binario (8 in decimale)
    
    printf("%d & %d = %d\n", a, b, risultato);
    return 0;
}
```

### Operatore OR bit a bit (|)

L'operatore OR bit a bit confronta ciascuna coppia di bit corrispondenti e restituisce 1 se almeno uno dei bit è 1, altrimenti restituisce 0.

| Bit 1 | Bit 2 | Risultato |
|-------|-------|----------|
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 1 |

```c
#include <stdio.h>

int main() {
    int a = 12;  // 1100 in binario
    int b = 10;  // 1010 in binario
    int risultato = a | b;  // 1110 in binario (14 in decimale)
    
    printf("%d | %d = %d\n", a, b, risultato);
    return 0;
}
```

### Operatore XOR bit a bit (^)

L'operatore XOR (OR esclusivo) bit a bit confronta ciascuna coppia di bit corrispondenti e restituisce 1 se i bit sono diversi, altrimenti restituisce 0.

| Bit 1 | Bit 2 | Risultato |
|-------|-------|----------|
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |

```c
#include <stdio.h>

int main() {
    int a = 12;  // 1100 in binario
    int b = 10;  // 1010 in binario
    int risultato = a ^ b;  // 0110 in binario (6 in decimale)
    
    printf("%d ^ %d = %d\n", a, b, risultato);
    return 0;
}
```

### Operatore NOT bit a bit (~)

L'operatore NOT bit a bit inverte tutti i bit di un valore (cambia 0 in 1 e 1 in 0).

| Bit | Risultato |
|-----|----------|
| 0 | 1 |
| 1 | 0 |

```c
#include <stdio.h>

int main() {
    unsigned char a = 12;  // 00001100 in binario
    unsigned char risultato = ~a;  // 11110011 in binario (243 in decimale per un unsigned char)
    
    printf("~%d = %d\n", a, risultato);
    return 0;
}
```

**Nota**: Il risultato dell'operatore NOT dipende dalla dimensione del tipo di dato e dalla rappresentazione dei numeri negativi (complemento a due).

### Operatore shift a sinistra (<<)

L'operatore shift a sinistra sposta tutti i bit di un valore verso sinistra di un numero specificato di posizioni. I bit vuoti a destra vengono riempiti con 0.

```c
#include <stdio.h>

int main() {
    int a = 5;  // 00000101 in binario
    int risultato = a << 2;  // 00010100 in binario (20 in decimale)
    
    printf("%d << 2 = %d\n", a, risultato);
    return 0;
}
```

Lo shift a sinistra di n posizioni equivale a moltiplicare il numero per 2^n (se non si verifica overflow).

### Operatore shift a destra (>>)

L'operatore shift a destra sposta tutti i bit di un valore verso destra di un numero specificato di posizioni. Per i numeri senza segno, i bit vuoti a sinistra vengono riempiti con 0. Per i numeri con segno, il comportamento dipende dall'implementazione (può essere aritmetico o logico).

```c
#include <stdio.h>

int main() {
    unsigned int a = 20;  // 00010100 in binario
    unsigned int risultato = a >> 2;  // 00000101 in binario (5 in decimale)
    
    printf("%u >> 2 = %u\n", a, risultato);
    return 0;
}
```

Lo shift a destra di n posizioni per numeri senza segno equivale a dividere il numero per 2^n.

## Applicazioni pratiche

### Maschere di bit

Le maschere di bit sono valori utilizzati con operatori bit a bit per isolare, impostare o cancellare bit specifici.

```c
#include <stdio.h>

int main() {
    unsigned char flags = 0;  // 00000000
    
    // Imposta il bit 1 e 3 (contando da 0)
    flags |= (1 << 1) | (1 << 3);  // 00001010
    printf("Flags dopo aver impostato i bit: %d\n", flags);
    
    // Verifica se il bit 3 è impostato
    if (flags & (1 << 3)) {
        printf("Il bit 3 è impostato\n");
    }
    
    // Cancella il bit 1
    flags &= ~(1 << 1);  // 00001000
    printf("Flags dopo aver cancellato il bit 1: %d\n", flags);
    
    // Inverte il bit 3
    flags ^= (1 << 3);  // 00000000
    printf("Flags dopo aver invertito il bit 3: %d\n", flags);
    
    return 0;
}
```

### Ottimizzazione delle prestazioni

Gli operatori bit a bit possono essere utilizzati per ottimizzare alcune operazioni:

```c
#include <stdio.h>

int main() {
    int a = 15;
    
    // Moltiplicazione per 2 usando lo shift a sinistra
    int b = a << 1;  // Equivalente a a * 2
    printf("%d * 2 = %d\n", a, b);
    
    // Divisione per 2 usando lo shift a destra
    int c = a >> 1;  // Equivalente a a / 2
    printf("%d / 2 = %d\n", a, c);
    
    // Verifica se un numero è pari o dispari
    if (a & 1) {
        printf("%d è dispari\n", a);
    } else {
        printf("%d è pari\n", a);
    }
    
    return 0;
}
```

### Scambio di valori senza variabile temporanea

```c
#include <stdio.h>

int main() {
    int a = 5, b = 10;
    
    printf("Prima dello scambio: a = %d, b = %d\n", a, b);
    
    // Scambio usando XOR
    a = a ^ b;
    b = a ^ b;  // Ora b contiene il valore originale di a
    a = a ^ b;  // Ora a contiene il valore originale di b
    
    printf("Dopo lo scambio: a = %d, b = %d\n", a, b);
    
    return 0;
}
```

## Precedenza degli operatori bit a bit

La precedenza degli operatori bit a bit in C è la seguente (dall'alto verso il basso):

1. `~` (NOT bit a bit)
2. `<<`, `>>` (shift a sinistra e a destra)
3. `&` (AND bit a bit)
4. `^` (XOR bit a bit)
5. `|` (OR bit a bit)

È sempre consigliabile utilizzare le parentesi per rendere chiara l'intenzione e evitare errori dovuti alla precedenza degli operatori.

## Best practice

1. **Utilizzare parentesi per chiarezza**: Anche quando non strettamente necessarie, le parentesi rendono il codice più leggibile e meno soggetto a errori.

   ```c
   int risultato = (a & b) | (c & d);  // Più chiaro di: a & b | c & d
   ```

2. **Utilizzare costanti simboliche per le maschere di bit**: Rende il codice più leggibile e manutenibile.

   ```c
   #define BIT_0 (1 << 0)
   #define BIT_1 (1 << 1)
   #define BIT_2 (1 << 2)
   
   unsigned char flags = 0;
   flags |= BIT_0 | BIT_2;  // Più chiaro di: flags |= (1 << 0) | (1 << 2)
   ```

3. **Fare attenzione agli effetti collaterali**: Gli operatori bit a bit possono avere effetti collaterali non intenzionali, specialmente quando si lavora con tipi con segno.

4. **Considerare la portabilità**: Il comportamento di alcuni operatori bit a bit (come lo shift a destra su numeri con segno) può variare tra diverse implementazioni.

## Esempi pratici

### Implementazione di un insieme di bit (bitset)

```c
#include <stdio.h>

#define MAX_ELEMENTI 32
#define IMPOSTA_BIT(a, k) ((a) |= (1 << (k)))
#define CANCELLA_BIT(a, k) ((a) &= ~(1 << (k)))
#define VERIFICA_BIT(a, k) ((a) & (1 << (k)))

int main() {
    unsigned int insieme = 0;  // Insieme vuoto
    
    // Aggiungi elementi all'insieme
    IMPOSTA_BIT(insieme, 5);  // Aggiungi l'elemento 5
    IMPOSTA_BIT(insieme, 10);  // Aggiungi l'elemento 10
    IMPOSTA_BIT(insieme, 15);  // Aggiungi l'elemento 15
    
    printf("Elementi nell'insieme: ");
    for (int i = 0; i < MAX_ELEMENTI; i++) {
        if (VERIFICA_BIT(insieme, i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
    
    // Rimuovi un elemento dall'insieme
    CANCELLA_BIT(insieme, 10);
    
    printf("Elementi dopo la rimozione: ");
    for (int i = 0; i < MAX_ELEMENTI; i++) {
        if (VERIFICA_BIT(insieme, i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
    
    return 0;
}
```

### Estrazione di byte da un intero

```c
#include <stdio.h>

int main() {
    unsigned int num = 0x12345678;  // Rappresentazione esadecimale
    
    // Estrai i singoli byte
    unsigned char byte0 = (num >> 0) & 0xFF;   // Byte meno significativo
    unsigned char byte1 = (num >> 8) & 0xFF;
    unsigned char byte2 = (num >> 16) & 0xFF;
    unsigned char byte3 = (num >> 24) & 0xFF;  // Byte più significativo
    
    printf("Numero: 0x%08X\n", num);
    printf("Byte 0: 0x%02X\n", byte0);
    printf("Byte 1: 0x%02X\n", byte1);
    printf("Byte 2: 0x%02X\n", byte2);
    printf("Byte 3: 0x%02X\n", byte3);
    
    return 0;
}
```

### Conteggio dei bit impostati (popolazione di bit)

```c
#include <stdio.h>

// Funzione per contare il numero di bit impostati a 1
int conta_bit(unsigned int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

// Versione ottimizzata (algoritmo di Kernighan)
int conta_bit_kernighan(unsigned int n) {
    int count = 0;
    while (n) {
        n &= (n - 1);  // Cancella il bit meno significativo impostato a 1
        count++;
    }
    return count;
}

int main() {
    unsigned int num = 0xA5;  // 10100101 in binario
    
    printf("Numero: 0x%X\n", num);
    printf("Numero di bit impostati (metodo 1): %d\n", conta_bit(num));
    printf("Numero di bit impostati (metodo 2): %d\n", conta_bit_kernighan(num));
    
    return 0;
}
```

## Domande di autovalutazione

1. Qual è il risultato dell'espressione `5 & 3` in C?

2. Cosa succede quando si esegue uno shift a sinistra di 1 su un numero intero?

3. Come si può utilizzare l'operatore AND bit a bit per verificare se un numero è pari o dispari?

4. Qual è la differenza tra gli operatori `&` e `&&` in C?

5. Come si può impostare il bit in posizione n di una variabile senza modificare gli altri bit?

## Esercizi proposti

1. Scrivi un programma che converta un numero decimale nella sua rappresentazione binaria utilizzando gli operatori bit a bit.

2. Implementa una funzione che inverta i bit di un numero intero (ad esempio, 0101 diventa 1010).

3. Scrivi un programma che verifichi se un numero intero è una potenza di 2 utilizzando gli operatori bit a bit.

4. Implementa una funzione che ruoti i bit di un numero intero a sinistra o a destra di n posizioni.

5. Scrivi un programma che utilizzi gli operatori bit a bit per implementare un semplice sistema di permessi (lettura, scrittura, esecuzione) simile a quello dei sistemi Unix.