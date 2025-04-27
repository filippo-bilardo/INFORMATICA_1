# Lettura e Scrittura dei File in C

## Introduzione

Dopo aver appreso come aprire e chiudere i file, il passo successivo è imparare a leggere e scrivere dati. Il linguaggio C offre diverse funzioni per queste operazioni, ognuna con caratteristiche specifiche adatte a diversi scenari.

## Scrittura su File

### Scrittura di Caratteri

La funzione più semplice per scrivere un singolo carattere in un file è `fputc()`:

```c
int fputc(int c, FILE *stream);
```

Questa funzione scrive il carattere `c` nel file specificato da `stream` e restituisce il carattere scritto, o `EOF` in caso di errore.

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("output.txt", "w");
    
    if (fp == NULL) {
        printf("Errore nell'apertura del file!\n");
        return 1;
    }
    
    fputc('A', fp);  // Scrive il carattere 'A' nel file
    
    fclose(fp);
    return 0;
}
```

### Scrittura di Stringhe

Per scrivere stringhe intere, si può utilizzare la funzione `fputs()`:

```c
int fputs(const char *s, FILE *stream);
```

Questa funzione scrive la stringa `s` nel file specificato da `stream` (senza aggiungere automaticamente un carattere di nuova riga) e restituisce un valore non negativo in caso di successo, o `EOF` in caso di errore.

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("output.txt", "w");
    
    if (fp == NULL) {
        printf("Errore nell'apertura del file!\n");
        return 1;
    }
    
    fputs("Hello, World!\n", fp);  // Scrive la stringa nel file
    
    fclose(fp);
    return 0;
}
```

### Scrittura Formattata

La funzione `fprintf()` permette di scrivere dati formattati in un file, in modo simile a `printf()`:

```c
int fprintf(FILE *stream, const char *format, ...);
```

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("output.txt", "w");
    int num = 42;
    float pi = 3.14159;
    
    if (fp == NULL) {
        printf("Errore nell'apertura del file!\n");
        return 1;
    }
    
    fprintf(fp, "Numero: %d, Pi greco: %.2f\n", num, pi);
    
    fclose(fp);
    return 0;
}
```

### Scrittura Binaria

Per scrivere dati in formato binario, si utilizza la funzione `fwrite()`:

```c
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
```

Questa funzione scrive `nmemb` elementi di dimensione `size` dal buffer puntato da `ptr` nel file `stream`.

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("dati.bin", "wb");  // Apertura in modalità binaria
    int numeri[5] = {1, 2, 3, 4, 5};
    
    if (fp == NULL) {
        printf("Errore nell'apertura del file!\n");
        return 1;
    }
    
    fwrite(numeri, sizeof(int), 5, fp);  // Scrive 5 interi nel file
    
    fclose(fp);
    return 0;
}
```

## Lettura da File

### Lettura di Caratteri

La funzione `fgetc()` legge un singolo carattere da un file:

```c
int fgetc(FILE *stream);
```

Questa funzione restituisce il carattere letto come `unsigned char` convertito in `int`, o `EOF` in caso di errore o fine del file.

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("input.txt", "r");
    int c;
    
    if (fp == NULL) {
        printf("Errore nell'apertura del file!\n");
        return 1;
    }
    
    c = fgetc(fp);  // Legge un carattere dal file
    printf("Carattere letto: %c\n", c);
    
    fclose(fp);
    return 0;
}
```

### Lettura di Stringhe

La funzione `fgets()` legge una riga da un file:

```c
char *fgets(char *s, int size, FILE *stream);
```

Questa funzione legge fino a `size-1` caratteri dal file `stream` e li memorizza nella stringa `s`, aggiungendo un carattere nullo alla fine. La lettura si interrompe dopo un carattere di nuova riga, che viene incluso nella stringa, o alla fine del file.

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("input.txt", "r");
    char buffer[100];
    
    if (fp == NULL) {
        printf("Errore nell'apertura del file!\n");
        return 1;
    }
    
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("Riga letta: %s", buffer);
    }
    
    fclose(fp);
    return 0;
}
```

### Lettura Formattata

La funzione `fscanf()` permette di leggere dati formattati da un file:

```c
int fscanf(FILE *stream, const char *format, ...);
```

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("input.txt", "r");
    int num;
    float pi;
    
    if (fp == NULL) {
        printf("Errore nell'apertura del file!\n");
        return 1;
    }
    
    fscanf(fp, "%d %f", &num, &pi);  // Legge un intero e un float dal file
    printf("Numero: %d, Pi greco: %.2f\n", num, pi);
    
    fclose(fp);
    return 0;
}
```

### Lettura Binaria

Per leggere dati in formato binario, si utilizza la funzione `fread()`:

```c
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
```

Questa funzione legge `nmemb` elementi di dimensione `size` dal file `stream` e li memorizza nel buffer puntato da `ptr`.

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("dati.bin", "rb");  // Apertura in modalità binaria
    int numeri[5];
    
    if (fp == NULL) {
        printf("Errore nell'apertura del file!\n");
        return 1;
    }
    
    fread(numeri, sizeof(int), 5, fp);  // Legge 5 interi dal file
    
    for (int i = 0; i < 5; i++) {
        printf("%d ", numeri[i]);
    }
    printf("\n");
    
    fclose(fp);
    return 0;
}
```

## Verifica della Fine del File

La funzione `feof()` permette di verificare se si è raggiunta la fine del file:

```c
int feof(FILE *stream);
```

Questa funzione restituisce un valore diverso da zero se si è raggiunta la fine del file, altrimenti restituisce zero.

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("input.txt", "r");
    int c;
    
    if (fp == NULL) {
        printf("Errore nell'apertura del file!\n");
        return 1;
    }
    
    // Legge e stampa tutti i caratteri del file
    while ((c = fgetc(fp)) != EOF) {
        putchar(c);
    }
    
    if (feof(fp)) {
        printf("\nFine del file raggiunta.\n");
    } else {
        printf("\nErrore durante la lettura del file.\n");
    }
    
    fclose(fp);
    return 0;
}
```

## Best Practices

1. **Controllare sempre i valori restituiti** dalle funzioni di lettura e scrittura per verificare se le operazioni sono avvenute con successo.
2. **Utilizzare le funzioni appropriate** in base al tipo di dati da leggere o scrivere.
3. **Gestire correttamente la fine del file** utilizzando `feof()` per distinguere tra errori e fine del file.
4. **Utilizzare buffer di dimensioni adeguate** per le operazioni di lettura, per evitare overflow.

## Conclusione

Le operazioni di lettura e scrittura sono fondamentali per lavorare con i file in C. La scelta della funzione più appropriata dipende dal tipo di dati da gestire e dalle specifiche esigenze dell'applicazione.

## Esercizi

1. Scrivi un programma che legga un file di testo carattere per carattere e lo copi in un altro file, convertendo tutti i caratteri in maiuscolo.
2. Implementa un programma che legga un file contenente numeri interi (uno per riga) e calcoli la loro somma e media.
3. Crea un programma che legga un file binario contenente una serie di strutture dati e ne stampi il contenuto in formato leggibile.