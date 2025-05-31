/*
 * ===============================================
 * ESEMPIO: Validazione Input Utente
 * ===============================================
 * 
 * Questo programma dimostra tecniche robuste
 * per la validazione dell'input utente, gestione
 * errori e creazione di interfacce user-friendly.
 * 
 * CONCETTI DIMOSTRATI:
 * - Validazione tipi di dato
 * - Gestione buffer overflow
 * - Controllo range e formato
 * - Messaggi di errore informativi
 * - Retry automatico con limiti
 * - Sanitizzazione input
 * - Pattern di validazione comuni
 * 
 * Autore: Corso C by Example
 * Versione: 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

// ===== COSTANTI =====
#define MAX_INPUT_LENGTH 256
#define MAX_TENTATIVI 3
#define MIN_PASSWORD_LENGTH 6
#define MAX_PASSWORD_LENGTH 20

// ===== STRUTTURE DATI =====
typedef struct {
    char nome[50];
    char cognome[50];
    int eta;
    char email[100];
    char telefono[20];
    char password[50];
} Utente;

typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

// ===== PROTOTIPI FUNZIONI =====
void demo_validazione_base(void);
void demo_validazione_numerica(void);
void demo_validazione_stringhe(void);
void demo_validazione_date(void);
void demo_registrazione_utente(void);
void demo_menu_con_validazione(void);

// Funzioni di validazione
int leggi_intero_validato(const char* prompt, int min, int max);
float leggi_float_validato(const char* prompt, float min, float max);
char leggi_carattere_validato(const char* prompt, const char* caratteri_validi);
bool leggi_stringa_validata(char* buffer, int max_len, const char* prompt);
bool leggi_email_validata(char* email, int max_len);
bool leggi_telefono_validato(char* telefono, int max_len);
bool leggi_password_validata(char* password, int max_len);
bool leggi_data_validata(Data* data);

// Funzioni di utilità
void pulisci_buffer_input(void);
void stampa_separatore(const char* titolo);
void stampa_errore(const char* messaggio);
void stampa_successo(const char* messaggio);
bool is_email_valida(const char* email);
bool is_telefono_valido(const char* telefono);
bool is_password_sicura(const char* password);
bool is_data_valida(int giorno, int mese, int anno);
bool is_anno_bisestile(int anno);
void mostra_requisiti_password(void);

// ===== FUNZIONE PRINCIPALE =====
int main() {
    printf("🔐 ESEMPI: Validazione Input Utente\n");
    printf("===================================\n\n");
    
    printf("💡 Questo programma dimostra tecniche professionali\n");
    printf("   per validare l'input utente in modo sicuro e user-friendly.\n\n");
    
    demo_validazione_base();
    demo_validazione_numerica();
    demo_validazione_stringhe();
    demo_validazione_date();
    demo_registrazione_utente();
    demo_menu_con_validazione();
    
    printf("🎉 Hai imparato tutte le tecniche di validazione input!\n");
    printf("🛡️ Il tuo codice sarà ora più robusto e sicuro.\n");
    
    return 0;
}

// ===== DEMO VALIDAZIONE BASE =====

/**
 * Dimostra tecniche di validazione base
 */
void demo_validazione_base(void) {
    stampa_separatore("VALIDAZIONE BASE");
    
    printf("🎯 Esempi di validazione input fondamentale:\n\n");
    
    // Validazione semplice
    printf("1️⃣ Inserimento età (18-99 anni):\n");
    int eta = leggi_intero_validato("   Inserisci la tua età: ", 18, 99);
    printf("   ✅ Età valida: %d anni\n\n", eta);
    
    // Validazione carattere
    printf("2️⃣ Selezione categoria (S/N per Studente/Non studente):\n");
    char categoria = leggi_carattere_validato("   Sei uno studente? (S/N): ", "SsNn");
    printf("   ✅ Categoria: %s\n\n", 
           (categoria == 'S' || categoria == 's') ? "Studente" : "Non studente");
    
    // Validazione float con range
    printf("3️⃣ Inserimento voto esame (18.0-30.0):\n");
    float voto = leggi_float_validato("   Voto conseguito: ", 18.0, 30.0);
    printf("   ✅ Voto valido: %.1f", voto);
    if (voto == 30.0) {
        printf(" - Eccellente! 🌟");
    } else if (voto >= 27.0) {
        printf(" - Ottimo! 😊");
    } else if (voto >= 24.0) {
        printf(" - Buono! 👍");
    }
    printf("\n\n");
}

