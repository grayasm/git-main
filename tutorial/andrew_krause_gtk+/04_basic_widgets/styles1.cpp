#include <gtk/gtk.h>

void destroy (GtkWidget*, gpointer) { gtk_main_quit(); }
int main (int argc, char** argv)
{
	gtk_init (&argc, &argv);

	gtk_rc_parse ("styles1.gtkrc");

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Styles1");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(destroy), 0);

	GtkWidget* vbox = gtk_vbox_new (FALSE, 4);
	GtkWidget* label = gtk_label_new ("GtkLabel");
	GtkWidget* button = gtk_button_new_with_label ("GtkButton");
	GtkWidget* checkbn = gtk_check_button_new_with_label ("GtkCheckButton");
	GtkWidget* togglebn = gtk_toggle_button_new_with_label ("GtkToggleButton");

	gtk_box_pack_start_defaults (GTK_BOX(vbox), label);
	gtk_box_pack_start_defaults (GTK_BOX(vbox), button);
	gtk_box_pack_start_defaults (GTK_BOX(vbox), checkbn);
	gtk_box_pack_start_defaults (GTK_BOX(vbox), togglebn);

	gtk_container_add (GTK_CONTAINER(window), vbox);
	gtk_widget_show_all (window);

	gtk_main ();
	return 0;
}
