/**
 * Sistema di Gestione Biblioteca
 * 
 * Questo programma implementa un semplice sistema di gestione per una biblioteca,
 * con funzionalità di aggiunta, ricerca, prestito e restituzione di libri.
 * 
 * Concetti applicati:
 * - Strutture e array di strutture
 * - Allocazione dinamica della memoria
 * - File I/O per persistenza dei dati
 * - Puntatori a funzione per ordinamento personalizzato
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TITOLO 100
#define MAX_AUTORE 50
#define MAX_ISBN 20
#define FILENAME "biblioteca.dat"

// Struttura per rappresentare un libro
typedef struct {
    char titolo[MAX_TITOLO];
    char autore[MAX_AUTORE];
    char isbn[MAX_ISBN];
    int anno_pubblicazione;
    int disponibile;  // 1 se disponibile, 0 se in prestito
    time_t data_prestito;  // Data dell'ultimo prestito
} Libro;

// Struttura per gestire la biblioteca
typedef struct {
    Libro* libri;  // Array dinamico di libri
    int num_libri;  // Numero di libri attualmente presenti
    int capacita;   // Capacità totale dell'array
} Biblioteca;

// Funzioni di inizializzazione e pulizia
Biblioteca* inizializza_biblioteca();
void libera_biblioteca(Biblioteca* bib);

// Funzioni di gestione dei libri
int aggiungi_libro(Biblioteca* bib, const char* titolo, const char* autore, 
                  const char* isbn, int anno);
Libro* cerca_libro_per_isbn(Biblioteca* bib, const char* isbn);
Libro* cerca_libri_per_autore(Biblioteca* bib, const char* autore, int* num_trovati);
Libro* cerca_libri_per_titolo(Biblioteca* bib, const char* titolo, int* num_trovati);

// Funzioni per prestito e restituzione
int presta_libro(Biblioteca* bib, const char* isbn);
int restituisci_libro(Biblioteca* bib, const char* isbn);

// Funzioni per ordinamento
void ordina_per_titolo(Biblioteca* bib);
void ordina_per_autore(Biblioteca* bib);
void ordina_per_anno(Biblioteca* bib);

// Funzioni per la persistenza dei dati
int salva_biblioteca(const Biblioteca* bib, const char* filename);
int carica_biblioteca(Biblioteca* bib, const char* filename);

// Funzioni di utilità
void stampa_libro(const Libro* libro);
void stampa_biblioteca(const Biblioteca* bib);

// Implementazione delle funzioni

Biblioteca* inizializza_biblioteca() {
    Biblioteca* bib = (Biblioteca*)malloc(sizeof(Biblioteca));
    if (bib == NULL) {
        fprintf(stderr, "Errore: impossibile allocare memoria per la biblioteca\n");
        return NULL;
    }
    
    bib->capacita = 10;  // Capacità iniziale
    bib->num_libri = 0;
    bib->libri = (Libro*)malloc(bib->capacita * sizeof(Libro));
    
    if (bib->libri == NULL) {
        fprintf(stderr, "Errore: impossibile allocare memoria per i libri\n");
        free(bib);
        return NULL;
    }
    
    return bib;
}

void libera_biblioteca(Biblioteca* bib) {
    if (bib != NULL) {
        if (bib->libri != NULL) {
            free(bib->libri);
        }
        free(bib);
    }
}

int aggiungi_libro(Biblioteca* bib, const char* titolo, const char* autore, 
                  const char* isbn, int anno) {
    // Verifica se il libro esiste già
    if (cerca_libro_per_isbn(bib, isbn) != NULL) {
        fprintf(stderr, "Errore: libro con ISBN %s già presente\n", isbn);
        return 0;
    }
    
    // Verifica se è necessario espandere l'array
    if (bib->num_libri >= bib->capacita) {
        bib->capacita *= 2;  // Raddoppia la capacità
        Libro* temp = (Libro*)realloc(bib->libri, bib->capacita * sizeof(Libro));
        
        if (temp == NULL) {
            fprintf(stderr, "Errore: impossibile espandere la memoria per i libri\n");
            return 0;
        }
        
        bib->libri = temp;
    }
    
    // Aggiungi il nuovo libro
    Libro* nuovo_libro = &(bib->libri[bib->num_libri]);
    strncpy(nuovo_libro->titolo, titolo, MAX_TITOLO - 1);
    nuovo_libro->titolo[MAX_TITOLO - 1] = '\0';  // Assicura terminazione
    
    strncpy(nuovo_libro->autore, autore, MAX_AUTORE - 1);
    nuovo_libro->autore[MAX_AUTORE - 1] = '\0';
    
    strncpy(nuovo_libro->isbn, isbn, MAX_ISBN - 1);
    nuovo_libro->isbn[MAX_ISBN - 1] = '\0';
    
    nuovo_libro->anno_pubblicazione = anno;
    nuovo_libro->disponibile = 1;  // Inizialmente disponibile
    nuovo_libro->data_prestito = 0;
    
    bib->num_libri++;
    return 1;
}

Libro* cerca_libro_per_isbn(Biblioteca* bib, const char* isbn) {
    for (int i = 0; i < bib->num_libri; i++) {
        if (strcmp(bib->libri[i].isbn, isbn) == 0) {
            return &(bib->libri[i]);
        }
    }
    return NULL;
}

Libro* cerca_libri_per_autore(Biblioteca* bib, const char* autore, int* num_trovati) {
    // Prima conta quanti libri corrispondono
    *num_trovati = 0;
    for (int i = 0; i < bib->num_libri; i++) {
        if (strstr(bib->libri[i].autore, autore) != NULL) {
            (*num_trovati)++;
        }
    }
    
    if (*num_trovati == 0) {
        return NULL;
    }
    
    // Alloca memoria per i risultati
    Libro* risultati = (Libro*)malloc((*num_trovati) * sizeof(Libro));
    if (risultati == NULL) {
        fprintf(stderr, "Errore: impossibile allocare memoria per i risultati\n");
        *num_trovati = 0;
        return NULL;
    }
    
    // Copia i libri corrispondenti
    int indice = 0;
    for (int i = 0; i < bib->num_libri; i++) {
        if (strstr(bib->libri[i].autore, autore) != NULL) {
            risultati[indice++] = bib->libri[i];
        }
    }
    
    return risultati;
}

Libro* cerca_libri_per_titolo(Biblioteca* bib, const char* titolo, int* num_trovati) {
    // Implementazione simile a cerca_libri_per_autore
    *num_trovati = 0;
    for (int i = 0; i < bib->num_libri; i++) {
        if (strstr(bib->libri[i].titolo, titolo) != NULL) {
            (*num_trovati)++;
        }
    }
    
    if (*num_trovati == 0) {
        return NULL;
    }
    
    Libro* risultati = (Libro*)malloc((*num_trovati) * sizeof(Libro));
    if (risultati == NULL) {
        fprintf(stderr, "Errore: impossibile allocare memoria per i risultati\n");
        *num_trovati = 0;
        return NULL;
    }
    
    int indice = 0;
    for (int i = 0; i < bib->num_libri; i++) {
        if (strstr(bib->libri[i].titolo, titolo) != NULL) {
            risultati[indice++] = bib->libri[i];
        }
    }
    
    return risultati;
}

int presta_libro(Biblioteca* bib, const char* isbn) {
    Libro* libro = cerca_libro_per_isbn(bib, isbn);
    
    if (libro == NULL) {
        fprintf(stderr, "Errore: libro con ISBN %s non trovato\n", isbn);
        return 0;
    }
    
    if (!libro->disponibile) {
        fprintf(stderr, "Errore: libro con ISBN %s già in prestito\n", isbn);
        return 0;
    }
    
    libro->disponibile = 0;
    libro->data_prestito = time(NULL);
    return 1;
}

int restituisci_libro(Biblioteca* bib, const char* isbn) {
    Libro* libro = cerca_libro_per_isbn(bib, isbn);
    
    if (libro == NULL) {
        fprintf(stderr, "Errore: libro con ISBN %s non trovato\n", isbn);
        return 0;
    }
    
    if (libro->disponibile) {
        fprintf(stderr, "Errore: libro con ISBN %s non risulta in prestito\n", isbn);
        return 0;
    }
    
    libro->disponibile = 1;
    return 1;
}

// Funzioni di confronto per qsort
int confronta_titoli(const void* a, const void* b) {
    return strcmp(((Libro*)a)->titolo, ((Libro*)b)->titolo);
}

int confronta_autori(const void* a, const void* b) {
    return strcmp(((Libro*)a)->autore, ((Libro*)b)->autore);
}

int confronta_anni(const void* a, const void* b) {
    return ((Libro*)a)->anno_pubblicazione - ((Libro*)b)->anno_pubblicazione;
}

void ordina_per_titolo(Biblioteca* bib) {
    qsort(bib->libri, bib->num_libri, sizeof(Libro), confronta_titoli);
}

void ordina_per_autore(Biblioteca* bib) {
    qsort(bib->libri, bib->num_libri, sizeof(Libro), confronta_autori);
}

void ordina_per_anno(Biblioteca* bib) {
    qsort(bib->libri, bib->num_libri, sizeof(Libro), confronta_anni);
}

int salva_biblioteca(const Biblioteca* bib, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        fprintf(stderr, "Errore: impossibile aprire il file %s per la scrittura\n", filename);
        return 0;
    }
    
    // Scrivi il numero di libri
    fwrite(&(bib->num_libri), sizeof(int), 1, file);
    
    // Scrivi i libri
    fwrite(bib->libri, sizeof(Libro), bib->num_libri, file);
    
    fclose(file);
    return 1;
}

int carica_biblioteca(Biblioteca* bib, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        // Non è un errore se il file non esiste ancora
        return 0;
    }
    
    // Leggi il numero di libri
    int num_libri;
    if (fread(&num_libri, sizeof(int), 1, file) != 1) {
        fprintf(stderr, "Errore: impossibile leggere il numero di libri dal file\n");
        fclose(file);
        return 0;
    }
    
    // Assicurati che ci sia abbastanza spazio
    if (num_libri > bib->capacita) {
        bib->capacita = num_libri;
        Libro* temp = (Libro*)realloc(bib->libri, bib->capacita * sizeof(Libro));
        
        if (temp == NULL) {
            fprintf(stderr, "Errore: impossibile allocare memoria per i libri\n");
            fclose(file);
            return 0;
        }
        
        bib->libri = temp;
    }
    
    // Leggi i libri
    if (fread(bib->libri, sizeof(Libro), num_libri, file) != num_libri) {
        fprintf(stderr, "Errore: impossibile leggere i libri dal file\n");
        fclose(file);
        return 0;
    }
    
    bib->num_libri = num_libri;
    
    fclose(file);
    return 1;
}

void stampa_libro(const Libro* libro) {
    printf("ISBN: %s\n", libro->isbn);
    printf("Titolo: %s\n", libro->titolo);
    printf("Autore: %s\n", libro->autore);
    printf("Anno: %d\n", libro->anno_pubblicazione);
    printf("Stato: %s\n", libro->disponibile ? "Disponibile" : "In prestito");
    
    if (!libro->disponibile) {
        char data_str[100];
        struct tm* timeinfo = localtime(&(libro->data_prestito));
        strftime(data_str, sizeof(data_str), "%d/%m/%Y %H:%M:%S", timeinfo);
        printf("Data prestito: %s\n", data_str);
    }
    
    printf("\n");
}

void stampa_biblioteca(const Biblioteca* bib) {
    printf("=== Biblioteca (%d libri) ===\n\n", bib->num_libri);
    
    for (int i = 0; i < bib->num_libri; i++) {
        printf("Libro %d:\n", i + 1);
        stampa_libro(&(bib->libri[i]));
    }
}

// Funzione principale per testare il sistema
int main() {
    Biblioteca* bib = inizializza_biblioteca();
    if (bib == NULL) {
        return EXIT_FAILURE;
    }
    
    // Prova a caricare la biblioteca dal file
    if (carica_biblioteca(bib, FILENAME)) {
        printf("Biblioteca caricata con successo dal file %s\n\n", FILENAME);
    } else {
        printf("Nessun file esistente. Creazione di una nuova biblioteca.\n\n");
        
        // Aggiungi alcuni libri di esempio
        aggiungi_libro(bib, "Il nome della rosa", "Umberto Eco", "9788845292866", 1980);
        aggiungi_libro(bib, "1984", "George Orwell", "9788804668237", 1949);
        aggiungi_libro(bib, "Il signore degli anelli", "J.R.R. Tolkien", "9788830101531", 1954);
        aggiungi_libro(bib, "Fondazione", "Isaac Asimov", "9788804667049", 1951);
        aggiungi_libro(bib, "Il piccolo principe", "Antoine de Saint-Exupéry", "9788845278679", 1943);
    }
    
    // Menu principale
    int scelta = 0;
    char buffer[100];
    
    do {
        printf("\n=== SISTEMA DI GESTIONE BIBLIOTECA ===\n");
        printf("1. Visualizza tutti i libri\n");
        printf("2. Aggiungi un libro\n");
        printf("3. Cerca libro per ISBN\n");
        printf("4. Cerca libri per autore\n");
        printf("5. Cerca libri per titolo\n");
        printf("6. Presta un libro\n");
        printf("7. Restituisci un libro\n");
        printf("8. Ordina libri per titolo\n");
        printf("9. Ordina libri per autore\n");
        printf("10. Ordina libri per anno\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }
        
        scelta = atoi(buffer);
        
        switch (scelta) {
            case 1: // Visualizza tutti i libri
                stampa_biblioteca(bib);
                break;
                
            case 2: { // Aggiungi un libro
                char titolo[MAX_TITOLO];
                char autore[MAX_AUTORE];
                char isbn[MAX_ISBN];
                int anno;
                
                printf("Titolo: ");
                fgets(titolo, sizeof(titolo), stdin);
                titolo[strcspn(titolo, "\n")] = '\0';
                
                printf("Autore: ");
                fgets(autore, sizeof(autore), stdin);
                autore[strcspn(autore, "\n")] = '\0';
                
                printf("ISBN: ");
                fgets(isbn, sizeof(isbn), stdin);
                isbn[strcspn(isbn, "\n")] = '\0';
                
                printf("Anno di pubblicazione: ");
                fgets(buffer, sizeof(buffer), stdin);
                anno = atoi(buffer);
                
                if (aggiungi_libro(bib, titolo, autore, isbn, anno)) {
                    printf("Libro aggiunto con successo!\n");
                    salva_biblioteca(bib, FILENAME);
                }
                break;
            }
                
            case 3: { // Cerca libro per ISBN
                char isbn[MAX_ISBN];
                
                printf("ISBN: ");
                fgets(isbn, sizeof(isbn), stdin);
                isbn[strcspn(isbn, "\n")] = '\0';
                
                Libro* libro = cerca_libro_per_isbn(bib, isbn);
                if (libro != NULL) {
                    printf("\nLibro trovato:\n");
                    stampa_libro(libro);
                } else {
                    printf("Nessun libro trovato con ISBN %s\n", isbn);
                }
                break;
            }
                
            case 4: { // Cerca libri per autore
                char autore[MAX_AUTORE];
                
                printf("Autore: ");
                fgets(autore, sizeof(autore), stdin);
                autore[strcspn(autore, "\n")] = '\0';
                
                int num_trovati;
                Libro* risultati = cerca_libri_per_autore(bib, autore, &num_trovati);
                
                if (risultati != NULL) {
                    printf("\nTrovati %d libri dell'autore '%s':\n\n", num_trovati, autore);
                    for (int i = 0; i < num_trovati; i++) {
                        printf("Libro %d:\n", i + 1);
                        stampa_libro(&risultati[i]);
                    }
                    free(risultati);
                } else {
                    printf("Nessun libro trovato dell'autore '%s'\n", autore);
                }
                break;
            }
                
            case 5: { // Cerca libri per titolo
                char titolo[MAX_TITOLO];
                
                printf("Titolo: ");
                fgets(titolo, sizeof(titolo), stdin);
                titolo[strcspn(titolo, "\n")] = '\0';
                
                int num_trovati;
                Libro* risultati = cerca_libri_per_titolo(bib, titolo, &num_trovati);
                
                if (risultati != NULL) {
                    printf("\nTrovati %d libri con titolo contenente '%s':\n\n", num_trovati, titolo);
                    for (int i = 0; i < num_trovati; i++) {
                        printf("Libro %d:\n", i + 1);
                        stampa_libro(&risultati[i]);
                    }
                    free(risultati);
                } else {
                    printf("Nessun libro trovato con titolo contenente '%s'\n", titolo);
                }
                break;
            }
                
            case 6: { // Presta un libro
                char isbn[MAX_ISBN];
                
                printf("ISBN del libro da prestare: ");
                fgets(isbn, sizeof(isbn), stdin);
                isbn[strcspn(isbn, "\n")] = '\0';
                
                if (presta_libro(bib, isbn)) {
                    printf("Libro prestato con successo!\n");
                    salva_biblioteca(bib, FILENAME);
                }
                break;
            }
                
            case 7: { // Restituisci un libro
                char isbn[MAX_ISBN];
                
                printf("ISBN del libro da restituire: ");
                fgets(isbn, sizeof(isbn), stdin);
                isbn[strcspn(isbn, "\n")] = '\0';
                
                if (restituisci_libro(bib, isbn)) {
                    printf("Libro restituito con successo!\n");
                    salva_biblioteca(bib, FILENAME);
                }
                break;
            }
                
            case 8: // Ordina libri per titolo
                ordina_per_titolo(bib);
                printf("Libri ordinati per titolo\n");
                salva_biblioteca(bib, FILENAME);
                break;
                
            case 9: // Ordina libri per autore
                ordina_per_autore(bib);
                printf("Libri ordinati per autore\n");
                salva_biblioteca(bib, FILENAME);
                break;
                
            case 10: // Ordina libri per anno
                ordina_per_anno(bib);
                printf("Libri ordinati per anno di pubblicazione\n");
                salva_biblioteca(bib, FILENAME);
                break;
                
            case 0: // Esci
                printf("Salvataggio della biblioteca...\n");
                salva_biblioteca(bib, FILENAME);
                printf("Arrivederci!\n");
                break;
                
            default:
                printf("Scelta non valida. Riprova.\n");
        }
        
    } while (scelta != 0);
    
    libera_biblioteca(bib);
    return EXIT_SUCCESS;
}

/**
 * Compilazione ed esecuzione:
 * 
 * Su sistemi Linux/Unix:
 *   gcc -o biblioteca biblioteca.c
 *   ./biblioteca
 * 
 * Su Windows con MinGW:
 *   gcc -o biblioteca biblioteca.c
 *   biblioteca.exe
 * 
 * Note:
 * - Il programma salva i dati in un file binario chiamato "biblioteca.dat"
 * - È possibile modificare il nome del file cambiando la costante FILENAME
 * - Il programma gestisce automaticamente l'espansione della memoria quando necessario
 */