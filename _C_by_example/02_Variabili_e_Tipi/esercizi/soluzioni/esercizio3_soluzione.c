/**
 * SOLUZIONE ESERCIZIO 3: Conversione di Temperatura
 * 
 * Questo programma avanzato dimostra conversioni tra scale di temperatura,
 * uso di costanti, validazione input e formattazione avanzata dell'output.
 */

#include <stdio.h>
#include <stdbool.h>

// 🔧 Costanti per le conversioni
#define ZERO_ASSOLUTO_CELSIUS -273.15
#define ZERO_ASSOLUTO_FAHRENHEIT -459.67
#define ZERO_ASSOLUTO_KELVIN 0.0
#define PUNTO_CONGELAMENTO_CELSIUS 0.0
#define PUNTO_EBOLLIZIONE_CELSIUS 100.0

int main() {
    // 🏷️ Intestazione del programma
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║            CONVERTITORE DI TEMPERATURE AVANZATO          ║\n");
    printf("║               Celsius ↔ Fahrenheit ↔ Kelvin             ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    // 📊 Variabili per le temperature
    double celsius, fahrenheit, kelvin;
    double temp_input;
    int scelta;
    bool temperatura_valida = true;
    
    // 📋 Menu di selezione
    printf("🌡️  SELEZIONA LA SCALA DI TEMPERATURA DI PARTENZA:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("1️⃣  Celsius (°C)\n");
    printf("2️⃣  Fahrenheit (°F)\n");
    printf("3️⃣  Kelvin (K)\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("Inserisci la tua scelta (1-3): ");
    
    scanf("%d", &scelta);
    
    // 📥 Input della temperatura
    printf("\nInserisci il valore della temperatura: ");
    scanf("%lf", &temp_input);
    
    // 🔄 Conversioni basate sulla scelta
    switch(scelta) {
        case 1: // Da Celsius
            celsius = temp_input;
            
            // Validazione: controllo zero assoluto
            if (celsius < ZERO_ASSOLUTO_CELSIUS) {
                printf("\n❌ ERRORE: Temperatura inferiore al zero assoluto!\n");
                printf("   Il zero assoluto è %.2f°C\n", ZERO_ASSOLUTO_CELSIUS);
                temperatura_valida = false;
                break;
            }
            
            // Conversioni
            fahrenheit = (celsius * 9.0/5.0) + 32.0;
            kelvin = celsius + 273.15;
            break;
            
        case 2: // Da Fahrenheit
            fahrenheit = temp_input;
            
            // Validazione: controllo zero assoluto
            if (fahrenheit < ZERO_ASSOLUTO_FAHRENHEIT) {
                printf("\n❌ ERRORE: Temperatura inferiore al zero assoluto!\n");
                printf("   Il zero assoluto è %.2f°F\n", ZERO_ASSOLUTO_FAHRENHEIT);
                temperatura_valida = false;
                break;
            }
            
            // Conversioni
            celsius = (fahrenheit - 32.0) * 5.0/9.0;
            kelvin = celsius + 273.15;
            break;
            
        case 3: // Da Kelvin
            kelvin = temp_input;
            
            // Validazione: controllo zero assoluto
            if (kelvin < ZERO_ASSOLUTO_KELVIN) {
                printf("\n❌ ERRORE: Temperatura inferiore al zero assoluto!\n");
                printf("   Il zero assoluto è %.2f K\n", ZERO_ASSOLUTO_KELVIN);
                temperatura_valida = false;
                break;
            }
            
            // Conversioni
            celsius = kelvin - 273.15;
            fahrenheit = (celsius * 9.0/5.0) + 32.0;
            break;
            
        default:
            printf("\n❌ ERRORE: Scelta non valida!\n");
            temperatura_valida = false;
            break;
    }
    
    // 📊 Visualizzazione risultati (solo se temperatura valida)
    if (temperatura_valida) {
        printf("\n🌡️  RISULTATI DELLE CONVERSIONI:\n");
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        
        printf("🔸 Celsius:    %8.2f °C\n", celsius);
        printf("🔸 Fahrenheit: %8.2f °F\n", fahrenheit);
        printf("🔸 Kelvin:     %8.2f K\n", kelvin);
        printf("\n");
        
        // 🔍 Analisi della temperatura
        printf("🔍 ANALISI DELLA TEMPERATURA:\n");
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        
        // Stato dell'acqua
        if (celsius <= PUNTO_CONGELAMENTO_CELSIUS) {
            printf("❄️  L'acqua è SOLIDA (ghiaccio)\n");
        } else if (celsius >= PUNTO_EBOLLIZIONE_CELSIUS) {
            printf("💨 L'acqua è GASSOSA (vapore)\n");
        } else {
            printf("💧 L'acqua è LIQUIDA\n");
        }
        
        // Classificazione temperatura ambiente
        if (celsius < -40) {
            printf("🥶 Temperatura ESTREMA (pericolo di vita)\n");
        } else if (celsius < 0) {
            printf("❄️  Temperatura MOLTO FREDDA\n");
        } else if (celsius < 10) {
            printf("🧊 Temperatura FREDDA\n");
        } else if (celsius < 20) {
            printf("😐 Temperatura FRESCA\n");
        } else if (celsius < 25) {
            printf("😊 Temperatura IDEALE\n");
        } else if (celsius < 30) {
            printf("☀️  Temperatura CALDA\n");
        } else if (celsius < 40) {
            printf("🌡️  Temperatura MOLTO CALDA\n");
        } else {
            printf("🔥 Temperatura ESTREMA (pericolo di vita)\n");
        }
        
        // 📏 Confronti interessanti
        printf("\n📏 CONFRONTI INTERESSANTI:\n");
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        
        double diff_zero_assoluto = kelvin - ZERO_ASSOLUTO_KELVIN;
        double diff_congelamento = celsius - PUNTO_CONGELAMENTO_CELSIUS;
        double diff_ebollizione = celsius - PUNTO_EBOLLIZIONE_CELSIUS;
        
        printf("🔸 Distanza dal zero assoluto: %.2f K\n", diff_zero_assoluto);
        printf("🔸 Distanza dal congelamento dell'acqua: %.2f °C\n", diff_congelamento);
        printf("🔸 Distanza dall'ebollizione dell'acqua: %.2f °C\n", diff_ebollizione);
        
        // 🧮 Formule utilizzate
        printf("\n🧮 FORMULE DI CONVERSIONE UTILIZZATE:\n");
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        printf("🔸 °F = (°C × 9/5) + 32\n");
        printf("🔸 °C = (°F - 32) × 5/9\n");
        printf("🔸 K = °C + 273.15\n");
        printf("🔸 °C = K - 273.15\n");
        
        // 🎯 Valori di riferimento
        printf("\n🎯 TEMPERATURE DI RIFERIMENTO:\n");
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        printf("❄️  Zero assoluto:        %.2f°C / %.2f°F / %.2f K\n", 
               ZERO_ASSOLUTO_CELSIUS, ZERO_ASSOLUTO_FAHRENHEIT, ZERO_ASSOLUTO_KELVIN);
        printf("🧊 Congelamento acqua:    %.1f°C / %.1f°F / %.2f K\n", 
               0.0, 32.0, 273.15);
        printf("💨 Ebollizione acqua:     %.1f°C / %.1f°F / %.2f K\n", 
               100.0, 212.0, 373.15);
        printf("🌡️  Temperatura corporea:  37.0°C / 98.6°F / 310.15 K\n");
    }
    
    // ✅ Messaggio finale
    printf("\n✅ Conversione completata!\n");
    printf("💡 Le conversioni sono accurate con precisione di due decimali.\n");
    printf("🔬 Ricorda: il zero assoluto è il limite teorico più basso!\n");
    
    return 0;
}