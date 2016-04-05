#define FNAME "file"
#define BUFSIZE 256

int main() {
	FILE *f;
	char buf[BUFSIZE];
	int read;

	f = fopen(FNAME, "r");
	if (!f) {
		perror("No se ha podido abrir el fichero");
		exit(EXIT_FAILURE);
	}

	read = fread(buf, sizeof(char), BUFSIZE - 1, f);
	if (ferror(f)) {
		perror("Error al leer");
		exit(EXIT_FAILURE);
	}

	buf[read] = '\0';
	printf("%s", buf);

	fclose(f);
	return 0;
}
