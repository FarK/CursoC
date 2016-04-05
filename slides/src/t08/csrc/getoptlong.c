#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>

int main(int argc, char **argv)
{
	static int usage = false;
	size_t width, height;
	bool random = false;
	int rseed;

	int option_index = 0;
	int c;

	static struct option long_options[] =
	{
		{"usage",  no_argument,       0, 'u'},
		{"width",  required_argument, 0, 'w'},
		{"height", required_argument, 0, 'h'},
		{"random", optional_argument, 0, 'r'},
		{0, 0, 0, 0}
	};

	while ((c = getopt_long(argc, argv, "uw:h:r::", long_options,
				&option_index)) != -1) {
		switch (c) {
		case 'u':
			usage = true;
			break;
		case 'w':
			width = strtol(optarg, NULL, 0);
			break;
		case 'h':
			height = strtol(optarg, NULL, 0);
			break;
		case 'r':
			random = true;
			if (optarg)
				rseed = strtol(optarg, NULL, 0);
			break;
		case '?':
			/* getopt_long imprime un mensaje de error*/
			break;
		default:
			printf("Error\n");
			exit(EXIT_FAILURE);
		}
	}

	printf("usage  = %s\n", usage? "TRUE" : "FALSE");
	printf("width  = %lu\n", width);
	printf("height = %lu\n", height);
	printf("random = %s\n", random? "TRUE" : "FALSE");
	printf("rseed  = %d\n", rseed);

	for (int i = optind; i < argc; i++)
		printf("Argumento desconocido: \"%s\"\n", argv[i]);

	exit(0);
}
