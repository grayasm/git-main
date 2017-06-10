#include <Python.h>


static PyObject*
helloworld(PyObject* self)
{
	return Py_BuildValue("s", "Hello, C-coded Python extensions world!");
}


static char helloworld_docs[] =
	"helloworld( ): return a popular greeting phrase\n";

static PyMethodDef helloworld_funcs[] = {
	{ "helloworld", (PyCFunction)helloworld, METH_NOARGS, helloworld_docs },
	{ NULL }
};


void
inithelloworld(void)
{
	Py_InitModule3("helloworld", helloworld_funcs, "Toy-level extension module");
}
