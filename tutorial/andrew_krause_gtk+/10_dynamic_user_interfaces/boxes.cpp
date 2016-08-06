#include <gtk/gtk.h>
#include <glade/glade.h>

void toolbutton_about_clicked (GtkButton*, gpointer);

int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);
	GladeXML* xml = glade_xml_new ("boxes.glade", NULL, NULL);
	GtkWidget* window = glade_xml_get_widget (xml, "window");

	glade_xml_signal_autoconnect (xml);

	glade_xml_signal_connect_data (xml,
	                               "on_toolbutton_about_clicked",
	                               G_CALLBACK(toolbutton_about_clicked),
	                               (gpointer)"Vasilian's Data");


	gtk_widget_show_all (window);
	gtk_main ();
	return 0;
}

void toolbutton_about_clicked (GtkButton*, gpointer data)
{
	g_print("\ntoolbutton_about_clicked %s", (char*)data);
}
