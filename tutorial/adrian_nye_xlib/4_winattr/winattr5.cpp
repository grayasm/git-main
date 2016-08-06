/*    Xlib Programming Manual (vol1) by Adrian Nye
 *    Cap.4 Window Attributes
 *    Xlib.h/struct XSetWinAttributes
 *    Xlib.h/extern Window XCreateWindow(..., XSetWindowAttributes*)
 *    Xlib.h/extern int    XChangeWindowAttributes(..., XSetWindowAttributes*)
 *
 *
 *    Set child window border to a Pixmap.
 *    (XSetWindowAttributes*)->border_pixmap;
 *
 *    I created a .xbm file with Gimp 3x3 Gray Scale to be set as border.
 *
 *    bitmaps/border_bitmap
 *    bitmaps/border_bitmap.xbm
 *
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include "bitmaps/border_bitmap"




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
	char* wintitle = (char*) "winattr5 - border pixmap";
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

	unsigned int childwidth = std::max(25, winwidth/4);
	unsigned int childheight = std::max(25, winheight/4);
	unsigned int childborder = 3; // pxl
	int depth = DefaultDepth(dpy, scrno);

	XSetWindowAttributes childattr;
	unsigned int bestwidth, bestheight;
	XQueryBestTile(dpy,
	               win,
	               childwidth,
	               childheight,
	               &bestwidth,
	               &bestheight);
	printf("\nBest Pixmap size for tiling is %d x %d\n", bestwidth, bestheight);

	Pixmap bgpixmap = XCreatePixmapFromBitmapData(dpy,
	                                              win,
	                                              border_bitmap_bits,
	                                              border_bitmap_width,
	                                              border_bitmap_height,
	                                              BlackPixel(dpy, scrno),
	                                              WhitePixel(dpy, scrno),
	                                              depth);
	childattr.background_pixel = WhitePixel(dpy, scrno);
	childattr.border_pixmap = bgpixmap;
	unsigned long mask = CWBackPixel | CWBorderPixmap; // <X11/X.h>

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
	}

	return 0;
}
