#include <gtk/gtk.h>


void destroy (GtkWidget*, gpointer);
int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GtkWidget* widget = gtk_about_dialog_new();
	GtkAboutDialog* about = GTK_ABOUT_DIALOG (widget);

	gtk_about_dialog_set_name (about, "Dialog name");
	gtk_about_dialog_set_program_name (about, "Program name");
	gtk_about_dialog_set_copyright (about, "TODO: Copyright notes.");
	gtk_about_dialog_set_comments (about, "TODO: comments");
	gtk_about_dialog_set_license (about, "GPL v.2 or later.");
	gtk_about_dialog_set_website (about, "http://www.gnome.org");
	const gchar* authors="author-1\nauthor-2\0";
	gtk_about_dialog_set_authors (about, &authors);
	const gchar* documenters = "documeter-1\ndocumenter-2\0";
	gtk_about_dialog_set_documenters (about, &documenters);
	const gchar* artists = "artist-1\nartist-2\0";
	gtk_about_dialog_set_artists (about, &artists);

	g_signal_connect (G_OBJECT(about),
	                  "destroy",
	                  G_CALLBACK(destroy),
	                  NULL);

	gtk_widget_show_all (widget);
	gtk_main ();
	return 0;
}


void destroy (GtkWidget*, gpointer)
{
	gtk_main_quit ();
}
