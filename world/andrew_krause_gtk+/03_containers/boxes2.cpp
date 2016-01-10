#include <gtk/gtk.h>

#define NUM_NAMES 4
const gchar* names[]= { "Andrew", "Joe", "Samantha", "Jonathan" };

int main (int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Boxes");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	gtk_widget_set_size_request (window, 200, -1);

	GtkWidget* vbox = gtk_vbox_new (TRUE, 5);

	/* Add 4 buttons to the vertical box. */
	for (int i=0; i < NUM_NAMES; ++i)
	{
		GtkWidget* button = gtk_button_new_with_label (names[i]);
		gtk_box_pack_end (GTK_BOX(vbox), button, FALSE, FALSE, 5);

		g_signal_connect_swapped (G_OBJECT(button),
		                          "clicked",
		                          G_CALLBACK(gtk_widget_destroy),
		                          (gpointer)button);
	}

	gtk_container_add (GTK_CONTAINER(window), vbox);
	gtk_widget_show_all (window);
	gtk_main ();

	return 0;
}
