/*
 *    Regions:
 *      - used to clip drawing to specific area (Region).
 *      - similar with XGCValues.clip_mask (Pixmap)
 *        If clip_mask can validate drawing based on bits set to 1 in a Pixmap,
 *        the region will validate drawing in the entire area enclosed by Region.
 *      - XCreateRegion, XDestroyRegion, XOffsetRegion, XShrinkRegion, etc
 *        there are usefull methods for Region data in Xutil.h
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <string>
#include <sstream>


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
	int winwidth = scrwidth / 3;
	int winheight = scrheight / 2;
	int winborder = 1;

	Window win = XCreateSimpleWindow(dpy,
	                                 RootWindow(dpy, scrno),
	                                 x, y,
	                                 winwidth, winheight,
	                                 winborder,
	                                 BlackPixel(dpy, scrno),
	                                 WhitePixel(dpy, scrno));


	char* title = (char*)"draw12 - Regions";
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

	XSelectInput(dpy,
	             win,
	             ExposureMask |
	             KeyPressMask |
	             ButtonPressMask |
	             StructureNotifyMask);



	XGCValues gcvalues;
	gcvalues.line_width = 1;
	gcvalues.foreground = 0xff0000;//RED
	gcvalues.background = WhitePixel(dpy, scrno);
	unsigned long gcmask = GCLineWidth | GCForeground | GCBackground;

	GC gc = XCreateGC(dpy,
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
			XClearWindow(dpy, win);

			/* Set a region which is resulted from 2 merged regions:
			   r1 : 100,100,winwidth/2,winheight/2
			   r2 : winwidth/2,winheight/2,winwidht-100,winheight-100
			   Fill red a rectangle
			   rect: 100,100,winwidth-100,winheight-100
			 */

			const int NUMPOINTS=5;
			XPoint pts1[NUMPOINTS]={{100,100},{winwidth/2,100},
			                        {winwidth/2,winheight/2},
			                        {100,winheight/2},{100,100}};
			Region r1 = XPolygonRegion(pts1, NUMPOINTS, EvenOddRule);

			XPoint pts2[NUMPOINTS]={{winwidth/2,winheight/2},
			                        {winwidth-100,winheight/2},
			                        {winwidth-100,winheight-100},
			                        {winwidth/2,winheight-100},
			                        {winwidth/2,winheight/2}};
			Region r2 = XPolygonRegion(pts2, NUMPOINTS, EvenOddRule);

			Region r3 = XCreateRegion();
			XUnionRegion(r1, r2, r3);
			XSetRegion(dpy,
			           gc,
			           r3);


			XFillRectangle(dpy,
			               win,
			               gc,
			               100, 100,
			               (int)(winwidth-200), (int)(winheight-200));

			XDestroyRegion(r1);
			XDestroyRegion(r2);
			XDestroyRegion(r3);
		}



		if(event.type == ConfigureNotify)
		{
			if(event.xconfigure.window == win)
			{
				x = event.xconfigure.x;
				y = event.xconfigure.y;
				winwidth = event.xconfigure.width;
				winheight = event.xconfigure.height;
			}
		}

		if(event.type == ButtonPress)
		{
			break;
		}
	}


	XFreeGC(dpy, gc);
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}
