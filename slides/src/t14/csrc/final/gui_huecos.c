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
		//Establecemos errno para que perror imprima el mensaje correcto
		errno = EINVAL;
		return NULL;
	}

	/* drawing area */
	g->drawing_area = gtk_drawing_area_new();
	// Tamanyo del la ventana de dibujado
	gtk_widget_set_size_request(g->drawing_area, ws_x, ws_y);
	// Necesario para capturar los click del raton
	gtk_widget_set_events(g->drawing_area,
		gtk_widget_get_events(g->drawing_area) | GDK_BUTTON_PRESS_MASK);
	// Anyadimos el nuevo widget al grid
	gtk_grid_attach_next_to(g->grid, g->drawing_area, g->btn_quit,
			GTK_POS_BOTTOM, 1, 1);

	/* Signals */
	g_signal_connect(g->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	/* TODO
	 * Conecta el resto de señales
	 */
	gtk_builder_connect_signals(g->builder, NULL);

	if (!w) {
		//Establecemos errno para que perror imprima el mensaje correcto
		errno = EINVAL;
		return NULL;
	}
	g->world = w;

	/* TODO
	 * Inicializa la estructura g->cell_size, que guarda el tamaño del
	 * rectángulo que va a representar una célula del mundo. Pista: las
	 * coordenadas del mundo no son las mismas que las de la ventana.
	 */

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

	/* TODO
	 * Dibuja el mundo sabiendo que el codigo de abajo dibuja un rectangulo
	 * blanco en las coordenadas (2, 3) de 5x4 pixeles de tamanyo
	 */
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_rectangle(cr, 2, 3, 5, 4);
	cairo_fill(cr);

	return false;
}

static gboolean timer_cb(gpointer gui)
{
	struct gui *g = (struct gui *)gui;
	step_cb(NULL, g);
	/* Si devuelve false, la senyal se desconecta y el callback no se vuelve
	 * a llamar
	 */
	return g->run;
}

static void step_cb(GtkWidget *widget, struct gui *g)
{
	world_iterate(g->world);
	gtk_widget_queue_draw(g->window);//Solicitamos que se repinte la ventana
}

static void pause_cb(GtkWidget *widget, struct gui *g)
{
	/* TODO
	 * Cambiar el label del boton de "run" a "pause" para que indique en
	 * cada momento su funcionalidad
	 */
	if (!g->run)
		g_timeout_add(VEL_MS, timer_cb, g); // Conectamos la senyal de nuevo
	g->run = !g->run;
}

static gboolean mouse_btn_cb(GtkWidget *widget, GdkEventButton *e,
			     struct gui *g)
{
	/* TODO
	 * e->x y e->y contienen las coordenadas de donde se ha hecho click con
	 * el ratón. Pista: las coordenadas del mundo no son las mismas que las
	 * de la ventana.
	 */
}
