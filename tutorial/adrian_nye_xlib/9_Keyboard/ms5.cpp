/*
  ms5.cpp  - a bit more of a sample

  1) getting button related events like press,release,enter,leave,motion
  2) each press will switch to another drawing figure and set origin
  3) motion between press,release will update the drawing figure
  obs) rectangle not ok for moving left to origin
       circle not ok for moving above origin
*/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <vector>



int inc(int); // increment Edraw type safe

int main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, 0);

	Display* dpy = XOpenDisplay(NULL);
	if(!dpy)
		return -1;


	int scrno = DefaultScreen(dpy);
	int scrwidth = DisplayWidth(dpy, scrno);
	int scrheight = DisplayHeight(dpy, scrno);

	int x = 10;
	int y = 10;
	int winwidth = scrwidth / 5;
	int winheight = scrheight / 6 ;
	int winborder = 1;

	Window win = XCreateSimpleWindow(dpy,
	                                 RootWindow(dpy, scrno),
	                                 x, y,
	                                 winwidth, winheight,
	                                 winborder,
	                                 BlackPixel(dpy, scrno),
	                                 WhitePixel(dpy, scrno));

	/* X.h
	   line: 150 to 175   Event definitions;
	*/
	long event_mask =
		ButtonPressMask | ButtonReleaseMask |
		EnterWindowMask | LeaveWindowMask |
		PointerMotionMask | ButtonMotionMask;

	/* Select all events for our top window. */
	XSelectInput(dpy, win, event_mask);



	/* Select a nice font */
	Font font;
	int fontret = 0;
	XFontStruct* fontinfos;
	char** fontlist = XListFontsWithInfo(dpy,
	                                     "*",
	                                     700,         // maxnames
	                                     &fontret,    // actual_count_return
	                                     &fontinfos); // info_return
	if(fontlist == NULL)
		return -1;

	// Font details
	int fsz =0, ascent=0, descent=0, lbearing=0, rbearing=0;
	XFontStruct* fontinfo = 0;
	for(int i=0; i < fontret; ++i)
	{
		XFontStruct* fs = &(fontinfos[i]);
		XCharStruct* cs = &(fs->max_bounds);
		fsz = cs->ascent + cs->descent;
		if(fsz < 14 || fsz > 16)
			continue;
		const char* fname = fontlist[i];
		// -medium-  -normal-  -r-
		if(strstr(fname, "-medium-") == 0 ||
		   strstr(fname, "-normal-") == 0 ||
		   strstr(fname, "-r-") == 0)
			continue;

		// found a Font
		font = XLoadFont(dpy, fname);        // load in the X server
		ascent = cs->ascent;
		descent = cs->descent;
		lbearing = cs->lbearing;
		rbearing = cs->rbearing;
		fontinfo = fs;
		break;
	}

	if(ascent == 0)
		return -1;


	/* Create a GC. */
	XGCValues gcvalues;
	gcvalues.line_width = 1;
	gcvalues.foreground = BlackPixel(dpy, scrno);
	gcvalues.background = WhitePixel(dpy, scrno);
	gcvalues.font = font;
	unsigned long gcmask = GCLineWidth | GCForeground | GCBackground | GCFont;

	GC gc = XCreateGC(dpy,
	                  win,
	                  gcmask,
	                  &gcvalues);

	/* Display window. */
	XMapWindow(dpy, win);



	bool bIfDrawing = false;
	enum Edraw
	{
		DRAW_ARC        =1,
		DRAW_LINE       =2,
		DRAW_POINT      =3,
		DRAW_RECTANGLE  =4,
		DRAW_SEGMENTS   =5
	} drawWhat = DRAW_ARC;

	XArc xarc; // x,y,width,height,angle1 (deg*64),angle2 (deg*64)
	XPoint xline[2]; // x,y
	XPoint xpoint;
	XRectangle xrect; // x,y,width,height
	XSegment xsegment[1]; // x1,y1,x2,y2

	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);

		if (event.type == ButtonPress)
		{
			// event
			XButtonEvent* xbutton = &(event.xbutton);
			std::stringstream ss;
			ss << xbutton->x; ss << ","; ss << xbutton->y; ss << " ButtonPress";

			// drawing
			bIfDrawing = true;
			drawWhat = (Edraw)inc((int) drawWhat);
			switch (drawWhat)
			{
			case DRAW_ARC:
				xarc.x = xbutton->x; xarc.y = xbutton->y;
				xarc.width = 5; xarc.height = 5;
				xarc.angle1 = 0; xarc.angle2 = 360*64; // degrees * 64
				ss << " Arc";
				break;
			case DRAW_LINE:
				xline[0].x = xbutton->x; xline[0].y = xbutton->y;
				ss << " Line";
				break;
			case DRAW_POINT:
				xpoint.x = xbutton->x; xpoint.y = xbutton->y;
				ss << " Point";
				break;
			case DRAW_RECTANGLE:
				xrect.x = xbutton->x; xrect.y = xbutton->y;
				ss << " Rectangle";
				break;
			case DRAW_SEGMENTS:
				xsegment[0].x1 = xbutton->x; xsegment[0].y1 = xbutton->y;
				ss << " Segments";
				break;
			}


			// show info
			std::string str = ss.str();
			XClearWindow (dpy, win);
			XDrawString (dpy,
			             win,
			             gc,
			             xbutton->x, xbutton->y,
			             str.c_str(),
			             str.size());

		}
		else if (event.type == ButtonRelease)
		{
			// event
			XButtonEvent* xbutton = &(event.xbutton);
			std::stringstream ss;
			ss << xbutton->x; ss << ","; ss << xbutton->y; ss << " ButtonRelease";

			// drawing
			bIfDrawing = false;

			// show info
			std::string str = ss.str();
			XClearWindow (dpy, win);
			XDrawString (dpy,
			             win,
			             gc,
			             xbutton->x, xbutton->y,
			             str.c_str(),
			             str.size());
		}
		else if (event.type == EnterNotify)
		{
			// event
			XCrossingEvent* xcrossing = &(event.xcrossing);
			std::stringstream ss;
			ss << xcrossing->x; ss << ","; ss << xcrossing->y; ss << " EnterNotify";

			// drawing
			bIfDrawing = false;

			// show info
			std::string str = ss.str();
			XClearWindow (dpy, win);
			XDrawString (dpy,
			             win,
			             gc,
			             xcrossing->x, xcrossing->y,
			             str.c_str(),
			             str.size());
		}
		else if (event.type == LeaveNotify)
		{
			// event
			XCrossingEvent* xcrossing = &(event.xcrossing);
			std::stringstream ss;
			ss << xcrossing->x; ss << ","; ss << xcrossing->y; ss << " LeaveNotify";

			// drawing
			bIfDrawing = false;

			// show info
			std::string str = ss.str();
			XClearWindow (dpy, win);
			XDrawString (dpy,
			             win,
			             gc,
			             xcrossing->x, xcrossing->y,
			             str.c_str(),
			             str.size());
		}
		else if (event.type == MotionNotify)
		{
			// event
			XMotionEvent* xmotion = &(event.xmotion);
			std::stringstream ss;
			ss << xmotion->x; ss << ","; ss << xmotion->y; ss << " MotionNotify";

			// drawing
			switch (drawWhat)
			{
			case DRAW_ARC:
			{
				int dx = xmotion->x - xarc.x;
				int dy = xmotion->y - xarc.y;
				xarc.width = dx;
				xarc.height = dy;
				ss << " Arc";
			}
			break;
			case DRAW_LINE:
				xline[1].x = xmotion->x; xline[1].y = xmotion->y;
				ss << " Line";
				break;
			case DRAW_POINT:
				xpoint.x = xmotion->x; xpoint.y = xmotion->y;
				ss << " Point";
				break;
			case DRAW_RECTANGLE:
			{
				int dx = xmotion->x - xrect.x;
				int dy = xmotion->y - xrect.y;
				xrect.width = dx;
				xrect.height = dy;
				ss << " Rectangle";
			}
			break;
			case DRAW_SEGMENTS:
				xsegment[0].x2 = xmotion->x; xsegment[0].y2 = xmotion->y;
				ss << " Segments";
				break;
			}

			// show info
			std::string str = ss.str();
			XClearWindow (dpy, win);
			XDrawString (dpy,
			             win,
			             gc,
			             xmotion->x, xmotion->y,
			             str.c_str(),
			             str.size());
		}


		// Effective drawing
		if (bIfDrawing)
		{
			switch (drawWhat)
			{
			case DRAW_ARC:
				XDrawArcs (dpy, win, gc, &xarc, 1);
				break;
			case DRAW_LINE:
				XDrawLines (dpy, win, gc, xline, 2, CoordModeOrigin);
				break;
			case DRAW_POINT:
				XDrawPoints (dpy, win, gc, &xpoint, 1, CoordModeOrigin); 
				break;
			case DRAW_RECTANGLE:
				XDrawRectangles (dpy, win, gc, &xrect, 1);
				break;
			case DRAW_SEGMENTS:
				XDrawSegments (dpy, win, gc, xsegment, 1);
				break;
			}
		}
	} // while

	XUnmapWindow(dpy, win);
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}


int inc(int val)  /* increment*/
{
	++ val;
	if (val > 5) // DRAW_SEGMENTS
		val = 1; // DRAW_ARC
	return val;
}
