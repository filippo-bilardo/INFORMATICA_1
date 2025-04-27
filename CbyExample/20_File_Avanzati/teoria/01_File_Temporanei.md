# File Temporanei in C

## Introduzione

I file temporanei sono file creati per memorizzare dati intermedi durante l'esecuzione di un programma e che vengono tipicamente eliminati al termine dell'elaborazione. Sono particolarmente utili quando si lavora con grandi quantità di dati che non possono essere mantenuti interamente in memoria.

## Creazione di File Temporanei

Il linguaggio C offre diverse funzioni per la creazione e gestione di file temporanei.

### La Funzione tmpfile()

La funzione `tmpfile()` crea un file temporaneo in modalità "wb+" (binario, lettura e scrittura):

```c
FILE *tmpfile(void);
```

Questa funzione restituisce un puntatore al file temporaneo creato, o `NULL` in caso di errore. Il file viene automaticamente eliminato quando viene chiuso o quando il programma termina.

```c
#include <stdio.h>

int main() {
    FILE *temp = tmpfile();
    
    if (temp == NULL) {
        printf("Errore nella creazione del file temporaneo!\n");
        return 1;
    }
    
    // Utilizzo del file temporaneo
    fprintf(temp, "Dati temporanei\n");
    
    // Riposizionamento all'inizio del file
    rewind(temp);
    
    // Lettura dei dati
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), temp) != NULL) {
        printf("Dati letti: %s", buffer);
    }
    
    // Chiusura del file (verrà eliminato automaticamente)
    fclose(temp);
    
    return 0;
}
```

### Le Funzioni tmpnam() e tempnam()

Le funzioni `tmpnam()` e `tempnam()` generano nomi di file temporanei unici:

```c
char *tmpnam(char *s);
char *tempnam(const char *dir, const char *pfx);
```

- `tmpnam()` genera un nome di file nella directory temporanea predefinita.
- `tempnam()` permette di specificare una directory e un prefisso per il nome del file.

A differenza di `tmpfile()`, queste funzioni non creano effettivamente il file, ma forniscono solo un nome che può essere utilizzato per creare un file temporaneo.

```c
#include <stdio.h>

int main() {
    char filename[L_tmpnam];
    
    // Genera un nome di file temporaneo
    if (tmpnam(filename) == NULL) {
        printf("Errore nella generazione del nome del file temporaneo!\n");
        return 1;
    }
    
    printf("Nome del file temporaneo: %s\n", filename);
    
    // Apertura del file temporaneo
    FILE *temp = fopen(filename, "w+");
    
    if (temp == NULL) {
        printf("Errore nell'apertura del file temporaneo!\n");
        return 1;
    }
    
    // Utilizzo del file temporaneo
    fprintf(temp, "Dati temporanei\n");
    
    // Chiusura del file
    fclose(temp);
    
    // Eliminazione manuale del file
    remove(filename);
    
    return 0;
}
```

### La Funzione mkstemp() (POSIX)

Nei sistemi POSIX, la funzione `mkstemp()` è considerata più sicura delle precedenti, poiché crea il file con permessi restrittivi e lo apre atomicamente:

```c
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    char template[] = "/tmp/tempfileXXXXXX";
    int fd;
    
    // Crea e apre il file temporaneo
    fd = mkstemp(template);
    
    if (fd == -1) {
        perror("Errore nella creazione del file temporaneo");
        return 1;
    }
    
    printf("File temporaneo creato: %s\n", template);
    
    // Conversione del file descriptor in FILE*
    FILE *temp = fdopen(fd, "w+");
    
    if (temp == NULL) {
        perror("Errore nella conversione del file descriptor");
        close(fd);
        return 1;
    }
    
    // Utilizzo del file temporaneo
    fprintf(temp, "Dati temporanei\n");
    
    // Chiusura del file
    fclose(temp);  // Chiude anche il file descriptor
    
    // Eliminazione del file
    unlink(template);
    
    return 0;
}
```

## Considerazioni sulla Sicurezza

L'uso di file temporanei può presentare rischi di sicurezza, in particolare:

1. **Race condition**: Se c'è un intervallo di tempo tra la generazione del nome del file e la sua creazione, un attaccante potrebbe creare un file con lo stesso nome.

2. **Prevedibilità dei nomi**: Se i nomi dei file temporanei sono prevedibili, un attaccante potrebbe indovinare il nome e accedere al file.

3. **Persistenza non intenzionale**: Se il programma termina in modo anomalo, i file temporanei potrebbero non essere eliminati.

Per mitigare questi rischi:

- Utilizzare `tmpfile()` quando possibile, poiché gestisce automaticamente la creazione e l'eliminazione del file.
- Nei sistemi POSIX, preferire `mkstemp()` a `tmpnam()` o `tempnam()`.
- Impostare permessi restrittivi sui file temporanei.
- Assicurarsi di eliminare i file temporanei anche in caso di errori o terminazione anomala del programma.

## Casi d'Uso Comuni

