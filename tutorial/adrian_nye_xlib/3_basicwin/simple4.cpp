/*    Based on simple2.cpp
 *
 *    Added window hints (Xutil.h/XWMHints/XSetWMProperties)
 *    but only for Input and State (no Pixmap for icon or window).
 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>




int main(int argc, char** argv)
{
	Display* disp = XOpenDisplay(NULL);
	if(!disp) return -1;

	int screen_num = DefaultScreen(disp);
	int screen_width = DisplayWidth(disp, screen_num);
	int screen_height = DisplayHeight(disp, screen_num);

	int win_width = screen_width/3;
	int win_height = screen_height/3;
	int win_border = 4;

	Window win = XCreateSimpleWindow(disp,
	                                 RootWindow(disp, screen_num),
	                                 0, 0,
	                                 win_width, win_height,
	                                 win_border,
	                                 BlackPixel(disp, screen_num),
	                                 WhitePixel(disp, screen_num));

	/* Setting the window title. */
	char* winTitle = (char*)"simple4 - XWMHints (input and state)";
	XTextProperty winNameProp;
	Status ret = XStringListToTextProperty(&winTitle, 1, &winNameProp);

	XWMHints wmhints;
	wmhints.flags = InputHint | StateHint;
	wmhints.input = 1; // for true
	wmhints.initial_state = NormalState;



	XSetWMProperties(disp,
	                 win,
	                 &winNameProp,
	                 NULL,          // icon property
	                 argv,
	                 argc,
	                 NULL,          // hints about size
	                 &wmhints,      // hints about window
	                 NULL           // hints about class
		);



	XSelectInput(disp,
	             win,
	             ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask);

	XMapWindow(disp, win);

	XEvent event;
	while(1)
	{
		XNextEvent(disp, &event);

		switch (event.type)
		{
		case Expose:
			break;
		case ConfigureNotify:
			break;
		case ButtonPress:
		case KeyPress:
			XCloseDisplay(disp);
			exit(0);
			break;
		} // switch
	} // while

	return 0;
}
