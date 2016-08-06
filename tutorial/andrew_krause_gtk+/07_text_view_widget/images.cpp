/* Inserting images into text buffers. */

#include <gtk/gtk.h>

#define IMAGE_UNDO "undo.png"
#define IMAGE_REDO "redo.png"


int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Pixbufs");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	gtk_widget_set_size_request (window, 200, 150);
	g_signal_connect (G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit), 0);

	GtkWidget* textview = gtk_text_view_new ();
	GtkTextBuffer* buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textview));
	gtk_text_buffer_set_text (buffer, " Undo\n Redo", -1);

	/* Create two images and insert them into the text buffer. */
	GdkPixbuf* undo = gdk_pixbuf_new_from_file (IMAGE_UNDO, NULL);
	GtkTextIter line;
	gtk_text_buffer_get_iter_at_line (buffer, &line, 0);
	gtk_text_buffer_insert_pixbuf (buffer, &line, undo);

	GdkPixbuf* redo = gdk_pixbuf_new_from_file (IMAGE_REDO, NULL);
	gtk_text_buffer_get_iter_at_line (buffer, &line, 1);
	gtk_text_buffer_insert_pixbuf (buffer, &line, redo);

	GtkWidget* scrolled_win = gtk_scrolled_window_new (NULL, NULL);
	gtk_container_add (GTK_CONTAINER(scrolled_win), textview);
	gtk_container_add (GTK_CONTAINER(window), scrolled_win);
	gtk_widget_show_all (window);

	gtk_main();
	return 0;
}
