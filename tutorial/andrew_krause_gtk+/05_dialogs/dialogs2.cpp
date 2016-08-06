/* Nonmodal Message Dialog
   see: GTK_DIALOG_DESTROY_WITH_PARENT
        compare dialogs2.cpp with dialogs.cpp
*/
#include <gtk/gtk.h>

void destroy(GtkWidget*, gpointer) { gtk_main_quit(); }
void button_clicked (GtkButton*, GtkWindow*);

int main(int argc, char** argv)
{
	gtk_init(&argc, &argv);

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Dialogs");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(destroy), 0);

	GtkWidget* button = gtk_button_new_with_mnemonic ("_Click Me");
	g_signal_connect (G_OBJECT(button),
	                  "clicked",
	                  G_CALLBACK(button_clicked),
	                  (gpointer) window);

	gtk_container_add (GTK_CONTAINER(window), button);
	gtk_widget_show_all (window);

	gtk_main();
	return 0;
}


/* Create a new GtkDialog that will tell the user that the button was clicked. */
void button_clicked (GtkButton* button, GtkWindow* parent)
{
	/* Create a new dialog with one OK button. */
	GtkWidget* dialog = gtk_dialog_new_with_buttons ("Information",
	                                                 parent,
	                                             GTK_DIALOG_DESTROY_WITH_PARENT,
	                                                 GTK_STOCK_OK,
	                                                 GTK_RESPONSE_OK,
	                                                 NULL);
	gtk_dialog_set_has_separator (GTK_DIALOG(dialog), FALSE);
	GtkWidget* label = gtk_label_new ("The button was clicked!");
	GtkWidget* image = gtk_image_new_from_stock (GTK_STOCK_DIALOG_INFO,
	                                             GTK_ICON_SIZE_DIALOG);
	GtkWidget* hbox = gtk_hbox_new (FALSE, 5);
	gtk_container_set_border_width (GTK_CONTAINER(hbox), 10);
	gtk_box_pack_start_defaults (GTK_BOX(hbox), image);
	gtk_box_pack_start_defaults (GTK_BOX(hbox), label);

	/* Pack the dialog content into the dialog's GtkVBox. */
	gtk_box_pack_start_defaults (GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox);
	gtk_widget_show_all (dialog);

	/* Call gtk_widget_destroy() when the dialog emits the response signal. */
	g_signal_connect (G_OBJECT(dialog),
	                  "response",
	                  G_CALLBACK(gtk_widget_destroy),
	                  NULL);
}
