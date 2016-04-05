#include <stdio.h>
#include "world.h"

int main()
{
	struct world *w;

	w = world_alloc(10, 10);
	world_init(w);
	world_print(w);

	do {
		world_iterate(w);
		world_print(w);
	} while(getchar() != 'q');

	world_free(w);

	return 0;
}
