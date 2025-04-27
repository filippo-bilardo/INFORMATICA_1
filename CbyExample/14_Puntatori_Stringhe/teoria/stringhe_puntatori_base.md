# Stringhe e Puntatori: Concetti Base

## Rappresentazione delle stringhe in C

In C, le stringhe sono rappresentate come array di caratteri terminati dal carattere nullo '\0'. Questo carattere speciale indica la fine della stringa ed è fondamentale per il corretto funzionamento delle funzioni di manipolazione delle stringhe.

```c
char stringa[6] = "Ciao"; // Occupa 5 byte: 'C', 'i', 'a', 'o', '\0'
```

È importante notare che la dimensione dell'array deve essere almeno un carattere più grande rispetto alla lunghezza della stringa per ospitare il carattere terminatore.

## Stringhe e puntatori

Le stringhe in C possono essere manipolate efficacemente utilizzando i puntatori. Un puntatore a carattere può essere utilizzato per riferirsi a una stringa.

```c
char *ptr = "Ciao"; // ptr punta al primo carattere della stringa
```

Esiste una differenza importante tra questi due approcci:

```c
char str[10] = "Ciao";  // Array di caratteri (modificabile)
char *ptr = "Ciao";     // Puntatore a una stringa costante (non modificabile)
```

Nel primo caso, `str` è un array che contiene i caratteri della stringa, e questi possono essere modificati. Nel secondo caso, `ptr` punta a una stringa costante memorizzata in un'area di memoria di sola lettura, quindi tentare di modificarla può causare errori di runtime.

## Accesso ai caratteri di una stringa

I caratteri di una stringa possono essere accessibili sia tramite la notazione degli array che tramite i puntatori:

```c
#include <stdio.h>

int main() {
    char str[] = "Ciao";
    char *ptr = str;
    
    // Accesso tramite notazione array
    printf("Primo carattere (array): %c\n", str[0]);
    
    // Accesso tramite puntatore
    printf("Primo carattere (puntatore): %c\n", *ptr);
    
    // Avanzamento del puntatore
    ptr++;
    printf("Secondo carattere (puntatore avanzato): %c\n", *ptr);
    
    return 0;
}
```

## Aritmetica dei puntatori con le stringhe

L'aritmetica dei puntatori è particolarmente utile quando si lavora con le stringhe:

```c
#include <stdio.h>

int main() {
    char str[] = "Programmazione in C";
    char *ptr = str;
    
    // Scorrere la stringa carattere per carattere
    while (*ptr != '\0') {
        printf("%c", *ptr);
        ptr++;
    }
    
    return 0;
}
```

Questo codice stampa la stringa carattere per carattere, avanzando il puntatore fino a raggiungere il carattere terminatore.

## Passaggio di stringhe alle funzioni

Quando si passano stringhe alle funzioni, si passa in realtà l'indirizzo del primo carattere:

```c
#include <stdio.h>

void stampa_stringa(char *str) {
    while (*str != '\0') {
        printf("%c", *str);
        str++;
    }
    printf("\n");
}

int main() {
    char messaggio[] = "Ciao, mondo!";
    stampa_stringa(messaggio);
    return 0;
}
```

La funzione `stampa_stringa` riceve un puntatore al primo carattere della stringa e la percorre fino a trovare il carattere terminatore.

## Confronto tra stringhe

Per confrontare due stringhe, non si può utilizzare l'operatore `==` che confronterebbe solo gli indirizzi. È necessario confrontare carattere per carattere:

```c
#include <stdio.h>

int confronta_stringhe(char *s1, char *s2) {
    while (*s1 != '\0' && *s2 != '\0') {
        if (*s1 != *s2) {
            return 0; // Stringhe diverse
        }
        s1++;
        s2++;
    }
    
    // Se entrambe le stringhe sono terminate, sono uguali
    return (*s1 == '\0' && *s2 == '\0');
}

int main() {
    char str1[] = "Ciao";
    char str2[] = "Ciao";
    char str3[] = "Mondo";
    
    printf("str1 e str2 sono %s\n", confronta_stringhe(str1, str2) ? "uguali" : "diverse");
    printf("str1 e str3 sono %s\n", confronta_stringhe(str1, str3) ? "uguali" : "diverse");
    
    return 0;
}
```

## Copia di stringhe

Per copiare una stringa in un'altra, è necessario copiare carattere per carattere:

```c
#include <stdio.h>

void copia_stringa(char *dest, char *src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0'; // Aggiungi il carattere terminatore
}

int main() {
    char origine[] = "Programmazione";
    char destinazione[20]; // Assicurati che ci sia spazio sufficiente
    
    copia_stringa(destinazione, origine);
    printf("Stringa copiata: %s\n", destinazione);
    
    return 0;
}
```

## Concatenazione di stringhe

La concatenazione consiste nell'aggiungere una stringa alla fine di un'altra:

```c
#include <stdio.h>

void concatena_stringhe(char *dest, char *src) {
    // Trova la fine della stringa di destinazione
    while (*dest != '\0') {
        dest++;
    }
    
    // Copia la stringa sorgente alla fine della destinazione
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    
    *dest = '\0'; // Aggiungi il carattere terminatore
}

int main() {
    char dest[50] = "Ciao, ";
    char src[] = "mondo!";
    
    concatena_stringhe(dest, src);
    printf("Risultato: %s\n", dest);
    
    return 0;
}
```

## Calcolo della lunghezza di una stringa

Per calcolare la lunghezza di una stringa (escluso il carattere terminatore), si può utilizzare un puntatore:

```c
#include <stdio.h>

int lunghezza_stringa(char *str) {
    int lunghezza = 0;
    while (*str != '\0') {
        lunghezza++;
        str++;
    }
    return lunghezza;
}

int main() {
    char messaggio[] = "Programmazione in C";
    printf("La lunghezza della stringa è: %d\n", lunghezza_stringa(messaggio));
    return 0;
}
```

## Esercizi proposti

1. Scrivi una funzione che conti il numero di occorrenze di un carattere specifico in una stringa.

2. Implementa una funzione che inverta una stringa (senza utilizzare una stringa di appoggio).

3. Scrivi una funzione che verifichi se una stringa è un palindromo (si legge allo stesso modo da sinistra a destra e da destra a sinistra).

4. Implementa una funzione che converta tutti i caratteri di una stringa in maiuscolo.

5. Scrivi una funzione che estragga una sottostringa da una stringa data, specificando la posizione iniziale e la lunghezza.

## Domande di autovalutazione

1. Qual è la differenza tra dichiarare una stringa come array di caratteri e come puntatore a carattere?

2. Perché è importante il carattere terminatore '\0' nelle stringhe C?

3. Come si può accedere al terzo carattere di una stringa utilizzando sia la notazione degli array che i puntatori?

4. Perché non si può utilizzare l'operatore `==` per confrontare due stringhe in C?

5. Quali sono i vantaggi dell'utilizzo dei puntatori nella manipolazione delle stringhe?

6. Come si può determinare se una stringa è più lunga di un'altra senza utilizzare funzioni di libreria?

7. Quali precauzioni bisogna prendere quando si copia una stringa in un'altra per evitare buffer overflow?

8. Come si può implementare una funzione che cerchi una sottostringa all'interno di una stringa più grande utilizzando i puntatori?