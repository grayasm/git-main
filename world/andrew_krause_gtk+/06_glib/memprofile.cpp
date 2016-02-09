#include <glib.h>

int main(int argc, char** argv)
{
	/* Set the GMemVTable to the default table.
	   This needs to be called before any other call to a GLib function.
	*/
	g_mem_set_vtable (glib_mem_profiler_table);

	/* Call g_mem_profile() when the application exists. */
	g_atexit (g_mem_profile);

	GSList* list = (GSList*) g_malloc (sizeof(GSList));
	list->next = (GSList*) g_malloc (sizeof(GSList));


	/* Only free one of the GSList objects to see the memory profiler output.*/
	g_free (list->next);


	return 0;
}
