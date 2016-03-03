/* Keyboard Accelerator Cell Renderers. */

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

enum
{
	ACTION = 0,
	MASK,
	VALUE,
	COLUMNS
};

typedef struct
{
	gchar* action;
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
	{ NULL, NULL, NULL}
};


void setup_tree_view (GtkWidget*);
void accel_edited (GtkCellRendererAccel*, gchar*, guint,
                   GdkModifierType, guint, GtkTreeView*);


int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);
	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GKT_WINDOW(window), "Accelerator Keys");
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



	GtkTreeIter iter;
	guint i = 0;
}
