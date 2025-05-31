# Posizionamento e Operazioni Avanzate sui File in C

## Posizionamento all'interno di un File

In C, è possibile posizionarsi in punti specifici di un file per leggere o scrivere dati. Questo è particolarmente utile quando si lavora con file binari o quando si desidera accedere a parti specifiche di un file senza dover leggere tutto il contenuto precedente.

### Funzioni di Posizionamento

#### `fseek()`

La funzione `fseek()` permette di posizionare l'indicatore di posizione del file in un punto specifico:

```c
int fseek(FILE *stream, long offset, int whence);
```

Dove:
- `stream` è il puntatore al file
- `offset` è lo spostamento in byte (può essere positivo o negativo)
- `whence` è il punto di riferimento per lo spostamento, può essere:
  - `SEEK_SET`: inizio del file
  - `SEEK_CUR`: posizione corrente
  - `SEEK_END`: fine del file

La funzione restituisce 0 in caso di successo, o un valore diverso da zero in caso di errore.

Esempio:

```c
#include <stdio.h>

int main() {
    FILE *fp;
    char buffer[100];
    
    fp = fopen("dati.txt", "r");
    if (fp == NULL) {
        perror("Errore nell'apertura del file");
        return 1;
    }
    
    // Posizionamento a 10 byte dall'inizio del file
    fseek(fp, 10, SEEK_SET);
    
    // Lettura di dati dalla nuova posizione
    fgets(buffer, sizeof(buffer), fp);
    printf("Dati letti: %s\n", buffer);
    
    // Posizionamento a 5 byte prima della posizione corrente
    fseek(fp, -5, SEEK_CUR);
    
    // Lettura di dati dalla nuova posizione
    fgets(buffer, sizeof(buffer), fp);
    printf("Dati letti: %s\n", buffer);
    
    fclose(fp);
    return 0;
}
```

#### `ftell()`

La funzione `ftell()` restituisce la posizione corrente dell'indicatore di posizione del file:

```c
long ftell(FILE *stream);
```

Esempio:

```c
#include <stdio.h>

int main() {
    FILE *fp;
    long pos;
    
    fp = fopen("dati.txt", "r");
    if (fp == NULL) {
        perror("Errore nell'apertura del file");
        return 1;
    }
    
    // Lettura di alcuni dati
    fgetc(fp);
    fgetc(fp);
    fgetc(fp);
    
    // Ottenimento della posizione corrente
    pos = ftell(fp);
    printf("Posizione corrente: %ld byte\n", pos);
    
    fclose(fp);
    return 0;
}
```

#### `rewind()`

La funzione `rewind()` riposiziona l'indicatore di posizione all'inizio del file:

```c
void rewind(FILE *stream);
```

Esempio:

```c
#include <stdio.h>

int main() {
    FILE *fp;
    char buffer[100];
    
    fp = fopen("dati.txt", "r");
    if (fp == NULL) {
        perror("Errore nell'apertura del file");
        return 1;
    }
    
    // Lettura della prima riga
    fgets(buffer, sizeof(buffer), fp);
    printf("Prima lettura: %s\n", buffer);
    
    // Riposizionamento all'inizio del file
    rewind(fp);
    
    // Lettura nuovamente della prima riga
    fgets(buffer, sizeof(buffer), fp);
    printf("Seconda lettura: %s\n", buffer);
    
    fclose(fp);
    return 0;
}
```

#### `fsetpos()` e `fgetpos()`

Queste funzioni sono simili a `fseek()` e `ftell()`, ma utilizzano un tipo di dato `fpos_t` per gestire la posizione, che è più portabile tra sistemi diversi:

```c
int fgetpos(FILE *stream, fpos_t *pos);
int fsetpos(FILE *stream, const fpos_t *pos);
```

Esempio:

