/*
  ms2.cpp  - sample2 taken from the book.
  Tracking the pointer motion by
  (1) getting all motion events.

  Select PointerMotionMask.
  Filter MotionNotify events (e.g. XMotionEvent*)

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
		PointerMotionMask |
		ButtonPressMask;

	/* Select all events for our top window. */
	XSelectInput(dpy, win, event_mask);


	/* Select a nice font */
	Font font;
	int fontret = 0;
	XFontStruct* fontinfos;
	char** fontlist = XListFontsWithInfo(dpy,
	                                     "*",
	                                     700,         // maxnames
	                                     &fontret,    // actual_count_return
	                                     &fontinfos); // info_return
	if(fontlist == NULL)
		return -1;

	int ascent=0, descent=0, lbearing=0, rbearing=0;
	XFontStruct* fontinfo = 0;
	for(int i=0; i < fontret; ++i)
	{
		XFontStruct* fs = &(fontinfos[i]);
		XCharStruct* cs = &(fs->max_bounds);
		int fsz = cs->ascent + cs->descent;
		if(fsz < 12 || fsz > 14)
			continue;
		const char* fname = fontlist[i];
		// -medium-  -normal-  -r-
		if(strstr(fname, "-medium-") == 0 ||
		   strstr(fname, "-normal-") == 0 ||
		   strstr(fname, "-r-") == 0)
			continue;

		// found a Font
		font = XLoadFont(dpy, fname);        // load in the X server
		ascent = cs->ascent;
		descent = cs->descent;
		lbearing = cs->lbearing;
		rbearing = cs->rbearing;
		fontinfo = fs;
		break;
	}

	if(ascent == 0)
		return -1;

	// create a GC
	XGCValues gcvalues;
	gcvalues.line_width = 1;
	gcvalues.foreground = BlackPixel(dpy, scrno);
	gcvalues.background = WhitePixel(dpy, scrno);
	gcvalues.font = font;
	unsigned long gcmask = GCLineWidth | GCForeground | GCBackground | GCFont;

	GC gc = XCreateGC(dpy,
	                  win,
	                  gcmask,
	                  &gcvalues);

	XMapWindow(dpy, win);


	int xpositions[BUF_SIZE], ypositions[BUF_SIZE];
	int count = 0;
	bool buffer_filled = false;

	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);

		if (event.type == MotionNotify)
		{
			xpositions[count] = event.xmotion.x;
			ypositions[count] = event.xmotion.y;
			XDrawPoint (dpy, win, gc, event.xmotion.x, event.xmotion.y);
			if (count <= BUF_SIZE)
				count++;
			else
			{
				count = 0;
				buffer_filled = true;
			}
		}

		if (event.type == Expose)
		{
			if (event.xexpose.count == 0)
			{
				if (event.xexpose.window == win)
				{
					size_t buffsz = (buffer_filled == true ? BUF_SIZE : count);
					for (int i=0; i < buffsz; ++i)
					{
						XDrawPoint (dpy, win, gc, xpositions[i], ypositions[i]);
					}
				}
			}
		}

		if (event.type == ButtonPress)
		{
			break;
		}
	}


	XUnmapWindow(dpy, win);
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}
