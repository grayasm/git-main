/*    Xlib Programming Manual (vol1) by Adrian Nye
 *    Cap.4 Window Attributes
 *    Xlib.h/struct XSetWinAttributes
 *    Xlib.h/extern Window XCreateWindow(..., XSetWindowAttributes*)
 *    Xlib.h/extern int    XChangeWindowAttributes(..., XSetWindowAttributes*)
 *
 *
 *    Set child window cursor to a Pixmap.
 *    (XSetWindowAttributes*)->cursor;
 *
 *    I created a .xbm file with Gimp 10x10 Gray Scale to be set as cursor.
 *
 *    bitmaps/cursor_bitmap
 *    bitmaps/cursor_bitmap.xbm
 *    bitmaps/cursor_mask
 *    bitmaps/cursor_mask.xbm
 *
 *    It tracks the pointer on the screen.
 *    It is sometimes also called the sprite.
 *    It is a server resource, defines a pattern, its colors and the point
 *            to be reported in events - the hotspot.
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include "bitmaps/cursor_bitmap"
#include "bitmaps/cursor_mask"



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
	char* wintitle = (char*) "winattr12 - cursor pixmap";
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
	unsigned int childborder = 4; // pxl
	int depth = DefaultDepth(dpy, scrno);

	XSetWindowAttributes childattr;
	Pixmap curpixmap = XCreatePixmapFromBitmapData(dpy,
	                                               RootWindow(dpy, scrno),
	                                               cursor_bitmap_bits,
	                                               cursor_bitmap_width,
	                                               cursor_bitmap_height,
	                                               1, //fg
	                                               0, //bg
	                                               1);//depth

	Pixmap curmask = XCreatePixmapFromBitmapData(dpy,
	                                             RootWindow(dpy, scrno),
	                                             cursor_mask_bits,
	                                             cursor_mask_width,
	                                             cursor_mask_height,
	                                             1, //fg
	                                             0, //bg
	                                             1);//depth
	XColor magenta, violet;
	Colormap clrmap = DefaultColormap(dpy, scrno);
	XParseColor(dpy, clrmap, "magenta", &magenta);
	XParseColor(dpy, clrmap, "BlueViolet", &violet);

	Cursor cur = XCreatePixmapCursor(dpy,
	                                 curpixmap,
	                                 curmask, // mask: pixmap or None
	                                 &magenta,
	                                 &violet,
	                                 cursor_bitmap_x_hot,
	                                 cursor_bitmap_y_hot
		);

	childattr.background_pixel = WhitePixel(dpy, scrno);
	childattr.border_pixel = BlackPixel(dpy, scrno);
	childattr.cursor = cur;
	unsigned long mask = CWBackPixel | CWBorderPixel | CWCursor;

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
