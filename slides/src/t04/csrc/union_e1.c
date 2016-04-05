union char_int {
	struct {
		char c1;
		char c2;
		char c3;
		char c4;
	};
	int   i;
};

int main()
{
	union char_int ci;

	ci.i = 1701999205;
	printf("%c%c%c%c\n", ci.c1, ci.c2, ci.c3, ci.c4);

	return 0;
}
