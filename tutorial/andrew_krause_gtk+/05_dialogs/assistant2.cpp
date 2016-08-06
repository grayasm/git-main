#include <gtk/gtk.h>

void apply_clicked (GtkAssistant*, gpointer) { printf("clicked Apply button\n"); }
void cancel_clicked(GtkAssistant*, gpointer) { printf("clicked Cancel button\n"); }
void close_clicked (GtkAssistant*, gpointer) { printf("clicked Close button\n");
                                               gtk_main_quit(); }

int main(int argc, char** argv)
{
	gtk_init (&argc, &argv);

	GtkWidget* assistant = gtk_assistant_new ();
	gtk_widget_set_size_request (assistant, 400, 300);
	gtk_window_set_title (GTK_WINDOW(assistant), "GtkAssistant by trial and error");
	g_signal_connect (G_OBJECT(assistant), "destroy", G_CALLBACK(gtk_main_quit), 0);
	g_signal_connect (G_OBJECT(assistant), "apply", G_CALLBACK(apply_clicked), 0);
	g_signal_connect (G_OBJECT(assistant), "cancel", G_CALLBACK(cancel_clicked), 0);
	g_signal_connect (G_OBJECT(assistant), "close", G_CALLBACK(close_clicked), 0);

	GtkWidget* label = gtk_label_new ("Gtk label.");
	gtk_assistant_append_page (GTK_ASSISTANT(assistant), label);
	gtk_assistant_set_page_title (GTK_ASSISTANT(assistant), label, "Page title");
	gtk_assistant_set_page_type (GTK_ASSISTANT(assistant), label, GTK_ASSISTANT_PAGE_CONFIRM);
	gtk_assistant_set_page_complete (GTK_ASSISTANT(assistant), label, TRUE);


	// show it
	gtk_widget_show_all (assistant);
	gtk_main();
	return 0;
}
