#include <gtk/gtk.h>
#include <glade/glade.h>
#include <string.h>


void button1_clicked_cb (GtkButton *bn, gpointer data);

/* Widget states
typedef enum
{
  GTK_STATE_NORMAL,
  GTK_STATE_ACTIVE,
  GTK_STATE_PRELIGHT,
  GTK_STATE_SELECTED,
  GTK_STATE_INSENSITIVE
} GtkStateType;

struct _GtkStyle
{
  GdkColor fg[5];     // 1 color for each GtkStateType
..


struct _GdkColor
{
  guint32 pixel;
  guint16 red;
  guint16 green;
  guint16 blue;
};
*/


struct Widgets
{
	GtkComboBox* combobox1;
	GtkColorButton* colorbutton1;
	GtkButton* button2;
};

int main (int argc, char** argv)
{
	gtk_init (&argc, &argv);

	// gtk_rc_parse ("gtk2-styles.gtkrc");

	GladeXML* xml = glade_xml_new ("gtk2-styles.glade", NULL, NULL);
	glade_xml_signal_autoconnect (xml);
	GtkWidget* window = glade_xml_get_widget (xml, "window");
	Widgets* w = g_slice_new (Widgets);
	w->combobox1 = GTK_COMBO_BOX (glade_xml_get_widget(xml, "combobox1"));
	w->colorbutton1 = GTK_COLOR_BUTTON (glade_xml_get_widget(xml, "colorbutton1"));
	w->button2 = GTK_BUTTON (glade_xml_get_widget(xml, "button2"));

	glade_xml_signal_connect_data (xml,
	                               "button1_clicked_cb",
	                               G_CALLBACK(button1_clicked_cb),
	                               w);

	gtk_widget_show_all (window);
	gtk_main ();

	g_slice_free(Widgets, w);

	return 0;
}


void button1_clicked_cb (GtkButton *bn, gpointer data)
{
	Widgets* w = (Widgets*)data;
	GtkComboBox* combobox1 = w->combobox1;
	GtkColorButton* colorbutton1 = w->colorbutton1;
	GtkButton* button2 = w->button2;

	const gchar* text = gtk_combo_box_get_active_text (combobox1);
	GdkColor color;
	gtk_color_button_get_color (colorbutton1, &color);


	g_print ("combobox1=%s\n", text);
	g_print ("bg color =%d.%d.%d\n",
		        (int)(color.red * 255. / 65535.0),
		        (int)(color.green * 255. / 65535.0),
		        (int)(color.blue * 255. / 65535.0));

	if (text == NULL)
		return;

	GtkStateType state = GTK_STATE_NORMAL;
	if ( strcmp(text, "normal") == 0 )
		state = GTK_STATE_NORMAL;
	else if (strcmp(text, "active") == 0 )
		state = GTK_STATE_ACTIVE;
	else if (strcmp(text, "prelight") == 0 )
		state = GTK_STATE_PRELIGHT;
	else if (strcmp(text, "selected") == 0 )
		state = GTK_STATE_SELECTED;
	else if (strcmp(text, "insensitive") == 0 )
		state = GTK_STATE_INSENSITIVE;
	else
		return;

	GtkStyle* style = gtk_widget_get_style (GTK_WIDGET(button2));
	if (style == NULL)
		return;

	gtk_widget_modify_bg (GTK_WIDGET(button2), state, &color);
}
