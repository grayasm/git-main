/* A GtkMenuBar widget with 3 menus: File, Edit and Help.
   Each of the menus is actually a GtkMenuItem with a submenu.
   A number of menu items are then added to each submenu.
*/

#include <gtk/gtk.h>

int main (int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Menu Bars");
	gtk_widget_set_size_request (window, 250, -1);
	g_signal_connect (G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),0);

	GtkAccelGroup* group = gtk_accel_group_new ();
	GtkWidget* menubar = gtk_menu_bar_new ();
	GtkWidget* file = gtk_menu_item_new_with_label ("File");
	GtkWidget* edit = gtk_menu_item_new_with_label ("Edit");
	GtkWidget* help = gtk_menu_item_new_with_label ("Help");

	GtkWidget* filemenu = gtk_menu_new ();
	GtkWidget* editmenu = gtk_menu_new ();
	GtkWidget* helpmenu = gtk_menu_new ();

	gtk_menu_item_set_submenu (GTK_MENU_ITEM(file), filemenu);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM(edit), editmenu);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM(help), helpmenu);

	gtk_menu_shell_append (GTK_MENU_SHELL(menubar), file);
	gtk_menu_shell_append (GTK_MENU_SHELL(menubar), edit);
	gtk_menu_shell_append (GTK_MENU_SHELL(menubar), help);

	/* Create the File menu content. */
	GtkWidget* New = gtk_image_menu_item_new_from_stock (GTK_STOCK_NEW, group);
	GtkWidget* Open= gtk_image_menu_item_new_from_stock (GTK_STOCK_OPEN, group);
	gtk_menu_shell_append (GTK_MENU_SHELL(filemenu), New);
	gtk_menu_shell_append (GTK_MENU_SHELL(filemenu), Open);

	/* Create the Edit menu content. */
	GtkWidget* Cut  = gtk_image_menu_item_new_from_stock (GTK_STOCK_CUT, group);
	GtkWidget* Copy = gtk_image_menu_item_new_from_stock (GTK_STOCK_COPY, group);
	GtkWidget* Paste= gtk_image_menu_item_new_from_stock (GTK_STOCK_PASTE, group);
	gtk_menu_shell_append (GTK_MENU_SHELL (editmenu), Cut);
	gtk_menu_shell_append (GTK_MENU_SHELL (editmenu), Copy);
	gtk_menu_shell_append (GTK_MENU_SHELL (editmenu), Paste);

	/* Create the Help menu content. */
	GtkWidget* contents = gtk_image_menu_item_new_from_stock (GTK_STOCK_HELP, group);
	GtkWidget* about = gtk_image_menu_item_new_from_stock (GTK_STOCK_ABOUT, group);
	gtk_menu_shell_append (GTK_MENU_SHELL (helpmenu), contents);
	gtk_menu_shell_append (GTK_MENU_SHELL (helpmenu), about);

	gtk_container_add (GTK_CONTAINER (window), menubar);
	gtk_window_add_accel_group (GTK_WINDOW (window), group);

	gtk_widget_show_all (window);
	gtk_main ();
	return 0;
}
