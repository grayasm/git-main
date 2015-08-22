/*
	ev21.cpp
	XEvent.xclient is XClientMessageEvent structure.
	Xlib Programming Manual, pag.454 ClientMessage

	A ClientMessage event is sent as a result of a call to XSendEvent() by
	a client to a particular window. Any type of event can be sent with
	XSendEvent(), but it will be distinguished from normal events by the
	send_event member being set to True.
	If your program wants to be able to treat events sent with XSendEvent()
	as different from normal events, you can read this member.

	There is no event mask for ClientMessage events, and they are not selected
	with XSelectInput. Instead XSendEvent directs them to a specific window,
	which is given as a window ID: the PointerWindow or the InputFocus.



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
			XClientMessageEvent xclient;        <---------- !!!!
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



void printXClientMessageEvent(XClientMessageEvent* xclient);

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


	Window win1 = XCreateSimpleWindow(dpy,
	                                  RootWindow(dpy, scrno),
	                                  x, y,
	                                  winwidth, winheight,
	                                  winborder,
	                                  BlackPixel(dpy, scrno),
	                                  WhitePixel(dpy, scrno));

	Window win2 = XCreateSimpleWindow(dpy,
	                                  RootWindow(dpy, scrno),
	                                  x, y + winheight + 20,
	                                  winwidth, winheight,
	                                  winborder,
	                                  BlackPixel(dpy, scrno),
	                                  WhitePixel(dpy, scrno));

	/* X.h
	   line: 150 to 175   Event definitions;
	*/
	long event_mask = StructureNotifyMask |ButtonPressMask;
	XSelectInput(dpy, win1, event_mask);
	XSelectInput(dpy, win2, event_mask);


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

	GC gc1 = XCreateGC(dpy, win1, gcmask, &gcvalues);
	GC gc2 = XCreateGC(dpy, win2, gcmask, &gcvalues);

	XMapWindow(dpy, win1);
	XMapWindow(dpy, win2);


	// An event needs to be sent between 2 windows
	// and it will contain the XClientMessageEvent member initialized.
	XEvent event1;
	event1.type = ClientMessage;
	XClientMessageEvent* xclient1 = &(event1.xclient);
	xclient1->type = ClientMessage;
	xclient1->send_event = True;
	xclient1->display = dpy;
	// xclient1->window; - set in the loop
	// xclient1->message_type; - unknown
	xclient1->format = 8; // client_event.data is char[20];
	const char* msg1 = "msg for window 1";
	const char* msg2 = "msg for window 2";

	XEvent event2;
	while (1)
	{
		XNextEvent(dpy, &event2);

		if(event2.type == ClientMessage)
		{
			XClientMessageEvent* xclient2 = &(event2.xclient);
			std::stringstream ss;
			ss << "XClientMessageEvent (";
			if(xclient2->format == 8)
				ss << xclient2->data.b;
			else
				ss << "format unknown";
			ss << ")";

			printXClientMessageEvent(xclient2);
			const std::string& msg = ss.str();

			Window win = xclient2->window;
			GC gc = (win == win1 ? gc1 : gc2);

			XClearWindow(dpy, win1);
			XClearWindow(dpy, win2);
			XDrawImageString(dpy,
			                 win,
			                 gc,
			                 20, 20,
			                 msg.c_str(),
			                 msg.size());
		}

		if(event2.type == ButtonPress)
		{
			XButtonEvent* xbutton = &(event2.xbutton);
			Window win = (xbutton->window == win1 ? win2 : win1);
			xclient1->window = win;
			strcpy(xclient1->data.b, (win == win1 ? msg1 : msg2));

			XSendEvent(dpy, win, True, NoEventMask, &event1);

			printf("client message from %s to %s\n",
			       (xbutton->window == win1 ? "win1" : "win2"),
			       (xbutton->window == win1 ? "win2" : "win1"));
		}
	}

	return 0;
}


void printXClientMessageEvent(XClientMessageEvent* xclient)
{
	printf("XClientMessageEvent is XEvent.xclient parameter;\n");
	printf("xclient.type          = %d (%s)\n",
	       xclient->type, "XClientMessageEvent");
	printf("xclient.serial        = %d\n", xclient->serial);
	printf("xclient.send_event    = %d\n", xclient->send_event);
	printf("xclient.display       = 0x%x\n", xclient->display);
	printf("xclient.message_type  = %d\n", xclient->message_type);
	printf("xclient.format        = %d\n", xclient->format);
	printf("xclient.data          = %s\n\n\n",
	       xclient->data.b); // i send only text
}
