#include <gtk/gtk.h>

void destroy(GtkWidget*, gpointer) { gtk_main_quit(); }

int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);

	/* Create a new GtkFileChooserDialog that will be used to create
	   a new folder. */
	GtkWidget* dialog = gtk_file_chooser_dialog_new ("Create a Folder ...",
	                                                 NULL,
	                                      GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER,
	                                                 GTK_STOCK_CANCEL,
	                                                 GTK_RESPONSE_CANCEL,
	                                                 GTK_STOCK_OK,
	                                                 GTK_RESPONSE_OK,
	                                                 NULL);

	gint result = gtk_dialog_run (GTK_DIALOG(dialog));
	if (result == GTK_RESPONSE_OK)
	{
		gchar* filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(dialog));
		g_print ("Create directory: %s\n", filename);
	}

	gtk_widget_destroy (dialog);
	return 0;
}
