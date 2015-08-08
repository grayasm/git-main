/*
 *    Events - printing all events
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
		printEvent(&event);
		// want to print them all
	}


	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}

void printEvent(XEvent* event)
{
	switch(event->type)
	{
	case KeyPress:             printf("\tKeyPress\n"); break;
	case KeyRelease:           printf("\tKeyRelease\n"); break;
	case ButtonPress:          printf("\tButtonPress\n"); break;
	case ButtonRelease:        printf("\tButtonRelease\n"); break;
	case MotionNotify:         printf("\tMotionNotify\n"); break;
	case EnterNotify:          printf("\tEnterNotify\n"); break;
	case LeaveNotify:          printf("\tLeaveNotify\n"); break;
	case FocusIn:              printf("\tFocusIn\n"); break;
	case FocusOut:             printf("\tFocusOut\n"); break;
	case KeymapNotify:         printf("\tKeymapNotify\n"); break;
	case Expose:               printf("\tExpose\n"); break;
	case GraphicsExpose:       printf("\tGraphicsExpose\n"); break;
	case NoExpose:             printf("\tNoExpose\n"); break;
	case VisibilityNotify:     printf("\tVisibilityNotify\n"); break;
	case CreateNotify:         printf("\tCreateNotify\n"); break;
	case DestroyNotify:        printf("\tDestroyNotify\n"); break;
	case UnmapNotify:          printf("\tUnmapNotify\n"); break;
	case MapNotify:            printf("\tMapNotify\n"); break;
	case MapRequest:           printf("\tMapRequest\n"); break;
	case ReparentNotify:       printf("\tReparentNotify\n"); break;
	case ConfigureNotify:      printf("\tConfigureNotify\n"); break;
	case ConfigureRequest:     printf("\tConfigureRequest\n"); break;
	case GravityNotify:        printf("\tGravityNotify\n"); break;
	case ResizeRequest:        printf("\tResizeRequest\n"); break;
	case CirculateNotify:      printf("\tCirculateNotify\n"); break;
	case CirculateRequest:     printf("\tCirculateRequest\n"); break;
	case PropertyNotify:       printf("\tPropertyNotify\n"); break;
	case SelectionClear:       printf("\tSelectionClear\n"); break;
	case SelectionRequest:     printf("\tSelectionRequest\n"); break;
	case SelectionNotify:      printf("\tSelectionNotify\n"); break;
	case ColormapNotify:       printf("\tColormapNotify\n"); break;
	case ClientMessage:        printf("\tClientMessage\n"); break;
	case MappingNotify:        printf("\tMappingNotify\n"); break;
	case GenericEvent:         printf("\tGenericEvent\n"); break;
	}
}
