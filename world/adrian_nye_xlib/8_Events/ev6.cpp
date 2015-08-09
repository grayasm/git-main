/*
  ev6.cpp
  XEvent.xcrossing is XCrossingEvent structure.

  This structure is filled on EnterWindow,LeaveWindow.
  On button press & release a grab/ungrab is also present as WindowLeave/Enter.

  typedef union _XEvent {
          int type;       //must not be changed; first element
          XAnyEvent xany;
          XKeyEvent xkey;
          XButtonEvent xbutton;
          XMotionEvent xmotion;
          XCrossingEvent xcrossing;        <-------- !!!!!
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



void printXCrossingEvent(XCrossingEvent* xmotion);

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
	long event_mask =
		EnterWindowMask | LeaveWindowMask;



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

		XCrossingEvent* xcrossing = 0;
		std::stringstream ss;

		if(event.type == EnterNotify)
		{
			xcrossing = &(event.xcrossing);
			ss << xcrossing->x << "," << xcrossing->y;
			ss << " EnterNotify";
		}
		if(event.type == LeaveNotify)
		{
			xcrossing = &(event.xcrossing);
			ss << xcrossing->x << "," << xcrossing->y;
			ss << " LeaveNotify";
		}

		if(xcrossing)
		{
			printXCrossingEvent(xcrossing);
			const std::string& msg = ss.str();
			XClearWindow(dpy, win);
			XDrawImageString(dpy,
			                 win,
			                 gc,
			                 xcrossing->x, xcrossing->y,
			                 msg.c_str(),
			                 msg.size());
		}
	}


	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}


void printXCrossingEvent(XCrossingEvent* xcrossing)
{
	printf("XCrossingEvent is XEvent.xcrossing parameter;\n");
	printf("xcrossing.type          = %d (%s)\n",
	       xcrossing->type, "XCrossingEvent");
	printf("xcrossing.serial        = %d\n", xcrossing->serial);
	printf("xcrossing.send_event    = %d\n", xcrossing->send_event);
	printf("xcrossing.display       = 0x%x\n", xcrossing->display);
	printf("xcrossing.window        = 0x%x\n", xcrossing->window);
	printf("xcrossing.root          = 0x%x\n", xcrossing->root);
	printf("xcrossing.subwindow     = 0x%x\n", xcrossing->subwindow);
	printf("xcrossing.time          = %d milisec\n", xcrossing->time);
	printf("xcrossing.x,y           = (%d,%d)\n", xcrossing->x, xcrossing->y);
	printf("xcrossing.x_root,y_root = (%d,%d)\n",
	       xcrossing->x_root, xcrossing->y_root);
	printf("xcrossing.mode          = %s\n",
	       xcrossing->mode == NotifyNormal ? "NotifyNormal" :
	       (xcrossing->mode == NotifyGrab ? "NotifyGrab" : "NotifyUngrab"));
	printf("xcrossing.detail        = %s\n",
	       (xcrossing->detail == NotifyAncestor ? "NotifyAncestor" :
	        (xcrossing->detail == NotifyVirtual ? "NotifyVirtual" :
	         (xcrossing->detail == NotifyInferior ? "NotifyInferior" :
	          (xcrossing->detail == NotifyNonlinear ? "NotifyNonlinear" :
	           "NotifyNonlinearVirtual")))));
	printf("xcrossing.same_screen   = %d\n", xcrossing->same_screen);
	printf("xcrossing.focus         = %d\n", xcrossing->focus);
	printf("xcrossing.state         = %d\n\n\n", xcrossing->state);
}
