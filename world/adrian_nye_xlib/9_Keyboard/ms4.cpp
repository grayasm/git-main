/*
  ms4.cpp  - sample taken from the book

  (3) reading the motion history buffer.
*/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <vector>


#define BUF_SIZE 2000

int main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	Display* dpy = XOpenDisplay(NULL);
	if(!dpy) return -1;

	if (XDisplayMotionBufferSize (dpy) <= 0)
	{
		printf ("%s: motion history buffer not provided on server", argv[0]);
		exit (-1); /* Or use all events method instead. */
	}


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
	long event_mask = ExposureMask | ButtonMotionMask | PointerMotionHintMask;

	/* Select all events for our top window. */
	XSelectInput(dpy, win, event_mask);

	/* Create a GC. */
	XGCValues gcvalues;
	gcvalues.line_width = 1;
	gcvalues.foreground = BlackPixel(dpy, scrno);
	gcvalues.background = WhitePixel(dpy, scrno);
	unsigned long gcmask = GCLineWidth | GCForeground | GCBackground;

	GC gc = XCreateGC(dpy,
	                  win,
	                  gcmask,
	                  &gcvalues);

	XSetForeground (dpy, gc, BlackPixel(dpy, scrno));

	/* Display window. */
	XMapWindow(dpy, win);



	/* History buffer. */
	int xpositions[BUF_SIZE], ypositions[BUF_SIZE];
	int count;
	Bool buffer_flled = False;
	Time start, stop, prevtime;
	XTimeCoord* xytimelist;
	int nevents;



	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);

		switch (event.type)
		{
		case MotionNotify:
			printf ("got a motion event\n");
			while (XCheckTypedEvent (dpy,
			                         MotionNotify,
			                         &event));
			start = prevtime;
			stop = event.xmotion.time;
			xytimelist = XGetMotionEvents (dpy,
			                               win,
			                               start,
			                               stop,
			                               &nevents);

			for (int i=0; i < nevents; ++i)
				XDrawPoint (dpy,
				            win,
				            gc,
				            xytimelist[i].x,
				            xytimelist[i].y);
			break;

		case Expose:
			printf ("got expose event\n");
			if (event.xexpose.window == win)
			{
				while (XCheckTypedWindowEvent (dpy,
				                               win,
				                               0,
				                               Expose,
				                               &event));

				xytimelist = XGetMotionEvents (dpy,
				                               win,
				                               0,
				                               CurrentTime,
				                               &nevents);
				for (int i=0; i < nevents; ++i)
					XDrawPoint (dpy,
					            win,
					            gc,
					            xytimelist[i].x,
					            xytimelist[i].y);
			}
			else
			{
				while (XCheckTypedWindowEvent (dpy,
				                               win,
				                               Expose,
				                               &event));
				/* Do basicwin drawing routine. */
			}
		} // switch
	} // while

	XUnmapWindow(dpy, win);
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}
