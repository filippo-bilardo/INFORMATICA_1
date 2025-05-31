/**
 * Esercizio 2: Calcolo delle proprietà di un rettangolo
 * 
 * Questo programma calcola area, perimetro e diagonale di un rettangolo
 * utilizzando i tipi di dati in virgola mobile.
 */

#include <stdio.h>
#include <math.h>  // Per la funzione sqrt (radice quadrata)

int main() {
    // Titolo del programma
    printf("\n");
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║            CALCOLO PROPRIETÀ RETTANGOLO               ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    printf("\n");

    // Dichiarazione delle variabili
    double lunghezza, larghezza;
    double area, perimetro;
    double diagonale;

    // Input dei dati
    printf("📏 Inserisci le dimensioni del rettangolo:\n");
    printf("════════════════════════════════════════════════════════\n");

    printf("Lunghezza (in metri): ");
    scanf("%lf", &lunghezza);

    printf("Larghezza (in metri): ");
    scanf("%lf", &larghezza);

    // Calcolo delle proprietà del rettangolo
    area = lunghezza * larghezza;
    perimetro = 2 * (lunghezza + larghezza);
    diagonale = sqrt(lunghezza * lunghezza + larghezza * larghezza);

    // Output dei risultati
    printf("\n");
    printf("📊 Risultati dei calcoli:\n");
    printf("════════════════════════════════════════════════════════\n");
    printf("Area: %.2f m²\n", area);
    printf("Perimetro: %.2f m\n", perimetro);
    printf("Diagonale: %.2f m\n", diagonale);

    // Messaggio finale
    printf("\n");
    printf("✅ Calcoli completati con successo!\n");
    printf("💡 Ricorda: l'area si misura in metri quadrati (m²)\n");

    return 0;
}