#include <gtk/gtk.h>

void destroy (GtkWidget*, gpointer) { gtk_main_quit(); }
void color_changed (GtkColorButton*, GtkWidget*);

int main (int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Color Button");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(destroy), 0);

	/* Set the initial color as #003366 and set the dialog title. */
	GdkColor color;
	gdk_color_parse ("#003366", &color);

	GtkWidget* button = gtk_color_button_new_with_color (&color);
	gtk_color_button_set_title (GTK_COLOR_BUTTON(button), "Select a Color");

	GtkWidget* label = gtk_label_new ("Look at my color!");
	gtk_widget_modify_fg (label, GTK_STATE_NORMAL, &color);

	g_signal_connect (G_OBJECT(button),
	                  "color-set",
	                  G_CALLBACK(color_changed),
	                  (gpointer) label);

	GtkWidget* hbox = gtk_hbox_new (FALSE, 5);
	gtk_box_pack_start_defaults (GTK_BOX(hbox), button);
	gtk_box_pack_start_defaults (GTK_BOX(hbox), label);

	gtk_container_add (GTK_CONTAINER (window), hbox);
	gtk_widget_show_all (window);

	gtk_main();
	return 0;
}

/* Retrieve the selected color and set it as the GtkLabel's foreground color. */
void color_changed (GtkColorButton* button, GtkWidget* label)
{
	GdkColor color;
	gtk_color_button_get_color (button, &color);
	gtk_widget_modify_fg (label, GTK_STATE_NORMAL, &color);
}
