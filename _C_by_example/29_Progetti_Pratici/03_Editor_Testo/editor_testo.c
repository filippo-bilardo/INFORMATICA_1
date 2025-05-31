/**
 * Editor di Testo Semplice
 * 
 * Questo programma implementa un editor di testo a riga di comando con funzionalità
 * di base come apertura, modifica e salvataggio di file di testo.
 * 
 * Concetti applicati:
 * - Manipolazione avanzata di stringhe
 * - Gestione di file di testo
 * - Interfaccia utente a riga di comando
 * - Gestione della memoria per documenti di grandi dimensioni
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
    #include <conio.h>  // Per getch() su Windows
    #define CLEAR_SCREEN "cls"
#else
    #include <unistd.h>
    #include <termios.h>
    #define CLEAR_SCREEN "clear"
    
    // Implementazione di getch() per sistemi Unix/Linux
    int getch() {
        struct termios oldattr, newattr;
        int ch;
        tcgetattr(STDIN_FILENO, &oldattr);
        newattr = oldattr;
        newattr.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
        return ch;
    }
#endif

#define MAX_LINES 1000
#define MAX_LINE_LENGTH 200
#define MAX_FILENAME 100

// Struttura per rappresentare il documento
typedef struct {
    char** lines;        // Array di stringhe (linee)
    int num_lines;       // Numero di linee nel documento
    int capacity;        // Capacità massima dell'array
    char filename[MAX_FILENAME];  // Nome del file aperto
    int modified;        // Flag per indicare se il documento è stato modificato
} Document;

// Funzioni di gestione del documento
Document* create_document();
void free_document(Document* doc);
int insert_line(Document* doc, int position, const char* text);
int delete_line(Document* doc, int position);
int replace_line(Document* doc, int position, const char* text);

// Funzioni di file I/O
int load_file(Document* doc, const char* filename);
int save_file(Document* doc, const char* filename);

// Funzioni dell'editor
void display_document(Document* doc, int current_line, int start_line);
void display_help();
void run_editor(Document* doc);

// Funzioni di utilità
void clear_screen();
char* duplicate_string(const char* str);

int main(int argc, char* argv[]) {
    Document* doc = create_document();
    if (doc == NULL) {
        fprintf(stderr, "Errore: impossibile creare il documento\n");
        return EXIT_FAILURE;
    }
    
    // Se è stato specificato un nome di file, caricalo
    if (argc > 1) {
        if (!load_file(doc, argv[1])) {
            printf("Creazione di un nuovo file: %s\n", argv[1]);
            strncpy(doc->filename, argv[1], MAX_FILENAME - 1);
            doc->filename[MAX_FILENAME - 1] = '\0';
        }
    }
    
    // Esegui l'editor
    run_editor(doc);
    
    // Libera la memoria
    free_document(doc);
    
    return EXIT_SUCCESS;
}

Document* create_document() {
    Document* doc = (Document*)malloc(sizeof(Document));
    if (doc == NULL) {
        return NULL;
    }
    
    doc->capacity = 10;  // Capacità iniziale
    doc->num_lines = 0;
    doc->modified = 0;
    doc->filename[0] = '\0';
    
    doc->lines = (char**)malloc(doc->capacity * sizeof(char*));
    if (doc->lines == NULL) {
        free(doc);
        return NULL;
    }
    
    // Inizializza con una linea vuota
    insert_line(doc, 0, "");
    doc->modified = 0;  // Reset del flag dopo l'inserimento iniziale
    
    return doc;
}

void free_document(Document* doc) {
    if (doc == NULL) {
        return;
    }
    
    // Libera ogni linea
    for (int i = 0; i < doc->num_lines; i++) {
        free(doc->lines[i]);
    }
    
    // Libera l'array di linee e la struttura documento
    free(doc->lines);
    free(doc);
}

int insert_line(Document* doc, int position, const char* text) {
    // Verifica che la posizione sia valida
    if (position < 0 || position > doc->num_lines) {
        return 0;
    }
    
    // Verifica se è necessario espandere l'array
    if (doc->num_lines >= doc->capacity) {
        doc->capacity *= 2;
        char** temp = (char**)realloc(doc->lines, doc->capacity * sizeof(char*));
        if (temp == NULL) {
            return 0;
        }
        doc->lines = temp;
    }
    
    // Duplica la stringa di testo
    char* new_line = duplicate_string(text);
    if (new_line == NULL) {
        return 0;
    }
    
    // Sposta le linee esistenti per fare spazio
    for (int i = doc->num_lines; i > position; i--) {
        doc->lines[i] = doc->lines[i - 1];
    }
    
    // Inserisci la nuova linea
    doc->lines[position] = new_line;
    doc->num_lines++;
    doc->modified = 1;
    
    return 1;
}

int delete_line(Document* doc, int position) {
    // Verifica che la posizione sia valida
    if (position < 0 || position >= doc->num_lines) {
        return 0;
    }
    
    // Libera la memoria della linea da eliminare
    free(doc->lines[position]);
    
    // Sposta le linee successive
    for (int i = position; i < doc->num_lines - 1; i++) {
        doc->lines[i] = doc->lines[i + 1];
    }
    
    doc->num_lines--;
    doc->modified = 1;
    
    // Se il documento è vuoto, aggiungi una linea vuota
    if (doc->num_lines == 0) {
        insert_line(doc, 0, "");
    }
    
    return 1;
}

int replace_line(Document* doc, int position, const char* text) {
    // Verifica che la posizione sia valida
    if (position < 0 || position >= doc->num_lines) {
        return 0;
    }
    
    // Duplica la nuova stringa
    char* new_line = duplicate_string(text);
    if (new_line == NULL) {
        return 0;
    }
    
    // Libera la vecchia linea e sostituiscila
    free(doc->lines[position]);
    doc->lines[position] = new_line;
    doc->modified = 1;
    
    return 1;
}

int load_file(Document* doc, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }
    
    // Resetta il documento
    for (int i = 0; i < doc->num_lines; i++) {
        free(doc->lines[i]);
    }
    doc->num_lines = 0;
    
    // Leggi il file linea per linea
    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL) {
        // Rimuovi il carattere newline se presente
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        // Inserisci la linea nel documento
        if (!insert_line(doc, doc->num_lines, buffer)) {
            fclose(file);
            return 0;
        }
    }
    
    fclose(file);
    
    // Se il file era vuoto, aggiungi una linea vuota
    if (doc->num_lines == 0) {
        insert_line(doc, 0, "");
    }
    
    // Salva il nome del file e resetta il flag di modifica
    strncpy(doc->filename, filename, MAX_FILENAME - 1);
    doc->filename[MAX_FILENAME - 1] = '\0';
    doc->modified = 0;
    
    return 1;
}

int save_file(Document* doc, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return 0;
    }
    
    // Scrivi ogni linea nel file
    for (int i = 0; i < doc->num_lines; i++) {
        fprintf(file, "%s\n", doc->lines[i]);
    }
    
    fclose(file);
    
    // Aggiorna il nome del file e resetta il flag di modifica
    strncpy(doc->filename, filename, MAX_FILENAME - 1);
    doc->filename[MAX_FILENAME - 1] = '\0';
    doc->modified = 0;
    
    return 1;
}

void display_document(Document* doc, int current_line, int start_line) {
    clear_screen();
    
    // Mostra l'intestazione
    printf("=== Editor di Testo Semplice ===\n");
    printf("File: %s%s\n\n", 
           doc->filename[0] ? doc->filename : "[Nuovo File]",
           doc->modified ? " (modificato)" : "");
    
    // Calcola l'intervallo di linee da visualizzare
    int end_line = start_line + 20;  // Mostra 20 linee alla volta
    if (end_line > doc->num_lines) {
        end_line = doc->num_lines;
    }
    
    // Mostra le linee del documento
    for (int i = start_line; i < end_line; i++) {
        if (i == current_line) {
            printf("-> %3d: %s\n", i + 1, doc->lines[i]);
        } else {
            printf("   %3d: %s\n", i + 1, doc->lines[i]);
        }
    }
    
    // Mostra il piè di pagina con i comandi
    printf("\n--- Comandi: h=aiuto, q=esci, s=salva, n=nuovo, a=aggiungi, d=elimina, e=modifica ---\n");
}

void display_help() {
    clear_screen();
    printf("=== Guida dell'Editor di Testo ===\n\n");
    printf("Comandi di navigazione:\n");
    printf("  Freccia Su/Giù: Sposta il cursore tra le linee\n");
    printf("  PgUp/PgDown: Scorre il documento di 10 linee\n\n");
    
    printf("Comandi di editing:\n");
    printf("  a: Aggiungi una nuova linea dopo quella corrente\n");
    printf("  i: Inserisci una nuova linea prima di quella corrente\n");
    printf("  d: Elimina la linea corrente\n");
    printf("  e: Modifica la linea corrente\n\n");
    
    printf("Comandi di file:\n");
    printf("  n: Nuovo documento\n");
    printf("  o: Apri un file esistente\n");
    printf("  s: Salva il documento\n");
    printf("  w: Salva con nome\n\n");
    
    printf("Altri comandi:\n");
    printf("  h: Mostra questa guida\n");
    printf("  q: Esci dall'editor\n\n");
    
    printf("Premi un tasto per tornare all'editor...");
    getch();
}

void run_editor(Document* doc) {
    int current_line = 0;
    int start_line = 0;
    char buffer[MAX_LINE_LENGTH];
    int running = 1;
    
    while (running) {
        // Visualizza il documento
        display_document(doc, current_line, start_line);
        
        // Leggi un comando
        int ch = getch();
        
        // Gestisci i tasti freccia (potrebbero essere sequenze di escape)
        if (ch == 27) {  // ESC
            ch = getch();
            if (ch == '[') {
                ch = getch();
                switch (ch) {
                    case 'A':  // Freccia Su
                        if (current_line > 0) {
                            current_line--;
                            if (current_line < start_line) {
                                start_line = current_line;
                            }
                        }
                        break;
                    case 'B':  // Freccia Giù
                        if (current_line < doc->num_lines - 1) {
                            current_line++;
                            if (current_line >= start_line + 20) {
                                start_line = current_line - 19;
                            }
                        }
                        break;
                    case '5':  // PgUp (alcuni terminali)
                        getch();  // Consuma il carattere '~'
                        start_line -= 10;
                        if (start_line < 0) start_line = 0;
                        current_line -= 10;
                        if (current_line < 0) current_line = 0;
                        break;
                    case '6':  // PgDown (alcuni terminali)
                        getch();  // Consuma il carattere '~'
                        start_line += 10;
                        if (start_line > doc->num_lines - 20) {
                            start_line = doc->num_lines - 20;
                            if (start_line < 0) start_line = 0;
                        }
                        current_line += 10;
                        if (current_line >= doc->num_lines) {
                            current_line = doc->num_lines - 1;
                        }
                        break;
                }
            }
            continue;
        }
        
        // Gestisci i comandi
        switch (ch) {
            case 'h':  // Aiuto
                display_help();
                break;
                
            case 'q':  // Esci
                if (doc->modified) {
                    printf("\nIl documento è stato modificato. Salvare prima di uscire? (s/n): ");
                    char response = getch();
                    if (response == 's' || response == 'S') {
                        if (doc->filename[0] == '\0') {
                            printf("\nNome del file: ");
                            if (fgets(buffer, MAX_FILENAME, stdin) != NULL) {
                                buffer[strcspn(buffer, "\n")] = '\0';
                                save_file(doc, buffer);
                            }
                        } else {
                            save_file(doc, doc->filename);
                        }
                    }
                }
                running = 0;
                break;
                
            case 'n':  // Nuovo documento
                if (doc->modified) {
                    printf("\nIl documento è stato modificato. Salvare prima di crearne uno nuovo? (s/n): ");
                    char response = getch();
                    if (response == 's' || response == 'S') {
                        if (doc->filename[0] == '\0') {
                            printf("\nNome del file: ");
                            if (fgets(buffer, MAX_FILENAME, stdin) != NULL) {
                                buffer[strcspn(buffer, "\n")] = '\0';
                                save_file(doc, buffer);
                            }
                        } else {
                            save_file(doc, doc->filename);
                        }
                    }
                }
                
                // Resetta il documento
                for (int i = 0; i < doc->num_lines; i++) {
                    free(doc->lines[i]);
                }
                doc->num_lines = 0;
                doc->filename[0] = '\0';
                insert_line(doc, 0, "");
                doc->modified = 0;
                current_line = 0;
                start_line = 0;
                break;
                
            case 'o':  // Apri file
                if (doc->modified) {
                    printf("\nIl documento è stato modificato. Salvare prima di aprirne un altro? (s/n): ");
                    char response = getch();
                    if (response == 's' || response == 'S') {
                        if (doc->filename[0] == '\0') {
                            printf("\nNome del file: ");
                            if (fgets(buffer, MAX_FILENAME, stdin) != NULL) {
                                buffer[strcspn(buffer, "\n")] = '\0';
                                save_file(doc, buffer);
                            }
                        } else {
                            save_file(doc, doc->filename);
                        }
                    }
                }
                
                printf("\nNome del file da aprire: ");
                if (fgets(buffer, MAX_FILENAME, stdin) != NULL) {
                    buffer[strcspn(buffer, "\n")] = '\0';
                    if (load_file(doc, buffer)) {
                        printf("\nFile caricato con successo.");
                    } else {
                        printf("\nImpossibile aprire il file.");
                    }
                    getch();  // Attendi un tasto
                }
                current_line = 0;
                start_line = 0;
                break;
                
            case 's':  // Salva
                if (doc->filename[0] == '\0') {
                    printf("\nNome del file: ");
                    if (fgets(buffer, MAX_FILENAME, stdin) != NULL) {
                        buffer[strcspn(buffer, "\n")] = '\0';
                        if (save_file(doc, buffer)) {
                            printf("\nFile salvato con successo.");
                        } else {
                            printf("\nImpossibile salvare il file.");
                        }
                        getch();  // Attendi un tasto
                    }
                } else {
                    if (save_file(doc, doc->filename)) {
                        printf("\nFile salvato con successo.");
                    } else {
                        printf("\nImpossibile salvare il file.");
                    }
                    getch();  // Attendi un tasto
                }
                break;
                
            case 'w':  // Salva con nome
                printf("\nNome del file: ");
                if (fgets(buffer, MAX_FILENAME, stdin) != NULL) {
                    buffer[strcspn(buffer, "\n")] = '\0';
                    if (save_file(doc, buffer)) {
                        printf("\nFile salvato con successo.");
                    } else {
                        printf("\nImpossibile salvare il file.");
                    }
                    getch();  // Attendi un tasto
                }
                break;
                
            case 'a':  // Aggiungi linea dopo quella corrente
                printf("\nNuova linea: ");
                if (fgets(buffer, MAX_LINE_LENGTH, stdin) != NULL) {
                    buffer[strcspn(buffer, "\n")] = '\0';
                    if (insert_line(doc, current_line + 1, buffer)) {
                        current_line++;
                        if (current_line >= start_line + 20) {
                            start_line++;
                        }
                    }
                }
                break;
                
            case 'i':  // Inserisci linea prima di quella corrente
                printf("\nNuova linea: ");
                if (fgets(buffer, MAX_LINE_LENGTH, stdin) != NULL) {
                    buffer[strcspn(buffer, "\n")] = '\0';
                    insert_line(doc, current_line, buffer);
                }
                break;
                
            case 'd':  // Elimina linea corrente
                if (doc->num_lines > 1) {  // Mantieni almeno una linea
                    delete_line(doc, current_line);
                    if (current_line >= doc->num_lines) {
                        current_line = doc->num_lines - 1;
                    }
                }
                break;
                
            case 'e':  // Modifica linea corrente
                printf("\nModifica: %s\n", doc->lines[current_line]);
                printf("Nuova linea: ");
                if (fgets(buffer, MAX_LINE_LENGTH, stdin) != NULL) {
                    buffer[strcspn(buffer, "\n")] = '\0';
                    replace_line(doc, current_line, buffer);
                }
                break;
        }
    }
}

void clear_screen() {
    system(CLEAR_SCREEN);
}

char* duplicate_string(const char* str) {
    size_t len = strlen(str);
    char* new_str = (char*)malloc(len + 1);
    if (new_str == NULL) {
        return NULL;
    }
    strcpy(new_str, str);
    return new_str;
}

/**
 * Compilazione ed esecuzione:
 * 
 * Su sistemi Linux/Unix:
 *   gcc -o editor_testo editor_testo.c
 *   ./editor_testo [nome_file]
 * 
 * Su Windows con MinGW:
 *   gcc -o editor_testo editor_testo.c
 *   editor_testo.exe [nome_file]
 * 
 * Note:
 * - L'editor supporta operazioni di base come inserimento, eliminazione e modifica di linee
 * - La navigazione può essere effettuata con i tasti freccia
 * - Il documento viene salvato in formato testo semplice
 * - L'editor chiede conferma prima di uscire se ci sono modifiche non salvate
 */