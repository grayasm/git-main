/* Applying some text properties that I found here
   https://developer.gnome.org/gtk2/stable/TextWidget.html
*/
#include <gtk/gtk.h>

int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Text View Properties");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	gtk_widget_set_size_request (window, 250, 150);
	g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit),0);


	GtkWidget* textview = gtk_text_view_new ();
	PangoFontDescription* font_desc = pango_font_description_from_string(
		                                                            "Serif 15");
	GtkTextBuffer* buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textview));
	gtk_text_buffer_set_text (buffer, "Hello, this is ome text", -1);

	/* Change default font throughout the widget. */
	gtk_widget_modify_font (textview, font_desc);
	pango_font_description_free (font_desc);

	/* Change default color throughout the widget. */
	GdkColor color;
	gdk_color_parse ("green", &color);
	gtk_widget_modify_text (textview, GTK_STATE_NORMAL, &color);

	/* Use a tag to change the color for just one part of the widget. */
	GtkTextTag* tag = gtk_text_buffer_create_tag (buffer,
	                                              "blue_foreground",
	                                              "foreground",
	                                              "blue",
	                                              NULL);
	GtkTextIter start,end;
	gtk_text_buffer_get_iter_at_offset (buffer, &start, 7);
	gtk_text_buffer_get_iter_at_offset (buffer, &end, 12);
	gtk_text_buffer_apply_tag (buffer, tag, &start, &end);

	/* This was applied in textview2.cpp sample. I will keep some here.*/
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW(textview), GTK_WRAP_WORD);
	gtk_text_view_set_justification (GTK_TEXT_VIEW(textview), GTK_JUSTIFY_RIGHT);

	gtk_text_view_set_editable (GTK_TEXT_VIEW(textview), TRUE);
	gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW(textview), TRUE);

	gtk_text_view_set_pixels_above_lines (GTK_TEXT_VIEW (textview), 5);
	gtk_text_view_set_pixels_below_lines (GTK_TEXT_VIEW (textview), 5);
	gtk_text_view_set_pixels_inside_wrap (GTK_TEXT_VIEW (textview), 5);

	gtk_text_view_set_left_margin (GTK_TEXT_VIEW(textview), 10);
	gtk_text_view_set_right_margin (GTK_TEXT_VIEW(textview), 10);


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
