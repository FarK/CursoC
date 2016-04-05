#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <gtk/gtk.h>
#include "gui.h"
#include "world.h"

#define VEL_MS 10

struct gui {
	GtkBuilder *builder;

	GtkWidget *window;
	GtkWidget *btn_quit;
	GtkWidget *btn_step;
	GtkWidget *btn_pause;
	GtkGrid   *grid;
	GtkWidget *drawing_area;

	struct {
		double x;
		double y;
	} cell_size;

	bool run;

	struct world *world;
};

/* Callbacks */
static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, struct gui *g);
static gboolean timer_cb(gpointer gui);
static void step_cb(GtkWidget *widget, struct gui *g);
static void pause_cb(GtkWidget *widget, struct gui *g);
static gboolean mouse_btn_cb(GtkWidget *widget, GdkEventButton *e,
			     struct gui *g);

struct gui *gui_alloc(const char *builder_file, struct world *w,
		      int ws_x, int ws_y)
{
	struct gui *g;

	/* struct gui */
	g = (struct gui *)malloc(sizeof(struct gui));
	if (!g)
		return NULL;

	/* builder */
	g->builder = gtk_builder_new();
	if (!gtk_builder_add_from_file(g->builder, builder_file, NULL))
		return NULL;

	/* GObjects */
	g->window    = GTK_WIDGET(gtk_builder_get_object(g->builder, "window"));
	g->btn_quit  = GTK_WIDGET(gtk_builder_get_object(g->builder, "btn_quit"));
	g->btn_step  = GTK_WIDGET(gtk_builder_get_object(g->builder, "btn_step"));
	g->btn_pause = GTK_WIDGET(gtk_builder_get_object(g->builder, "btn_pause"));
	g->grid      = GTK_GRID(gtk_builder_get_object(g->builder,   "grid"));
	if (!(g->window && g->btn_quit && g->btn_step && g->btn_pause &&
	      g->grid)) {
		errno = EINVAL;
		return NULL;
	}

	/* drawing area */
	g->drawing_area = gtk_drawing_area_new();
	gtk_widget_set_size_request(g->drawing_area, ws_x, ws_y);
	gtk_widget_set_events(g->drawing_area,
		gtk_widget_get_events(g->drawing_area) | GDK_BUTTON_PRESS_MASK);
	gtk_grid_attach_next_to(g->grid, g->drawing_area, g->btn_quit,
			GTK_POS_BOTTOM, 1, 1);

	/* Signals */
	g_signal_connect(g->window,       "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(g->btn_quit,     "clicked", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(g->btn_step,     "clicked", G_CALLBACK(step_cb),       g);
	g_signal_connect(g->btn_pause,    "clicked", G_CALLBACK(pause_cb),      g);
	g_signal_connect(g->drawing_area, "draw",    G_CALLBACK(draw_cb),       g);
	g_signal_connect(g->drawing_area, "button-press-event", G_CALLBACK(mouse_btn_cb), g);
	gtk_builder_connect_signals(g->builder, NULL);

	if (!w) {
		errno = EINVAL;
		return NULL;
	}
	g->world = w;

	g->cell_size.x = ws_x / world_get_sizex(g->world);
	g->cell_size.y = ws_y / world_get_sizey(g->world);

	g->run = false;
	gtk_widget_show_all(g->window);

	return g;
}

void gui_free(struct gui *g)
{
	free(g);
}

static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, struct gui *g)
{
	/* Clear screen */
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_paint(cr);

	/* Paint world */
	cairo_set_source_rgb(cr, 1, 1, 1);
	for (int i = 0; i < world_get_sizex(g->world); i++)
		for (int j = 0; j < world_get_sizey(g->world); j++)
			if (world_get_cell(g->world, i, j))
				cairo_rectangle(cr,
						i*g->cell_size.x,
						j*g->cell_size.y,
						g->cell_size.x,
						g->cell_size.y);
	cairo_fill(cr);

	return false;
}

static gboolean timer_cb(gpointer gui)
{
	struct gui *g = (struct gui *)gui;
	step_cb(NULL, g);
	return g->run;
}

static void step_cb(GtkWidget *widget, struct gui *g)
{
	world_iterate(g->world);
	gtk_widget_queue_draw(g->window);
}

static void pause_cb(GtkWidget *widget, struct gui *g)
{
	if (g->run) {
		gtk_button_set_label(GTK_BUTTON(g->btn_pause), "run");
	} else {
		gtk_button_set_label(GTK_BUTTON(g->btn_pause), "pause");
		g_timeout_add(VEL_MS, timer_cb, g);
	}
	g->run = !g->run;
}

static gboolean mouse_btn_cb(GtkWidget *widget, GdkEventButton *e,
			     struct gui *g)
{
	world_set_cell(g->world, e->x / g->cell_size.x, e->y / g->cell_size.y,
		       true);
	gtk_widget_queue_draw(g->window);
}
