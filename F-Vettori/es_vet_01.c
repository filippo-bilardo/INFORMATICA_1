#include <stdio.h>

int main(void) 
{
  //inizializzo i primi 3 elementi del vettore
  int vet[5]={1,2,3}; 
  int i;

  //stampo tutti gli elementi del vettore
  for(i=0;i<5;i++) {
    printf("vet[%d]= %d\n",i , vet[i]);
  }
  
  printf("\n");
	return 0;
} 
