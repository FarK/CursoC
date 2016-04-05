#include <stdio.h>

int main()
{
	int magic = '\0' << 3*8 | 'y' << 2*8 | 'a' << 1*8 | 'w';
	int magic = 0x00796177;
	printf("\nmagic = %0X\n", magic);
	printf("magic = \"%s\"\n", (char *)(&magic));

	return 0;
}
