/* Using Cell Data Functions. */

#include <gtk/gtk.h>

enum
{
	COLOR=0,
	COLUMNS
};

const gchar* clr[6] = { "00", "33", "66", "99", "CC", "FF" };

void setup_tree_view (GtkWidget*);
void cell_data_func  (GtkTreeViewColumn*,
                      GtkCellRenderer*,
                      GtkTreeModel*,
                      GtkTreeIter*,
                      gpointer);


int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Color List");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	gtk_widget_set_size_request (window, 250, 175);
	g_signal_connect (G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), 0);

	GtkWidget* treeview = gtk_tree_view_new ();
	setup_tree_view (treeview);
	GtkListStore* store = gtk_list_store_new (COLUMNS, G_TYPE_STRING);

	/* Add all of the products to the GtkListStore. */
	GtkTreeIter iter;
	for (gint i = 0; i < 6; i++)
		for (gint j = 0; j < 6; j++)
			for (gint k = 0; k < 6; k++)
			{
				gchar* color = g_strconcat ("#", clr[i], clr[j], clr[k], NULL);
				gtk_list_store_append (store, &iter);
				gtk_list_store_set (store, &iter, COLOR, color, -1);
				g_free (color);
			} // for(i,j,k)

	gtk_tree_view_set_model (GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
	g_object_unref (store);

	GtkWidget* scrolled_win = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled_win),
	                                GTK_POLICY_AUTOMATIC,
	                                GTK_POLICY_AUTOMATIC);
	gtk_container_add (GTK_CONTAINER(scrolled_win), treeview);
	gtk_container_add (GTK_CONTAINER(window), scrolled_win);
	gtk_widget_show_all (window);
	gtk_main();
	return 0;
}


/* Add three columns to the GtkTreeView. All three of the columns will be
   displayed as text, although one is a gboolean value and another is an
   integer. */
void setup_tree_view (GtkWidget* treeview)
{
	GtkCellRenderer* renderer = gtk_cell_renderer_text_new ();
	GtkTreeViewColumn* column = gtk_tree_view_column_new_with_attributes(
		                                                     "Standard Colors",
		                                                     renderer,
		                                                     "text",
		                                                     COLOR,
		                                                     NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW(treeview), column);
	gtk_tree_view_column_set_cell_data_func (column,
	                                         renderer,
	                                         cell_data_func,
	                                         NULL,
	                                         NULL);
}


void cell_data_func  (GtkTreeViewColumn* column,
                      GtkCellRenderer* renderer,
                      GtkTreeModel* model,
                      GtkTreeIter* iter,
                      gpointer data)
{
	/* Get the color string stored by the column and make it
	   the foreground color.
	*/
	gchar* text;
	gtk_tree_model_get (model, iter, COLOR, &text, -1);
	g_object_set (renderer,
	              "foreground", "#FFFFFF", "foreground-set", TRUE,
	              "background", text,      "background-set", TRUE,
	              "text", text,
	              NULL);
	g_free (text);
}
