/* PangoTabArray object defines a new tab size,
   if we don't like the default.*/

#include <gtk/gtk.h>

void make_tab_array (PangoFontDescription*, gsize, GtkWidget*);
int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Text View Properties");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	gtk_widget_set_size_request (window, 250, 150);
	g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit),0);

	PangoFontDescription* fd = pango_font_description_from_string(
		                                                   "Monospace Bold 10");
	GtkWidget* textview = gtk_text_view_new ();
	gtk_widget_modify_font (textview, fd);

	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW(textview), GTK_WRAP_WORD);
	gtk_text_view_set_justification (GTK_TEXT_VIEW(textview), GTK_JUSTIFY_RIGHT);

	gtk_text_view_set_editable (GTK_TEXT_VIEW(textview), TRUE);
	gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW(textview), TRUE);

	gtk_text_view_set_pixels_above_lines (GTK_TEXT_VIEW (textview), 5);
	gtk_text_view_set_pixels_below_lines (GTK_TEXT_VIEW (textview), 5);
	gtk_text_view_set_pixels_inside_wrap (GTK_TEXT_VIEW (textview), 5);

	gtk_text_view_set_left_margin (GTK_TEXT_VIEW(textview), 10);
	gtk_text_view_set_right_margin (GTK_TEXT_VIEW(textview), 10);

	make_tab_array (fd, 8, textview);

	GtkTextBuffer* buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textview));
	gtk_text_buffer_set_text (buffer, "This is some text!\nChange me!", -1);

	GtkWidget* scrolled_win = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled_win),
	                                GTK_POLICY_AUTOMATIC,
	                                GTK_POLICY_ALWAYS);

	gtk_container_add (GTK_CONTAINER(scrolled_win), textview);
	gtk_container_add (GTK_CONTAINER(window), scrolled_win);
	gtk_widget_show_all (window);

	gtk_main();
	return 0;
}

void make_tab_array (PangoFontDescription* fd,
                     gsize tab_size,
                     GtkWidget* textview)
{
	g_return_if_fail (tab_size < 100);

	gchar* tab_string = g_strnfill (tab_size, ' ');
	PangoLayout* layout = gtk_widget_create_pango_layout (textview, tab_string);
	pango_layout_set_font_description (layout, fd);
	gint width, height;
	pango_layout_get_pixel_size (layout, &width, &height);

	PangoTabArray* tab_array = pango_tab_array_new (1, TRUE);
	pango_tab_array_set_tab (tab_array, 0, PANGO_TAB_LEFT, width);
	gtk_text_view_set_tabs (GTK_TEXT_VIEW(textview), tab_array);

	g_free (tab_string);
}
