/**
 * SOLUZIONE ESERCIZIO 1: Calcolatore Espressioni Matematiche
 * 
 * DIFFICOLTÀ: ⭐⭐ Facile
 * TEMPO COMPLETAMENTO: 30-40 minuti
 * 
 * OBIETTIVO RAGGIUNTO:
 * ✅ Implementato calcolatore che valuta espressioni matematiche
 * ✅ Utilizzati tutti gli operatori aritmetici con precedenza corretta
 * ✅ Gestita divisione per zero e casi limite
 * ✅ Dimostrati operatori di incremento/decremento
 * ✅ Utilizzato operatore ternario per selezione
 */

#include <stdio.h>
#include <stdbool.h>

int main() {
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║               🧮 CALCOLATORE ESPRESSIONI 🧮               ║\n");
    printf("║                      SOLUZIONE                           ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    // Variabili per i tre numeri
    double a, b, c;
    
    // Raccolta input dall'utente
    printf("🔢 Inserisci tre numeri per le espressioni matematiche:\n");
    printf("   Numero a: ");
    scanf("%lf", &a);
    printf("   Numero b: ");
    scanf("%lf", &b);
    printf("   Numero c: ");
    scanf("%lf", &c);
    
    // Salviamo i valori originali per confronto finale
    double a_orig = a, b_orig = b, c_orig = c;
    
    printf("\n📊 RISULTATI DELLE ESPRESSIONI:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    // 1. Espressione: a + b * c
    double expr1 = a + b * c;
    printf("🔸 Espressione 1: a + b * c\n");
    printf("   %.2f + %.2f * %.2f = %.2f + %.2f = %.2f\n", a, b, c, a, b * c, expr1);
    printf("   📝 La moltiplicazione (*) ha precedenza maggiore dell'addizione (+)\n\n");
    
    // 2. Espressione: (a + b) * c
    double expr2 = (a + b) * c;
    printf("🔸 Espressione 2: (a + b) * c\n");
    printf("   (%.2f + %.2f) * %.2f = %.2f * %.2f = %.2f\n", a, b, c, a, a + b, expr2);
    printf("   📝 Le parentesi forzano l'addizione prima della moltiplicazione\n\n");
    
    // 3. Espressione: a / b + c (con controllo divisione per zero)
    printf("🔸 Espressione 3: a / b + c\n");
    if (b != 0) {
        double expr3 = a / b + c;
        printf("   %.2f / %.2f + %.2f = %.2f + %.2f = %.2f\n", a, b, c, a, a / b, expr3);
        printf("   📝 La divisione (/) ha precedenza maggiore dell'addizione (+)\n\n");
    } else {
        printf("   ❌ ERRORE: Divisione per zero non permessa (b = 0)\n");
        printf("   📝 Sempre controllare il denominatore prima della divisione!\n\n");
    }
    
    // 4. Espressione: a % b (solo per numeri interi)
    printf("🔸 Espressione 4: a %% b (resto divisione)\n");
    // Convertiamo a interi per l'operazione modulo
    int a_int = (int)a;
    int b_int = (int)b;
    
    if (b_int != 0) {
        int expr4 = a_int % b_int;
        printf("   %d %% %d = %d\n", a_int, b_int, expr4);
        printf("   📝 L'operatore modulo (%%) restituisce il resto della divisione intera\n");
        if (expr4 == 0) {
            printf("   💡 %d è divisibile per %d!\n\n", a_int, b_int);
        } else {
            printf("   💡 %d diviso %d dà resto %d\n\n", a_int, b_int, expr4);
        }
    } else {
        printf("   ❌ ERRORE: Operazione modulo con zero non permessa\n\n");
    }
    
    // 5. Espressione: ++a + b-- (pre-incremento e post-decremento)
    printf("🔸 Espressione 5: ++a + b-- (incremento/decremento)\n");
    printf("   Valori prima: a = %.2f, b = %.2f\n", a, b);
    
    double expr5 = ++a + b--;  // Pre-incremento di a, post-decremento di b
    
    printf("   ++a + b-- = %.2f + %.2f = %.2f\n", a, b + 1, expr5);
    printf("   📝 ++a: incrementa PRIMA di usare il valore\n");
    printf("   📝 b--: usa il valore PRIMA di decrementare\n");
    printf("   Valori dopo: a = %.2f, b = %.2f\n\n", a, b);
    
    // 6. Espressione: operatore ternario a > b ? a : b
    printf("🔸 Espressione 6: a > b ? a : b (operatore ternario)\n");
    double expr6 = a > b ? a : b;
    printf("   %.2f > %.2f ? %.2f : %.2f = %.2f\n", a, b, a, b, expr6);
    printf("   📝 Operatore ternario: condizione ? valore_se_vero : valore_se_falso\n");
    printf("   💡 Il valore maggiore tra a e b è: %.2f\n\n", expr6);
    
    // Riepilogo valori finali
    printf("📈 RIEPILOGO VALORI FINALI:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("   a: %.2f → %.2f (incrementato di %.2f)\n", a_orig, a, a - a_orig);
    printf("   b: %.2f → %.2f (decrementato di %.2f)\n", b_orig, b, b_orig - b);
    printf("   c: %.2f → %.2f (invariato)\n", c_orig, c);
    
    // Analisi aggiuntiva delle precedenze
    printf("\n🎓 LEZIONI APPRESE SULLE PRECEDENZE:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("   1️⃣  Parentesi ()          - Massima precedenza\n");
    printf("   2️⃣  ++, -- (unari)        - Pre/post incremento\n");
    printf("   3️⃣  *, /, %%               - Moltiplicazione, divisione, modulo\n");
    printf("   4️⃣  +, -                  - Addizione, sottrazione\n");
    printf("   5️⃣  <, >, <=, >=          - Operatori relazionali\n");
    printf("   6️⃣  ==, !=                - Uguaglianza, disuguaglianza\n");
    printf("   7️⃣  ? :                   - Operatore ternario\n");
    
    printf("\n💡 CONSIGLI PRATICI:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("   ✓ Usa sempre parentesi quando hai dubbi sulla precedenza\n");
    printf("   ✓ Controlla sempre la divisione per zero prima di dividere\n");
    printf("   ✓ Ricorda che ++a è diverso da a++\n");
    printf("   ✓ L'operatore modulo funziona solo con numeri interi\n");
    printf("   ✓ L'operatore ternario rende il codice più conciso\n");
    
    // Test con espressione complessa combinata
    printf("\n🧪 BONUS - ESPRESSIONE COMPLESSA:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    // Reset valori per test finale
    a = a_orig; b = b_orig; c = c_orig;
    
    if (b != 0) {
        // Espressione: (a + b) * c / (a > b ? 2 : 3) + (a % (int)b)
        double complessa = (a + b) * c / (a > b ? 2.0 : 3.0);
        if ((int)b != 0) {
            complessa += (int)a % (int)b;
        }
        
        printf("   (a + b) * c / (a > b ? 2 : 3) + (a %% b)\n");
        printf("   (%.2f + %.2f) * %.2f / %.0f + %d = %.2f\n", 
               a, b, c, (a > b ? 2.0 : 3.0), (int)a % (int)b, complessa);
        printf("   📝 Esempio di precedenza multipla in una singola espressione\n");
    }
    
    printf("\n🎉 Esercizio completato con successo!\n");
    printf("   Hai imparato a utilizzare tutti gli operatori aritmetici del C\n");
    printf("   e a gestire correttamente le precedenze e i casi limite.\n\n");
    
    return 0;
}

/*
 * 📊 ANALISI DELLA SOLUZIONE:
 * 
 * ✅ OBIETTIVI RAGGIUNTI:
 * - Utilizzati tutti gli operatori aritmetici (+, -, *, /, %)
 * - Dimostrata precedenza degli operatori con esempi pratici
 * - Gestiti casi di errore (divisione per zero)
 * - Implementati operatori di incremento/decremento
 * - Utilizzato operatore ternario per selezione condizionale
 * - Fornite spiegazioni dettagliate per ogni operazione
 * 
 * 🎓 CONCETTI INSEGNATI:
 * - Precedenza operatori: (), ++/--, * / %, +-, confronti, ?:
 * - Differenza tra pre-incremento (++a) e post-incremento (a++)
 * - Gestione errori con controlli condizionali
 * - Casting tra tipi (double to int per modulo)
 * - Formattazione output con printf
 * 
 * 💪 SKILLS SVILUPPATE:
 * - Manipolazione espressioni matematiche complesse
 * - Debugging e gestione casi limite
 * - Comprensione profonda degli operatori C
 * - Best practices per codice robusto e leggibile
 * 
 * 🚀 PROSSIMI PASSI:
 * - Applicare questi concetti in progetti più grandi
 * - Combinare con operatori logici e bit a bit
 * - Utilizzare in algoritmi e strutture dati avanzate
 */