/**
 * Dimostra validazione numerica avanzata
 */
void demo_validazione_numerica(void) {
    stampa_separatore("VALIDAZIONE NUMERICA AVANZATA");
    
    printf("🔢 Esempi di validazione numerica con casi speciali:\n\n");
    
    // Validazione numero primo
    printf("1️⃣ Inserimento numero primo (2-100):\n");
    int numero;
    bool is_primo = false;
    
    do {
        numero = leggi_intero_validato("   Inserisci un numero primo: ", 2, 100);
        
        // Verifica se è primo
        is_primo = true;
        for (int i = 2; i * i <= numero; i++) {
            if (numero % i == 0) {
                is_primo = false;
                break;
            }
        }
        
        if (!is_primo) {
            stampa_errore("Il numero non è primo! Riprova.");
        }
    } while (!is_primo);
    
    printf("   ✅ Numero primo valido: %d\n\n", numero);
    
    // Validazione percentuale
    printf("2️⃣ Inserimento percentuale di completamento:\n");
    float percentuale = leggi_float_validato("   Progresso (0.0-100.0%): ", 0.0, 100.0);
    
    printf("   📊 Barra di progresso: [");
    int barre = (int)(percentuale / 5);  // 20 caratteri max
    for (int i = 0; i < 20; i++) {
        if (i < barre) {
            printf("█");
        } else {
            printf("░");
        }
    }
    printf("] %.1f%%\n\n", percentuale);
    
    // Validazione range dinamico
    printf("3️⃣ Gioco indovina numero con validazione:\n");
    int numero_segreto = rand() % 50 + 1;
    int guess;
    int tentativi = 0;
    const int max_tentativi = 5;
    
    printf("   🎲 Ho pensato un numero tra 1 e 50. Hai %d tentativi!\n", max_tentativi);
    
    do {
        tentativi++;
        printf("   Tentativo %d/%d:\n", tentativi, max_tentativi);
        guess = leggi_intero_validato("      Il tuo numero: ", 1, 50);
        
        if (guess == numero_segreto) {
            stampa_successo("🎉 BRAVO! Hai indovinato!");
            break;
        } else if (guess < numero_segreto) {
            printf("      📈 Troppo basso!\n");
        } else {
            printf("      📉 Troppo alto!\n");
        }
    } while (tentativi < max_tentativi);
    
    if (guess != numero_segreto) {
        printf("   😞 Hai esaurito i tentativi. Il numero era: %d\n", numero_segreto);
    }
    
    printf("\n");
}

/**
 * Dimostra validazione stringhe
 */
