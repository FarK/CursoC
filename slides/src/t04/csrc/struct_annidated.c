struct A {
	int a;
	struct B {
		int b;
	} stb;
};

int main()
{
	struct A a = {1, {2}};

	printf("a = {%d, {%d}}\n", a.a, a.stb.b);

	return 0;
}
