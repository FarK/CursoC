#include "world.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct world
{
	bool *cells[2];
	int current_buf;
	int size_x;
	int size_y;
};

static void fix_coords(const struct world *w, int *x, int *y);
static bool get_cell(const struct world *w, int x, int y);
static void set_cell(struct world *w, int buf, int x, int y, bool val);
static int count_neighbors(const struct world *w, int x, int y);

struct world *world_alloc(int size_x, int size_y)
{
	struct world *w;

	w = (struct world *)malloc(sizeof(struct world));
	if (!w)
		return NULL;
	w->cells[0] = (bool *)malloc(size_x * size_y * sizeof(bool));
	w->cells[1] = (bool *)malloc(size_x * size_y * sizeof(bool));
	if (!w->cells[0] || !w->cells[1])
		return NULL;

	w->size_x = size_x - 1;
	w->size_y = size_y - 1;

	return w;
}

void world_free(struct world *w)
{
	free(w->cells[0]);
	free(w->cells[1]);
	free(w);
}

void world_init(struct world *w)
{
	memset(w->cells[0], 0, w->size_x * w->size_y * sizeof(bool));
	memset(w->cells[1], 0, w->size_x * w->size_y * sizeof(bool));
	w->current_buf = 0;

	/* Glider */
	set_cell(w, 0, 0, 1, true);
	set_cell(w, 0, 1, 2, true);
	set_cell(w, 0, 2, 0, true);
	set_cell(w, 0, 2, 1, true);
	set_cell(w, 0, 2, 2, true);
}

int world_get_sizex(const struct world *w)
{
	return w->size_x;
}
int world_get_sizey(const struct world *w)
{
	return w->size_y;
}

static void fix_coords(const struct world *w, int *x, int *y)
{
	if (*x >= w->size_x)
		*x = 0;
	else if (*x < 0)
		*x = w->size_x - 1;

	if (*y >= w->size_y)
		*y = 0;
	else if (*y < 0)
		*y = w->size_y - 1;
}

inline static bool get_cell(const struct world *w, int x, int y)
{
	return *(w->cells[w->current_buf] + x * w->size_y + y);
}

bool world_get_cell(const struct world *w, int x, int y)
{
	fix_coords(w, &x, &y);
	return get_cell(w, x, y);
}

inline static void set_cell(struct world *w, int buf, int x, int y, bool val)
{
	*(w->cells[buf] + x * w->size_y + y) = val;
}

void world_set_cell(struct world *w, int x, int y, bool val)
{
	fix_coords(w, &x, &y);
	set_cell(w, w->current_buf, x, y, val);
}

static int count_neighbors(const struct world *w, int x, int y)
{
	int count = 0;

	count += world_get_cell(w, x - 1, y + 1);
	count += world_get_cell(w, x - 0, y + 1);
	count += world_get_cell(w, x + 1, y + 1);
	count += world_get_cell(w, x - 1, y + 0);
	count += world_get_cell(w, x + 1, y + 0);
	count += world_get_cell(w, x - 1, y - 1);
	count += world_get_cell(w, x - 0, y - 1);
	count += world_get_cell(w, x + 1, y - 1);

	return count;
}

void world_iterate(struct world *w)
{
	int neighbors;

	for (int i = 0; i < w->size_x; i++) {
		for (int j = 0; j < w->size_y; j++) {
			neighbors = count_neighbors(w, i, j);
			if (world_get_cell(w, i, j))
				set_cell(w, !w->current_buf, i, j,
					 neighbors == 2 || neighbors == 3);
			else
				set_cell(w, !w->current_buf, i, j,
					 neighbors == 3);
		}
	}

	w->current_buf = !w->current_buf;
}

void world_print(const struct world *w)
{
	for (int i = 0; i < w->size_x; i++) {
		for (int j = 0; j < w->size_y; j++)
			printf("%s", get_cell(w, i, j)? "o" : ".");
		printf("\n");
	}
	printf("\n");
}
