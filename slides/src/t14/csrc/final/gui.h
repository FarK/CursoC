#ifndef GUI_H_
#define GUI_H_

#include "world.h"

struct gui;

struct gui *gui_alloc(const char *builder_file, struct world *w,
		      int ws_x, int ws_y);
void gui_free(struct gui *g);

#endif
