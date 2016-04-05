#include <stdio.h>

/* Declaracion */
int f(int a, int b);

int main()
{
	/* Llamada */
	printf("%d\n", f(2, 3));

	return 0;
}

/* Definicion */
int f(int a, int b)
{
	return a + b;
}
