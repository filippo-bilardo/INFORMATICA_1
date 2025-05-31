/*
 * ===============================================
 * ESEMPIO: Menu Interattivo
 * ===============================================
 * 
 * Questo programma dimostra come creare menu
 * interattivi utilizzando cicli e strutture
 * condizionali per gestire le scelte dell'utente.
 * 
 * CONCETTI DIMOSTRATI:
 * - Menu principale con ciclo infinito
 * - Switch-case per gestire opzioni
 * - Validazione input utente
 * - Sottomenu e navigazione
 * - Gestione errori e messaggi informativi
 * - Stato del programma e persistenza dati
 * 
 * Autore: Corso C by Example
 * Versione: 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ===== STRUTTURE DATI =====
typedef struct {
    char nome[50];
    float saldo;
    int transazioni;
} ContoBancario;

typedef struct {
    char titolo[100];
    char autore[50];
    int anno;
    int disponibile;
} Libro;

// ===== VARIABILI GLOBALI =====
ContoBancario conto = {"Mario Rossi", 1500.75, 0};
Libro biblioteca[5] = {
    {"Il Signore degli Anelli", "J.R.R. Tolkien", 1954, 1},
    {"1984", "George Orwell", 1949, 1},
    {"Il Piccolo Principe", "Antoine de Saint-Exupéry", 1943, 0},
    {"Programmazione in C", "Dennis Ritchie", 1978, 1},
    {"Algoritmi e Strutture Dati", "Robert Sedgewick", 1988, 1}
};

// ===== PROTOTIPI FUNZIONI =====
void menu_principale(void);
void menu_banca(void);
void menu_biblioteca(void);
void menu_calcolatrice(void);
void menu_giochi(void);

void banca_visualizza_saldo(void);
void banca_deposita(void);
void banca_preleva(void);
void banca_storico(void);

void biblioteca_visualizza(void);
void biblioteca_cerca(void);
void biblioteca_prestito(void);
void biblioteca_restituzione(void);

void calcolatrice_semplice(void);
void calcolatrice_scientifica(void);

void gioco_indovina_numero(void);
void gioco_carta_forbice_sasso(void);

void stampa_intestazione(const char* titolo);
void pausa_sistema(void);
void pulisci_schermo(void);
int leggi_intero(const char* prompt, int min, int max);
float leggi_float(const char* prompt);

// ===== FUNZIONE PRINCIPALE =====
int main() {
    srand(time(NULL));
    
    printf("🎮 SISTEMA MENU INTERATTIVO\n");
    printf("============================\n");
    printf("Benvenuto nel sistema di gestione multifunzione!\n\n");
    
    menu_principale();
    
    printf("\n👋 Grazie per aver utilizzato il sistema!\n");
    printf("🎓 Hai imparato a creare menu interattivi in C!\n");
    
    return 0;
}

// ===== MENU PRINCIPALE =====

/**
 * Menu principale del sistema
 */
void menu_principale(void) {
    int scelta;
    
    do {
        pulisci_schermo();
        stampa_intestazione("MENU PRINCIPALE");
        
        printf("Seleziona un'area di interesse:\n\n");
        printf("1. 🏦 Sistema Bancario\n");
        printf("2. 📚 Gestione Biblioteca\n");
        printf("3. 🧮 Calcolatrice\n");
        printf("4. 🎲 Giochi\n");
        printf("5. ℹ️  Informazioni Sistema\n");
        printf("0. 🚪 Esci\n");
        
        scelta = leggi_intero("\n➤ Inserisci la tua scelta: ", 0, 5);
        
        switch (scelta) {
            case 1:
                menu_banca();
                break;
            case 2:
                menu_biblioteca();
                break;
            case 3:
                menu_calcolatrice();
                break;
            case 4:
                menu_giochi();
                break;
            case 5:
                pulisci_schermo();
                stampa_intestazione("INFORMAZIONI SISTEMA");
                printf("📋 Nome: Sistema Menu Interattivo\n");
                printf("🔢 Versione: 1.0\n");
                printf("👨‍💻 Autore: Corso C by Example\n");
                printf("📅 Data: %s\n", __DATE__);
                printf("⏰ Ora compilazione: %s\n", __TIME__);
                printf("\n💡 Questo programma dimostra l'uso di:\n");
                printf("   • Menu interattivi con cicli\n");
                printf("   • Switch-case per gestione opzioni\n");
                printf("   • Validazione input utente\n");
                printf("   • Gestione stato del programma\n");
                pausa_sistema();
                break;
            case 0:
                printf("\n👋 Arrivederci!\n");
                break;
            default:
                printf("\n❌ Opzione non valida!\n");
                pausa_sistema();
                break;
        }
    } while (scelta != 0);
}

