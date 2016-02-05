#include <gtk/gtk.h>
#include <string.h>

void entry_changed (GtkEditable*, GtkAssitant*);
void button_toggled (GtkCheckButton*, GtkAssitant*);
void button_clicked (GtkButton*, GtkAssitant*);
void assitant_cancel (GtkAssitant*, gpointer);
void assitant_close (GtkAssitant*, gpointer);


typedef struct {
	GtkWidget*      widget;
	gint            index;
	const gchar*    title;
	GtkAssitantPageType type;
	gboolean        complete;
} PageInfo;


int main (int argc, char** argv)
{
	GtkWidget* assitant, *entry, *label, *button, *progress, *hbox;
	guint i;
	PageInfo page[5] = {
		{NULL, -1, "Introduction",           GTK_ASSISTANT_PAGE_INTRO,   TRUE},
		{NULL, -1, NULL,                     GTK_ASSISTANT_PAGE_CONTENT, FALSE},
		{NULL, -1, "Click the Check Button", GTK_ASSISTANT_PAGE_CONTENT, FALSE},
		{NULL, -1, "Click the Button",       GTK_ASSISTANT_PAGE_PROGRESS, FALSE},
		{NULL, -1, "Confirmation",           GTK_ASSISTANT_PAGE_CONFIRM, TRUE},
	};

	gtk_init (&argc, &argv);

	/* Create a new assitant widget with no pages. */
}
