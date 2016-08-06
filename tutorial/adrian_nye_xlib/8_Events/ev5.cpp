/*
  ev5.cpp
  XEvent.xmotion is XMotionEvent structure.

  There was a problem receiving MotionNotify between ButtonPress/Release.
  If ButtonPress/Release are not processed, no MotionNotify is comming in
  between these events.

  typedef union _XEvent {
          int type;       //must not be changed; first element
          XAnyEvent xany;
          XKeyEvent xkey;
          XButtonEvent xbutton;
          XMotionEvent xmotion;        <-------- !!!!!
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



void printXMotionEvent(XMotionEvent* xmotion);

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
		PointerMotionMask |
		ButtonPressMask |
		ButtonReleaseMask;

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

		if(event.type == MotionNotify)
		{
			XMotionEvent* xmotion = &(event.xmotion);
			printXMotionEvent(xmotion);

			std::stringstream ss;
			ss << xmotion->x << "," << xmotion->y;
			ss << " XMotionNotify";
			const std::string& msg = ss.str();

			XClearWindow(dpy, win);
			XDrawImageString(dpy,
			                 win,
			                 gc,
			                 xmotion->x, xmotion->y,
			                 msg.c_str(),
			                 msg.size());
		}

		if(event.type == ButtonPress)
		{
			XButtonEvent* xbutton = &(event.xbutton);
			std::stringstream ss;
			ss << xbutton->x << "," << xbutton->y;
			ss << " ButtonPress";
			const std::string& msg = ss.str();

			XClearWindow(dpy, win);
			XDrawImageString(dpy,
			                 win,
			                 gc,
			                 xbutton->x, xbutton->y,
			                 msg.c_str(),
			                 msg.size());
		}

		if(event.type == ButtonRelease)
		{
			XButtonEvent* xbutton = &(event.xbutton);
			std::stringstream ss;
			ss << xbutton->x << "," << xbutton->y;
			ss << " ButtonRelease";
			const std::string& msg = ss.str();

			XClearWindow(dpy, win);
			XDrawImageString(dpy,
			                 win,
			                 gc,
			                 xbutton->x, xbutton->y,
			                 msg.c_str(),
			                 msg.size());
		}
	}


	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}


void printXMotionEvent(XMotionEvent* xmotion)
{
	printf("XMotionEvent is XEvent.xmotion parameter;\n");
	printf("xmotion.type          = %d (%s)\n",
	       xmotion->type, "MotionNotify");
	printf("xmotion.serial        = %d\n", xmotion->serial);
	printf("xmotion.send_event    = %d\n", xmotion->send_event);
	printf("xmotion.display       = 0x%x\n", xmotion->display);
	printf("xmotion.window        = 0x%x\n", xmotion->window);
	printf("xmotion.root          = 0x%x\n", xmotion->root);
	printf("xmotion.subwindow     = 0x%x\n", xmotion->subwindow);
	printf("xmotion.time          = %d milisec\n", xmotion->time);
	printf("xmotion.x,y           = (%d,%d)\n", xmotion->x, xmotion->y);
	printf("xmotion.x_root,y_root = (%d,%d)\n",
	       xmotion->x_root, xmotion->y_root);
	printf("xmotion.state         = %d\n", xmotion->state);
	printf("xmotion.is_hint       = %d\n", xmotion->is_hint);
	printf("xmotion.same_screen   = %d\n\n\n", xmotion->same_screen);
}