// ===== MENU SISTEMA BANCARIO =====

/**
 * Menu del sistema bancario
 */
void menu_banca(void) {
    int scelta;
    
    do {
        pulisci_schermo();
        stampa_intestazione("SISTEMA BANCARIO");
        printf("👤 Titolare: %s\n", conto.nome);
        printf("💰 Saldo attuale: €%.2f\n", conto.saldo);
        printf("📊 Transazioni effettuate: %d\n\n", conto.transazioni);
        
        printf("Operazioni disponibili:\n\n");
        printf("1. 👁️  Visualizza saldo dettagliato\n");
        printf("2. ⬆️  Deposita denaro\n");
        printf("3. ⬇️  Preleva denaro\n");
        printf("4. 📈 Storico transazioni\n");
        printf("0. ⬅️  Torna al menu principale\n");
        
        scelta = leggi_intero("\n➤ Scegli operazione: ", 0, 4);
        
        switch (scelta) {
            case 1:
                banca_visualizza_saldo();
                break;
            case 2:
                banca_deposita();
                break;
            case 3:
                banca_preleva();
                break;
            case 4:
                banca_storico();
                break;
            case 0:
                printf("\n🔙 Ritorno al menu principale...\n");
                break;
            default:
                printf("\n❌ Operazione non valida!\n");
                pausa_sistema();
                break;
        }
    } while (scelta != 0);
}

void banca_visualizza_saldo(void) {
    pulisci_schermo();
    stampa_intestazione("DETTAGLI CONTO");
    
    printf("👤 Intestatario: %s\n", conto.nome);
    printf("💰 Saldo disponibile: €%.2f\n", conto.saldo);
    printf("📊 Numero transazioni: %d\n", conto.transazioni);
    
    // Classificazione del saldo
    if (conto.saldo >= 10000) {
        printf("🌟 Status: Cliente Premium\n");
    } else if (conto.saldo >= 1000) {
        printf("⭐ Status: Cliente Standard\n");
    } else if (conto.saldo >= 0) {
        printf("📊 Status: Cliente Base\n");
    } else {
        printf("⚠️  Status: Conto in rosso\n");
    }
    
    pausa_sistema();
}

void banca_deposita(void) {
    pulisci_schermo();
    stampa_intestazione("DEPOSITO DENARO");
    
    printf("💰 Saldo attuale: €%.2f\n\n", conto.saldo);
    
    float importo = leggi_float("➤ Inserisci importo da depositare: €");
    
    if (importo <= 0) {
        printf("\n❌ Importo non valido!\n");
    } else if (importo > 50000) {
        printf("\n⚠️  Importo troppo elevato! Massimo €50.000 per transazione.\n");
    } else {
        conto.saldo += importo;
        conto.transazioni++;
        printf("\n✅ Deposito effettuato con successo!\n");
        printf("💰 Nuovo saldo: €%.2f\n", conto.saldo);
    }
    
    pausa_sistema();
}

void banca_preleva(void) {
    pulisci_schermo();
    stampa_intestazione("PRELIEVO DENARO");
    
    printf("💰 Saldo attuale: €%.2f\n\n", conto.saldo);
    
    float importo = leggi_float("➤ Inserisci importo da prelevare: €");
    
    if (importo <= 0) {
        printf("\n❌ Importo non valido!\n");
    } else if (importo > conto.saldo) {
        printf("\n❌ Saldo insufficiente!\n");
        printf("💰 Saldo disponibile: €%.2f\n", conto.saldo);
    } else if (importo > 1000) {
        printf("\n⚠️  Importo elevato! Massimo €1.000 per prelievo.\n");
    } else {
        conto.saldo -= importo;
        conto.transazioni++;
        printf("\n✅ Prelievo effettuato con successo!\n");
        printf("💰 Nuovo saldo: €%.2f\n", conto.saldo);
    }
    
    pausa_sistema();
}

