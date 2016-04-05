#include <stdio.h>
#include <stdlib.h>

int *array_alloc(int n)
{
	int *p = (int *)malloc(n * sizeof(int))
	return p;
}

static const int tam = 3;

int main()
{
	int i;
	int *array;

	array = array_alloc(tam);

	/* Inicializamos */
	for (i = 0; i < tam; i++)
		array[i] = i;

	/* Imprimimos */
	for (i = 0; i < tam; i++)
		printf("%d\n", array[i]);

	free(array);

	return 0;
}
