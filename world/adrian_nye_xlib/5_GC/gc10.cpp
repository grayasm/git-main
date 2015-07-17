/*    Cap 5. The Graphic Context
 *
 *    Clip Mask: limit effect of graphics requests to particular area.
 *    XGCValues.clip_mask is of type Pixmap
 *    clip_mask can also be set with: XSetClipMask
 *                                    XSetClipRectangle
 *                                    XSetRegion
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include "bitmaps/clip_mask"



int main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	Display* dpy = XOpenDisplay(NULL);
	if(!dpy) return -1;

	int scrno = DefaultScreen(dpy);
	int scrwidth = DisplayWidth(dpy, scrno);
	int scrheight = DisplayHeight(dpy, scrno);


	int winwidth = scrwidth / 3;
	int winheight = scrheight / 2;

	int winborder = 1;

	Window win = XCreateSimpleWindow(dpy,
	                                 RootWindow(dpy, scrno),
	                                 10, 10,
	                                 winwidth, winheight,
	                                 winborder,
	                                 BlackPixel(dpy, scrno),
	                                 WhitePixel(dpy, scrno));


	char* title = (char*)"gc10 - Clip mask";
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

	XSelectInput(dpy,win,ButtonPressMask | ExposureMask);


	Font fixed = XLoadFont(dpy, "fixed");
	Pixmap clippixmap = XCreatePixmapFromBitmapData(dpy,
	                                                win,
	                                                clip_mask_bits,
	                                                clip_mask_width,
	                                                clip_mask_height,
	                                                1,
	                                                0,
	                                                1);

	XGCValues gcvalues;
	gcvalues.foreground = 0x00ff00;
	gcvalues.background = WhitePixel(dpy, scrno);
	gcvalues.font = fixed;
	gcvalues.clip_mask = clippixmap;
	gcvalues.clip_x_origin = winwidth/2 - 100;
	gcvalues.clip_y_origin = winheight/2 - 100;


	unsigned long gcmask =
		GCForeground | GCBackground |
		GCFont |
		GCClipMask | GCClipXOrigin | GCClipYOrigin;


	GC gc = XCreateGC(dpy,
	                  win,
	                  gcmask,
	                  &gcvalues);

	XMapWindow(dpy, win);

	bool bfill = false;
	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);
		if(event.type == ButtonPress)
		{
			bfill = !bfill;
			XSetArcMode(dpy,
			            gc,
			            (bfill ? ArcPieSlice : ArcChord));

			// erase text
			XClearWindow(dpy, win);

			// write new text but in the clip_mask area (to be visible)
			char* str = (char*) (bfill ? "ArcPieSlice" : "ArcChord");
			int len = strlen(str);
			XDrawString(dpy,
			            win,
			            gc,
			            winwidth/2-100, winheight/2-100+20,
			            str,
			            len);
		}

		if(event.type == Expose &&
		   event.xexpose.count == 0)
		{
			XArc arcs[1]= {{winwidth/2, winheight/2, 200,200,90*64,270*64}};
			XFillArcs(dpy,
			          win,
			          gc,
			          arcs,
			          1);
		}
	}

	return 0;
}
