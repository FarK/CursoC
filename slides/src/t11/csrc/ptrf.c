int mul(int i)
{
	return i*2;
}

int div(int i)
{
	return i/2;
}

int main()
{
	int (*pf)(int);

	pf = mul;
	printf("%d\n", pf(10));

	pf = div;
	printf("%d\n", pf(10));

	return 0;
}
