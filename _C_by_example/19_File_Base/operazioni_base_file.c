/**
 * File: operazioni_base_file.c
 * Descrizione: Esempi di operazioni di base sui file in C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funzione per dimostrare l'apertura e chiusura di un file
void esempio_apertura_chiusura() {
    FILE *file;
    
    printf("\n=== Esempio di Apertura e Chiusura File ===\n");
    
    // Apertura di un file in modalità scrittura
    file = fopen("esempio.txt", "w");
    
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return;
    }
    
    printf("File aperto con successo in modalità scrittura.\n");
    
    // Scrittura nel file
    fprintf(file, "Questo è un esempio di scrittura su file.\n");
    fprintf(file, "Questa è la seconda riga del file.\n");
    
    // Chiusura del file
    if (fclose(file) == 0) {
        printf("File chiuso con successo.\n");
    } else {
        perror("Errore nella chiusura del file");
    }
}

// Funzione per dimostrare la lettura da un file
void esempio_lettura() {
    FILE *file;
    char buffer[100];
    
    printf("\n=== Esempio di Lettura da File ===\n");
    
    // Apertura di un file in modalità lettura
    file = fopen("esempio.txt", "r");
    
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return;
    }
    
    printf("File aperto con successo in modalità lettura.\n");
    printf("Contenuto del file:\n");
    
    // Lettura e stampa del file riga per riga
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    
    // Chiusura del file
    fclose(file);
}

// Funzione per dimostrare la scrittura formattata su file
void esempio_scrittura_formattata() {
    FILE *file;
    int numeri[] = {10, 20, 30, 40, 50};
    char *nomi[] = {"Mario", "Luigi", "Giovanni", "Paolo", "Roberto"};
    
    printf("\n=== Esempio di Scrittura Formattata su File ===\n");
    
    // Apertura di un file in modalità scrittura
    file = fopen("dati.txt", "w");
    
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return;
    }
    
    // Scrittura dell'intestazione
    fprintf(file, "ID\tNome\tValore\n");
    fprintf(file, "------------------------\n");
    
    // Scrittura dei dati formattati
    for (int i = 0; i < 5; i++) {
        fprintf(file, "%d\t%s\t%d\n", i+1, nomi[i], numeri[i]);
    }
    
    printf("Dati scritti nel file 'dati.txt'.\n");
    
    // Chiusura del file
    fclose(file);
}

// Funzione per dimostrare la lettura formattata da file
void esempio_lettura_formattata() {
    FILE *file;
    int id, valore;
    char nome[50];
    char buffer[100];
    
    printf("\n=== Esempio di Lettura Formattata da File ===\n");
    
    // Apertura di un file in modalità lettura
    file = fopen("dati.txt", "r");
    
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return;
    }
    
    // Salto delle prime due righe (intestazione)
    fgets(buffer, sizeof(buffer), file);
    fgets(buffer, sizeof(buffer), file);
    
    printf("Dati letti dal file:\n");
    printf("ID\tNome\tValore\n");
    printf("------------------------\n");
    
    // Lettura e stampa dei dati formattati
    while (fscanf(file, "%d\t%s\t%d\n", &id, nome, &valore) == 3) {
        printf("%d\t%s\t%d\n", id, nome, valore);
    }
    
    // Chiusura del file
    fclose(file);
}

// Funzione per dimostrare la lettura e scrittura di caratteri singoli
void esempio_caratteri() {
    FILE *file_in, *file_out;
    int c;
    
    printf("\n=== Esempio di Lettura e Scrittura di Caratteri ===\n");
    
    // Apertura del file di input
    file_in = fopen("esempio.txt", "r");
    
    if (file_in == NULL) {
        perror("Errore nell'apertura del file di input");
        return;
    }
    
    // Apertura del file di output
    file_out = fopen("esempio_copia.txt", "w");
    
    if (file_out == NULL) {
        perror("Errore nell'apertura del file di output");
        fclose(file_in);
        return;
    }
    
    printf("Copia del file in corso...\n");
    
    // Copia carattere per carattere
    while ((c = fgetc(file_in)) != EOF) {
        fputc(c, file_out);
    }
    
    printf("File copiato con successo.\n");
    
    // Chiusura dei file
    fclose(file_in);
    fclose(file_out);
}

// Funzione per dimostrare la lettura e scrittura binaria
void esempio_binario() {
    FILE *file;
    int numeri[] = {123, 456, 789, 101112, 131415};
    int numeri_letti[5];
    size_t elementi_scritti, elementi_letti;
    
    printf("\n=== Esempio di Lettura e Scrittura Binaria ===\n");
    
    // Apertura del file in modalità scrittura binaria
    file = fopen("dati.bin", "wb");
    
    if (file == NULL) {
        perror("Errore nell'apertura del file per scrittura binaria");
        return;
    }
    
    // Scrittura binaria
    elementi_scritti = fwrite(numeri, sizeof(int), 5, file);
    printf("Elementi scritti: %zu\n", elementi_scritti);
    
    // Chiusura del file
    fclose(file);
    
    // Apertura del file in modalità lettura binaria
    file = fopen("dati.bin", "rb");
    
    if (file == NULL) {
        perror("Errore nell'apertura del file per lettura binaria");
        return;
    }
    
    // Lettura binaria
    elementi_letti = fread(numeri_letti, sizeof(int), 5, file);
    printf("Elementi letti: %zu\n", elementi_letti);
    
    // Stampa dei dati letti
    printf("Dati letti dal file binario:\n");
    for (int i = 0; i < elementi_letti; i++) {
        printf("%d ", numeri_letti[i]);
    }
    printf("\n");
    
    // Chiusura del file
    fclose(file);
}

int main() {
    // Esecuzione degli esempi
    esempio_apertura_chiusura();
    esempio_lettura();
    esempio_scrittura_formattata();
    esempio_lettura_formattata();
    esempio_caratteri();
    esempio_binario();
    
    printf("\nTutti gli esempi sono stati completati.\n");
    
    return 0;
}

/**
 * Esercizi proposti:
 * 
 * 1. Modificare l'esempio di lettura formattata per gestire nomi con spazi
 *    (suggerimento: utilizzare fgets e strtok invece di fscanf).
 * 
 * 2. Implementare un programma che conti il numero di caratteri, parole e righe
 *    in un file di testo.
 * 
 * 3. Creare un programma che unisca il contenuto di due file in un terzo file.
 * 
 * 4. Implementare un semplice editor di testo che permetta di visualizzare, aggiungere
 *    e modificare righe in un file di testo.
 */