#include <gtk/gtk.h>
#include <string.h>

#define SLICE_SIZE 20
int main(int argc, char** argv)
{
	gchar* strings[5];
	for (gint i = 0; i < 5; ++i)
	{
		strings[i] = (gchar*)g_slice_alloc (SLICE_SIZE);
		sprintf (strings[i], "g_slice_alloc %d", i);
		g_print ("%s\n", strings[i]);
	}

	for (gint i = 0; i < 5; ++i)
		g_slice_free1 (SLICE_SIZE, strings[i]);
	return 0;
}
