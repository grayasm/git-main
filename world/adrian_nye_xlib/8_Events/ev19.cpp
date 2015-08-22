/*
	ev19.cpp
	XEvent.xgravity is XGravityEvent structure.
	Xlib Programming Manual, pag.472 GravityNotify

	A GravityNotify event reports when a window is moved because of a change
	in the size of its parent. This happens when the win_gravity attribute
	of the child window is something other than StaticGravity or UnmapGravity.
	This event is selected for a single window by specifying the window ID
	with StructureNotifyMask. To receive notification of movement due to
	gravity for a group of siblings, specify the parent ID with
	SubstructureNotifyMask.




  typedef union _XEvent {
			int type;       //must not be changed; first element
			XAnyEvent xany;
			XKeyEvent xkey;
			XButtonEvent xbutton;
			XMotionEvent xmotion;
			XCrossingEvent xcrossing;
			XFocusChangeEvent xfocus;
			XExposeEvent xexpose;
			XGraphicsExposeEvent xgraphicsexpose;
			XNoExposeEvent xnoexpose;
			XVisibilityEvent xvisibility;
			XCreateWindowEvent xcreatewindow;
			XDestroyWindowEvent xdestroywindow;
			XUnmapEvent xunmap;
			XMapEvent xmap;
			XMapRequestEvent xmaprequest;
			XReparentEvent xreparent;
			XConfigureEvent xconfigure;
			XGravityEvent xgravity;        <---------- !!!!
			XResizeRequestEvent xresizerequest;
			XConfigureRequestEvent xconfigurerequest;
			XCirculateEvent xcirculate;
			XCirculateRequestEvent xcirculaterequest;
			XPropertyEvent xproperty;
			XSelectionClearEvent xselectionclear;
			XSelectionRequestEvent xselectionrequest;
			XSelectionEvent xselection;
			XColormapEvent xcolormap;
			XClientMessageEvent xclient;
			XMappingEvent xmapping;
			XErrorEvent xerror;
			XKeymapEvent xkeymap;
			XGenericEvent xgeneric;
			XGenericEventCookie xcookie;
			long pad[24];
  } XEvent;
*/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xproto.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>



void printXGravityEvent(XGravityEvent* xgravity);

int main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	Display* dpy = XOpenDisplay(NULL);
	if(!dpy) return -1;

	int scrno = DefaultScreen(dpy);
	int scrwidth = DisplayWidth(dpy, scrno);
	int scrheight = DisplayHeight(dpy, scrno);
	int depth = DefaultDepth(dpy, scrno);

	int x = 10;
	int y = 10;
	int winwidth = scrwidth / 5;
	int winheight = scrheight / 5 ;
	int winborder = 2;


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
		StructureNotifyMask |
		SubstructureNotifyMask |
		ButtonPressMask;

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

	int ascent=0, descent=0, lbearing=0, rbearing=0;
	XFontStruct* fontinfo = 0;
	for(int i=0; i < fontret; ++i)
	{
		XFontStruct* fs = &(fontinfos[i]);
		XCharStruct* cs = &(fs->max_bounds);
		int fsz = cs->ascent + cs->descent;
		if(fsz < 12 || fsz > 14)
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

	// create a GC
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

	XMapWindow(dpy, win);

	// create a child window
	int cx = winwidth - 320;
	int cy = winheight - 100;
	int cwidth = 300;
	int cheight = 80;

	Window child = XCreateSimpleWindow(dpy,
	                                   win,
	                                   cx, cy,
	                                   cwidth, cheight,
	                                   winborder,
	                                   BlackPixel(dpy, scrno),
	                                   WhitePixel(dpy, scrno));
	XSelectInput(dpy, child, event_mask);

	// set gravity attribute of the window to receive GravityNotify event.
	unsigned long attrmask = CWWinGravity;
	XSetWindowAttributes attrvalues;
	attrvalues.win_gravity = SouthEastGravity;
	XChangeWindowAttributes(dpy, child, attrmask, &attrvalues);
	XMapWindow(dpy, child);




	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);

		if(event.type == GravityNotify)
		{
			XGravityEvent* xgravity = &(event.xgravity);
			std::stringstream ss;
			ss << "(" << cx << "," << cy << "; ";
			ss << cwidth << "," << cheight << ") XGravityEvent";

			printXGravityEvent(xgravity);
			const std::string& msg = ss.str();

			XClearWindow(dpy, win);
			XDrawImageString(dpy,
			                 child,
			                 gc,
			                 20, 20,
			                 msg.c_str(),
			                 msg.size());
		}

		if(event.type == ButtonPress)
		{
			break;
		}
	}

	return 0;
}


void printXGravityEvent(XGravityEvent* xgravity)
{
	printf("XGravityEvent is XEvent.xgravity parameter;\n");
	printf("xgravity.type          = %d (%s)\n",
	       xgravity->type, "XGravityEvent");
	printf("xgravity.serial        = %d\n", xgravity->serial);
	printf("xgravity.send_event    = %d\n", xgravity->send_event);
	printf("xgravity.display       = 0x%x\n", xgravity->display);
	printf("xgravity.event         = 0x%x\n", xgravity->event);
	printf("xgravity.window        = 0x%x\n", xgravity->window);
	printf("xgravity.[x,y]         = [%d,%d]\n\n\n",
	       xgravity->x, xgravity->y);
}
