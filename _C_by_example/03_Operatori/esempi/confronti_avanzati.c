/**
 * ESEMPIO 2: Confronti Avanzati e Logica Booleana
 * 
 * Questo programma dimostra l'uso degli operatori relazionali e logici
 * in situazioni pratiche con validazione avanzata.
 */

#include <stdio.h>
#include <stdbool.h>

int main() {
    // 🏷️ Intestazione del programma
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║              CONFRONTI E LOGICA AVANZATA                 ║\n");
    printf("║            Operatori Relazionali e Logici                ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    // 📊 Sistema di valutazione studente
    printf("🎓 SISTEMA DI VALUTAZIONE STUDENTE\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    int voto_matematica, voto_italiano, voto_inglese;
    int assenze;
    bool ha_recuperato_debiti;
    char risposta;
    
    // 📥 Input dati studente
    printf("📚 Inserisci i voti (0-10):\n");
    printf("  Matematica: ");
    scanf("%d", &voto_matematica);
    printf("  Italiano: ");
    scanf("%d", &voto_italiano);
    printf("  Inglese: ");
    scanf("%d", &voto_inglese);
    
    printf("\n📅 Inserisci il numero di assenze: ");
    scanf("%d", &assenze);
    
    printf("\n💯 Ha recuperato tutti i debiti? (s/n): ");
    scanf(" %c", &risposta);
    ha_recuperato_debiti = (risposta == 's' || risposta == 'S');
    
    // 🧮 Calcoli e analisi
    double media = (voto_matematica + voto_italiano + voto_inglese) / 3.0;
    
    printf("\n📊 ANALISI PRESTAZIONI:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    // 🔍 Operatori relazionali
    printf("🔸 CONFRONTI INDIVIDUALI:\n");
    printf("  Matematica %s sufficiente (%d %s 6)\n", 
           (voto_matematica >= 6) ? "✅" : "❌",
           voto_matematica,
           (voto_matematica >= 6) ? "≥" : "<");
    
    printf("  Italiano %s sufficiente (%d %s 6)\n", 
           (voto_italiano >= 6) ? "✅" : "❌",
           voto_italiano,
           (voto_italiano >= 6) ? "≥" : "<");
    
    printf("  Inglese %s sufficiente (%d %s 6)\n", 
           (voto_inglese >= 6) ? "✅" : "❌",
           voto_inglese,
           (voto_inglese >= 6) ? "≥" : "<");
    
    printf("  Media: %.2f\n", media);
    printf("  Assenze: %d (limite: 50)\n", assenze);
    
    // 🔗 Operatori logici complessi
    printf("\n🔸 ANALISI CON OPERATORI LOGICI:\n");
    
    // AND logico - tutte le condizioni devono essere vere
    bool tutti_sufficienti = (voto_matematica >= 6) && (voto_italiano >= 6) && (voto_inglese >= 6);
    printf("  Tutti i voti sufficienti: %s\n", tutti_sufficienti ? "✅ SÌ" : "❌ NO");
    
    // OR logico - almeno una condizione deve essere vera
    bool almeno_uno_eccellente = (voto_matematica >= 9) || (voto_italiano >= 9) || (voto_inglese >= 9);
    printf("  Almeno un voto eccellente (≥9): %s\n", almeno_uno_eccellente ? "✅ SÌ" : "❌ NO");
    
    // NOT logico
    bool poche_assenze = !(assenze > 50);
    printf("  Assenze accettabili (≤50): %s\n", poche_assenze ? "✅ SÌ" : "❌ NO");
    
    // Combinazioni complesse
    bool promosso = tutti_sufficienti && poche_assenze && ha_recuperato_debiti;
    printf("  PROMOSSO: %s\n", promosso ? "🎉 SÌ" : "💔 NO");
    
    // 🎯 Short-circuit evaluation
    printf("\n🔸 DIMOSTRAZIONE SHORT-CIRCUIT EVALUATION:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    int x = 5, y = 0;
    
    // AND: se la prima condizione è falsa, la seconda non viene valutata
    printf("🔸 AND Short-circuit: ");
    if ((x > 10) && (++y > 0)) {
        printf("Condizione vera\n");
    } else {
        printf("Condizione falsa (y non incrementato: %d)\n", y);
    }
    
    // OR: se la prima condizione è vera, la seconda non viene valutata
    y = 0; // reset
    printf("🔸 OR Short-circuit: ");
    if ((x > 0) || (++y > 0)) {
        printf("Condizione vera (y non incrementato: %d)\n", y);
    } else {
        printf("Condizione falsa\n");
    }
    
    // 📈 Sistema di classificazione avanzato
    printf("\n📈 CLASSIFICAZIONE DETTAGLIATA:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    if (media >= 9.0 && tutti_sufficienti && poche_assenze) {
        printf("🏆 ECCELLENZA - Studente modello!\n");
    } else if (media >= 8.0 && tutti_sufficienti && poche_assenze) {
        printf("🥇 OTTIMO - Ottimi risultati!\n");
    } else if (media >= 7.0 && tutti_sufficienti && poche_assenze) {
        printf("🥈 BUONO - Buona performance!\n");
    } else if (media >= 6.0 && tutti_sufficienti && poche_assenze) {
        printf("✅ SUFFICIENTE - Promosso!\n");
    } else if (!tutti_sufficienti && ha_recuperato_debiti && poche_assenze) {
        printf("⚠️  RECUPERO - Necessari esami di recupero\n");
    } else {
        printf("❌ INSUFFICIENTE - Non promosso\n");
    }
    
    // 🔢 Tabella di verità
    printf("\n🔢 TABELLA DI VERITÀ (esempio con A=true, B=false):\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    bool A = true, B = false;
    printf("  A = %s, B = %s\n", A ? "true" : "false", B ? "true" : "false");
    printf("  A && B = %s\n", (A && B) ? "true" : "false");
    printf("  A || B = %s\n", (A || B) ? "true" : "false");
    printf("  !A = %s\n", (!A) ? "true" : "false");
    printf("  !B = %s\n", (!B) ? "true" : "false");
    
    // 💡 Note tecniche
    printf("\n💡 NOTE TECNICHE:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("🔸 && ha precedenza maggiore di ||\n");
    printf("🔸 ! ha precedenza maggiore di && e ||\n");
    printf("🔸 In C, 0 è falso, qualsiasi altro valore è vero\n");
    printf("🔸 Short-circuit: && si ferma al primo false, || al primo true\n");
    printf("🔸 Usa parentesi per chiarire espressioni complesse\n");
    
    // ✅ Messaggio finale
    printf("\n✅ Analisi completata!\n");
    printf("🚀 Prossimo step: Sperimenta con gli operatori bit a bit!\n");
    
    return 0;
}
