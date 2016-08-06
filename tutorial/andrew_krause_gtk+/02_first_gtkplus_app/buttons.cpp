#include <gtk/gtk.h>

void destroy (GtkWidget*, gpointer);
int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Buttons");
	gtk_container_set_border_width (GTK_CONTAINER(window), 25);
	gtk_widget_set_size_request (window, 200, 100);
	g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(destroy), NULL);

	GtkWidget* button = gtk_button_new_with_mnemonic ("_Cose"); // Alt+C
	gtk_button_set_relief (GTK_BUTTON(button), GTK_RELIEF_NONE);
	g_signal_connect_swapped (G_OBJECT(button), "clicked",
	                          G_CALLBACK(gtk_widget_destroy),
	                          (gpointer)window);

	gtk_container_add (GTK_CONTAINER(window), button);
	gtk_widget_show_all (window);

	gtk_main ();
	return 0;
}

void destroy (GtkWidget*, gpointer)
{
	gtk_main_quit ();
}
