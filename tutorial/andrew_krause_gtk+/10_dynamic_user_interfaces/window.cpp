/*
  1) used /usr/bin/glade-3 on centos7 (2016-04-16)
  2) tell Glade to use format "Libglade" and not "GtkBuilder"
     e.g. <widget class="GtkWindow" id="window">
  3) .glade Common : Widget/Height request = 50,50 ->minimum window size.
  4) .glade Signals: had to re-write gtk_main_quit to get it done.
 */

#include <gtk/gtk.h>
#include <glade/glade.h>

int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GladeXML* xml = glade_xml_new("window.glade", NULL, NULL);
	GtkWidget* window = glade_xml_get_widget(xml, "window");

	glade_xml_signal_autoconnect (xml);

	gtk_widget_show_all (window);
	gtk_main ();

	return 0;
}
