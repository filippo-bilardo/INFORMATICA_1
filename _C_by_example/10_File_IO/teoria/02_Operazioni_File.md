# Operazioni Fondamentali sui File in C

## Apertura e Chiusura dei File

### Apertura di un File

Per aprire un file in C, si utilizza la funzione `fopen()`, che ha la seguente sintassi:

```c
FILE *fopen(const char *filename, const char *mode);
```

Dove:
- `filename` è il nome del file da aprire (può includere il percorso)
- `mode` è la modalità di apertura ("r", "w", "a", ecc.)

La funzione restituisce un puntatore a `FILE` in caso di successo, o `NULL` in caso di errore.

### Chiusura di un File

Dopo aver terminato le operazioni su un file, è fondamentale chiuderlo utilizzando la funzione `fclose()`:

```c
int fclose(FILE *stream);
```

La funzione restituisce 0 in caso di successo, o `EOF` in caso di errore.

Esempio di apertura e chiusura di un file:

```c
#include <stdio.h>

int main() {
    FILE *fp;
    
    fp = fopen("dati.txt", "r");
    if (fp == NULL) {
        perror("Errore nell'apertura del file");
        return 1;
    }
    
    // Operazioni sul file...
    
    fclose(fp);
    return 0;
}
```

## Lettura da File

C offre diverse funzioni per leggere dati da un file:

### Lettura di Caratteri

```c
int fgetc(FILE *stream);
```

Legge un singolo carattere dal file e lo restituisce come intero. Restituisce `EOF` alla fine del file o in caso di errore.

Esempio:

```c
#include <stdio.h>

int main() {
    FILE *fp;
    int c;
    
    fp = fopen("testo.txt", "r");
    if (fp == NULL) {
        perror("Errore nell'apertura del file");
        return 1;
    }
    
    // Legge e stampa tutti i caratteri del file
    while ((c = fgetc(fp)) != EOF) {
        putchar(c);
    }
    
    fclose(fp);
    return 0;
}
```

### Lettura di Stringhe

```c
char *fgets(char *str, int n, FILE *stream);
```

Legge al massimo `n-1` caratteri dal file e li memorizza in `str`, aggiungendo il carattere null (`\0`) alla fine. La lettura si interrompe quando si incontra un carattere di nuova linea, la fine del file o quando sono stati letti `n-1` caratteri.

Esempio:

```c
#include <stdio.h>

int main() {
    FILE *fp;
    char buffer[100];
    
    fp = fopen("testo.txt", "r");
    if (fp == NULL) {
        perror("Errore nell'apertura del file");
        return 1;
    }
    
    // Legge e stampa tutte le righe del file
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    
    fclose(fp);
    return 0;
}
```

### Lettura Formattata

```c
int fscanf(FILE *stream, const char *format, ...);
```

Legge dati dal file secondo il formato specificato. Funziona in modo simile a `scanf()`, ma legge da un file anziché dallo standard input.

Esempio:

```c
#include <stdio.h>

int main() {
    FILE *fp;
    int num;
    char str[50];
    
    fp = fopen("dati.txt", "r");
    if (fp == NULL) {
        perror("Errore nell'apertura del file");
        return 1;
    }
    
    // Legge un intero e una stringa dal file
    while (fscanf(fp, "%d %s", &num, str) == 2) {
        printf("Numero: %d, Stringa: %s\n", num, str);
    }
    
    fclose(fp);
    return 0;
}
```

## Scrittura su File

C offre diverse funzioni per scrivere dati su un file:

### Scrittura di Caratteri

```c
int fputc(int c, FILE *stream);
```

Scrive un singolo carattere nel file. Restituisce il carattere scritto in caso di successo, o `EOF` in caso di errore.

Esempio:

```c
#include <stdio.h>

int main() {
    FILE *fp;
    char str[] = "Hello, World!";
    int i = 0;
    
    fp = fopen("output.txt", "w");
    if (fp == NULL) {
        perror("Errore nell'apertura del file");
        return 1;
    }
    
    // Scrive la stringa carattere per carattere
    while (str[i] != '\0') {
        fputc(str[i], fp);
        i++;
    }
    
    fclose(fp);
    return 0;
}
```

### Scrittura di Stringhe

```c
int fputs(const char *str, FILE *stream);
```

Scrive una stringa nel file (senza il carattere null terminatore). Restituisce un valore non negativo in caso di successo, o `EOF` in caso di errore.

Esempio:

```c
#include <stdio.h>

int main() {
    FILE *fp;
    
    fp = fopen("output.txt", "w");
    if (fp == NULL) {
        perror("Errore nell'apertura del file");
        return 1;
    }
    
    fputs("Prima riga\n", fp);
    fputs("Seconda riga\n", fp);
    fputs("Terza riga\n", fp);
    
    fclose(fp);
    return 0;
}
```