void banca_storico(void) {
    pulisci_schermo();
    stampa_intestazione("STORICO TRANSAZIONI");
    
    printf("📊 Totale transazioni effettuate: %d\n", conto.transazioni);
    printf("💰 Saldo attuale: €%.2f\n\n", conto.saldo);
    
    if (conto.transazioni == 0) {
        printf("📭 Nessuna transazione effettuata ancora.\n");
    } else {
        printf("📈 Attività recente del conto:\n");
        printf("   • Transazioni completate: %d\n", conto.transazioni);
        printf("   • Media per transazione: €%.2f\n", 
               conto.saldo / conto.transazioni);
    }
    
    pausa_sistema();
}

// ===== MENU BIBLIOTECA =====

/**
 * Menu gestione biblioteca
 */
void menu_biblioteca(void) {
    int scelta;
    
    do {
        pulisci_schermo();
        stampa_intestazione("GESTIONE BIBLIOTECA");
        
        // Conta libri disponibili
        int disponibili = 0;
        for (int i = 0; i < 5; i++) {
            if (biblioteca[i].disponibile) disponibili++;
        }
        
        printf("📚 Libri in catalogo: 5\n");
        printf("✅ Libri disponibili: %d\n", disponibili);
        printf("📖 Libri in prestito: %d\n\n", 5 - disponibili);
        
        printf("Operazioni disponibili:\n\n");
        printf("1. 📋 Visualizza catalogo\n");
        printf("2. 🔍 Cerca libro\n");
        printf("3. 📤 Prestito libro\n");
        printf("4. 📥 Restituzione libro\n");
        printf("0. ⬅️  Torna al menu principale\n");
        
        scelta = leggi_intero("\n➤ Scegli operazione: ", 0, 4);
        
        switch (scelta) {
            case 1:
                biblioteca_visualizza();
                break;
            case 2:
                biblioteca_cerca();
                break;
            case 3:
                biblioteca_prestito();
                break;
            case 4:
                biblioteca_restituzione();
                break;
            case 0:
                printf("\n🔙 Ritorno al menu principale...\n");
                break;
            default:
                printf("\n❌ Operazione non valida!\n");
                pausa_sistema();
                break;
        }
    } while (scelta != 0);
}

void biblioteca_visualizza(void) {
    pulisci_schermo();
    stampa_intestazione("CATALOGO BIBLIOTECA");
    
    printf("📚 Elenco completo dei libri:\n\n");
    
    for (int i = 0; i < 5; i++) {
        printf("%d. 📖 \"%s\"\n", i + 1, biblioteca[i].titolo);
        printf("   👤 Autore: %s\n", biblioteca[i].autore);
        printf("   📅 Anno: %d\n", biblioteca[i].anno);
        printf("   📊 Status: %s\n\n", 
               biblioteca[i].disponibile ? "✅ Disponibile" : "❌ In prestito");
    }
    
    pausa_sistema();
}

void biblioteca_cerca(void) {
    pulisci_schermo();
    stampa_intestazione("RICERCA LIBRO");
    
    char termine[50];
    printf("🔍 Inserisci termine di ricerca (titolo o autore): ");
    fgets(termine, sizeof(termine), stdin);
    
    // Rimuovi newline
    termine[strcspn(termine, "\n")] = 0;
    
    printf("\n📋 Risultati della ricerca:\n\n");
    int trovati = 0;
    
    for (int i = 0; i < 5; i++) {
        if (strstr(biblioteca[i].titolo, termine) || 
            strstr(biblioteca[i].autore, termine)) {
            printf("✅ Trovato: \"%s\" di %s (%d)\n", 
                   biblioteca[i].titolo, biblioteca[i].autore, biblioteca[i].anno);
            printf("   Status: %s\n\n", 
                   biblioteca[i].disponibile ? "Disponibile" : "In prestito");
            trovati++;
        }
    }
    
    if (trovati == 0) {
        printf("❌ Nessun libro trovato con il termine \"%s\"\n", termine);
    }
    
    pausa_sistema();
}

void biblioteca_prestito(void) {
    pulisci_schermo();
    stampa_intestazione("PRESTITO LIBRO");
    
    biblioteca_visualizza();
    
    int scelta = leggi_intero("➤ Seleziona numero libro (1-5): ", 1, 5);
    scelta--; // Converti a indice array
    
    if (biblioteca[scelta].disponibile) {
        biblioteca[scelta].disponibile = 0;
        printf("\n✅ Prestito effettuato!\n");
        printf("📖 Libro: \"%s\"\n", biblioteca[scelta].titolo);
        printf("📅 Ricorda di restituirlo entro 30 giorni.\n");
    } else {
        printf("\n❌ Libro già in prestito!\n");
    }
    
    pausa_sistema();
}

