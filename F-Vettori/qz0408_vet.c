#include <stdio.h> 
int main(void) { 
    int s,i,t[] = { 0, 1, 2, 3, 4, 5 }; 

    s = 1; 
    for(i = 2; i < 6 ; i += i + 1) 
    	s += t[i]; 
    printf("%d",s); 
    return 0; 
}
/*
the program outputs 1
the program outputs 2
the program outputs 4
the program outputs 8
*/