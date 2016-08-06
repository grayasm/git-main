#include <gtk/gtk.h>
#include <glade/glade.h>

/*look up developer.gnome.org for enter-notify-event to get the fn signature*/
gboolean enter (GtkWidget*, GdkEvent*, gpointer);
gboolean leave (GtkWidget*, GdkEvent*, gpointer);
void     click (GtkButton*, gpointer);

int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GladeXML* xml = glade_xml_new("button.glade", NULL, NULL);
	GtkWidget* window = glade_xml_get_widget (xml, "window");

	glade_xml_signal_autoconnect (xml);

	glade_xml_signal_connect (xml, "enter-notify-event", G_CALLBACK(enter));
	glade_xml_signal_connect (xml, "leave-notify-event", G_CALLBACK(leave));
	glade_xml_signal_connect (xml, "on_button1_clicked", G_CALLBACK(click));

	gtk_widget_show_all (window);
	gtk_main ();

	return 0;
}


gboolean enter (GtkWidget*, GdkEvent*, gpointer)
{
	g_print("\ncall to enter-notify-event");
	return 0;
}

gboolean leave (GtkWidget*, GdkEvent*, gpointer)
{
	g_print("\ncall to leave-notify-event");
	return 0;
}

void     click (GtkButton*, gpointer)
{
	g_print("\ncall to clicked event");
}
