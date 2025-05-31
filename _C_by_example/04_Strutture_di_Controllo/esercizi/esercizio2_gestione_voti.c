/*
 * ===============================================
 * ESERCIZIO 2: Sistema Gestione Voti Studenti
 * ===============================================
 * 
 * OBIETTIVO:
 * Sviluppare un sistema completo per la gestione dei voti
 * degli studenti utilizzando strutture di controllo avanzate,
 * validazione input e algoritmi di elaborazione dati.
 * 
 * REQUISITI:
 * 1. Gestione database studenti (max 50 studenti)
 * 2. Inserimento voti con validazione rigorosa
 * 3. Calcolo medie, statistiche e classifiche
 * 4. Sistema di ricerca e filtri avanzati
 * 5. Generazione report dettagliati
 * 6. Modalità interattiva con menu completo
 * 
 * DIFFICOLTÀ: ⭐⭐⭐⭐ (Avanzato)
 * TEMPO STIMATO: 60-90 minuti
 * 
 * CONCETTI UTILIZZATI:
 * - Array e gestione indici
 * - Cicli nested per ricerche
 * - Condizioni complesse per filtri
 * - Algoritmi di ordinamento
 * - Validazione input robusta
 * - Menu multi-livello
 * 
 * Autore: Corso C by Example
 * Versione: 1.0
 */w

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

// ===== COSTANTI =====
#define MAX_STUDENTI 50
#define MAX_VOTI_PER_STUDENTE 10
#define MAX_NOME_LENGTH 30
#define MAX_MATERIA_LENGTH 20
#define MIN_VOTO 18
#define MAX_VOTO 30
#define VOTO_LODE 31  // Rappresenta 30 e lode

// ===== STRUTTURE DATI =====
typedef struct {
    char materia[MAX_MATERIA_LENGTH];
    int voto;  // 18-30, o 31 per 30 e lode
    char data[11];  // formato: gg/mm/aaaa
} Esame;

typedef struct {
    char nome[MAX_NOME_LENGTH];
    char cognome[MAX_NOME_LENGTH];
    int matricola;
    int anno_corso;
    Esame esami[MAX_VOTI_PER_STUDENTE];
    int num_esami;
    bool attivo;  // true se studente è ancora iscritto
} Studente;

typedef struct {
    Studente studenti[MAX_STUDENTI];
    int num_studenti;
    int prossima_matricola;
} Database;

// ===== PROTOTIPI FUNZIONI =====
void inizializza_database(Database* db);
void menu_principale(Database* db);

// Gestione studenti
void aggiungi_studente(Database* db);
void rimuovi_studente(Database* db);
void cerca_studente(const Database* db);
void modifica_studente(Database* db);
void lista_studenti(const Database* db);

// Gestione voti
void aggiungi_voto(Database* db);
void modifica_voto(Database* db);
void rimuovi_voto(Database* db);
void visualizza_voti_studente(const Database* db);

// Statistiche e report
void calcola_statistiche_studente(const Database* db);
void calcola_statistiche_generali(const Database* db);
void genera_classifica(const Database* db);
void report_per_materia(const Database* db);
void report_per_anno(const Database* db);

// Ricerca e filtri
void ricerca_avanzata(const Database* db);
void filtra_per_media(const Database* db);
void filtra_per_materia(const Database* db);
void trova_migliori_peggiori(const Database* db);

// Utility e validazione
int trova_studente_per_matricola(const Database* db, int matricola);
int trova_studente_per_nome(const Database* db, const char* nome, const char* cognome);
bool valida_voto(int voto);
bool valida_data(const char* data);
bool valida_matricola(int matricola);
float calcola_media_studente(const Studente* s);
void ordina_studenti_per_media(Database* db);
void stampa_studente_dettagliato(const Studente* s);
void stampa_intestazione_sistema(void);
const char* converti_voto_stringa(int voto);

