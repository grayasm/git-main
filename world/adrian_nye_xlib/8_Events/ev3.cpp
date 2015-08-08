/*
  Events: printing structure XKeyEvent (XEvent.xkey member)

  typedef union _XEvent {
          int type;       //must not be changed; first element
          XAnyEvent xany;
          XKeyEvent xkey;        <-------- !!!!!
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


void printEvent(XEvent* event);

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
	long event_mask = KeyPressMask | KeyReleaseMask;

	/* Select all events for our top window. */
	XSelectInput(dpy, win, event_mask);
	XMapWindow(dpy, win);


	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);

		if(event.type == KeyPress ||
		   event.type == KeyRelease)
		{
			XKeyEvent* xkey = &(event.xkey);
			printf("XKeyEvent is part of XEvent structure; XEvent.xkey\n");
			printf("xkey.type           = %d  (%s)\n",
			       xkey->type,
			       (xkey->type == KeyPress ? "KeyPress" : "KeyRelease"));
			printf("xkey.serial         = %d\n", xkey->serial);
			printf("xkey.send_event     = %d\n", xkey->send_event);
			printf("xkey.display        = %x\n", xkey->display);
			printf("xkey.window         = %d\n", xkey->window);
 			printf("xkey.root           = %d\n", xkey->root);
			printf("xkey.subwindow      = %d\n", xkey->subwindow);
			printf("xkey.time           = %d milisec\n", xkey->time);
			printf("xkey.x,y            = %d, %d\n", xkey->x, xkey->y);
			printf("xkey.x_root,y_root  = %d, %d\n", xkey->x_root, xkey->y_root);
			printf("xkey.state          = %d\n", xkey->state);
			printf("xkey.keycode        = %d\n", xkey->keycode);
			printf("xkey.same_screen    = %d\n\n\n", xkey->same_screen);
		}
	}


	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}
