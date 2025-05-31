# Esercizi su Strutture e Unioni

In questa sezione troverai una serie di esercizi pratici per consolidare la tua comprensione delle strutture e unioni in C. Gli esercizi sono organizzati in ordine crescente di difficoltà.

## Esercizio 1: Gestione di un Registro Studenti

### Obiettivo
Creare un programma che gestisca un registro di studenti utilizzando le strutture.

### Specifiche
1. Definisci una struttura `Studente` con i seguenti campi:
   - Nome (stringa di massimo 50 caratteri)
   - Cognome (stringa di massimo 50 caratteri)
   - Matricola (intero)
   - Media voti (float)

2. Crea un array di 5 strutture `Studente`

3. Implementa le seguenti funzionalità:
   - Inserimento dei dati di uno studente
   - Visualizzazione dei dati di tutti gli studenti
   - Ricerca di uno studente per matricola
   - Calcolo della media dei voti di tutti gli studenti

### Esempio di implementazione

```c
#include <stdio.h>
#include <string.h>

#define MAX_STUDENTI 5

typedef struct {
    char nome[50];
    char cognome[50];
    int matricola;
    float media;
} Studente;

void inserisciStudente(Studente *s) {
    printf("Inserisci nome: ");
    scanf("%49s", s->nome);
    
    printf("Inserisci cognome: ");
    scanf("%49s", s->cognome);
    
    printf("Inserisci matricola: ");
    scanf("%d", &s->matricola);
    
    printf("Inserisci media voti: ");
    scanf("%f", &s->media);
}

void visualizzaStudenti(Studente studenti[], int n) {
    printf("\nElenco studenti:\n");
    printf("%-20s %-20s %-10s %-10s\n", "Nome", "Cognome", "Matricola", "Media");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("%-20s %-20s %-10d %-10.2f\n", 
               studenti[i].nome, 
               studenti[i].cognome, 
               studenti[i].matricola, 
               studenti[i].media);
    }
}

Studente* cercaStudentePerMatricola(Studente studenti[], int n, int matricola) {
    for (int i = 0; i < n; i++) {
        if (studenti[i].matricola == matricola) {
            return &studenti[i];
        }
    }
    return NULL; // Studente non trovato
}

float calcolaMediaVoti(Studente studenti[], int n) {
    float somma = 0.0f;
    for (int i = 0; i < n; i++) {
        somma += studenti[i].media;
    }
    return n > 0 ? somma / n : 0.0f;
}

int main() {
    Studente registro[MAX_STUDENTI];
    int numStudenti = 0;
    int scelta;
    int matricola;
    
    do {
        printf("\nGestione Registro Studenti\n");
        printf("1. Inserisci studente\n");
        printf("2. Visualizza tutti gli studenti\n");
        printf("3. Cerca studente per matricola\n");
        printf("4. Calcola media voti\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        
        switch (scelta) {
            case 1:
                if (numStudenti < MAX_STUDENTI) {
                    inserisciStudente(&registro[numStudenti]);
                    numStudenti++;
                } else {
                    printf("Registro pieno!\n");
                }
                break;
            case 2:
                visualizzaStudenti(registro, numStudenti);
                break;
            case 3:
                printf("Inserisci matricola da cercare: ");
                scanf("%d", &matricola);
                Studente* trovato = cercaStudentePerMatricola(registro, numStudenti, matricola);
                if (trovato) {
                    printf("Studente trovato:\n");
                    printf("Nome: %s\n", trovato->nome);
                    printf("Cognome: %s\n", trovato->cognome);
                    printf("Matricola: %d\n", trovato->matricola);
                    printf("Media: %.2f\n", trovato->media);
                } else {
                    printf("Studente non trovato!\n");
                }
                break;
            case 4:
                if (numStudenti > 0) {
                    printf("Media voti di tutti gli studenti: %.2f\n", calcolaMediaVoti(registro, numStudenti));
                } else {
                    printf("Nessuno studente nel registro!\n");
                }
                break;
            case 0:
                printf("Arrivederci!\n");
                break;
            default:
                printf("Scelta non valida!\n");
        }
    } while (scelta != 0);
    
    return 0;
}
```

## Esercizio 2: Gestione di Forme Geometriche

### Obiettivo
Creare un programma che utilizzi unioni per rappresentare diverse forme geometriche.

### Specifiche
1. Definisci un'enumerazione `TipoForma` con i valori: `CERCHIO`, `RETTANGOLO`, `TRIANGOLO`

2. Definisci una struttura `Cerchio` con il campo `raggio` (float)

