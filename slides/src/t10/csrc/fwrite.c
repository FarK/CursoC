#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FNAME "file"

int main() {
	FILE *f;
	char buf[] = "Hola Mundo";

	f = fopen(FNAME, "w+");
	if (!f) {
		perror("Error al abrir");
		exit(EXIT_FAILURE);
	}

	fwrite(buf, sizeof(char), strlen(buf), f);
	if (ferror(f)) {
		perror("Error al escribir");
		exit(EXIT_FAILURE);
	}

	fclose(f);
	return 0;
}
