/**
 * ESERCIZIO 2: Sistema di Controllo Accessi
 * 
 * DIFFICOLTÀ: ⭐⭐⭐ Medio
 * TEMPO: 45-60 minuti
 * 
 * OBIETTIVO:
 * Implementare un sistema di controllo accessi usando operatori
 * relazionali, logici e l'operatore ternario per decisioni complesse.
 */

#include <stdio.h>
#include <stdbool.h>

int main() {
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                  ESERCIZIO 2 - TO DO                     ║\n");
    printf("║              Sistema Controllo Accessi                   ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    /* 
     * 🎯 COMPITO:
     * 
     * Crea un sistema che controlli l'accesso a diverse aree di un edificio
     * basandosi su credenziali utente e regole di sicurezza.
     * 
     * 📋 REQUISITI:
     * 
     * 1. RACCOLTA DATI UTENTE:
     *    - ID utente (numero intero)
     *    - Livello di sicurezza (1-5)
     *    - Età dell'utente
     *    - Ha badge attivo? (s/n)
     *    - È in orario lavorativo? (s/n)
     *    - Ha autorizzazione speciale? (s/n)
     * 
     * 2. AREE DA CONTROLLARE (con regole):
     *    
     *    🏢 LOBBY (Area Pubblica):
     *    - Tutti possono accedere sempre
     *    
     *    🏢 UFFICI (Livello 1):
     *    - Livello sicurezza ≥ 2 AND badge attivo
     *    - OPPURE autorizzazione speciale
     *    
     *    🏢 LABORATORIO (Livello 2):
     *    - Livello sicurezza ≥ 3 AND badge attivo AND orario lavorativo
     *    - OPPURE (livello ≥ 4 AND autorizzazione speciale)
     *    
     *    🏢 SERVER ROOM (Livello 3):
     *    - Livello sicurezza = 5 AND badge attivo AND orario lavorativo
     *    - AND età ≥ 25 (per esperienza)
     *    
     *    🏢 BUNKER (Livello 4):
     *    - Livello sicurezza = 5 AND autorizzazione speciale
     *    - AND (età ≥ 30 OR ID < 1000) # Manager senior o dipendenti storici
     * 
     * 3. OUTPUT RICHIESTO:
     *    - Mostra profilo utente
     *    - Per ogni area, indica se l'accesso è garantito
     *    - Spiega il motivo del diniego (se applicabile)
     *    - Calcola un punteggio di sicurezza complessivo
     * 
     * 4. FUNZIONALITÀ EXTRA:
     *    - Contatore tentativi di accesso falliti
     *    - Avviso di sicurezza se troppi tentativi falliti
     *    - Suggerimenti per ottenere l'accesso
     * 
     * ESEMPIO OUTPUT:
     * 
     * ID Utente: 1250
     * Livello Sicurezza: 4
     * Età: 28
     * Badge Attivo: Sì
     * Orario Lavorativo: Sì  
     * Autorizzazione Speciale: No
     * 
     * 🔐 CONTROLLO ACCESSI:
     * ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
     * 🏢 LOBBY: ✅ ACCESSO GARANTITO (area pubblica)
     * 🏢 UFFICI: ✅ ACCESSO GARANTITO (livello ≥ 2 + badge)
     * 🏢 LABORATORIO: ✅ ACCESSO GARANTITO (livello ≥ 3 + badge + orario)
     * 🏢 SERVER ROOM: ❌ ACCESSO NEGATO (richiede livello 5)
     * 🏢 BUNKER: ❌ ACCESSO NEGATO (richiede livello 5 + autorizzazione)
     * 
     * 📊 STATISTICHE:
     * Aree accessibili: 3/5
     * Tentativi falliti: 2
     * Punteggio sicurezza: 75/100
     * 
     * 💡 SUGGERIMENTI:
     * - Richiedi upgrade a livello 5 per server room
     * - Ottieni autorizzazione speciale per bunker
     */
    
    // 🚧 IL TUO CODICE QUI SOTTO 🚧
    
    
    
    return 0;
}

/*
 * 💡 AIUTI TECNICI:
 * 
 * 🔸 Per leggere carattere:
 *    char risposta;
 *    scanf(" %c", &risposta);  // Nota lo spazio prima di %c
 *    bool valore = (risposta == 's' || risposta == 'S');
 * 
 * 🔸 Per operatori logici complessi:
 *    bool condizione = (A && B) || (C && D);
 * 
 * 🔸 Per contare accessi:
 *    int accessi_ok = 0, accessi_totali = 5;
 *    if (accesso_garantito) accessi_ok++;
 * 
 * 🔸 Per calcolare percentuale:
 *    int percentuale = (accessi_ok * 100) / accessi_totali;
 * 
 * 📚 CONCETTI FOCUS:
 * - Operatori logici: && || !
 * - Precedenza: ! > && > ||
 * - Short-circuit evaluation
 * - Operatori relazionali: == != < > <= >=
 * - Operatore ternario per output condizionale
 * - Combinazione condizioni complesse
 */
