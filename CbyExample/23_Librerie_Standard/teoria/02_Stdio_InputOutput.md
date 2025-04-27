# La Libreria stdio.h: Input e Output in C

## Introduzione

La libreria `stdio.h` (Standard Input/Output) è una delle librerie più importanti e utilizzate in C. Fornisce funzioni e macro per operazioni di input e output, permettendo ai programmi di interagire con l'utente attraverso la console e di leggere e scrivere file.

## Flussi Standard

In C, l'input e l'output sono gestiti attraverso "flussi" (streams). Ci sono tre flussi standard predefiniti:

- **stdin**: Standard input (input da tastiera)
- **stdout**: Standard output (output su console)
- **stderr**: Standard error (output di errori su console)

Questi flussi sono rappresentati come puntatori a `FILE`, un tipo di dato definito in `stdio.h`.

## Funzioni di Input/Output su Console

### Output su Console

#### printf()

La funzione `printf()` è utilizzata per stampare dati formattati su stdout:

```c
#include <stdio.h>

int main() {
    int numero = 42;
    float decimale = 3.14;
    char carattere = 'A';
    char *stringa = "Hello";
    
    printf("Numero intero: %d\n", numero);
    printf("Numero decimale: %f\n", decimale);
    printf("Carattere: %c\n", carattere);
    printf("Stringa: %s\n", stringa);
    
    // Formattazione avanzata
    printf("Esadecimale: %x\n", numero);  // 2a
    printf("Decimale con precisione: %.2f\n", decimale);  // 3.14
    printf("Intero con padding: %05d\n", numero);  // 00042
    
    return 0;
}
```

#### Specificatori di Formato Comuni

- `%d` o `%i`: Intero decimale
- `%u`: Intero decimale senza segno
- `%f`: Numero in virgola mobile
- `%e` o `%E`: Notazione scientifica
- `%g` o `%G`: Usa %f o %e a seconda di quale è più breve
- `%c`: Carattere
- `%s`: Stringa
- `%p`: Puntatore
- `%x` o `%X`: Esadecimale
- `%o`: Ottale
- `%%`: Carattere %

#### putchar() e puts()

Funzioni più semplici per l'output:

```c
#include <stdio.h>

int main() {
    // Stampa un singolo carattere
    putchar('A');  // Stampa: A
    putchar('\n');  // Nuova riga
    
    // Stampa una stringa seguita da una nuova riga
    puts("Hello, World!");  // Stampa: Hello, World! (con nuova riga)
    
    return 0;
}
```

### Input da Console

#### scanf()

La funzione `scanf()` legge dati formattati da stdin:

```c
#include <stdio.h>

int main() {
    int numero;
    float decimale;
    char carattere;
    char stringa[50];
    
    printf("Inserisci un numero intero: ");
    scanf("%d", &numero);
    
    printf("Inserisci un numero decimale: ");
    scanf("%f", &decimale);
    
    // Consumare il carattere newline rimasto nel buffer
    getchar();
    
    printf("Inserisci un carattere: ");
    scanf("%c", &carattere);
    
    printf("Inserisci una stringa: ");
    scanf("%s", stringa);  // Nota: non serve & per gli array
    
    printf("\nHai inserito:\n");
    printf("Numero: %d\n", numero);
    printf("Decimale: %f\n", decimale);
    printf("Carattere: %c\n", carattere);
    printf("Stringa: %s\n", stringa);
    
    return 0;
}
```

> **Attenzione**: `scanf()` con `%s` legge solo fino al primo spazio bianco e non controlla i limiti dell'array, potendo causare buffer overflow. Per input più sicuro, considerare `fgets()`.

#### getchar() e gets()

Funzioni più semplici per l'input:

```c
#include <stdio.h>

int main() {
    char c;
    char stringa[50];
    
    printf("Inserisci un carattere: ");
    c = getchar();  // Legge un singolo carattere
    
    // Consumare il carattere newline rimasto nel buffer
    getchar();
    
    printf("Hai inserito: %c\n\n", c);
    
    printf("Inserisci una stringa: ");
    fgets(stringa, 50, stdin);  // Legge una riga (più sicuro di gets())
    
    printf("Hai inserito: %s", stringa);
    
    return 0;
}
```

> **Nota**: La funzione `gets()` è considerata pericolosa e obsoleta perché non controlla i limiti dell'array. È stata rimossa dallo standard C11. Utilizzare sempre `fgets()` al suo posto.

## Operazioni su File

### Apertura e Chiusura di File

