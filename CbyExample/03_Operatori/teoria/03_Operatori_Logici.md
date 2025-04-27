# Operatori logici in C

Gli operatori logici in C permettono di combinare espressioni condizionali e sono fondamentali per implementare logiche decisionali complesse. Questi operatori lavorano con valori booleani: in C, il valore 0 rappresenta "falso", mentre qualsiasi valore diverso da 0 rappresenta "vero".

## Operatori logici disponibili

Il C fornisce tre operatori logici principali:

| Operatore | Descrizione | Esempio |
|-----------|-------------|--------|
| `&&` | AND logico | `a && b` |
| `\|\|` | OR logico | `a \|\| b` |
| `!` | NOT logico | `!a` |

## Utilizzo degli operatori logici

### Operatore AND (&&)

L'operatore AND logico restituisce vero solo se entrambe le espressioni sono vere.

| Espressione 1 | Espressione 2 | Risultato |
|---------------|---------------|----------|
| Falso (0) | Falso (0) | Falso (0) |
| Falso (0) | Vero (non-0) | Falso (0) |
| Vero (non-0) | Falso (0) | Falso (0) |
| Vero (non-0) | Vero (non-0) | Vero (1) |

```c
#include <stdio.h>

int main() {
    int eta = 25;
    int stipendio = 30000;
    
    // Verifica se una persona ha più di 21 anni E guadagna più di 25000
    if (eta > 21 && stipendio > 25000) {
        printf("La persona soddisfa entrambi i criteri\n");
    } else {
        printf("La persona non soddisfa entrambi i criteri\n");
    }
    
    return 0;
}
```

### Operatore OR (||)

L'operatore OR logico restituisce vero se almeno una delle espressioni è vera.

| Espressione 1 | Espressione 2 | Risultato |
|---------------|---------------|----------|
| Falso (0) | Falso (0) | Falso (0) |
| Falso (0) | Vero (non-0) | Vero (1) |
| Vero (non-0) | Falso (0) | Vero (1) |
| Vero (non-0) | Vero (non-0) | Vero (1) |

```c
#include <stdio.h>

int main() {
    int eta = 17;
    int accompagnato = 1;  // 1 = vero, accompagnato da un adulto
    
    // Verifica se una persona può entrare in un cinema (età >= 18 OPPURE accompagnato)
    if (eta >= 18 || accompagnato) {
        printf("Può entrare nel cinema\n");
    } else {
        printf("Non può entrare nel cinema\n");
    }
    
    return 0;
}
```

### Operatore NOT (!)

L'operatore NOT logico inverte il valore di verità di un'espressione.

| Espressione | Risultato |
|-------------|----------|
| Falso (0) | Vero (1) |
| Vero (non-0) | Falso (0) |

```c
#include <stdio.h>

int main() {
    int piove = 1;  // 1 = vero, sta piovendo
    
    if (!piove) {
        printf("Non sta piovendo, possiamo uscire\n");
    } else {
        printf("Sta piovendo, meglio restare a casa\n");
    }
    
    return 0;
}
```

## Valutazione a corto circuito

Gli operatori `&&` e `||` in C utilizzano la valutazione a corto circuito (short-circuit evaluation), il che significa che il secondo operando viene valutato solo se necessario:

- Per `&&`: se il primo operando è falso, il risultato sarà falso indipendentemente dal secondo operando, quindi il secondo operando non viene valutato.
- Per `||`: se il primo operando è vero, il risultato sarà vero indipendentemente dal secondo operando, quindi il secondo operando non viene valutato.

Questo comportamento è utile per evitare errori o operazioni costose:

```c
#include <stdio.h>

int main() {
    int a = 5;
    int b = 0;
    
    // Evita la divisione per zero grazie alla valutazione a corto circuito
    if (b != 0 && a / b > 2) {
        printf("a/b è maggiore di 2\n");
    } else {
        printf("Condizione non soddisfatta o divisione per zero evitata\n");
    }
    
    return 0;
}
```

## Precedenza degli operatori logici

