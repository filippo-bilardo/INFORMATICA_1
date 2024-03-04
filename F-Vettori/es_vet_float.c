#include <stdio.h> 

int main(void) 
{
    int i;
    float sum=0, t[5] = {1E0, 1E1, 1E2, 1E3, 1E4}; 

    for(i=0; i<5; i++) { 
      sum += t[i];
      printf("t[%d]=%f, sum=%f\n",i, t[i], sum);
    }
}