/*    Cap 5. The Graphic Context
 *
 *    Example 5-6 Setting line characteristics in a GC
 *
 *    XGCValues.line_width
 *    XGCValues.line_style
 *    XGCValues.cap_style
 *    XGCValues.join_style
 *    for a list of all parameters see README.txt
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


	char* title = (char*)"gc6 - XSetLineAttributes";
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
	gcvalues.foreground = BlackPixel(dpy, scrno);
	gcvalues.background = WhitePixel(dpy, scrno);
	unsigned long gcmask = GCForeground | GCBackground;

	GC gc = XCreateGC(dpy,
	                  win,
	                  gcmask,
	                  &gcvalues);
	unsigned int line_width = 3;
	int line_style = LineSolid; /* If LineOfOffDash or LineDoubleDash must set
	                               dashes.  */
	int cap_style = CapRound;   /* else CapNotLast, CapButt or CapProjecting */
	int join_style = JoinRound; /* else JoinMiter or JoinBevel               */
	XSetLineAttributes(dpy,
	                   gc,
	                   line_width,
	                   line_style,
	                   cap_style,
	                   join_style);

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
			               gc,
			               winwidth/4-30, winheight/4-30,
			               winwidth/2, winheight/2);
			XDrawRectangle(dpy,
			               win,
			               gc,
			               winwidth/4+30, winheight/4+30,
			               winwidth/2, winheight/2);
		}
	}

	return 0;
}
