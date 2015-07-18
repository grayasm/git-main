/*
 *    XReadBitmapFile - a bit more complex, requires additional steps compared
 *                      with XCreateBitmapFromData, because it does not have
 *                      the correct depth value.
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <algorithm>
#include "bitmaps/tile_bitmap"



int main(int argc, char** argv)
{
	setvbuf(stdin, NULL, _IONBF, 0);
	Display* dpy = XOpenDisplay(NULL);
	if(!dpy) return -1;

	int scrno = DefaultScreen(dpy);
	int scrwidth = DisplayWidth(dpy, scrno);
	int scrheight = DisplayHeight(dpy, scrno);
	int depth = DefaultDepth(dpy, scrno);

	int winwidth = scrwidth / 3;
	int winheight = scrheight / 3;
	int winborder = 4;

	Window win = XCreateSimpleWindow(dpy,
	                                 RootWindow(dpy, scrno),
	                                 10, 10,
	                                 winwidth, winheight,
	                                 winborder,
	                                 BlackPixel(dpy, scrno),
	                                 WhitePixel(dpy, scrno));
	char* wintitle = (char*) "draw6 - XReadBitmapFile";
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
	             ExposureMask);

	XMapWindow(dpy, win);


	/* Because XReadBitmapFile + steps require a GC we will create a GC
	   now without tiling settings. */
	XGCValues values;
	values.line_width = 1;
	values.foreground = 0x000000;
	values.background = 0xffffff;
	unsigned long mask = GCLineWidth | GCForeground | GCBackground;

	GC gc = XCreateGC(dpy,
	                  win,
	                  mask,
	                  &values);



	/*    Depth of the data available as char[][] versus
	      depth of the data read from a file.

	      To create a pixmap with depth from included data, you can substitute
	      XCreatePixmapFromBitmapData() for XCreateBitmapFromData() .

	      To create a pixmap with depth from data read from a file,
	      you must create a bitmap with XReadBitmapFile() , then create a pixmap
	      with depth using XCreatePixmap(), then copy from the bitmap to the
	      pixmap using XCopyPlane().
	 */
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

	/*    Finally we have a valid Pixmap for tiling operations. */
	XSetTile(dpy,
	         gc,
	         tile);

	XSetFillStyle(dpy,
	              gc,
	              FillTiled);

	XSetTSOrigin(dpy,
	             gc,
	             0, 0);// x, y


	XEvent event;
	while(1)
	{
		XNextEvent(dpy, &event);

		if(event.type == Expose &&
		   event.xexpose.count == 0)
		{
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

			printf("\nXDrawRectangle\nXFillRectangle\n");
		}
	}

	return 0;
}