// Input validazione
int leggi_intero(const char* prompt, int min, int max);
float leggi_float(const char* prompt, float min, float max);
bool leggi_stringa(char* buffer, int max_len, const char* prompt);
bool leggi_data(char* data);

// ===== IMPLEMENTAZIONE =====

int main() {
    Database database;
    inizializza_database(&database);
    
    stampa_intestazione_sistema();
    printf("🎓 Benvenuto nel Sistema di Gestione Voti Studenti!\n\n");
    
    // Carica alcuni dati di esempio per testing
    // (In un sistema reale, caricheresti da file)
    
    menu_principale(&database);
    
    printf("\n📊 Sessione terminata. Statistiche finali del database:\n");
    printf("   • Studenti registrati: %d\n", database.num_studenti);
    printf("   • Prossima matricola: %d\n", database.prossima_matricola);
    
    printf("\n👋 Grazie per aver utilizzato il sistema!\n");
    return 0;
}

/**
 * TODO: Implementa l'inizializzazione del database
 * - Azzera contatori
 * - Imposta matricola iniziale (es. 1000)
 * - Marca tutti gli studenti come non attivi
 */
void inizializza_database(Database* db) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Usa memset o loop per azzerare tutto
    // - Imposta prossima_matricola a un valore iniziale (1000)
    // - Inizializza num_studenti a 0
}

/**
 * TODO: Implementa il menu principale del sistema
 * Opzioni:
 * 1. Gestione Studenti (sottomenu)
 * 2. Gestione Voti (sottomenu)  
 * 3. Statistiche e Report (sottomenu)
 * 4. Ricerca Avanzata (sottomenu)
 * 5. Mostra Database Completo
 * 0. Esci
 */
void menu_principale(Database* db) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Usa ciclo do-while per ripetere menu
    // - Ogni opzione dovrebbe chiamare sottomenu specifici
    // - Mostra sempre numero studenti attuali
    // - Valida input con leggi_intero()
}

/**
 * TODO: Implementa l'aggiunta di un nuovo studente
 * - Verifica spazio disponibile (MAX_STUDENTI)
 * - Richiedi e valida nome, cognome, anno corso
 * - Assegna matricola automaticamente
 * - Inizializza array esami vuoto
 */
void aggiungi_studente(Database* db) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Controlla db->num_studenti < MAX_STUDENTI
    // - Valida che nome/cognome non siano vuoti
    // - Anno corso: 1-6 (triennale + magistrale + fuori corso)
    // - Incrementa num_studenti e prossima_matricola
}

/**
 * TODO: Implementa la ricerca studente per matricola o nome
 * - Permetti ricerca per matricola
 * - Permetti ricerca per nome e cognome
 * - Mostra risultati dettagliati
 * - Gestisci caso "non trovato"
 */
void cerca_studente(const Database* db) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Menu: 1=Cerca per matricola, 2=Cerca per nome
    // - Usa le funzioni trova_studente_*
    // - Mostra dettagli completi se trovato
}

/**
 * TODO: Implementa l'aggiunta di un voto
 * - Trova studente per matricola
 * - Verifica spazio per nuovo esame
 * - Valida materia, voto e data
 * - Aggiungi esame all'array
 */
void aggiungi_voto(Database* db) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Cerca studente con trova_studente_per_matricola()
    // - Controlla num_esami < MAX_VOTI_PER_STUDENTE
    // - Valida voto (18-30, 31 per lode)
    // - Valida data con valida_data()
}

/**
 * TODO: Implementa il calcolo statistiche per uno studente
 * - Media aritmetica dei voti
 * - Voto minimo e massimo
 * - Numero esami sostenuti
 * - Percentuale lodi
 * - Trend (miglioramento/peggioramento)
 */
void calcola_statistiche_studente(const Database* db) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Chiedi matricola studente
    // - Calcola media con calcola_media_studente()
    // - Trova min/max con ciclo for
    // - Conta lodi (voto == 31)
}

