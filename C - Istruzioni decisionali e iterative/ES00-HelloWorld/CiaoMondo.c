// gcc -g CiaoMondo.c

#include <stdio.h> //printf, scanf

int main() 
{
  //dichiariamo la variabile a
  int a;
  
  //scrivere a schermo un messagio
  printf("Inserisci il tuo voto ");
  
  //lettura da tastiera di un intero in base 10
  scanf("%d", &a);
  
  //stampiamo a schermo un messaggio contenente
  //il valore del numero inserito da tastiera
  printf("Hai inserito il numero %d\n\n", a);
 
  //terminiamo il programma
  return 0;
}
  
  
