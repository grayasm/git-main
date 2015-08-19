/*
	ev17.cpp
	XEvent.xreparent is XReparentEvent structure.
	https://tronche.com/gui/x/xlib/events/window-state-change/reparent.html


	The X server can report ParentNotify events to clients wanting information
	about changing a window's parent. The X server generates this event
	whenever a client application calls XReparentWindow() and the window is
	actually reparented.

	To receive ReparentNotify events, set the StructureNotifyMask bit in 
	the event-mask attribute of the window or the SubstructureNotifyMask bit
	in the event-mask attribute of either the old or the new parent window
	(in which case, reparenting any child generates an event).


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
			XReparentEvent xreparent;        <---------- !!!!
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



void printXReparentEvent(XReparentEvent* xreparent);

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


	
	Window parent1 = XCreateSimpleWindow(dpy,
	                                RootWindow(dpy, scrno),
	                                x, y,
	                                winwidth, winheight,
	                                winborder,
	                                BlackPixel(dpy, scrno),
	                                WhitePixel(dpy, scrno));
	
	Window parent2 = XCreateSimpleWindow(dpy,
	                                RootWindow(dpy, scrno),
	                                x, y+winheight+20,
	                                winwidth, winheight,
	                                winborder,
	                                BlackPixel(dpy, scrno),
	                                WhitePixel(dpy, scrno));


	/* X.h
	   line: 150 to 175   Event definitions;
	*/
	long event_mask =	StructureNotifyMask | ButtonPressMask;
	
	XSelectInput(dpy, parent1, event_mask);
	XSelectInput(dpy, parent2, event_mask);

	
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

	GC gc1 = XCreateGC(dpy,
	                parent1,
	                gcmask,
	                &gcvalues);
	GC gc2 = XCreateGC(dpy,
					parent2,
					gcmask,
					&gcvalues);
	XMapWindow(dpy, parent1);
	XMapWindow(dpy, parent2);


	// create a child window to reparent
	Window childwin = XCreateSimpleWindow(dpy,
							parent1,
	                        x, y,
	                        winwidth-2*x, winheight-2*x,
	                        winborder,
	                        BlackPixel(dpy, scrno),
	                        WhitePixel(dpy, scrno));
	XSelectInput(dpy, childwin, event_mask);
	XMapWindow(dpy, childwin);
	
	bool bparent1 = true;
	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);

		if(event.type == ReparentNotify)
		{
			XReparentEvent* xreparent = &(event.xreparent);
			std::stringstream ss;
			ss << "XReparentEvent";

			printXReparentEvent(xreparent);
			const std::string& msg = ss.str();

			XClearWindow(dpy, xreparent->window);
			XDrawImageString(dpy,
			                xreparent->window,
			                (xreparent->parent == parent1 ? gc1 : gc2),
			                20, 20,
			                msg.c_str(),
			                msg.size());
		}
		
		if(event.type == ButtonPress)
		{
			XReparentWindow(dpy,
							childwin,
							(bparent1 == false ? parent1 : parent2),
							x, y);

			std::string msg("old parent");
			
			XClearWindow(dpy, (bparent1 == false ? parent2 : parent1));
			XDrawImageString(dpy,
			                (bparent1 == false ? parent2 : parent1),
			                (bparent1 == false ? gc2 : gc1),
			                20, 20,
			                msg.c_str(),
			                msg.size());
			bparent1 = !bparent1;
		}
	}

	return 0;
}


void printXReparentEvent(XReparentEvent* xreparent)
{
	printf("XReparentEvent is XEvent.xreparent parameter;\n");
	printf("xreparent.type          = %d (%s)\n",
	       xreparent->type, "XReparentEvent");
	printf("xreparent.serial        = %d\n", xreparent->serial);
	printf("xreparent.send_event    = %d\n", xreparent->send_event);
	printf("xreparent.display       = 0x%x\n", xreparent->display);
	printf("xreparent.event         = 0x%x\n", xreparent->event);
	printf("xreparent.window        = 0x%x\n", xreparent->window);
	printf("xreparent.parent        = 0x%x\n", xreparent->parent);
	printf("xreparent.[x,y]         = [%d,%d]\n",
		xreparent->x, xreparent->y);
	printf("xreparent.override_redirect= %d\n\n\n", xreparent->override_redirect);
}
