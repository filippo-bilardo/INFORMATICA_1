#include <stdio.h> 
int main(void) { 
    int i,t[4] = { 1, 2, 4, 8 }; 

    for(i = 0; i < 2 ; i++) 
    	t[i] = t[3 - i]; 
    printf("%d",t[2]); 
    return 0; 
}
/*
the program outputs 4
the program outputs 8
the program outputs 2
the program outputs 1
*/
