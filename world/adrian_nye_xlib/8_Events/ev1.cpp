/*
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void printEvent(XEvent* event);

int main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	Display* dpy = XOpenDisplay(NULL);
	if(!dpy) return -1;

	int scrno = DefaultScreen(dpy);
	int scrwidth = DisplayWidth(dpy, scrno);
	int scrheight = DisplayHeight(dpy, scrno);


	int x = 10;
	int y = 10;
	int winwidth = scrwidth / 5;
	int winheight = scrheight * 6 ;
	int winborder = 1;


	Window win = XCreateSimpleWindow(dpy,
	                                 RootWindow(dpy, scrno),
	                                 x, y,
	                                 winwidth, winheight,
	                                 winborder,
	                                 BlackPixel(dpy, scrno),
	                                 WhitePixel(dpy, scrno));


	/* X.h
	   line: 150 to 175   Event definitions;
	*/
	long event_mask =
		KeyPressMask | KeyReleaseMask |
		ButtonPressMask | ButtonReleaseMask |
		EnterWindowMask | LeaveWindowMask |
		PointerMotionMask | PointerMotionHintMask |
		Button1MotionMask | Button2MotionMask | Button3MotionMask |
		Button5MotionMask | ButtonMotionMask |
		KeymapStateMask |
		ExposureMask |
		VisibilityChangeMask |
		StructureNotifyMask |
		ResizeRedirectMask |
		SubstructureNotifyMask |
		SubstructureRedirectMask |
		FocusChangeMask |
		PropertyChangeMask |
		ColormapChangeMask |
		OwnerGrabButtonMask;

	/* Select all events for our top window. */
	XSelectInput(dpy, win, event_mask);
	XMapWindow(dpy, win);



	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);
		printEvent(&event);

		// want to print them all
	}


	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}

void printEvent(XEvent* event)
{
	switch(event->type)
	{
	case KeyPress: printf("\tKeyPress\n"); break;
	}
}
