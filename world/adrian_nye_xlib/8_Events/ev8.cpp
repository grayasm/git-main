/*
  ev8.cpp
  XEvent.xexpose is XExposeEvent structure.

  Drag another window over this program top window to see the update.


  typedef union _XEvent {
          int type;       //must not be changed; first element
          XAnyEvent xany;
          XKeyEvent xkey;
          XButtonEvent xbutton;
          XMotionEvent xmotion;
          XCrossingEvent xcrossing;
          XFocusChangeEvent xfocus;
          XExposeEvent xexpose;      <-------------- !!!!!
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
          XGravityEvent xgravity;
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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>



void printXExposeEvent(XExposeEvent* xexpose);

int main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	Display* dpy = XOpenDisplay(NULL);
	if(!dpy) return -1;

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
	long event_mask = ExposureMask;



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

	int ascent=0, descent=0, lbearing=0, rbearing=0;
	XFontStruct* fontinfo = 0;
	for(int i=0; i < fontret; ++i)
	{
		XFontStruct* fs = &(fontinfos[i]);
		XCharStruct* cs = &(fs->max_bounds);
		int fsz = cs->ascent + cs->descent;
		if(fsz < 16 || fsz > 20)
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


	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);

		XExposeEvent* xexpose = 0;
		std::stringstream ss;
		if(event.type == Expose)
		{
			xexpose = &(event.xexpose);
			ss << xexpose->x << "," << xexpose->y
			   << " W:" << xexpose->width << " H:" << xexpose->height
			   << " Expose";
		}

		if(xexpose && xexpose->count == 0)
		{
			printXExposeEvent(xexpose);
			const std::string& msg = ss.str();
			XClearWindow(dpy, win);
			XDrawImageString(dpy,
			                 win,
			                 gc,
			                 xexpose->x, xexpose->y,
			                 msg.c_str(),
			                 msg.size());
		}
	}


	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}


void printXExposeEvent(XExposeEvent* xexpose)
{
	printf("XExposeEvent is XEvent.xexpose parameter;\n");
	printf("xexpose.type          = %d (%s)\n",
	       xexpose->type, "XExposeEvent");
	printf("xexpose.serial        = %d\n", xexpose->serial);
	printf("xexpose.send_event    = %d\n", xexpose->send_event);
	printf("xexpose.display       = 0x%x\n", xexpose->display);
	printf("xexpose.window        = 0x%x\n", xexpose->window);
	printf("xexpose.x,y           = (%d,%d)\n", xexpose->x, xexpose->y);
	printf("xexpose.width,height  = (%d,%d)\n", xexpose->width, xexpose->height);
	printf("xexpose.count         = %d\n\n\n", xexpose->count);
}
