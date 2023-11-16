/**
 * @file es01_main.c - © FB - 08/12/20
 * @brief Passaggio di argomenti alla funzione main tramite linea di comando
 * argc: numero di argomenti passati
 * argv: array di stringhe contenente gli argomenti passati
 */
#include <stdio.h>  //printf
#include <stdlib.h> //exit

int main(int argc, char **argv) 
//int main(int argc, char *argv[])
//int main(int argc, char argv[][MAX_ARG_LENGTH])
{
  // Verifica argomenti passati al main
  int i;
  printf("\nNumero di argomenti passati, argc=%d\n", argc);
  
  // Stampa gli argomenti passati
  for(i=0; i<argc; ++i) {
    printf("argv[%d]:=%s\n", i, argv[i]);
  }
  printf("\n");

  return EXIT_SUCCESS;
} 
 