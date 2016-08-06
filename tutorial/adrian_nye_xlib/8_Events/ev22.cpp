/*
	ev22.cpp
	XEvent.xkeymap is XKeymapEvent structure.
	Xlib Programming Manual, pag.474 KeymapNotify

	A KeymapNotify event reports the state of the keyboard and occurs when
	the pointer or keyboard focus enters a window. KeymapNotify events are
	reported immediately after EnterNotify or FocusIn events. This is a way
	for the application to read the keyboard state as the application is
	"woken up", since the two triggering events usually indicate that the
	application is about to receive user input.

	This event is selected with KeymapStateMask


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
			XKeymapEvent xkeymap;        <---------- !!!!
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



void printXKeymapEvent(XKeymapEvent* xclient);

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
	long event_mask = KeymapStateMask | ButtonPressMask;
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

	GC gc = XCreateGC(dpy, win, gcmask, &gcvalues);

	XMapWindow(dpy, win);



	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);

		if(event.type == KeymapNotify)
		{
			XKeymapEvent* xkeymap = &(event.xkeymap);
			std::stringstream ss;
			ss << "XKeymapEvent";

			printXKeymapEvent(xkeymap);
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


void printXKeymapEvent(XKeymapEvent* xclient)
{
	printf("XKeymapEvent is XEvent.xclient parameter;\n");
	printf("xclient.type          = %d (%s)\n",
	       xclient->type, "XKeymapEvent");
	printf("xclient.serial        = %d\n", xclient->serial);
	printf("xclient.send_event    = %d\n", xclient->send_event);
	printf("xclient.display       = 0x%x\n", xclient->display);
	printf("xclient.window        = 0x%x\n", xclient->window);
	printf("xclient.key_vector    = %s\n\n\n", xclient->key_vector);
}
