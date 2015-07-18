/*
 *    XCopyArea, XClearArea
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <algorithm>



int main(int argc, char** argv)
{
	setvbuf(stdin, NULL, _IONBF, 0);
	Display* dpy = XOpenDisplay(NULL);
	if(!dpy) return -1;

	int scrno = DefaultScreen(dpy);
	int scrwidth = DisplayWidth(dpy, scrno);
	int scrheight = DisplayHeight(dpy, scrno);
	int depth = DefaultDepth(dpy, scrno);

	int winwidth = (int)(scrwidth / 1.5);
	int winheight = (int)(scrheight / 1.5);
	int winborder = 1;

	Window win = XCreateSimpleWindow(dpy,
	                                 RootWindow(dpy, scrno),
	                                 10, 10,
	                                 winwidth, winheight,
	                                 winborder,
	                                 BlackPixel(dpy, scrno),
	                                 WhitePixel(dpy, scrno));
	char* wintitle = (char*) "draw7 - XCopyArea, XClearArea";
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

	XSelectInput(dpy,
	             win,
	             ExposureMask |
	             ButtonPressMask |
	             StructureNotifyMask);

	XMapWindow(dpy, win);



	XGCValues values;
	values.line_width = 1;
	values.foreground = 0x000000;
	values.background = 0xffffff;
	unsigned long mask = GCLineWidth | GCForeground | GCBackground;

	GC gc = XCreateGC(dpy,
	                  win,
	                  mask,
	                  &values);



	// See draw6.cpp for XReadBitmapFile explanations
	Pixmap pixmap;
	unsigned int pix_width, pix_height;
	int x_hot, y_hot;
	int error = XReadBitmapFile(dpy,
	                            win,
	                            "bitmaps/tile_bitmap",
	                            &pix_width,
	                            &pix_height,
	                            &pixmap,
	                            &x_hot,
	                            &y_hot);
	if(error != BitmapSuccess)
		return -1;
	printf("\ntile_bitmap= %d x %d\n", pix_width, pix_height);

	Pixmap tile = XCreatePixmap(dpy,
	                            win,
	                            pix_width,
	                            pix_height,
	                            depth);

	XCopyPlane(dpy,
	           pixmap,  // src - from file
	           tile,    // dst - created
	           gc,
	           0, 0,
	           pix_width-1, pix_height-1,
	           0, 0,
	           1);

	XSetTile(dpy,
	         gc,
	         tile);

	XSetFillStyle(dpy,
	              gc,
	              FillTiled);

	XSetTSOrigin(dpy,
	             gc,
	             0, 0);// x, y


	bool bcopy = false;

	XEvent event;
	while(1)
	{
		XNextEvent(dpy, &event);

		if(event.type == Expose &&
		   event.xexpose.count == 0)
		{
			XClearWindow(dpy, win);

			XDrawRectangle(dpy,
			               win,
			               gc,
			               50, 50,
			               300, 300);

			XFillRectangle(dpy,
			               win,
			               gc,
			               70, 70,
			               260, 260);

			printf("\nXDrawRectangle, XFillRectangle");

			/* Testing XCopyArea, XClearArea */
			if(bcopy)
			{
				XCopyArea(dpy,
				          win,
				          win,
				          gc,
				          50, 50,
				          150, 150,
				          50, 450);
				XClearArea(dpy,
				           win,
				           50, 50,
				           150, 150,
				           False);
				printf("\nXCopyArea, XClearArea");
			}
		}

		if(event.type == ButtonPress)
		{
			bcopy = !bcopy;
		}
	}

	return 0;
}