void biblioteca_restituzione(void) {
    pulisci_schermo();
    stampa_intestazione("RESTITUZIONE LIBRO");
    
    printf("📚 Libri attualmente in prestito:\n\n");
    int prestiti = 0;
    
    for (int i = 0; i < 5; i++) {
        if (!biblioteca[i].disponibile) {
            printf("%d. 📖 \"%s\"\n", i + 1, biblioteca[i].titolo);
            prestiti++;
        }
    }
    
    if (prestiti == 0) {
        printf("✅ Nessun libro in prestito!\n");
        pausa_sistema();
        return;
    }
    
    int scelta = leggi_intero("\n➤ Seleziona numero libro da restituire: ", 1, 5);
    scelta--; // Converti a indice array
    
    if (!biblioteca[scelta].disponibile) {
        biblioteca[scelta].disponibile = 1;
        printf("\n✅ Restituzione effettuata!\n");
        printf("📖 Libro: \"%s\"\n", biblioteca[scelta].titolo);
        printf("🙏 Grazie per la restituzione!\n");
    } else {
        printf("\n❌ Questo libro non è in prestito!\n");
    }
    
    pausa_sistema();
}

// ===== MENU CALCOLATRICE =====

/**
 * Menu calcolatrice
 */
void menu_calcolatrice(void) {
    int scelta;
    
    do {
        pulisci_schermo();
        stampa_intestazione("CALCOLATRICE");
        
        printf("Seleziona tipo di calcolo:\n\n");
        printf("1. 🧮 Calcolatrice semplice\n");
        printf("2. 🔬 Calcolatrice scientifica\n");
        printf("0. ⬅️  Torna al menu principale\n");
        
        scelta = leggi_intero("\n➤ Scegli modalità: ", 0, 2);
        
        switch (scelta) {
            case 1:
                calcolatrice_semplice();
                break;
            case 2:
                calcolatrice_scientifica();
                break;
            case 0:
                printf("\n🔙 Ritorno al menu principale...\n");
                break;
            default:
                printf("\n❌ Modalità non valida!\n");
                pausa_sistema();
                break;
        }
    } while (scelta != 0);
}

void calcolatrice_semplice(void) {
    pulisci_schermo();
    stampa_intestazione("CALCOLATRICE SEMPLICE");
    
    float a = leggi_float("➤ Inserisci primo numero: ");
    float b = leggi_float("➤ Inserisci secondo numero: ");
    
    printf("\nSeleziona operazione:\n");
    printf("1. ➕ Addizione\n");
    printf("2. ➖ Sottrazione\n");
    printf("3. ✖️  Moltiplicazione\n");
    printf("4. ➗ Divisione\n");
    
    int op = leggi_intero("\n➤ Operazione: ", 1, 4);
    
    printf("\n📊 Risultato: %.2f ", a);
    
    switch (op) {
        case 1:
            printf("+ %.2f = %.2f\n", b, a + b);
            break;
        case 2:
            printf("- %.2f = %.2f\n", b, a - b);
            break;
        case 3:
            printf("× %.2f = %.2f\n", b, a * b);
            break;
        case 4:
            if (b != 0) {
                printf("÷ %.2f = %.2f\n", b, a / b);
            } else {
                printf("÷ %.2f = ❌ Errore: divisione per zero!\n", b);
            }
            break;
    }
    
    pausa_sistema();
}

void calcolatrice_scientifica(void) {
    pulisci_schermo();
    stampa_intestazione("CALCOLATRICE SCIENTIFICA");
    
    printf("🔬 Funzioni avanzate non implementate in questo esempio.\n");
    printf("💡 Suggerimento: Potresti implementare:\n");
    printf("   • Potenze e radici\n");
    printf("   • Funzioni trigonometriche\n");
    printf("   • Logaritmi\n");
    printf("   • Fattoriali\n");
    
    pausa_sistema();
}

// ===== MENU GIOCHI =====

/**
 * Menu giochi
 */