/**
 * TODO: Implementa statistiche generali del database
 * - Media generale di tutti gli studenti
 * - Distribuzione voti (18-21, 22-24, 25-27, 28-30, lode)
 * - Studente con media più alta/bassa
 * - Materia con media più alta/bassa
 */
void calcola_statistiche_generali(const Database* db) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Itera su tutti gli studenti attivi
    // - Mantieni contatori per distribuzione
    // - Trova massimi/minimi con confronti
    // - Calcola medie per materia
}

/**
 * TODO: Implementa la generazione di classifica
 * - Ordina studenti per media decrescente
 * - Mostra posizioni con pari merito
 * - Include numero esami per ogni studente
 * - Opzione per filtrare per anno corso
 */
void genera_classifica(const Database* db) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Crea copia temporanea per ordinamento
    // - Usa ordina_studenti_per_media()
    // - Gestisci pari merito con controllo media uguale
    // - Formatta output come tabella
}

/**
 * TODO: Implementa ricerca avanzata
 * - Filtra per range di media
 * - Filtra per anno corso
 * - Filtra per numero minimo esami
 * - Combinazione di filtri multipli
 */
void ricerca_avanzata(const Database* db) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Menu con opzioni di filtro multiple
    // - Permetti combinazione di criteri
    // - Usa flag booleani per ogni criterio
    // - Mostra risultati in formato tabella
}

/**
 * TODO: Implementa validazione voto
 * - Range 18-30 per voti normali
 * - 31 per rappresentare 30 e lode
 * - Gestisci input non validi
 */
bool valida_voto(int voto) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Controlla range 18-31
    // - Return true se valido, false altrimenti
}

/**
 * TODO: Implementa validazione data
 * - Formato gg/mm/aaaa
 * - Verifica giorni/mesi validi
 * - Anni ragionevoli (2000-2030)
 */
bool valida_data(const char* data) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Usa sscanf per parsing: sscanf(data, "%d/%d/%d", &g, &m, &a)
    // - Controlla range giorni (1-31), mesi (1-12), anni (2000-2030)
    // - Considera giorni per mese (febbraio, mesi con 30/31 giorni)
}

/**
 * TODO: Implementa calcolo media studente
 * - Somma tutti i voti (31 = 30 per calcolo)
 * - Dividi per numero esami
 * - Gestisci caso nessun esame
 */
float calcola_media_studente(const Studente* s) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Controlla s->num_esami > 0
    // - Tratta voto 31 come 30 per calcolo media
    // - Return 0.0 se nessun esame
}

/**
 * TODO: Implementa ricerca studente per matricola
 * - Itera attraverso array studenti
 * - Confronta matricola e flag attivo
 * - Return indice se trovato, -1 se non trovato
 */
int trova_studente_per_matricola(const Database* db, int matricola) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Usa for loop su db->studenti
    // - Controlla sia matricola che flag attivo
    // - Return i se trovato, -1 altrimenti
}

/**
 * TODO: Implementa ordinamento studenti per media
 * - Algoritmo bubble sort o selection sort
 * - Ordina per media decrescente
 * - Mantieni associazione dati studente
 */
void ordina_studenti_per_media(Database* db) {
    // COMPLETA QUESTA FUNZIONE
    // Suggerimenti:
    // - Usa bubble sort per semplicità
    // - Confronta medie calcolate con calcola_media_studente()
    // - Scambia studenti completi, non solo medie
}

// ===== FUNZIONI UTILITY GIÀ IMPLEMENTATE =====

void stampa_intestazione_sistema(void) {
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║            🎓 SISTEMA GESTIONE VOTI STUDENTI 🎓               ║\n");
    printf("║                                                                ║\n");
    printf("║  Gestione completa di studenti, voti, statistiche e report    ║\n");
    printf("║  con validazione avanzata e funzionalità di ricerca           ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
}

const char* converti_voto_stringa(int voto) {
    static char buffer[10];
    if (voto == 31) {
        strcpy(buffer, "30 e lode");
    } else {
        sprintf(buffer, "%d", voto);
    }
    return buffer;
}

int leggi_intero(const char* prompt, int min, int max) {
    int valore;
    char buffer[100];
    
    do {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &valore) == 1) {
                if (valore >= min && valore <= max) {
                    return valore;
                }
            }
        }
        printf("❌ Inserisci un numero tra %d e %d!\n", min, max);
    } while (1);
}

