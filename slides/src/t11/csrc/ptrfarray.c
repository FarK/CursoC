#include <stdio.h>

void es() { printf("Hola\n");  }
void en() { printf("Hello\n"); }
void fr() { printf("Salut\n"); }

int main()
{
	void (*salute[])() = {es, en, fr};

	printf("Chose an option:\n"
		"\t0- spanish\n"
		"\t1- english\n"
		"\t2- french\n"
	);

	salute[getchar() - '0']();

	switch (getchar()) {
		case '0': es(); break;
		case '1': en(); break;
		case '2': fr(); break;
		default : es();
	};

	return 0;
}
