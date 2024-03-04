#include <stdio.h>

int main(void)
{
	int i, t[5];

	t[4] = 0;
	for (i = 3; i >= 0; i--)
	{
		t[i] = t[i + 1] + i;
		printf("t[%d]=%d; ", i, t[i]);
	}
	printf("\nt[0]=%d; \n", t[0]);
}
