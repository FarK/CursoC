#include <stdio.h>

int main()
{
	int i;
	int vector1[10];
	int vector2[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

	for (i = 0; i < 10; i++)
		vector1[i] = vector2[i];

	for (i = 0; i < 10; i++)
		printf("%d ", vector1[i]);

	return 0;
}
