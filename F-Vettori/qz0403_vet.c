#include <stdio.h> 
int main(void) { 
    int i, t[5]; 

    t[0] = 0; 
    for(i = 1; i < 5; i++) 
    	t[i] = t[i - 1] + i; 
    printf("%d",t[4]); 
    return 0; 
}
/*
the program outputs 8
the program outputs 9
the program outputs 11
the program outputs 10
*/
