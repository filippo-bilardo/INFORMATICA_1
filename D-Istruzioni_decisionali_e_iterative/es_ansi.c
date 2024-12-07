#include <stdio.h>
#include <stdlib.h>

// Definizione dei codici ANSI per il colore del testo
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define UNDERLINE   "\033[4m"
#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"

// Definizione dei codici ANSI per il colore dello sfondo
#define BACK_BLACK  "\033[40m"
#define BACK_RED    "\033[41m"
#define BACK_GREEN  "\033[42m"
#define BACK_YELLOW "\033[43m"
#define BACK_BLUE   "\033[44m"
#define BACK_MAGENTA "\033[45m"
#define BACK_CYAN   "\033[46m"
#define BACK_WHITE  "\033[47m"

// Definizione per cancellare lo schermo
#define CLEAR_SCREEN "\033[2J"

// Funzione principale
int main() {
    // Cancella lo schermo
    printf(CLEAR_SCREEN);

    // Test dei colori del testo
    printf(RED "Questo è un testo rosso!\n" RESET);
    printf(GREEN "Questo è un testo verde!\n" RESET);
    printf(BLUE "Questo è un testo blu!\n" RESET);

    // Test dello sfondo colorato
    printf(BACK_YELLOW BLACK "Testo con sfondo giallo e testo nero\n" RESET);
    printf(BACK_BLUE WHITE "Testo con sfondo blu e testo bianco\n" RESET);

    // Test di stile: grassetto e sottolineato
    printf(BOLD "Questo è un testo in grassetto!\n" RESET);
    printf(UNDERLINE "Questo è un testo sottolineato!\n" RESET);

    // Test di combinazione di colori e stili
    printf(RED BACK_WHITE BOLD "Testo rosso su sfondo bianco e in grassetto\n" RESET);
    printf(GREEN BACK_CYAN UNDERLINE "Testo verde su sfondo ciano e sottolineato\n" RESET);

    // Posizionamento del cursore: spostiamo il cursore nella riga 5, colonna 10
    printf("\033[5;10H" GREEN "Posizionato il cursore alla riga 5, colonna 10!" RESET "\n");

    // Risultato finale
    printf("Programma terminato!\n");

    return 0;
}
