/*
	ev12.cpp
	XEvent.xcreatewindow is XCreateWindowEvent structure.
	https://tronche.com/gui/x/xlib/events/window-state-change/create.html

	X server can report CreateNotify events to clients wanting information about 
	creation of windows. The X server generates this event whenever a client
	application creates a widow by calling XCreateWindow() or XCreateSimpleWindow().

	Set SubstructureNotifyMask bit in the event-mask attribute of the window.
	Creating any children generates an event.


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
			XCreateWindowEvent xcreatewindow;        <---------- !!!!!
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
#include <X11/Xproto.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>



void printXCreateWindowEvent(XCreateWindowEvent* xcreatewindow);

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
	long event_mask = SubstructureNotifyMask | ButtonPressMask;



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

		if(event.type == CreateNotify)
		{
			XCreateWindowEvent* xcreatewindow = &(event.xcreatewindow);
			std::stringstream ss;
			ss << "XCreateWindowEvent";

			printXCreateWindowEvent(xcreatewindow);
			const std::string& msg = ss.str();

			XDrawImageString(dpy,
			                 win,
			                 gc,
			                 20, 20,
			                 msg.c_str(),
			                 msg.size());
		}
		
		if(event.type == ButtonPress)
		{
			Window childwin = XCreateSimpleWindow(dpy,
									win,
	                                x, y,
	                                winwidth-2*x, winheight-2*x,
	                                winborder,
	                                BlackPixel(dpy, scrno),
	                                WhitePixel(dpy, scrno));
			XMapWindow(dpy, childwin);
		}
	}


	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}


void printXCreateWindowEvent(XCreateWindowEvent* xcreatewindow)
{
	printf("XCreateWindowEvent is XEvent.xcreatewindow parameter;\n");
	printf("xcreatewindow.type          = %d (%s)\n",
	       xcreatewindow->type, "XCreateWindowEvent");
	printf("xcreatewindow.serial        = %d\n", xcreatewindow->serial);
	printf("xcreatewindow.send_event    = %d\n", xcreatewindow->send_event);
	printf("xcreatewindow.display       = 0x%x\n", xcreatewindow->display);
	printf("xcreatewindow.parent        = 0x%x\n", xcreatewindow->parent);
	printf("xcreatewindow.window        = 0x%x\n", xcreatewindow->window);
	printf("xcreatewindow.[x,y]         = [%d,%d]\n",
		xcreatewindow->x, xcreatewindow->y);
	printf("xcreatewindow.[width,height]= [%d,%d]\n",
		xcreatewindow->width, xcreatewindow->height);
	printf("xcreatewindow.border_width  = %d\n", xcreatewindow->border_width);
	printf("xcreatewindow.override_redir= %d\n\n\n", xcreatewindow->override_redirect);
}
