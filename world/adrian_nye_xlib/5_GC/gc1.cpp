/*    Cap 5. The Graphic Context
 *
 *    1. The GC is very much like the window attributes are set.
 *       The structure name is XGCValues and is made up of these symbols:

        member                   mask                       default
        --------------------------------------------------------------
        function                 GCFunction                 GXcopy
        plane_mask               GCPlaneMask                all 1
        foreground               GCForeground               0
        background               GCBackground               1
        line_width               GCLineWidth                0
        line_style               GCLineStyle                LineSolid
        cap_style                GCCapStyle                 CapButt
        join_style               GCJoinStyle                JoinMiter
        fill_style               GCFillStyle                FillSolid
        fill_rule                GCFillRule                 EvenOddRule
        arc_mode                 GCArcMode                  ArcPieSlice
        tile                     GCTile                     pixmap filled with foreground
        stipple                  GCStipple                  pixmap filled with 1
        ts_x_origin              GCTileStipXOrigin          0
        ts_y_origin              GCTileStipYOrigin          0
        font                     GCFont                     implementation dependent
        subwindow_mode           GCSubwindowMode            ClipByChildren
        graphics_exposure        GCGraphicsExposures        True
        clip_x_origin            GCClipXOrigin              0
        clip_y_origin            GCClipYOrigin              0
        clip_mask                GCClipMask                 None
        dash_offset              GCDashOffset               0
        dashes                   GCDashList                 4

 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>




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


	char* title = (char*)"gc1 - simple GC";
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
	unsigned long gcmask = GCLineWidth;

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
			XDrawRectangle(dpy,
			               win,
			               gc,
			               winwidth/4, winheight/4,
			               winwidth/2, winheight/2);
			printf("\nXDrawRectangle\n");
		}
	}

	XFreeGC(dpy, gc);
	XCloseDisplay(dpy);
	return 0;
}
