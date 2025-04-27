# Gestione Dinamica delle Stringhe

## Allocazione dinamica della memoria per le stringhe

In C, le stringhe possono essere allocate dinamicamente utilizzando le funzioni di gestione della memoria come `malloc()`, `calloc()` e `realloc()`. Questo approccio offre maggiore flessibilità rispetto all'uso di array di dimensione fissa.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
```

### Allocazione con malloc

```c
char *stringa = (char *)malloc(lunghezza + 1);
```

È importante aggiungere 1 alla lunghezza desiderata per ospitare il carattere terminatore '\0'.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocazione di una stringa di 10 caratteri
    char *stringa = (char *)malloc(11); // 10 caratteri + '\0'
    
    if (stringa == NULL) {
        printf("Errore di allocazione della memoria\n");
        return 1;
    }
    
    strcpy(stringa, "Ciao Mondo");
    printf("Stringa: %s\n", stringa);
    
    // Liberazione della memoria
    free(stringa);
    
    return 0;
}
```

### Allocazione con calloc

`calloc()` alloca la memoria e la inizializza a zero, il che può essere utile per le stringhe.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocazione di una stringa di 20 caratteri
    char *stringa = (char *)calloc(21, sizeof(char)); // 20 caratteri + '\0'
    
    if (stringa == NULL) {
        printf("Errore di allocazione della memoria\n");
        return 1;
    }
    
    strcpy(stringa, "Programmazione in C");
    printf("Stringa: %s\n", stringa);
    
    // Liberazione della memoria
    free(stringa);
    
    return 0;
}
```

## Ridimensionamento delle stringhe

### Utilizzo di realloc

`realloc()` permette di ridimensionare una stringa precedentemente allocata.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocazione iniziale
    char *stringa = (char *)malloc(11); // 10 caratteri + '\0'
    
    if (stringa == NULL) {
        printf("Errore di allocazione della memoria\n");
        return 1;
    }
    
    strcpy(stringa, "Ciao");
    printf("Stringa iniziale: %s\n", stringa);
    
    // Ridimensionamento per ospitare una stringa più lunga
    stringa = (char *)realloc(stringa, 21); // 20 caratteri + '\0'
    
    if (stringa == NULL) {
        printf("Errore di riallocazione della memoria\n");
        return 1;
    }
    
    strcat(stringa, " Mondo! Benvenuti");
    printf("Stringa dopo realloc: %s\n", stringa);
    
    // Liberazione della memoria
    free(stringa);
    
    return 0;
}
```

## Creazione di funzioni per la gestione dinamica delle stringhe

### Duplicazione di una stringa

Implementazione di una funzione simile a `strdup()` della libreria standard:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *duplica_stringa(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t lunghezza = strlen(str);
    char *nuova_stringa = (char *)malloc(lunghezza + 1);
    
    if (nuova_stringa == NULL) {
        return NULL; // Errore di allocazione
    }
    
    strcpy(nuova_stringa, str);
    return nuova_stringa;
}

int main() {
    char originale[] = "Questa è una stringa di test";
    char *duplicata = duplica_stringa(originale);
    
    if (duplicata != NULL) {
        printf("Originale: %s\n", originale);
        printf("Duplicata: %s\n", duplicata);
        
        free(duplicata);
    }
    
    return 0;
}
```

### Concatenazione di stringhe con allocazione dinamica

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatena_stringhe_dinamiche(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return NULL;
    }
    
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    
    char *risultato = (char *)malloc(len1 + len2 + 1);
    
    if (risultato == NULL) {
        return NULL; // Errore di allocazione
    }
    
    strcpy(risultato, str1);
    strcat(risultato, str2);
    
    return risultato;
}

int main() {
    char *str1 = "Ciao ";
    char *str2 = "Mondo!";
    
    char *concatenata = concatena_stringhe_dinamiche(str1, str2);
    
    if (concatenata != NULL) {
        printf("Risultato: %s\n", concatenata);
        free(concatenata);
    }
    
    return 0;
}
```

