/**
 * Soluzione Esercizio 4: Gestione di una Rubrica Telefonica
 *
 * Questo programma implementa una rubrica telefonica che memorizza nomi e numeri
 * di telefono utilizzando allocazione dinamica della memoria.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definizione della struttura Contatto
typedef struct {
    char *nome;
    char *telefono;
} Contatto;

// Definizione della struttura Rubrica
typedef struct {
    Contatto *contatti;
    int num_contatti;
    int capacita;
} Rubrica;

// Funzione per inizializzare la rubrica
Rubrica* inizializza_rubrica(int capacita_iniziale) {
    Rubrica *rubrica = (Rubrica *)malloc(sizeof(Rubrica));
    if (rubrica == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return NULL;
    }
    
    rubrica->contatti = (Contatto *)malloc(capacita_iniziale * sizeof(Contatto));
    if (rubrica->contatti == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        free(rubrica);
        return NULL;
    }
    
    rubrica->num_contatti = 0;
    rubrica->capacita = capacita_iniziale;
    
    return rubrica;
}

// Funzione per aggiungere un nuovo contatto
int aggiungi_contatto(Rubrica *rubrica, const char *nome, const char *telefono) {
    // Verifica se la rubrica è piena e, in tal caso, aumenta la capacità
    if (rubrica->num_contatti >= rubrica->capacita) {
        int nuova_capacita = rubrica->capacita * 2;
        Contatto *nuovi_contatti = (Contatto *)realloc(rubrica->contatti, nuova_capacita * sizeof(Contatto));
        
        if (nuovi_contatti == NULL) {
            printf("Errore: allocazione memoria fallita\n");
            return 0; // Fallimento
        }
        
        rubrica->contatti = nuovi_contatti;
        rubrica->capacita = nuova_capacita;
    }
    
    // Alloca memoria per il nome
    rubrica->contatti[rubrica->num_contatti].nome = (char *)malloc(strlen(nome) + 1);
    if (rubrica->contatti[rubrica->num_contatti].nome == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        return 0; // Fallimento
    }
    
    // Alloca memoria per il numero di telefono
    rubrica->contatti[rubrica->num_contatti].telefono = (char *)malloc(strlen(telefono) + 1);
    if (rubrica->contatti[rubrica->num_contatti].telefono == NULL) {
        printf("Errore: allocazione memoria fallita\n");
        free(rubrica->contatti[rubrica->num_contatti].nome);
        return 0; // Fallimento
    }
    
    // Copia i dati
    strcpy(rubrica->contatti[rubrica->num_contatti].nome, nome);
    strcpy(rubrica->contatti[rubrica->num_contatti].telefono, telefono);
    
    rubrica->num_contatti++;
    return 1; // Successo
}

// Funzione per cercare un contatto per nome
int cerca_contatto(Rubrica *rubrica, const char *nome, Contatto *risultato) {
    for (int i = 0; i < rubrica->num_contatti; i++) {
        if (strcmp(rubrica->contatti[i].nome, nome) == 0) {
            if (risultato != NULL) {
                risultato->nome = rubrica->contatti[i].nome;
                risultato->telefono = rubrica->contatti[i].telefono;
            }
            return i; // Indice del contatto trovato
        }
    }
    
    return -1; // Contatto non trovato
}

// Funzione per modificare un contatto esistente
int modifica_contatto(Rubrica *rubrica, const char *nome, const char *nuovo_telefono) {
    for (int i = 0; i < rubrica->num_contatti; i++) {
        if (strcmp(rubrica->contatti[i].nome, nome) == 0) {
            // Alloca memoria per il nuovo numero di telefono
            char *nuovo = (char *)malloc(strlen(nuovo_telefono) + 1);
            if (nuovo == NULL) {
                printf("Errore: allocazione memoria fallita\n");
                return 0; // Fallimento
            }
            
            // Libera la vecchia memoria e aggiorna il numero
            free(rubrica->contatti[i].telefono);
            rubrica->contatti[i].telefono = nuovo;
            strcpy(rubrica->contatti[i].telefono, nuovo_telefono);
            
            return 1; // Successo
        }
    }
    
    return 0; // Contatto non trovato
}

// Funzione per eliminare un contatto
int elimina_contatto(Rubrica *rubrica, const char *nome) {
    int indice = cerca_contatto(rubrica, nome, NULL);
    
    if (indice == -1) {
        return 0; // Contatto non trovato
    }
    
    // Libera la memoria allocata per il contatto
    free(rubrica->contatti[indice].nome);
    free(rubrica->contatti[indice].telefono);
    
    // Sposta tutti i contatti successivi di una posizione indietro
    for (int i = indice; i < rubrica->num_contatti - 1; i++) {
        rubrica->contatti[i] = rubrica->contatti[i + 1];
    }
    
    rubrica->num_contatti--;
    return 1; // Successo
}

// Funzione per visualizzare tutti i contatti
void visualizza_contatti(Rubrica *rubrica) {
    printf("\nRubrica Telefonica (%d contatti):\n", rubrica->num_contatti);
    printf("--------------------------\n");
    
    if (rubrica->num_contatti == 0) {
        printf("La rubrica è vuota.\n");
        return;
    }
    
    for (int i = 0; i < rubrica->num_contatti; i++) {
        printf("%d. Nome: %s, Telefono: %s\n", i + 1, rubrica->contatti[i].nome, rubrica->contatti[i].telefono);
    }
    printf("--------------------------\n");
}

// Funzione per liberare tutta la memoria allocata
void libera_rubrica(Rubrica *rubrica) {
    if (rubrica == NULL) {
        return;
    }
    
    // Libera la memoria per ogni contatto
    for (int i = 0; i < rubrica->num_contatti; i++) {
        free(rubrica->contatti[i].nome);
        free(rubrica->contatti[i].telefono);
    }
    
    // Libera l'array di contatti e la rubrica stessa
    free(rubrica->contatti);
    free(rubrica);
}

int main() {
    Rubrica *rubrica = inizializza_rubrica(5);
    if (rubrica == NULL) {
        return 1;
    }
    
    int scelta;
    char nome[100], telefono[100];
    
    printf("Benvenuto nella Rubrica Telefonica\n");
    
    do {
        printf("\nOperazioni disponibili:\n");
        printf("1. Aggiungi contatto\n");
        printf("2. Cerca contatto\n");
        printf("3. Modifica contatto\n");
        printf("4. Elimina contatto\n");
        printf("5. Visualizza tutti i contatti\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        getchar(); // Consuma il newline
        
        switch (scelta) {
            case 1: // Aggiungi contatto
                printf("Inserisci nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0'; // Rimuove il newline
                
                printf("Inserisci numero di telefono: ");
                fgets(telefono, sizeof(telefono), stdin);
                telefono[strcspn(telefono, "\n")] = '\0'; // Rimuove il newline
                
                if (aggiungi_contatto(rubrica, nome, telefono)) {
                    printf("Contatto aggiunto con successo!\n");
                } else {
                    printf("Impossibile aggiungere il contatto.\n");
                }
                break;
                
            case 2: // Cerca contatto
                printf("Inserisci nome da cercare: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0'; // Rimuove il newline
                
                Contatto risultato;
                int indice = cerca_contatto(rubrica, nome, &risultato);
                
                if (indice != -1) {
                    printf("Contatto trovato: Nome: %s, Telefono: %s\n", risultato.nome, risultato.telefono);
                } else {
                    printf("Contatto non trovato.\n");
                }
                break;
                
            case 3: // Modifica contatto
                printf("Inserisci nome del contatto da modificare: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0'; // Rimuove il newline
                
                printf("Inserisci nuovo numero di telefono: ");
                fgets(telefono, sizeof(telefono), stdin);
                telefono[strcspn(telefono, "\n")] = '\0'; // Rimuove il newline
                
                if (modifica_contatto(rubrica, nome, telefono)) {
                    printf("Contatto modificato con successo!\n");
                } else {
                    printf("Impossibile modificare il contatto.\n");
                }
                break;
                
            case 4: // Elimina contatto
                printf("Inserisci nome del contatto da eliminare: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0'; // Rimuove il newline
                
                if (elimina_contatto(rubrica, nome)) {
                    printf("Contatto eliminato con successo!\n");
                } else {
                    printf("Impossibile eliminare il contatto.\n");
                }
                break;
                
            case 5: // Visualizza tutti i contatti
                visualizza_contatti(rubrica);
                break;
                
            case 0: // Esci
                printf("Arrivederci!\n");
                break;
                
            default:
                printf("Scelta non valida. Riprova.\n");
        }
    } while (scelta != 0);
    
    // Libera la memoria prima di uscire
    libera_rubrica(rubrica);
    
    return 0;
}