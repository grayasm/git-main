/*
  ev9.cpp
  XEvent.xgraphicsexpose is XGraphicsExposeEvent structure.

  Event is sent to notify that an XCopyArea 's source is overlapped.
  XCopyArea copies from the source window src an area at (x,y,width,height)
  to the destination window dst at (x,y).
  Now, if src is partially (or totally) overalpped by another window on the
  screen then the X server does not update this area (ax,ay,aw,ah).
  This causes as side effect that XCopyArea 's destination to be partially
  drawn. The corresponding (ax,ay,aw,ah) from the source is not updated in the
  dst.
  For this effect the X server sends a GrahpicsExpose :)


  typedef union _XEvent {
          int type;       //must not be changed; first element
          XAnyEvent xany;
          XKeyEvent xkey;
          XButtonEvent xbutton;
          XMotionEvent xmotion;
          XCrossingEvent xcrossing;
          XFocusChangeEvent xfocus;
          XExposeEvent xexpose;
          XGraphicsExposeEvent xgraphicsexpose;      <---------- !!!!!
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
#include <X11/Xproto.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>



void printXGraphicsExposeEvent(XGraphicsExposeEvent* xgraphicsexpose);

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
	printf("\ntile_bitmap= %d x %d\n", pix_width, pix_height);

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

		// XCopyArea, XClearArea to trigger GraphicsExpose
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

			printf("\nXDrawRectangle, XFillRectangle");

			/* Testing XCopyArea, XClearArea */
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
				printf("\nXCopyArea, XClearArea");
			}
		}


		if(event.type == ButtonPress)
		{
			bcopy = !bcopy;
		}


		if(event.type == GraphicsExpose)
		{
			XGraphicsExposeEvent* xgraphicsexpose = &(event.xgraphicsexpose);
			std::stringstream ss;
			ss << xgraphicsexpose->x << "," << xgraphicsexpose->y
			   << " W:" << xgraphicsexpose->width
			   << " H:" << xgraphicsexpose->height
			   << " GraphicsExpose";

			printXGraphicsExposeEvent(xgraphicsexpose);
			const std::string& msg = ss.str();

			XDrawImageString(dpy,
			                 win,
			                 gc,
			                 xgraphicsexpose->x, xgraphicsexpose->y,
			                 msg.c_str(),
			                 msg.size());
		}
	}


	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}


void printXGraphicsExposeEvent(XGraphicsExposeEvent* xgraphicsexpose)
{
	printf("XGraphicsExposeEvent is XEvent.xgraphicsexpose parameter;\n");
	printf("xgraphicsexpose.type          = %d (%s)\n",
	       xgraphicsexpose->type, "XGraphicsExposeEvent");
	printf("xgraphicsexpose.serial        = %d\n", xgraphicsexpose->serial);
	printf("xgraphicsexpose.send_event    = %d\n", xgraphicsexpose->send_event);
	printf("xgraphicsexpose.display       = 0x%x\n", xgraphicsexpose->display);
	printf("xgraphicsexpose.window        = 0x%x\n", xgraphicsexpose->drawable);
	printf("xgraphicsexpose.x,y           = (%d,%d)\n", xgraphicsexpose->x, xgraphicsexpose->y);
	printf("xgraphicsexpose.width,height  = (%d,%d)\n", xgraphicsexpose->width, xgraphicsexpose->height);
	printf("xgraphicsexpose.count         = %d\n", xgraphicsexpose->count);
	printf("xgraphicsexpose.major_code    = %s\n",
	       (xgraphicsexpose->major_code == X_CopyArea ? "CopyArea" : "CopyPlane"));
	printf("xgraphicsexpose.minor_code    = %d (%s)\n\n\n",
	       xgraphicsexpose->minor_code, "not defined in the core");
}
