/**
 * =============================================================================
 *                         ESERCIZIO 3: SIMULATORE ASCENSORE
 * =============================================================================
 * 
 * DESCRIZIONE:
 * Implementa un simulatore di ascensore avanzato per un edificio di 10 piani.
 * Il sistema deve gestire chiamate, movimenti, stati di emergenza e statistiche.
 * 
 * OBIETTIVI DIDATTICI:
 * - Implementazione di macchine a stati complesse
 * - Gestione avanzata di loop annidati e switch-case
 * - Simulazione di sistemi real-time con timer
 * - Gestione di code e priorità
 * - Validazione complessa dell'input
 * 
 * FUNZIONALITÀ RICHIESTE:
 * 
 * 1. SISTEMA DI CHIAMATE:
 *    - Chiamate interne (da dentro l'ascensore)
 *    - Chiamate esterne (dai piani) con direzione (su/giù)
 *    - Coda di chiamate con algoritmo di ottimizzazione
 *    - Gestione delle priorità (emergenza > normale)
 * 
 * 2. STATI DELL'ASCENSORE:
 *    - FERMO: ascensore in attesa
 *    - SALENDO: movimento verso l'alto
 *    - SCENDENDO: movimento verso il basso
 *    - MANUTENZIONE: fuori servizio
 *    - EMERGENZA: stato di allarme
 * 
 * 3. SISTEMA DI MOVIMENTO:
 *    - Velocità variabile (lenta/normale/veloce)
 *    - Tempo di apertura/chiusura porte (3 secondi)
 *    - Tempo di fermata per piano (2 secondi)
 *    - Algoritmo di ottimizzazione percorso
 * 
 * 4. FUNZIONI DI SICUREZZA:
 *    - Peso massimo (8 persone = 800kg)
 *    - Sensore di ostruzione porte
 *    - Pulsante di emergenza
 *    - Sistema di allarme
 * 
 * 5. INTERFACCIA UTENTE:
 *    - Menu principale con opzioni chiare
 *    - Visualizzazione stato ascensore in tempo reale
 *    - Pannello di controllo amministratore
 *    - Log delle operazioni
 * 
 * 6. STATISTICHE E MONITORAGGIO:
 *    - Numero di viaggi effettuati
 *    - Piano più visitato
 *    - Tempo totale di funzionamento
 *    - Efficienza energetica
 * 
 * SPECIFICHE TECNICHE:
 * - Piano terra = 0, piani superiori 1-9
 * - Tempo di movimento tra piani: 3 secondi
 * - Capacità massima: 8 persone (100kg/persona)
 * - Modalità eco: riduce velocità del 30%
 * - Modalità express: salta piani intermedi quando possibile
 * 
 * VALIDAZIONE INPUT:
 * - Controllo range piani (0-9)
 * - Validazione peso passeggeri
 * - Controllo stato ascensore prima delle operazioni
 * - Gestione errori di input non numerici
 * 
 * ALGORITMO DI OTTIMIZZAZIONE:
 * - Servire prima le chiamate nella direzione corrente
 * - Minimizzare i cambi di direzione
 * - Priorità alle chiamate di emergenza
 * - Gestione intelligente delle code
 * 
 * ESTENSIONI OPZIONALI:
 * - Simulazione di più ascensori
 * - Sistema di prenotazione chiamate
 * - Interfaccia grafica ASCII
 * - Salvataggio statistiche su file
 * - Modalità debug con trace completo
 * 
 * =============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

/* =============================================================================
 *                              COSTANTI GLOBALI
 * =============================================================================
 */

#define PIANI_TOTALI 10
#define PESO_MAX_KG 800
#define PESO_PERSONA_KG 100
#define PERSONE_MAX 8
#define TEMPO_MOVIMENTO_SEC 3
#define TEMPO_PORTE_SEC 3
#define TEMPO_FERMATA_SEC 2

