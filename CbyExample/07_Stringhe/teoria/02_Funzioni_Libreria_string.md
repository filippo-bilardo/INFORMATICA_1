# Funzioni della Libreria string.h in C

La libreria standard `string.h` fornisce un insieme completo di funzioni per manipolare le stringhe in C. Questa guida esplora le funzioni più comuni e il loro utilizzo, con esempi pratici.

## Introduzione alla Libreria string.h

Per utilizzare le funzioni della libreria `string.h`, è necessario includere l'header file all'inizio del programma:

```c
#include <string.h>
```

Questo header file dichiara numerose funzioni che operano su stringhe (array di caratteri terminati da null) e su blocchi di memoria.

## Funzioni per la Manipolazione delle Stringhe

### 1. Funzioni di Copia

#### strcpy() e strncpy()

Queste funzioni copiano una stringa in un'altra:

```c
#include <stdio.h>
#include <string.h>

int main() {
    char dest[20];
    char src[] = "Programmazione in C";
    
    // strcpy - copia l'intera stringa (pericoloso se dest è troppo piccolo)
    strcpy(dest, "Hello");
    printf("Dopo strcpy: %s\n", dest);
    
    // strncpy - copia al massimo n caratteri
    strncpy(dest, src, 13);
    dest[13] = '\0'; // Importante: strncpy non aggiunge '\0' se src è più lungo di n
    printf("Dopo strncpy: %s\n", dest);
    
    return 0;
}
```

### 2. Funzioni di Concatenazione

#### strcat() e strncat()

Queste funzioni aggiungono una stringa alla fine di un'altra:

```c
#include <stdio.h>
#include <string.h>

int main() {
    char dest[50] = "Hello, ";
    char src[] = "World!";
    
    // strcat - concatena l'intera stringa
    strcat(dest, src);
    printf("Dopo strcat: %s\n", dest); // "Hello, World!"
    
    // strncat - concatena al massimo n caratteri e aggiunge '\0'
    strncat(dest, " Welcome", 5);
    printf("Dopo strncat: %s\n", dest); // "Hello, World! Welco"
    
    return 0;
}
```

### 3. Funzioni di Lunghezza

#### strlen()

Questa funzione calcola la lunghezza di una stringa (escluso il terminatore null):

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Programmazione";
    
    size_t lunghezza = strlen(str);
    printf("La lunghezza di \"%s\" è: %zu\n", str, lunghezza);
    
    return 0;
}
```

## Funzioni per la Ricerca nelle Stringhe

### 1. strchr() e strrchr()

Queste funzioni cercano la prima o l'ultima occorrenza di un carattere in una stringa:

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "esempio@email.com";
    
    // strchr - trova la prima occorrenza di un carattere
    char *prima_occorrenza = strchr(str, '@');
    if (prima_occorrenza) {
        printf("Prima '@' trovata alla posizione: %ld\n", prima_occorrenza - str);
        printf("Parte dopo '@': %s\n", prima_occorrenza + 1);
    }
    
    // strrchr - trova l'ultima occorrenza di un carattere
    char *ultima_occorrenza = strrchr(str, '.');
    if (ultima_occorrenza) {
        printf("Ultima '.' trovata alla posizione: %ld\n", ultima_occorrenza - str);
        printf("Estensione: %s\n", ultima_occorrenza + 1);
    }
    
    return 0;
}
```

### 2. strstr()

Questa funzione cerca una sottostringa all'interno di una stringa:

```c
#include <stdio.h>
#include <string.h>

int main() {
    char haystack[] = "Questo è un esempio di testo per la ricerca";
    char needle[] = "esempio";
    
    char *risultato = strstr(haystack, needle);
    if (risultato) {
        printf("Sottostringa trovata alla posizione: %ld\n", risultato - haystack);
        printf("Testo da quel punto: %s\n", risultato);
    } else {
        printf("Sottostringa non trovata\n");
    }
    
    return 0;
}
```

