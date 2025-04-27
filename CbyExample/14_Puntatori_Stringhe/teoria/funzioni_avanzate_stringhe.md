# Funzioni Avanzate per Stringhe

## Libreria string.h e sue funzioni principali

La libreria standard `string.h` in C fornisce numerose funzioni per la manipolazione delle stringhe. Queste funzioni sono implementate utilizzando puntatori per una gestione efficiente delle stringhe.

```c
#include <string.h>
```

Ecco alcune delle funzioni più importanti:

### strlen - Calcolo della lunghezza di una stringa

```c
size_t strlen(const char *s);
```

Questa funzione calcola la lunghezza di una stringa (escluso il carattere terminatore '\0').

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Programmazione in C";
    size_t lunghezza = strlen(str);
    
    printf("La lunghezza della stringa è: %zu\n", lunghezza);
    return 0;
}
```

### strcpy e strncpy - Copia di stringhe

```c
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
```

`strcpy` copia la stringa sorgente (incluso il carattere terminatore) nella stringa di destinazione. `strncpy` copia al massimo `n` caratteri.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char src[] = "Programmazione";
    char dest1[20];
    char dest2[20];
    
    strcpy(dest1, src);
    printf("strcpy: %s\n", dest1);
    
    strncpy(dest2, src, 5); // Copia solo i primi 5 caratteri
    dest2[5] = '\0'; // Importante: strncpy non aggiunge automaticamente '\0'
    printf("strncpy: %s\n", dest2);
    
    return 0;
}
```

### strcat e strncat - Concatenazione di stringhe

```c
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, size_t n);
```

`strcat` aggiunge la stringa sorgente alla fine della stringa di destinazione. `strncat` aggiunge al massimo `n` caratteri.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char dest[50] = "Ciao, ";
    char src[] = "mondo!";
    
    strcat(dest, src);
    printf("Risultato: %s\n", dest);
    
    char dest2[50] = "Salve, ";
    strncat(dest2, "universo!", 3); // Aggiunge solo "uni"
    printf("Risultato con strncat: %s\n", dest2);
    
    return 0;
}
```

### strcmp e strncmp - Confronto di stringhe

```c
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
```

`strcmp` confronta due stringhe e restituisce un valore intero che indica la relazione tra di esse. `strncmp` confronta al massimo `n` caratteri.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str1[] = "Ciao";
    char str2[] = "Ciao";
    char str3[] = "Mondo";
    
    int risultato1 = strcmp(str1, str2);
    int risultato2 = strcmp(str1, str3);
    
    printf("Confronto str1 e str2: %d\n", risultato1); // 0 se uguali
    printf("Confronto str1 e str3: %d\n", risultato2); // Valore negativo se str1 < str3
    
    return 0;
}
```

## Implementazione manuale delle funzioni di string.h

Comprendere come implementare queste funzioni utilizzando i puntatori è fondamentale per padroneggiare la manipolazione delle stringhe in C.

### Implementazione di strlen

```c
size_t mia_strlen(const char *s) {
    const char *p = s;
    
    while (*p != '\0') {
        p++;
    }
    
    return p - s;
}
```

Questa implementazione utilizza l'aritmetica dei puntatori per calcolare la lunghezza della stringa.

### Implementazione di strcpy

```c
char *mio_strcpy(char *dest, const char *src) {
    char *original_dest = dest;
    
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    
    *dest = '\0'; // Aggiungi il carattere terminatore
    return original_dest;
}
```

### Implementazione di strcat

```c
char *mio_strcat(char *dest, const char *src) {
    char *original_dest = dest;
    
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
    return original_dest;
}
```

### Implementazione di strcmp

```c
int mio_strcmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    
    return (unsigned char)*s1 - (unsigned char)*s2;
}
```

## Funzioni avanzate per la ricerca nelle stringhe

### strchr e strrchr - Ricerca di un carattere

```c
char *strchr(const char *s, int c);
char *strrchr(const char *s, int c);
```

`strchr` trova la prima occorrenza di un carattere in una stringa. `strrchr` trova l'ultima occorrenza.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Programmazione in C";
    char *prima = strchr(str, 'a');
    char *ultima = strrchr(str, 'a');
    
    if (prima != NULL) {
        printf("Prima 'a' trovata alla posizione: %ld\n", prima - str);
    }
    
    if (ultima != NULL) {
        printf("Ultima 'a' trovata alla posizione: %ld\n", ultima - str);
    }
    
    return 0;
}
```

### strstr - Ricerca di una sottostringa

```c
char *strstr(const char *haystack, const char *needle);
```

Questa funzione trova la prima occorrenza di una sottostringa in una stringa.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Programmazione in C è divertente";
    char *sottostringa = strstr(str, "in C");
    
    if (sottostringa != NULL) {
        printf("Sottostringa trovata alla posizione: %ld\n", sottostringa - str);
        printf("Testo da quella posizione: %s\n", sottostringa);
    }
    
    return 0;
}
```

## Tokenizzazione delle stringhe

### strtok - Divisione di una stringa in token

```c
char *strtok(char *str, const char *delim);
```

Questa funzione divide una stringa in una serie di token utilizzando i delimitatori specificati.

```c
#include <stdio.h>
#include <string.h>

int main() {
    char frase[] = "Questa,è,una,frase,di,esempio";
    char *token;
    
    // Prima chiamata a strtok
    token = strtok(frase, ",");
    
    // Chiamate successive
    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, ",");
    }
    
    return 0;
}
```

È importante notare che `strtok` modifica la stringa originale sostituendo i delimitatori con caratteri '\0'.

## Conversione di stringhe

### atoi, atol, atof - Conversione da stringa a numero

```c
int atoi(const char *nptr);
long atol(const char *nptr);
double atof(const char *nptr);
```

Queste funzioni convertono una stringa in un valore numerico.

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    char str_int[] = "12345";
    char str_long[] = "123456789";
    char str_double[] = "123.456";
    
    int valore_int = atoi(str_int);
    long valore_long = atol(str_long);
    double valore_double = atof(str_double);
    
    printf("Intero: %d\n", valore_int);
    printf("Long: %ld\n", valore_long);
    printf("Double: %f\n", valore_double);
    
    return 0;
}
```

### strtol, strtod - Conversione avanzata con controllo degli errori

```c
long strtol(const char *nptr, char **endptr, int base);
double strtod(const char *nptr, char **endptr);
```

Queste funzioni offrono un controllo più preciso sulla conversione.

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    char str[] = "12345abc";
    char *endptr;
    
    long valore = strtol(str, &endptr, 10);
    
    printf("Valore convertito: %ld\n", valore);
    printf("Parte non convertita: %s\n", endptr);
    
    return 0;
}
```

## Conclusione

Le funzioni avanzate per la manipolazione delle stringhe in C sono strumenti potenti che, se utilizzate correttamente, permettono di gestire efficacemente le stringhe. La comprensione di come queste funzioni utilizzano i puntatori internamente è fondamentale per scrivere codice C efficiente e sicuro.

Ricordate sempre di verificare che ci sia spazio sufficiente nelle stringhe di destinazione e di gestire correttamente il carattere terminatore '\0' quando manipolate manualmente le stringhe.