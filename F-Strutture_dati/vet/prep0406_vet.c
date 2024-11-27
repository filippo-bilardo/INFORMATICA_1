#include <stdio.h> 
int main(void) 
{ 
	int i, t[5]; 

	for(i=4; i>=0; i--)
	{
		t[i] = i-1;
		printf("t[%d]=%d; ",i , t[i]);
	}
	printf("\n"); 

	printf("t[ t[2]+t[3] = %d; ",t[ t[2]+t[3] ]);
	printf("\n"); 
	return 0; 
}



