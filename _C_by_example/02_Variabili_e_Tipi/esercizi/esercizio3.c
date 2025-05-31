/**
 * Esercizio 3: Conversione di temperature
 * 
 * Questo programma converte temperature tra diverse unità di misura:
 * Celsius, Fahrenheit e Kelvin.
 */

#include <stdio.h>
#include <stdbool.h>  // Per il tipo bool

// Costanti per i limiti fisici delle temperature
#define ZERO_ASSOLUTO_KELVIN 0.0
#define ZERO_ASSOLUTO_CELSIUS -273.15
#define ZERO_ASSOLUTO_FAHRENHEIT -459.67

int main() {
    // Titolo del programma
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════════╗\n");
    printf("║                  CONVERTITORE DI TEMPERATURE                     ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════╝\n\n");
    
    // Variabili per le temperature
    double celsius, fahrenheit, kelvin;
    double temp_input;
    int scelta;
    bool temperatura_valida = true;
    
    // Menu di selezione
    printf("Scegli l'unità di misura di partenza:\n");
    printf("1. Celsius (°C)\n");
    printf("2. Fahrenheit (°F)\n");
    printf("3. Kelvin (K)\n");
    printf("Scelta: ");
    scanf("%d", &scelta);
    
    // Input della temperatura
    printf("\nInserisci la temperatura: ");
    scanf("%lf", &temp_input);
    
    // Conversione in base alla scelta
    switch(scelta) {
        case 1:  // Da Celsius a altre unità
            celsius = temp_input;
            
            // Verifica che la temperatura non sia sotto lo zero assoluto
            if (celsius < ZERO_ASSOLUTO_CELSIUS) {
                printf("\n❌ ERRORE: Temperatura inferiore al zero assoluto!\n");
                printf("   Il zero assoluto è %.2f °C\n", ZERO_ASSOLUTO_CELSIUS);
                temperatura_valida = false;
                break;
            }
            
            // Conversioni
            fahrenheit = (celsius * 9.0/5.0) + 32.0;
            kelvin = celsius + 273.15;
            break;
            
        case 2:  // Da Fahrenheit a altre unità
            fahrenheit = temp_input;
            
            // Verifica che la temperatura non sia sotto lo zero assoluto
            if (fahrenheit < ZERO_ASSOLUTO_FAHRENHEIT) {
                printf("\n❌ ERRORE: Temperatura inferiore al zero assoluto!\n");
                printf("   Il zero assoluto è %.2f °F\n", ZERO_ASSOLUTO_FAHRENHEIT);
                temperatura_valida = false;
                break;
            }
            
            // Conversioni
            celsius = (fahrenheit - 32.0) * 5.0/9.0;
            kelvin = celsius + 273.15;
            break;
            
        case 3:  // Da Kelvin a altre unità
            kelvin = temp_input;
            
            // Verifica che la temperatura non sia sotto lo zero assoluto
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
    
    // Visualizzazione dei risultati se la temperatura è valida
    if (temperatura_valida) {
        printf("\n📊 Risultati della conversione:\n");
        printf("════════════════════════════════════════════════════════\n");
        printf("Celsius (°C): %.2f\n", celsius);
        printf("Fahrenheit (°F): %.2f\n", fahrenheit);
        printf("Kelvin (K): %.2f\n", kelvin);
        
        // Informazioni aggiuntive sulla temperatura
        printf("\n💡 Informazioni aggiuntive:\n");
        if (celsius <= 0) {
            printf("- L'acqua è ghiacciata a questa temperatura\n");
        } else if (celsius < 100) {
            printf("- L'acqua è liquida a questa temperatura\n");
        } else {
            printf("- L'acqua bolle a questa temperatura\n");
        }
    }
    
    return 0;
}