/* Stati dell'ascensore */
typedef enum {
    STATO_FERMO,
    STATO_SALENDO,
    STATO_SCENDENDO,
    STATO_MANUTENZIONE,
    STATO_EMERGENZA
} StatoAscensore;

/* Direzioni di movimento */
typedef enum {
    DIREZIONE_SU,
    DIREZIONE_GIU,
    DIREZIONE_FERMA
} Direzione;

/* Tipi di chiamata */
typedef enum {
    CHIAMATA_INTERNA,
    CHIAMATA_ESTERNA_SU,
    CHIAMATA_ESTERNA_GIU,
    CHIAMATA_EMERGENZA
} TipoChiamata;

/* Modalità di funzionamento */
typedef enum {
    MODALITA_NORMALE,
    MODALITA_ECO,
    MODALITA_EXPRESS,
    MODALITA_MANUTENZIONE
} ModalitaFunzionamento;

/* Struttura per le chiamate */
typedef struct {
    int piano;
    TipoChiamata tipo;
    time_t timestamp;
    bool attiva;
} Chiamata;

/* Struttura principale dell'ascensore */
typedef struct {
    int piano_corrente;
    StatoAscensore stato;
    Direzione direzione;
    ModalitaFunzionamento modalita;
    int peso_corrente_kg;
    int numero_passeggeri;
    bool porte_aperte;
    bool sensore_ostruzione;
    bool emergenza_attiva;
    
    /* Coda delle chiamate */
    Chiamata chiamate[PIANI_TOTALI * 3]; /* Massimo 3 chiamate per piano */
    int numero_chiamate;
    
    /* Statistiche */
    int viaggi_totali;
    int piani_visitati[PIANI_TOTALI];
    time_t tempo_funzionamento;
    int emergenze_totali;
    double energia_consumata_kwh;
    
} Ascensore;

/* =============================================================================
 *                          PROTOTIPI DELLE FUNZIONI
 * =============================================================================
 */

/* Inizializzazione e configurazione */
void inizializza_ascensore(Ascensore* asc);
void stampa_banner(void);
void mostra_menu_principale(void);

/* Gestione delle chiamate */
void aggiungi_chiamata(Ascensore* asc, int piano, TipoChiamata tipo);
void rimuovi_chiamata(Ascensore* asc, int piano, TipoChiamata tipo);
bool ha_chiamate_attive(const Ascensore* asc);
int prossima_destinazione(const Ascensore* asc);

/* Movimento e controllo */
void muovi_ascensore(Ascensore* asc);
void apri_porte(Ascensore* asc);
void chiudi_porte(Ascensore* asc);
void cambia_stato(Ascensore* asc, StatoAscensore nuovo_stato);

/* Sicurezza e emergenze */
bool verifica_peso(const Ascensore* asc, int peso_aggiuntivo);
void attiva_emergenza(Ascensore* asc);
void disattiva_emergenza(Ascensore* asc);
bool verifica_sicurezza(const Ascensore* asc);

/* Interfaccia utente */
void mostra_stato_ascensore(const Ascensore* asc);
void mostra_statistiche(const Ascensore* asc);
void pannello_controllo_admin(Ascensore* asc);
void simulazione_tempo_reale(Ascensore* asc);

/* Utilità */
const char* stato_to_string(StatoAscensore stato);
const char* direzione_to_string(Direzione dir);
const char* modalita_to_string(ModalitaFunzionamento mod);
void simula_attesa(int secondi);
int input_sicuro_int(const char* prompt, int min, int max);

/* =============================================================================
 *                              FUNZIONE MAIN
 * =============================================================================
 */

