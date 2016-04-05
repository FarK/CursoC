#include <stdio.h>
#include <stdlib.h>
#include "person.h"

int main()
{
	struct person *p;

	p = person_alloc();

	if (!p) {
		printf("Error: cannot allocate a person\n");
		return EXIT_FAILURE;
	}

	person_set_name(p, "Alice Smith");
	person_set_dni(p, "12345678W");
	person_set_age(p, 25);
	person_print(p);

	person_free(p);

	return EXIT_SUCCESS;
}
