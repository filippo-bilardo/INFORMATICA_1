
/*
In linguaggio C, il termine "variable shadowing" viene utilizzato per descrivere 
la situazione in cui una variabile locale all'interno di un blocco di codice o di 
una funzione ha lo stesso nome di una variabile globale o di un'altra variabile 
in uno scope più ampio.

Quando una variabile locale ombreggia una variabile esterna con lo stesso nome, 
significa che la sua definizione locale avrà la precedenza sulla definizione 
della variabile esterna durante l'esecuzione del blocco di codice o della funzione. 
Di conseguenza, quando si fa riferimento a quella variabile all'interno dello 
scope locale, verrà utilizzata la sua definizione locale, mentre all'esterno dello 
scope locale sarà visibile la variabile esterna.

22/06/23
*/
#include <stdio.h> //printf, scanf

int x=5;

void fun1() {
    int x=20; 
    printf("%d\n",x);
    x = x+10;
    printf("%d\n",x);
}

void fun2() {
    x=x+1; 
    printf("%d\n",x);
}

int main() 
{
    //int a;
    printf("%d\n",x);
    printf(".\n");
    fun1();
    fun1();
    fun1();
    printf(".\n");
    fun2();
    fun2();
    fun2();
    fun2();
    printf(".\n");
    printf("%d\n",x); 

    //terminiamo il programma
    return 0;
}
  
  
