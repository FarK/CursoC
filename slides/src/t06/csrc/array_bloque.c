#define ROWS 3
#define COLS 3

int main()
{
	int i, j;
	int *array;

	/* Reservamos */
	array = (int *)malloc(ROWS * COLS * sizeof(int));
	if (!array) {
		printf("Can't allocate the array\n");
		return -1;
	}

	/* Inicializamos */
	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLS; j++)
			*(array + i * COLS + j) = i * 10 + j;

	/* Imprimimos */
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			printf("%02d ", *(array + i * COLS + j));
		}
		printf("\n");
	}

	free(array); /* Liberamos */
	return 0;
}