3. Definisci una struttura `Rettangolo` con i campi `base` e `altezza` (float)

4. Definisci una struttura `Triangolo` con i campi `lato1`, `lato2` e `lato3` (float)

5. Definisci una struttura `Forma` che contenga:
   - Un campo `tipo` di tipo `TipoForma`
   - Un'unione che può contenere una delle tre forme definite

6. Implementa funzioni per:
   - Calcolare l'area di una forma
   - Calcolare il perimetro di una forma

### Esempio di implementazione

```c
#include <stdio.h>
#include <math.h>

typedef enum {
    CERCHIO,
    RETTANGOLO,
    TRIANGOLO
} TipoForma;

typedef struct {
    float raggio;
} Cerchio;

typedef struct {
    float base;
    float altezza;
} Rettangolo;

typedef struct {
    float lato1;
    float lato2;
    float lato3;
} Triangolo;

typedef struct {
    TipoForma tipo;
    union {
        Cerchio cerchio;
        Rettangolo rettangolo;
        Triangolo triangolo;
    } dati;
} Forma;

float calcolaArea(Forma f) {
    switch (f.tipo) {
        case CERCHIO:
            return 3.14159f * f.dati.cerchio.raggio * f.dati.cerchio.raggio;
        case RETTANGOLO:
            return f.dati.rettangolo.base * f.dati.rettangolo.altezza;
        case TRIANGOLO: {
            // Formula di Erone
            float s = (f.dati.triangolo.lato1 + f.dati.triangolo.lato2 + f.dati.triangolo.lato3) / 2;
            return sqrt(s * (s - f.dati.triangolo.lato1) * (s - f.dati.triangolo.lato2) * (s - f.dati.triangolo.lato3));
        }
        default:
            return 0.0f;
    }
}

float calcolaPerimetro(Forma f) {
    switch (f.tipo) {
        case CERCHIO:
            return 2.0f * 3.14159f * f.dati.cerchio.raggio;
        case RETTANGOLO:
            return 2.0f * (f.dati.rettangolo.base + f.dati.rettangolo.altezza);
        case TRIANGOLO:
            return f.dati.triangolo.lato1 + f.dati.triangolo.lato2 + f.dati.triangolo.lato3;
        default:
            return 0.0f;
    }
}

int main() {
    Forma forme[3];
    
    // Inizializzazione di un cerchio
    forme[0].tipo = CERCHIO;
    forme[0].dati.cerchio.raggio = 5.0f;
    
    // Inizializzazione di un rettangolo
    forme[1].tipo = RETTANGOLO;
    forme[1].dati.rettangolo.base = 4.0f;
    forme[1].dati.rettangolo.altezza = 6.0f;
    
    // Inizializzazione di un triangolo
    forme[2].tipo = TRIANGOLO;
    forme[2].dati.triangolo.lato1 = 3.0f;
    forme[2].dati.triangolo.lato2 = 4.0f;
    forme[2].dati.triangolo.lato3 = 5.0f;
    
    // Stampa delle aree e dei perimetri
    char* nomi[] = {"Cerchio", "Rettangolo", "Triangolo"};
    
    for (int i = 0; i < 3; i++) {
        printf("%s:\n", nomi[forme[i].tipo]);
        printf("  Area: %.2f\n", calcolaArea(forme[i]));
        printf("  Perimetro: %.2f\n\n", calcolaPerimetro(forme[i]));
    }
    
    return 0;
}
```

## Esercizio 3: Sistema di Gestione Biblioteca

### Obiettivo
Creare un sistema di gestione per una biblioteca utilizzando strutture, unioni e campi di bit.

### Specifiche
1. Definisci un'enumerazione `TipoMedia` con i valori: `LIBRO`, `RIVISTA`, `DVD`, `CD`

2. Definisci una struttura `Libro` con i campi:
   - Titolo (stringa)
   - Autore (stringa)
   - ISBN (stringa)
   - Anno pubblicazione (intero)

3. Definisci strutture simili per `Rivista`, `DVD` e `CD`

4. Definisci una struttura `Media` che contenga:
   - Un campo `tipo` di tipo `TipoMedia`
   - Un'unione che può contenere uno dei quattro tipi di media
   - Un campo di bit `stato` che indichi se il media è:
     - Disponibile (1 bit)
     - In prestito (1 bit)
     - Riservato (1 bit)
     - Danneggiato (1 bit)

