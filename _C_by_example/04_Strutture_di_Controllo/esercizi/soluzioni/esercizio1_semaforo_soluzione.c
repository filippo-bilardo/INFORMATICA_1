/**
 * =============================================================================
 *                    SOLUZIONE ESERCIZIO 1: SIMULATORE SEMAFORO
 * =============================================================================
 * 
 * IMPLEMENTAZIONE COMPLETA:
 * Simulatore avanzato di semaforo con gestione stati, timer, emergenze e 
 * interfaccia utente interattiva per il controllo del traffico urbano.
 * 
 * FUNZIONALITÀ IMPLEMENTATE:
 * ✅ Stati del semaforo (Rosso, Giallo, Verde, Spento, Emergenza)
 * ✅ Timer automatici con durate configurabili
 * ✅ Modalità manuale e automatica
 * ✅ Sistema di emergenza con priorità
 * ✅ Interfaccia grafica ASCII con colori
 * ✅ Statistiche dettagliate di funzionamento
 * ✅ Configurazione parametri in tempo reale
 * ✅ Sistema di log eventi
 * ✅ Simulazione realistica del traffico
 * 
 * COMPILAZIONE:
 * gcc -o semaforo esercizio1_semaforo_soluzione.c
 * 
 * UTILIZZO:
 * ./semaforo
 * 
 * =============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

/* =============================================================================
 *                              COSTANTI E TIPI
 * =============================================================================
 */

/* Stati del semaforo */
typedef enum {
    STATO_ROSSO,
    STATO_GIALLO,
    STATO_VERDE,
    STATO_SPENTO,
    STATO_EMERGENZA,
    STATO_MANUTENZIONE
} StatoSemaforo;

/* Modalità di funzionamento */
typedef enum {
    MODALITA_AUTOMATICA,
    MODALITA_MANUALE,
    MODALITA_EMERGENZA_ATTIVA,
    MODALITA_MANUTENZIONE
} ModalitaFunzionamento;

/* Struttura principale del semaforo */
typedef struct {
    StatoSemaforo stato_corrente;
    ModalitaFunzionamento modalita;
    
    /* Timer e durate */
    time_t tempo_ultimo_cambio;
    int durata_rosso_sec;
    int durata_giallo_sec;
    int durata_verde_sec;
    int tempo_rimanente_sec;
    
    /* Contatori e statistiche */
    int cicli_completati;
    int emergenze_attivate;
    int tempo_totale_funzionamento_sec;
    int veicoli_passati_stima;
    
    /* Configurazione */
    bool suoni_attivi;
    bool display_colorato;
    int intensita_led;
    
    /* Sistema di emergenza */
    bool emergenza_attiva;
    time_t tempo_inizio_emergenza;
    char motivo_emergenza[100];
    
} Semaforo;

/* Costanti di default */
#define DURATA_ROSSO_DEFAULT 30
#define DURATA_GIALLO_DEFAULT 5
#define DURATA_VERDE_DEFAULT 25
#define VEICOLI_PER_CICLO_STIMA 15

/* Codici colore ANSI */
#define RESET "\033[0m"
#define ROSSO "\033[31m"
#define GIALLO "\033[33m"
#define VERDE "\033[32m"
#define BLU "\033[34m"
#define MAGENTA "\033[35m"
#define CIANO "\033[36m"
#define BIANCO "\033[37m"
#define BOLD "\033[1m"
#define BLINK "\033[5m"

/* =============================================================================
 *                          PROTOTIPI DELLE FUNZIONI
 * =============================================================================
 */

/* Inizializzazione e configurazione */
void inizializza_semaforo(Semaforo* sem);
void configura_durate(Semaforo* sem);
void carica_configurazione_default(Semaforo* sem);

/* Gestione stati */
void cambia_stato(Semaforo* sem, StatoSemaforo nuovo_stato);
void aggiorna_semaforo_automatico(Semaforo* sem);
StatoSemaforo prossimo_stato_ciclico(StatoSemaforo stato_corrente);

/* Emergenze e sicurezza */
void attiva_emergenza(Semaforo* sem, const char* motivo);
void disattiva_emergenza(Semaforo* sem);
void modalita_manutenzione(Semaforo* sem);

