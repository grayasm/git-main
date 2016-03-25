/* Loading a Menu with GtkUIManager */
#include <gtk/gtk.h>

/* All of the menu item callback functions have a GtkMenuItem parameter, and
   receive the same gpointer value. There is only one callback function shown
   since all of the rest will be formatted in the same mannger.
*/
void open (GtkMenuItem* menuitem, gpointer data) { }
void save (GtkMenuItem* menuitem, gpointer data) { }
void quit (GtkMenuItem* menuitem, gpointer data) { }
void cut  (GtkMenuItem* menuitem, gpointer data) { }
void copy (GtkMenuItem* menuitem, gpointer data) { }
void paste(GtkMenuItem* menuitem, gpointer data) { }
void selectall (GtkMenuItem *menuitem, gpointer data) { }
void deselect (GtkMenuItem *menuitem, gpointer data) { }
void help (GtkMenuItem *menuitem, gpointer data) { }
void about(GtkMenuItem *menuitem, gpointer data) { }


#define NUM_ENTRIES 13
GtkActionEntry entries[]=
{
	{ "File", NULL, "_File", NULL, NULL, NULL },
	{ "Open", GTK_STOCK_OPEN, NULL, NULL, "Open an existing file", G_CALLBACK (open)},
	{ "Save", GTK_STOCK_SAVE, NULL, NULL, "Save the doc to a file", G_CALLBACK(save)},
	{ "Quit", GTK_STOCK_QUIT, NULL, NULL, "Quit the application",  G_CALLBACK(quit)},
	{ "Edit", NULL, "_Edit", NULL, NULL, NULL},
	{ "Cut", GTK_STOCK_CUT, NULL, NULL, "Cut to clipboard", G_CALLBACK(cut)},
	{ "Copy", GTK_STOCK_COPY, NULL, NULL, "Copy to clipboard", G_CALLBACK(copy)},
	{ "Paste", GTK_STOCK_PASTE, NULL, NULL, "Paste from clipboard", G_CALLBACK(paste)},
	{ "SelectAll", GTK_STOCK_SELECT_ALL, NULL, NULL, "Select all", G_CALLBACK(selectall)},
	{ "Deselect", NULL, "_Deselect", "<control>d", "Deselect all", G_CALLBACK(deselect)},
	{ "Help", NULL, "_Help", NULL, NULL, NULL},
	{ "Contents", GTK_STOCK_HELP, NULL, NULL, "Get help", G_CALLBACK(help)},
	{ "About", GTK_STOCK_ABOUT, NULL, NULL, "More info", G_CALLBACK(about)}
};

int main (int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "UI Manager");
	gtk_widget_set_size_request (window, 250, -1);
	g_signal_connect (G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),0);

	/* Create a new action group and add all of the actions to it. */
	GtkActionGroup* group = gtk_action_group_new ("MainActionGroup");
	gtk_action_group_add_actions (group, entries, NUM_ENTRIES, NULL);

	/* Create a new UI manager and build the menu bar and toolbar. */
	GtkUIManager* uimanager = gtk_ui_manager_new ();
	gtk_ui_manager_insert_action_group (uimanager, group, 0);
	gtk_ui_manager_add_ui_from_file (uimanager, "menu.ui", NULL);
	gtk_ui_manager_add_ui_from_file (uimanager, "toolbar.ui", NULL);

	/* Retrieve the necessary widgets and associate accelerators. */
	GtkWidget* menubar = gtk_ui_manager_get_widget (uimanager, "/MenuBar");
	GtkWidget* toolbar = gtk_ui_manager_get_widget (uimanager, "/Toolbar");
	gtk_toolbar_set_style (GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
	gtk_window_add_accel_group (GTK_WINDOW(window),
	                            gtk_ui_manager_get_accel_group (uimanager));

	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	gtk_box_pack_start_defaults (GTK_BOX(vbox), menubar);
	gtk_box_pack_start_defaults (GTK_BOX(vbox), toolbar);

	gtk_container_add (GTK_CONTAINER (window), vbox);
	gtk_widget_show_all (window);

	gtk_main ();
	return 0;
}