void demo_validazione_stringhe(void) {
    stampa_separatore("VALIDAZIONE STRINGHE");
    
    printf("📝 Esempi di validazione stringhe e formati:\n\n");
    
    char buffer[MAX_INPUT_LENGTH];
    
    // Validazione nome
    printf("1️⃣ Inserimento nome (solo lettere, 2-30 caratteri):\n");
    bool nome_valido = false;
    
    do {
        if (leggi_stringa_validata(buffer, sizeof(buffer), "   Il tuo nome: ")) {
            // Verifica che contenga solo lettere
            nome_valido = true;
            for (int i = 0; buffer[i]; i++) {
                if (!isalpha(buffer[i]) && buffer[i] != ' ') {
                    nome_valido = false;
                    break;
                }
            }
            
            if (strlen(buffer) < 2 || strlen(buffer) > 30) {
                nome_valido = false;
            }
            
            if (!nome_valido) {
                stampa_errore("Nome non valido! Usa solo lettere (2-30 caratteri).");
            }
        }
    } while (!nome_valido);
    
    printf("   ✅ Nome valido: %s\n\n", buffer);
    
    // Validazione codice fiscale simulato
    printf("2️⃣ Inserimento codice fiscale (formato: XXX123X):\n");
    bool codice_valido = false;
    
    do {
        if (leggi_stringa_validata(buffer, sizeof(buffer), "   Codice fiscale: ")) {
            // Verifica formato: 3 lettere + 3 numeri + 1 lettera
            if (strlen(buffer) == 7) {
                codice_valido = true;
                
                // Prime 3 lettere
                for (int i = 0; i < 3; i++) {
                    if (!isalpha(buffer[i])) {
                        codice_valido = false;
                        break;
                    }
                }
                
                // 3 numeri
                for (int i = 3; i < 6; i++) {
                    if (!isdigit(buffer[i])) {
                        codice_valido = false;
                        break;
                    }
                }
                
                // Ultima lettera
                if (!isalpha(buffer[6])) {
                    codice_valido = false;
                }
            }
            
            if (!codice_valido) {
                stampa_errore("Formato non valido! Usa: XXX123X (3 lettere + 3 cifre + 1 lettera)");
            }
        }
    } while (!codice_valido);
    
    printf("   ✅ Codice fiscale valido: %s\n\n", buffer);
    
    // Validazione targa auto
    printf("3️⃣ Inserimento targa auto (formato: XX123XX):\n");
    bool targa_valida = false;
    
    do {
        if (leggi_stringa_validata(buffer, sizeof(buffer), "   Targa: ")) {
            // Converte in maiuscolo per uniformità
            for (int i = 0; buffer[i]; i++) {
                buffer[i] = toupper(buffer[i]);
            }
            
            // Verifica formato: 2 lettere + 3 numeri + 2 lettere
            if (strlen(buffer) == 7) {
                targa_valida = true;
                
                // Prime 2 lettere
                for (int i = 0; i < 2; i++) {
                    if (!isalpha(buffer[i])) {
                        targa_valida = false;
                        break;
                    }
                }
                
                // 3 numeri
                for (int i = 2; i < 5; i++) {
                    if (!isdigit(buffer[i])) {
                        targa_valida = false;
                        break;
                    }
                }
                
                // Ultime 2 lettere
                for (int i = 5; i < 7; i++) {
                    if (!isalpha(buffer[i])) {
                        targa_valida = false;
                        break;
                    }
                }
            }
            
            if (!targa_valida) {
                stampa_errore("Formato non valido! Usa: XX123XX (2 lettere + 3 cifre + 2 lettere)");
            }
        }
    } while (!targa_valida);
    
    printf("   ✅ Targa valida: %s\n\n", buffer);
}

/**
 * Dimostra validazione date
 */
void demo_validazione_date(void) {
    stampa_separatore("VALIDAZIONE DATE");
    
    printf("📅 Esempi di validazione date e formati temporali:\n\n");
    
    Data data;
    
    printf("1️⃣ Inserimento data di nascita:\n");
    if (leggi_data_validata(&data)) {
        printf("   ✅ Data valida: %02d/%02d/%d\n", data.giorno, data.mese, data.anno);
        
        // Calcola età approssimativa
        time_t now = time(NULL);
        struct tm* tm_now = localtime(&now);
        int anno_corrente = tm_now->tm_year + 1900;
        int eta_approssimativa = anno_corrente - data.anno;
        
        printf("   🎂 Età approssimativa: %d anni\n", eta_approssimativa);
        
        if (is_anno_bisestile(data.anno)) {
            printf("   📆 Anno bisestile!\n");
        }
    }
    
    printf("\n");
}

/**
 * Dimostra registrazione utente completa
 */
