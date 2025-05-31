/**
 * SOLUZIONE ESERCIZIO 1: Dichiarazione e Inizializzazione di Variabili
 * 
 * Questo esercizio dimostra l'uso corretto di tutti i tipi di dato
 * fondamentali del linguaggio C con inizializzazione e output formattato.
 */

#include <stdio.h>

int main() {
    // 🏷️ Intestazione del programma
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║           DIMOSTRAZIONE TIPI DI DATO IN C                ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    // 📊 TIPI INTERI
    printf("🔢 TIPI DI DATO INTERI:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    char carattere = 'A';
    short numero_piccolo = 1000;
    int numero_intero = 42000;
    long numero_grande = 1000000L;
    
    printf("char carattere = '%c' (valore ASCII: %d)\n", carattere, carattere);
    printf("short numero_piccolo = %d\n", numero_piccolo);
    printf("int numero_intero = %d\n", numero_intero);
    printf("long numero_grande = %ld\n", numero_grande);
    printf("\n");
    
    // 🎯 TIPI IN VIRGOLA MOBILE
    printf("🔢 TIPI DI DATO DECIMALI:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    float pi_float = 3.14159f;
    double pi_double = 3.141592653589793;
    
    printf("float pi_float = %.5f\n", pi_float);
    printf("double pi_double = %.15f\n", pi_double);
    printf("\n");
    
    // ⚖️ TIPI UNSIGNED
    printf("➕ TIPI SENZA SEGNO (UNSIGNED):\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    unsigned char byte_value = 255;
    unsigned int numero_positivo = 4000000U;
    
    printf("unsigned char byte_value = %u\n", byte_value);
    printf("unsigned int numero_positivo = %u\n", numero_positivo);
    printf("\n");
    
    // 📏 DIMENSIONI DEI TIPI
    printf("📏 DIMENSIONI IN MEMORIA:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    printf("char:          %2zu byte(s)\n", sizeof(char));
    printf("short:         %2zu byte(s)\n", sizeof(short));
    printf("int:           %2zu byte(s)\n", sizeof(int));
    printf("long:          %2zu byte(s)\n", sizeof(long));
    printf("float:         %2zu byte(s)\n", sizeof(float));
    printf("double:        %2zu byte(s)\n", sizeof(double));
    printf("\n");
    
    // 🧮 OPERAZIONI ARITMETICHE
    printf("🧮 OPERAZIONI ARITMETICHE:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    int a = 15, b = 4;
    float risultato_float = (float)a / (float)b;
    
    printf("Dati: a = %d, b = %d\n", a, b);
    printf("a + b = %d\n", a + b);
    printf("a - b = %d\n", a - b);
    printf("a * b = %d\n", a * b);
    printf("a / b = %d (divisione intera)\n", a / b);
    printf("a %% b = %d (resto)\n", a % b);
    printf("a / b = %.2f (divisione float)\n", risultato_float);
    printf("\n");
    
    // 🔄 CONVERSIONI DI TIPO
    printf("🔄 CONVERSIONI DI TIPO:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    int intero = 100;
    char carattere_da_int = (char)intero;
    float float_da_int = (float)intero;
    
    printf("int intero = %d\n", intero);
    printf("Conversione a char: '%c' (ASCII %d)\n", carattere_da_int, carattere_da_int);
    printf("Conversione a float: %.2f\n", float_da_int);
    printf("\n");
    
    // ✅ MESSAGGIO FINALE
    printf("✅ Tutti i tipi di dato fondamentali sono stati dimostrati!\n");
    printf("💡 Studia le differenze tra i vari tipi e le loro applicazioni.\n");
    
    return 0;
}