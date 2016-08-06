#include <gtk/gtk.h>

void create_toolbar (GtkWidget*, GtkWidget*);
void select_all (GtkEditable*);

int main (int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Toolbars");
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	gtk_widget_set_size_request (window, 325, -1);

	g_signal_connect (G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),0);

	GtkWidget* entry = gtk_entry_new ();
	GtkWidget* toolbar = gtk_toolbar_new ();
	create_toolbar (toolbar, entry);

	GtkWidget* vbox = gtk_vbox_new (FALSE, 5);
	gtk_box_pack_start_defaults (GTK_BOX(vbox), toolbar);
	gtk_box_pack_start_defaults (GTK_BOX(vbox), entry);

	gtk_container_add (GTK_CONTAINER(window), vbox);
	gtk_widget_show_all (window);

	gtk_main();
	return 0;
}

/* Create a toolbar with Cut, Copy, Paste and Select All toolbar items. */
void create_toolbar (GtkWidget* toolbar, GtkWidget* entry)
{
	GtkToolItem* cut  = gtk_tool_button_new_from_stock (GTK_STOCK_CUT);
	GtkToolItem* copy = gtk_tool_button_new_from_stock (GTK_STOCK_COPY);
	GtkToolItem* paste= gtk_tool_button_new_from_stock (GTK_STOCK_PASTE);
	GtkToolItem* selectall = gtk_tool_button_new_from_stock (GTK_STOCK_SELECT_ALL);
	GtkToolItem* separator = gtk_separator_tool_item_new ();

	gtk_toolbar_set_show_arrow (GTK_TOOLBAR(toolbar), TRUE);
	gtk_toolbar_set_style (GTK_TOOLBAR (toolbar), GTK_TOOLBAR_BOTH);

	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), cut, 0);
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), copy, 1);
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), paste, 2);
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), separator, 3);
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), selectall, 4);

	g_signal_connect_swapped (G_OBJECT (cut),
	                          "clicked",
	                          G_CALLBACK (gtk_editable_cut_clipboard),
	                          entry);
	g_signal_connect_swapped (G_OBJECT (copy),
	                          "clicked",
	                          G_CALLBACK (gtk_editable_copy_clipboard),
	                          entry);
	g_signal_connect_swapped (G_OBJECT (paste),
	                          "clicked",
	                          G_CALLBACK (gtk_editable_paste_clipboard),
	                          entry);
	g_signal_connect_swapped (G_OBJECT (selectall),
	                          "clicked",
	                          G_CALLBACK (select_all),
	                          entry);
}

/* Select all of the text in the GtkEditable. */
void select_all (GtkEditable* entry)
{
	gtk_editable_select_region (entry, 0, -1);
}
