struct A {
	int a;
	struct {
		int b;
	};
};

int main()
{
	struct A a = {1, {2}};

	printf("a = {%d, {%d}}\n", a.a, a.b);

	return 0;
}