int main(void) {
    /* TODO: Implementare il main del simulatore
     * 
     * STRUTTURA RICHIESTA:
     * 1. Inizializzazione sistema
     * 2. Mostra banner di benvenuto
     * 3. Loop principale del menu
     * 4. Gestione scelte utente
     * 5. Cleanup e salvataggio statistiche finali
     * 
     * MENU PRINCIPALE:
     * 1. Chiama ascensore (esterno)
     * 2. Seleziona piano (interno)
     * 3. Apri/Chiudi porte manualmente
     * 4. Aggiungi/Rimuovi passeggeri
     * 5. Emergenza
     * 6. Modalità manutenzione
     * 7. Cambio modalità funzionamento
     * 8. Visualizza statistiche
     * 9. Simulazione automatica
     * 0. Esci
     * 
     * GESTIONE ERRORI:
     * - Input non validi
     * - Operazioni non permesse nello stato corrente
     * - Sovraccarico peso
     * - Chiamate a piani non esistenti
     */
    
    printf("=== SIMULATORE ASCENSORE ===\n");
    printf("Implementare qui il main completo!\n\n");
    
    printf("Il main deve includere:\n");
    printf("- Inizializzazione ascensore\n");
    printf("- Menu interattivo con tutte le opzioni\n");
    printf("- Gestione completa delle chiamate\n");
    printf("- Sistema di emergenza\n");
    printf("- Simulazione tempo reale\n");
    printf("- Statistiche dettagliate\n");
    
    return 0;
}

/* =============================================================================
 *                        IMPLEMENTAZIONI DELLE FUNZIONI
 * =============================================================================
 */

/**
 * Inizializza l'ascensore con valori di default
 */
void inizializza_ascensore(Ascensore* asc) {
    /* TODO: Implementare inizializzazione completa
     * 
     * INIZIALIZZAZIONE RICHIESTA:
     * - Piano corrente = 0 (piano terra)
     * - Stato = FERMO
     * - Direzione = FERMA
     * - Modalità = NORMALE
     * - Peso e passeggeri = 0
     * - Porte chiuse
     * - Nessuna emergenza
     * - Azzeramento chiamate
     * - Reset statistiche
     * - Timestamp iniziale
     */
    
    printf("TODO: Implementare inizializza_ascensore()\n");
}

/**
 * Aggiunge una chiamata alla coda
 */
void aggiungi_chiamata(Ascensore* asc, int piano, TipoChiamata tipo) {
    /* TODO: Implementare gestione chiamate
     * 
     * LOGICA RICHIESTA:
     * 1. Validare piano (0-9)
     * 2. Controllare se chiamata già esistente
     * 3. Verificare stato ascensore
     * 4. Aggiungere alla coda con timestamp
     * 5. Ordinare per priorità (emergenza > normale)
     * 6. Attivare movimento se necessario
     */
    
    printf("TODO: Implementare aggiungi_chiamata() per piano %d, tipo %d\n", piano, tipo);
}

/**
 * Gestisce il movimento dell'ascensore
 */
void muovi_ascensore(Ascensore* asc) {
    /* TODO: Implementare logica di movimento
     * 
     * ALGORITMO RICHIESTO:
     * 1. Determinare direzione ottimale
     * 2. Verificare sicurezza
     * 3. Chiudere porte se aperte
     * 4. Simulare movimento (3 sec/piano)
     * 5. Aggiornare piano corrente
     * 6. Controllare chiamate per il piano
     * 7. Fermarsi se necessario
     * 8. Aggiornare statistiche
     */
    
    printf("TODO: Implementare muovi_ascensore()\n");
}

/**
 * Mostra lo stato completo dell'ascensore
 */
void mostra_stato_ascensore(const Ascensore* asc) {
    /* TODO: Implementare visualizzazione stato
     * 
     * INFORMAZIONI DA MOSTRARE:
     * - Piano corrente con indicatore grafico
     * - Stato e direzione corrente
     * - Numero passeggeri e peso
     * - Stato porte (aperte/chiuse)
     * - Chiamate attive per piano
     * - Modalità di funzionamento
     * - Eventuali allarmi o emergenze
     * - Prossima destinazione
     */
    
    printf("TODO: Implementare mostra_stato_ascensore()\n");
}

/**
 * Gestisce le emergenze
 */
