int main()
{
	int i, j;
	int **array;

	/* Reservamos */
	array = (int **)malloc(ROWS * sizeof(int *));
	for (i = 0; i < ROWS; i++)
		array[i] = (int *)malloc(COLS * sizeof(int)); // Falta comprobar

	/* Inicializamos */
	for (i = 0; i < ROWS; i++)
		for (j = 0; j < ROWS; j++)
			array[i][j] = i * 10 + j;

	/* Imprimimos */
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < ROWS; j++) {
			printf("%02d ", array[i][j]);
		}
		printf("\n");
	}

	/* Liberamos */
	for (i = 0; i < ROWS; i++)
		free(array[i]);

	return 0;
}