bool leggi_stringa(char* buffer, int max_len, const char* prompt) {
    printf("%s", prompt);
    if (fgets(buffer, max_len, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;  // Rimuovi newline
        return strlen(buffer) > 0;
    }
    return false;
}

/*
 * ===============================================
 * ISTRUZIONI DETTAGLIATE PER LO STUDENTE:
 * ===============================================
 * 
 * FASE 1 - SETUP BASE (15 min):
 * • Implementa inizializza_database()
 * • Implementa le funzioni di validazione base
 * • Testa l'inizializzazione con printf di debug
 * 
 * FASE 2 - GESTIONE STUDENTI (20 min):
 * • Implementa aggiungi_studente()
 * • Implementa trova_studente_per_matricola()
 * • Implementa cerca_studente()
 * • Testa aggiunta e ricerca studenti
 * 
 * FASE 3 - GESTIONE VOTI (15 min):
 * • Implementa valida_voto() e valida_data()
 * • Implementa aggiungi_voto()
 * • Implementa calcola_media_studente()
 * • Testa inserimento voti e calcolo medie
 * 
 * FASE 4 - STATISTICHE (15 min):
 * • Implementa calcola_statistiche_studente()
 * • Implementa calcola_statistiche_generali()
 * • Implementa ordina_studenti_per_media()
 * • Testa generazione statistiche
 * 
 * FASE 5 - MENU E RICERCA (15 min):
 * • Implementa menu_principale()
 * • Implementa genera_classifica()
 * • Implementa ricerca_avanzata()
 * • Test completo del sistema
 * 
 * SUGGERIMENTI IMPLEMENTAZIONE:
 * 
 * 1. GESTIONE MEMORIA:
 *    - Controlla sempre i bounds degli array
 *    - Verifica num_studenti < MAX_STUDENTI
 *    - Verifica num_esami < MAX_VOTI_PER_STUDENTE
 * 
 * 2. VALIDAZIONE INPUT:
 *    - Non fidarti mai dell'input utente
 *    - Valida lunghezza stringhe
 *    - Controlla range numerici
 *    - Gestisci buffer overflow
 * 
 * 3. ALGORITMI:
 *    - Per ordinamento usa bubble sort (semplice)
 *    - Per ricerca usa linear search
 *    - Per statistiche usa accumulatori
 * 
 * 4. INTERFACCIA UTENTE:
 *    - Messaggi chiari e informativi
 *    - Gestisci casi "non trovato"
 *    - Conferme per operazioni critiche
 *    - Menu ben strutturati
 * 
 * FUNZIONALITÀ BONUS (OPZIONALI):
 * • Salvataggio/caricamento da file
 * • Backup automatico del database
 * • Grafici ASCII per distribuzione voti
 * • Sistema di notifiche per scadenze
 * • Export report in formato CSV
 * • Calcolo crediti CFU
 * • Simulazione voti mancanti per laurea
 * 
 * TESTING:
 * 1. Aggiungi 5-10 studenti di test
 * 2. Inserisci voti vari per ogni studente
 * 3. Testa tutte le funzioni di ricerca
 * 4. Verifica calcoli statistici manualmente
 * 5. Prova edge cases (database vuoto, studente senza voti)
 * 
 * CRITERI VALUTAZIONE:
 * ✅ Funzionalità base complete (CRUD studenti/voti)
 * ✅ Validazione input robusta
 * ✅ Calcoli statistici corretti
 * ✅ Menu e navigazione intuitivi
 * ✅ Gestione errori appropriata
 * ✅ Codice ben strutturato e commentato
 * ✅ Testing completo e debugging
 */
