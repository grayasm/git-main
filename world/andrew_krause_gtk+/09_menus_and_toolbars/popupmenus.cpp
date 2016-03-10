/* A simple pop-up menu with three menu items. */

#include <gtk/gtk.h>

void create_popup_menu (GtkWidget*, GtkWidget*);
void pulse_activated (GtkMenuItem*, GtkProgressBar*);
void clear_activated (GtkMenuItem*, GtkProgressBar*);
void fill_activated (GtkMenuItem*, GtkProgressBar*);
gboolean button_press_event (GtkWidget*, GdkEventButton*, gpointer);


int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Pop-up Menus");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	gtk_widget_set_size_request (window, 250, -1);
	g_signal_connect (G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),0);

	/* Create all of the necessary widgets and initialize the pop-up menu. */
	GtkWidget* menu = gtk_menu_new ();
	GtkWidget* eventbox = gtk_event_box_new ();
	GtkWidget* progress = gtk_progress_bar_new ();
	gtk_progress_bar_set_text (GTK_PROGRESS_BAR(progress), "Nothing Yet Happened");
	create_popup_menu (menu, progress);

	gtk_progress_bar_set_pulse_step (GTK_PROGRESS_BAR(progress), 0.05);
	gtk_event_box_set_above_child (GTK_EVENT_BOX(eventbox), FALSE);

	g_signal_connect (G_OBJECT(eventbox),
	                  "button_press_event",
	                  G_CALLBACK(button_press_event),
	                  menu);

	gtk_container_add (GTK_CONTAINER(eventbox), progress);
	gtk_container_add (GTK_CONTAINER(window), eventbox);

	gtk_widget_set_events (eventbox, GDK_BUTTON_PRESS_MASK);
	gtk_widget_realize (eventbox);

	gtk_widget_show_all (window);
	gtk_main ();
	return 0;
}


/* Create the pop-up menu and attach it to the progress bar. This will make
   sure that the accelerators will work from application load.
*/
void create_popup_menu (GtkWidget* menu, GtkWidget* progress)
{
	GtkWidget* pulse = gtk_menu_item_new_with_label ("Pulse Progress");
	GtkWidget* fill = gtk_menu_item_new_with_label ("Set as Complete");
	GtkWidget* clear = gtk_menu_item_new_with_label ("Clear Progress");
	GtkWidget* separator = gtk_separator_menu_item_new ();

	g_signal_connect (G_OBJECT(pulse),
	                  "activate",
	                  G_CALLBACK(pulse_activated),
	                  progress);
	g_signal_connect (G_OBJECT(fill),
	                  "activate",
	                  G_CALLBACK(fill_activated),
	                  progress);
	g_signal_connect (G_OBJECT(clear),
	                  "activate",
	                  G_CALLBACK(clear_activated),
	                  progress);

	gtk_menu_shell_append (GTK_MENU_SHELL(menu), pulse);
	gtk_menu_shell_append (GTK_MENU_SHELL(menu), separator);
	gtk_menu_shell_append (GTK_MENU_SHELL(menu), fill);
	gtk_menu_shell_append (GTK_MENU_SHELL(menu), clear);

	gtk_menu_attach_to_widget (GTK_MENU(menu), progress, NULL);
	gtk_widget_show_all (menu);
}

gboolean button_press_event (GtkWidget*      eventbox,
                             GdkEventButton* event,
                             gpointer        user_data)
{
	GtkWidget* menu = (GtkWidget*)user_data;

	if((event->button == 3) && (event->type == GDK_BUTTON_PRESS))
	{
		gtk_menu_popup (GTK_MENU(menu), NULL,NULL,NULL,NULL,
		                event->button,
		                event->time);
		return TRUE;
	}
	return FALSE;
}

void pulse_activated (GtkMenuItem* item, GtkProgressBar* progress)
{
	gtk_progress_bar_pulse (progress);
	gtk_progress_bar_set_text (progress, "Pulse!");
}

void fill_activated (GtkMenuItem* item, GtkProgressBar* progress)
{
	gtk_progress_bar_set_fraction (progress, 1.0);
	gtk_progress_bar_set_text (progress, "One Hundred Percent");
}

void clear_activated (GtkMenuItem* item, GtkProgressBar* progress)
{
	gtk_progress_bar_set_fraction (progress, 0.0);
	gtk_progress_bar_set_text (progress, "Reset to Zero");
}
