#include <stdio.h>
#include <stdlib.h>

int main()
{
	void *p1 = malloc(2 * 1024);
	void *p2 = malloc(1 * 1024);
	void *p3 = malloc(2 * 1024);

	void *p;

	printf("%ld\n", (long int)p1 / 1024);
	printf("%ld\n", (long int)p2 / 1024);
	printf("%ld\n", (long int)p3 / 1024);

	free(p2);
	p = malloc(2 * 1024);

	printf("\n%ld\n", (long int)p / 1024);

	return 0;
}
