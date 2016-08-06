#include <glib.h>

void handle_error(GError*);
int main (int argc, char** argv)
{

	/* Build a filename in the user's home directory. */
	gchar* filename = g_build_filename (g_get_home_dir(), "temp", NULL);

	GError* error = NULL;
	gsize bytes;

	/* Set the contents of the given file and report any errors. */
	GIOChannel* write = g_io_channel_new_file (filename, "w", &error);
	handle_error (error);
	g_io_channel_write_chars (write, "Hello World!", -1, &bytes, NULL);
	g_io_channel_close (write);

	if (!g_file_test (filename, G_FILE_TEST_EXISTS))
		g_error ("Error: File does not exists!\n");

	gchar* content;

	/* Get the contents of the given file and report any errors. */
	GIOChannel* read = g_io_channel_new_file (filename, "r", &error);
	handle_error (error);
	g_io_channel_read_to_end (read, &content, &bytes, NULL);
	g_print ("%s\n", content);

	g_io_channel_close (read);
	g_free (content);
	g_free (filename);

	return 0;
}


void handle_error (GError* error)
{
	if (error != NULL)
	{
		g_print (error->message);
		g_clear_error (&error);
	}
}