```c
#include <stdio.h>

int main() {
    FILE *fp;
    fpos_t position;
    char buffer[100];
    
    fp = fopen("dati.txt", "r");
    if (fp == NULL) {
        perror("Errore nell'apertura del file");
        return 1;
    }
    
    // Lettura della prima riga
    fgets(buffer, sizeof(buffer), fp);
    printf("Prima riga: %s\n", buffer);
    
    // Salvataggio della posizione corrente
    fgetpos(fp, &position);
    
    // Lettura della seconda riga
    fgets(buffer, sizeof(buffer), fp);
    printf("Seconda riga: %s\n", buffer);
    
    // Ritorno alla posizione salvata
    fsetpos(fp, &position);
    
    // Lettura nuovamente della seconda riga
    fgets(buffer, sizeof(buffer), fp);
    printf("Rilettura seconda riga: %s\n", buffer);
    
    fclose(fp);
    return 0;
}
```

## Operazioni Avanzate sui File

### File Temporanei

I file temporanei sono utili per memorizzare dati intermedi che non devono essere conservati dopo la chiusura del programma.

#### `tmpfile()`

La funzione `tmpfile()` crea un file temporaneo in modalità "wb+" (binario, lettura e scrittura):

```c
FILE *tmpfile(void);
```

Il file viene automaticamente eliminato quando viene chiuso o quando il programma termina.

Esempio:

```c
#include <stdio.h>

int main() {
    FILE *temp;
    char buffer[100];
    
    // Creazione di un file temporaneo
    temp = tmpfile();
    if (temp == NULL) {
        perror("Errore nella creazione del file temporaneo");
        return 1;
    }
    
    // Scrittura nel file temporaneo
    fputs("Dati temporanei\n", temp);
    
    // Riposizionamento all'inizio del file
    rewind(temp);
    
    // Lettura dal file temporaneo
    fgets(buffer, sizeof(buffer), temp);
    printf("Dati letti dal file temporaneo: %s", buffer);
    
    // Chiusura del file (verrà eliminato automaticamente)
    fclose(temp);
    
    return 0;
}
```

### Buffering

Il buffering è un meccanismo che migliora le prestazioni delle operazioni di I/O accumulando dati in memoria prima di trasferirli effettivamente al file o dal file.

#### `setvbuf()`

La funzione `setvbuf()` permette di controllare il buffering per un file:

```c
int setvbuf(FILE *stream, char *buffer, int mode, size_t size);
```

Dove:
- `stream` è il puntatore al file
- `buffer` è un buffer fornito dall'utente (o NULL per utilizzare un buffer allocato automaticamente)
- `mode` è la modalità di buffering:
  - `_IOFBF`: buffering completo
  - `_IOLBF`: buffering di linea
  - `_IONBF`: nessun buffering
- `size` è la dimensione del buffer

Esempio:

```c
#include <stdio.h>

int main() {
    FILE *fp;
    char buffer[1024];
    
    fp = fopen("output.txt", "w");
    if (fp == NULL) {
        perror("Errore nell'apertura del file");
        return 1;
    }
    
    // Impostazione del buffering
    setvbuf(fp, buffer, _IOFBF, sizeof(buffer));
    
    // Scrittura nel file
    fprintf(fp, "Questo testo verrà bufferizzato\n");
    
    // Forzare lo svuotamento del buffer
    fflush(fp);
    
    fclose(fp);
    return 0;
}
```

#### `fflush()`

La funzione `fflush()` forza lo svuotamento del buffer associato a un file:

```c
int fflush(FILE *stream);
```

Se `stream` è NULL, la funzione svuota tutti i buffer aperti.

### Gestione degli Errori Avanzata

Oltre alle funzioni di base per la gestione degli errori, C offre altre funzioni utili:

#### `strerror()`

La funzione `strerror()` restituisce una stringa che descrive l'errore corrispondente a un dato codice di errore:

```c
char *strerror(int errnum);
```

Esempio:

```c
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {
    FILE *fp;
    
    fp = fopen("file_inesistente.txt", "r");
    if (fp == NULL) {
        printf("Errore: %s\n", strerror(errno));
        return 1;
    }
    
    fclose(fp);
    return 0;
}
```

