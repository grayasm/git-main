/*
  ev11.cpp
  XEvent.xnoexpose is XNoExposeEvent structure.

  Event is sent to notify that an XCopyArea 's source is NOT overlapped.
  XCopyArea copies from the source window src an area at (x,y,width,height)
  to the destination window dst at (x,y).
  In ev9.cpp we tested GraphicsExpose event, which is sent when the source
  is overlapped resulting in destination being blank (background color).
  Here ev10.cpp we test NoExpose which simply says that XCopyArea will
  succeed because source is not overlapped.
  These 2 events do not tell anything about the dst (destination), but only
  about the src (source).


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
          XNoExposeEvent xnoexpose;      <---------- !!!!!
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
#include <X11/Xproto.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>



void printXNoExposeEvent(XNoExposeEvent* xnoexpose);

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
	int winwidth = scrwidth / 3;
	int winheight = scrheight / 2 ;
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
	long event_mask = ExposureMask | ButtonPressMask;



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



	// Need an example of XCopyArea (see 6_Draw/draw7.cpp)
	Pixmap pixmap;
	unsigned int pix_width, pix_height;
	int x_hot, y_hot;
	int error = XReadBitmapFile(dpy,
	                            win,
	                            "bitmaps/tile_bitmap",
	                            &pix_width,
	                            &pix_height,
	                            &pixmap,
	                            &x_hot,
	                            &y_hot);
	if(error != BitmapSuccess)
		return -1;


	Pixmap tile = XCreatePixmap(dpy,
	                            win,
	                            pix_width,
	                            pix_height,
	                            depth);

	XCopyPlane(dpy,
	           pixmap,  // src - from file
	           tile,    // dst - created
	           gc,
	           0, 0,
	           pix_width-1, pix_height-1,
	           0, 0,
	           1);

	XSetTile(dpy,
	         gc,
	         tile);

	XSetFillStyle(dpy,
	              gc,
	              FillTiled);

	XSetTSOrigin(dpy,
	             gc,
	             0, 0);// x, y



	bool bcopy = false;
	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);

		// XCopyArea, XClearArea to trigger GraphicsExpose and/or NoExpose
		if(event.type == Expose &&
		   event.xexpose.count == 0)
		{
			XClearWindow(dpy, win);

			XDrawRectangle(dpy,
			               win,
			               gc,
			               50, 50,
			               300, 300);

			XFillRectangle(dpy,
			               win,
			               gc,
			               70, 70,
			               260, 260);


			// Testing XCopyArea, XClearArea
			if(bcopy)
			{
				XCopyArea(dpy,
				          win,
				          win,
				          gc,
				          50, 50,
				          150, 150,
				          50, 450);
				XClearArea(dpy,
				           win,
				           50, 50,
				           150, 150,
				           False);
			}
		}


		if(event.type == ButtonPress)
		{
			bcopy = !bcopy;
		}


		if(event.type == NoExpose)
		{
			XNoExposeEvent* xnoexpose = &(event.xnoexpose);
			std::stringstream ss;
			ss << "XNoExposeEvent";

			printXNoExposeEvent(xnoexpose);
			const std::string& msg = ss.str();

			XDrawImageString(dpy,
			                 win,
			                 gc,
			                 20, 20,
			                 msg.c_str(),
			                 msg.size());
		}
	}


	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}


void printXNoExposeEvent(XNoExposeEvent* xnoexpose)
{
	printf("XNoExposeEvent is XEvent.xnoexpose parameter;\n");
	printf("xnoexpose.type          = %d (%s)\n",
	       xnoexpose->type, "XNoExposeEvent");
	printf("xnoexpose.serial        = %d\n", xnoexpose->serial);
	printf("xnoexpose.send_event    = %d\n", xnoexpose->send_event);
	printf("xnoexpose.display       = 0x%x\n", xnoexpose->display);
	printf("xnoexpose.window        = 0x%x\n", xnoexpose->drawable);
	printf("xnoexpose.major_code    = %s\n",
	       (xnoexpose->major_code == X_CopyArea ? "CopyArea" : "CopyPlane"));
	printf("xnoexpose.minor_code    = %d (%s)\n\n\n",
	       xnoexpose->minor_code, "not defined in the core");
}