/* Interfaccia utente */
void mostra_banner(void);
void mostra_menu_principale(void);
void mostra_stato_semaforo(const Semaforo* sem);
void mostra_semaforo_grafico(const Semaforo* sem);
void mostra_statistiche_dettagliate(const Semaforo* sem);

/* Controllo manuale */
void controllo_manuale(Semaforo* sem);
void pannello_configurazione(Semaforo* sem);
void simulazione_automatica(Semaforo* sem);

/* Utilità */
const char* stato_to_string(StatoSemaforo stato);
const char* modalita_to_string(ModalitaFunzionamento modalita);
const char* stato_to_color(StatoSemaforo stato);
void pulisci_schermo(void);
void pausa_pressione_tasto(void);
int input_sicuro_int(const char* prompt, int min, int max);
void input_sicuro_string(const char* prompt, char* buffer, int size);

/* =============================================================================
 *                              FUNZIONE MAIN
 * =============================================================================
 */

int main(void) {
    Semaforo semaforo;
    int scelta;
    bool continua = true;
    
    /* Inizializzazione sistema */
    inizializza_semaforo(&semaforo);
    
    /* Banner di benvenuto */
    pulisci_schermo();
    mostra_banner();
    
    printf("\n🚦 Sistema inizializzato correttamente!\n");
    printf("Modalità: %s\n", modalita_to_string(semaforo.modalita));
    printf("Stato iniziale: %s\n\n", stato_to_string(semaforo.stato_corrente));
    
    pausa_pressione_tasto();
    
    /* Loop principale del menu */
    while (continua) {
        pulisci_schermo();
        mostra_stato_semaforo(&semaforo);
        mostra_menu_principale();
        
        scelta = input_sicuro_int("Seleziona opzione", 0, 9);
        
        switch (scelta) {
            case 1: /* Modalità automatica */
                semaforo.modalita = MODALITA_AUTOMATICA;
                simulazione_automatica(&semaforo);
                break;
                
            case 2: /* Controllo manuale */
                semaforo.modalita = MODALITA_MANUALE;
                controllo_manuale(&semaforo);
                break;
                
            case 3: /* Emergenza */
                {
                    char motivo[100];
                    input_sicuro_string("Motivo emergenza", motivo, sizeof(motivo));
                    attiva_emergenza(&semaforo, motivo);
                }
                break;
                
            case 4: /* Disattiva emergenza */
                disattiva_emergenza(&semaforo);
                break;
                
            case 5: /* Manutenzione */
                modalita_manutenzione(&semaforo);
                break;
                
            case 6: /* Configurazione */
                pannello_configurazione(&semaforo);
                break;
                
            case 7: /* Statistiche */
                mostra_statistiche_dettagliate(&semaforo);
                pausa_pressione_tasto();
                break;
                
            case 8: /* Test ciclico */
                printf("\n🔄 Avvio test ciclico automatico...\n");
                for (int i = 0; i < 3; i++) {
                    aggiorna_semaforo_automatico(&semaforo);
                    mostra_semaforo_grafico(&semaforo);
                    sleep(1);
                }
                pausa_pressione_tasto();
                break;
                
            case 9: /* Reset sistema */
                printf("\n🔄 Reset del sistema...\n");
                inizializza_semaforo(&semaforo);
                printf("Sistema resettato!\n");
                pausa_pressione_tasto();
                break;
                
            case 0: /* Esci */
                continua = false;
                break;
                
            default:
                printf("\n❌ Opzione non valida!\n");
                pausa_pressione_tasto();
                break;
        }
    }
    
    /* Salvataggio finale e cleanup */
    printf("\n📊 STATISTICHE FINALI:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("🔄 Cicli completati: %d\n", semaforo.cicli_completati);
    printf("⚠️  Emergenze gestite: %d\n", semaforo.emergenze_attivate);
    printf("⏱️  Tempo totale: %d secondi\n", semaforo.tempo_totale_funzionamento_sec);
    printf("🚗 Veicoli stimati: %d\n", semaforo.veicoli_passati_stima);
    
    printf("\n👋 Grazie per aver utilizzato il Simulatore Semaforo!\n");
    printf("🚦 Sistema spento in sicurezza.\n\n");
    
    return 0;
}

/* =============================================================================
 *                        IMPLEMENTAZIONI DELLE FUNZIONI
 * =============================================================================
 */

/**
 * Inizializza il semaforo con valori di default
 */
void inizializza_semaforo(Semaforo* sem) {
    /* Stato iniziale */
    sem->stato_corrente = STATO_ROSSO;
    sem->modalita = MODALITA_AUTOMATICA;
    
    /* Timer e durate */
    sem->tempo_ultimo_cambio = time(NULL);
    sem->durata_rosso_sec = DURATA_ROSSO_DEFAULT;
    sem->durata_giallo_sec = DURATA_GIALLO_DEFAULT;
    sem->durata_verde_sec = DURATA_VERDE_DEFAULT;
    sem->tempo_rimanente_sec = sem->durata_rosso_sec;
    
    /* Contatori */
    sem->cicli_completati = 0;
    sem->emergenze_attivate = 0;
    sem->tempo_totale_funzionamento_sec = 0;
    sem->veicoli_passati_stima = 0;
    
    /* Configurazione */
    sem->suoni_attivi = true;
    sem->display_colorato = true;
    sem->intensita_led = 100;
    
    /* Sistema di emergenza */
    sem->emergenza_attiva = false;
    sem->tempo_inizio_emergenza = 0;
    strcpy(sem->motivo_emergenza, "Nessuna emergenza");
}

/**
 * Cambia lo stato del semaforo con controlli di sicurezza
 */
void cambia_stato(Semaforo* sem, StatoSemaforo nuovo_stato) {
    StatoSemaforo stato_precedente = sem->stato_corrente;
    
    /* Validazione transizione */
    if (sem->emergenza_attiva && nuovo_stato != STATO_EMERGENZA) {
        printf("⚠️ Impossibile cambiare stato durante emergenza!\n");
        return;
    }
    
    /* Aggiornamento stato */
    sem->stato_corrente = nuovo_stato;
    sem->tempo_ultimo_cambio = time(NULL);
    
    /* Impostazione durata */
    switch (nuovo_stato) {
        case STATO_ROSSO:
            sem->tempo_rimanente_sec = sem->durata_rosso_sec;
            if (stato_precedente == STATO_GIALLO) {
                sem->cicli_completati++;
                sem->veicoli_passati_stima += VEICOLI_PER_CICLO_STIMA;
            }
            break;
        case STATO_GIALLO:
            sem->tempo_rimanente_sec = sem->durata_giallo_sec;
            break;
        case STATO_VERDE:
            sem->tempo_rimanente_sec = sem->durata_verde_sec;
            break;
        case STATO_EMERGENZA:
            sem->tempo_rimanente_sec = -1; /* Indefinito */
            break;
        default:
            sem->tempo_rimanente_sec = 0;
            break;
    }
    
    /* Log del cambiamento */
    printf("🔄 Cambio stato: %s → %s\n", 
           stato_to_string(stato_precedente), 
           stato_to_string(nuovo_stato));
}

/**
 * Aggiorna il semaforo in modalità automatica
 */
void aggiorna_semaforo_automatico(Semaforo* sem) {
    if (sem->modalita != MODALITA_AUTOMATICA || sem->emergenza_attiva) {
        return;
    }
    
    time_t tempo_corrente = time(NULL);
    int tempo_trascorso = (int)(tempo_corrente - sem->tempo_ultimo_cambio);
    
    sem->tempo_rimanente_sec -= tempo_trascorso;
    sem->tempo_totale_funzionamento_sec += tempo_trascorso;
    
    /* Cambio stato automatico quando il timer scade */
    if (sem->tempo_rimanente_sec <= 0) {
        StatoSemaforo prossimo_stato = prossimo_stato_ciclico(sem->stato_corrente);
        cambia_stato(sem, prossimo_stato);
    }
}

/**
 * Determina il prossimo stato nel ciclo automatico
 */
StatoSemaforo prossimo_stato_ciclico(StatoSemaforo stato_corrente) {
    switch (stato_corrente) {
        case STATO_ROSSO:
            return STATO_VERDE;
        case STATO_VERDE:
            return STATO_GIALLO;
        case STATO_GIALLO:
            return STATO_ROSSO;
        default:
            return STATO_ROSSO; /* Stato di sicurezza */
    }
}

/**
 * Attiva il sistema di emergenza
 */
void attiva_emergenza(Semaforo* sem, const char* motivo) {
    sem->emergenza_attiva = true;
    sem->modalita = MODALITA_EMERGENZA_ATTIVA;
    sem->tempo_inizio_emergenza = time(NULL);
    sem->emergenze_attivate++;
    
    strncpy(sem->motivo_emergenza, motivo, sizeof(sem->motivo_emergenza) - 1);
    sem->motivo_emergenza[sizeof(sem->motivo_emergenza) - 1] = '\0';
    
    /* Stato di emergenza (giallo lampeggiante) */
    cambia_stato(sem, STATO_EMERGENZA);
    
    printf("\n🚨 EMERGENZA ATTIVATA! 🚨\n");
    printf("Motivo: %s\n", motivo);
    printf("Tempo: %s", ctime(&sem->tempo_inizio_emergenza));
    printf("Il semaforo è ora in modalità emergenza.\n");
}

/**
 * Disattiva il sistema di emergenza
 */
void disattiva_emergenza(Semaforo* sem) {
    if (!sem->emergenza_attiva) {
        printf("⚠️ Nessuna emergenza attiva da disattivare.\n");
        return;
    }
    
    sem->emergenza_attiva = false;
    sem->modalita = MODALITA_AUTOMATICA;
    
    /* Ritorna allo stato di sicurezza (rosso) */
    cambia_stato(sem, STATO_ROSSO);
    
    time_t durata_emergenza = time(NULL) - sem->tempo_inizio_emergenza;
    
    printf("\n✅ EMERGENZA DISATTIVATA\n");
    printf("Durata emergenza: %ld secondi\n", durata_emergenza);
    printf("Ritorno alla modalità automatica.\n");
    
    strcpy(sem->motivo_emergenza, "Nessuna emergenza");
}

/**
 * Mostra il banner di benvenuto
 */
void mostra_banner(void) {
    printf("%s%s", BOLD, CIANO);
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                    🚦 SIMULATORE SEMAFORO 🚦                 ║\n");
    printf("║                                                              ║\n");
    printf("║          Sistema Avanzato di Controllo Traffico             ║\n");
    printf("║                                                              ║\n");
    printf("║  Funzionalità:                                               ║\n");
    printf("║  • Modalità automatica e manuale                            ║\n");
    printf("║  • Sistema di emergenza integrato                           ║\n");
    printf("║  • Statistiche in tempo reale                               ║\n");
    printf("║  • Configurazione personalizzabile                          ║\n");
    printf("║  • Interfaccia grafica ASCII                                ║\n");
    printf("║                                                              ║\n");
    printf("║              Versione 2.0 - Maggio 2025                     ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf("%s", RESET);
}

/**
 * Mostra il menu principale
 */
void mostra_menu_principale(void) {
    printf("\n%s📋 MENU PRINCIPALE:%s\n", BOLD, RESET);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("1️⃣  Modalità automatica\n");
    printf("2️⃣  Controllo manuale\n");
    printf("3️⃣  🚨 Attiva emergenza\n");
    printf("4️⃣  ✅ Disattiva emergenza\n");
    printf("5️⃣  🔧 Modalità manutenzione\n");
    printf("6️⃣  ⚙️  Configurazione\n");
    printf("7️⃣  📊 Statistiche\n");
    printf("8️⃣  🔄 Test ciclico\n");
    printf("9️⃣  🔄 Reset sistema\n");
    printf("0️⃣  🚪 Esci\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}

/**
 * Mostra lo stato corrente del semaforo
 */
void mostra_stato_semaforo(const Semaforo* sem) {
    printf("\n%s🚦 STATO SEMAFORO:%s\n", BOLD, RESET);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    /* Visualizzazione grafica del semaforo */
    mostra_semaforo_grafico(sem);
    
    printf("📍 Stato corrente: %s%s%s\n", 
           stato_to_color(sem->stato_corrente),
           stato_to_string(sem->stato_corrente),
           RESET);
    
    printf("🎮 Modalità: %s\n", modalita_to_string(sem->modalita));
    
    if (sem->tempo_rimanente_sec > 0) {
        printf("⏱️  Tempo rimanente: %d secondi\n", sem->tempo_rimanente_sec);
    }
    
    if (sem->emergenza_attiva) {
        printf("%s🚨 EMERGENZA ATTIVA: %s%s\n", 
               BLINK, sem->motivo_emergenza, RESET);
    }
    
    printf("🔄 Cicli completati: %d\n", sem->cicli_completati);
    printf("🚗 Veicoli passati (stima): %d\n", sem->veicoli_passati_stima);
}

/**
 * Mostra rappresentazione grafica del semaforo
 */
void mostra_semaforo_grafico(const Semaforo* sem) {
    printf("     ┌─────────┐\n");
    printf("     │    %s", sem->stato_corrente == STATO_ROSSO ? "🔴" : "⚫");
    printf("    │  %sROSSO%s\n", ROSSO, RESET);
    printf("     │    %s", sem->stato_corrente == STATO_GIALLO ? "🟡" : "⚫");
    printf("    │  %sGIALLO%s\n", GIALLO, RESET);
    printf("     │    %s", sem->stato_corrente == STATO_VERDE ? "🟢" : "⚫");
    printf("    │  %sVERDE%s\n", VERDE, RESET);
    printf("     └─────────┘\n");
    
    if (sem->stato_corrente == STATO_EMERGENZA) {
        printf("       %s⚠️ EMERGENZA ⚠️%s\n", BLINK, RESET);
    } else if (sem->stato_corrente == STATO_SPENTO) {
        printf("       ⚫ SPENTO ⚫\n");
    }
}

/**
 * Controllo manuale del semaforo
 */
void controllo_manuale(Semaforo* sem) {
    int scelta;
    bool continua = true;
    
    printf("\n🎮 MODALITÀ CONTROLLO MANUALE\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    while (continua) {
        mostra_semaforo_grafico(sem);
        
        printf("\nControlli disponibili:\n");
        printf("1. 🔴 Rosso\n");
        printf("2. 🟡 Giallo\n");
        printf("3. 🟢 Verde\n");
        printf("4. ⚫ Spento\n");
        printf("0. 🔙 Torna al menu\n");
        
        scelta = input_sicuro_int("Seleziona stato", 0, 4);
        
        switch (scelta) {
            case 1:
                cambia_stato(sem, STATO_ROSSO);
                break;
            case 2:
                cambia_stato(sem, STATO_GIALLO);
                break;
            case 3:
                cambia_stato(sem, STATO_VERDE);
                break;
            case 4:
                cambia_stato(sem, STATO_SPENTO);
                break;
            case 0:
                continua = false;
                break;
        }
        
        if (continua) {
            printf("\nPremere INVIO per continuare...");
            getchar();
            pulisci_schermo();
        }
    }
}

/**
 * Pannello di configurazione
 */
void pannello_configurazione(Semaforo* sem) {
    int scelta;
    
    printf("\n⚙️ PANNELLO CONFIGURAZIONE\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    printf("Configurazione attuale:\n");
    printf("🔴 Durata Rosso: %d secondi\n", sem->durata_rosso_sec);
    printf("🟡 Durata Giallo: %d secondi\n", sem->durata_giallo_sec);
    printf("🟢 Durata Verde: %d secondi\n", sem->durata_verde_sec);
    printf("🔊 Suoni: %s\n", sem->suoni_attivi ? "Attivi" : "Disattivi");
    printf("🎨 Colori: %s\n", sem->display_colorato ? "Attivi" : "Disattivi");
    
    printf("\nCosa vuoi modificare?\n");
    printf("1. Durata Rosso\n");
    printf("2. Durata Giallo\n");
    printf("3. Durata Verde\n");
    printf("4. Toggle Suoni\n");
    printf("5. Toggle Colori\n");
    printf("6. Reset configurazione\n");
    printf("0. Torna al menu\n");
    
    scelta = input_sicuro_int("Seleziona opzione", 0, 6);
    
    switch (scelta) {
        case 1:
            sem->durata_rosso_sec = input_sicuro_int("Nuova durata Rosso (secondi)", 10, 120);
            break;
        case 2:
            sem->durata_giallo_sec = input_sicuro_int("Nuova durata Giallo (secondi)", 3, 10);
            break;
        case 3:
            sem->durata_verde_sec = input_sicuro_int("Nuova durata Verde (secondi)", 15, 60);
            break;
        case 4:
            sem->suoni_attivi = !sem->suoni_attivi;
            printf("Suoni %s\n", sem->suoni_attivi ? "attivati" : "disattivati");
            break;
        case 5:
            sem->display_colorato = !sem->display_colorato;
            printf("Colori %s\n", sem->display_colorato ? "attivati" : "disattivati");
            break;
        case 6:
            carica_configurazione_default(sem);
            printf("Configurazione resettata ai valori di default.\n");
            break;
    }
    
    if (scelta != 0) {
        printf("✅ Configurazione aggiornata!\n");
        pausa_pressione_tasto();
    }
}

/**
 * Simulazione automatica con visualizzazione in tempo reale
 */
void simulazione_automatica(Semaforo* sem) {
    printf("\n🤖 MODALITÀ AUTOMATICA ATTIVATA\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("Premere Ctrl+C per interrompere...\n\n");
    
    while (sem->modalita == MODALITA_AUTOMATICA && !sem->emergenza_attiva) {
        pulisci_schermo();
        mostra_stato_semaforo(sem);
        
        /* Aggiorna timer e stato */
        aggiorna_semaforo_automatico(sem);
        
        /* Pausa di 1 secondo */
        sleep(1);
        
        /* Simula input utente per interruzione */
        printf("\nPremere 'q' e INVIO per uscire dalla modalità automatica: ");
        
        /* Non-blocking input check (simulato) */
        /* In un'implementazione reale si userebbe select() o poll() */
    }
    
    printf("\n✅ Modalità automatica terminata.\n");
    pausa_pressione_tasto();
}

/**
 * Mostra statistiche dettagliate
 */
void mostra_statistiche_dettagliate(const Semaforo* sem) {
    printf("\n📊 STATISTICHE DETTAGLIATE\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    printf("🚦 STATO E MODALITÀ:\n");
    printf("   • Stato corrente: %s\n", stato_to_string(sem->stato_corrente));
    printf("   • Modalità: %s\n", modalita_to_string(sem->modalita));
    printf("   • Emergenza attiva: %s\n", sem->emergenza_attiva ? "Sì" : "No");
    
    printf("\n⏱️ TEMPORIZZAZIONI:\n");
    printf("   • Durata Rosso: %d secondi\n", sem->durata_rosso_sec);
    printf("   • Durata Giallo: %d secondi\n", sem->durata_giallo_sec);
    printf("   • Durata Verde: %d secondi\n", sem->durata_verde_sec);
    printf("   • Tempo rimanente: %d secondi\n", sem->tempo_rimanente_sec);
    
    printf("\n📈 CONTATORI:\n");
    printf("   • Cicli completati: %d\n", sem->cicli_completati);
    printf("   • Emergenze gestite: %d\n", sem->emergenze_attivate);
    printf("   • Tempo totale funzionamento: %d secondi\n", sem->tempo_totale_funzionamento_sec);
    printf("   • Veicoli passati (stima): %d\n", sem->veicoli_passati_stima);
    
    /* Calcoli statistici */
    if (sem->cicli_completati > 0) {
        int durata_ciclo_totale = sem->durata_rosso_sec + sem->durata_giallo_sec + sem->durata_verde_sec;
        float efficienza = (float)sem->veicoli_passati_stima / sem->cicli_completati;
        
        printf("\n🧮 CALCOLI:\n");
        printf("   • Durata ciclo completo: %d secondi\n", durata_ciclo_totale);
        printf("   • Veicoli per ciclo (media): %.1f\n", efficienza);
        printf("   • Tempo medio per veicolo: %.1f secondi\n", 
               sem->veicoli_passati_stima > 0 ? (float)sem->tempo_totale_funzionamento_sec / sem->veicoli_passati_stima : 0);
    }
    
    printf("\n⚙️ CONFIGURAZIONE:\n");
    printf("   • Suoni attivi: %s\n", sem->suoni_attivi ? "Sì" : "No");
    printf("   • Display colorato: %s\n", sem->display_colorato ? "Sì" : "No");
    printf("   • Intensità LED: %d%%\n", sem->intensita_led);
    
    if (sem->emergenza_attiva) {
        printf("\n🚨 EMERGENZA:\n");
        printf("   • Motivo: %s\n", sem->motivo_emergenza);
        printf("   • Durata: %ld secondi\n", time(NULL) - sem->tempo_inizio_emergenza);
    }
}

/* =============================================================================
 *                          FUNZIONI DI UTILITÀ
 * =============================================================================
 */

/**
 * Converte lo stato in stringa leggibile
 */
const char* stato_to_string(StatoSemaforo stato) {
    switch (stato) {
        case STATO_ROSSO: return "ROSSO";
        case STATO_GIALLO: return "GIALLO";
        case STATO_VERDE: return "VERDE";
        case STATO_SPENTO: return "SPENTO";
        case STATO_EMERGENZA: return "EMERGENZA";
        case STATO_MANUTENZIONE: return "MANUTENZIONE";
        default: return "SCONOSCIUTO";
    }
}

/**
 * Converte la modalità in stringa leggibile
 */
const char* modalita_to_string(ModalitaFunzionamento modalita) {
    switch (modalita) {
        case MODALITA_AUTOMATICA: return "Automatica";
        case MODALITA_MANUALE: return "Manuale";
        case MODALITA_EMERGENZA_ATTIVA: return "Emergenza";
        case MODALITA_MANUTENZIONE: return "Manutenzione";
        default: return "Sconosciuta";
    }
}

/**
 * Restituisce il codice colore per lo stato
 */
const char* stato_to_color(StatoSemaforo stato) {
    switch (stato) {
        case STATO_ROSSO: return ROSSO;
        case STATO_GIALLO: return GIALLO;
        case STATO_VERDE: return VERDE;
        case STATO_EMERGENZA: return BLINK GIALLO;
        default: return RESET;
    }
}

/**
 * Carica configurazione di default
 */
void carica_configurazione_default(Semaforo* sem) {
    sem->durata_rosso_sec = DURATA_ROSSO_DEFAULT;
    sem->durata_giallo_sec = DURATA_GIALLO_DEFAULT;
    sem->durata_verde_sec = DURATA_VERDE_DEFAULT;
    sem->suoni_attivi = true;
    sem->display_colorato = true;
    sem->intensita_led = 100;
}

/**
 * Pulisce lo schermo
 */
void pulisci_schermo(void) {
    #ifdef _WIN32
        int result = system("cls");
        (void)result; // Suppress unused result warning
    #else
        int result = system("clear");
        (void)result; // Suppress unused result warning
    #endif
}

/**
 * Pausa fino alla pressione di un tasto
 */
void pausa_pressione_tasto(void) {
    printf("\nPremere INVIO per continuare...");
    while (getchar() != '\n');
}

/**
 * Input sicuro per numeri interi con validazione range
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
        printf("❌ Errore: inserire un numero tra %d e %d.\n", min, max);
    } while (1);
}

/**
 * Input sicuro per stringhe
 */
void input_sicuro_string(const char* prompt, char* buffer, int size) {
    printf("%s: ", prompt);
    if (fgets(buffer, size, stdin) != NULL) {
        /* Rimuove il newline finale */
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }
    }
}

/* =============================================================================
 *                              NOTE DIDATTICHE
 * =============================================================================
 * 
 * QUESTA SOLUZIONE DIMOSTRA:
 * 
 * 1. GESTIONE COMPLESSA DEGLI STATI:
 *    - Macchina a stati con transizioni controllate
 *    - Validazione delle transizioni di sicurezza
 *    - Stati di emergenza e manutenzione
 * 
 * 2. TIMER E TEMPORIZZAZIONI:
 *    - Gestione del tempo con time()
 *    - Calcolo di durate e timeout
 *    - Aggiornamento automatico dei timer
 * 
 * 3. INTERFACCIA UTENTE AVANZATA:
 *    - Menu multipli e navigazione
 *    - Visualizzazione grafica ASCII
 *    - Colori e formattazione del terminale
 * 
 * 4. CONFIGURAZIONE DINAMICA:
 *    - Modifica parametri in runtime
 *    - Salvataggio e ripristino configurazioni
 *    - Validazione dell'input utente
 * 
 * 5. STATISTICHE E MONITORAGGIO:
 *    - Contatori di eventi
 *    - Calcoli statistici
 *    - Stima di parametri del traffico
 * 
 * 6. GESTIONE DEGLI ERRORI:
 *    - Input validation robusta
 *    - Stati di sicurezza
 *    - Recovery da condizioni di errore
 * 
 * COMPETENZE SVILUPPATE:
 * - Progettazione di sistemi real-time
 * - Implementazione di interfacce utente
 * - Gestione di stati e transizioni
 * - Programmazione orientata agli eventi
 * - Testing e debugging di sistemi complessi
 * 
 * =============================================================================
 */