La precedenza degli operatori logici in C è la seguente (dall'alto verso il basso):

1. `!` (NOT)
2. `&&` (AND)
3. `||` (OR)

È sempre consigliabile utilizzare le parentesi per rendere chiara l'intenzione e evitare errori dovuti alla precedenza degli operatori.

```c
#include <stdio.h>

int main() {
    int a = 5, b = 10, c = 15;
    
    // Senza parentesi: prima viene valutato a > b (falso), poi !false && c > b (vero)
    if (!a > b && c > b) {
        printf("Condizione 1 vera\n");
    } else {
        printf("Condizione 1 falsa\n");
    }
    
    // Con parentesi: prima viene valutato !(a > b) (vero), poi true && c > b (vero)
    if (!(a > b) && c > b) {
        printf("Condizione 2 vera\n");
    } else {
        printf("Condizione 2 falsa\n");
    }
    
    return 0;
}
```

## Combinazione di operatori logici e di confronto

Gli operatori logici vengono spesso utilizzati insieme agli operatori di confronto per creare condizioni complesse:

```c
#include <stdio.h>

int main() {
    int eta = 25;
    int stipendio = 30000;
    int esperienza = 3;
    
    // Verifica criteri complessi per un lavoro
    if ((eta >= 21 && eta <= 40) && (stipendio > 25000 || esperienza >= 5)) {
        printf("Candidato idoneo\n");
    } else {
        printf("Candidato non idoneo\n");
    }
    
    return 0;
}
```

## Operatori logici a livello di bit

Oltre agli operatori logici standard, C fornisce anche operatori logici a livello di bit (`&`, `|`, `^`, `~`), che operano sui singoli bit dei valori. Questi sono diversi dagli operatori logici discussi qui e verranno trattati separatamente.

## Best practice

1. **Utilizzare parentesi per chiarezza**: Anche quando non strettamente necessarie, le parentesi rendono il codice più leggibile e meno soggetto a errori.

   ```c
   if ((a > b) && (c < d)) {  // Più chiaro di: if (a > b && c < d)
       // Codice
   }
   ```

2. **Sfruttare la valutazione a corto circuito**: Posizionare le condizioni più semplici o più probabili prima nelle espressioni `&&` e `||` per migliorare l'efficienza.

3. **Evitare espressioni troppo complesse**: Suddividere espressioni logiche complesse in parti più semplici utilizzando variabili intermedie per migliorare la leggibilità.

   ```c
   // Invece di:
   if (a > b && c < d && e == f && g != h) {
       // Codice
   }
   
   // Meglio:
   bool condizione1 = (a > b && c < d);
   bool condizione2 = (e == f && g != h);
   if (condizione1 && condizione2) {
       // Codice
   }
   ```

4. **Attenzione ai valori non booleani**: Ricordare che in C qualsiasi valore diverso da zero è considerato vero, il che può portare a comportamenti inaspettati.

## Esempi pratici

### Verifica di un numero in un intervallo

```c
#include <stdio.h>

int main() {
    int numero;
    
    printf("Inserisci un numero: ");
    scanf("%d", &numero);
    
    if (numero >= 1 && numero <= 100) {
        printf("%d è compreso tra 1 e 100\n", numero);
    } else {
        printf("%d non è compreso tra 1 e 100\n", numero);
    }
    
    return 0;
}
```

### Verifica di un anno bisestile

```c
#include <stdio.h>

int main() {
    int anno;
    
    printf("Inserisci un anno: ");
    scanf("%d", &anno);
    
    // Un anno è bisestile se è divisibile per 4 ma non per 100, oppure se è divisibile per 400
    if ((anno % 4 == 0 && anno % 100 != 0) || (anno % 400 == 0)) {
        printf("%d è un anno bisestile\n", anno);
    } else {
        printf("%d non è un anno bisestile\n", anno);
    }
    
    return 0;
}
```

### Validazione dell'input utente

```c
#include <stdio.h>

int main() {
    int voto;
    
    printf("Inserisci un voto (0-100): ");
    scanf("%d", &voto);
    
    if (voto >= 0 && voto <= 100) {
        if (voto >= 60) {
            printf("Promosso\n");
        } else {
            printf("Bocciato\n");
        }
    } else {
        printf("Voto non valido. Deve essere compreso tra 0 e 100.\n");
    }
    
    return 0;
}
```

### Implementazione di un menu semplice

```c
#include <stdio.h>

int main() {
    char scelta;
    
    printf("Menu:\n");
    printf("a - Opzione A\n");
    printf("b - Opzione B\n");
    printf("c - Opzione C\n");
    printf("q - Esci\n");
    printf("Inserisci la tua scelta: ");
    scanf(" %c", &scelta);  // Nota lo spazio prima di %c per ignorare whitespace
    
    if (scelta == 'a' || scelta == 'b' || scelta == 'c') {
        printf("Hai selezionato l'opzione %c\n", scelta);
    } else if (scelta == 'q') {
        printf("Uscita dal programma\n");
    } else {
        printf("Scelta non valida\n");
    }
    
    return 0;
}
```

## Domande di autovalutazione

1. Qual è il risultato dell'espressione `(5 > 3) && (2 < 1)` in C?

2. Cosa succede quando si valuta l'espressione `(a > 0) || (b / a > 2)` se `a` è zero?

3. Come si può verificare se un numero non è compreso nell'intervallo tra 10 e 20?

4. Qual è la differenza tra gli operatori `&` e `&&` in C?

5. Perché è importante l'ordine delle condizioni quando si utilizza la valutazione a corto circuito?

## Esercizi proposti

1. Scrivi un programma che legga tre numeri e determini se possono formare un triangolo (la somma di due lati qualsiasi deve essere maggiore del terzo lato).

2. Implementa un programma che verifichi se un carattere inserito è una vocale, una consonante o un altro tipo di carattere.

3. Crea un programma che legga un numero e determini se è divisibile per 2, per 3, per entrambi o per nessuno dei due.

4. Scrivi un programma che implementi una calcolatrice semplice che accetti due numeri e un operatore (+, -, *, /) e mostri il risultato, gestendo correttamente la divisione per zero.

5. Implementa un programma che simuli un sistema di login semplice, dove l'utente può accedere se inserisce il nome utente corretto E la password corretta, oppure se è un amministratore (identificato da un codice speciale).