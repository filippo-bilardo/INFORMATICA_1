/**
 * File: file_avanzati_esempi.c
 * Descrizione: Esempi avanzati di gestione dei file in C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>   // Per le funzioni di I/O a basso livello
#include <unistd.h>  // Per le funzioni di I/O a basso livello
#include <sys/stat.h>
#include <errno.h>

// Esempio di utilizzo di file temporanei
void esempio_file_temporanei() {
    FILE *temp_file;
    char buffer[100];
    
    printf("\n=== Esempio di File Temporanei ===\n");
    
    // Creazione di un file temporaneo con tmpfile()
    temp_file = tmpfile();
    if (temp_file == NULL) {
        perror("Errore nella creazione del file temporaneo");
        return;
    }
    
    printf("File temporaneo creato con successo.\n");
    
    // Scrittura nel file temporaneo
    fputs("Questo è un contenuto scritto in un file temporaneo.\n", temp_file);
    fputs("Il file verrà eliminato automaticamente alla chiusura.\n", temp_file);
    
    // Riposizionamento all'inizio del file
    rewind(temp_file);
    
    // Lettura e stampa del contenuto
    printf("Contenuto del file temporaneo:\n");
    while (fgets(buffer, sizeof(buffer), temp_file) != NULL) {
        printf("%s", buffer);
    }
    
    // Chiusura del file (verrà eliminato automaticamente)
    fclose(temp_file);
    printf("File temporaneo chiuso e rimosso.\n");
    
    // Utilizzo di tmpnam() per generare un nome di file temporaneo
    char temp_name[L_tmpnam];
    if (tmpnam(temp_name) != NULL) {
        printf("Nome di file temporaneo generato: %s\n", temp_name);
    } else {
        printf("Errore nella generazione del nome temporaneo.\n");
    }
}

// Esempio di I/O a basso livello
void esempio_io_basso_livello() {
    int fd;
    char buffer[100];
    ssize_t bytes_read, bytes_written;
    
    printf("\n=== Esempio di I/O a Basso Livello ===\n");
    
    // Apertura (o creazione) di un file con open()
    fd = open("basso_livello.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Errore nell'apertura del file");
        return;
    }
    
    printf("File aperto con successo in modalità scrittura a basso livello.\n");
    
    // Scrittura nel file con write()
    const char *testo = "Questo è un esempio di scrittura a basso livello.\n";
    bytes_written = write(fd, testo, strlen(testo));
    printf("Bytes scritti: %zd\n", bytes_written);
    
    // Chiusura del file
    close(fd);
    
    // Riapertura del file in modalità lettura
    fd = open("basso_livello.txt", O_RDONLY);
    if (fd == -1) {
        perror("Errore nell'apertura del file");
        return;
    }
    
    // Lettura dal file con read()
    bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';  // Aggiunta del terminatore di stringa
        printf("Contenuto letto (%zd bytes):\n%s", bytes_read, buffer);
    }
    
    // Chiusura del file
    close(fd);
}

// Esempio di tecniche di buffering
void esempio_buffering() {
    FILE *file;
    char buffer[1024];
    
    printf("\n=== Esempio di Tecniche di Buffering ===\n");
    
    // Apertura di un file
    file = fopen("buffering.txt", "w");
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return;
    }
    
    // Impostazione del buffer personalizzato
    if (setvbuf(file, buffer, _IOFBF, sizeof(buffer)) != 0) {
        printf("Errore nell'impostazione del buffer.\n");
    } else {
        printf("Buffer personalizzato impostato con successo.\n");
    }
    
    // Scrittura nel file
    for (int i = 0; i < 100; i++) {
        fprintf(file, "Linea %d: Questo è un test di buffering.\n", i + 1);
    }
    
    // Forzare lo svuotamento del buffer
    printf("Forzatura dello svuotamento del buffer...\n");
    if (fflush(file) == 0) {
        printf("Buffer svuotato con successo.\n");
    } else {
        perror("Errore nello svuotamento del buffer");
    }
    
    // Chiusura del file
    fclose(file);
    
    // Esempio di diversi tipi di buffering
    printf("\nTipi di buffering disponibili:\n");
    printf("_IOFBF: Buffering completo\n");
    printf("_IOLBF: Buffering di linea\n");
    printf("_IONBF: Nessun buffering\n");
    
    // Apertura di un file senza buffering
    file = fopen("no_buffer.txt", "w");
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return;
    }
    
    // Disabilitazione del buffering
    if (setvbuf(file, NULL, _IONBF, 0) != 0) {
        printf("Errore nella disabilitazione del buffer.\n");
    } else {
        printf("Buffering disabilitato con successo.\n");
    }
    
    // Scrittura nel file senza buffering
    fprintf(file, "Questa scrittura avviene senza buffering.\n");
    
    // Chiusura del file
    fclose(file);
}

// Esempio di gestione degli errori avanzata
void esempio_gestione_errori() {
    FILE *file;
    
    printf("\n=== Esempio di Gestione Errori Avanzata ===\n");
    
    // Tentativo di apertura di un file inesistente
    file = fopen("file_inesistente.txt", "r");
    if (file == NULL) {
        printf("Errore nell'apertura del file: %s\n", strerror(errno));
        printf("Codice errore: %d\n", errno);
        
        switch (errno) {
            case ENOENT:
                printf("Il file non esiste.\n");
                break;
            case EACCES:
                printf("Permesso negato.\n");
                break;
            default:
                printf("Errore sconosciuto.\n");
        }
    } else {
        printf("File aperto con successo.\n");
        fclose(file);
    }
    
    // Reset dell'indicatore di errore
    clearerr(file);
    
    // Verifica degli indicatori di errore e fine file
    if (ferror(file)) {
        printf("Si è verificato un errore durante le operazioni sul file.\n");
    }
    
    if (feof(file)) {
        printf("È stata raggiunta la fine del file.\n");
    }
}

int main() {
    // Esecuzione degli esempi
    esempio_file_temporanei();
    esempio_io_basso_livello();
    esempio_buffering();
    esempio_gestione_errori();
    
    printf("\nTutti gli esempi sono stati completati.\n");
    
    return 0;
}

/**
 * Esercizi proposti:
 * 
 * 1. Implementare un programma che utilizzi file temporanei per ordinare grandi quantità di dati
 *    che non possono essere contenuti interamente in memoria.
 * 
 * 2. Creare un programma che utilizzi le funzioni di I/O a basso livello per copiare un file,
 *    implementando una barra di progresso che mostri l'avanzamento della copia.
 * 
 * 3. Implementare un programma che confronti le prestazioni di diverse strategie di buffering
 *    (nessun buffering, buffering di linea, buffering completo) durante la lettura e scrittura
 *    di file di grandi dimensioni.
 * 
 * 4. Creare un sistema di logging che utilizzi tecniche avanzate di gestione dei file per
 *    garantire che i messaggi di log vengano scritti in modo affidabile anche in caso di errori.
 */