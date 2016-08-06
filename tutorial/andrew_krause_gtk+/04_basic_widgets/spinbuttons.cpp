#include <gtk/gtk.h>

void destroy (GtkWidget*, gpointer) { gtk_main_quit(); }
int main (int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Spin Buttons");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	gtk_widget_set_size_request (window, 150, 100);
	g_signal_connect (G_OBJECT(window),
	                  "destroy",
	                  G_CALLBACK(destroy),
	                  window);

	/* Create two new adjustments. The first spans between 0 and 10, starting
	   at 5 and moves in increments of 1. The second spans between 0 and 1,
	   starting at 0.5 and moves in increments of 0.1
	*/
	GtkAdjustment* integer = GTK_ADJUSTMENT (gtk_adjustment_new(5,0,10,1,2,2));
	GtkAdjustment* float_pt= GTK_ADJUSTMENT (gtk_adjustment_new(0.5,0,1,0.1,0.5,0.5));

	/* Create two new spin buttons. The first display no decimal places and the
	   second will display one decimal place.
	*/
	GtkWidget* spin_int  = gtk_spin_button_new (integer, 1, 0);
	GtkWidget* spin_float= gtk_spin_button_new (float_pt, 0.1, 1);

	GtkWidget* vbox = gtk_vbox_new (FALSE, 5);
	gtk_box_pack_start_defaults (GTK_BOX(vbox), spin_int);
	gtk_box_pack_start_defaults (GTK_BOX(vbox), spin_float);

	gtk_container_add (GTK_CONTAINER(window), vbox);
	gtk_widget_show_all (window);

	gtk_main ();
	return 0;
}
