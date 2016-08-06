/* Using IO Channels for Pipes (iochannels.c)
   The books describes how the pipes were set up in UNIX using fork().
   The next section will show how to set up pipes and fork() an application
   that is supported across platforms. */

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

void entry_changed (GtkEditable*, GIOChannel*);
void setup_app (gint input[], gint output[], gint pid);
gboolean iochannel_read (GIOChannel*, GIOCondition, GtkEntry*);

gulong signal_id = 0;

int main(int argc, char** argv)
{
	/* Set up read and write pipes for the child and parent processes. */
	gint parent_to_child[2];
	gint ret_value = pipe (parent_to_child);

	if (ret_value == -1)
	{
		g_error ("Error: %s\n", g_strerror (errno));
		exit (1);
	}

	gint child_to_parent[2];
	ret_value = pipe (child_to_parent);
	if (ret_value == -1)
	{
		g_error ("Error: %s\n", g_strerror(errno));
		exit (1);
	}

	/* Fork the application, setting up both instances accordingly. */
	gint pid = fork ();
	switch (pid)
	{
	case -1:
		g_error ("Error: %s\n", g_strerror(errno));
		exit (1);

	case 0:
		gtk_init (&argc, &argv);
		setup_app (parent_to_child, child_to_parent, pid);
		break;

	default:
		gtk_init (&argc, &argv);
		setup_app (child_to_parent, parent_to_child, pid);
	}

	gtk_main ();
	return 0;
}



/* Set up the GUI aspects of each window and setup IO channel watches. */
void setup_app (gint input[], gint output[], gint pid)
{
	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	GtkWidget* entry = gtk_entry_new ();

	gtk_container_add (GTK_CONTAINER(window), entry);
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	gtk_widget_set_size_request (window, 200, -1);
	gtk_widget_show_all (window);

	/* Close the unnecessary pipes for the given process. */
	close (input[1]);
	close (input[0]);

	/* Create read and write channels out of the remaining pipes. */
	GIOChannel* channel_read = g_io_channel_unix_new (input[0]);
	GIOChannel* channel_write = g_io_channel_unix_new (output[1]);

	if (channel_read == NULL || channel_write == NULL)
		g_error ("Error: The GIOChannel could not be created!\n");

	/* Watch the read channel for changes. This will send the appropriate data.*/
    // GLIB_SYSDEF_POLLIN | GLIB_SYSDEF_POLLHUP
	GIOCondition giocondition = G_IO_HUP;
	if (!g_io_add_watch (channel_read,
	                     giocondition,
	                     (GIOFunc) iochannel_read,
	                     (gpointer) entry))
		g_error ("Error: Read watch could not be added to the GIOChannel!\n");

	signal_id = g_signal_connect (G_OBJECT(entry),
	                              "changed",
	                              G_CALLBACK (entry_changed),
	                              (gpointer) channel_write);

	/* Set the window title depending on the process identifier. */
	if (pid == 0)
		gtk_window_set_title (GTK_WINDOW(window), "Child process");
	else
		gtk_window_set_title (GTK_WINDOW(window), "Parent process");
}


/* Read the message from the pipe and set the text to the GtkEntry. */
gboolean iochannel_read (GIOChannel* channel,
                         GIOCondition condition,
                         GtkEntry* entry)
{
	/* The pipe has died unexpectedly, so exit the application. */
	if (condition & G_IO_HUP)
		g_error ("Error: The pipe has died!\n");

	/* Read the data that has been sent through the pipe. */
	gchar* message;
	gsize length;
	GIOStatus ret_value = g_io_channel_read_line (channel,
	                                              &message,
	                                              &length,
	                                              NULL,
	                                              NULL);
	if (ret_value == G_IO_STATUS_ERROR)
		g_error ("Error: The line could not be read!\n");

	/* Synchronize the GtkEntry text, blocking the changed signal.
	   Otherwise, an infinite loop of communication would ensue. */
	g_signal_handler_block ((gpointer) entry, signal_id);
	message[length-1] = 0;
	gtk_entry_set_text (entry, message);
	g_signal_handler_unblock ((gpointer) entry, signal_id);

	return TRUE;
}


/* Write the new contents of the GtkEntry to the write IO channe. */
void entry_changed (GtkEditable* entry, GIOChannel* channel)
{
	gchar* text = g_strconcat (gtk_entry_get_text (GTK_ENTRY(entry)),
	                           "\n",
	                           NULL);

	gsize length;
	/* Write the text to the channel so that the other process will get it.*/
	GIOStatus ret_value = g_io_channel_write_chars (channel,
	                                                text,
	                                                -1,
	                                                &length,
	                                                NULL);
	if (ret_value = G_IO_STATUS_ERROR)
		g_error ("Error: The changes could not be written to the pipe!\n");
	else
		g_io_channel_flush (channel, NULL);
}
