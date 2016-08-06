#include <gtk/gtk.h>

typedef struct
{
	GtkWidget* window;
	GtkWidget* label;
} Widgets;

int main(int argc, char** argv)
{
	Widgets* w = g_slice_new (Widgets);

	gtk_init (&argc, &argv);
	w->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	w->label = gtk_label_new ("I'm allocated with g_slice_new :)");

	gtk_container_add (GTK_CONTAINER(w->window), w->label);
	g_signal_connect (G_OBJECT(w->window), "destroy", G_CALLBACK(gtk_main_quit), 0);
	gtk_widget_set_size_request (w->window, 200, 100);
	gtk_widget_show_all (w->window);
	gtk_main ();

	g_slice_free (Widgets, w);
	return 0;
}
