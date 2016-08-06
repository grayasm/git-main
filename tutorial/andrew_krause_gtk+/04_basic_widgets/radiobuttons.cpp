#include <gtk/gtk.h>

void destroy(GtkWidget*, gpointer*){ gtk_main_quit(); }

int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Radio Buttons");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	g_signal_connect (G_OBJECT(window),
	                  "destroy",
	                  G_CALLBACK(destroy),
	                  window);

	/* Create three radio buttons where the second two join radio1's group. */
	GtkWidget* radio1 = gtk_radio_button_new_with_label (
		NULL,
		"I want to be clicked!");

	GtkWidget* radio2 = gtk_radio_button_new_with_label_from_widget (
		GTK_RADIO_BUTTON(radio1),
		"Clicke me instead!");

	GtkWidget* radio3 = gtk_radio_button_new_with_label_from_widget (
		GTK_RADIO_BUTTON(radio1),
		"No! Click me!");

	/* Note: The radio button you create the new widget from does no matter
	   as long as it is already a member of the group.
	*/
	GtkWidget* radio4 = gtk_radio_button_new_with_label_from_widget (
		GTK_RADIO_BUTTON(radio3),
		"No! Click me instead!");

	GtkWidget* vbox = gtk_vbox_new (FALSE, 5);
	gtk_box_pack_start_defaults (GTK_BOX(vbox), radio1);
	gtk_box_pack_start_defaults (GTK_BOX(vbox), radio2);
	gtk_box_pack_start_defaults (GTK_BOX(vbox), radio3);
	gtk_box_pack_start_defaults (GTK_BOX(vbox), radio4);

	gtk_container_add (GTK_CONTAINER(window), vbox);
	gtk_widget_show_all (window);

	gtk_main ();
	return 0;
}
