#include <stdio.h>

int main()
{
	int entero = 3;
	char c;

	c = 'c';

	printf("int\n\tvalor = %d\n\ttamanyo %lu\n\n", entero, sizeof(entero));
	printf("char\n\tvalor = %c\n\ttamanyo %lu\n\n", c, sizeof(char));
}
