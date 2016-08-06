#include <gtk/gtk.h>

int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Handle Box");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	gtk_widget_set_size_request (window, 200, 100);

	GtkWidget* handle = gtk_handle_box_new ();
	GtkWidget* label = gtk_label_new ("Detach Me");

	/* add a shadow to the handle box.
	   set the handle position on the left.
	   set the snap edge to the top of the widget.
	*/
	gtk_handle_box_set_shadow_type (GTK_HANDLE_BOX(handle), GTK_SHADOW_IN);
	gtk_handle_box_set_handle_position (GTK_HANDLE_BOX(handle), GTK_POS_LEFT);
	gtk_handle_box_set_snap_edge (GTK_HANDLE_BOX(handle), GTK_POS_TOP);

	gtk_container_add (GTK_CONTAINER(handle), label);
	gtk_container_add (GTK_CONTAINER(window), handle);
	gtk_widget_show_all (window);

	gtk_main ();
	return 0;
}
