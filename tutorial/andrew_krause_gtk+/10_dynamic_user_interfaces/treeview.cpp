#include <gtk/gtk.h>
#include <glade/glade.h>


int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GladeXML* xml = glade_xml_new ("treeview.glade", NULL, NULL);
	GtkWidget* window = glade_xml_get_widget (xml, "window");

	glade_xml_signal_autoconnect (xml);

	GtkWidget* treeview = glade_xml_get_widget (xml, "treeview1");

	/* 1 renderer defined per column */
	GtkCellRenderer* renderer = gtk_cell_renderer_text_new ();
	GtkTreeViewColumn* column = gtk_tree_view_column_new_with_attributes (
		"Name",     // title
		renderer,   // cell
		"text",     // ,...
		0,
		NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW(treeview), column);
	/* repeat for another column */


	GtkTreeStore* store = gtk_tree_store_new (1, G_TYPE_STRING);
	GtkTreeIter iter, child;
	gtk_tree_store_append (store, &iter, NULL);
	gtk_tree_store_set (store,         // store
	                    &iter,         // iterator
	                    0,             // column index
	                    "first",       // assoc. value
	                    -1);           // -1 -> end

	gtk_tree_store_append (store, &child, &iter);
	gtk_tree_store_set (store,
	                    &child,
	                    0,
	                    "second",
	                    -1);

	gtk_tree_view_set_model (GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
	gtk_tree_view_expand_all (GTK_TREE_VIEW(treeview));
	g_object_unref (store);

	gtk_widget_show_all (window);
	gtk_main ();

	return 0;
}