### 3. strspn() e strcspn()

Queste funzioni calcolano la lunghezza del segmento iniziale di una stringa che contiene (o non contiene) determinati caratteri:

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "123456abc789";
    
    // strspn - lunghezza del segmento iniziale che contiene solo i caratteri specificati
    size_t len1 = strspn(str, "0123456789");
    printf("Numero di cifre all'inizio: %zu\n", len1); // 6
    
    // strcspn - lunghezza del segmento iniziale che NON contiene i caratteri specificati
    size_t len2 = strcspn(str, "abc");
    printf("Posizione del primo carattere alfabetico: %zu\n", len2); // 6
    
    return 0;
}
```

## Funzioni per la Comparazione delle Stringhe

### 1. strcmp() e strncmp()

Queste funzioni confrontano due stringhe:

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str1[] = "apple";
    char str2[] = "apple";
    char str3[] = "banana";
    
    // strcmp - confronta due stringhe
    int risultato1 = strcmp(str1, str2);
    printf("strcmp(str1, str2): %d\n", risultato1); // 0 (uguali)
    
    int risultato2 = strcmp(str1, str3);
    printf("strcmp(str1, str3): %d\n", risultato2); // Negativo (a < b)
    
    // strncmp - confronta i primi n caratteri
    char str4[] = "application";
    int risultato3 = strncmp(str1, str4, 3);
    printf("strncmp(str1, str4, 3): %d\n", risultato3); // 0 (i primi 3 caratteri sono uguali)
    
    return 0;
}
```

### 2. strcoll()

Questa funzione confronta due stringhe tenendo conto delle impostazioni locali (locale):

```c
#include <stdio.h>
#include <string.h>
#include <locale.h>

int main() {
    setlocale(LC_COLLATE, "it_IT.UTF-8"); // Imposta il locale italiano
    
    char str1[] = "ciao";
    char str2[] = "ciào"; // Con accento
    
    int risultato = strcoll(str1, str2);
    if (risultato < 0) {
        printf("%s viene prima di %s\n", str1, str2);
    } else if (risultato > 0) {
        printf("%s viene prima di %s\n", str2, str1);
    } else {
        printf("%s e %s sono equivalenti\n", str1, str2);
    }
    
    return 0;
}
```

## Funzioni per la Conversione delle Stringhe

### 1. strtol(), strtod(), strtoul()

Queste funzioni convertono stringhe in valori numerici:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char str[] = "123.456 789 0xFF";
    char *endptr;
    
    // Conversione in double
    double valore_double = strtod(str, &endptr);
    printf("Valore double: %f\n", valore_double);
    printf("Resto della stringa: %s\n\n", endptr);
    
    // Conversione in long int (base 10)
    long int valore_long = strtol(endptr, &endptr, 10);
    printf("Valore long: %ld\n", valore_long);
    printf("Resto della stringa: %s\n\n", endptr);
    
    // Conversione in unsigned long int (base 16)
    unsigned long int valore_hex = strtoul(endptr, NULL, 16);
    printf("Valore hex: %lu (0x%lX)\n", valore_hex, valore_hex);
    
    return 0;
}
```

### 2. Funzioni di Trasformazione

#### strtok()

Questa funzione divide una stringa in token:

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Questa,è,una,stringa,separata,da,virgole";
    
    // Prima chiamata con la stringa da tokenizzare
    char *token = strtok(str, ",");
    
    // Chiamate successive con NULL per continuare la tokenizzazione
    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, ",");
    }
    
    // Nota: la stringa originale viene modificata da strtok!
    printf("\nStringa originale dopo strtok: %s\n", str); // Solo "Questa"
    
    return 0;
}
```

## Funzioni per la Manipolazione della Memoria

### 1. memcpy() e memmove()

Queste funzioni copiano blocchi di memoria:

