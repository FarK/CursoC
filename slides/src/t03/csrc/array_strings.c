#include <stdio.h>

int main()
{
	int i;
	char hola[] = {'h', 'o', 'l', 'a', '\0'};
	char mundo[] = "mundo";

	printf("%s %s\n", hola, mundo);

	for (i = 0; i < 4; i++)
		printf("%c ", hola[i]);

	for (i = 0; i < 5; i++)
		printf("%c ", mundo[i]);

	return 0;
}
