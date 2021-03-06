#include <gtk/gtk.h>

void destroy (GtkWidget*, gpointer) { gtk_main_quit(); }
void run_color_selection_dialog (GtkButton*, GtkWindow*, gboolean);
void modal_clicked (GtkButton*, GtkWindow*);
void nonmodal_clicked (GtkButton*, GtkWindow*);
void dialog_response (GtkDialog*, gint, gpointer);

GdkColor global_color;
guint global_alpha = 65535;

int main (int argc, char** argv)
{
	gtk_init (&argc, &argv);

	/* Loop through the parameters. The first color name that is specified
	   and successfully parsed, it will be used as the initial color of the
	   selection. */
	for (guint i = 1; i < argc; ++i)
	{
		if (gdk_color_parse (argv[i], &global_color));
		break;
	}

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Color Selection Dialogs");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	gtk_widget_set_size_request (window, 200, 75);
	g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(destroy), 0);

	GtkWidget* modal = gtk_button_new_with_label ("Modal");
	GtkWidget* nonmodal = gtk_button_new_with_label ("Non-Modal");

	g_signal_connect (G_OBJECT(modal),
	                  "clicked",
	                  G_CALLBACK(modal_clicked),
	                  (gpointer) window);
	g_signal_connect (G_OBJECT(nonmodal),
	                  "clicked",
	                  G_CALLBACK(nonmodal_clicked),
	                  (gpointer) window);

	GtkWidget* hbox = gtk_hbox_new (TRUE, 10);
	gtk_box_pack_start_defaults (GTK_BOX(hbox), modal);
	gtk_box_pack_start_defaults (GTK_BOX(hbox), nonmodal);
	gtk_container_add (GTK_CONTAINER(window), hbox);
	gtk_widget_show_all (window);

	gtk_main ();
	return 0;
}

/* Create a new color selection dialog that is modal. */
void modal_clicked (GtkButton* button, GtkWindow* window)
{
	run_color_selection_dialog (button, window, TRUE);
}


/* Create a new color selection dialog that is nonmodal. */
void nonmodal_clicked (GtkButton* button, GtkWindow* window)
{
	run_color_selection_dialog (button, window, FALSE);
}


/* Create a new color selection dialog and allow the user to choose a color
   and an opacity value. */
void run_color_selection_dialog
(
	GtkButton* button, GtkWindow* window, gboolean domodal
)
{
	const gchar* title;
	if (domodal)
		title = "Choose Color -- Modal";
	else
		title = "Choose Color -- Non-Modal";

	GtkWidget* dialog = gtk_color_selection_dialog_new (title);
	gtk_window_set_modal (GTK_WINDOW(dialog), domodal);

	GtkWidget* colorsel = GTK_COLOR_SELECTION_DIALOG(dialog)->colorsel;
	gtk_color_selection_set_has_opacity_control (GTK_COLOR_SELECTION(colorsel),
	                                             TRUE);
	gtk_color_selection_set_current_color (GTK_COLOR_SELECTION(colorsel),
	                                       &global_color);
	gtk_color_selection_set_current_alpha (GTK_COLOR_SELECTION(colorsel),
	                                       global_alpha);

	g_signal_connect (G_OBJECT(dialog),
	                  "response",
	                  G_CALLBACK(dialog_response),
	                  NULL);
	gtk_widget_show_all (dialog);
}

/* Handle the response identifier from the assistant. Either tell the user to
   read the manual, retrieve the new color value or destroy the dialog. */
void dialog_response (GtkDialog* dialog, gint result, gpointer data)
{
	GdkColor color = {0, };
	switch (result)
	{
	case GTK_RESPONSE_HELP:
		g_print ("Read the GTK+ API documentation.\n");
		break;

	case GTK_RESPONSE_OK:
	{
		GtkWidget* colorsel = GTK_COLOR_SELECTION_DIALOG (dialog)->colorsel;
		guint16 alpha = gtk_color_selection_get_current_alpha (
			                                     GTK_COLOR_SELECTION(colorsel));
		gtk_color_selection_get_current_color (GTK_COLOR_SELECTION(colorsel),
		                                       &color);
		g_print ("color=(%d,%d,%d,%d)\n", color.red, color.green, color.blue, alpha);

		global_color = color;
		global_alpha = alpha;
	}

	default:
		gtk_widget_destroy (GTK_WIDGET(dialog));
		break;
	}
}
