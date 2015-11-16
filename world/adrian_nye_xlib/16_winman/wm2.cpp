/*    Cap 16 Window Management
      Simple window manager;
*/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h> // XC_arrow

#include <stdio.h>
#include <stdlib.h>    // system
#include <string.h>
#include <unistd.h>    // execve
#include <sys/wait.h>  // wait

#include <sstream>
#include <string>
#include <list>




// declarations
void LogText (Window window,
              Window parent,
              Window subwindow,
              Window root,
              int    x,
              int    y,
              int    h,
              const std::string& text,
              Display* dpy,
              Window output,
              GC gc);

void MoveWindow (Display* dpy,
                 int scrno,
                 Window win,
                 GC gc,
                 Cursor hand_cursor,
                 int pointerx,
                 int pointery,
                 Window dbgwin,
                 GC dbggc,
                 int fnheight);

void DrawBox (Display* dpy,
              int scrno,
              Window win,
              GC gc,
              int left,
              int top,
              int right,
              int bottom);

void UndrawBox (Display* dpy,
                int scrno,
                Window win,
                GC gc,
                int left,
                int top,
                int right,
                int bottom);

void DrawFocusFrame (Display* dpy,
                     int scrno,
                     Window focus_window);


// program
int main(int argc, char* argv[])
{
	setvbuf(stdout, NULL, _IONBF, 0);
	Display* dpy = XOpenDisplay(NULL);
	if (!dpy) return -1;

	int scrno = DefaultScreen(dpy);
	int scrwidth = DisplayWidth(dpy, scrno);
	int scrheight = DisplayHeight(dpy, scrno);
	int depth = DefaultDepth(dpy, scrno);

	int x = 0;
	int y = 0;
	int winwidth = scrwidth;
	int winheight = 2 * scrheight / 3;
	int winborder = 1;

	unsigned long whitepxl = 0xffffff;
	unsigned long blackpxl = 0x000000;
	unsigned long yellowpxl= 0xfffdcf; // light yellow
	unsigned long bluepxl = 0x000d8d;  // dark blue

	Window rootwin = RootWindow(dpy, scrno);
	Window wallwin = XCreateSimpleWindow(dpy,
	                                     rootwin,
	                                     x, y,
	                                     winwidth, winheight,
	                                     winborder,
	                                     BlackPixel(dpy, scrno),
	                                     WhitePixel(dpy, scrno));

	int dbgwidth = winwidth;
	int dbgheight = scrheight / 3;
	Window dbgwin = XCreateSimpleWindow(dpy,
	                                    rootwin,
	                                    x, y + winheight,
	                                    dbgwidth, dbgheight,
	                                    winborder,
	                                    bluepxl,
	                                    yellowpxl);

	XSelectInput (dpy,
	              RootWindow(dpy, scrno),
	              SubstructureNotifyMask);


	long eventmask =
//		KeyPressMask | KeyReleaseMask |
		ButtonPressMask | ButtonReleaseMask |
		EnterWindowMask | LeaveWindowMask |
		PointerMotionMask |
//		PointerMotionHintMask |
//		Button1MotionMask |
//		Button2MotionMask |
//		Button3MotionMask |
//		Button4MotionMask |
//		Button5MotionMask |
//		ButtonMotionMask |
//		KeymapStateMask |
		ExposureMask |
//		VisibilityChangeMask |
		StructureNotifyMask |
//		ResizeRedirectMask |
		SubstructureNotifyMask |
//		SubstructureRedirectMask |
		FocusChangeMask |
		PropertyChangeMask |
		ColormapChangeMask |
		OwnerGrabButtonMask
		;

	XSelectInput (dpy,
	              wallwin,
	              eventmask);



	/* Select a nice (Latin-1) font for drawing text. */
	Font font;
	int fontret = 0;
	XFontStruct* fontinfos;
	char** fontlist = XListFontsWithInfo(dpy,
	                                     "*",
	                                     700,        // maxnames
	                                     &fontret,   // actual_count_return
	                                     &fontinfos);// info_return

	if (fontlist == NULL)
		return -1;

	int fnascent=0, fndescent=0, fnheight = 0, fnwidth = 0;
	XFontStruct* fontinfo = 0;
	for (int i=0; i < fontret; ++i)
	{
		XFontStruct* fs = &(fontinfos[i]);
		XCharStruct* cs = &(fs->max_bounds);
		int fsz = cs->ascent + cs->descent;
		if (fsz < 16 || fsz > 20)
			continue;

		const char* fname = fontlist[i];

		// xlsfonts: list all fonts
		// -medium- -normal- -r- -iso8859-
		if (strstr(fname, "-medium-") == 0 ||
		    strstr(fname, "-normal-") == 0 ||
		    strstr(fname, "-r-")      == 0 ||
		    strstr(fname, "-iso8859-")== 0)
			continue;

		// found a Font
		font = XLoadFont(dpy, fname); // load 1 time in the X server, than shared.
		fnascent = cs->ascent;
		fndescent = cs->descent;
		fnheight = fnascent + fndescent;
		fnwidth = cs->width;
		fontinfo = fs;
		break;
	}

	if (fnascent == 0)
		return -1;

	// create a GC
	XGCValues gcvalues;
	gcvalues.line_width = 1;
	gcvalues.foreground = BlackPixel(dpy, scrno);
	gcvalues.background = WhitePixel(dpy, scrno);
	gcvalues.font = font;
	unsigned long gcmask = GCLineWidth | GCForeground | GCBackground | GCFont;

	GC wallgc = XCreateGC (dpy,
	                   wallwin,
	                   gcmask,
	                   &gcvalues);

	gcvalues.foreground = bluepxl;
	gcvalues.background = yellowpxl;
	GC dbggc = XCreateGC(dpy,
	                     dbgwin,
	                     gcmask,
	                     &gcvalues);

	/* see cursorfont.h:
	   google: cursorfont.h images
	*/

	Cursor x_cursor = XCreateFontCursor (dpy, XC_X_cursor);
	Cursor left_arrow = XCreateFontCursor (dpy, XC_left_ptr);
	Cursor right_arrow = XCreateFontCursor (dpy, XC_arrow);
	Cursor hand_cursor = XCreateFontCursor (dpy, XC_hand2);

	XDefineCursor (dpy, wallwin, left_arrow);

	XMapWindow (dpy, wallwin);
	XMapWindow (dpy, dbgwin);


	// create a simple menu
	int mx = 0;
	int my = 0;
	int mwidth = 20 * fnwidth;
	int mheight = 1.5 * fnheight;



	const int menusz = 3;
	std::string smenu[ menusz ] = {"New Xterm", "Exit", "Move"};
	Window menu[ menusz ];
	GC gcmenu[ menusz ];
	for (int i=0; i < menusz; ++i)
	{
		menu[i] = XCreateSimpleWindow(dpy,
		                              wallwin,
		                              mx, my + (i+1)*mheight,
		                              mwidth, mheight ,
		                              winborder,
		                              blackpxl,
		                              whitepxl);
		XSelectInput (dpy, menu[i], ExposureMask | ButtonPressMask);
		gcmenu[i] = XCreateGC (dpy, menu[i], gcmask, &gcvalues);
		XDefineCursor (dpy, menu[i], right_arrow);
	}



	// Event loop
	XEvent event;
	while (1)
	{
		XNextEvent (dpy, &event);

		if (event.type == ButtonPress)
		{
			XButtonEvent* xbutton = &(event.xbutton);
			if (xbutton->window == wallwin)
			{
				std::stringstream ss;
				ss << " Btn=" << xbutton->button;
				ss << " ButtonPress";
				LogText (xbutton->window,
				         0,
				         xbutton->subwindow,
				         xbutton->root,
				         xbutton->x,
				         xbutton->y,
				         fnheight,
				         ss.str(),
				         dpy,
				         dbgwin,
				         dbggc);

				// display the menu
				if (xbutton->button == 1)
				{
					for (int i=0; i < menusz; ++i)
					{
						XMapWindow (dpy, menu[i]);
						XMoveWindow (dpy, menu[i], xbutton->x+5, xbutton->y + i*mheight - 5);
					}
				}

				// hide the menu
				if (xbutton->button == 3)
				{
					for (int i=0; i < menusz; ++i)
					{
						XUnmapWindow (dpy, menu[i]);
					}
				}
			}
			else if (xbutton->window == menu[0]) // xterm
			{
				system ("xterm &");

				LogText (xbutton->window,
				         0,
				         xbutton->subwindow,
				         xbutton->root,
				         xbutton->x,
				         xbutton->y,
				         fnheight,
				         " xterm&",
				         dpy,
				         dbgwin,
				         dbggc);
			}
			else if (xbutton->window == menu[1]) // exit
			{
				break;
			}
			else if (xbutton->window == menu[2]) // Move
			{
				/* all events are sent to the grabbing
                 * window regardless of
                 * whether this is True or False.
                 * owner events only affects the distribution of
                 * events when the pointer is within this
                 * application's windows. */
				XGrabPointer (dpy,
				              wallwin,        // grab window
				              False,          // owner events
				              ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
				              GrabModeAsync,  // pointer mode
				              GrabModeAsync,  // keyboard mode
				              None,           // confine the cursor to
				              hand_cursor,
				              CurrentTime);

				printf("XGrabPointer\n");

				bool moveIsValid = false;
				while (1)
				{
					XNextEvent (dpy, &event);

					/* Left mouse click into a foreign window. */
					if (event.type != ButtonPress)
						continue;

					if (event.xbutton.button != 1 ||
					    event.xbutton.window == wallwin ||
					    event.xbutton.window == dbgwin)
					{
						printf("Will not move window, break;\n");

						std::stringstream ss;
						ss << " Btn=" << xbutton->button;
						ss << " ButtonPress";
						LogText (xbutton->window,
						         0,
						         xbutton->subwindow,
						         xbutton->root,
						         xbutton->x,
						         xbutton->y,
						         fnheight,
						         ss.str(),
						         dpy,
						         dbgwin,
						         dbggc);
						break;
					}


					xbutton = &(event.xbutton);
					moveIsValid = true;
				}

				if (moveIsValid)
				{
					printf("\nMove is valid, let's start move action.");

					std::stringstream ss;
					ss << " Btn=" << xbutton->button;
					ss << " ACTION= MOVE started.";
					LogText (xbutton->window,
					         0,
					         xbutton->subwindow,
					         xbutton->root,
					         xbutton->x,
					         xbutton->y,
					         fnheight,
					         ss.str(),
					         dpy,
					         dbgwin,
					         dbggc);

					MoveWindow (dpy,
					            scrno,
					            xbutton->window,
					            wallgc,
					            hand_cursor,
					            xbutton->x,
					            xbutton->y,
					            dbgwin,
					            dbggc,
					            fnheight);

					printf("\nReturned from MoveWindow, ungrab follows");
				}

				XUngrabPointer (dpy, CurrentTime);
				XFlush (dpy);

				{
					/* Announce Ungrab Pointer */
					std::stringstream ss;
					ss << " Btn=" << xbutton->button;
					ss << " ACTION=MOVE ended.";
					LogText (xbutton->window,
					         0,
					         xbutton->subwindow,
					         xbutton->root,
					         xbutton->x,
					         xbutton->y,
					         fnheight,
					         ss.str(),
					         dpy,
					         dbgwin,
					         dbggc);
				}
			}
		}

		if (event.type == ButtonRelease)
		{
			XButtonEvent* xbutton = &(event.xbutton);
			if (xbutton->window == wallwin)
			{
                /* Log the event */
				std::stringstream ss;
				ss << " Btn=" << xbutton->button;
				ss << " ButtonRelease";
				LogText (xbutton->window,
				         0,
				         xbutton->subwindow,
				         xbutton->root,
				         xbutton->x,
				         xbutton->y,
				         fnheight,
				         ss.str(),
				         dpy,
				         dbgwin,
				         dbggc);
			}
		}

		if (event.type == EnterNotify)
		{
			XCrossingEvent* xcrossing = &(event.xcrossing);
			std::stringstream ss;
			if (xcrossing->window == wallwin)
				ss << " EnterNotify";
			else
				ss << " EnterNotify !wall";

			LogText (xcrossing->window,
			         0,
			         xcrossing->subwindow,
			         xcrossing->root,
			         xcrossing->x,
			         xcrossing->y,
			         fnheight,
			         ss.str(),
			         dpy,
			         dbgwin,
			         dbggc);
		}

		if (event.type == LeaveNotify)
		{
			XCrossingEvent* xcrossing = &(event.xcrossing);
			std::stringstream ss;
			if (xcrossing->window == wallwin)
				ss << " LeaveNotify";
			else
				ss << " LeaveNotify !wall";

			LogText (xcrossing->window,
			         0,
			         xcrossing->subwindow,
			         xcrossing->root,
			         xcrossing->x,
			         xcrossing->y,
			         fnheight,
			         ss.str(),
			         dpy,
			         dbgwin,
			         dbggc);
		}

		if (event.type == MotionNotify)
		{
			XMotionEvent* xmotion = &(event.xmotion);
			if (xmotion->window == wallwin)
			{
				int mx = xmotion->x;
				int my = xmotion->y;
				std::stringstream ss1;
				ss1 << "[" << mx << "," << my << "]";
				std::string str = ss1.str();

				XClearWindow(dpy, wallwin);
				XDrawString (dpy, wallwin, wallgc, mx, my, str.c_str(), str.size());
			}
		}

		if (event.type == Expose)
		{
			XExposeEvent* xexpose = &(event.xexpose);
			std::stringstream ss;
			if (xexpose->window == wallwin && xexpose->count == 0)
				ss << " Expose";
			else
				ss << " Expose !wall";

			LogText (xexpose->window,
			         0,
			         0,
			         0,
			         xexpose->x,
			         xexpose->y,
			         fnheight,
			         ss.str(),
			         dpy,
			         dbgwin,
			         dbggc);

			// menu items
			for (int i=0; i < menusz; ++i)
			{
				if (xexpose->window == menu[i])
				{
					XDrawString (dpy,
					             menu[i],
					             gcmenu[i],
					             1,
					             fnheight,
					             smenu[i].c_str(),
					             smenu[i].size());
				}
			}
		}

		if (event.type == ConfigureNotify)
		{
			XConfigureEvent* xconfigure = &(event.xconfigure);
			std::stringstream ss;
			if (xconfigure->window == wallwin)
				ss << " ConfigureNotify";
			else
				ss << " ConfigureNotify !wall";

			LogText (xconfigure->window,
			         xconfigure->above,
			         xconfigure->event,
			         0,
			         xconfigure->x,
			         xconfigure->y,
			         fnheight,
			         " ConfigureNotify",
			         dpy,
			         dbgwin,
			         dbggc);
		}

		if (event.type == VisibilityNotify)
		{
			LogText (0,
			         0,
				     0,
			         0,
				     0,
			         0,
			         fnheight,
			         " VisibilityNotify info",
			         dpy,
			         dbgwin,
			         dbggc);
		}

		if (event.type == CreateNotify)
		{
			XCreateWindowEvent* xcreatewindow;
			LogText (0,
			         0,
			         0,
			         0,
			         0,
			         0,
			         fnheight,
			         " XCreateWindowEvent info",
			         dpy,
			         dbgwin,
			         dbggc);
		}

		if (event.type == DestroyNotify)
		{
			XDestroyWindowEvent* xdestroywindow;
			LogText (0,
			         0,
			         0,
			         0,
			         0,
			         0,
			         fnheight,
			         " XDestroyWindowEvent info",
			         dpy,
			         dbgwin,
			         dbggc);
		}

		if (event.type == UnmapNotify)
		{
			XUnmapEvent* xunmap;
			LogText (0,
			         0,
			         0,
			         0,
			         0,
			         0,
			         fnheight,
			         " XUnmapEvent info",
			         dpy,
			         dbgwin,
			         dbggc);
		}

		if (event.type == MapNotify)
		{
			XMapEvent* xmap;
			LogText (0,
			         0,
			         0,
			         0,
			         0,
			         0,
			         fnheight,
			         " XMapEvent info",
			         dpy,
			         dbgwin,
			         dbggc);
		}

		if (event.type == MapRequest)
		{
			XMapRequestEvent* xmaprequest;
			LogText (0,
			         0,
			         0,
			         0,
			         0,
			         0,
			         fnheight,
			         " XMapRequestEvent info",
			         dpy,
			         dbgwin,
			         dbggc);
		}

		if (event.type == ReparentNotify)
		{
			XReparentEvent* xreparent;
			LogText (0,
			         0,
			         0,
			         0,
			         0,
			         0,
			         fnheight,
			         " XReparentEvent info",
			         dpy,
			         dbgwin,
			         dbggc);
		}

		if (event.type == ConfigureRequest)
		{
			XConfigureRequestEvent* xconfigurerequest;
			LogText (0,
			         0,
			         0,
			         0,
			         0,
			         0,
			         fnheight,
			         " XConfigureRequestEvent info",
			         dpy,
			         dbgwin,
			         dbggc);
		}

		if (event.type == ResizeRequest)
		{
			XResizeRequestEvent* xresizerequest;
			LogText (0,
			         0,
			         0,
			         0,
			         0,
			         0,
			         fnheight,
			         " XResizeRequestEvent info",
			         dpy,
			         dbgwin,
			         dbggc);
		}

		if (event.type == CirculateNotify)
		{
			XCirculateEvent* xcirculate;
			LogText (0,
			         0,
			         0,
			         0,
			         0,
			         0,
			         fnheight,
			         " XCirculateEvent info",
			         dpy,
			         dbgwin,
			         dbggc);
		}

		if (event.type == CirculateRequest)
		{
			XCirculateRequestEvent* xcirculaterequest;
			LogText (0,
			         0,
			         0,
			         0,
			         0,
			         0,
			         fnheight,
			         " XCirculateRequestEvent info",
			         dpy,
			         dbgwin,
			         dbggc);
		}

		if (event.type == PropertyNotify)
		{
			XPropertyEvent* xproperty;
			LogText (0,
			         0,
			         0,
			         0,
			         0,
			         0,
			         fnheight,
			         " XPropertyEvent info",
			         dpy,
			         dbgwin,
			         dbggc);
		}

		if (event.type == SelectionClear)
		{
			XSelectionClearEvent* xselectionclear;
			LogText (0,
			         0,
			         0,
			         0,
			         0,
			         0,
			         fnheight,
			         " XSelectionClearEvent info",
			         dpy,
			         dbgwin,
			         dbggc);
		}

		if (event.type == SelectionRequest)
		{
			XSelectionRequestEvent* xselectionrequest;
			LogText (0,
			         0,
			         0,
			         0,
			         0,
			         0,
			         fnheight,
			         " XSelectionRequestEvent info",
			         dpy,
			         dbgwin,
			         dbggc);
		}

		if (event.type == SelectionNotify)
		{
			XSelectionEvent* xselection;
			LogText (0,
			         0,
			         0,
			         0,
			         0,
			         0,
			         fnheight,
			         " XSelectionEvent info",
			         dpy,
			         dbgwin,
			         dbggc);
		}

		if (event.type == ColormapNotify)
		{
			XColormapEvent* xcolormap;
			LogText (0,
			         0,
			         0,
			         0,
			         0,
			         0,
			         fnheight,
			         " XColormapEvent info",
			         dpy,
			         dbgwin,
			         dbggc);
		}

		if (event.type == ClientMessage)
		{
			XClientMessageEvent* xclient;
			LogText (0,
			         0,
			         0,
			         0,
			         0,
			         0,
			         fnheight,
			         " XClientMessageEvent info",
			         dpy,
			         dbgwin,
			         dbggc);
		}

		if (event.type == MappingNotify)
		{
			XMappingEvent* xmapping;
			LogText (0,
			         0,
			         0,
			         0,
			         0,
			         0,
			         fnheight,
			         " XMappingEvent info",
			         dpy,
			         dbgwin,
			         dbggc);
		}

		if (event.type == GenericEvent)
		{
			XGenericEvent* xgeneric;
			LogText (0,
			         0,
			         0,
			         0,
			         0,
			         0,
			         fnheight,
			         " XGenericEvent info",
			         dpy,
			         dbgwin,
			         dbggc);
		}
	}



	XFreeGC(dpy, wallgc);
	XFreeGC(dpy, dbggc);
	XDestroyWindow(dpy, wallwin);
	XDestroyWindow(dpy, dbgwin);
	XCloseDisplay(dpy);

	return 0;
}