### Scrittura Formattata

```c
int fprintf(FILE *stream, const char *format, ...);
```

Scrive dati nel file secondo il formato specificato. Funziona in modo simile a `printf()`, ma scrive su un file anziché sullo standard output.

Esempio:

```c
#include <stdio.h>

int main() {
    FILE *fp;
    int num = 42;
    float pi = 3.14159;
    
    fp = fopen("output.txt", "w");
    if (fp == NULL) {
        perror("Errore nell'apertura del file");
        return 1;
    }
    
    fprintf(fp, "Numero intero: %d\n", num);
    fprintf(fp, "Numero float: %.2f\n", pi);
    fprintf(fp, "Una stringa: %s\n", "Hello, World!");
    
    fclose(fp);
    return 0;
}
```

## Lettura e Scrittura Binaria

Per i file binari, C fornisce funzioni specifiche:

### Lettura Binaria

```c
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
```

Legge `nmemb` elementi di dimensione `size` dal file e li memorizza in `ptr`. Restituisce il numero di elementi letti con successo.

### Scrittura Binaria

```c
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
```

Scrive `nmemb` elementi di dimensione `size` da `ptr` nel file. Restituisce il numero di elementi scritti con successo.

Esempio di lettura e scrittura binaria:

```c
#include <stdio.h>

struct Persona {
    char nome[50];
    int eta;
    float altezza;
};

int main() {
    FILE *fp;
    struct Persona p1 = {"Mario Rossi", 30, 1.75};
    struct Persona p2;
    
    // Scrittura binaria
    fp = fopen("persone.dat", "wb");
    if (fp == NULL) {
        perror("Errore nell'apertura del file");
        return 1;
    }
    
    fwrite(&p1, sizeof(struct Persona), 1, fp);
    fclose(fp);
    
    // Lettura binaria
    fp = fopen("persone.dat", "rb");
    if (fp == NULL) {
        perror("Errore nell'apertura del file");
        return 1;
    }
    
    fread(&p2, sizeof(struct Persona), 1, fp);
    fclose(fp);
    
    printf("Nome: %s, Età: %d, Altezza: %.2f\n", p2.nome, p2.eta, p2.altezza);
    
    return 0;
}
```

## Gestione degli Errori

È fondamentale gestire correttamente gli errori nelle operazioni sui file. Oltre a verificare il valore restituito da `fopen()`, è possibile utilizzare le seguenti funzioni:

- `ferror()`: Verifica se si è verificato un errore durante le operazioni sul file
- `feof()`: Verifica se è stata raggiunta la fine del file
- `clearerr()`: Resetta gli indicatori di errore e di fine file
- `perror()`: Stampa un messaggio di errore basato sul valore di `errno`

Esempio:

```c
#include <stdio.h>

int main() {
    FILE *fp;
    int c;
    
    fp = fopen("file_inesistente.txt", "r");
    if (fp == NULL) {
        perror("Errore");
        return 1;
    }
    
    c = fgetc(fp);
    if (ferror(fp)) {
        printf("Si è verificato un errore durante la lettura\n");
        clearerr(fp);
    }
    
    fclose(fp);
    return 0;
}
```

## Domande di Autovalutazione

1. Quali sono le principali funzioni per aprire e chiudere un file in C?
2. Quali sono le differenze tra `fgetc()`, `fgets()` e `fscanf()`?
3. Come si può verificare se è stata raggiunta la fine di un file durante la lettura?
4. Quali sono le differenze tra la lettura/scrittura di file di testo e file binari?
5. Perché è importante gestire gli errori nelle operazioni sui file?

## Esercizi Proposti

1. Scrivi un programma che legga un file di testo riga per riga e conti il numero di occorrenze di una parola specificata dall'utente.
2. Implementa un programma che legga un file contenente numeri interi (uno per riga) e calcoli la somma, la media, il minimo e il massimo di questi numeri.
3. Crea un programma che legga un file di testo e ne crei una copia, ma con tutte le lettere maiuscole convertite in minuscole e viceversa.
4. Scrivi un programma che legga un file binario contenente strutture di tipo `Studente` (con campi come nome, matricola e voto) e visualizzi i dati degli studenti con voto superiore a una soglia specificata.
5. Implementa un semplice editor di testo che permetta all'utente di aprire un file, visualizzarne il contenuto, modificarlo e salvarlo.

## Conclusione

Le operazioni fondamentali sui file sono essenziali per sviluppare applicazioni che interagiscono con dati persistenti. Nella prossima sezione, esploreremo tecniche più avanzate per la manipolazione dei file in C, come il posizionamento all'interno dei file e la gestione di file binari complessi.