#include <stdio.h> //printf
#include <string.h> 

void printAscii() 
{
  int i=0;
  for(i=32; i<=127; i++) 
  {
    printf("\nAscii code[%d], %x=%c", i,i,i);
  }
  printf("\n");
  printf("\n");  
}
    
     
int main(int argc, char **argv) 
//int main(int argc, char *argv[]) 
{
  // Verifica argomenti passati al main
  int i;
  printf("Numero di argomenti passati, argc=%d\n",argc);
  
  for(i=0;i < argc;++i) {
    printf("argv[%d]:=%s\n",i,argv[i]);
  }
  printf("\n");

  // Utilizzo delle stringhe
  printf("\n----------------");
  char *msg1 = "Ciao mondo";    // Puntatore ad una costante stringa
  char msg2[] = "Ciao mondo";   // vettore contenente una copia della costante "Ciao mondo", msg2 puntatore alla base del vettore
  char msg3[30];
  //char *msg3;
  //char *msg4={'l','e',' ','s','t','r','i','n','g','h','e','\0'};
  char msg4[]={'l','e',' ','s','t','r','i','n','g','h','e','\0'};
  char A[]="Ciao";
  char B[]="Mario";
  char C[30];
  
  //msg1[2] = 10;   //Istruzione illegale perchè msg1 punta ad una stinga costante
  msg2[3] = 'Z';
  msg2[4] = 65;
  msg2[8] = 0;
  
  printf("\nmsg1=%s", msg1);
  printf("\nmsg2=%s", msg2);
  printf("\nmsg4=%s", msg4);
  printf("\nmsg1[0]=%c, msg1[1]=%c", msg1[0], msg1[1]);
  printf("\n");
  
  printf("\nInserisci una stringa: ");
  scanf("%s", &msg3);
  printf("\nmsg3=%s", msg3);

  // Codice Ascii
  //printf("\n----------------");
  //printAscii();
  
  return 0;
} 
 
 