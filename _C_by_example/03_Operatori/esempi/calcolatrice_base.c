/**
 * ESEMPIO 1: Calcolatrice Base con Operatori Aritmetici
 * 
 * Questo programma dimostra l'uso di tutti gli operatori aritmetici
 * fondamentali del linguaggio C con gestione degli errori.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    // 🏷️ Intestazione del programma
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                  CALCOLATRICE BASE                       ║\n");
    printf("║              Operatori Aritmetici in C                   ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    // 📊 Dichiarazione variabili
    double num1, num2;
    int scelta;
    double risultato;
    
    // 📥 Input dei numeri
    printf("🔢 Inserisci il primo numero: ");
    scanf("%lf", &num1);
    
    printf("🔢 Inserisci il secondo numero: ");
    scanf("%lf", &num2);
    
    // 📋 Menu operazioni
    printf("\n🧮 SELEZIONA L'OPERAZIONE:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("1️⃣  Addizione (+)\n");
    printf("2️⃣  Sottrazione (-)\n");
    printf("3️⃣  Moltiplicazione (*)\n");
    printf("4️⃣  Divisione (/)\n");
    printf("5️⃣  Modulo (%% - solo interi)\n");
    printf("6️⃣  Potenza (simulata)\n");
    printf("7️⃣  Tutte le operazioni\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("Inserisci la tua scelta (1-7): ");
    scanf("%d", &scelta);
    
    printf("\n📊 RISULTATI:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    switch(scelta) {
        case 1: // Addizione
            risultato = num1 + num2;
            printf("➕ %.2f + %.2f = %.2f\n", num1, num2, risultato);
            break;
            
        case 2: // Sottrazione
            risultato = num1 - num2;
            printf("➖ %.2f - %.2f = %.2f\n", num1, num2, risultato);
            break;
            
        case 3: // Moltiplicazione
            risultato = num1 * num2;
            printf("✖️  %.2f × %.2f = %.2f\n", num1, num2, risultato);
            break;
            
        case 4: // Divisione
            if (num2 != 0) {
                risultato = num1 / num2;
                printf("➗ %.2f ÷ %.2f = %.2f\n", num1, num2, risultato);
            } else {
                printf("❌ ERRORE: Divisione per zero non permessa!\n");
            }
            break;
            
        case 5: // Modulo (solo per interi)
            if ((int)num2 != 0) {
                int mod_result = (int)num1 % (int)num2;
                printf("🔢 %d %% %d = %d\n", (int)num1, (int)num2, mod_result);
                printf("💡 Nota: Il modulo funziona solo con interi\n");
            } else {
                printf("❌ ERRORE: Modulo per zero non permesso!\n");
            }
            break;
            
        case 6: // Potenza (simulata con moltiplicazioni)
            if (num2 >= 0 && num2 == (int)num2 && num2 <= 10) {
                risultato = 1;
                for(int i = 0; i < (int)num2; i++) {
                    risultato *= num1;
                }
                printf("🔺 %.2f^%.0f = %.2f\n", num1, num2, risultato);
                printf("💡 Nota: Implementata con moltiplicazioni iterative\n");
            } else {
                printf("❌ ERRORE: Esponente deve essere intero positivo ≤ 10\n");
            }
            break;
            
        case 7: // Tutte le operazioni
            printf("🔸 TUTTE LE OPERAZIONI:\n");
            printf("  ➕ %.2f + %.2f = %.2f\n", num1, num2, num1 + num2);
            printf("  ➖ %.2f - %.2f = %.2f\n", num1, num2, num1 - num2);
            printf("  ✖️  %.2f × %.2f = %.2f\n", num1, num2, num1 * num2);
            
            if (num2 != 0) {
                printf("  ➗ %.2f ÷ %.2f = %.2f\n", num1, num2, num1 / num2);
            } else {
                printf("  ➗ %.2f ÷ %.2f = ❌ (divisione per zero)\n", num1, num2);
            }
            
            if ((int)num2 != 0) {
                printf("  🔢 %d %% %d = %d\n", (int)num1, (int)num2, (int)num1 % (int)num2);
            } else {
                printf("  🔢 %d %% %d = ❌ (modulo per zero)\n", (int)num1, (int)num2);
            }
            break;
            
        default:
            printf("❌ ERRORE: Scelta non valida!\n");
            return 1;
    }
    
    // 🔍 Analisi aggiuntiva per operatori di incremento/decremento
    if (scelta >= 1 && scelta <= 7) {
        printf("\n🔄 DIMOSTRAZIONE INCREMENTO/DECREMENTO:\n");
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        
        int valore = 10;
        printf("🔸 Valore iniziale: %d\n", valore);
        printf("🔸 Pre-incremento (++valore): %d\n", ++valore);  // valore diventa 11
        printf("🔸 Post-incremento (valore++): %d\n", valore++); // stampa 11, valore diventa 12
        printf("🔸 Valore dopo post-incremento: %d\n", valore);  // 12
        printf("🔸 Pre-decremento (--valore): %d\n", --valore);  // valore diventa 11
        printf("🔸 Post-decremento (valore--): %d\n", valore--); // stampa 11, valore diventa 10
        printf("🔸 Valore finale: %d\n", valore);                // 10
    }
    
    // 💡 Suggerimenti e note
    printf("\n💡 NOTE IMPORTANTI:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("🔸 La divisione tra interi tronca il risultato (es: 7/3 = 2)\n");
    printf("🔸 Il modulo (%) funziona solo con numeri interi\n");
    printf("🔸 Pre-incremento (++i) modifica prima, post-incremento (i++) dopo\n");
    printf("🔸 Attenzione alla precedenza: 2 + 3 * 4 = 14, non 20\n");
    printf("🔸 Usa parentesi per chiarire: (2 + 3) * 4 = 20\n");
    
    // ✅ Messaggio finale
    printf("\n✅ Operazioni completate con successo!\n");
    printf("🚀 Prossimo step: Studia gli operatori relazionali e logici!\n");
    
    return 0;
}
