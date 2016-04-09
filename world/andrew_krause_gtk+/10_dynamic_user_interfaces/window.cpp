/*
  1) This source needs .glade file in "Libglade" format, not "GtkBuilder".
     e.g. <widget class="GtkWindow" id="window">
  2) .glade Common : Widget/Height request = 50,50 ->minimum window size.
  3) .glade Signals: had to re-write gtk_main_quit to get it done.
 */

#include <gtk/gtk.h>
#include <glade/glade.h>

int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GladeXML* xml = glade_xml_new("01_window.glade", NULL, NULL);
	GtkWidget* window = glade_xml_get_widget(xml, "window");

	glade_xml_signal_autoconnect (xml);

	gtk_widget_show_all (window);
	gtk_main ();

	return 0;
}
