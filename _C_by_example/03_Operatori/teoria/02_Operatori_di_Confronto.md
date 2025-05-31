# Operatori di confronto in C

Gli operatori di confronto in C permettono di confrontare due valori e restituiscono un risultato booleano (vero o falso). In C, il valore 0 rappresenta "falso", mentre qualsiasi valore diverso da 0 rappresenta "vero".

## Operatori di confronto disponibili

Il C fornisce i seguenti operatori di confronto:

| Operatore | Descrizione | Esempio |
|-----------|-------------|--------|
| `==` | Uguale a | `a == b` |
| `!=` | Diverso da | `a != b` |
| `>` | Maggiore di | `a > b` |
| `<` | Minore di | `a < b` |
| `>=` | Maggiore o uguale a | `a >= b` |
| `<=` | Minore o uguale a | `a <= b` |

## Utilizzo degli operatori di confronto

Gli operatori di confronto vengono tipicamente utilizzati nelle strutture di controllo come `if`, `while`, e `for` per prendere decisioni basate sul confronto di valori.

### Operatore di uguaglianza (==)

L'operatore di uguaglianza verifica se due valori sono uguali.

```c
#include <stdio.h>

int main() {
    int a = 5, b = 5, c = 10;
    
    if (a == b) {
        printf("%d è uguale a %d\n", a, b);
    }
    
    if (a == c) {
        printf("%d è uguale a %d\n", a, c);
    } else {
        printf("%d non è uguale a %d\n", a, c);
    }
    
    return 0;
}
```

**Attenzione**: Non confondere l'operatore di uguaglianza `==` con l'operatore di assegnazione `=`. Un errore comune è scrivere `if (a = b)` invece di `if (a == b)`, il che assegna il valore di `b` ad `a` e poi valuta `a` come condizione.

### Operatore di disuguaglianza (!=)

L'operatore di disuguaglianza verifica se due valori sono diversi.

```c
#include <stdio.h>

int main() {
    int a = 5, b = 10;
    
    if (a != b) {
        printf("%d è diverso da %d\n", a, b);
    }
    
    return 0;
}
```

### Operatori di confronto maggiore (>) e minore (<)

Questi operatori verificano se un valore è maggiore o minore di un altro.

```c
#include <stdio.h>

int main() {
    int a = 5, b = 10;
    
    if (a < b) {
        printf("%d è minore di %d\n", a, b);
    }
    
    if (b > a) {
        printf("%d è maggiore di %d\n", b, a);
    }
    
    return 0;
}
```

### Operatori maggiore o uguale (>=) e minore o uguale (<=)

Questi operatori verificano se un valore è maggiore/minore o uguale a un altro.

```c
#include <stdio.h>

int main() {
    int a = 5, b = 5, c = 10;
    
    if (a <= b) {
        printf("%d è minore o uguale a %d\n", a, b);
    }
    
    if (c >= b) {
        printf("%d è maggiore o uguale a %d\n", c, b);
    }
    
    return 0;
}
```

## Confronto tra tipi di dati diversi

Quando si confrontano valori di tipi diversi, il C esegue automaticamente una conversione di tipo (promozione) secondo regole specifiche:

1. Se uno degli operandi è di tipo `long double`, l'altro viene convertito in `long double`
2. Altrimenti, se uno degli operandi è di tipo `double`, l'altro viene convertito in `double`
3. Altrimenti, se uno degli operandi è di tipo `float`, l'altro viene convertito in `float`
4. Altrimenti, viene applicata la promozione intera (i tipi più piccoli di `int` vengono convertiti in `int`)
5. Se uno degli operandi è di tipo `long long`, l'altro viene convertito in `long long`
6. Altrimenti, se uno degli operandi è di tipo `long`, l'altro viene convertito in `long`

```c
#include <stdio.h>

int main() {
    int a = 5;
    float b = 5.0;
    
    if (a == b) {  // a viene convertito in float prima del confronto
        printf("a e b sono uguali\n");
    }
    
    return 0;
}
```

## Confronto di caratteri

I caratteri in C sono rappresentati internamente come valori interi (codice ASCII), quindi possono essere confrontati utilizzando gli operatori di confronto.

```c
#include <stdio.h>

int main() {
    char ch1 = 'A', ch2 = 'B';
    
    if (ch1 < ch2) {  // Confronta i valori ASCII: 'A' (65) < 'B' (66)
        printf("%c viene prima di %c nell'alfabeto\n", ch1, ch2);
    }
    
    return 0;
}
```

## Confronto di puntatori

Gli operatori di confronto possono essere utilizzati anche con i puntatori, ma il risultato dipende dall'implementazione e può variare tra sistemi diversi. In generale:

- Due puntatori sono uguali (`==`) se puntano alla stessa posizione di memoria
- I confronti `<`, `>`, `<=`, `>=` tra puntatori sono significativi solo se i puntatori puntano a elementi dello stesso array

