#include <stdio.h>
#include "person.h"

void print_person(const struct person *p)
{
	printf("%s, %s\n", p->surname, p->name);
	printf("\t- age:   %d\n", p->age);
	printf("\t- phone: %d\n", p->phone);
}
