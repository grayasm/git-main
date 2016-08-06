#include <gtk/gtk.h>

typedef struct
{
	GtkWidget* entry;
	GtkWidget* textview;
} Widgets;


void insert_text (GtkButton*, Widgets*);
void retrieve_text (GtkButton*, Widgets*);

int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Text Iterators");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	gtk_widget_set_size_request (window, -1, 200);
	g_signal_connect (G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),0);

	Widgets*w = g_slice_new (Widgets);
	w->textview = gtk_text_view_new ();
	w->entry = gtk_entry_new ();
	GtkWidget* insert = gtk_button_new_with_label ("Insert Text");
	GtkWidget* retrieve = gtk_button_new_with_label ("Get Text");

	g_signal_connect (G_OBJECT(insert),
	                  "clicked",
	                  G_CALLBACK(insert_text),
	                  (gpointer) w);
	g_signal_connect (G_OBJECT(retrieve),
	                  "clicked",
	                  G_CALLBACK(retrieve_text),
	                  (gpointer) w);

	GtkWidget* scrolled_win = gtk_scrolled_window_new (NULL, NULL);
	gtk_container_add (GTK_CONTAINER(scrolled_win), w->textview);

	GtkWidget* hbox = gtk_hbox_new (FALSE, 5);
	gtk_box_pack_start_defaults (GTK_BOX(hbox), w->entry);
	gtk_box_pack_start_defaults (GTK_BOX(hbox), insert);
	gtk_box_pack_start_defaults (GTK_BOX(hbox), retrieve);

	GtkWidget* vbox = gtk_vbox_new (FALSE, 5);
	gtk_box_pack_start (GTK_BOX(vbox), scrolled_win, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX(vbox), hbox, FALSE, TRUE, 0);

	gtk_container_add (GTK_CONTAINER(window), vbox);
	gtk_widget_show_all (window);

	gtk_main();
	return 0;
}

/* Insert the text from the GtkEntry into the GtkTextView. */
void insert_text (GtkButton* button, Widgets* w)
{
	GtkTextBuffer* buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(w->textview));
	const gchar* text = gtk_entry_get_text (GTK_ENTRY(w->entry));
	GtkTextMark* mark = gtk_text_buffer_get_insert (buffer);

	GtkTextIter iter;
	gtk_text_buffer_get_iter_at_mark (buffer, &iter, mark);
	gtk_text_buffer_insert (buffer, &iter, text, -1);
}


/* Retrieve the selected text from the GtkTextView and display it to the user.*/
void retrieve_text (GtkButton* button, Widgets* w)
{
	GtkTextBuffer* buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(w->textview));
	GtkTextIter start, end;
	gtk_text_buffer_get_selection_bounds (buffer, &start, &end);
	gchar* text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
	g_print ("%s\n", text);
}
