#include <gtk/gtk.h>

#define NUM_ELEMENTS 4
const gchar* widgets[] = {"GtkDialog", "GtkWindow", "GtkContainer", "GtkWidget"};

int main (int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Automatic Completion");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);

	g_signal_connect (G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),0);

	GtkWidget* label = gtk_label_new ("Enter a widget in the following GtkEntry:");
	GtkWidget* entry = gtk_entry_new ();

	/*  Create a GtkListStore that will hold the autocompletion possibilities.
	    GtkListStore is the Model from Pattern:Model-View-Controller.
	    See 08_tree_view_widget/README.txt for extended explanation.
	*/
	GtkTreeIter iter;
	GtkListStore* store = gtk_list_store_new (1, G_TYPE_STRING);
	for (unsigned int i = 0; i < NUM_ELEMENTS; i++)
	{
		gtk_list_store_append (store, &iter);
		gtk_list_store_set (store, &iter, 0, widgets[i], -1);
	}

	GtkEntryCompletion* completion = gtk_entry_completion_new ();
	gtk_entry_set_completion (GTK_ENTRY(entry), completion);
	gtk_entry_completion_set_model (completion, GTK_TREE_MODEL (store));
	gtk_entry_completion_set_text_column (completion, 0);

	GtkWidget* vbox = gtk_vbox_new (FALSE, 5);
	gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), entry, FALSE, FALSE, 0);

	gtk_container_add (GTK_CONTAINER (window), vbox);
	gtk_widget_show_all (window);

	g_object_unref (completion);
	g_object_unref (store);

	gtk_main ();
	return 0;
}
