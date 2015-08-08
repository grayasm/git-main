/*
  ev4.cpp
  XEvent.xbutton is XButtonEvent structure.

  typedef union _XEvent {
          int type;       //must not be changed; first element
          XAnyEvent xany;
          XKeyEvent xkey;
          XButtonEvent xbutton;        <-------- !!!!!
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
	long event_mask = ButtonPressMask | ButtonReleaseMask;

	/* Select all events for our top window. */
	XSelectInput(dpy, win, event_mask);
	XMapWindow(dpy, win);


	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);

		if(event.type == ButtonPress ||
		   event.type == ButtonRelease)
		{
			XButtonEvent* xbutton = &(event.xbutton);
			printf("XButtonEvent member of XEvent; XEvent.xbutton\n");
			printf("xbutton.type          = %d (%s)\n",
			       xbutton->type,
			       (xbutton->type == ButtonPress ? "ButtonPress" :
			                                       "ButtonRelease"));
			printf("xbutton.serial        = %d\n", xbutton->serial);
			printf("xbutton.send_event    = %d\n", xbutton->send_event);
			printf("xbutton.display       = %x\n", xbutton->display);
			printf("xbutton.window        = %d\n", xbutton->window);
			printf("xbutton.root          = %d\n", xbutton->root);
			printf("xbutton.subwindow     = %d\n", xbutton->subwindow);
			printf("xbutton.time          = %d milisec\n", xbutton->time);
			printf("xbutton.x, y          = [%d,%d]\n", xbutton->x, xbutton->y);
			printf("xbutton.x_root, y_root= [%d,%d]\n",
			       xbutton->x_root, xbutton->y_root);
			printf("xbutton.state         = %d\n", xbutton->state);
			printf("xbutton.button        = %d\n", xbutton->button);
			printf("xbutton.same_screen   = %d\n\n\n", xbutton->same_screen);
		}
	}


	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}
