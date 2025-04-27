# Operazioni di I/O a Basso Livello in C

## Introduzione

Oltre alle funzioni di I/O di alto livello fornite dalla libreria standard (`stdio.h`), il linguaggio C permette di accedere a funzioni di I/O a basso livello che interagiscono direttamente con il sistema operativo. Queste funzioni offrono un controllo più preciso sulle operazioni di I/O, ma richiedono una gestione più attenta da parte del programmatore.

## File Descriptor

Nelle operazioni di I/O a basso livello, i file sono identificati da numeri interi chiamati "file descriptor" anziché da puntatori a strutture `FILE`. I file descriptor sono indici in una tabella mantenuta dal sistema operativo per ogni processo.

Per convenzione, i seguenti file descriptor sono predefiniti:
- 0: Standard Input (stdin)
- 1: Standard Output (stdout)
- 2: Standard Error (stderr)

## Funzioni di I/O a Basso Livello

### open()

La funzione `open()` apre un file e restituisce un file descriptor:

```c
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int open(const char *pathname, int flags, mode_t mode);
```

Parametri:
- `pathname`: percorso del file da aprire
- `flags`: modalità di apertura (O_RDONLY, O_WRONLY, O_RDWR, ecc.)
- `mode`: permessi del file (se viene creato)

La funzione restituisce un file descriptor in caso di successo, o -1 in caso di errore.

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd;
    
    // Apre un file in lettura
    fd = open("dati.txt", O_RDONLY);
    
    if (fd == -1) {
        perror("Errore nell'apertura del file");
        exit(EXIT_FAILURE);
    }
    
    printf("File aperto con successo, file descriptor: %d\n", fd);
    
    // Chiude il file
    close(fd);
    
    // Crea un nuovo file con permessi di lettura e scrittura per l'utente
    fd = open("nuovo.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    
    if (fd == -1) {
        perror("Errore nella creazione del file");
        exit(EXIT_FAILURE);
    }
    
    printf("Nuovo file creato, file descriptor: %d\n", fd);
    
    close(fd);
    
    return 0;
}
```

### read()

La funzione `read()` legge dati da un file descriptor:

```c
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count);
```

Parametri:
- `fd`: file descriptor
- `buf`: buffer in cui memorizzare i dati letti
- `count`: numero massimo di byte da leggere

La funzione restituisce il numero di byte letti, 0 alla fine del file, o -1 in caso di errore.

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd;
    char buffer[100];
    ssize_t bytes_read;
    
    fd = open("dati.txt", O_RDONLY);
    
    if (fd == -1) {
        perror("Errore nell'apertura del file");
        exit(EXIT_FAILURE);
    }
    
    // Legge fino a 99 byte dal file
    bytes_read = read(fd, buffer, 99);
    
    if (bytes_read == -1) {
        perror("Errore nella lettura del file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    // Aggiunge il terminatore di stringa
    buffer[bytes_read] = '\0';
    
    printf("Dati letti (%zd byte): %s\n", bytes_read, buffer);
    
    close(fd);
    
    return 0;
}
```

### write()

La funzione `write()` scrive dati su un file descriptor:

```c
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count);
```

Parametri:
- `fd`: file descriptor
- `buf`: buffer contenente i dati da scrivere
- `count`: numero di byte da scrivere

La funzione restituisce il numero di byte scritti, o -1 in caso di errore.

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int fd;
    const char *testo = "Questo è un test di scrittura a basso livello.\n";
    ssize_t bytes_written;
    
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    
    if (fd == -1) {
        perror("Errore nell'apertura del file");
        exit(EXIT_FAILURE);
    }
    
    // Scrive il testo nel file
    bytes_written = write(fd, testo, strlen(testo));
    
    if (bytes_written == -1) {
        perror("Errore nella scrittura del file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    printf("Dati scritti con successo (%zd byte)\n", bytes_written);
    
    close(fd);
    
    return 0;
}
```

### close()

La funzione `close()` chiude un file descriptor:

```c
#include <unistd.h>

int close(int fd);
```

La funzione restituisce 0 in caso di successo, o -1 in caso di errore.

### lseek()

La funzione `lseek()` modifica la posizione corrente all'interno di un file:

```c
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence);
```

Parametri:
- `fd`: file descriptor
- `offset`: spostamento in byte
- `whence`: punto di riferimento (SEEK_SET, SEEK_CUR, SEEK_END)

La funzione restituisce la nuova posizione in caso di successo, o -1 in caso di errore.

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd;
    char buffer[10];
    off_t position;
    
    fd = open("dati.txt", O_RDONLY);
    
    if (fd == -1) {
        perror("Errore nell'apertura del file");
        exit(EXIT_FAILURE);
    }
    
    // Posiziona l'indicatore 10 byte dopo l'inizio del file
    position = lseek(fd, 10, SEEK_SET);
    
    if (position == -1) {
        perror("Errore nel posizionamento");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    printf("Nuova posizione: %ld\n", (long)position);
    
    // Legge 5 byte dalla nuova posizione
    read(fd, buffer, 5);
    buffer[5] = '\0';
    
    printf("Dati letti dalla posizione %ld: %s\n", (long)position, buffer);
    
    close(fd);
    
    return 0;
}
```

