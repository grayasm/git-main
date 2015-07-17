/*    Cap 5. The Graphic Context
 *
 *    Fill Rule
 *    XGCValues.fill_rule : where XFillPolygon draws (which pixels in path).
 *    XSetFillRule        : equivalent function
 *
 *    Possible values: EvenOddRule if area is overlapped an odd number of time
 *                                 it is not filled.
 *                     WindingRule overlapped area are always filled.
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>




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


	char* title = (char*)"gc8 - Fill Rule";
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
	XGCValues gcvalues;
	gcvalues.foreground = BlackPixel(dpy, scrno);
	gcvalues.background = WhitePixel(dpy, scrno);
	gcvalues.font = fixed;
	unsigned long gcmask = GCForeground | GCBackground | GCFont;

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
			XSetFillRule(dpy,
			             gc,
			             (bfill ? EvenOddRule : WindingRule));

			// erase text
			XClearWindow(dpy, win);

			// write new text
			char* str = (char*) (bfill ? "EvenOddRule" : "WindingRule");
			int len = strlen(str);
			XDrawString(dpy,
			            win,
			            gc,
			            20, 20,
			            str,
			            len);
		}

		if(event.type == Expose &&
		   event.xexpose.count == 0)
		{
			XPoint pts[12] = { {101,53}, {99,660}, {418,660}, {415,245},
			                  {44,241}, {74,421}, {487,413}, {317,294},
			                  {465,553},{600,368},{200,55}, {101,53} };
			XFillPolygon(dpy,
			             win,
			             gc,
			             pts,
			             12,
			             Complex,
			             CoordModeOrigin);
		}
	}

	return 0;
}
