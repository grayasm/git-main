#include <gtk/gtk.h>

int main (int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Tables");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	gtk_widget_set_size_request (window, 150, 100);

	GtkWidget* table = gtk_table_new (2, 2, TRUE);
	GtkWidget* label = gtk_label_new ("Enter the following information ...");
	GtkWidget* label2= gtk_label_new ("Name: ");
	GtkWidget* name = gtk_entry_new ();

	/* Attach the two labels and entry widget to their parent container. */
	/*
	  0-------------1-------------2
	    Enter the following ...
	  1-------------x-------------x
	    Name:         GtkEntry
	  2-------------x-------------x
	 */
	gtk_table_attach (GTK_TABLE(table),      // table
	                  label,                 // child
	                  0, 2, 0, 1,            // l,r,t,bottom
	                  GTK_EXPAND,            // xoptions
	                  GTK_SHRINK,            // yoptions
	                  0, 0);                 // x,y padding

	gtk_table_attach (GTK_TABLE (table), label2, 0, 1, 1, 2,
	                  GTK_EXPAND, GTK_SHRINK, 0, 0);
	gtk_table_attach (GTK_TABLE (table), name, 1, 2, 1, 2,
	                  GTK_EXPAND, GTK_SHRINK, 0, 0);


	/* Add 5 pixels of spacing between every row and every column. */
	gtk_table_set_row_spacings (GTK_TABLE(table), 5);
	gtk_table_set_col_spacings (GTK_TABLE(table), 5);

	gtk_container_add (GTK_CONTAINER(window), table);
	gtk_widget_show_all (window);

	gtk_main ();
	return 0;
}
