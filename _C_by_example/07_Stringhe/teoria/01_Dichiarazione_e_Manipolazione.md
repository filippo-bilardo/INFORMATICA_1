# Dichiarazione e Manipolazione di Stringhe in C

In C, le stringhe sono implementate come array di caratteri terminati da un carattere speciale chiamato "null terminator" (`'\0'`). Questa guida esplora come dichiarare, inizializzare e manipolare le stringhe in C.

## Definizione di Stringhe in C

Una stringa in C è essenzialmente un array di caratteri che termina con il carattere null (`'\0'`). Questo carattere speciale indica la fine della stringa e permette alle funzioni di manipolazione delle stringhe di sapere dove termina la stringa.

```c
// Una stringa è un array di caratteri
char stringa[6]; // Può contenere 5 caratteri + il terminatore null
```

## Inizializzazione di Stringhe

Ci sono diversi modi per inizializzare una stringa in C:

```c
// Inizializzazione con una stringa letterale
char nome[10] = "Mario"; // Il compilatore aggiunge automaticamente '\0'

// Inizializzazione carattere per carattere
char citta[6] = {'R', 'o', 'm', 'a', '\0'}; // Nota il terminatore null esplicito

// Inizializzazione senza specificare la dimensione
char paese[] = "Italia"; // Il compilatore calcola la dimensione necessaria

// Inizializzazione con puntatore a char (stringa costante)
const char *messaggio = "Ciao, mondo!"; // Non modificabile
```

## Il Carattere Terminatore Null ('\0')

Il carattere terminatore null è fondamentale per le stringhe in C:

```c
// Esempio che mostra l'importanza del terminatore null
char stringa1[6] = "Ciao"; // Corretto: 'C', 'i', 'a', 'o', '\0'
char stringa2[5] = {'C', 'i', 'a', 'o', '\0'}; // Corretto
char stringa3[4] = {'C', 'i', 'a', 'o'}; // Errato: manca il terminatore null

// La funzione printf si aspetta un terminatore null
printf("%s\n", stringa1); // Funziona correttamente
printf("%s\n", stringa2); // Funziona correttamente
printf("%s\n", stringa3); // Comportamento indefinito: continua a leggere la memoria fino a trovare '\0'
```

## Accesso ai Caratteri di una Stringa

I caratteri di una stringa possono essere accessibili come elementi di un array:

```c
#include <stdio.h>

int main() {
    char nome[] = "Mario";
    
    // Accesso a singoli caratteri
    printf("Primo carattere: %c\n", nome[0]); // 'M'
    printf("Terzo carattere: %c\n", nome[2]); // 'r'
    
    // Modifica di un carattere
    nome[0] = 'D';
    printf("Nome modificato: %s\n", nome); // "Dario"
    
    // Iterazione attraverso i caratteri
    printf("Caratteri uno per uno: ");
    for (int i = 0; nome[i] != '\0'; i++) {
        printf("%c ", nome[i]);
    }
    printf("\n");
    
    return 0;
}
```

## Operazioni di Base sulle Stringhe

### 1. Calcolo della Lunghezza

Per calcolare la lunghezza di una stringa (senza contare il terminatore null), si può utilizzare la funzione `strlen()` dalla libreria `string.h` o implementare una propria funzione:

```c
#include <stdio.h>
#include <string.h>

// Implementazione manuale di strlen
int mia_strlen(const char *str) {
    int lunghezza = 0;
    while (str[lunghezza] != '\0') {
        lunghezza++;
    }
    return lunghezza;
}

int main() {
    char testo[] = "Esempio";
    
    // Usando la funzione della libreria standard
    printf("Lunghezza (strlen): %lu\n", strlen(testo));
    
    // Usando la nostra implementazione
    printf("Lunghezza (mia_strlen): %d\n", mia_strlen(testo));
    
    return 0;
}
```

### 2. Copia di Stringhe

Per copiare una stringa in un'altra, si può utilizzare la funzione `strcpy()` o `strncpy()` (più sicura):

```c
#include <stdio.h>
#include <string.h>

int main() {
    char origine[] = "Testo originale";
    char destinazione1[20]; // Assicurarsi che ci sia spazio sufficiente
    char destinazione2[10]; // Spazio limitato
    
    // Copia completa (potenzialmente pericolosa se destinazione è troppo piccola)
    strcpy(destinazione1, origine);
    printf("Dopo strcpy: %s\n", destinazione1);
    
    // Copia sicura con limite di caratteri
    strncpy(destinazione2, origine, 9);
    destinazione2[9] = '\0'; // Assicura la terminazione con null
    printf("Dopo strncpy: %s\n", destinazione2);
    
    return 0;
}
```