const int MAX_OUTPUT = 20;
static int line = 0;
static std::list<std::string> buffer;
void LogText( Window window,
              Window parent,
              Window subwindow,
              Window root,
              int    x,
              int    y,
              int    h,
              const std::string& text,
              Display* dpy,
              Window output,
              GC gc)
{
	std::stringstream ss;
	ss << std::dec << line++ << " ";
	ss << std::dec << "( " << x << "," << y << " )";
	ss << std::hex << " W:0x" << window;
	ss << std::hex << " P:0x" << parent;
	ss << std::hex << " C:0x" << subwindow;
	ss << std::hex << " R:0x" << root;
	ss << std::hex << " T: " << text.c_str();

	buffer.push_back(ss.str());
	while (buffer.size() > MAX_OUTPUT)
	{
		buffer.erase (buffer.begin());
	}

	XClearWindow (dpy, output);
	int i = h;
	for (std::list<std::string>::iterator it = buffer.begin();
	     it != buffer.end(); ++it, i += h)
	{
		XDrawString (dpy, output, gc, 5, i, (*it).c_str(), (*it).size());
	}
}


void MoveWindow (Display* dpy,          // default display
                 int scrno,             // screen number
                 Window win,            // window to move
                 GC gc,                 // wallwin GC
                 Cursor hand_cursor,    // cursor for move action
                 int pointerx,          // where is mouse now
                 int pointery,          // where is mouse now
                 Window dbgwin,         // debug window
                 GC dbggc,              // debug GC
                 int fnheight)          // font height
{
	{
		LogText (0,0,0,0,0,0,
		         fnheight,
		         " MoveWindow (1)",
		         dpy,
		         dbgwin,
		         dbggc);
	}


	bool box_drawn = false;

	XWindowAttributes winattr;
	XGetWindowAttributes (dpy,
	                      win,
	                      &winattr);
	int attrx = winattr.x;
	int attry = winattr.y;
	int width = winattr.width;
	int height = winattr.height;

	int offx = pointerx - attrx;
	int offy = pointery - attry;

	int x = pointerx - offx;
	int y = pointery - offy;

	XEvent event;
	while (1)
	{
		XNextEvent (dpy, &event);

		if (event.type == ButtonRelease)
		{
			XButtonEvent* xbutton = &(event.xbutton);

			if (box_drawn)
				UndrawBox (dpy, scrno, win, gc, x, y, width, height);

			x = xbutton->x - offx;
			y = xbutton->y - offy;

			XMoveWindow(dpy,
			            win,
			            x,
			            y);

			return;
		}
		else if (event.type == MotionNotify)
		{
			XMotionEvent* xmotion = &(event.xmotion);

			if (box_drawn == true)
				UndrawBox (dpy, scrno, win, gc, x, y, width, height);

			x = xmotion->x - offx;
			y = xmotion->y - offy;

			DrawBox (dpy, scrno, win, gc, x, y, width, height);

			box_drawn = true;
		}
		else
		{
			/* StructureNotify events shouldn't appear here,
			   because of the ChangeActivePointerGrab
			   call, but they do for some reason.
			   Anyway, it doesn't matter
			*/
			// printf("\nUnexpected event type %s\n", report.type);
		}
	}
}

void DrawBox (Display* dpy,
              int scrno,
              Window win,
              GC gc,
              int x,
              int y,
              int width,
              int height)
{
	XSetForeground (dpy,
	                gc,
	                WhitePixel (dpy, scrno) ^ BlackPixel (dpy, scrno));

	XDrawRectangle (dpy,
	                win,
	                gc,
	                x,
	                y,
	                width,
	                height);
}

void UndrawBox (Display* dpy,
                int scrno,
                Window win,
                GC gc,
                int x,
                int y,
                int width,
                int height)
{
	DrawBox (dpy, scrno, win, gc, x, y, width, height);
}
