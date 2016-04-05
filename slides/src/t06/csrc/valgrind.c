#include <stdio.h>
#include <stdlib.h>

int main()
{
	int *p = (int *)malloc(20);

	if (!p)
		return EXIT_FAILURE;

	printf("La direccion de p es %p\n", p);

	/* free(p) */

	return 0;
}
