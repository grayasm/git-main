#include <glib.h>

void handle_error (GError*);

int main(int argc, char** argv)
{

	/* Build a filenname in the user's home directory. */
	gchar* filename = g_build_filename (g_get_home_dir(), "temp", NULL);

	/* Set the contents of the given file and report any errors. */
	GError* error = NULL;
	g_file_set_contents (filename, "Hello World!", -1, &error);
	handle_error (error);

	if (!g_file_test (filename, G_FILE_TEST_EXISTS))
		g_error ("Error: File does not exist!");

	/* Get the contents of the given file and report any errors. */
	gchar* content;
	gsize bytes;
	g_file_get_contents (filename, &content, &bytes, &error);
	handle_error (error);
	g_print ("%s\n", content);

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
