#include <gtk/gtk.h>
#include <glade/glade.h>


int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GladeXML* xml = glade_xml_new ("treeview.glade", NULL, NULL);
	GtkWidget* window = glade_xml_get_widget (xml, "window");

	glade_xml_signal_autoconnect (xml);

	GtkWidget* treeview = glade_xml_get_widget (xml, "treeview1");

	gtk_widget_show_all (window);
	gtk_main ();

	return 0;
}