void demo_registrazione_utente(void) {
    stampa_separatore("REGISTRAZIONE UTENTE COMPLETA");
    
    printf("👤 Sistema di registrazione con validazione completa:\n\n");
    
    Utente utente;
    
    // Nome
    printf("1️⃣ Nome:\n");
    bool nome_valido = false;
    do {
        if (leggi_stringa_validata(utente.nome, sizeof(utente.nome), "   Nome: ")) {
            nome_valido = strlen(utente.nome) >= 2;
            if (!nome_valido) {
                stampa_errore("Il nome deve avere almeno 2 caratteri!");
            }
        }
    } while (!nome_valido);
    
    // Cognome
    printf("\n2️⃣ Cognome:\n");
    bool cognome_valido = false;
    do {
        if (leggi_stringa_validata(utente.cognome, sizeof(utente.cognome), "   Cognome: ")) {
            cognome_valido = strlen(utente.cognome) >= 2;
            if (!cognome_valido) {
                stampa_errore("Il cognome deve avere almeno 2 caratteri!");
            }
        }
    } while (!cognome_valido);
    
    // Età
    printf("\n3️⃣ Età:\n");
    utente.eta = leggi_intero_validato("   Età: ", 13, 120);
    
    // Email
    printf("\n4️⃣ Email:\n");
    while (!leggi_email_validata(utente.email, sizeof(utente.email))) {
        stampa_errore("Email non valida! Formato richiesto: nome@dominio.ext");
    }
    
    // Telefono
    printf("\n5️⃣ Telefono:\n");
    while (!leggi_telefono_validato(utente.telefono, sizeof(utente.telefono))) {
        stampa_errore("Telefono non valido! Formato: +39 123 456 7890 o 123-456-7890");
    }
    
    // Password
    printf("\n6️⃣ Password:\n");
    mostra_requisiti_password();
    while (!leggi_password_validata(utente.password, sizeof(utente.password))) {
        stampa_errore("Password non sicura! Verifica i requisiti sopra.");
        mostra_requisiti_password();
    }
    
    // Riepilogo registrazione
    printf("\n" "═══════════════════════════════════════════════════════════════\n");
    printf("✅ REGISTRAZIONE COMPLETATA CON SUCCESSO!\n");
    printf("═══════════════════════════════════════════════════════════════\n");
    printf("👤 Nome completo: %s %s\n", utente.nome, utente.cognome);
    printf("🎂 Età: %d anni\n", utente.eta);
    printf("📧 Email: %s\n", utente.email);
    printf("📱 Telefono: %s\n", utente.telefono);
    printf("🔐 Password: %s\n", "••••••••••••");
    printf("═══════════════════════════════════════════════════════════════\n\n");
}

/**
 * Dimostra menu con validazione
 */
