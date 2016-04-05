union float_t{
	float f;
	struct {
		uint32_t fra : 23;
		uint32_t exp : 8;
		uint32_t sig : 1;
	};
};

int main()
{
	union float_t f;

	f.f = -3.1416;

	printf("signo     = %u\n", f.sig);
	printf("exponente = %d\n", f.exp);
	printf("fraccion  = %d\n", f.fra);

	return 0;
}
