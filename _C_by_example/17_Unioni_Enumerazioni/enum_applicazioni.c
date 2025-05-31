/**
 * File: enum_applicazioni.c
 * Descrizione: Applicazioni pratiche delle enumerazioni in C
 */

#include <stdio.h>

// Esempio 1: Enumerazione per un menu di opzioni
enum OpzioneMenu {
    ESCI = 0,
    APRI_FILE,
    SALVA_FILE,
    MODIFICA_TESTO,
    CERCA_TESTO,
    SOSTITUISCI_TESTO
};

// Esempio 2: Enumerazione per flags (utilizzando potenze di 2)
enum Permesso {
    NESSUNO     = 0,      // 000
    LETTURA     = 1 << 0,  // 001
    SCRITTURA   = 1 << 1,  // 010
    ESECUZIONE  = 1 << 2   // 100
};

// Esempio 3: Enumerazione per stati di una macchina a stati
enum StatoConnessione {
    DISCONNESSO,
    CONNESSIONE_IN_CORSO,
    CONNESSO,
    DISCONNESSIONE_IN_CORSO,
    ERRORE
};

// Esempio 4: Enumerazione per livelli di log
enum LivelloLog {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

// Funzione per gestire le opzioni del menu
void gestisci_opzione(enum OpzioneMenu opzione) {
    switch (opzione) {
        case ESCI:
            printf("Uscita dal programma...\n");
            break;
        case APRI_FILE:
            printf("Apertura file...\n");
            break;
        case SALVA_FILE:
            printf("Salvataggio file...\n");
            break;
        case MODIFICA_TESTO:
            printf("Modifica testo...\n");
            break;
        case CERCA_TESTO:
            printf("Ricerca testo...\n");
            break;
        case SOSTITUISCI_TESTO:
            printf("Sostituzione testo...\n");
            break;
        default:
            printf("Opzione non valida!\n");
    }
}

// Funzione per verificare i permessi
void verifica_permessi(int permessi) {
    printf("Permessi: ");
    
    if (permessi == NESSUNO) {
        printf("Nessun permesso\n");
        return;
    }
    
    if (permessi & LETTURA) {
        printf("Lettura ");
    }
    
    if (permessi & SCRITTURA) {
        printf("Scrittura ");
    }
    
    if (permessi & ESECUZIONE) {
        printf("Esecuzione");
    }
    
    printf("\n");
}

// Funzione per gestire lo stato della connessione
void gestisci_stato(enum StatoConnessione stato) {
    static enum StatoConnessione stato_precedente = DISCONNESSO;
    
    if (stato != stato_precedente) {
        switch (stato) {
            case DISCONNESSO:
                printf("Stato: Disconnesso\n");
                break;
            case CONNESSIONE_IN_CORSO:
                printf("Stato: Connessione in corso...\n");
                break;
            case CONNESSO:
                printf("Stato: Connesso\n");
                break;
            case DISCONNESSIONE_IN_CORSO:
                printf("Stato: Disconnessione in corso...\n");
                break;
            case ERRORE:
                printf("Stato: Errore di connessione\n");
                break;
        }
        stato_precedente = stato;
    }
}

// Funzione per il logging con filtro di livello
void log_messaggio(enum LivelloLog livello, const char* messaggio) {
    static enum LivelloLog livello_minimo = INFO; // Livello minimo di log da mostrare
    
    if (livello >= livello_minimo) {
        const char* prefisso;
        
        switch (livello) {
            case DEBUG:
                prefisso = "[DEBUG]";
                break;
            case INFO:
                prefisso = "[INFO]";
                break;
            case WARNING:
                prefisso = "[WARNING]";
                break;
            case ERROR:
                prefisso = "[ERROR]";
                break;
            case CRITICAL:
                prefisso = "[CRITICAL]";
                break;
            default:
                prefisso = "[UNKNOWN]";
        }
        
        printf("%s %s\n", prefisso, messaggio);
    }
}

// Esempio 5: Enumerazione per carte da gioco
enum Seme {
    CUORI,
    QUADRI,
    FIORI,
    PICCHE
};

enum Valore {
    ASSO = 1,
    DUE,
    TRE,
    QUATTRO,
    CINQUE,
    SEI,
    SETTE,
    OTTO,
    NOVE,
    DIECI,
    JACK,
    DONNA,
    RE
};

struct Carta {
    enum Seme seme;
    enum Valore valore;
};

// Funzione per stampare una carta
void stampa_carta(struct Carta carta) {
    const char* nome_seme;
    const char* nome_valore;
    
    switch (carta.seme) {
        case CUORI:   nome_seme = "Cuori";   break;
        case QUADRI:  nome_seme = "Quadri";  break;
        case FIORI:   nome_seme = "Fiori";   break;
        case PICCHE:  nome_seme = "Picche";  break;
        default:      nome_seme = "Sconosciuto";
    }
    
    switch (carta.valore) {
        case ASSO:    nome_valore = "Asso";    break;
        case JACK:    nome_valore = "Jack";    break;
        case DONNA:   nome_valore = "Donna";   break;
        case RE:      nome_valore = "Re";      break;
        default:      nome_valore = "";        break;
    }
    
    if (nome_valore[0] == '\0') {
        printf("%d di %s\n", carta.valore, nome_seme);
    } else {
        printf("%s di %s\n", nome_valore, nome_seme);
    }
}

int main() {
    // Esempio 1: Menu di opzioni
    printf("\n=== Esempio 1: Menu di opzioni ===\n");
    
    enum OpzioneMenu scelta = MODIFICA_TESTO;
    gestisci_opzione(scelta);
    
    // Esempio 2: Flags e operazioni bit a bit
    printf("\n=== Esempio 2: Flags e operazioni bit a bit ===\n");
    
    int permessi1 = LETTURA | SCRITTURA;
    int permessi2 = LETTURA | ESECUZIONE;
    int permessi3 = NESSUNO;
    
    verifica_permessi(permessi1);
    verifica_permessi(permessi2);
    verifica_permessi(permessi3);
    
    // Aggiunta di un permesso
    permessi3 |= LETTURA;
    printf("Dopo l'aggiunta del permesso di lettura: ");
    verifica_permessi(permessi3);
    
    // Rimozione di un permesso
    permessi1 &= ~SCRITTURA;
    printf("Dopo la rimozione del permesso di scrittura: ");
    verifica_permessi(permessi1);
    
    // Verifica di un permesso specifico
    if ((permessi2 & SCRITTURA) == 0) {
        printf("Il permesso di scrittura non è presente\n");
    }
    
    // Esempio 3: Macchina a stati
    printf("\n=== Esempio 3: Macchina a stati ===\n");
    
    enum StatoConnessione stato = DISCONNESSO;
    gestisci_stato(stato);
    
    stato = CONNESSIONE_IN_CORSO;
    gestisci_stato(stato);
    
    stato = CONNESSO;
    gestisci_stato(stato);
    
    stato = DISCONNESSIONE_IN_CORSO;
    gestisci_stato(stato);
    
    stato = DISCONNESSO;
    gestisci_stato(stato);
    
    // Esempio 4: Sistema di logging
    printf("\n=== Esempio 4: Sistema di logging ===\n");
    
    log_messaggio(DEBUG, "Questo è un messaggio di debug");
    log_messaggio(INFO, "Questo è un messaggio informativo");
    log_messaggio(WARNING, "Questo è un avviso");
    log_messaggio(ERROR, "Questo è un errore");
    log_messaggio(CRITICAL, "Questo è un errore critico");
    
    // Esempio 5: Carte da gioco
    printf("\n=== Esempio 5: Carte da gioco ===\n");
    
    struct Carta mano[5] = {
        {CUORI, ASSO},
        {QUADRI, DIECI},
        {FIORI, JACK},
        {PICCHE, DONNA},
        {CUORI, RE}
    };
    
    printf("Mano di carte:\n");
    for (int i = 0; i < 5; i++) {
        stampa_carta(mano[i]);
    }
    
    return 0;
}