void demo_menu_con_validazione(void) {
    stampa_separatore("MENU CON VALIDAZIONE");
    
    printf("📋 Sistema menu con gestione errori e retry automatico:\n\n");
    
    int scelta;
    do {
        printf("╔══════════════════════════════════════════════════════════════╗\n");
        printf("║                      MENU PRINCIPALE                        ║\n");
        printf("╠══════════════════════════════════════════════════════════════╣\n");
        printf("║  1. 🔍 Cerca prodotto                                       ║\n");
        printf("║  2. 🛒 Aggiungi al carrello                                 ║\n");
        printf("║  3. 💳 Procedi al pagamento                                 ║\n");
        printf("║  4. 📊 Visualizza statistiche                               ║\n");
        printf("║  5. ⚙️  Impostazioni                                         ║\n");
        printf("║  0. 🚪 Esci                                                  ║\n");
        printf("╚══════════════════════════════════════════════════════════════╝\n");
        
        scelta = leggi_intero_validato("\n➤ Seleziona opzione (0-5): ", 0, 5);
        
        switch (scelta) {
            case 1:
                printf("\n🔍 Funzione ricerca prodotto (simulata)\n");
                printf("   Inseriresti qui la logica di ricerca...\n");
                break;
                
            case 2:
                printf("\n🛒 Funzione carrello (simulata)\n");
                int quantita = leggi_intero_validato("   Quantità da aggiungere: ", 1, 99);
                printf("   ✅ Aggiunti %d articoli al carrello\n", quantita);
                break;
                
            case 3:
                printf("\n💳 Funzione pagamento (simulata)\n");
                float importo = leggi_float_validato("   Importo da pagare: €", 0.01, 9999.99);
                printf("   ✅ Pagamento di €%.2f processato\n", importo);
                break;
                
            case 4:
                printf("\n📊 Statistiche sistema:\n");
                printf("   • Utenti registrati: %d\n", rand() % 1000 + 100);
                printf("   • Prodotti disponibili: %d\n", rand() % 500 + 50);
                printf("   • Ordini oggi: %d\n", rand() % 50 + 5);
                break;
                
            case 5:
                printf("\n⚙️ Impostazioni:\n");
                char lingua = leggi_carattere_validato("   Lingua (I/E/F): ", "IiEeFf");
                printf("   ✅ Lingua impostata: %c\n", toupper(lingua));
                break;
                
            case 0:
                printf("\n👋 Grazie per aver utilizzato il sistema!\n");
                break;
                
            default:
                stampa_errore("Opzione non implementata!");
                break;
        }
        
        if (scelta != 0) {
            printf("\n⏸️ Premi INVIO per continuare...");
            while (getchar() != '\n');
            printf("\n");
        }
        
    } while (scelta != 0);
    
    printf("\n");
}

// ===== FUNZIONI DI VALIDAZIONE =====

/**
 * Legge un intero con validazione completa
 */
int leggi_intero_validato(const char* prompt, int min, int max) {
    char buffer[MAX_INPUT_LENGTH];
    int valore;
    int tentativi = 0;
    
    while (tentativi < MAX_TENTATIVI) {
        printf("%s", prompt);
        
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Rimuovi newline se presente
            buffer[strcspn(buffer, "\n")] = 0;
            
            // Controlla se la stringa è vuota
            if (strlen(buffer) == 0) {
                stampa_errore("Input vuoto! Inserisci un numero.");
                tentativi++;
                continue;
            }
            
            // Controlla se tutti i caratteri sono cifre (o segno meno iniziale)
            bool valido = true;
            for (int i = 0; buffer[i]; i++) {
                if (i == 0 && buffer[i] == '-') continue;  // Permetti segno meno
                if (!isdigit(buffer[i])) {
                    valido = false;
                    break;
                }
            }
            
            if (!valido) {
                stampa_errore("Inserisci solo cifre numeriche!");
                tentativi++;
                continue;
            }
            
            // Converti in intero
            valore = atoi(buffer);
            
            // Controlla range
            if (valore < min || valore > max) {
                printf("❌ Valore fuori range! Inserisci un numero tra %d e %d.\n", min, max);
                tentativi++;
                continue;
            }
            
            return valore;
        }
        
        stampa_errore("Errore di lettura!");
        tentativi++;
    }
    
    printf("🚫 Troppi tentativi falliti. Uso valore predefinito: %d\n", min);
    return min;
}

/**
 * Legge un float con validazione
 */
float leggi_float_validato(const char* prompt, float min, float max) {
    char buffer[MAX_INPUT_LENGTH];
    float valore;
    int tentativi = 0;
    
    while (tentativi < MAX_TENTATIVI) {
        printf("%s", prompt);
        
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = 0;
            
            if (strlen(buffer) == 0) {
                stampa_errore("Input vuoto! Inserisci un numero.");
                tentativi++;
                continue;
            }
            
            // Usa sscanf per conversione più robusta
            if (sscanf(buffer, "%f", &valore) != 1) {
                stampa_errore("Formato non valido! Inserisci un numero decimale.");
                tentativi++;
                continue;
            }
            
            if (valore < min || valore > max) {
                printf("❌ Valore fuori range! Inserisci un numero tra %.2f e %.2f.\n", min, max);
                tentativi++;
                continue;
            }
            
            return valore;
        }
        
        stampa_errore("Errore di lettura!");
        tentativi++;
    }
    
    printf("🚫 Troppi tentativi falliti. Uso valore predefinito: %.2f\n", min);
    return min;
}

