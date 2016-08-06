/*    Xlib Programming Manual (vol1) by Adrian Nye
 *    Cap.4 Window Attributes
 *    Xlib.h/struct XSetWinAttributes
 *    Xlib.h/extern Window XCreateWindow(..., XSetWindowAttributes*)
 *    Xlib.h/extern int    XChangeWindowAttributes(..., XSetWindowAttributes*)
 *
 *    Failed to set window attribute bit_gravity.
 *
 *    Bit gravity is never necessary in programs. It does not affect the
 *    appearance or functionality of the client. It is used to improve
 *    performance in certain cases. Some X servers may not implement bit
 *    gravity and may throw out the window contents on resizing regardless
 *    of the setting of this attribute.
 *    The default bit gravity is ForgetGravity.
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>


int main(int argc, char** argv)
{
	Display* dpy = XOpenDisplay(NULL);
	if(!dpy) return -1;

	int scrno = DefaultScreen(dpy);
	int scrwidth = DisplayWidth(dpy, scrno);
	int scrheight = DisplayHeight(dpy, scrno);

	int winwidth = scrwidth / 3;
	int winheight = scrheight / 3;
	int winborder = 4; //pxl

	Window win = XCreateSimpleWindow(dpy,
	                                 RootWindow(dpy, scrno),
	                                 10, 10,
	                                 winwidth, winheight,
	                                 winborder,
	                                 BlackPixel(dpy, scrno),
	                                 WhitePixel(dpy, scrno));

	char* wintitle = (char*) "winattr7 - bit gravity";
	XTextProperty wintitleprop;
	XStringListToTextProperty(&wintitle, 1, &wintitleprop);

	XSetWMProperties(dpy,
	                 win,
	                 &wintitleprop,
	                 NULL,              // icon property
	                 argv,
	                 argc,
	                 NULL,              // hints about size
	                 NULL,              // hints about window
	                 NULL);             // hints about class

	// set top window bit_gravity flag
	XSetWindowAttributes winattr;
	winattr.bit_gravity = NorthEastGravity;
	XChangeWindowAttributes(dpy,
	                        win,
	                        CWBitGravity,
	                        &winattr);


	unsigned int childwidth = std::max(25, winwidth/4);
	unsigned int childheight = std::max(25, winheight/4);
	unsigned int childx = winwidth - childwidth - 20;
	unsigned int childy = winheight - childheight - 20;
	unsigned int childborder = 4; // pxl
	int depth = DefaultDepth(dpy, scrno);

	XSetWindowAttributes childattr;
	childattr.border_pixel = BlackPixel(dpy, scrno);
	childattr.background_pixel = WhitePixel(dpy, scrno);
	unsigned long mask = CWBackPixel | CWBorderPixel;
	Window child = XCreateWindow(dpy,
	                             win,
	                             childx, childy,
	                             childwidth, childheight,
	                             childborder,
	                             depth,
	                             InputOutput,
	                             CopyFromParent,
	                             mask,
	                             &childattr);

	XMapWindow(dpy, win);
	XMapWindow(dpy, child);


	XEvent event;
	while(1)
	{
		XNextEvent(dpy, &event);
	}

	return 0;
}
