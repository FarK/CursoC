int array[3] = {1, 2, 3};
int *p = array;
int i;

/* Todas las direcciones iguales */
printf("%p\n%p\n%p\n", array, p, &array[0]);

p[2] = 22;
p += 1;
*p = 33;
*(p - 1) = 11;

/* Que imprimira? */
for (i = 0; i < 3; i++)
	printf("%d\n", array[i]);
