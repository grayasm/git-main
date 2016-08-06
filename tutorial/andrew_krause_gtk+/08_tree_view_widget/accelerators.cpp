/* Keyboard Accelerator Cell Renderers. */

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <gdk/gdktypes.h>

enum
{
	ACTION = 0,
	MASK,
	VALUE,
	COLUMNS
};

typedef struct
{
	const gchar* action;
	GdkModifierType mask;
	guint value;
} Accelerator;

const Accelerator list[] =
{
	{ "Cut",   GDK_CONTROL_MASK, GDK_X },
	{ "Copy",  GDK_CONTROL_MASK, GDK_C },
	{ "Paste", GDK_CONTROL_MASK, GDK_V },
	{ "New",   GDK_CONTROL_MASK, GDK_N },
	{ "Open",  GDK_CONTROL_MASK, GDK_0 },
	{ "Print", GDK_CONTROL_MASK, GDK_P },
	{ NULL,    GDK_CONTROL_MASK, 0}
};


void setup_tree_view (GtkWidget*);
void accel_edited (GtkCellRendererAccel*, gchar*, guint,
                   GdkModifierType, guint, GtkTreeView*);


int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);
	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Accelerator Keys");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	gtk_widget_set_size_request (window, 250, 250);
	g_signal_connect (G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),0);

	GtkWidget* treeview = gtk_tree_view_new ();
	setup_tree_view (treeview);

	GtkListStore* store = gtk_list_store_new (COLUMNS,
	                                          G_TYPE_STRING,
	                                          G_TYPE_INT,
	                                          G_TYPE_UINT);

	/* Add all of the keyboard accelerators to the GtkListStore. */
	guint i = 0;
	GtkTreeIter iter;
	while (list[i].action != NULL)
	{
		gtk_list_store_append (store, &iter);
		gtk_list_store_set (store, &iter, ACTION, list[i].action,
		                    MASK, (gint) list[i].mask, VALUE, list[i].value, -1);
		i++;
	}

	gtk_tree_view_set_model (GTK_TREE_VIEW (treeview), GTK_TREE_MODEL(store));
	g_object_unref (store);

	GtkWidget* scrolled_win = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled_win),
	                                GTK_POLICY_AUTOMATIC,
	                                GTK_POLICY_AUTOMATIC);
	gtk_container_add (GTK_CONTAINER(scrolled_win), treeview);
	gtk_container_add (GTK_CONTAINER(window), scrolled_win);
	gtk_widget_show_all (window);

	gtk_main ();
	return 0;
}


/* Create a tree view with 2 columns. The 1st is an action and the
   2nd is a keyboard accelerator.
*/
void setup_tree_view (GtkWidget* treeview)
{
	GtkCellRenderer* renderer = gtk_cell_renderer_text_new ();
	GtkTreeViewColumn* column = gtk_tree_view_column_new_with_attributes (
		                                                      "Buy",
		                                                      renderer,
		                                                      "text",
		                                                      ACTION,
		                                                      NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), column);

	renderer = gtk_cell_renderer_accel_new ();
	g_object_set (renderer,
	              "accel-mode",
	              GTK_CELL_RENDERER_ACCEL_MODE_GTK,
	              "editable",
	              TRUE,
	              NULL);

	column = gtk_tree_view_column_new_with_attributes ("Buy",
	                                                   renderer,
	                                                   "accel-mods",
	                                                   MASK,
	                                                   "accel-key",
	                                                   VALUE,
	                                                   NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW(treeview), column);
	g_signal_connect (G_OBJECT(renderer),
	                  "accel_edited",
	                  G_CALLBACK(accel_edited),
	                  (gpointer) treeview);
}

/* Apply the new keyboard accelerator key and mask to the cell. */
void accel_edited (GtkCellRendererAccel* renderer,
                   gchar* path,
                   guint accel_key,
                   GdkModifierType mask,
                   guint hardware_keycode,
                   GtkTreeView* treeview)
{
	GtkTreeModel* model = gtk_tree_view_get_model (treeview);
	GtkTreeIter iter;
	if (gtk_tree_model_get_iter_from_string (model, &iter, path))
		gtk_list_store_set (GTK_LIST_STORE (model),
		                    &iter,
		                    MASK,
		                    (gint) mask,
		                    VALUE,
		                    accel_key,
		                    -1);
}
