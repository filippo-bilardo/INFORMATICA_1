/**
 * @file es_vet_01.c
 * Gestione di un vettore di interi
 * inizializzazione di alcuni elementi utilizzando 
 * l'operatore di assegnazione e l'operatore di inizializzazione   
 * e stampa di tutti gli elementi del vettore *
 */
#include <stdio.h>

int main(void) 
{
  //inizializzo i primi 3 elementi del vettore
  int vet[5]={1,2,3}; 
  //Equivalente a 
  //int vet[5]={1,2,3,0,0};
  //int vet[]={1,2,3,0,0};

  //stampo tutti gli elementi del vettore
  for(int i=0;i<5;i++) {
    printf("vet[%d]= %d\n",i , vet[i]);
  } 
  printf("\n");

  int uni[10] = {1};
  for(int i=0;i<10;i++) {
    printf("uni[%d]= %d\n",i , uni[i]);
  }
  printf("\n");

	return 0;
} 
