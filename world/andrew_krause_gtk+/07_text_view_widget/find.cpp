/* Using GtkTextIter Find Function. */

#include <gtk/gtk.h>

typedef struct
{
	GtkWidget* entry;
	GtkWidget* textview;
} Widgets;


void search (GtkButton*, Widgets*);

int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);

	Widgets* w = g_slice_new (Widgets);
	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Searching Buffers");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit),0);

	w->textview = gtk_text_view_new ();
	w->entry = gtk_entry_new ();
	gtk_entry_set_text (GTK_ENTRY(w->entry), "Search for ...");

	GtkWidget* find = gtk_button_new_from_stock (GTK_STOCK_FIND);
	g_signal_connect (G_OBJECT(find),
	                  "clicked",
	                  G_CALLBACK(search),
	                  (gpointer)w);

	GtkWidget* scrolled_win = gtk_scrolled_window_new (NULL, NULL);
	gtk_widget_set_size_request (scrolled_win, 250, 200);
	gtk_container_add (GTK_CONTAINER(scrolled_win), w->textview);

	GtkWidget* hbox = gtk_hbox_new (FALSE, 5);
	gtk_box_pack_start (GTK_BOX(hbox), w->entry, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX(hbox), find, FALSE, TRUE, 0);


	GtkWidget* vbox = gtk_vbox_new (FALSE, 5);
	gtk_box_pack_start (GTK_BOX(vbox), scrolled_win, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX(vbox), hbox, FALSE, TRUE, 0);

	gtk_container_add (GTK_CONTAINER(window), vbox);
	gtk_widget_show_all (window);


	gtk_main();
	return 0;
}


/* Search for the entered string within the GtkTextView. Then ell the user
   how many times it was found. */
void search (GtkButton* button, Widgets* w)
{
	const gchar* find = gtk_entry_get_text (GTK_ENTRY(w->entry));
	GtkTextBuffer* buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(w->textview));

	GtkTextIter start, begin, end;
	gtk_text_buffer_get_start_iter (buffer, &start);
	gboolean success = gtk_text_iter_forward_search (&start,
	                                                 (gchar*) find,
	                                                 GTK_TEXT_SEARCH_VISIBLE_ONLY,
	                                                 &begin,
	                                                 &end,
	                                                 NULL);


	gint begpos = gtk_text_iter_get_offset (&begin);
	gint i = (success == true ? 1 : 0);
	while (success)
	{
		gtk_text_iter_set_offset (&start, begpos + 1);

		success = gtk_text_iter_forward_search (&start,
		                                        (gchar*) find,
		                                        GTK_TEXT_SEARCH_VISIBLE_ONLY,
		                                        &begin,
		                                        &end,
		                                        NULL);

		if(success) i++;
	}

	gchar* output = g_strdup_printf ("The string '%s' was found %i times!",
	                                 find,
	                                 i);
	GtkWidget* dialog = gtk_message_dialog_new (NULL,
	                                            GTK_DIALOG_MODAL,
	                                            GTK_MESSAGE_INFO,
	                                            GTK_BUTTONS_OK,
	                                            output,
	                                            NULL);
	gtk_dialog_run (GTK_DIALOG(dialog));
	gtk_widget_destroy (dialog);
	g_free (output);
}
