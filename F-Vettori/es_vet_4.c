#include <stdio.h> 
int main(void) { 
	int i, t[5]; 

	for(i=4; i>=0; i--) {
  	t[i] = i-1;
    printf("t[%d]=%d; ",i , t[i]);
  }
  printf("\nt[ t[2]+t[3] = %d; \n",t[ t[2]+t[3] ]);
	return 0; 
}



