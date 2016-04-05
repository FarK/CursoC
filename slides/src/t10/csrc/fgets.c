#define FNAME "file"
#define BUFSIZE 256

int main()
{
	FILE *f;
	char buf[BUFSIZE];

	f = fopen(FNAME, "r");
	if (!f) {
		perror("Error al abrir");
		exit(EXIT_FAILURE);
	}

	int i = 0;
	while (fgets(buf, BUFSIZE, f))
		printf("%d: \"%s\"\n", i++, buf);
	if (ferror(f)) {
		perror("Error al leer");
		exit(EXIT_FAILURE);
	}

	fclose(f);
	return 0;
}
