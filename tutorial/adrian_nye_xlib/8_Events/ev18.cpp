/*
	ev18.cpp
	XEvent.xconfigure is XConfigureEvent structure.
	http://tronche.com/gui/x/xlib/events/window-state-change/configure.html

	The X server can report ConfigureNotify events to clients wanting
	information about actual changes to a window's state, such as size,
	position, border and stacking order. The X server generates this event
	type whenever one of the following configure window requests made by a
	client application actually completes:

	* A window's size, position, border and/or stacking order is configured
	  by calling XConfigureWindow()
	* The window's position in the stacking order is changed by calling
	  XLowerWindow(), XRaiseWindow() or XRestackWindows()
	* A window is moved by XMoveWindow()
	* A window size is changed by XResizeWindow()
	* A window size and location is changed by XMoveResizeWindow()
	* A window is mapped and its position in the stacking order is changed
	  by XMapRaised()
	* A window border is changed by XSetWindowBorderWidth()

	To receive ConfigureNotify events, set the StructureNotifyMask bit in the
	event-mask attribute of the window or the SubstructureNotifyMask bit in
	the event-mask attribute of the parent window (in which case, configuring
	any child generates an event).


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
			XConfigureEvent xconfigure;        <---------- !!!!
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
#include <X11/Xproto.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>



void printXConfigureEvent(XConfigureEvent* xconfigure);

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
	long event_mask = StructureNotifyMask | ButtonPressMask;

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


	int count = 0;
	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);

		if(event.type == ConfigureNotify)
		{
			XConfigureEvent* xconfigure = &(event.xconfigure);
			std::stringstream ss;
			ss << "XConfigureEvent";

			printXConfigureEvent(xconfigure);
			const std::string& msg = ss.str();

			XClearWindow(dpy, win);
			XDrawImageString(dpy,
			                 win,
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


void printXConfigureEvent(XConfigureEvent* xconfigure)
{
	printf("XConfigureEvent is XEvent.xconfigure parameter;\n");
	printf("xconfigure.type          = %d (%s)\n",
	       xconfigure->type, "XConfigureEvent");
	printf("xconfigure.serial        = %d\n", xconfigure->serial);
	printf("xconfigure.send_event    = %d\n", xconfigure->send_event);
	printf("xconfigure.display       = 0x%x\n", xconfigure->display);
	printf("xconfigure.event         = 0x%x\n", xconfigure->event);
	printf("xconfigure.window        = 0x%x\n", xconfigure->window);
	printf("xconfigure.[x,y]         = [%d,%d]\n",
	       xconfigure->x, xconfigure->y);
	printf("xconfigure.[width,height]= [%d,%d]\n",
	       xconfigure->width, xconfigure->height);
	printf("xconfigure.border_width  = %d\n", xconfigure->border_width);
	printf("xconfigure.above         = %x\n", xconfigure->above);
	printf("xconfigure.override_redirect= %d\n\n\n", xconfigure->override_redirect);
}