## Array di stringhe allocate dinamicamente

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int num_stringhe = 3;
    
    // Allocazione di un array di puntatori a char
    char **array_stringhe = (char **)malloc(num_stringhe * sizeof(char *));
    
    if (array_stringhe == NULL) {
        printf("Errore di allocazione dell'array\n");
        return 1;
    }
    
    // Allocazione di ogni stringa
    array_stringhe[0] = (char *)malloc(6); // "Ciao" + '\0'
    array_stringhe[1] = (char *)malloc(7); // "Mondo" + '\0'
    array_stringhe[2] = (char *)malloc(2); // "!" + '\0'
    
    // Controllo delle allocazioni
    for (int i = 0; i < num_stringhe; i++) {
        if (array_stringhe[i] == NULL) {
            printf("Errore di allocazione della stringa %d\n", i);
            
            // Liberazione delle stringhe già allocate
            for (int j = 0; j < i; j++) {
                free(array_stringhe[j]);
            }
            
            free(array_stringhe);
            return 1;
        }
    }
    
    // Inizializzazione delle stringhe
    strcpy(array_stringhe[0], "Ciao");
    strcpy(array_stringhe[1], "Mondo");
    strcpy(array_stringhe[2], "!");
    
    // Utilizzo delle stringhe
    for (int i = 0; i < num_stringhe; i++) {
        printf("%s ", array_stringhe[i]);
    }
    printf("\n");
    
    // Liberazione della memoria
    for (int i = 0; i < num_stringhe; i++) {
        free(array_stringhe[i]);
    }
    
    free(array_stringhe);
    
    return 0;
}
```

## Gestione degli errori nell'allocazione dinamica

La gestione degli errori è fondamentale quando si lavora con l'allocazione dinamica della memoria:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *crea_stringa_sicura(const char *str) {
    if (str == NULL) {
        fprintf(stderr, "Errore: stringa sorgente NULL\n");
        return NULL;
    }
    
    size_t lunghezza = strlen(str);
    char *nuova_stringa = (char *)malloc(lunghezza + 1);
    
    if (nuova_stringa == NULL) {
        fprintf(stderr, "Errore: impossibile allocare memoria\n");
        return NULL;
    }
    
    strcpy(nuova_stringa, str);
    return nuova_stringa;
}

int main() {
    char *stringa = crea_stringa_sicura("Test di allocazione");
    
    if (stringa != NULL) {
        printf("Stringa creata: %s\n", stringa);
        free(stringa);
    } else {
        printf("Impossibile creare la stringa\n");
    }
    
    return 0;
}
```

## Problemi comuni e come evitarli

### Memory leak (perdita di memoria)

Un memory leak si verifica quando si alloca memoria ma non la si libera correttamente:

```c
// Esempio di memory leak
void funzione_con_leak() {
    char *stringa = (char *)malloc(100);
    strcpy(stringa, "Questa memoria non verrà mai liberata");
    // Manca free(stringa)
}

// Versione corretta
void funzione_senza_leak() {
    char *stringa = (char *)malloc(100);
    strcpy(stringa, "Questa memoria verrà liberata correttamente");
    free(stringa);
}
```

### Doppia liberazione (double free)

```c
// Esempio di double free (errore)
void funzione_con_double_free() {
    char *stringa = (char *)malloc(100);
    strcpy(stringa, "Test");
    free(stringa);
    free(stringa); // Errore: doppia liberazione
}

// Versione corretta
void funzione_senza_double_free() {
    char *stringa = (char *)malloc(100);
    strcpy(stringa, "Test");
    free(stringa);
    stringa = NULL; // Buona pratica: impostare a NULL dopo free
}
```

### Accesso dopo liberazione (use after free)

```c
// Esempio di use after free (errore)
void funzione_con_use_after_free() {
    char *stringa = (char *)malloc(100);
    strcpy(stringa, "Test");
    free(stringa);
    printf("%s\n", stringa); // Errore: accesso dopo liberazione
}

// Versione corretta
void funzione_senza_use_after_free() {
    char *stringa = (char *)malloc(100);
    strcpy(stringa, "Test");
    printf("%s\n", stringa);
    free(stringa);
}
```

## Conclusione

La gestione dinamica delle stringhe in C offre grande flessibilità ma richiede attenzione per evitare errori comuni come memory leak, double free e use after free. Seguendo le best practices e controllando sempre i valori di ritorno delle funzioni di allocazione, è possibile scrivere codice robusto ed efficiente per la manipolazione delle stringhe.

Ricordate sempre di:

1. Controllare il valore di ritorno di `malloc()`, `calloc()` e `realloc()`
2. Liberare la memoria con `free()` quando non è più necessaria
3. Impostare i puntatori a `NULL` dopo averli liberati
4. Allocare sempre spazio sufficiente per il carattere terminatore '\0'
5. Gestire correttamente gli errori di allocazione