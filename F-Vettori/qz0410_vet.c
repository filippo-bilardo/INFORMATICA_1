#include <stdio.h> 
int main(void) { 
    float t[5] = { 1E0, 1E1, 1E2, 1E3, 1E4 }; 

    printf("%f",t[0] + t[2] + t[3]); 
    return 0; 
}
/*
the program outputs 1101.000000
the program outputs 1110.000000
the program outputs 1011.000000
the program outputs 1111.000000
*/