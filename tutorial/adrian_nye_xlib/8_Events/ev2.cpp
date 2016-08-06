/*
  Events:
  XAnyEvent is part of XEvent structure;  e.g. XEvent.xany

  typedef union _XEvent {
          int type;       //must not be changed; first element
          XAnyEvent xany;                   <---- !!!!!
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
		KeyPressMask | KeyReleaseMask |
		ButtonPressMask | ButtonReleaseMask |
		EnterWindowMask | LeaveWindowMask |
		PointerMotionMask | PointerMotionHintMask |
		Button1MotionMask | Button2MotionMask | Button3MotionMask |
		Button5MotionMask | ButtonMotionMask |
		KeymapStateMask |
		ExposureMask |
		VisibilityChangeMask |
		StructureNotifyMask |
		ResizeRedirectMask |
		SubstructureNotifyMask |
		SubstructureRedirectMask |
		FocusChangeMask |
		PropertyChangeMask |
		ColormapChangeMask |
		OwnerGrabButtonMask;

	/* Select all events for our top window. */
	XSelectInput(dpy, win, event_mask);
	XMapWindow(dpy, win);


	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);

		XAnyEvent* xany = &(event.xany);
		printf("XAnyEvent is component of XEvent; XEvent.xany\n");
		printf("XEvent.xany.type      = %d\n", xany->type);
		printf("XEvent.xany.serial    = %d\n", xany->serial);
		printf("XEvent.xany.send_event= %d\n", xany->send_event);
		printf("XEvent.xany.display   = %x\n", xany->display);
		printf("XEvent.xany.window    = %x\n\n\n", xany->window);
	}


	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}