```c
#include <stdio.h>

int main() {
    FILE *file;
    
    // Apertura di un file in modalità scrittura
    file = fopen("esempio.txt", "w");
    
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return 1;
    }
    
    // Operazioni sul file...
    
    // Chiusura del file
    fclose(file);
    
    return 0;
}
```

### Modalità di Apertura dei File

- `"r"`: Lettura (il file deve esistere)
- `"w"`: Scrittura (crea il file se non esiste, altrimenti lo tronca)
- `"a"`: Append (aggiunge alla fine del file, lo crea se non esiste)
- `"r+"`: Lettura e scrittura (il file deve esistere)
- `"w+"`: Lettura e scrittura (crea il file se non esiste, altrimenti lo tronca)
- `"a+"`: Lettura e append (crea il file se non esiste)

Aggiungendo `b` alla modalità (es. `"rb"`, `"wb"`) si apre il file in modalità binaria anziché testo.

### Scrittura su File

```c
#include <stdio.h>

int main() {
    FILE *file = fopen("esempio.txt", "w");
    
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return 1;
    }
    
    // Scrittura formattata
    fprintf(file, "Numero: %d\n", 42);
    fprintf(file, "Stringa: %s\n", "Hello, World!");
    
    // Scrittura di un carattere
    fputc('A', file);
    fputc('\n', file);
    
    // Scrittura di una stringa
    fputs("Una riga di testo.\n", file);
    
    // Scrittura binaria
    int numeri[5] = {1, 2, 3, 4, 5};
    fwrite(numeri, sizeof(int), 5, file);
    
    fclose(file);
    return 0;
}
```

### Lettura da File

```c
#include <stdio.h>

int main() {
    FILE *file = fopen("esempio.txt", "r");
    
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return 1;
    }
    
    // Lettura formattata
    int numero;
    char stringa[50];
    fscanf(file, "Numero: %d\n", &numero);
    fscanf(file, "Stringa: %s\n", stringa);
    
    printf("Letto: numero=%d, stringa=%s\n", numero, stringa);
    
    // Lettura di un carattere
    char c = fgetc(file);
    printf("Carattere letto: %c\n", c);
    
    // Consumare il carattere newline
    fgetc(file);
    
    // Lettura di una riga
    char riga[100];
    fgets(riga, 100, file);
    printf("Riga letta: %s", riga);
    
    // Lettura binaria
    int numeri[5];
    fread(numeri, sizeof(int), 5, file);
    
    printf("Numeri letti: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numeri[i]);
    }
    printf("\n");
    
    fclose(file);
    return 0;
}
```

### Posizionamento nel File

```c
#include <stdio.h>

int main() {
    FILE *file = fopen("esempio.txt", "r+");
    
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return 1;
    }
    
    // Spostamento dall'inizio del file
    fseek(file, 10, SEEK_SET);  // 10 byte dall'inizio
    
    // Spostamento dalla posizione corrente
    fseek(file, 5, SEEK_CUR);   // 5 byte avanti
    
    // Spostamento dalla fine del file
    fseek(file, -8, SEEK_END);  // 8 byte prima della fine
    
    // Ottenere la posizione corrente
    long pos = ftell(file);
    printf("Posizione corrente: %ld byte\n", pos);
    
    // Tornare all'inizio del file
    rewind(file);
    
    fclose(file);
    return 0;
}
```

## Gestione degli Errori

```c
#include <stdio.h>
#include <errno.h>  // Per accedere alla variabile errno
#include <string.h> // Per strerror()

int main() {
    FILE *file = fopen("file_inesistente.txt", "r");
    
    if (file == NULL) {
        // Metodo 1: perror
        perror("Errore");  // Stampa: Errore: No such file or directory
        
        // Metodo 2: errno e strerror
        printf("Errore %d: %s\n", errno, strerror(errno));
        
        return 1;
    }
    
    fclose(file);
    return 0;
}
```

## Funzioni di Formattazione Avanzate

### sprintf() e sscanf()

Queste funzioni permettono di formattare e analizzare stringhe in memoria:

```c
#include <stdio.h>

int main() {
    char buffer[100];
    int numero = 42;
    float decimale = 3.14;
    
    // Formattazione in una stringa
    sprintf(buffer, "Numero: %d, Decimale: %.2f", numero, decimale);
    printf("Buffer: %s\n", buffer);  // Buffer: Numero: 42, Decimale: 3.14
    
    // Analisi da una stringa
    char input[] = "123 45.67";
    int n;
    float f;
    sscanf(input, "%d %f", &n, &f);
    printf("Valori letti: %d, %.2f\n", n, f);  // Valori letti: 123, 45.67
    
    return 0;
}
```

### snprintf()