/**
 * Legge un carattere da una lista di caratteri validi
 */
char leggi_carattere_validato(const char* prompt, const char* caratteri_validi) {
    char buffer[MAX_INPUT_LENGTH];
    int tentativi = 0;
    
    while (tentativi < MAX_TENTATIVI) {
        printf("%s", prompt);
        
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = 0;
            
            if (strlen(buffer) != 1) {
                stampa_errore("Inserisci un solo carattere!");
                tentativi++;
                continue;
            }
            
            char c = buffer[0];
            if (strchr(caratteri_validi, c) != NULL) {
                return c;
            }
            
            printf("❌ Carattere non valido! Caratteri ammessi: %s\n", caratteri_validi);
            tentativi++;
        }
    }
    
    printf("🚫 Troppi tentativi falliti. Uso primo carattere valido: %c\n", caratteri_validi[0]);
    return caratteri_validi[0];
}

/**
 * Legge una stringa con validazione lunghezza
 */
bool leggi_stringa_validata(char* buffer, int max_len, const char* prompt) {
    printf("%s", prompt);
    
    if (fgets(buffer, max_len, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;  // Rimuovi newline
        
        if (strlen(buffer) == 0) {
            stampa_errore("Input vuoto!");
            return false;
        }
        
        return true;
    }
    
    stampa_errore("Errore di lettura!");
    return false;
}

/**
 * Legge e valida un'email
 */
bool leggi_email_validata(char* email, int max_len) {
    if (leggi_stringa_validata(email, max_len, "   Email: ")) {
        return is_email_valida(email);
    }
    return false;
}

/**
 * Legge e valida un numero di telefono
 */
bool leggi_telefono_validato(char* telefono, int max_len) {
    if (leggi_stringa_validata(telefono, max_len, "   Telefono: ")) {
        return is_telefono_valido(telefono);
    }
    return false;
}

/**
 * Legge e valida una password
 */
bool leggi_password_validata(char* password, int max_len) {
    printf("   Password: ");
    
    // In un programma reale, useresti funzioni per nascondere l'input
    if (fgets(password, max_len, stdin) != NULL) {
        password[strcspn(password, "\n")] = 0;
        return is_password_sicura(password);
    }
    
    return false;
}

/**
 * Legge e valida una data
 */
bool leggi_data_validata(Data* data) {
    char buffer[20];
    int tentativi = 0;
    
    while (tentativi < MAX_TENTATIVI) {
        printf("   Data (gg/mm/aaaa): ");
        
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = 0;
            
            if (sscanf(buffer, "%d/%d/%d", &data->giorno, &data->mese, &data->anno) == 3) {
                if (is_data_valida(data->giorno, data->mese, data->anno)) {
                    return true;
                } else {
                    stampa_errore("Data non valida!");
                }
            } else {
                stampa_errore("Formato non valido! Usa: gg/mm/aaaa");
            }
        }
        
        tentativi++;
    }
    
    return false;
}

// ===== FUNZIONI DI UTILITÀ =====

/**
 * Pulisce il buffer di input
 */
void pulisci_buffer_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Stampa separatore con titolo
 */
void stampa_separatore(const char* titolo) {
    printf("═══════════════════════════════════════════════════════════════\n");
    printf("🔹 %s\n", titolo);
    printf("═══════════════════════════════════════════════════════════════\n");
}

/**
 * Stampa messaggio di errore
 */
void stampa_errore(const char* messaggio) {
    printf("❌ ERRORE: %s\n", messaggio);
}

/**
 * Stampa messaggio di successo
 */
void stampa_successo(const char* messaggio) {
    printf("✅ %s\n", messaggio);
}

