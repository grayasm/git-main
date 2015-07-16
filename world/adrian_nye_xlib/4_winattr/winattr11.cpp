/*    Xlib Programming Manual (vol1) by Adrian Nye
 *    Cap.4 Window Attributes
 *    Xlib.h/struct XSetWinAttributes
 *    Xlib.h/extern Window XCreateWindow(..., XSetWindowAttributes*)
 *    Xlib.h/extern int    XChangeWindowAttributes(..., XSetWindowAttributes*)
 *
 *    event_mask= specifies which event type are queued for the window when
 *                they occur.
 *    do_not_propagate_mask= defines which events should not be propagated
 *                to ancestor windows when the event type is not selected
 *                in this window.
 *                Both masks are made by combining the constants listed below
 *
 *                Button1MotionMask        KeyPressMask
 *                Button2MotionMask        KeyReleaseMask
 *                Button3MotionMask        LeaveWindowMask
 *                Button4MotionMask        NoEventMask
 *                Button5MotionMask        OwnerGrabButtonMask
 *                ButtonMotionMask         PointerMotionHintMask
 *                ButtonPressMask          PropertyChangeMask
 *                ButtonReleaseMask        ResizeRedirectMask
 *                ColormapChangeMask       StructureNotifyMask
 *                EnterWindowMask          SubstructureNotifyMask
 *                ExposureMask             SubstructureRedirectMask
 *                FocusChangeMask          VisibilityChangeMask
 *                KeymapStateMask
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>




int main(int argc, char** argv)
{
	setvbuf(stdin, NULL, _IONBF, 0);
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
	char* wintitle = (char*) "winattr11 - even_mask";
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

	// allow events for win
	XSelectInput(dpy, win,
	             KeyPressMask | KeyReleaseMask |
	             ButtonPressMask | ButtonReleaseMask);

	unsigned int childwidth = std::max(25, winwidth/4);
	unsigned int childheight = std::max(25, winheight/4);
	unsigned int childborder = 2; // pxl
	int depth = DefaultDepth(dpy, scrno);

	XSetWindowAttributes childattr;
	childattr.background_pixel = WhitePixel(dpy, scrno);
	childattr.border_pixel = BlackPixel(dpy, scrno);

	// child will receive Button events.
	childattr.event_mask = ButtonPressMask | ButtonReleaseMask;

	// for win region under child:
	// ButtonPress, ButtonRelease are selected by child
	// KeyPress is restricted by child to be passed to win.
	// KeyRelease is not selected and not restricted-> will be passed along.
	childattr.do_not_propagate_mask = KeyPressMask;


	unsigned long mask = CWBackPixel | CWBorderPixel |
		CWEventMask | CWDontPropagate;

	Window child = XCreateWindow(dpy,
	                             win,
	                             20, 20,
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

		/*    In area of child window only
		      child: Button events
		      win  : KeyRelease events
		             should be printed
		*/
		if(event.type == ButtonPress)
		{
			if(event.xany.window == win)   printf("\nTop:  ButtonPress");
			if(event.xany.window == child) printf("\nChild:ButtonPress");
		}
		if(event.type == ButtonRelease)
		{
			if(event.xany.window == win)   printf("\nTop:  ButtonRelease");
			if(event.xany.window == child) printf("\nChild:ButtonRelease");
		}
		if(event.type == KeyPress)
		{
			if(event.xany.window == win)   printf("\nTop:  KeyPress");
			if(event.xany.window == child) printf("\nChild:KeyPress");
		}
		if(event.type == KeyRelease)
		{
			if(event.xany.window == win)   printf("\nTop:  KeyRelease");
			if(event.xany.window == child) printf("\nChild:KeyRelease");
		}
	}

	return 0;
}
