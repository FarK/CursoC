#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int aflag;
	int bvalue;
	char *cvalue;
	int c;

	while ((c = getopt(argc, argv, "ab:c:")) != -1) {
		switch (c)
		{
		case 'a':
			aflag = 1;
			break;
		case 'b':
			bvalue = strtol(optarg, NULL, 0);
			break;
		case 'c':
			cvalue = optarg;
			break;
		default:
			return EXIT_FAILURE;
		}
	}

	printf("aflag  = %d\n", aflag);
	printf("bvalue = %d\n", bvalue);
	printf("cvalue = \"%s\"\n", cvalue);

	for (int i = optind; i < argc; i++)
		printf("Argumento desconocido \"%s\"\n", argv[i]);

	return 0;
}