## Operazioni su File Binari Avanzate

### Lettura e Scrittura di Strutture Complesse

Quando si lavora con file binari, è comune leggere e scrivere strutture dati complesse:

```c
#include <stdio.h>
#include <string.h>

#define MAX_STUDENTI 100

struct Studente {
    int matricola;
    char nome[50];
    char cognome[50];
    float media;
};

// Funzione per salvare un array di strutture su file
void salvaStudenti(struct Studente studenti[], int n, const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("Errore nell'apertura del file");
        return;
    }
    
    // Scrittura del numero di studenti
    fwrite(&n, sizeof(int), 1, fp);
    
    // Scrittura dell'array di strutture
    fwrite(studenti, sizeof(struct Studente), n, fp);
    
    fclose(fp);
}

// Funzione per caricare un array di strutture da file
int caricaStudenti(struct Studente studenti[], const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Errore nell'apertura del file");
        return 0;
    }
    
    int n;
    
    // Lettura del numero di studenti
    fread(&n, sizeof(int), 1, fp);
    
    if (n > MAX_STUDENTI) {
        printf("Troppi studenti nel file!\n");
        fclose(fp);
        return 0;
    }
    
    // Lettura dell'array di strutture
    fread(studenti, sizeof(struct Studente), n, fp);
    
    fclose(fp);
    return n;
}

int main() {
    struct Studente classe[MAX_STUDENTI];
    int numStudenti = 3;
    
    // Inizializzazione di alcuni studenti
    classe[0].matricola = 1001;
    strcpy(classe[0].nome, "Mario");
    strcpy(classe[0].cognome, "Rossi");
    classe[0].media = 27.5;
    
    classe[1].matricola = 1002;
    strcpy(classe[1].nome, "Laura");
    strcpy(classe[1].cognome, "Bianchi");
    classe[1].media = 29.0;
    
    classe[2].matricola = 1003;
    strcpy(classe[2].nome, "Giovanni");
    strcpy(classe[2].cognome, "Verdi");
    classe[2].media = 24.5;
    
    // Salvataggio su file
    salvaStudenti(classe, numStudenti, "studenti.dat");
    
    // Azzeramento dell'array
    memset(classe, 0, sizeof(classe));
    
    // Caricamento da file
    numStudenti = caricaStudenti(classe, "studenti.dat");
    
    // Visualizzazione dei dati caricati
    printf("Studenti caricati: %d\n\n", numStudenti);
    for (int i = 0; i < numStudenti; i++) {
        printf("Matricola: %d\n", classe[i].matricola);
        printf("Nome: %s\n", classe[i].nome);
        printf("Cognome: %s\n", classe[i].cognome);
        printf("Media: %.1f\n\n", classe[i].media);
    }
    
    return 0;
}
```

### Accesso Casuale ai Dati

L'accesso casuale ai dati è particolarmente utile quando si lavora con file binari strutturati, come database semplici:

