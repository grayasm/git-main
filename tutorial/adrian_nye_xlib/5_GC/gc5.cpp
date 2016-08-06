/*    Cap 5. The Graphic Context
 *
 *    5.3 Controlling pixel selection.
 *    5.3.1 Line Characteristics
 *
 *    XGCValues.line_width    (0 fast, >= 1 with width)
 *    XGCValues.line_style    (LineSolid, LineOnOffDash, LineDoubleDash)
 *    XGCValues.cap_style     (CapButt, CapNotLast, CapProjecting, CapRound)
 *    XGCValues.join_style    (JoinBevel, JoinMiter, JoinRound)
 *    XGCValues.dashes        (3 means 3 pxl black, 3 pxl white)
 *    XGCValues.dash_offset   (0 usually)
 *
 *    In this example we use line_width, line_style and XSetDashes which can
 *    create more complex line patterns than XGCValues's dashes.
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>


#define NUMLINES 5
#define DOTTED_LIST_LENGTH 2
#define DOT_DASHED_LIST_LENGTH 4
#define SHORT_DASHED_LIST_LENGTH 2
#define LONG_DASHED_LIST_LENGTH 2
#define ODD_DASHED_LIST_LENGTH 3


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


	char* title = (char*)"gc5 - line characteristics";
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

	XSelectInput(dpy,win,ExposureMask);

	GC gc[NUMLINES];
	const int dash_list_length[] =
		{
			DOTTED_LIST_LENGTH,
			DOT_DASHED_LIST_LENGTH,
			SHORT_DASHED_LIST_LENGTH,
			LONG_DASHED_LIST_LENGTH,
			ODD_DASHED_LIST_LENGTH
		};
	const char dotted[DOTTED_LIST_LENGTH] = {2,6};
	const char dot_dashed[DOT_DASHED_LIST_LENGTH] = {2,8,2,1};
	const char short_dashed[SHORT_DASHED_LIST_LENGTH] = {12,12};
	const char long_dashed[LONG_DASHED_LIST_LENGTH] = {4,12};
	const char odd_dashed[ODD_DASHED_LIST_LENGTH] = {4,8,12};
	const char* dash_list[] =
		{
			dotted,
			dot_dashed,
			short_dashed,
			long_dashed,
			odd_dashed
		};
	for(int i=0; i < NUMLINES; ++i)
	{
		XGCValues gcv;
		int dash_offset = 0;
		gcv.line_width = 2;
		gcv.line_style = LineOnOffDash;
		gc[i] = XCreateGC(dpy,
		                  RootWindow(dpy, scrno),
		                  GCLineWidth | GCLineStyle,
		                  &gcv);
		XSetDashes(dpy,
		           gc[i],
		           dash_offset,
		           dash_list[i],
		           dash_list_length[i]);
	}


	XMapWindow(dpy, win);

	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);
		if(event.type == Expose &&
		   event.xexpose.count == 0)
		{
			for(int i=0; i < NUMLINES; ++i)
			{
				XDrawLine(dpy,
				          win,
				          gc[i],
				          winwidth/4, 40 + 30*i,
				          3 * (winwidth/4), 40 + 30*i);
			}
		}
	}

	return 0;
}
