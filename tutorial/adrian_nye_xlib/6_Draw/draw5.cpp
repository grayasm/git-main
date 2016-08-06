/*    Cap. 6  Drawing Graphics and Text.
 *
 *    XFillPolygon
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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


	char* title = (char*)"draw5 - XFillPolygon";
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
	gcvalues.foreground = BlackPixel(dpy, scrno);
	gcvalues.background = WhitePixel(dpy, scrno);
	unsigned long gcmask = GCLineWidth | GCForeground | GCBackground;

	GC gc = XCreateGC(dpy,
	                  win,
	                  gcmask,
	                  &gcvalues);

	XMapWindow(dpy, win);

	bool bfill = true;
	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);
		if(event.type == Expose &&
		   event.xexpose.count == 0)
		{
			XClearWindow(dpy,
			             win);

			const int NUMPOINTS = 20;
			XPoint pts[NUMPOINTS];
			for(int i=0; i < NUMPOINTS; ++i)
			{
				int px = (int)(rand() % winwidth);
				int py = (int)(rand() % winheight);
				pts[i].x = px;
				pts[i].y = py;

				printf("\npt= %d, %d", px, py);
			}

			XFillPolygon(dpy,
			             win,
			             gc,
			             pts,
			             NUMPOINTS,
			             Complex,
			             CoordModeOrigin);

			char* msg0 = (char*)"XFillPolygon drawing random generated points";
			char* msg1 = (char*)"Mouse click to XSetFillRule";
			char* msg2 = (char*)(bfill ? "EvenOddRule" : "WindingRule");
			XDrawString(dpy, win, gc, 20, 50, msg0, strlen(msg0));
			XDrawString(dpy, win, gc, 20, 70, msg1, strlen(msg1));
			XDrawString(dpy, win, gc, 20, 90, msg2, strlen(msg2));
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
			bfill = !bfill;
			if(bfill) XSetFillRule(dpy, gc, EvenOddRule);
			else XSetFillRule(dpy, gc, WindingRule);
		}
	}

	return 0;
}
