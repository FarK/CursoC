#include <stdio.h>

int main()
{
	int i = 42;
	int *pi;

	pi = &i;
	printf("dir = %p\n",  pi);
	printf("val = %d\n", *pi);

	*pi = 24;
	printf("val = %d\n", i);

	return 0;
}