/**
 * Verifica se un'email è valida (controllo basilare)
 */
bool is_email_valida(const char* email) {
    // Controlli base per email
    int len = strlen(email);
    if (len < 5 || len > 100) return false;  // Lunghezza ragionevole
    
    int at_count = 0;
    int dot_count = 0;
    int at_pos = -1;
    int last_dot_pos = -1;
    
    for (int i = 0; i < len; i++) {
        if (email[i] == '@') {
            at_count++;
            at_pos = i;
        } else if (email[i] == '.') {
            dot_count++;
            last_dot_pos = i;
        }
    }
    
    // Deve avere esattamente una @
    if (at_count != 1) return false;
    
    // @ non deve essere all'inizio o alla fine
    if (at_pos == 0 || at_pos == len - 1) return false;
    
    // Deve avere almeno un punto dopo @
    if (last_dot_pos <= at_pos) return false;
    
    // Deve avere almeno un carattere tra @ e ultimo punto
    if (last_dot_pos - at_pos < 2) return false;
    
    // Deve avere almeno 2 caratteri dopo l'ultimo punto
    if (len - last_dot_pos < 3) return false;
    
    return true;
}

/**
 * Verifica se un telefono è valido
 */
bool is_telefono_valido(const char* telefono) {
    int len = strlen(telefono);
    if (len < 8 || len > 20) return false;
    
    int cifre = 0;
    for (int i = 0; i < len; i++) {
        if (isdigit(telefono[i])) {
            cifre++;
        } else if (telefono[i] != ' ' && telefono[i] != '-' && 
                   telefono[i] != '+' && telefono[i] != '(' && telefono[i] != ')') {
            return false;  // Caratteri non permessi
        }
    }
    
    return cifre >= 8 && cifre <= 15;  // Numero ragionevole di cifre
}

/**
 * Verifica se una password è sicura
 */
bool is_password_sicura(const char* password) {
    int len = strlen(password);
    
    if (len < MIN_PASSWORD_LENGTH || len > MAX_PASSWORD_LENGTH) {
        return false;
    }
    
    bool ha_maiuscola = false;
    bool ha_minuscola = false;
    bool ha_numero = false;
    bool ha_speciale = false;
    
    for (int i = 0; i < len; i++) {
        if (isupper(password[i])) ha_maiuscola = true;
        else if (islower(password[i])) ha_minuscola = true;
        else if (isdigit(password[i])) ha_numero = true;
        else ha_speciale = true;
    }
    
    // Deve avere almeno 3 dei 4 tipi di caratteri
    int tipi = ha_maiuscola + ha_minuscola + ha_numero + ha_speciale;
    return tipi >= 3;
}

/**
 * Verifica se una data è valida
 */
bool is_data_valida(int giorno, int mese, int anno) {
    if (anno < 1900 || anno > 2100) return false;
    if (mese < 1 || mese > 12) return false;
    if (giorno < 1) return false;
    
    int giorni_mese[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Aggiusta febbraio per anni bisestili
    if (is_anno_bisestile(anno)) {
        giorni_mese[1] = 29;
    }
    
    return giorno <= giorni_mese[mese - 1];
}

/**
 * Verifica se un anno è bisestile
 */
bool is_anno_bisestile(int anno) {
    return (anno % 4 == 0 && anno % 100 != 0) || (anno % 400 == 0);
}

/**
 * Mostra i requisiti per la password
 */
void mostra_requisiti_password(void) {
    printf("   📋 Requisiti password:\n");
    printf("      • Lunghezza: %d-%d caratteri\n", MIN_PASSWORD_LENGTH, MAX_PASSWORD_LENGTH);
    printf("      • Almeno 3 di questi tipi:\n");
    printf("        - Lettere maiuscole (A-Z)\n");
    printf("        - Lettere minuscole (a-z)\n");
    printf("        - Numeri (0-9)\n");
    printf("        - Caratteri speciali (!@#$%^&*)\n");
}
