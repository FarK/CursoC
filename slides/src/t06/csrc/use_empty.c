#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person
{
	char name[200];
	char surname[200];
	unsigned char age;
};

int main()
{
	struct person *p;

	p = (struct person *)malloc(sizeof(struct person));

	strcpy(p->name, "Bob");
	strcpy(p->surname, "Smith");
	p->age = 20;

	free(p);

	printf("name    = %s\n", p->name);
	printf("surname = %s\n", p->surname);
	printf("age     = %d\n", p->age);

	return 0;
}
