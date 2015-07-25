/*
 *    Images:
 *       - storing all data corresponding to a screen area or pixmap
 *       - it is a structure on the client side, and image methods do not need
 *         the X server to process data
 *       - Xlib has few minimal routines for manipulating image structures:
 *         create, initialize, destroy, get a pixel, set a pixel, extract a
 *         subimage, and add a constant value to all pixels.
 *       - routines are relatively slow because they work pixel by pixel
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
	int winheight = scrheight * 3 / 4 ;
	int winborder = 1;

	Window win1 = XCreateSimpleWindow(dpy,
	                                  RootWindow(dpy, scrno),
	                                  x, y,
	                                  winwidth, winheight,
	                                  winborder,
	                                  BlackPixel(dpy, scrno),
	                                  WhitePixel(dpy, scrno));


	char* title = (char*)"draw13 - Images";
	XTextProperty titleprop;
	XStringListToTextProperty(&title, 1, &titleprop);
	XSetWMProperties(dpy,
	                 win1,
	                 &titleprop,
	                 NULL,
	                 argv,
	                 argc,
	                 NULL,
	                 NULL,
	                 NULL);

	XSelectInput(dpy,
	             win1,
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
	                  win1,
	                  gcmask,
	                  &gcvalues);

	XMapWindow(dpy, win1);

	Window win2 = XCreateSimpleWindow(dpy,
	                                  RootWindow(dpy, scrno),
	                                  scrwidth/2,10,
	                                  winwidth, winheight,
	                                  winborder,
	                                  BlackPixel(dpy, scrno),
	                                  WhitePixel(dpy, scrno));
	XMapWindow(dpy, win2);


	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);
		if(event.type == Expose &&
		   event.xexpose.count == 0)
		{
			XClearWindow(dpy, win1);
			XFillRectangle(dpy,
			               win1,
			               gc,
			               20, 20,
			               winwidth-40, winheight-40);

			/* Image processing */
			XClearWindow(dpy, win2);
			XImage* xi = XGetImage(dpy,
			                       win1,
			                       0, 0,
			                       winwidth, winheight,
			                       AllPlanes,
			                       XYPixmap);

			for(int left_x = 0; left_x < winwidth/2; left_x++)
			{
				for(int y=0; y < winheight; ++y)
				{
					unsigned long pixel1 = XGetPixel(xi, left_x, y);
					int right_x = winwidth - left_x;
					if(left_x != right_x)
					{
						unsigned long pixel2 = XGetPixel(xi, right_x, y);
						XPutPixel(xi, left_x, y, pixel2);
					}
					XPutPixel(xi, right_x, y, pixel1);
				}
			}

			XPutImage(dpy,
			          win2,
			          gc,
			          xi,
			          0, 0,
			          0, 0,
			          winwidth, winheight);
		}



		if(event.type == ConfigureNotify)
		{
			if(event.xconfigure.window == win1)
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
	XDestroyWindow(dpy, win1);
	XDestroyWindow(dpy, win2);
	XCloseDisplay(dpy);

	return 0;
}
