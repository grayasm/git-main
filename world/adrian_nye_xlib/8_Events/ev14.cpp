/*
	ev14.cpp
	XEvent.xunmap is XUnmapEvent structure.
	https://tronche.com/gui/x/xlib/events/window-state-change/unmap.html

	The X server can report UnmapNotify events to clients wanting information about
	which windows are unmapped. The X server generates this event type whenever
	a client application changes the window's state from mapped to unmapped.

	To receive UnmapNotify events, set the StructureNotifyMask bit in the
	event-mask attribute of the window or the SubstructureNotifyMask bit in 
	the event-mask attribute of the parent window (in which case, unmapping
	any child window generates an event).
	
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
			XUnmapEvent xunmap;        <---------- !!!!!
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



void printXUnmapEvent(XUnmapEvent* xunmap);

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
	long event_mask = StructureNotifyMask | ButtonPressMask | ButtonReleaseMask;



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


	// create a child window to map + unmap on button click
	Window childwin = XCreateSimpleWindow(dpy,
							win,
	                        x, y,
	                        winwidth-2*x, winheight-2*x,
	                        winborder,
	                        BlackPixel(dpy, scrno),
	                        WhitePixel(dpy, scrno));
	XSelectInput(dpy, childwin, event_mask);
			
	

	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);

		if(event.type == UnmapNotify)
		{
			XUnmapEvent* xunmap = &(event.xunmap);
			std::stringstream ss;
			ss << "XUnmapEvent";

			printXUnmapEvent(xunmap);
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
			std::string str("childwin mapped");
			XDrawImageString(dpy,
			                childwin,
			                gc,
			                20, 20,
			                str.c_str(),
			                str.size());
		}
		
		if(event.type == ButtonRelease)
		{
			XUnmapWindow(dpy, childwin);
		}
	}


	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}


void printXUnmapEvent(XUnmapEvent* xunmap)
{
	printf("XUnmapEvent is XEvent.xunmap parameter;\n");
	printf("xunmap.type          = %d (%s)\n",
	       xunmap->type, "XUnmapEvent");
	printf("xunmap.serial        = %d\n", xunmap->serial);
	printf("xunmap.send_event    = %d\n", xunmap->send_event);
	printf("xunmap.display       = 0x%x\n", xunmap->display);
	printf("xunmap.event (Window)= 0x%x\n", xunmap->event);
	printf("xunmap.window        = 0x%x\n", xunmap->window);
	printf("xunmap.from_configure= %d\n\n\n", xunmap->from_configure);
}