## Confronto tra I/O di Alto e Basso Livello

### Vantaggi dell'I/O a Basso Livello

1. **Controllo diretto**: Accesso diretto alle funzionalità del sistema operativo.
2. **Prestazioni**: Potenzialmente più veloce per operazioni specifiche, poiché evita il buffering aggiuntivo.
3. **Funzionalità specifiche**: Accesso a funzionalità specifiche del sistema operativo non disponibili attraverso le funzioni di alto livello.
4. **Controllo dei permessi**: Maggiore controllo sui permessi dei file durante la creazione.

### Svantaggi dell'I/O a Basso Livello

1. **Complessità**: Richiede una gestione più attenta da parte del programmatore.
2. **Portabilità**: Meno portabile tra sistemi operativi diversi.
3. **Buffering manuale**: Il programmatore deve gestire manualmente il buffering per ottimizzare le prestazioni.
4. **Gestione degli errori**: Richiede una gestione più dettagliata degli errori.

## Conversione tra File Descriptor e FILE*

È possibile convertire un file descriptor in un puntatore a `FILE` e viceversa:

```c
#include <stdio.h>

// Converte un file descriptor in FILE*
FILE *fdopen(int fd, const char *mode);

// Ottiene il file descriptor associato a un FILE*
int fileno(FILE *stream);
```

Questo può essere utile quando si desidera utilizzare funzioni di alto livello su un file aperto con funzioni di basso livello, o viceversa.

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd;
    FILE *fp;
    
    // Apre un file con una funzione di basso livello
    fd = open("dati.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    
    if (fd == -1) {
        perror("Errore nell'apertura del file");
        exit(EXIT_FAILURE);
    }
    
    // Converte il file descriptor in FILE*
    fp = fdopen(fd, "r+");
    
    if (fp == NULL) {
        perror("Errore nella conversione");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    // Ora è possibile utilizzare funzioni di alto livello
    fprintf(fp, "Test di conversione\n");
    
    // Ottiene nuovamente il file descriptor
    int new_fd = fileno(fp);
    
    printf("File descriptor originale: %d, nuovo: %d\n", fd, new_fd);
    
    // Chiude il file (chiude anche il file descriptor)
    fclose(fp);
    
    return 0;
}
```

## Operazioni Avanzate

### Operazioni Non Bloccanti

È possibile aprire un file in modalità non bloccante utilizzando il flag `O_NONBLOCK`:

```c
fd = open("fifo", O_RDONLY | O_NONBLOCK);
```

In modalità non bloccante, le operazioni di lettura e scrittura restituiscono immediatamente se non possono essere completate, anziché bloccare il processo.

### Operazioni di I/O Multiplex

Le funzioni `select()` e `poll()` permettono di monitorare più file descriptor contemporaneamente:

```c
#include <sys/select.h>

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
```

Questo è particolarmente utile per applicazioni che devono gestire più fonti di input/output contemporaneamente.

## Best Practices

1. **Chiudere sempre i file descriptor** dopo l'utilizzo per evitare perdite di risorse.

2. **Controllare sempre i valori restituiti** dalle funzioni di I/O a basso livello per verificare se le operazioni sono avvenute con successo.

3. **Utilizzare il buffering appropriato** per ottimizzare le prestazioni quando si leggono o scrivono grandi quantità di dati.

4. **Scegliere il livello di I/O appropriato** in base alle esigenze dell'applicazione: alto livello per semplicità e portabilità, basso livello per controllo e prestazioni.

5. **Gestire correttamente gli errori** utilizzando `perror()` o `strerror()` per ottenere messaggi di errore significativi.

## Conclusione

Le operazioni di I/O a basso livello offrono un controllo più preciso sulle operazioni di file, ma richiedono una gestione più attenta da parte del programmatore. Sono particolarmente utili in situazioni che richiedono prestazioni ottimali o accesso a funzionalità specifiche del sistema operativo.

## Esercizi

1. Implementa un programma che utilizzi le funzioni di I/O a basso livello per copiare un file, gestendo correttamente i buffer per ottimizzare le prestazioni.

2. Crea un'applicazione che utilizzi `select()` per monitorare contemporaneamente l'input dell'utente e i dati provenienti da un file.

3. Sviluppa un programma che utilizzi le funzioni di I/O a basso livello per implementare un semplice editor di testo binario che permetta di modificare singoli byte in un file.