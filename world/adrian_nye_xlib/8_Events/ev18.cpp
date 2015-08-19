/*
	ev18.cpp
	XEvent.xconfigure is XConfigureEvent structure.
	


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
	long event_mask =	StructureNotifyMask | ButtonPressMask;
	
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
	                parent1,
	                gcmask,
	                &gcvalues);
	
	XMapWindow(dpy, win);
	
	enum Methods
	{
		X_CONFIGURE_WINDOW=1,
		X_LOWER_WINDOW,
		X_MOVE_WINDOW,
		X_RESIZE_WINDOW,
		X_MOVE_RESIZE_WINDOW,
		X_MAP_RAISED,
		X_SET_WINDOW_BORDER_WIDTH
	};
	
	Methods method = X_CONFIGURE_WINDOW;
	
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

			XClearWindow(dpy, xconfigure->window);
			XDrawImageString(dpy,
			                xconfigure->window,
			                (xconfigure->parent == parent1 ? gc1 : gc2),
			                20, 20,
			                msg.c_str(),
			                msg.size());
		}

		if(event.type == ButtonPress)
		{
			switch(method)
			{
				case X_CONFIGURE_WINDOW:
				{
					unsigned int attrmask = 0;
					XWindowChanges values = {0, 0, 200, 80, 2, 
					
					XConfigureWindow(dpy, win, attrmask, &values);
				}
				break;
					
				case X_LOWER_WINDOW: break;
				case X_MOVE_WINDOW: break;
				case X_RESIZE_WINDOW: break;
				case X_MOVE_RESIZE_WINDOW: break;
				case X_MAP_RAISED: break;
				case X_SET_WINDOW_BORDER_WIDTH: break;
			}
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
	printf("xconfigure.parent        = 0x%x\n", xconfigure->parent);
	printf("xconfigure.[x,y]         = [%d,%d]\n",
		xconfigure->x, xconfigure->y);
	printf("xconfigure.override_redirect= %d\n\n\n", xconfigure->override_redirect);
}
