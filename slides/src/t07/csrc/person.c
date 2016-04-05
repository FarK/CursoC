#include "person.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define DNI_LEN 9
#define ATTR_SET(flags, attr)    (flags) |= (1 << (attr))
#define ATTR_IS_SET(flags, attr) ((flags) & (1 << (attr)))

struct person {
	char *name;
	char dni[DNI_LEN];
	int  age;

	uint32_t flags;
};

enum person_attr {
	PERSON_NAME,
	PERSON_DNI,
	PERSON_AGE,
};

struct person *person_alloc()
{
	struct person *p;

	p = (struct person *)malloc(sizeof(struct person));
	p->flags = 0;

	return p;
}

void person_free(struct person *p)
{
	if (ATTR_IS_SET(p->flags, PERSON_NAME))
		free(p->name);
	free(p);
}

void person_set_name(struct person *p, const char *name)
{
	if (ATTR_IS_SET(p->flags, PERSON_NAME))
		free(p->name);

	p->name = strdup(name);
	ATTR_SET(p->flags, PERSON_NAME);
}

int person_set_dni(struct person *p, const char *dni)
{
	if (strlen(dni) != DNI_LEN)
		return 0;

	strcpy(p->dni, dni);
	ATTR_SET(p->flags, PERSON_DNI);

	return 1;
}

int person_set_age(struct person *p, int age)
{
	if (age < 0 || age > 150)
		return 0;

	p->age = age;
	ATTR_SET(p->flags, PERSON_AGE);

	return 1;
}

const char *person_get_name(const struct person *p)
{
	if (ATTR_IS_SET(p->flags, PERSON_NAME))
		return p->name;
	else
		return NULL;
}

const char *person_get_dni(const struct person *p)
{
	if (ATTR_IS_SET(p->flags, PERSON_DNI))
		return p->dni;
	else
		return NULL;
}

int person_get_age(const struct person *p)
{
	if (ATTR_IS_SET(p->flags, PERSON_AGE))
		return p->age;
	else
		return -1;
}

void person_print(const struct person *p)
{
	printf("Person {");

	if (ATTR_IS_SET(p->flags, PERSON_NAME))
		printf("\n\tname = \"%s\"", p->name);

	if (ATTR_IS_SET(p->flags, PERSON_DNI))
		printf("\n\tdni  = \"%s\"", p->dni);

	if (ATTR_IS_SET(p->flags, PERSON_AGE))
		printf("\n\tage  = %d", p->age);

	printf("\n}\n");
}
