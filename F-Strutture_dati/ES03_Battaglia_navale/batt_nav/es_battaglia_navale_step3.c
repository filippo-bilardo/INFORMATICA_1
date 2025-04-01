/**
 * @file es_battaglia_navale_step3.c
 * @brief Battaglia Navale - Step 3: Implementazione del meccanismo di sparo
 * @author Mario Rossi
 * @version 1.0 01/04/25 Versione iniziale
 * 
 * @details
 * OBIETTIVO DELL'ESERCIZIO:
 * Implementare il meccanismo che permette al giocatore di "sparare" a una certa
 * posizione del campo di gioco, verificando se ha colpito la nave o l'acqua.
 * 
 * ANALISI DEI REQUISITI:
 * 1. Consentire all'utente di inserire le coordinate (riga, colonna) per lo sparo
 * 2. Verificare che le coordinate siano valide (all'interno del campo)
 * 3. Verificare che non si spari due volte nella stessa posizione
 * 4. Indicare se il colpo è andato a segno o meno:
 *    - Se colpisce la nave, contrassegnare con 'X' e segnalare un colpo riuscito
 *    - Se colpisce l'acqua, contrassegnare con 'O' e segnalare un colpo mancato
 * 5. Consentire un numero fisso di tentativi (5 per questo step)
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIMENSIONE 5
#define LUNGHEZZA_NAVE 3

/* Prototipi delle funzioni */
/**
 * @brief Funzione per inizializzare il campo con acqua
 * 
 * @param campo La matrice da inizializzare
 */
void inizializzaCampo(char campo[DIMENSIONE][DIMENSIONE]);

/**
 * @brief Funzione per posizionare casualmente una nave sul campo
 * 
 * @param campo La matrice dove posizionare la nave
 */
void posizionaNave(char campo[DIMENSIONE][DIMENSIONE]);

/**
 * @brief Funzione per visualizzare il campo
 * 
 * @param campo La matrice da visualizzare
 * @param mostraNave Flag che indica se mostrare o nascondere la nave (1=mostra, 0=nascondi)
 */
void visualizzaCampo(char campo[DIMENSIONE][DIMENSIONE], int mostraNave);

/**
 * @brief Funzione per gestire uno sparo
 * 
 * @param campo La matrice del campo di gioco
 * @param riga La riga dove sparare
 * @param colonna La colonna dove sparare
 * @return int 1 se il colpo è andato a segno, 0 se è acqua, -1 se le coordinate non sono valide
 */
int spara(char campo[DIMENSIONE][DIMENSIONE], int riga, int colonna);

/**
 * @brief Funzione principale
 * 
 * @return int Codice di uscita del programma
 */
int main() {
    // Implementare il main
}

/* Implementazione delle funzioni */
void inizializzaCampo(char campo[DIMENSIONE][DIMENSIONE]) {
    // Implementare la funzione per inizializzare il campo
}

void posizionaNave(char campo[DIMENSIONE][DIMENSIONE]) {
    // Implementare la funzione per posizionare la nave casualmente
}

void visualizzaCampo(char campo[DIMENSIONE][DIMENSIONE], int mostraNave) {
    // Implementare la funzione per visualizzare il campo
}

int spara(char campo[DIMENSIONE][DIMENSIONE], int riga, int colonna) {
    // Implementare la funzione per gestire uno sparo
}
