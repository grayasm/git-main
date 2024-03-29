#include <gtk/gtk.h>

int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Text Views");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	gtk_widget_set_size_request (window, 250, 150);

	GtkWidget* textview = gtk_text_view_new ();
	GtkTextBuffer* buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview));
	gtk_text_buffer_set_text (buffer, "Your 1st GtkTextView widget!", -1);

	GtkWidget* scrolled_win = gtk_scrolled_window_new (NULL, NULL);
	gtk_container_add (GTK_CONTAINER(scrolled_win), textview);
	gtk_container_add (GTK_CONTAINER(window), scrolled_win);
	gtk_widget_show_all (window);

	gtk_main ();
	return 0;
}
