int main(int argc, char *argv[])
{
	int i;

	printf("Argumento i = <argumento>\n");
	for (i = 0; i < argc; i++)
		printf("%d = %s\n", i, argv[i]);

	return 0;
}
