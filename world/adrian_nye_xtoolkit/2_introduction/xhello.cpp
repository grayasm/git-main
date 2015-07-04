/*
 *    xhello.c - simple program to put up a banner on the display.
 */

/*    Include files required for all Toolkit programs. */
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>

#ifdef X11R3
#include <X11/Label.h>
#else
#include <X11/Xaw/Label.h>
#endif


int main(int argc, char** argv)
{
	Widget topLevel, hello;
	topLevel = XtInitialize(
		argv[0],
		"XHello",
		NULL,
		0,
		&argc,
		argv
		);

	hello = XtCreateManagedWidget(
		"hello",
		labelWidgetClass,
		topLevel,
		NULL,
		0
		);

	XtRealizeWidget(topLevel);
	XtMainLoop();
	return 0;
}