void attiva_emergenza(Ascensore* asc) {
    /* TODO: Implementare sistema emergenza
     * 
     * AZIONI RICHIESTE:
     * 1. Fermare immediatamente l'ascensore
     * 2. Aprire le porte
     * 3. Cancellare tutte le chiamate normali
     * 4. Attivare allarme
     * 5. Passare a stato EMERGENZA
     * 6. Registrare evento nelle statistiche
     * 7. Notificare centro controllo
     */
    
    printf("TODO: Implementare attiva_emergenza()\n");
}

/**
 * Mostra statistiche dettagliate
 */
void mostra_statistiche(const Ascensore* asc) {
    /* TODO: Implementare visualizzazione statistiche
     * 
     * STATISTICHE DA MOSTRARE:
     * - Viaggi totali effettuati
     * - Piano più visitato
     * - Tempo totale di funzionamento
     * - Emergenze gestite
     * - Energia consumata (stima)
     * - Efficienza media
     * - Distribuzione chiamate per piano
     * - Tempo medio tra chiamate
     */
    
    printf("TODO: Implementare mostra_statistiche()\n");
}

/* =============================================================================
 *                          FUNZIONI DI UTILITÀ
 * =============================================================================
 */

/**
 * Converte lo stato in stringa leggibile
 */
const char* stato_to_string(StatoAscensore stato) {
    switch(stato) {
        case STATO_FERMO: return "FERMO";
        case STATO_SALENDO: return "SALENDO";
        case STATO_SCENDENDO: return "SCENDENDO";
        case STATO_MANUTENZIONE: return "MANUTENZIONE";
        case STATO_EMERGENZA: return "EMERGENZA";
        default: return "SCONOSCIUTO";
    }
}

/**
 * Input sicuro con validazione range
 */
int input_sicuro_int(const char* prompt, int min, int max) {
    int valore;
    char buffer[100];
    
    do {
        printf("%s (range: %d-%d): ", prompt, min, max);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &valore) == 1) {
                if (valore >= min && valore <= max) {
                    return valore;
                }
            }
        }
        printf("Errore: inserire un numero tra %d e %d.\n", min, max);
    } while (1);
}

/* =============================================================================
 *                              NOTE DIDATTICHE
 * =============================================================================
 * 
 * QUESTO ESERCIZIO DIMOSTRA:
 * 
 * 1. MACCHINE A STATI COMPLESSE:
 *    - Gestione di stati multipli con transizioni controllate
 *    - Validazione delle transizioni di stato
 *    - Comportamenti diversi per ogni stato
 * 
 * 2. ALGORITMI DI OTTIMIZZAZIONE:
 *    - Ordinamento e prioritizzazione delle chiamate
 *    - Minimizzazione del tempo di percorrenza
 *    - Gestione efficiente delle risorse
 * 
 * 3. SIMULAZIONE TEMPO REALE:
 *    - Gestione del tempo e dei ritardi
 *    - Sincronizzazione delle operazioni
 *    - Simulazione di processi continui
 * 
 * 4. STRUTTURE DATI AVANZATE:
 *    - Code e liste di chiamate
 *    - Strutture complesse con molti campi
 *    - Gestione della memoria dinamica
 * 
 * 5. INTERFACCE UTENTE COMPLESSE:
 *    - Menu multipli e navigazione
 *    - Visualizzazione di stato in tempo reale
 *    - Gestione di input complessi
 * 
 * 6. GESTIONE DEGLI ERRORI:
 *    - Validazione completa dell'input
 *    - Gestione delle condizioni di errore
 *    - Recovery automatico da errori
 * 
 * COMPETENZE SVILUPPATE:
 * - Progettazione di sistemi complessi
 * - Implementazione di algoritmi efficienti
 * - Gestione di stati e transizioni
 * - Programmazione orientata agli eventi
 * - Debugging di sistemi complessi
 * 
 * =============================================================================
 */
