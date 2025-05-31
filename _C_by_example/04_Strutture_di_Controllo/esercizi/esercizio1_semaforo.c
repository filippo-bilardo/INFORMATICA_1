/*
 * ===============================================
 * ESERCIZIO 1: Simulatore Semaforo Intelligente
 * ===============================================
 * 
 * OBIETTIVO:
 * Creare un simulatore di semaforo che gestisce il traffico
 * in un incrocio utilizzando strutture di controllo e menu
 * interattivi per mostrare stati e transizioni.
 * 
 * REQUISITI:
 * 1. Menu principale con opzioni multiple
 * 2. Simulazione automatica con cicli temporizzati
 * 3. Modalità manuale per controllo step-by-step
 * 4. Gestione stati del semaforo (Verde, Giallo, Rosso)
 * 5. Contatori di traffico e statistiche
 * 6. Modalità emergenza e manutenzione
 * 
 * DIFFICOLTÀ: ⭐⭐⭐ (Intermedio)
 * TEMPO STIMATO: 45-60 minuti
 * 
 * CONCETTI UTILIZZATI:
 * - Switch-case per gestione stati
 * - Cicli while/for per simulazioni
 * - If-else per condizioni logiche
 * - Menu interattivi con validazione
 * - Gestione del tempo e contatori
 * 
 * Autore: Corso C by Example
 * Versione: 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// ===== ENUMERAZIONI E COSTANTI =====
typedef enum {
    VERDE = 0,
    GIALLO = 1,
    ROSSO = 2,
    LAMPEGGIANTE = 3,
    SPENTO = 4
} StatoSemaforo;

typedef enum {
    NORMALE = 0,
    EMERGENZA = 1,
    MANUTENZIONE = 2
} ModalitaFunzionamento;

#define TEMPO_VERDE 10
#define TEMPO_GIALLO 3
#define TEMPO_ROSSO 8
#define MAX_VEICOLI_CODA 50

// ===== STRUTTURE DATI =====
typedef struct {
    StatoSemaforo stato_attuale;
    ModalitaFunzionamento modalita;
    int tempo_rimanente;
    int veicoli_passati;
    int veicoli_in_coda;
    int cicli_completati;
    bool automatico;
    time_t tempo_avvio;
} Semaforo;

// ===== PROTOTIPI FUNZIONI =====
void inizializza_semaforo(Semaforo* s);
void stampa_stato_semaforo(const Semaforo* s);
void aggiorna_semaforo(Semaforo* s);
void prossimo_stato(Semaforo* s);
void simula_traffico(Semaforo* s);

void menu_principale(Semaforo* s);
void modalita_automatica(Semaforo* s);
void modalita_manuale(Semaforo* s);
void mostra_statistiche(const Semaforo* s);
void gestisci_emergenza(Semaforo* s);
void manutenzione_semaforo(Semaforo* s);

const char* nome_stato(StatoSemaforo stato);
const char* colore_stato(StatoSemaforo stato);
int tempo_stato(StatoSemaforo stato);
void stampa_intestazione(void);
void pausa(int secondi);

// ===== IMPLEMENTAZIONE =====

int main() {
    srand(time(NULL));
    
    Semaforo semaforo;
    inizializza_semaforo(&semaforo);
    
    stampa_intestazione();
    printf("🚦 Benvenuto nel Simulatore Semaforo Intelligente!\n\n");
    
    menu_principale(&semaforo);
    
    printf("\n🏁 Simulazione terminata. Statistiche finali:\n");
    mostra_statistiche(&semaforo);
    printf("\n👋 Grazie per aver utilizzato il simulatore!\n");
    
    return 0;
}

/**
 * TODO: Implementa l'inizializzazione del semaforo
 * - Imposta stato iniziale a ROSSO
 * - Modalità NORMALE
 * - Azzera tutti i contatori
 * - Salva tempo di avvio
 */
void inizializza_semaforo(Semaforo* s) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimento: usa time(NULL) per il tempo di avvio
}

/**
 * TODO: Implementa la visualizzazione dello stato
 * Mostra:
 * - Stato attuale con emoji colore
 * - Tempo rimanente se in automatico
 * - Contatori veicoli
 * - Modalità funzionamento
 */
void stampa_stato_semaforo(const Semaforo* s) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Usa 🔴🟡🟢 per i colori
    // - Mostra barra di progresso per tempo rimanente
    // - Usa switch per formattare output in base allo stato
}

/**
 * TODO: Implementa l'aggiornamento automatico
 * - Decrementa tempo rimanente
 * - Cambia stato quando tempo scade
 * - Aggiorna contatori veicoli
 * - Gestisce modalità speciali
 */
void aggiorna_semaforo(Semaforo* s) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Controlla se tempo_rimanente > 0
    // - Usa prossimo_stato() quando tempo scade
    // - Simula traffico con simula_traffico()
}

/**
 * TODO: Implementa la transizione al prossimo stato
 * Sequenza normale: ROSSO -> VERDE -> GIALLO -> ROSSO
 * Gestisci anche modalità speciali
 */
void prossimo_stato(Semaforo* s) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Usa switch per gestire transizioni
    // - Aggiorna tempo_rimanente con tempo_stato()
    // - Incrementa cicli_completati quando torna a ROSSO
}

/**
 * TODO: Implementa la simulazione del traffico
 * - Genera veicoli casuali in base allo stato
 * - Aggiorna contatori di passaggio
 * - Gestisci code di attesa
 */
void simula_traffico(Semaforo* s) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - VERDE: veicoli passano (riduci coda)
    // - ROSSO: veicoli si accodano
    // - Usa rand() per variazione casuale
}

