union float_int {
	float f;
	int   i;
};

int main()
{
	union float_int fi;

	fi.f = 2.7182;
	printf("%X\n", fi.i);

	return 0;
}
