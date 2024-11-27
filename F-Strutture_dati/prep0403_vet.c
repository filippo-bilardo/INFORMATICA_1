#include <stdio.h> 
int main(void) 
	{ 
	int i, t[5]; 

	t[4]=0; 
	for(i=3; i>=0; i--)
	{
		t[i] = t[i + 1] + i;
		printf("t[%d]=%d; ",i , t[i]);
	}
	printf("\n"); 

	printf("t[0]=%d; ",t[0]);
	printf("\n"); 
	return 0; 
}

