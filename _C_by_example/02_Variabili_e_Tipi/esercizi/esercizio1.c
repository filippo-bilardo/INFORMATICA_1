/**
 * Esercizio 1: Tipi di dati fondamentali in C
 * 
 * Questo programma dimostra l'uso dei tipi di dati fondamentali in C
 * e le conversioni tra diversi tipi.
 */

#include <stdio.h>

int main() {
    // Titolo del programma
    printf("\n");
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║            TIPI DI DATI FONDAMENTALI IN C            ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    printf("\n");

    // Dimostrazione dei tipi interi
    char carattere = 'A';
    short numero_piccolo = 1000;
    int numero_intero = 42000;
    long numero_grande = 1000000L;

    printf("char carattere = '%c' (valore ASCII: %d)\n", carattere, carattere);
    printf("short numero_piccolo = %d\n", numero_piccolo);
    printf("int numero_intero = %d\n", numero_intero);
    printf("long numero_grande = %ld\n", numero_grande);
    printf("\n");

    // Dimostrazione dei tipi in virgola mobile
    float numero_float = 3.14159f;
    double numero_double = 3.14159265359;

    printf("float numero_float = %.5f\n", numero_float);
    printf("double numero_double = %.10f\n", numero_double);
    printf("\n");

    // Dimostrazione dei limiti di precisione
    float precisione_float = 123456789.0f;
    double precisione_double = 123456789.0;

    printf("Precisione float: %.1f\n", precisione_float);
    printf("Precisione double: %.1f\n", precisione_double);
    printf("\n");

    // Dimostrazione delle conversioni di tipo (casting)
    int intero = 65;
    char carattere_da_int = (char)intero;
    float float_da_int = (float)intero;

    printf("int intero = %d\n", intero);
    printf("Conversione a char: '%c' (ASCII %d)\n", carattere_da_int, carattere_da_int);
    printf("Conversione a float: %.2f\n", float_da_int);
    printf("\n");

    // Messaggio finale
    printf("✅ Tutti i tipi di dato fondamentali sono stati dimostrati!\n");
    printf("💡 Studia le differenze tra i vari tipi e le loro applicazioni.\n");

    return 0;
}