void menu_giochi(void) {
    int scelta;
    
    do {
        pulisci_schermo();
        stampa_intestazione("AREA GIOCHI");
        
        printf("Seleziona un gioco:\n\n");
        printf("1. 🎯 Indovina il numero\n");
        printf("2. ✂️  Carta, Forbice, Sasso\n");
        printf("0. ⬅️  Torna al menu principale\n");
        
        scelta = leggi_intero("\n➤ Scegli gioco: ", 0, 2);
        
        switch (scelta) {
            case 1:
                gioco_indovina_numero();
                break;
            case 2:
                gioco_carta_forbice_sasso();
                break;
            case 0:
                printf("\n🔙 Ritorno al menu principale...\n");
                break;
            default:
                printf("\n❌ Gioco non valido!\n");
                pausa_sistema();
                break;
        }
    } while (scelta != 0);
}

void gioco_indovina_numero(void) {
    pulisci_schermo();
    stampa_intestazione("INDOVINA IL NUMERO");
    
    int numero_segreto = rand() % 100 + 1;
    int tentativi = 0;
    int massimo_tentativi = 7;
    int indovinato = 0;
    
    printf("🎯 Ho pensato un numero tra 1 e 100!\n");
    printf("🎮 Hai %d tentativi per indovinarlo.\n\n", massimo_tentativi);
    
    while (tentativi < massimo_tentativi && !indovinato) {
        int guess = leggi_intero("➤ Il tuo numero: ", 1, 100);
        tentativi++;
        
        if (guess == numero_segreto) {
            printf("\n🎉 BRAVO! Hai indovinato in %d tentativi!\n", tentativi);
            indovinato = 1;
        } else if (guess < numero_segreto) {
            printf("📈 Troppo basso! Tentativi rimasti: %d\n\n", 
                   massimo_tentativi - tentativi);
        } else {
            printf("📉 Troppo alto! Tentativi rimasti: %d\n\n", 
                   massimo_tentativi - tentativi);
        }
    }
    
    if (!indovinato) {
        printf("\n😞 Hai esaurito i tentativi!\n");
        printf("🔢 Il numero era: %d\n", numero_segreto);
    }
    
    pausa_sistema();
}

void gioco_carta_forbice_sasso(void) {
    pulisci_schermo();
    stampa_intestazione("CARTA, FORBICE, SASSO");
    
    printf("🎮 Regole del gioco:\n");
    printf("📄 Carta batte Sasso\n");
    printf("✂️  Forbice batte Carta\n");
    printf("🗿 Sasso batte Forbice\n\n");
    
    printf("Scegli la tua mossa:\n");
    printf("1. 📄 Carta\n");
    printf("2. ✂️  Forbice\n");
    printf("3. 🗿 Sasso\n");
    
    int giocatore = leggi_intero("\n➤ La tua scelta: ", 1, 3);
    int computer = rand() % 3 + 1;
    
    char* mosse[] = {"", "📄 Carta", "✂️  Forbice", "🗿 Sasso"};
    
    printf("\n🎲 Tu hai scelto: %s\n", mosse[giocatore]);
    printf("🤖 Computer ha scelto: %s\n\n", mosse[computer]);
    
    if (giocatore == computer) {
        printf("🤝 PAREGGIO!\n");
    } else if ((giocatore == 1 && computer == 3) ||  // Carta batte Sasso
               (giocatore == 2 && computer == 1) ||  // Forbice batte Carta
               (giocatore == 3 && computer == 2)) {  // Sasso batte Forbice
        printf("🎉 HAI VINTO!\n");
    } else {
        printf("😞 HAI PERSO!\n");
    }
    
    pausa_sistema();
}

// ===== FUNZIONI UTILITY =====

/**
 * Stampa intestazione con titolo
 */
void stampa_intestazione(const char* titolo) {
    printf("══════════════════════════════════════════════════\n");
    printf("    %s\n", titolo);
    printf("══════════════════════════════════════════════════\n\n");
}

/**
 * Pausa per leggere output
 */
void pausa_sistema(void) {
    printf("\n⏸️  Premi INVIO per continuare...");
    while (getchar() != '\n');
}

/**
 * Simula pulizia schermo
 */
void pulisci_schermo(void) {
    // In un sistema reale useresti system("clear") o system("cls")
    printf("\n\n");
}

/**
 * Legge un intero con validazione
 */
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

/**
 * Legge un float con validazione
 */
float leggi_float(const char* prompt) {
    float valore;
    char buffer[100];
    
    do {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%f", &valore) == 1) {
                return valore;
            }
        }
        printf("❌ Inserisci un numero valido!\n");
    } while (1);
}
