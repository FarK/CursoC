#include <stdio.h>

#define TAM_ARRAY 20
#define POW2(x) ((x)*(x))
#define PRINT 0

int main()
{
	int array[TAM_ARRAY];
	int i;

	for (i = 0; i < TAM_ARRAY; i++)
		array[i] = POW2(i);

#if PRINT == 1
	for (i = 0; i < TAM_ARRAY; i++)
		printf("%i ", array[i]);
#elif PRINT == -1
	printf("Array initialized\n");
#else
	#warning PRINT may be 1 or -1
	printf("Error in %s:%d\n", __FILE__, __LINE__);
#endif

	return 0;
}
