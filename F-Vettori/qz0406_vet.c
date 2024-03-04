#include <stdio.h> 
int main(void) { 
    int i,t[3]; 

    for(i = 2; i >=0 ; i--) 
    	t[i] = i - 1; 
    printf("%d",t[1] - t[t[0] + t[2]]); 
    return 0; 
}
/*
the program outputs 0
the program outputs 2
the program outputs -1
the program outputs 1
*/