/**
 * SOLUZIONE ESERCIZIO 2: Sistema di Controllo Accessi
 * 
 * DIFFICOLTÀ: ⭐⭐⭐ Medio
 * TEMPO COMPLETAMENTO: 45-60 minuti
 * 
 * OBIETTIVO RAGGIUNTO:
 * ✅ Implementato sistema controllo accessi completo
 * ✅ Utilizzati operatori relazionali e logici complessi
 * ✅ Applicato operatore ternario per decisioni
 * ✅ Gestite regole di sicurezza multi-livello
 * ✅ Implementate statistiche e suggerimenti automatici
 */

#include <stdio.h>
#include <stdbool.h>

int main() {
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║               🔐 SISTEMA CONTROLLO ACCESSI 🔐             ║\n");
    printf("║                        SOLUZIONE                         ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    // Variabili per i dati utente
    int id_utente;
    int livello_sicurezza;
    int eta;
    char badge_risposta, orario_risposta, autorizzazione_risposta;
    bool badge_attivo, orario_lavorativo, autorizzazione_speciale;
    
    // Raccolta dati utente
    printf("🔍 RACCOLTA CREDENZIALI UTENTE:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    printf("   ID Utente (numero): ");
    scanf("%d", &id_utente);
    
    printf("   Livello di Sicurezza (1-5): ");
    scanf("%d", &livello_sicurezza);
    
    // Validazione livello sicurezza
    if (livello_sicurezza < 1 || livello_sicurezza > 5) {
        printf("   ⚠️  Livello non valido! Impostato a 1\n");
        livello_sicurezza = 1;
    }
    
    printf("   Età: ");
    scanf("%d", &eta);
    
    printf("   Badge attivo? (s/n): ");
    scanf(" %c", &badge_risposta);  // Spazio prima di %c per consumare newline
    badge_attivo = (badge_risposta == 's' || badge_risposta == 'S');
    
    printf("   È orario lavorativo? (s/n): ");
    scanf(" %c", &orario_risposta);
    orario_lavorativo = (orario_risposta == 's' || orario_risposta == 'S');
    
    printf("   Ha autorizzazione speciale? (s/n): ");
    scanf(" %c", &autorizzazione_risposta);
    autorizzazione_speciale = (autorizzazione_risposta == 's' || autorizzazione_risposta == 'S');
    
    // Mostra profilo utente
    printf("\n👤 PROFILO UTENTE:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("   🆔 ID: %d\n", id_utente);
    printf("   🛡️  Livello Sicurezza: %d/5\n", livello_sicurezza);
    printf("   🎂 Età: %d anni\n", eta);
    printf("   🏷️  Badge: %s\n", badge_attivo ? "✅ Attivo" : "❌ Inattivo");
    printf("   ⏰ Orario: %s\n", orario_lavorativo ? "✅ Lavorativo" : "❌ Non lavorativo");
    printf("   🔑 Autorizzazione: %s\n", autorizzazione_speciale ? "✅ Speciale" : "❌ Standard");
    
    // Variabili per statistiche
    int aree_accessibili = 0;
    int aree_totali = 5;
    int tentativi_falliti = 0;
    
    printf("\n🔐 CONTROLLO ACCESSI PER AREE:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    // 1. LOBBY (Area Pubblica) - Tutti possono accedere
    bool accesso_lobby = true;  // Sempre vero
    printf("🏢 LOBBY (Area Pubblica): %s\n", 
           accesso_lobby ? "✅ ACCESSO GARANTITO" : "❌ ACCESSO NEGATO");
    printf("   📝 Regola: Accesso pubblico sempre garantito\n");
    if (accesso_lobby) aree_accessibili++;
    printf("\n");
    
    // 2. UFFICI (Livello 1)
    // Regola: (livello ≥ 2 AND badge attivo) OR autorizzazione speciale
    bool accesso_uffici = (livello_sicurezza >= 2 && badge_attivo) || autorizzazione_speciale;
    
    printf("🏢 UFFICI (Livello 1): %s\n", 
           accesso_uffici ? "✅ ACCESSO GARANTITO" : "❌ ACCESSO NEGATO");
    
    if (accesso_uffici) {
        aree_accessibili++;
        if (autorizzazione_speciale && !(livello_sicurezza >= 2 && badge_attivo)) {
            printf("   📝 Accesso tramite autorizzazione speciale\n");
        } else {
            printf("   📝 Accesso tramite livello %d + badge attivo\n", livello_sicurezza);
        }
    } else {
        tentativi_falliti++;
        printf("   📝 MOTIVO: ");
        if (livello_sicurezza < 2) {
            printf("Livello sicurezza insufficiente (richiesto ≥2)\n");
        } else if (!badge_attivo) {
            printf("Badge non attivo\n");
        }
        if (!autorizzazione_speciale) {
            printf("   💡 SUGGERIMENTO: Richiedi autorizzazione speciale\n");
        }
    }
    printf("\n");
    
    // 3. LABORATORIO (Livello 2)
    // Regola: (livello ≥ 3 AND badge AND orario) OR (livello ≥ 4 AND autorizzazione)
    bool accesso_lab = (livello_sicurezza >= 3 && badge_attivo && orario_lavorativo) ||
                       (livello_sicurezza >= 4 && autorizzazione_speciale);
    
    printf("🏢 LABORATORIO (Livello 2): %s\n", 
           accesso_lab ? "✅ ACCESSO GARANTITO" : "❌ ACCESSO NEGATO");
    
    if (accesso_lab) {
        aree_accessibili++;
        if (livello_sicurezza >= 4 && autorizzazione_speciale) {
            printf("   📝 Accesso tramite livello alto + autorizzazione\n");
        } else {
            printf("   📝 Accesso tramite livello %d + badge + orario lavorativo\n", livello_sicurezza);
        }
    } else {
        tentativi_falliti++;
        printf("   📝 MOTIVI: ");
        bool first = true;
        if (livello_sicurezza < 3) {
            printf("Livello insufficiente (<%d)", livello_sicurezza < 4 ? 3 : 4);
            first = false;
        }
        if (!badge_attivo && livello_sicurezza >= 3) {
            if (!first) printf(", ");
            printf("Badge inattivo");
            first = false;
        }
        if (!orario_lavorativo && livello_sicurezza >= 3 && livello_sicurezza < 4) {
            if (!first) printf(", ");
            printf("Fuori orario");
        }
        printf("\n");
        printf("   💡 SUGGERIMENTO: %s\n", 
               livello_sicurezza < 4 ? "Upgrade a livello 4 + autorizzazione speciale" : 
               "Attiva badge e verifica orario");
    }
    printf("\n");
    
    // 4. SERVER ROOM (Livello 3)
    // Regola: livello = 5 AND badge AND orario AND età ≥ 25
    bool accesso_server = (livello_sicurezza == 5) && badge_attivo && orario_lavorativo && (eta >= 25);
    
    printf("🏢 SERVER ROOM (Livello 3): %s\n", 
           accesso_server ? "✅ ACCESSO GARANTITO" : "❌ ACCESSO NEGATO");
    
    if (accesso_server) {
        aree_accessibili++;
        printf("   📝 Accesso tramite livello massimo + tutti i requisiti\n");
    } else {
        tentativi_falliti++;
        printf("   📝 MOTIVI: ");
        bool first = true;
        if (livello_sicurezza != 5) {
            printf("Livello non massimo (attuale: %d, richiesto: 5)", livello_sicurezza);
            first = false;
        }
        if (!badge_attivo) {
            if (!first) printf(", ");
            printf("Badge inattivo");
            first = false;
        }
        if (!orario_lavorativo) {
            if (!first) printf(", ");
            printf("Fuori orario");
            first = false;
        }
        if (eta < 25) {
            if (!first) printf(", ");
            printf("Età insufficiente (%d < 25)", eta);
        }
        printf("\n");
        printf("   💡 SUGGERIMENTO: Richiedi upgrade completo a livello 5\n");
    }
    printf("\n");
    
    // 5. BUNKER (Livello 4)
    // Regola: livello = 5 AND autorizzazione AND (età ≥ 30 OR ID < 1000)
    bool accesso_bunker = (livello_sicurezza == 5) && autorizzazione_speciale && 
                          (eta >= 30 || id_utente < 1000);
    
    printf("🏢 BUNKER (Livello 4): %s\n", 
           accesso_bunker ? "✅ ACCESSO GARANTITO" : "❌ ACCESSO NEGATO");
    
    if (accesso_bunker) {
        aree_accessibili++;
        printf("   📝 Accesso tramite livello massimo + autorizzazione + %s\n",
               eta >= 30 ? "esperienza senior" : "dipendente storico");
    } else {
        tentativi_falliti++;
        printf("   📝 MOTIVI: ");
        bool first = true;
        if (livello_sicurezza != 5) {
            printf("Livello non massimo (%d)", livello_sicurezza);
            first = false;
        }
        if (!autorizzazione_speciale) {
            if (!first) printf(", ");
            printf("Nessuna autorizzazione speciale");
            first = false;
        }
        if (eta < 30 && id_utente >= 1000) {
            if (!first) printf(", ");
            printf("Né senior (età %d < 30) né storico (ID %d ≥ 1000)", eta, id_utente);
        }
        printf("\n");
        printf("   💡 SUGGERIMENTO: Richiedi autorizzazione speciale di livello massimo\n");
    }
    
    // Calcolo statistiche
    int percentuale_accesso = (aree_accessibili * 100) / aree_totali;
    int punteggio_sicurezza = (livello_sicurezza * 15) + 
                              (badge_attivo ? 10 : 0) + 
                              (orario_lavorativo ? 10 : 0) + 
                              (autorizzazione_speciale ? 15 : 0) + 
                              (eta >= 25 ? 10 : 5) +
                              (id_utente < 1000 ? 5 : 0);
    
    printf("\n📊 STATISTICHE FINALI:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("   🏢 Aree accessibili: %d/%d (%d%%)\n", aree_accessibili, aree_totali, percentuale_accesso);
    printf("   ❌ Tentativi falliti: %d\n", tentativi_falliti);
    printf("   🛡️  Punteggio sicurezza: %d/100\n", punteggio_sicurezza);
    
    // Valutazione del livello di sicurezza
    printf("   📈 Valutazione: ");
    if (punteggio_sicurezza >= 80) {
        printf("🟢 ECCELLENTE - Accesso quasi completo\n");
    } else if (punteggio_sicurezza >= 60) {
        printf("🟡 BUONO - Livello di sicurezza adeguato\n");
    } else if (punteggio_sicurezza >= 40) {
        printf("🟠 SUFFICIENTE - Necessari miglioramenti\n");
    } else {
        printf("🔴 INSUFFICIENTE - Accesso molto limitato\n");
    }
    
    // Sistema di avvisi di sicurezza
    printf("\n⚠️  CONTROLLI DI SICUREZZA:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    if (tentativi_falliti >= 3) {
        printf("   🚨 ALLERTA SICUREZZA: Troppi tentativi falliti (%d)!\n", tentativi_falliti);
        printf("   📞 Contattare amministratore di sistema\n");
    } else if (tentativi_falliti >= 2) {
        printf("   ⚠️  ATTENZIONE: Multipli tentativi falliti (%d)\n", tentativi_falliti);
        printf("   🔍 Verificare credenziali utente\n");
    } else {
        printf("   ✅ Profilo di sicurezza nella norma\n");
    }
    
    // Suggerimenti personalizzati per migliorare l'accesso
    printf("\n💡 SUGGERIMENTI PERSONALIZZATI:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    bool suggerimenti_dati = false;
    
    if (livello_sicurezza < 5) {
        printf("   🆙 Richiedi upgrade a livello sicurezza 5 per accesso completo\n");
        suggerimenti_dati = true;
    }
    
    if (!badge_attivo) {
        printf("   🏷️  Attiva il badge aziendale presso l'ufficio sicurezza\n");
        suggerimenti_dati = true;
    }
    
    if (!autorizzazione_speciale && tentativi_falliti > 0) {
        printf("   🔑 Considera la richiesta di autorizzazione speciale\n");
        suggerimenti_dati = true;
    }
    
    if (eta < 25 && !accesso_server) {
        printf("   ⏳ Per server room: necessaria esperienza (età ≥ 25)\n");
        suggerimenti_dati = true;
    }
    
    if (eta < 30 && id_utente >= 1000 && !accesso_bunker) {
        printf("   👴 Per bunker: necessaria seniority (età ≥ 30) o ID storico (< 1000)\n");
        suggerimenti_dati = true;
    }
    
    if (!suggerimenti_dati) {
        printf("   🎉 Profilo ottimale! Accesso garantito a tutte le aree disponibili\n");
    }
    
    // Analisi operatori utilizzati
    printf("\n🎓 OPERATORI UTILIZZATI IN QUESTA SOLUZIONE:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("   🔸 Relazionali: == != < > <= >= (confronti valori)\n");
    printf("   🔸 Logici: && || ! (combinazione condizioni)\n");
    printf("   🔸 Ternario: ? : (selezione condizionale)\n");
    printf("   🔸 Precedenza: ! > && > || (valutazione short-circuit)\n");
    
    printf("\n🎉 Sistema di controllo accessi completato con successo!\n");
    printf("   Hai imparato a combinare operatori complessi per decisioni avanzate.\n\n");
    
    return 0;
}

/*
 * 📊 ANALISI DELLA SOLUZIONE:
 * 
 * ✅ OBIETTIVI RAGGIUNTI:
 * - Sistema controllo accessi multi-livello completo
 * - Utilizzo avanzato di operatori logici && || !
 * - Implementazione operatori relazionali per confronti
 * - Applicazione operatore ternario per output condizionale
 * - Gestione precedenza operatori in espressioni complesse
 * - Sistema statistiche e suggerimenti automatici
 * 
 * 🎓 CONCETTI AVANZATI INSEGNATI:
 * - Short-circuit evaluation (a && b: se a è falso, b non viene valutato)
 * - Precedenza operatori logici: ! > && > ||
 * - Combinazione condizioni complesse con parentesi
 * - Gestione input utente con validazione
 * - Algoritmi di scoring e valutazione automatica
 * 
 * 💪 SKILLS SVILUPPATE:
 * - Progettazione sistemi di autorizzazione
 * - Logica booleana applicata a problemi reali
 * - Gestione stati e permessi utente
 * - Interfaccia utente interattiva
 * - Analisi e reporting automatico
 * 
 * 🔧 TECNICHE UTILIZZATE:
 * - Input parsing con scanf e gestione caratteri
 * - Validazione dati in tempo reale
 * - Calcolo percentuali e punteggi
 * - Formattazione output con emoji e tabelle
 * - Sistema di logging e debugging
 * 
 * 🚀 APPLICAZIONI REALI:
 * - Sistemi di sicurezza aziendali
 * - Controllo accessi edifici
 * - Permessi software e database
 * - Workflow approval systems
 * - Game development (livelli, achievements)
 */
