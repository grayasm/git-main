#include <gtk/gtk.h>

void destroy(GtkWidget*, gpointer) { gtk_main_quit(); }

int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Button from stock");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	g_signal_connect (G_OBJECT(window),
	                  "destroy",
	                  G_CALLBACK(destroy),
	                  (gpointer)NULL);

	GtkWidget* button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);

	g_signal_connect_swapped (G_OBJECT(button),
	                          "clicked",
	                          G_CALLBACK(gtk_widget_destroy),
	                          (gpointer)window);

	gtk_container_add (GTK_CONTAINER(window), button);
	gtk_widget_show_all (window);

	gtk_main();
	return 0;
}
