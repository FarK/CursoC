int main()
{
	FILE *f;
	char str1[10], srt2[10];
	int a, b, c, ret;

	f = fopen(FNAME, "r");
	if (!f) {
		perror("Error al abrir");
		exit(EXIT_FAILURE);
	}

	while ((ret = fscanf(f, "%10s %10s %d + %d = %d",
	              str1, str2, &a, &b, &c)) == 5) {
		printf("%s %s\n %d + %d = %d\n", str1, str2, a, b, c);
	}
	if (ferror(f)) {
		perror("Error al leer");
		exit(EXIT_FAILURE);
	}
	else if (ret != EOF) {
		fprintf(stderr, "Error al analizar: %d/%d\n", ret, 5);
	}

	fclose(f);
	return 0;
}