### 3. Concatenazione di Stringhe

Per unire due stringhe, si può utilizzare la funzione `strcat()` o `strncat()` (più sicura):

```c
#include <stdio.h>
#include <string.h>

int main() {
    char destinazione[50] = "Ciao, ";
    char origine[] = "mondo!";
    
    // Concatenazione standard
    strcat(destinazione, origine);
    printf("Dopo strcat: %s\n", destinazione); // "Ciao, mondo!"
    
    // Concatenazione con limite di caratteri
    char altro_testo[] = " Benvenuti in C.";
    strncat(destinazione, altro_testo, 11);
    printf("Dopo strncat: %s\n", destinazione); // "Ciao, mondo! Benvenuti"
    
    return 0;
}
```

### 4. Confronto di Stringhe

Per confrontare due stringhe, si utilizza la funzione `strcmp()` o `strncmp()`:

```c
#include <stdio.h>
#include <string.h>

int main() {
    char stringa1[] = "apple";
    char stringa2[] = "apple";
    char stringa3[] = "banana";
    
    // Confronto completo
    printf("strcmp(stringa1, stringa2): %d\n", strcmp(stringa1, stringa2)); // 0 (uguali)
    printf("strcmp(stringa1, stringa3): %d\n", strcmp(stringa1, stringa3)); // Negativo (a < b)
    printf("strcmp(stringa3, stringa1): %d\n", strcmp(stringa3, stringa1)); // Positivo (b > a)
    
    // Confronto dei primi n caratteri
    char stringa4[] = "application";
    printf("strncmp(stringa1, stringa4, 3): %d\n", strncmp(stringa1, stringa4, 3)); // 0 (i primi 3 caratteri sono uguali)
    
    return 0;
}
```

## Problemi Comuni e Best Practices

### 1. Buffer Overflow

Uno dei problemi più comuni con le stringhe in C è il buffer overflow, che si verifica quando si tenta di memorizzare più caratteri di quanti ne possa contenere l'array:

```c
// Esempio di potenziale buffer overflow
char nome[5]; // Può contenere 4 caratteri + '\0'
strcpy(nome, "Alessandro"); // ERRORE: nome non è abbastanza grande
```

Per evitare questo problema, utilizzare sempre funzioni sicure come `strncpy()` e assicurarsi che ci sia spazio sufficiente:

```c
// Approccio sicuro
char nome[5];
strncpy(nome, "Alessandro", 4);
nome[4] = '\0'; // Assicura la terminazione con null
```

### 2. Dimenticare il Terminatore Null

Assicurarsi sempre che le stringhe siano terminate correttamente con il carattere null:

```c
// Esempio di problema con il terminatore null
char buffer[10];
strncpy(buffer, "Testo lungo", 10); // Riempie tutto il buffer senza spazio per '\0'
// strncpy non aggiunge automaticamente '\0' se la stringa origine è più lunga

// Soluzione
char buffer[10];
strncpy(buffer, "Testo lungo", 9);
buffer[9] = '\0'; // Aggiunge manualmente il terminatore null
```

### 3. Utilizzo di Stringhe Letterali

Le stringhe letterali (come `"Ciao"`) sono memorizzate in un'area di memoria di sola lettura. Tentare di modificarle può causare errori:

```c
// Errore comune
char *str = "Ciao";
str[0] = 'D'; // ERRORE: tentativo di modificare una stringa costante

// Approccio corretto
char str[] = "Ciao"; // Crea una copia modificabile
str[0] = 'D'; // OK
```

## Domande di Autovalutazione

1. Qual è la differenza tra `char str[] = "Ciao"` e `char *str = "Ciao"`?

2. Perché è importante il carattere terminatore null nelle stringhe C?

3. Quali sono i vantaggi di utilizzare `strncpy()` rispetto a `strcpy()`?

4. Come si può determinare se una stringa è più lunga di un'altra senza utilizzare la funzione `strlen()`?

5. Quali problemi possono verificarsi quando si manipolano stringhe in C e come si possono evitare?

## Esercizi Proposti

1. Scrivi una funzione che inverta una stringa senza utilizzare array temporanei.

2. Implementa una funzione che conti il numero di occorrenze di un carattere specifico in una stringa.

3. Crea una funzione che verifichi se una stringa è un palindromo (si legge allo stesso modo da sinistra a destra e da destra a sinistra).

4. Scrivi un programma che rimuova tutti gli spazi da una stringa.

5. Implementa una funzione che converta tutti i caratteri di una stringa in maiuscolo senza utilizzare le funzioni della libreria standard.