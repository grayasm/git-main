#include <gtk/gtk.h>

int main(int argc, char** argv)
{
	gtk_init(&argc, &argv);

	GtkWidget* dialog = gtk_dialog_new_with_buttons("Edit User Information",
	                                                NULL,
	                                                GTK_DIALOG_MODAL,
	                                                GTK_STOCK_OK,
	                                                GTK_RESPONSE_OK,
	                                                GTK_STOCK_CANCEL,
	                                                GTK_RESPONSE_CANCEL,
	                                                NULL);
	gtk_dialog_set_default_response (GTK_DIALOG(dialog), GTK_RESPONSE_OK);

	/* Create four entries that will tell the user what data to enter. */
	GtkWidget* lbl1 = gtk_label_new ("User Name:");
	GtkWidget* lbl2 = gtk_label_new ("Real Name:");
	GtkWidget* lbl3 = gtk_label_new ("Home Dir:");
	GtkWidget* lbl4 = gtk_label_new ("Host Name:");

	GtkWidget* user = gtk_entry_new ();
	GtkWidget* real = gtk_entry_new ();
	GtkWidget* home = gtk_entry_new ();
	GtkWidget* host = gtk_entry_new ();

	/* Retrieve the user's information for the default values. */
	gtk_entry_set_text (GTK_ENTRY(user), g_get_user_name());
	gtk_entry_set_text (GTK_ENTRY(real), g_get_real_name());
	gtk_entry_set_text (GTK_ENTRY(home), g_get_home_dir());
	gtk_entry_set_text (GTK_ENTRY(host), g_get_host_name());

	GtkWidget* table = gtk_table_new (4, 2, FALSE);
	gtk_table_attach_defaults (GTK_TABLE(table), lbl1, 0, 1, 0, 1);//l,r,t,b
	gtk_table_attach_defaults (GTK_TABLE(table), lbl2, 0, 1, 1, 2);
	gtk_table_attach_defaults (GTK_TABLE(table), lbl3, 0, 1, 2, 3);
	gtk_table_attach_defaults (GTK_TABLE(table), lbl4, 0, 1, 3, 4);
	gtk_table_attach_defaults (GTK_TABLE(table), user, 1, 2, 0, 1);
	gtk_table_attach_defaults (GTK_TABLE(table), real, 1, 2, 1, 2);
	gtk_table_attach_defaults (GTK_TABLE(table), home, 1, 2, 2, 3);
	gtk_table_attach_defaults (GTK_TABLE(table), host, 1, 2, 3, 4);

	gtk_table_set_row_spacings (GTK_TABLE(table), 5);
	gtk_table_set_col_spacings (GTK_TABLE(table), 5);
	gtk_container_set_border_width (GTK_CONTAINER(table), 5);

	gtk_box_pack_start_defaults (GTK_BOX(GTK_DIALOG(dialog)->vbox), table);
	gtk_widget_show_all (dialog);

	/* Run the dialog and output the data if the user clicks the OK button. */
	gint result = gtk_dialog_run(GTK_DIALOG(dialog));
	if (result == GTK_RESPONSE_OK)
	{
		g_print ("User Name: %s\n", gtk_entry_get_text (GTK_ENTRY(user)));
		g_print ("Real Name: %s\n", gtk_entry_get_text (GTK_ENTRY(real)));
		g_print ("Home Folder: %s\n", gtk_entry_get_text (GTK_ENTRY(home)));
		g_print ("Host Name: %s\n", gtk_entry_get_text (GTK_ENTRY(host)));
	}

	gtk_widget_destroy (dialog);
	return 0;
}
