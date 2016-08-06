/*    Cap 5. The Graphic Context
 *
 *    Switching between 2 GC, means to create 2 GC and to use them sequentially.
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>



int main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	Display* dpy = XOpenDisplay(NULL);
	if(!dpy) return -1;

	int scrno = DefaultScreen(dpy);
	int scrwidth = DisplayWidth(dpy, scrno);
	int scrheight = DisplayHeight(dpy, scrno);


	int winwidth = scrwidth / 3;
	int winheight = scrheight / 2;

	int winborder = 1;

	Window win = XCreateSimpleWindow(dpy,
	                                 RootWindow(dpy, scrno),
	                                 10, 10,
	                                 winwidth, winheight,
	                                 winborder,
	                                 BlackPixel(dpy, scrno),
	                                 WhitePixel(dpy, scrno));


	char* title = (char*)"gc4 - switch GC";
	XTextProperty titleprop;
	XStringListToTextProperty(&title, 1, &titleprop);
	XSetWMProperties(dpy,
	                 win,
	                 &titleprop,
	                 NULL,
	                 argv,
	                 argc,
	                 NULL,
	                 NULL,
	                 NULL);

	XSelectInput(dpy,win,ExposureMask);


	XGCValues gcvalues;
	gcvalues.foreground = 0x00ff00;
	gcvalues.background = 0xff0000;
	unsigned long gcmask = GCForeground | GCBackground;

	GC gc1 = XCreateGC(dpy,
	                   win,
	                   gcmask,
	                   &gcvalues);
	std::swap(gcvalues.foreground, gcvalues.background);

	GC gc2 = XCreateGC(dpy,
	                   win,
	                   gcmask,
	                   &gcvalues);

	XMapWindow(dpy, win);

	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);
		if(event.type == Expose &&
		   event.xexpose.count == 0)
		{
			XDrawRectangle(dpy,
			               win,
			               gc1,
			               winwidth/4-30, winheight/4-30,
			               winwidth/2, winheight/2);
			XDrawRectangle(dpy,
			               win,
			               gc2,
			               winwidth/4+30, winheight/4+30,
			               winwidth/2, winheight/2);
		}
	}

	return 0;
}
