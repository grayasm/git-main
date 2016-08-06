/* Greeting the World Again (helloworld2.c) */

#include <gtk/gtk.h>


void destroy (GtkWidget*, gpointer);
gboolean delete_event (GtkWidget*, GdkEvent*, gpointer);

int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "second GTK+ app");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	gtk_widget_set_size_request (window, 200, 100);

	// 2.42.2 at the moment
	printf("GLib version: %d.%d.%d\n",
	       GLIB_MAJOR_VERSION,
	       GLIB_MINOR_VERSION,
	       GLIB_MICRO_VERSION);

	/* Connect the main window to the destroy and delete-event signals. */
	g_signal_connect (G_OBJECT(window),
	                  "destroy",
	                  G_CALLBACK(destroy),
	                  NULL);

	g_signal_connect (G_OBJECT(window),
	                  "delete-event",
	                  G_CALLBACK(delete_event),
	                  NULL);

	/* Create a new GtkLabel widget that is selectable. */
	GtkWidget* label = gtk_label_new ("A GTK+ Label");
	gtk_label_set_selectable (GTK_LABEL(label), TRUE);


	/* Add the label as a child widget of the window. */
	gtk_container_add (GTK_CONTAINER(window), label);
	gtk_widget_show_all (window);

	gtk_main ();

	return 0;
}


/* Stop the GTK+ main loop function when the window is destroyed. */
void destroy (GtkWidget* window, gpointer data)
{
	printf("GTK+ event: \"destroy\"\n");
	gtk_main_quit ();
}


/* Return FALSE to destroy the widget.
   By returning TRUE, you can cancel a delete-event.
   This can be used to confirm quitting the application.
*/
gboolean delete_event (GtkWidget* window, GdkEvent* event, gpointer data)
{
	printf("GTK+ event: \"delete-event\"\n");
	return FALSE;
}
