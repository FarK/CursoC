#include <stdio.h>

long long int sum_all(long long int i)
{
	if (i >= 2)
		return i + sum_all(i - 1);
	else
		return i;
}

int main()
{
	printf("%lld\n", sum_all(1000000));

	return 0;
}
