/*    Based on simple2.cpp
 *
 *    When size hints (Xutil.h/XSizeHints/XSetWMProperties)
 *    are set correctly the window cannot be resized under the minimun
 *    size set, or maximized beyond max size (tested with fvwm)
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

	char* winTitle = (char*)"simple3 - window size";
	XTextProperty winNameProp;
	Status ret = XStringListToTextProperty(&winTitle, 1, &winNameProp);

	XSizeHints szhints;
	szhints.flags = PPosition | PSize | PMinSize | PMaxSize;
	szhints.x = 0;
	szhints.y = 0;
	szhints.width = win_width;
	szhints.height = win_height;
	szhints.min_width = 200;
	szhints.min_height = 200;
	szhints.max_width = screen_width - 200;
	szhints.max_height = screen_height - 200;

	XSetWMProperties(disp,
	                 win,
	                 &winNameProp,
	                 NULL,          // icon property
	                 argv,
	                 argc,
	                 &szhints,      // hints about size
	                 NULL,          // hints about window
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

