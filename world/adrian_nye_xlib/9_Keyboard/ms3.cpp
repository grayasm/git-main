/*
  ms3.cpp  - sample3 taken from the book.
  Tracking the pointer motion by
  (2) getting current position using motion hints is the most efficient
  method of handling pointer motion events.
*/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>



#define BUF_SIZE 2000

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
	int winheight = scrheight / 6 ;
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
		ExposureMask |
		ButtonPressMask | ButtonReleaseMask | ButtonMotionMask |
		PointerMotionHintMask;

	/* Select all events for our top window. */
	XSelectInput(dpy, win, event_mask);

	// create a GC
	GC gc = XCreateGC(dpy,
	                  win,
	                  0,
	                  NULL);
	XSetForeground(dpy, gc, BlackPixel(dpy, scrno));
	XSetBackground(dpy, gc, WhitePixel(dpy, scrno));
	XMapWindow(dpy, win);


	int root_x=0, root_y=0;
	Window root, child;
	unsigned int keys_buttons;
	XPoint points[BUF_SIZE];
	int index = 1;
	int pos_x=0, pos_y=0;
	int prev_x=0, prev_y=0;


	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);

		switch (event.type)
		{
		case ButtonPress:
			points[index].x = event.xbutton.x;
			points[index].y = event.xbutton.y;
			break;

		case ButtonRelease:
			index++;
			points[index].x = event.xbutton.x;
			points[index].y = event.xbutton.y;
			break;

		case MotionNotify:
			printf("got a motion event\n");
			while (XCheckMaskEvent (dpy,
			                        ButtonMotionMask,
			                        &event));

			if (!XQueryPointer(dpy,
			                   event.xmotion.window,
			                   &root,
			                   &child,
			                   &root_x,
			                   &root_y,
			                   &pos_x,
			                   &pos_y,
			                   &keys_buttons))
				/* Pointer is on other screen */
				break;

				/* Undraw previous line, only if not first */
			XSetFunction (dpy, gc, GXxor);
			if (index != 1)
				XDrawLine (dpy,
				           win,
				           gc,
				           points[index].x,
				           points[index].y,
				           prev_x,
				           prev_y);
			XSetFunction (dpy, gc, GXcopy);

			/* Draw current line */
			XDrawLine(dpy,
			          win,
			          gc,
			          points[index].x,
			          points[index].y,
			          pos_x,
			          pos_y);
			prev_x = pos_x;
			prev_y = pos_y;
			break;

		case Expose:
			printf("got expose event\n");
			if (event.xexpose.window == win)
			{
				while (XCheckTypedWindowEvent (dpy,
				                               win,
				                               Expose,
				                               &event));
				XClearWindow(dpy, win);
				XDrawLines (dpy,
				            win,
				            gc,
				            points,
				            index,
				            CoordModeOrigin);
			}
		} // switch
	} // while

	XUnmapWindow(dpy, win);
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}