### Ordinamento di Grandi Quantità di Dati

Quando si devono ordinare dati che non entrano interamente in memoria, si può utilizzare un approccio di ordinamento esterno con file temporanei:

```c
#include <stdio.h>
#include <stdlib.h>

#define CHUNK_SIZE 1000

// Funzione di confronto per qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Funzione per ordinare un file di interi
void sort_large_file(const char *input_file, const char *output_file) {
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");
    FILE *temp_files[100];  // Array di file temporanei
    int num_temp_files = 0;
    int buffer[CHUNK_SIZE];
    
    if (input == NULL || output == NULL) {
        printf("Errore nell'apertura dei file!\n");
        return;
    }
    
    // Fase 1: Dividi il file in chunk, ordina ciascun chunk e salvalo in un file temporaneo
    while (!feof(input)) {
        int count = 0;
        
        // Leggi un chunk di dati
        while (count < CHUNK_SIZE && fscanf(input, "%d", &buffer[count]) == 1) {
            count++;
        }
        
        if (count == 0) break;  // Nessun dato letto
        
        // Ordina il chunk
        qsort(buffer, count, sizeof(int), compare);
        
        // Crea un file temporaneo per il chunk ordinato
        temp_files[num_temp_files] = tmpfile();
        
        if (temp_files[num_temp_files] == NULL) {
            printf("Errore nella creazione del file temporaneo!\n");
            return;
        }
        
        // Scrivi il chunk ordinato nel file temporaneo
        for (int i = 0; i < count; i++) {
            fprintf(temp_files[num_temp_files], "%d\n", buffer[i]);
        }
        
        // Riposiziona il file temporaneo all'inizio
        rewind(temp_files[num_temp_files]);
        
        num_temp_files++;
    }
    
    // Fase 2: Unisci i file temporanei (merge)
    // ...
    
    // Chiudi e elimina i file temporanei
    for (int i = 0; i < num_temp_files; i++) {
        fclose(temp_files[i]);
    }
    
    fclose(input);
    fclose(output);
}
```

### Elaborazione di File di Grandi Dimensioni

I file temporanei sono utili anche quando si devono elaborare file di grandi dimensioni in più passaggi:

```c
#include <stdio.h>

// Funzione per contare le occorrenze di una parola in un file di testo
int count_word_occurrences(const char *filename, const char *word) {
    FILE *file = fopen(filename, "r");
    FILE *temp = tmpfile();
    char buffer[1024];
    int count = 0;
    
    if (file == NULL || temp == NULL) {
        printf("Errore nell'apertura dei file!\n");
        return -1;
    }
    
    // Primo passaggio: normalizza il testo (converti in minuscolo, rimuovi punteggiatura)
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Normalizza il testo
        for (int i = 0; buffer[i]; i++) {
            if (buffer[i] >= 'A' && buffer[i] <= 'Z') {
                buffer[i] = buffer[i] - 'A' + 'a';
            } else if (buffer[i] == '.' || buffer[i] == ',' || buffer[i] == '!' || buffer[i] == '?') {
                buffer[i] = ' ';
            }
        }
        
        // Scrivi il testo normalizzato nel file temporaneo
        fputs(buffer, temp);
    }
    
    // Riposiziona il file temporaneo all'inizio
    rewind(temp);
    
    // Secondo passaggio: conta le occorrenze della parola
    while (fscanf(temp, "%s", buffer) == 1) {
        if (strcmp(buffer, word) == 0) {
            count++;
        }
    }
    
    fclose(file);
    fclose(temp);  // Il file temporaneo viene eliminato automaticamente
    
    return count;
}
```

## Best Practices

1. **Utilizzare `tmpfile()` quando possibile**, poiché gestisce automaticamente la creazione e l'eliminazione del file.

2. **Controllare sempre i valori restituiti** dalle funzioni di creazione di file temporanei per verificare se le operazioni sono avvenute con successo.

3. **Eliminare esplicitamente i file temporanei** creati con `tmpnam()` o `tempnam()` quando non sono più necessari.

4. **Gestire correttamente gli errori** per garantire che i file temporanei vengano eliminati anche in caso di terminazione anomala del programma.

5. **Limitare l'accesso ai file temporanei** impostando permessi restrittivi quando possibile.

## Conclusione

I file temporanei sono uno strumento potente per gestire dati intermedi durante l'esecuzione di un programma. Consentono di elaborare grandi quantità di dati che non potrebbero essere mantenuti interamente in memoria e facilitano operazioni complesse come l'ordinamento esterno. Tuttavia, è importante utilizzarli con attenzione, seguendo le best practices per evitare problemi di sicurezza e garantire la corretta gestione delle risorse.

## Esercizi

1. Implementa un programma che utilizzi file temporanei per invertire l'ordine delle righe di un file di testo.

2. Crea un'applicazione che utilizzi file temporanei per unire e ordinare più file di dati.

3. Sviluppa un programma che utilizzi file temporanei per implementare un semplice database con funzionalità di ricerca e ordinamento.