5. Implementa un sistema completo con funzioni per:
   - Aggiungere un nuovo media alla biblioteca
   - Cercare un media per titolo
   - Prestare un media
   - Restituire un media
   - Visualizzare lo stato di un media

### Suggerimenti
- Utilizza array dinamici per gestire la collezione di media
- Implementa una funzione di menu per interagire con l'utente
- Usa i campi di bit per gestire efficientemente lo stato dei media

### Esempio di implementazione

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    LIBRO,
    RIVISTA,
    DVD,
    CD
} TipoMedia;

typedef struct {
    char titolo[100];
    char autore[100];
    char isbn[20];
    int anno;
} Libro;

typedef struct {
    char titolo[100];
    char editore[100];
    int numero;
    int anno;
} Rivista;

typedef struct {
    char titolo[100];
    char regista[100];
    int durata; // in minuti
    int anno;
} DVD;

typedef struct {
    char titolo[100];
    char artista[100];
    int tracce;
    int anno;
} CD;

typedef struct {
    TipoMedia tipo;
    union {
        Libro libro;
        Rivista rivista;
        DVD dvd;
        CD cd;
    } dati;
    struct {
        unsigned int disponibile : 1;
        unsigned int in_prestito : 1;
        unsigned int riservato : 1;
        unsigned int danneggiato : 1;
    } stato;
} Media;

// Funzione per aggiungere un nuovo media
void aggiungiMedia(Media** biblioteca, int* numMedia) {
    *biblioteca = realloc(*biblioteca, (*numMedia + 1) * sizeof(Media));
    Media* nuovoMedia = &(*biblioteca)[*numMedia];
    
    printf("Seleziona tipo di media:\n");
    printf("0. Libro\n");
    printf("1. Rivista\n");
    printf("2. DVD\n");
    printf("3. CD\n");
    printf("Scelta: ");
    int scelta;
    scanf("%d", &scelta);
    nuovoMedia->tipo = (TipoMedia)scelta;
    
    printf("Inserisci titolo: ");
    scanf(" %99[^\n]", scelta == LIBRO ? nuovoMedia->dati.libro.titolo : 
                        scelta == RIVISTA ? nuovoMedia->dati.rivista.titolo : 
                        scelta == DVD ? nuovoMedia->dati.dvd.titolo : 
                        nuovoMedia->dati.cd.titolo);
    
    printf("Inserisci anno: ");
    scanf("%d", &(scelta == LIBRO ? nuovoMedia->dati.libro.anno : 
                  scelta == RIVISTA ? nuovoMedia->dati.rivista.anno : 
                  scelta == DVD ? nuovoMedia->dati.dvd.anno : 
                  nuovoMedia->dati.cd.anno));
    
    switch (scelta) {
        case LIBRO:
            printf("Inserisci autore: ");
            scanf(" %99[^\n]", nuovoMedia->dati.libro.autore);
            printf("Inserisci ISBN: ");
            scanf(" %19[^\n]", nuovoMedia->dati.libro.isbn);
            break;
        case RIVISTA:
            printf("Inserisci editore: ");
            scanf(" %99[^\n]", nuovoMedia->dati.rivista.editore);
            printf("Inserisci numero: ");
            scanf("%d", &nuovoMedia->dati.rivista.numero);
            break;
        case DVD:
            printf("Inserisci regista: ");
            scanf(" %99[^\n]", nuovoMedia->dati.dvd.regista);
            printf("Inserisci durata (minuti): ");
            scanf("%d", &nuovoMedia->dati.dvd.durata);
            break;
        case CD:
            printf("Inserisci artista: ");
            scanf(" %99[^\n]", nuovoMedia->dati.cd.artista);
            printf("Inserisci numero tracce: ");
            scanf("%d", &nuovoMedia->dati.cd.tracce);
            break;
    }
    
    // Imposta lo stato iniziale
    nuovoMedia->stato.disponibile = 1;
    nuovoMedia->stato.in_prestito = 0;
    nuovoMedia->stato.riservato = 0;
    nuovoMedia->stato.danneggiato = 0;
    
    (*numMedia)++;
    printf("Media aggiunto con successo!\n");
}

// Funzione per cercare un media per titolo
Media* cercaMediaPerTitolo(Media* biblioteca, int numMedia, const char* titolo) {
    for (int i = 0; i < numMedia; i++) {
        const char* mediaTitle = NULL;
        switch (biblioteca[i].tipo) {
            case LIBRO: mediaTitle = biblioteca[i].dati.libro.titolo; break;
            case RIVISTA: mediaTitle = biblioteca[i].dati.rivista.titolo; break;
            case DVD: mediaTitle = biblioteca[i].dati.dvd.titolo; break;
            case CD: mediaTitle = biblioteca[i].dati.cd.titolo; break;
        }
        
        if (mediaTitle && strcmp(mediaTitle, titolo) == 0) {
            return &biblioteca[i];
        }
    }
    return NULL;
}

