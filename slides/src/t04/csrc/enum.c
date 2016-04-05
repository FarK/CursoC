#include <stdio.h>

struct person {
	char name[256];
	char surname[256];
	unsigned char age;
	unsigned int phone;
};

enum person_attr {
	NAME,
	SURNAME,
	AGE,
	PHONE
};

int main ()
{
	person p = {"Alice", "Smith", 25, 12434321};
	enum person_attr choice = NAME;

	switch (choice) {
	case NAME:
		printf("%s\n", p.name);
		break;
	case SURNAME:
		printf("%s\n", p.surname);
		break;
	case AGE:
		printf("%d\n", p.age);
		break;
	case PHONE:
		printf("%d\n", p.phone);
		break;
	default:
		printf("error: %s:%d", __FILE__, __LINE__);
	}

	return 0;
}