Versione più sicura di `sprintf()` che limita il numero di caratteri scritti:

```c
#include <stdio.h>

int main() {
    char buffer[10];  // Buffer piccolo
    
    // Limita la scrittura a 9 caratteri + terminatore
    snprintf(buffer, sizeof(buffer), "Numero: %d", 12345678);
    
    printf("Buffer: %s\n", buffer);  // Buffer: Numero: 1
    
    return 0;
}
```

## Reindirizzamento dei Flussi Standard

```c
#include <stdio.h>

int main() {
    // Salva il puntatore originale a stdout
    FILE *stdout_originale = stdout;
    
    // Reindirizza stdout a un file
    FILE *file = fopen("output.txt", "w");
    if (file != NULL) {
        stdout = file;
        
        // Ora printf scrive sul file
        printf("Questo testo va nel file\n");
        
        // Ripristina stdout
        stdout = stdout_originale;
        
        fclose(file);
    }
    
    // Ora printf scrive di nuovo sulla console
    printf("Questo testo va sulla console\n");
    
    return 0;
}
```

## Funzioni di Buffer

```c
#include <stdio.h>

int main() {
    FILE *file = fopen("esempio.txt", "w");
    
    if (file != NULL) {
        // Imposta la modalità di buffering
        // _IONBF: nessun buffering
        // _IOLBF: buffering di linea
        // _IOFBF: buffering completo
        setvbuf(file, NULL, _IOFBF, 1024);  // Buffer di 1024 byte
        
        // Scrittura sul file...
        fprintf(file, "Testo di esempio\n");
        
        // Forza lo svuotamento del buffer
        fflush(file);
        
        fclose(file);
    }
    
    return 0;
}
```

## Esempi Pratici

### Copia di un File

```c
#include <stdio.h>

int main() {
    FILE *sorgente, *destinazione;
    char carattere;
    
    sorgente = fopen("sorgente.txt", "r");
    if (sorgente == NULL) {
        perror("Errore nell'apertura del file sorgente");
        return 1;
    }
    
    destinazione = fopen("destinazione.txt", "w");
    if (destinazione == NULL) {
        perror("Errore nell'apertura del file destinazione");
        fclose(sorgente);
        return 1;
    }
    
    // Copia carattere per carattere
    while ((carattere = fgetc(sorgente)) != EOF) {
        fputc(carattere, destinazione);
    }
    
    printf("File copiato con successo\n");
    
    fclose(sorgente);
    fclose(destinazione);
    
    return 0;
}
```

### Conteggio di Righe, Parole e Caratteri

```c
#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *file;
    char c;
    int caratteri = 0, parole = 0, righe = 0;
    int in_parola = 0;  // Flag per tenere traccia se siamo all'interno di una parola
    
    file = fopen("testo.txt", "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return 1;
    }
    
    while ((c = fgetc(file)) != EOF) {
        caratteri++;
        
        // Conteggio righe
        if (c == '\n') {
            righe++;
        }
        
        // Conteggio parole
        if (isspace(c)) {
            in_parola = 0;
        } else if (in_parola == 0) {
            in_parola = 1;
            parole++;
        }
    }
    
    // Se il file non termina con una nuova riga, incrementa il conteggio delle righe
    if (caratteri > 0 && c != '\n') {
        righe++;
    }
    
    printf("Il file contiene:\n");
    printf("- %d caratteri\n", caratteri);
    printf("- %d parole\n", parole);
    printf("- %d righe\n", righe);
    
    fclose(file);
    
    return 0;
}
```

## Esercizi Pratici

1. Scrivi un programma che legga un file di testo e lo converta in maiuscolo, salvando il risultato in un nuovo file.

2. Implementa un programma che legga un file CSV (valori separati da virgole) e calcoli la somma e la media di ogni colonna numerica.

3. Crea un'applicazione che unisca più file di testo in un unico file, aggiungendo numeri di riga.

4. Sviluppa un programma che legga un file binario contenente numeri interi e li ordini in ordine crescente, salvando il risultato in un nuovo file.

5. Implementa un semplice editor di testo che permetta all'utente di visualizzare, modificare e salvare file di testo.

## Domande di Autovalutazione

1. Quali sono le differenze tra le funzioni `printf()` e `fprintf()`?

2. Perché `fgets()` è considerato più sicuro di `gets()`?

3. Quali sono le diverse modalità di apertura di un file e quando è appropriato utilizzare ciascuna?

4. Come si può verificare se un'operazione di I/O ha avuto successo?

5. Quali sono i vantaggi e gli svantaggi delle diverse modalità di buffering?