/**
 * TODO: Implementa il menu principale
 * Opzioni:
 * 1. Modalità automatica
 * 2. Modalità manuale
 * 3. Statistiche
 * 4. Emergenza
 * 5. Manutenzione
 * 0. Esci
 */
void menu_principale(Semaforo* s) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Usa ciclo do-while per ripetere menu
    // - Valida input utente
    // - Mostra sempre stato attuale
}

/**
 * TODO: Implementa la modalità automatica
 * - Ciclo continuo con aggiornamenti temporizzati
 * - Mostra stato in tempo reale
 * - Permetti interruzione utente
 */
void modalita_automatica(Semaforo* s) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Usa while loop con controllo interruzione
    // - pausa(1) per simulare passaggio tempo
    // - Stampa stato ogni secondo
}

/**
 * TODO: Implementa la modalità manuale
 * - Avanzamento step-by-step
 * - Controllo utente per ogni transizione
 * - Mostra sempre stato corrente
 */
void modalita_manuale(Semaforo* s) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Menu con opzioni: Prossimo stato, Stato attuale, Esci
    // - Permetti controllo completo all'utente
}

/**
 * TODO: Implementa visualizzazione statistiche
 * Mostra:
 * - Tempo totale funzionamento
 * - Veicoli totali passati
 * - Cicli completati
 * - Efficienza del semaforo
 */
void mostra_statistiche(const Semaforo* s) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Calcola tempo funzionamento: time(NULL) - tempo_avvio
    // - Mostra veicoli per minuto
    // - Calcola percentuale utilizzo
}

/**
 * TODO: Implementa gestione emergenza
 * - Passa tutti i semafori a LAMPEGGIANTE
 * - Mostra istruzioni sicurezza
 * - Permetti ritorno a modalità normale
 */
void gestisci_emergenza(Semaforo* s) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Cambia modalita a EMERGENZA
    // - Stato LAMPEGGIANTE
    // - Mostra messaggi di sicurezza
}

/**
 * TODO: Implementa modalità manutenzione
 * - Spegni semaforo (stato SPENTO)
 * - Mostra avvisi di pericolo
 * - Reset contatori opzionale
 */
void manutenzione_semaforo(Semaforo* s) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Modalità MANUTENZIONE
    // - Opzioni: Spegni, Accendi, Reset, Test
}

// ===== FUNZIONI UTILITY (GIÀ IMPLEMENTATE) =====

const char* nome_stato(StatoSemaforo stato) {
    switch (stato) {
        case VERDE: return "VERDE";
        case GIALLO: return "GIALLO";
        case ROSSO: return "ROSSO";
        case LAMPEGGIANTE: return "LAMPEGGIANTE";
        case SPENTO: return "SPENTO";
        default: return "SCONOSCIUTO";
    }
}

const char* colore_stato(StatoSemaforo stato) {
    switch (stato) {
        case VERDE: return "🟢";
        case GIALLO: return "🟡";
        case ROSSO: return "🔴";
        case LAMPEGGIANTE: return "⚠️";
        case SPENTO: return "⚫";
        default: return "❓";
    }
}

int tempo_stato(StatoSemaforo stato) {
    switch (stato) {
        case VERDE: return TEMPO_VERDE;
        case GIALLO: return TEMPO_GIALLO;
        case ROSSO: return TEMPO_ROSSO;
        default: return 1;
    }
}

void stampa_intestazione(void) {
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║               🚦 SIMULATORE SEMAFORO INTELLIGENTE 🚦          ║\n");
    printf("║                                                              ║\n");
    printf("║  Gestisce il traffico urbano con modalità automatiche       ║\n");
    printf("║  e manuali, emergency override e statistiche dettagliate    ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n\n");
}

void pausa(int secondi) {
    // Simula pausa senza bloccare (in ambiente reale useresti sleep())
    clock_t start = clock();
    while (clock() < start + secondi * CLOCKS_PER_SEC) {
        // Attesa attiva
    }
}

/*
 * ===============================================
 * ISTRUZIONI PER LO STUDENTE:
 * ===============================================
 * 
 * 1. COMPRENSIONE:
 *    - Studia le strutture dati definite
 *    - Comprendi il flusso del programma
 *    - Analizza le funzioni utility già implementate
 * 
 * 2. IMPLEMENTAZIONE:
 *    - Inizia con inizializza_semaforo()
 *    - Procedi con stampa_stato_semaforo()
 *    - Implementa la logica di aggiornamento
 *    - Completa i menu e le modalità
 * 
 * 3. TEST:
 *    - Compila e testa ogni funzione incrementalmente
 *    - Verifica le transizioni di stato
 *    - Controlla i contatori e le statistiche
 * 
 * 4. MIGLIORAMENTI (OPZIONALI):
 *    - Aggiungi suoni per i cambi stato
 *    - Implementa semafori multipli
 *    - Aggiungi sensori di traffico
 *    - Salva statistiche su file
 * 
 * SUGGERIMENTI:
 * - Usa printf per debug durante sviluppo
 * - Testa ogni modalità separatamente
 * - Controlla i edge cases (tempo = 0, overflow contatori)
 * - Rendi l'interfaccia user-friendly con messaggi chiari
 *
 * CRITERI DI VALUTAZIONE:
 * ✅ Funzionalità base (menu, stati, transizioni)
 * ✅ Modalità automatica funzionante
 * ✅ Modalità manuale funzionante  
 * ✅ Statistiche accurate
 * ✅ Gestione errori e edge cases
 * ✅ Interfaccia utente chiara
 * ✅ Codice ben commentato e leggibile
 */
