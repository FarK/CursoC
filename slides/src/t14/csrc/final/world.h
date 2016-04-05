#ifndef _WORLD_H_
#define _WORLD_H_

#include <stdbool.h>

struct world;

struct world *world_alloc(int size_x, int size_y);
void world_free(struct world *w);
void world_init(struct world *w);

int world_get_sizex(const struct world *w);
int world_get_sizey(const struct world *w);
bool world_get_cell(const struct world *w, int x, int y);
void world_set_cell(struct world *w, int x, int y, bool val);
void world_iterate(struct world *w);

void world_print(const struct world *w);

#endif
