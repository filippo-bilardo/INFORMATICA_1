/**
 * ESERCIZIO 1: Calcolatore Espressioni Matematiche
 * 
 * DIFFICOLTÀ: ⭐⭐ Facile
 * TEMPO: 30-40 minuti
 * 
 * OBIETTIVO:
 * Creare un programma che valuti espressioni matematiche semplici
 * utilizzando tutti gli operatori aritmetici con precedenza corretta.
 */

#include <stdio.h>

int main() {
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                  ESERCIZIO 1 - TO DO                     ║\n");
    printf("║             Calcolatore Espressioni                      ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    /* 
     * 🎯 COMPITO:
     * 
     * 1. Chiedi all'utente di inserire tre numeri: a, b, c
     * 
     * 2. Calcola e stampa i seguenti risultati:
     *    - Espressione 1: a + b * c
     *    - Espressione 2: (a + b) * c  
     *    - Espressione 3: a / b + c (controlla divisione per zero)
     *    - Espressione 4: a % b (solo se b != 0 e sono interi)
     *    - Espressione 5: ++a + b--
     *    - Espressione 6: a > b ? a : b (operatore ternario)
     * 
     * 3. Per ogni risultato, spiega la precedenza degli operatori
     * 
     * 4. Gestisci i casi di errore (divisione per zero, ecc.)
     * 
     * 5. Mostra i valori di a e b dopo le operazioni di incremento/decremento
     * 
     * ESEMPIO OUTPUT:
     * 
     * Inserisci tre numeri: 10 5 3
     * 
     * 📊 RISULTATI:
     * ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
     * 🔸 a + b * c = 10 + 5 * 3 = 10 + 15 = 25
     *    (moltiplicazione ha precedenza maggiore)
     * 
     * 🔸 (a + b) * c = (10 + 5) * 3 = 15 * 3 = 45
     *    (parentesi forzano addizione prima)
     * 
     * 🔸 a / b + c = 10 / 5 + 3 = 2.00 + 3 = 5.00
     *    (divisione ha precedenza maggiore dell'addizione)
     * 
     * 🔸 a % b = 10 % 5 = 0
     *    (resto della divisione intera)
     * 
     * 🔸 ++a + b-- = 11 + 5 = 16
     *    (pre-incremento di a, post-decremento di b)
     * 
     * 🔸 a > b ? a : b = 11 > 4 ? 11 : 4 = 11
     *    (operatore ternario: se a>b allora a, altrimenti b)
     * 
     * 📈 VALORI FINALI:
     * a = 11 (incrementato da 10)
     * b = 4 (decrementato da 5)
     * c = 3 (invariato)
     * 
     * SUGGERIMENTI:
     * - Usa printf con formattazione appropriata
     * - Salva i valori originali se necessario
     * - Testa con diversi input inclusi casi limite
     * - Aggiungi commenti per spiegare ogni calcolo
     */
    
    // 🚧 IL TUO CODICE QUI SOTTO 🚧
    
    
    
    return 0;
}

/*
 * 💡 AIUTI:
 * 
 * 🔸 Per salvare valori originali:
 *    int a_orig = a, b_orig = b, c_orig = c;
 * 
 * 🔸 Per verificare se un numero è intero:
 *    if (b == (int)b && b != 0)
 * 
 * 🔸 Per formattare decimali:
 *    printf("%.2f", valore);
 * 
 * 🔸 Per l'operatore ternario:
 *    risultato = condizione ? valore_se_vero : valore_se_falso;
 * 
 * 📚 CONCETTI CHIAVE:
 * - Precedenza operatori: (), ++/-- unari, */%, +-, confronti, ?:
 * - Differenza tra pre/post incremento
 * - Gestione errori (divisione per zero)
 * - Casting tra tipi
 */