```c
#include <stdio.h>
#include <string.h>

struct Prodotto {
    int id;
    char nome[50];
    float prezzo;
};

// Funzione per aggiungere un prodotto al file
void aggiungiProdotto(struct Prodotto p, const char *filename) {
    FILE *fp = fopen(filename, "ab");
    if (fp == NULL) {
        perror("Errore nell'apertura del file");
        return;
    }
    
    fwrite(&p, sizeof(struct Prodotto), 1, fp);
    fclose(fp);
}

// Funzione per leggere un prodotto specifico dal file
int leggiProdotto(int id, struct Prodotto *p, const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Errore nell'apertura del file");
        return 0;
    }
    
    struct Prodotto temp;
    int trovato = 0;
    
    while (fread(&temp, sizeof(struct Prodotto), 1, fp) == 1) {
        if (temp.id == id) {
            *p = temp;
            trovato = 1;
            break;
        }
    }
    
    fclose(fp);
    return trovato;
}

// Funzione per aggiornare un prodotto nel file
int aggiornaProdotto(struct Prodotto p, const char *filename) {
    FILE *fp = fopen(filename, "r+b");
    if (fp == NULL) {
        perror("Errore nell'apertura del file");
        return 0;
    }
    
    struct Prodotto temp;
    int trovato = 0;
    long posizione;
    
    while (1) {
        posizione = ftell(fp);
        if (fread(&temp, sizeof(struct Prodotto), 1, fp) != 1) {
            break;
        }
        
        if (temp.id == p.id) {
            fseek(fp, posizione, SEEK_SET);
            fwrite(&p, sizeof(struct Prodotto), 1, fp);
            trovato = 1;
            break;
        }
    }
    
    fclose(fp);
    return trovato;
}

int main() {
    struct Prodotto p1 = {1, "Laptop", 999.99};
    struct Prodotto p2 = {2, "Smartphone", 499.99};
    struct Prodotto p3;
    
    // Aggiunta di prodotti
    aggiungiProdotto(p1, "prodotti.dat");
    aggiungiProdotto(p2, "prodotti.dat");
    
    // Lettura di un prodotto
    if (leggiProdotto(1, &p3, "prodotti.dat")) {
        printf("Prodotto trovato:\n");
        printf("ID: %d\n", p3.id);
        printf("Nome: %s\n", p3.nome);
        printf("Prezzo: %.2f\n\n", p3.prezzo);
    }
    
    // Aggiornamento di un prodotto
    p2.prezzo = 449.99;
    if (aggiornaProdotto(p2, "prodotti.dat")) {
        printf("Prodotto aggiornato con successo!\n");
    }
    
    // Verifica dell'aggiornamento
    if (leggiProdotto(2, &p3, "prodotti.dat")) {
        printf("Prodotto aggiornato:\n");
        printf("ID: %d\n", p3.id);
        printf("Nome: %s\n", p3.nome);
        printf("Prezzo: %.2f\n", p3.prezzo);
    }
    
    return 0;
}
```

## Domande di Autovalutazione

1. Quali sono le principali funzioni per il posizionamento all'interno di un file in C?
2. Qual è la differenza tra `fseek()` e `fsetpos()`?
3. Come si può ottenere la posizione corrente all'interno di un file?
4. Cosa sono i file temporanei e quando è utile utilizzarli?
5. Quali sono i diversi tipi di buffering disponibili in C e come si possono controllare?
6. Come si può implementare un sistema di accesso casuale ai dati in un file binario?
7. Quali precauzioni bisogna prendere quando si leggono e scrivono strutture dati complesse su file binari?

## Esercizi Proposti

1. Scrivi un programma che crei un file di testo, vi scriva alcune righe, e poi legga e visualizzi solo le righe pari (2ª, 4ª, ecc.).

2. Implementa un semplice database di contatti (nome, telefono, email) utilizzando un file binario. Il programma deve permettere di aggiungere, visualizzare, cercare, modificare ed eliminare contatti.

3. Scrivi un programma che legga un file di testo e crei un nuovo file contenente le stesse righe ma in ordine inverso (dall'ultima alla prima).

4. Implementa un programma che divida un file di grandi dimensioni in più file più piccoli (ad esempio, dividere in parti da 1MB ciascuna) e un altro programma che ricomponga il file originale a partire dai frammenti.

5. Crea un programma che simuli un semplice editor di testo con la possibilità di aprire un file, modificarlo (inserendo o eliminando testo in punti specifici) e salvarlo.

## Conclusione

Le operazioni avanzate sui file, come il posizionamento e l'accesso casuale ai dati, sono strumenti potenti che permettono di sviluppare applicazioni più sofisticate per la gestione dei dati. La comprensione di questi concetti è fondamentale per creare programmi efficienti che manipolano file di grandi dimensioni o che richiedono un accesso strutturato ai dati.

Nella prossima sezione, esploreremo tecniche ancora più avanzate per la gestione dei file e dei dati in C, come la mappatura di file in memoria e l'uso di file per l'interprocess communication (IPC).