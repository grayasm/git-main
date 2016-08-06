/*
	ev16.cpp
	XEvent.xmaprequest is XMapRequestEvent structure.
	https://tronche.com/gui/x/xlib/events/structure-control/map.html
 
	The X server can report MapRequest events to clients wanting information
	about a different client's desire to map windows. A window is considered
	mapped whan a map window request completes. The X server generates this
	event whenever a different client initiates a map window request on an 
	unmapped window whose override_redirect member is set to False. Clients
	initiate map window requests by calling XMapWindow(), XMapRaised() or 
	XMapSubwindows().

	To receive MapRequest events, set the SubstructureRedirectMask bit in the
	event-mask attribute of the window. This means another client's attempts
	to map a child window by calling one of the map window request functions
	is intercepted, and you are sent a MapRequest instead. For example, suppose
	a client application calls XMapWindow() to map a window. If you (usually
	a window manager) had selected SubstructureRedirectMask on the parent
	window and if the override_redirect attribute of the window is set to False,
	the X server reports a MapRequest event to you and does not map the specified
	window. Thus, this event gives your window manager client the ability
	to control the placement of subwindows.
 
	This sample does not work (e.g. the X server does not send the MapRequest
	event). I don't have enough knowledge about setting up the window manager.
 

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
			XMapRequestEvent xmaprequest;        <---------- !!!!!
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



void printXMapRequestEvent(XMapRequestEvent* xmaprequest);

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


	/*	Condition to receive MapRequest events:
		Have SubstructureRedirectMask on parent window.
		Have override_redirect = False on window attribute.
	*/
	long event_mask =	SubstructureRedirectMask |
						StructureNotifyMask |
						ButtonPressMask | ButtonReleaseMask;
	XSelectInput(dpy, win, event_mask);
	
	XSetWindowAttributes winattr;
	winattr.override_redirect = False;
	unsigned long attrmask = CWOverrideRedirect;
	XChangeWindowAttributes(dpy, win, attrmask, &winattr);
	
	
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


	// create a child window to map + unmap on button click
	Window childwin = XCreateSimpleWindow(dpy,
							win,
	                        x, y,
	                        winwidth-2*x, winheight-2*x,
	                        winborder,
	                        BlackPixel(dpy, scrno),
	                        WhitePixel(dpy, scrno));
	XSelectInput(dpy, childwin, event_mask);
	XChangeWindowAttributes(dpy, childwin, attrmask, &winattr);
			
	

	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);

		if(event.type == MapRequest)
		{
			XMapRequestEvent* xmaprequest = &(event.xmaprequest);
			std::stringstream ss;
			ss << "XMapRequestEvent";

			printXMapRequestEvent(xmaprequest);
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
			XMapWindow(dpy, childwin);			
		}
		
		if(event.type == ButtonRelease)
		{
			XUnmapWindow(dpy, childwin);
			std::string str("childwin unmapped");
			XDrawImageString(dpy,
			                win,
			                gc,
			                20, 20,
			                str.c_str(),
			                str.size());
		}
	}


	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}


void printXMapRequestEvent(XMapRequestEvent* xmaprequest)
{
	printf("XMapRequestEvent is XEvent.xmaprequest parameter;\n");
	printf("xmaprequest.type          = %d (%s)\n",
	       xmaprequest->type, "XMapRequestEvent");
	printf("xmaprequest.serial        = %d\n", xmaprequest->serial);
	printf("xmaprequest.send_event    = %d\n", xmaprequest->send_event);
	printf("xmaprequest.display       = 0x%x\n", xmaprequest->display);
	printf("xmaprequest.parent        = 0x%x\n", xmaprequest->parent);
	printf("xmaprequest.window        = 0x%x\n\n\n", xmaprequest->window);
}
