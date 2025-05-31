/**
 * SOLUZIONE ESERCIZIO 2: Calcolatore di Area e Perimetro
 * 
 * Questo programma dimostra l'uso di float/double per calcoli matematici
 * precisi e l'applicazione di formule geometriche.
 */

#include <stdio.h>
#include <math.h>

int main() {
    // 🏷️ Intestazione del programma
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║        CALCOLATORE DI AREA E PERIMETRO - RETTANGOLO      ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    // 📏 Dichiarazione e inizializzazione delle variabili
    double lunghezza, larghezza;
    double area, perimetro;
    double diagonale;
    
    // 📥 Input dei dati
    printf("📐 Inserisci le dimensioni del rettangolo:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    printf("Lunghezza (in metri): ");
    scanf("%lf", &lunghezza);
    
    printf("Larghezza (in metri): ");
    scanf("%lf", &larghezza);
    
    // 🧮 Calcoli matematici
    area = lunghezza * larghezza;
    perimetro = 2 * (lunghezza + larghezza);
    diagonale = sqrt(lunghezza * lunghezza + larghezza * larghezza);
    
    // 📊 Visualizzazione dei risultati
    printf("\n📊 RISULTATI DEI CALCOLI:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    printf("🔹 Dimensioni:\n");
    printf("   Lunghezza: %.2f m\n", lunghezza);
    printf("   Larghezza: %.2f m\n", larghezza);
    printf("\n");
    
    printf("🔹 Calcoli:\n");
    printf("   Area = lunghezza × larghezza\n");
    printf("   Area = %.2f × %.2f = %.2f m²\n", lunghezza, larghezza, area);
    printf("\n");
    
    printf("   Perimetro = 2 × (lunghezza + larghezza)\n");
    printf("   Perimetro = 2 × (%.2f + %.2f) = %.2f m\n", lunghezza, larghezza, perimetro);
    printf("\n");
    
    printf("   Diagonale = √(lunghezza² + larghezza²)\n");
    printf("   Diagonale = √(%.2f² + %.2f²) = %.2f m\n", lunghezza, larghezza, diagonale);
    printf("\n");
    
    // 📈 Analisi aggiuntiva
    printf("📈 ANALISI AGGIUNTIVA:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━\n");
    
    if (lunghezza == larghezza) {
        printf("🔸 Il rettangolo è un QUADRATO!\n");
    } else if (lunghezza > larghezza) {
        double rapporto = lunghezza / larghezza;
        printf("🔸 Rettangolo orientato orizzontalmente\n");
        printf("🔸 Rapporto lunghezza/larghezza: %.2f:1\n", rapporto);
    } else {
        double rapporto = larghezza / lunghezza;
        printf("🔸 Rettangolo orientato verticalmente\n");
        printf("🔸 Rapporto larghezza/lunghezza: %.2f:1\n", rapporto);
    }
    
    // 🎯 Classificazione per area
    printf("\n🎯 CLASSIFICAZIONE PER AREA:\n");
    if (area < 1.0) {
        printf("🔹 Area piccola (< 1 m²)\n");
    } else if (area < 10.0) {
        printf("🔹 Area media (1-10 m²)\n");
    } else if (area < 100.0) {
        printf("🔹 Area grande (10-100 m²)\n");
    } else {
        printf("🔹 Area molto grande (> 100 m²)\n");
    }
    
    // 💰 Calcolo costi (esempio pratico)
    printf("\n💰 CALCOLO COSTI ESEMPIO:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    double costo_pavimento = 25.50;  // €/m²
    double costo_battiscopa = 8.75;  // €/m
    double costo_totale = (area * costo_pavimento) + (perimetro * costo_battiscopa);
    
    printf("🔸 Pavimento (%.2f €/m²): %.2f €\n", costo_pavimento, area * costo_pavimento);
    printf("🔸 Battiscopa (%.2f €/m): %.2f €\n", costo_battiscopa, perimetro * costo_battiscopa);
    printf("🔸 TOTALE: %.2f €\n", costo_totale);
    
    // ✅ Messaggio finale
    printf("\n✅ Calcoli completati con successo!\n");
    printf("💡 Nota: sqrt() richiede #include <math.h>\n");
    printf("🔧 Compila con: gcc -o esercizio2 esercizio2_soluzione.c -lm\n");
    
    return 0;
}