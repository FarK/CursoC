#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#define BUILDER_FILE "builder.ui"

static void button_cb(GtkWidget *widget, const char *str);

int main(int argc, char **argv)
{
	GtkBuilder *builder;
	GtkWidget *window;
	GtkWidget *button1;
	GtkWidget *button2;

	gtk_init(&argc, &argv);

	/* builder */
	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file(builder, BUILDER_FILE, NULL)) {
		fprintf(stderr, "Can't open file \"%s\"\n", BUILDER_FILE);
		exit(EXIT_FAILURE);
	}

	/* objects */
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
	button2 = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));

	/* signals */
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(button1, "clicked", G_CALLBACK(button_cb), "Hola");
	g_signal_connect(button2, "clicked", G_CALLBACK(button_cb), "Adios");
	gtk_builder_connect_signals(builder, NULL);

	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}

static void button_cb(GtkWidget *widget, const char *str)
{
	printf("%s mundo!\n", str);
}