```c
#include <stdio.h>
#include <string.h>

int main() {
    char src[] = "Programmazione in C";
    char dest1[30];
    char dest2[30];
    
    // memcpy - copia n byte (non sicuro se le aree si sovrappongono)
    memcpy(dest1, src, strlen(src) + 1); // +1 per includere '\0'
    printf("Dopo memcpy: %s\n", dest1);
    
    // Esempio con aree di memoria sovrapposte
    char overlap[20] = "abcdefghijklmnopqrs";
    
    // Sposta "defghi" 4 posizioni avanti
    // memcpy potrebbe non funzionare correttamente qui
    // memcpy(overlap + 8, overlap + 3, 6);
    
    // memmove - sicuro anche con aree sovrapposte
    memmove(overlap + 8, overlap + 3, 6);
    printf("Dopo memmove: %s\n", overlap); // "abcdefghdefghiopqrs"
    
    return 0;
}
```

### 2. memset()

Questa funzione riempie un blocco di memoria con un valore specifico:

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[20];
    
    // Riempie i primi 10 byte con 'A'
    memset(str, 'A', 10);
    str[10] = '\0'; // Aggiunge il terminatore null
    printf("Dopo memset: %s\n", str); // "AAAAAAAAAA"
    
    // Inizializza un array a zero
    int numeri[5];
    memset(numeri, 0, sizeof(numeri));
    
    printf("Array di interi dopo memset: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numeri[i]);
    }
    printf("\n");
    
    return 0;
}
```

### 3. memcmp()

Questa funzione confronta blocchi di memoria:

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str1[] = "abcdef";
    char str2[] = "abcxyz";
    
    // Confronta i primi 3 byte
    int risultato1 = memcmp(str1, str2, 3);
    printf("memcmp per i primi 3 byte: %d\n", risultato1); // 0 (uguali)
    
    // Confronta i primi 4 byte
    int risultato2 = memcmp(str1, str2, 4);
    printf("memcmp per i primi 4 byte: %d\n", risultato2); // Negativo (d < x)
    
    return 0;
}
```

## Best Practices nell'Uso delle Funzioni string.h

1. **Prevenire i Buffer Overflow**: Utilizzare sempre le versioni con limite di caratteri (`strncpy`, `strncat`) quando possibile.

2. **Gestire il Terminatore Null**: Ricordarsi che `strncpy` non aggiunge automaticamente il terminatore null se la stringa origine è più lunga di n caratteri.

3. **Controllo dei Valori di Ritorno**: Verificare sempre i valori restituiti dalle funzioni per gestire correttamente gli errori.

4. **Attenzione alle Aree di Memoria Sovrapposte**: Utilizzare `memmove` invece di `memcpy` quando le aree di memoria potrebbero sovrapporsi.

5. **Considerare le Impostazioni Locali**: Per applicazioni internazionali, utilizzare funzioni che rispettano le impostazioni locali come `strcoll`.

## Domande di Autovalutazione

1. Qual è la differenza principale tra `memcpy()` e `memmove()`?

2. Perché è importante aggiungere manualmente il terminatore null dopo una chiamata a `strncpy()`?

3. Come funziona `strtok()` e quali precauzioni bisogna prendere quando la si utilizza?

4. Quali sono i vantaggi di utilizzare `strncmp()` rispetto a `strcmp()`?

5. Come si può utilizzare `strchr()` per estrarre il dominio da un indirizzo email?

## Esercizi Proposti

1. Scrivi una funzione che conti il numero di parole in una stringa utilizzando `strtok()`.

2. Implementa una funzione che sostituisca tutte le occorrenze di una sottostringa con un'altra in una stringa data.

3. Crea un programma che legga una stringa contenente numeri separati da spazi e calcoli la loro somma utilizzando `strtol()`.

4. Scrivi una funzione che verifichi se una stringa è l'anagramma di un'altra (contiene gli stessi caratteri ma in ordine diverso).

5. Implementa una versione sicura di `strcat()` che controlli lo spazio disponibile nel buffer di destinazione prima di effettuare la concatenazione.