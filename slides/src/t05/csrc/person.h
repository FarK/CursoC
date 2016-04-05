#ifndef _PERSON_H_
#define _PERSON_H_

#define MAX_NAME 256

struct person {
	char name[MAX_NAME];
	char surname[MAX_NAME];
	unsigned int age;
	int phone;
};

void print_person(const struct person *p);

#endif
