#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include "gui.h"
#include "world.h"

#define WORLD_X 200
#define WORLD_Y 100
#define WINDOW_X 800
#define WINDOW_Y 400

int main(int argc, char **argv)
{
	struct world *w;
	struct gui *g;

	gtk_init(&argc, &argv);

	w = world_alloc(WORLD_X, WORLD_Y);
	if (!w) {
		perror("Can't allocate world");
		exit(EXIT_FAILURE);
	}
	world_init(w);

	g = gui_alloc("builder.ui", w, WINDOW_X, WINDOW_Y);
	if (!g) {
		perror("Can't create gui");
		exit(EXIT_FAILURE);
	}

	gtk_main();

	world_free(w);
	gui_free(g);

	return 0;
}
