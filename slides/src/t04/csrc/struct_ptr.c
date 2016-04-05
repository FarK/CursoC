#include <stdio.h>

struct cell {
	int state;
	int size;
};

int main()
{
	struct cell culture[5] = {{1,10}, {0,342}, {1,7}, {1,50}, {1,77}};
	struct cell *c;

	for (c = culture; c <= &culture[4]; c++)
		printf("{%d, %d}\n", c->state, c->size);

	return 0;
};
