#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FNAME "file"

int main()
{
	FILE *f;

	f = fopen(FNAME, "w+");
	if (!f) {
		perror("Error al abrir");
		exit(EXIT_FAILURE);
	}

	fprintf(f, "Hola Mundo\n 2 + 2 = %d", 2 + 2);
	if (ferror(f)) {
		perror("Error al escribir");
		exit(EXIT_FAILURE);
	}

	fclose(f);
	return 0;
}
