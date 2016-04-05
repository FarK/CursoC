#include <stdio.h>

void f(int a)
{
	a = 33;
}

int main()
{
	int a = 3;
	f(a);
	printf("%d\n", a);

	return 0;
}
