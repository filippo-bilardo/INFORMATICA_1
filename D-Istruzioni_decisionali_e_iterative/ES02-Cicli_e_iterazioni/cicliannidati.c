/**
 * @file cicliannidati.c
 * 
 * Esempio di cicli annidati
 * 
 * @author FB
 * @version 1.0 20/11/2023
 */

#include <stdio.h>
#include <stdlib.h>

#define RIGHE_TOT 5
#define COLONNE_TOT 4

int main()
{
    int riga, colonna;
    char carattere;

    //Chiediamo all'utente di inserire un carattere
    printf("Inserisci un carattere: ");
    scanf("%c", &carattere);

    //Stampiamo una matrice contenente il carattere inserito
    for(riga=0; riga<RIGHE_TOT; riga++)
    {
        for(colonna=0; colonna<COLONNE_TOT; colonna++)
        {
            printf("%c ", carattere);
        }
        printf("\n");
    }

    return 0;
}