// Funzione per prestare un media
void prestaMedia(Media* media) {
    if (!media->stato.disponibile) {
        printf("Media non disponibile!\n");
        return;
    }
    if (media->stato.danneggiato) {
        printf("Media danneggiato, non può essere prestato!\n");
        return;
    }
    if (media->stato.riservato) {
        printf("Media riservato, non può essere prestato!\n");
        return;
    }
    
    media->stato.disponibile = 0;
    media->stato.in_prestito = 1;
    printf("Media prestato con successo!\n");
}

// Funzione per restituire un media
void restituisciMedia(Media* media) {
    if (!media->stato.in_prestito) {
        printf("Media non in prestito!\n");
        return;
    }
    
    media->stato.disponibile = 1;
    media->stato.in_prestito = 0;
    printf("Media restituito con successo!\n");
}

// Funzione per visualizzare lo stato di un media
void visualizzaStatoMedia(Media* media) {
    printf("Stato del media:\n");
    printf("Disponibile: %s\n", media->stato.disponibile ? "Sì" : "No");
    printf("In prestito: %s\n", media->stato.in_prestito ? "Sì" : "No");
    printf("Riservato: %s\n", media->stato.riservato ? "Sì" : "No");
    printf("Danneggiato: %s\n", media->stato.danneggiato ? "Sì" : "No");
}

// Funzione per visualizzare i dettagli di un media
void visualizzaMedia(Media* media) {
    printf("Tipo: ");
    switch (media->tipo) {
        case LIBRO: printf("Libro\n"); break;
        case RIVISTA: printf("Rivista\n"); break;
        case DVD: printf("DVD\n"); break;
        case CD: printf("CD\n"); break;
    }
    
    printf("Titolo: ");
    switch (media->tipo) {
        case LIBRO: printf("%s\n", media->dati.libro.titolo); break;
        case RIVISTA: printf("%s\n", media->dati.rivista.titolo); break;
        case DVD: printf("%s\n", media->dati.dvd.titolo); break;
        case CD: printf("%s\n", media->dati.cd.titolo); break;
    }
    
    printf("Anno: ");
    switch (media->tipo) {
        case LIBRO: printf("%d\n", media->dati.libro.anno); break;
        case RIVISTA: printf("%d\n", media->dati.rivista.anno); break;
        case DVD: printf("%d\n", media->dati.dvd.anno); break;
        case CD: printf("%d\n", media->dati.cd.anno); break;
    }
    
    switch (media->tipo) {
        case LIBRO:
            printf("Autore: %s\n", media->dati.libro.autore);
            printf("ISBN: %s\n", media->dati.libro.isbn);
            break;
        case RIVISTA:
            printf("Editore: %s\n", media->dati.rivista.editore);
            printf("Numero: %d\n", media->dati.rivista.numero);
            break;
        case DVD:
            printf("Regista: %s\n", media->dati.dvd.regista);
            printf("Durata: %d minuti\n", media->dati.dvd.durata);
            break;
        case CD:
            printf("Artista: %s\n", media->dati.cd.artista);
            printf("Tracce: %d\n", media->dati.cd.tracce);
            break;
    }
    
    visualizzaStatoMedia(media);
}

