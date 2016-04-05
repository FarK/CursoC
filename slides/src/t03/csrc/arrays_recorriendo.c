int main() {
	int i;
	p = array;

	// forma 1: Contador e incremento de puntero
	for (i = 0; i < 5; i++)
		printf("%d\t", *p++);

	// forma 2: Incremento de puntero y comparacion de direcciones
	for (p = array; p <= &array[4]; p++)
		printf("%d\t", *p);

	// forma 3: Contador y puntero como array
	for (i = 0, p = array; i < 5; i++)
		printf("%d\t", p[i]);

	return 0;
}