```c
#include <stdio.h>

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int *p1 = &arr[1];  // Punta al secondo elemento (20)
    int *p2 = &arr[3];  // Punta al quarto elemento (40)
    
    if (p1 == p2) {
        printf("I puntatori sono uguali\n");
    } else {
        printf("I puntatori sono diversi\n");
    }
    
    if (p1 < p2) {  // Confronto valido perché entrambi puntano allo stesso array
        printf("p1 punta a un elemento che viene prima di quello puntato da p2\n");
    }
    
    return 0;
}
```

## Utilizzo degli operatori di confronto nelle espressioni

Gli operatori di confronto restituiscono 1 (vero) o 0 (falso), quindi possono essere utilizzati in espressioni aritmetiche.

```c
#include <stdio.h>

int main() {
    int a = 5, b = 10;
    int risultato = (a < b) + (a == b) + (a > b);  // 1 + 0 + 0 = 1
    
    printf("Risultato: %d\n", risultato);
    return 0;
}
```

## Best practice

1. **Evitare confusione tra `==` e `=`**: Alcuni programmatori preferiscono scrivere le costanti a sinistra nelle condizioni per evitare questo errore: `if (5 == a)` invece di `if (a == 5)`. Se per errore si scrive `if (5 = a)`, il compilatore segnalerà un errore.

2. **Attenzione ai confronti in virgola mobile**: A causa degli errori di arrotondamento, i confronti di uguaglianza esatta tra numeri in virgola mobile possono essere inaffidabili. È meglio verificare se la differenza è inferiore a una piccola tolleranza.

   ```c
   float a = 0.1 + 0.2;  // Potrebbe non essere esattamente 0.3
   float b = 0.3;
   float epsilon = 0.0001;  // Tolleranza
   
   if (fabs(a - b) < epsilon) {  // Richiede #include <math.h>
       printf("a e b sono approssimativamente uguali\n");
   }
   ```

3. **Utilizzare parentesi per chiarezza**: Quando si combinano più operatori di confronto con operatori logici, utilizzare le parentesi per rendere chiara l'intenzione.

   ```c
   if ((a > b) && (c < d)) {  // Più chiaro di: if (a > b && c < d)
       // Codice
   }
   ```

## Esempi pratici

### Verifica di un numero in un intervallo

```c
#include <stdio.h>

int main() {
    int numero, min = 1, max = 100;
    
    printf("Inserisci un numero: ");
    scanf("%d", &numero);
    
    if (numero >= min && numero <= max) {
        printf("%d è nell'intervallo [%d, %d]\n", numero, min, max);
    } else {
        printf("%d è fuori dall'intervallo [%d, %d]\n", numero, min, max);
    }
    
    return 0;
}
```

### Ordinamento di tre numeri

```c
#include <stdio.h>

int main() {
    int a, b, c, temp;
    
    printf("Inserisci tre numeri: ");
    scanf("%d %d %d", &a, &b, &c);
    
    // Ordina i numeri usando gli operatori di confronto
    if (a > b) {
        temp = a;
        a = b;
        b = temp;
    }
    
    if (b > c) {
        temp = b;
        b = c;
        c = temp;
    }
    
    if (a > b) {
        temp = a;
        a = b;
        b = temp;
    }
    
    printf("Numeri ordinati: %d %d %d\n", a, b, c);
    return 0;
}
```

### Verifica di un carattere

```c
#include <stdio.h>

int main() {
    char ch;
    
    printf("Inserisci un carattere: ");
    scanf("%c", &ch);
    
    if (ch >= 'a' && ch <= 'z') {
        printf("%c è una lettera minuscola\n", ch);
    } else if (ch >= 'A' && ch <= 'Z') {
        printf("%c è una lettera maiuscola\n", ch);
    } else if (ch >= '0' && ch <= '9') {
        printf("%c è una cifra\n", ch);
    } else {
        printf("%c è un carattere speciale\n", ch);
    }
    
    return 0;
}
```

## Domande di autovalutazione

1. Qual è la differenza tra gli operatori `==` e `=` in C?

2. Cosa restituisce l'espressione `5 > 3` in C?

3. Come si può verificare se un numero è compreso tra 10 e 20 (inclusi)?

4. Perché i confronti di uguaglianza esatta tra numeri in virgola mobile possono essere problematici?

5. Cosa succede quando si confrontano caratteri in C?

## Esercizi proposti

1. Scrivi un programma che legga due numeri dall'utente e determini se sono uguali o quale dei due è maggiore.

2. Implementa un programma che verifichi se un anno inserito dall'utente è bisestile.

3. Crea un programma che legga un carattere e determini se è una vocale o una consonante.

4. Scrivi un programma che legga tre numeri e li stampi in ordine crescente.

5. Implementa un semplice calcolatore che legga due numeri e un operatore (+, -, *, /) e mostri il risultato dell'operazione corrispondente.