int main() {
    Media* biblioteca = NULL;
    int numMedia = 0;
    int scelta;
    char titolo[100];
    
    do {
        printf("\nGestione Biblioteca\n");
        printf("1. Aggiungi media\n");
        printf("2. Cerca media per titolo\n");
        printf("3. Presta media\n");
        printf("4. Restituisci media\n");
        printf("5. Visualizza stato media\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        
        switch (scelta) {
            case 1:
                aggiungiMedia(&biblioteca, &numMedia);
                break;
            case 2:
            case 3:
            case 4:
            case 5: {
                if (numMedia == 0) {
                    printf("Nessun media in biblioteca!\n");
                    break;
                }
                
                printf("Inserisci titolo: ");
                scanf(" %99[^\n]", titolo);
                Media* media = cercaMediaPerTitolo(biblioteca, numMedia, titolo);
                
                if (media) {
                    switch (scelta) {
                        case 2:
                            visualizzaMedia(media);
                            break;
                        case 3:
                            prestaMedia(media);
                            break;
                        case 4:
                            restituisciMedia(media);
                            break;
                        case 5:
                            visualizzaStatoMedia(media);
                            break;
                    }
                } else {
                    printf("Media non trovato!\n");
                }
                break;
            }
            case 0:
                printf("Arrivederci!\n");
                break;
            default:
                printf("Scelta non valida!\n");
        }
    } while (scelta != 0);
    
    // Libera la memoria
    free(biblioteca);
    
    return 0;
}
```

## Esercizio 4: Rubrica Telefonica con Ordinamento

### Obiettivo
Creare un programma che implementi una rubrica telefonica con funzionalità di ordinamento e ricerca avanzata utilizzando strutture annidate e allocazione dinamica della memoria.

### Specifiche
1. Definisci una struttura `Indirizzo` con i campi:
   - Via (stringa di massimo 100 caratteri)
   - Numero civico (intero)
   - CAP (stringa di 5 caratteri)
   - Città (stringa di massimo 50 caratteri)
   - Provincia (stringa di 2 caratteri)

2. Definisci una struttura `Contatto` con i campi:
   - Nome (stringa di massimo 50 caratteri)
   - Cognome (stringa di massimo 50 caratteri)
   - Telefono fisso (stringa di massimo 20 caratteri)
   - Cellulare (stringa di massimo 20 caratteri)
   - Email (stringa di massimo 100 caratteri)
   - Indirizzo (struttura `Indirizzo`)
   - Categoria (enumerazione con valori: FAMIGLIA, AMICI, LAVORO, ALTRO)

3. Implementa le seguenti funzionalità:
   - Aggiunta di un nuovo contatto
   - Modifica di un contatto esistente
   - Eliminazione di un contatto
   - Ricerca di contatti per nome, cognome o numero di telefono
   - Ordinamento dei contatti per nome, cognome o categoria
   - Visualizzazione di tutti i contatti o filtrati per categoria
   - Salvataggio e caricamento della rubrica da file

### Esempio di implementazione

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    FAMIGLIA,
    AMICI,
    LAVORO,
    ALTRO
} Categoria;

typedef struct {
    char via[100];
    int numero_civico;
    char cap[6]; // 5 caratteri + terminatore
    char citta[50];
    char provincia[3]; // 2 caratteri + terminatore
} Indirizzo;

typedef struct {
    char nome[50];
    char cognome[50];
    char telefono_fisso[20];
    char cellulare[20];
    char email[100];
    Indirizzo indirizzo;
    Categoria categoria;
} Contatto;

typedef struct {
    Contatto* contatti;
    int num_contatti;
    int capacita;
} Rubrica;

// Inizializza una nuova rubrica
Rubrica* inizializzaRubrica(int capacita_iniziale) {
    Rubrica* rubrica = (Rubrica*)malloc(sizeof(Rubrica));
    if (rubrica == NULL) {
        printf("Errore: impossibile allocare memoria per la rubrica\n");
        return NULL;
    }
    
    rubrica->contatti = (Contatto*)malloc(capacita_iniziale * sizeof(Contatto));
    if (rubrica->contatti == NULL) {
        printf("Errore: impossibile allocare memoria per i contatti\n");
        free(rubrica);
        return NULL;
    }
    
    rubrica->num_contatti = 0;
    rubrica->capacita = capacita_iniziale;
    
    return rubrica;
}

// Libera la memoria allocata per la rubrica
void liberaRubrica(Rubrica* rubrica) {
    if (rubrica != NULL) {
        free(rubrica->contatti);
        free(rubrica);
    }
}

// Espande la capacità della rubrica se necessario
int espandiRubrica(Rubrica* rubrica) {
    if (rubrica->num_contatti >= rubrica->capacita) {
        int nuova_capacita = rubrica->capacita * 2;
        Contatto* nuovi_contatti = (Contatto*)realloc(rubrica->contatti, nuova_capacita * sizeof(Contatto));
        
        if (nuovi_contatti == NULL) {
            printf("Errore: impossibile espandere la rubrica\n");
            return 0;
        }
        
        rubrica->contatti = nuovi_contatti;
        rubrica->capacita = nuova_capacita;
    }
    
    return 1;
}

// Aggiunge un nuovo contatto alla rubrica
int aggiungiContatto(Rubrica* rubrica, Contatto nuovo_contatto) {
    if (!espandiRubrica(rubrica)) {
        return 0;
    }
    
    rubrica->contatti[rubrica->num_contatti] = nuovo_contatto;
    rubrica->num_contatti++;
    
    return 1;
}

// Elimina un contatto dalla rubrica per indice
int eliminaContatto(Rubrica* rubrica, int indice) {
    if (indice < 0 || indice >= rubrica->num_contatti) {
        printf("Errore: indice non valido\n");
        return 0;
    }
    
    // Sposta tutti i contatti successivi indietro di una posizione
    for (int i = indice; i < rubrica->num_contatti - 1; i++) {
        rubrica->contatti[i] = rubrica->contatti[i + 1];
    }
    
    rubrica->num_contatti--;
    return 1;
}

// Cerca un contatto per nome o cognome
int cercaContatto(Rubrica* rubrica, const char* chiave, Contatto* risultati[], int max_risultati) {
    int trovati = 0;
    
    for (int i = 0; i < rubrica->num_contatti && trovati < max_risultati; i++) {
        if (strstr(rubrica->contatti[i].nome, chiave) != NULL || 
            strstr(rubrica->contatti[i].cognome, chiave) != NULL || 
            strstr(rubrica->contatti[i].cellulare, chiave) != NULL) {
            
            risultati[trovati] = &rubrica->contatti[i];
            trovati++;
        }
    }
    
    return trovati;
}

// Confronta due contatti per cognome (per qsort)
int confrontaPerCognome(const void* a, const void* b) {
    Contatto* contatto_a = (Contatto*)a;
    Contatto* contatto_b = (Contatto*)b;
    
    return strcmp(contatto_a->cognome, contatto_b->cognome);
}

// Confronta due contatti per nome (per qsort)
int confrontaPerNome(const void* a, const void* b) {
    Contatto* contatto_a = (Contatto*)a;
    Contatto* contatto_b = (Contatto*)b;
    
    return strcmp(contatto_a->nome, contatto_b->nome);
}

// Confronta due contatti per categoria (per qsort)
int confrontaPerCategoria(const void* a, const void* b) {
    Contatto* contatto_a = (Contatto*)a;
    Contatto* contatto_b = (Contatto*)b;
    
    return contatto_a->categoria - contatto_b->categoria;
}

// Ordina i contatti nella rubrica
void ordinaRubrica(Rubrica* rubrica, int criterio) {
    if (rubrica->num_contatti <= 1) {
        return; // Niente da ordinare
    }
    
    switch (criterio) {
        case 1: // Ordina per cognome
            qsort(rubrica->contatti, rubrica->num_contatti, sizeof(Contatto), confrontaPerCognome);
            break;
        case 2: // Ordina per nome
            qsort(rubrica->contatti, rubrica->num_contatti, sizeof(Contatto), confrontaPerNome);
            break;
        case 3: // Ordina per categoria
            qsort(rubrica->contatti, rubrica->num_contatti, sizeof(Contatto), confrontaPerCategoria);
            break;
        default:
            printf("Criterio di ordinamento non valido\n");
    }
}

// Visualizza i dettagli di un contatto
void visualizzaContatto(Contatto* contatto) {
    const char* categorie[] = {"Famiglia", "Amici", "Lavoro", "Altro"};
    
    printf("Nome: %s\n", contatto->nome);
    printf("Cognome: %s\n", contatto->cognome);
    printf("Telefono fisso: %s\n", contatto->telefono_fisso);
    printf("Cellulare: %s\n", contatto->cellulare);
    printf("Email: %s\n", contatto->email);
    printf("Indirizzo: %s, %d - %s %s (%s)\n", 
           contatto->indirizzo.via, 
           contatto->indirizzo.numero_civico, 
           contatto->indirizzo.cap, 
           contatto->indirizzo.citta, 
           contatto->indirizzo.provincia);
    printf("Categoria: %s\n", categorie[contatto->categoria]);
}

// Visualizza tutti i contatti nella rubrica
void visualizzaRubrica(Rubrica* rubrica, int categoria_filtro) {
    printf("\nRubrica Telefonica (%d contatti):\n", rubrica->num_contatti);
    printf("-----------------------------------------\n");
    
    const char* categorie[] = {"Famiglia", "Amici", "Lavoro", "Altro"};
    int contatti_mostrati = 0;
    
    for (int i = 0; i < rubrica->num_contatti; i++) {
        // Se categoria_filtro è -1, mostra tutti i contatti
        // altrimenti mostra solo i contatti della categoria specificata
        if (categoria_filtro == -1 || rubrica->contatti[i].categoria == categoria_filtro) {
            printf("\n[%d] %s %s (%s)\n", 
                   i + 1, 
                   rubrica->contatti[i].nome, 
                   rubrica->contatti[i].cognome, 
                   categorie[rubrica->contatti[i].categoria]);
            printf("Tel: %s, Cell: %s\n", 
                   rubrica->contatti[i].telefono_fisso, 
                   rubrica->contatti[i].cellulare);
            contatti_mostrati++;
        }
    }
    
    if (contatti_mostrati == 0) {
        printf("Nessun contatto trovato\n");
    }
}

// Salva la rubrica su file
int salvaRubrica(Rubrica* rubrica, const char* nome_file) {
    FILE* file = fopen(nome_file, "wb");
    if (file == NULL) {
        printf("Errore: impossibile aprire il file %s per la scrittura\n", nome_file);
        return 0;
    }
    
    // Scrivi il numero di contatti
    fwrite(&rubrica->num_contatti, sizeof(int), 1, file);
    
    // Scrivi i contatti
    fwrite(rubrica->contatti, sizeof(Contatto), rubrica->num_contatti, file);
    
    fclose(file);
    return 1;
}

// Carica la rubrica da file
Rubrica* caricaRubrica(const char* nome_file) {
    FILE* file = fopen(nome_file, "rb");
    if (file == NULL) {
        printf("Errore: impossibile aprire il file %s per la lettura\n", nome_file);
        return NULL;
    }
    
    // Leggi il numero di contatti
    int num_contatti;
    if (fread(&num_contatti, sizeof(int), 1, file) != 1) {
        printf("Errore: impossibile leggere il numero di contatti dal file\n");
        fclose(file);
        return NULL;
    }
    
    // Inizializza la rubrica con la capacità necessaria
    Rubrica* rubrica = inizializzaRubrica(num_contatti > 0 ? num_contatti : 10);
    if (rubrica == NULL) {
        fclose(file);
        return NULL;
    }
    
    // Leggi i contatti
    if (num_contatti > 0) {
        if (fread(rubrica->contatti, sizeof(Contatto), num_contatti, file) != num_contatti) {
            printf("Errore: impossibile leggere i contatti dal file\n");
            liberaRubrica(rubrica);
            fclose(file);
            return NULL;
        }
        rubrica->num_contatti = num_contatti;
    }
    
    fclose(file);
    return rubrica;
}

// Funzione per inserire un nuovo contatto
void inserisciNuovoContatto(Rubrica* rubrica) {
    Contatto nuovo;
    
    printf("Inserisci nome: ");
    scanf(" %49[^\n]", nuovo.nome);
    
    printf("Inserisci cognome: ");
    scanf(" %49[^\n]", nuovo.cognome);
    
    printf("Inserisci telefono fisso: ");
    scanf(" %19[^\n]", nuovo.telefono_fisso);
    
    printf("Inserisci cellulare: ");
    scanf(" %19[^\n]", nuovo.cellulare);
    
    printf("Inserisci email: ");
    scanf(" %99[^\n]", nuovo.email);
    
    printf("Inserisci via: ");
    scanf(" %99[^\n]", nuovo.indirizzo.via);
    
    printf("Inserisci numero civico: ");
    scanf("%d", &nuovo.indirizzo.numero_civico);
    
    printf("Inserisci CAP: ");
    scanf(" %5[^\n]", nuovo.indirizzo.cap);
    
    printf("Inserisci città: ");
    scanf(" %49[^\n]", nuovo.indirizzo.citta);
    
    printf("Inserisci provincia (2 caratteri): ");
    scanf(" %2[^\n]", nuovo.indirizzo.provincia);
    
    printf("Seleziona categoria:\n");
    printf("0. Famiglia\n");
    printf("1. Amici\n");
    printf("2. Lavoro\n");
    printf("3. Altro\n");
    printf("Scelta: ");
    int cat;
    scanf("%d", &cat);
    nuovo.categoria = (cat >= 0 && cat <= 3) ? cat : ALTRO;
    
    if (aggiungiContatto(rubrica, nuovo)) {
        printf("Contatto aggiunto con successo!\n");
    } else {
        printf("Errore nell'aggiunta del contatto\n");
    }
}

int main() {
    Rubrica* rubrica = NULL;
    char nome_file[] = "rubrica.dat";
    
    // Prova a caricare la rubrica da file, altrimenti ne crea una nuova
    rubrica = caricaRubrica(nome_file);
    if (rubrica == NULL) {
        printf("Creazione di una nuova rubrica...\n");
        rubrica = inizializzaRubrica(10);
        if (rubrica == NULL) {
            printf("Errore: impossibile creare la rubrica\n");
            return 1;
        }
    }
    
    int scelta;
    char chiave[50];
    Contatto* risultati[100];
    int num_risultati;
    
    do {
        printf("\nGestione Rubrica Telefonica\n");
        printf("1. Inserisci nuovo contatto\n");
        printf("2. Visualizza tutti i contatti\n");
        printf("3. Cerca contatto\n");
        printf("4. Elimina contatto\n");
        printf("5. Ordina rubrica\n");
        printf("6. Filtra per categoria\n");
        printf("7. Salva rubrica\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        
        switch (scelta) {
            case 1:
                inserisciNuovoContatto(rubrica);
                break;
            case 2:
                visualizzaRubrica(rubrica, -1); // Mostra tutti i contatti
                break;
            case 3:
                printf("Inserisci nome, cognome o numero da cercare: ");
                scanf(" %49[^\n]", chiave);
                num_risultati = cercaContatto(rubrica, chiave, risultati, 100);
                
                if (num_risultati > 0) {
                    printf("\nRisultati della ricerca (%d trovati):\n", num_risultati);
                    for (int i = 0; i < num_risultati; i++) {
                        printf("\n[%d] %s %s\n", i + 1, risultati[i]->nome, risultati[i]->cognome);
                        visualizzaContatto(risultati[i]);
                        printf("-----------------------------------------\n");
                    }
                } else {
                    printf("Nessun contatto trovato\n");
                }
                break;
            case 4:
                visualizzaRubrica(rubrica, -1);
                if (rubrica->num_contatti > 0) {
                    int indice;
                    printf("Inserisci il numero del contatto da eliminare: ");
                    scanf("%d", &indice);
                    if (eliminaContatto(rubrica, indice - 1)) {
                        printf("Contatto eliminato con successo\n");
                    }
                }
                break;
            case 5:
                printf("Seleziona criterio di ordinamento:\n");
                printf("1. Ordina per cognome\n");
                printf("2. Ordina per nome\n");
                printf("3. Ordina per categoria\n");
                printf("Scelta: ");
                int criterio;
                scanf("%d", &criterio);
                ordinaRubrica(rubrica, criterio);
                printf("Rubrica ordinata\n");
                break;
            case 6:
                printf("Seleziona categoria da visualizzare:\n");
                printf("0. Famiglia\n");
                printf("1. Amici\n");
                printf("2. Lavoro\n");
                printf("3. Altro\n");
                printf("Scelta: ");
                int cat;
                scanf("%d", &cat);
                if (cat >= 0 && cat <= 3) {
                    visualizzaRubrica(rubrica, cat);
                } else {
                    printf("Categoria non valida\n");
                }
                break;
            case 7:
                if (salvaRubrica(rubrica, nome_file)) {
                    printf("Rubrica salvata con successo\n");
                }
                break;
            case 0:
                printf("Salvataggio della rubrica prima di uscire...\n");
                salvaRubrica(rubrica, nome_file);
                printf("Arrivederci!\n");
                break;
            default:
                printf("Scelta non valida!\n");
        }
    } while (scelta != 0);
    
    // Libera la memoria
    liberaRubrica(rubrica);
    
    return 0;
}
```

## Domande di Autovalutazione

1. Qual è la differenza principale tra strutture e unioni in C?

2. In quali situazioni è preferibile utilizzare un'unione invece di una struttura?

3. Come si può accedere ai membri di una struttura annidata?

4. Quali sono i vantaggi dell'utilizzo dei campi di bit?

5. Come si può passare una struttura a una funzione? Quali sono i diversi metodi e quali sono i loro vantaggi e svantaggi?

6. Cosa succede quando si assegna una struttura a un'altra? I dati vengono copiati o viene creato un riferimento?

7. Come si può allocare dinamicamente memoria per un array di strutture?

8. Quali sono le limitazioni delle enumerazioni in C?

## Sfida Avanzata

Implementa un sistema di gestione per un'agenda elettronica che utilizzi strutture, unioni, enumerazioni e campi di bit. Il sistema dovrebbe permettere di:

- Gestire diversi tipi di eventi (appuntamenti, riunioni, promemoria)
- Impostare priorità e categorie per gli eventi
- Cercare eventi per data, tipo o priorità
- Visualizzare gli eventi in ordine cronologico
- Salvare e caricare l'agenda da un file

Utilizza tecniche avanzate come l'allocazione dinamica della memoria e la gestione dei puntatori a strutture per implementare il sistema in modo efficiente.