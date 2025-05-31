/**
 * ESEMPIO 3: Manipolazione Bit a Bit
 * 
 * Questo programma dimostra l'uso degli operatori bit a bit
 * in applicazioni pratiche come permessi, flags e ottimizzazioni.
 */

#include <stdio.h>
#include <stdint.h>

// 🏷️ Definizione flag per permessi (come sistema UNIX)
#define PERM_READ    0x04  // 100 in binario
#define PERM_WRITE   0x02  // 010 in binario  
#define PERM_EXECUTE 0x01  // 001 in binario

// 🎮 Flag per stati del gioco
#define GAME_PAUSED     0x01  // 00000001
#define GAME_SOUND_ON   0x02  // 00000010
#define GAME_HARD_MODE  0x04  // 00000100
#define GAME_ONLINE     0x08  // 00001000

// Funzione per stampare rappresentazione binaria
void stampa_binario(unsigned int num, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0 && i > 0) printf(" ");
    }
}

int main() {
    // 🏷️ Intestazione del programma
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                MANIPOLAZIONE BIT A BIT                    ║\n");
    printf("║              Operatori & | ^ ~ << >>                     ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    // 📊 Operazioni base bit a bit
    printf("🔢 OPERAZIONI BIT A BIT FONDAMENTALI:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    uint8_t a = 12;  // 00001100 in binario
    uint8_t b = 10;  // 00001010 in binario
    
    printf("🔸 Valori iniziali:\n");
    printf("  a = %3d = ", a);
    stampa_binario(a, 8);
    printf("\n");
    printf("  b = %3d = ", b);
    stampa_binario(b, 8);
    printf("\n\n");
    
    // AND bit a bit (&)
    uint8_t and_result = a & b;
    printf("🔸 AND bit a bit (a & b):\n");
    printf("  %3d = ", and_result);
    stampa_binario(and_result, 8);
    printf(" ← bit 1 solo se entrambi 1\n");
    
    // OR bit a bit (|)
    uint8_t or_result = a | b;
    printf("🔸 OR bit a bit (a | b):\n");
    printf("  %3d = ", or_result);
    stampa_binario(or_result, 8);
    printf(" ← bit 1 se almeno uno è 1\n");
    
    // XOR bit a bit (^)
    uint8_t xor_result = a ^ b;
    printf("🔸 XOR bit a bit (a ^ b):\n");
    printf("  %3d = ", xor_result);
    stampa_binario(xor_result, 8);
    printf(" ← bit 1 se diversi\n");
    
    // NOT bit a bit (~)
    uint8_t not_a = ~a;
    printf("🔸 NOT bit a bit (~a):\n");
    printf("  %3d = ", not_a);
    stampa_binario(not_a, 8);
    printf(" ← inverte tutti i bit\n");
    
    // Shift a sinistra (<<)
    uint8_t left_shift = a << 2;
    printf("🔸 Shift sinistro (a << 2):\n");
    printf("  %3d = ", left_shift);
    stampa_binario(left_shift, 8);
    printf(" ← sposta 2 posizioni sx\n");
    
    // Shift a destra (>>)
    uint8_t right_shift = a >> 2;
    printf("🔸 Shift destro (a >> 2):\n");
    printf("  %3d = ", right_shift);
    stampa_binario(right_shift, 8);
    printf(" ← sposta 2 posizioni dx\n");
    
    // 🔐 Sistema permessi (come UNIX)
    printf("\n🔐 SISTEMA PERMESSI (stile UNIX):\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    uint8_t permessi_utente = 0;  // Nessun permesso inizialmente
    
    printf("🔸 Stato iniziale: ");
    stampa_binario(permessi_utente, 8);
    printf(" (nessun permesso)\n");
    
    // Assegnazione permessi (OR per settare bit)
    permessi_utente |= PERM_READ;
    printf("🔸 Aggiungi lettura: ");
    stampa_binario(permessi_utente, 8);
    printf(" (può leggere)\n");
    
    permessi_utente |= PERM_WRITE;
    printf("🔸 Aggiungi scrittura: ");
    stampa_binario(permessi_utente, 8);
    printf(" (può leggere e scrivere)\n");
    
    permessi_utente |= PERM_EXECUTE;
    printf("🔸 Aggiungi esecuzione: ");
    stampa_binario(permessi_utente, 8);
    printf(" (tutti i permessi)\n");
    
    // Verifica permessi (AND per testare bit)
    printf("\n🔍 VERIFICA PERMESSI:\n");
    printf("  Può leggere? %s\n", (permessi_utente & PERM_READ) ? "✅ SÌ" : "❌ NO");
    printf("  Può scrivere? %s\n", (permessi_utente & PERM_WRITE) ? "✅ SÌ" : "❌ NO");
    printf("  Può eseguire? %s\n", (permessi_utente & PERM_EXECUTE) ? "✅ SÌ" : "❌ NO");
    
    // Rimozione permessi (AND con NOT per cancellare bit)
    permessi_utente &= ~PERM_WRITE;
    printf("\n🔸 Rimuovi scrittura: ");
    stampa_binario(permessi_utente, 8);
    printf(" (solo lettura ed esecuzione)\n");
    
    printf("  Può scrivere ora? %s\n", (permessi_utente & PERM_WRITE) ? "✅ SÌ" : "❌ NO");
    
    // 🎮 Sistema flags per gioco
    printf("\n🎮 SISTEMA FLAGS PER GIOCO:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    uint8_t game_state = GAME_SOUND_ON | GAME_ONLINE;  // Suono attivo e online
    
    printf("🔸 Stato iniziale gioco: ");
    stampa_binario(game_state, 8);
    printf("\n");
    
    printf("🔍 Verifica stati:\n");
    printf("  Gioco in pausa? %s\n", (game_state & GAME_PAUSED) ? "✅ SÌ" : "❌ NO");
    printf("  Suono attivo? %s\n", (game_state & GAME_SOUND_ON) ? "✅ SÌ" : "❌ NO");
    printf("  Modalità difficile? %s\n", (game_state & GAME_HARD_MODE) ? "✅ SÌ" : "❌ NO");
    printf("  Online? %s\n", (game_state & GAME_ONLINE) ? "✅ SÌ" : "❌ NO");
    
    // Toggle flag (XOR per invertire bit)
    printf("\n🔄 Toggle suono (XOR):\n");
    game_state ^= GAME_SOUND_ON;
    printf("  Suono ora: %s\n", (game_state & GAME_SOUND_ON) ? "🔊 ON" : "🔇 OFF");
    
    game_state ^= GAME_SOUND_ON;  // Toggle di nuovo
    printf("  Suono ora: %s\n", (game_state & GAME_SOUND_ON) ? "🔊 ON" : "🔇 OFF");
    
    // ⚡ Ottimizzazioni con operatori bit
    printf("\n⚡ OTTIMIZZAZIONI CON OPERATORI BIT:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    int numero = 42;
    
    // Verifica se pari o dispari (bit meno significativo)
    printf("🔸 %d è %s (ultimo bit: %d)\n", 
           numero, 
           (numero & 1) ? "dispari" : "pari",
           numero & 1);
    
    // Moltiplicazione per potenze di 2 con shift
    printf("🔸 %d × 4 = %d (shift sinistro di 2)\n", numero, numero << 2);
    printf("🔸 %d ÷ 4 = %d (shift destro di 2)\n", numero, numero >> 2);
    
    // Swap di due numeri con XOR
    int x = 15, y = 25;
    printf("\n🔄 Swap con XOR:\n");
    printf("  Prima: x=%d, y=%d\n", x, y);
    
    x = x ^ y;  // x ora contiene x XOR y
    y = x ^ y;  // y ora contiene x (originale)
    x = x ^ y;  // x ora contiene y (originale)
    
    printf("  Dopo: x=%d, y=%d\n", x, y);
    
    // 💰 Applicazione pratica: compressione dati
    printf("\n💰 COMPRESSIONE SEMPLICE (esempio):\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    // Memorizzare 4 valori da 0-15 in un solo uint16_t
    uint16_t dati_compressi = 0;
    uint8_t val1 = 12, val2 = 5, val3 = 9, val4 = 3;
    
    // Packing (ogni valore usa 4 bit)
    dati_compressi = (val1 << 12) | (val2 << 8) | (val3 << 4) | val4;
    
    printf("🔸 Valori originali: %d, %d, %d, %d\n", val1, val2, val3, val4);
    printf("🔸 Dati compressi: ");
    stampa_binario(dati_compressi, 16);
    printf(" (%d)\n", dati_compressi);
    
    // Unpacking (estrazione dei valori)
    uint8_t estratto1 = (dati_compressi >> 12) & 0x0F;
    uint8_t estratto2 = (dati_compressi >> 8) & 0x0F;
    uint8_t estratto3 = (dati_compressi >> 4) & 0x0F;
    uint8_t estratto4 = dati_compressi & 0x0F;
    
    printf("🔸 Valori estratti: %d, %d, %d, %d\n", estratto1, estratto2, estratto3, estratto4);
    
    // 💡 Note tecniche
    printf("\n💡 NOTE TECNICHE:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("🔸 Shift sinistro (<<) moltiplica per 2^n\n");
    printf("🔸 Shift destro (>>) divide per 2^n (interi)\n");
    printf("🔸 & può essere usato come maschera per isolare bit\n");
    printf("🔸 | può settare bit specifici\n");
    printf("🔸 ^ può invertire/toggle bit specifici\n");
    printf("🔸 ~ inverte tutti i bit (complemento a 1)\n");
    
    // ✅ Messaggio finale
    printf("\n✅ Manipolazione bit completata!\n");
    printf("🚀 Applicazioni: crittografia, compressione, ottimizzazioni!\n");
    
    return 0;
}
