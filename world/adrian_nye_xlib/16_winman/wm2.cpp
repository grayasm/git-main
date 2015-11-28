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

void ResizeWindow (Display* dpy,
                   int scrno,
                   Window win,
                   GC gc,
                   Cursor hand_cursor,
                   int pointerx,
                   int pointery,
                   Window dbgwin,
                   GC dbggc,
                   int fnheight);

void GetEventInfo (XEvent* event,
                   std::string& info);


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
	Window rootwin = RootWindow(dpy, scrno);


	int x = 0;
	int y = 0;
	int winwidth = scrwidth;
	int winheight = 2 * scrheight / 3;
	int winborder = 1;


	unsigned long whitepxl = 0xffffff;
	unsigned long blackpxl = 0x000000;
	unsigned long yellowpxl= 0xfffdcf; // light yellow
	unsigned long bluepxl = 0x000d8d;  // dark blue



	Window wallwin = XCreateSimpleWindow(dpy,
	                                     rootwin,
	                                     x, y,
	                                     winwidth, winheight,
	                                     winborder,
	                                     BlackPixel(dpy, scrno),
	                                     WhitePixel(dpy, scrno));
	long wallevents = ButtonPressMask | ButtonReleaseMask | PointerMotionMask;
	XSelectInput (dpy, wallwin, wallevents);

	XSetWindowAttributes wallattr;
	wallattr.do_not_propagate_mask = wallevents;
	XChangeWindowAttributes (dpy, wallwin, CWDontPropagate, &wallattr);


	int dbgwidth = winwidth;
	int dbgheight = scrheight / 3;
	Window dbgwin = XCreateSimpleWindow(dpy,
	                                    rootwin,
	                                    x, y + winheight,
	                                    dbgwidth, dbgheight,
	                                    winborder,
	                                    bluepxl,
	                                    yellowpxl);

	/* There is a trick: if a window (e.g. debug win) does not select an event,
	   by design X will propagate it to the parent window. The parent in the
	   hierarcy that has selected the event type will get its ID assigned
	   to the event's window member. If we do a grab we must see in which window
	   the button was pressed. In case of debug or wall window we should refuse
	   to move or resize or icondify etc these 2.
	 */
	XSelectInput (dpy, dbgwin, wallevents);

	/* MotionNotify events are sent to this client application. Spam. */
	long rootevents = SubstructureNotifyMask;
	XSelectInput (dpy, rootwin, rootevents);


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
		if (fsz < 14 || fsz > 16)
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



	const int menusz = 5;
	std::string smenu[ menusz ] = {"New Xterm",
	                               "Exit",
	                               "Move",
	                               "Resize",
	                               "Raise"};
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
				// hide the menu
				for (int i=0; i < menusz; ++i)
				{
					XUnmapWindow (dpy, menu[i]);
				}

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
				// hide the menu
				for (int i=0; i < menusz; ++i)
				{
					XUnmapWindow (dpy, menu[i]);
				}


				/* There've been a bit of struggle to get this correctly.
				   I must grab the root window!
				   The owner event must be True so we get on every grabbed
				   event the correct window ID where the mouse action happened.
				   We can than decide if to move/resize/iconify/etc the
				   wall+debug windows of the win manager or not.
				*/
				XGrabPointer (dpy,
				              rootwin,        // grab window (must grab root!)
				              True,           // owner events (must be True!)
				              ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
				              GrabModeAsync,  // pointer mode
				              GrabModeAsync,  // keyboard mode
				              None,           // confine the cursor to
				              hand_cursor,
				              CurrentTime);


				{
					/* Announce Grabbed Pointer */
					std::stringstream ss;
					ss << " Btn=" << xbutton->button;
					ss << " Pointer grabbed. ACTION=MOVE started.";
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



				bool actionIsValid = false;
				while (1)
				{
					XNextEvent (dpy, &event);

					{
						std::string info;
						GetEventInfo (&event, info);
						LogText (0,0,0,0,0,0,
						         fnheight,
						         info,
						         dpy,
						         dbgwin,
						         dbggc);
					}

					/* Discard all (motion) events until next ButtonPress. */
					if (event.type != ButtonPress)
						continue;

					xbutton = &(event.xbutton);


					/* Now this is SOMETHING!!
					   When mouse moves over the wall and debug windows their
					   IDs are at xbutton->window.
					   When mouse moves over other windows their IDs are at
					   xbutton->subwindow.
					*/
					if (xbutton->button != 1 ||
					    xbutton->window == wallwin ||
					    xbutton->window == dbgwin)
					{
						std::stringstream ss;
						ss << " Btn=" << xbutton->button;
						ss << " ButtonPress. Cannot move this window.";
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
					actionIsValid = true;
					break;
				}

				if (actionIsValid)
				{
					std::stringstream ss;
					ss << " ACTION=MOVE Calling MoveWindow procedure.";
					LogText (xbutton->window,
					         0,
					         xbutton->subwindow,
					         xbutton->root,
					         xbutton->x_root,
					         xbutton->y_root,
					         fnheight,
					         ss.str(),
					         dpy,
					         dbgwin,
					         dbggc);

					MoveWindow (dpy,
					            scrno,
					            xbutton->subwindow,
					            wallgc,
					            hand_cursor,
					            xbutton->x_root,
					            xbutton->y_root,
					            dbgwin,
					            dbggc,
					            fnheight);
				}

				XUngrabPointer (dpy, CurrentTime);

				{
					/* Announce Ungrab Pointer */
					std::stringstream ss;
					ss << " Btn=" << xbutton->button;
					ss << " Pointer ungrabbed. ACTION=MOVE ended.";
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
			else if (xbutton->window == menu[3]) // Resize
			{
				// hide the menu
				for (int i=0; i < menusz; ++i)
				{
					XUnmapWindow (dpy, menu[i]);
				}

				/* Follow the pattern and comments from MOVE. */
				/* There've been a bit of struggle to get this correctly.
				   I must grab the root window!
				   The owner event must be True so we get on every grabbed
				   event the correct window ID where the mouse action happened.
				   We can than decide if to move/resize/iconify/etc the
				   wall+debug windows of the win manager or not.
				*/
				XGrabPointer (dpy,
				              rootwin,        // grab window (must grab root!)
				              True,           // owner events (must be True!)
				              ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
				              GrabModeAsync,  // pointer mode
				              GrabModeAsync,  // keyboard mode
				              None,           // confine the cursor to
				              hand_cursor,
				              CurrentTime);


				{
					/* Announce Grabbed Pointer */
					std::stringstream ss;
					ss << " Btn=" << xbutton->button;
					ss << " Pointer grabbed. ACTION=RESIZE started.";
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



				bool actionIsValid = false;
				while (1)
				{
					XNextEvent (dpy, &event);

					{
						std::string info;
						GetEventInfo (&event, info);
						LogText (0,0,0,0,0,0,
						         fnheight,
						         info,
						         dpy,
						         dbgwin,
						         dbggc);
					}

					/* Discard all (motion) events until next ButtonPress. */
					if (event.type != ButtonPress)
						continue;

					xbutton = &(event.xbutton);

					/* Follow the pattern and comments from MOVE. */
					/* Now this is SOMETHING!!
					   When mouse moves over the wall and debug windows their
					   IDs are at xbutton->window.
					   When mouse moves over other windows their IDs are at
					   xbutton->subwindow.
					*/
					if (xbutton->button != 1 ||
					    xbutton->window == wallwin ||
					    xbutton->window == dbgwin)
					{
						std::stringstream ss;
						ss << " Btn=" << xbutton->button;
						ss << " ButtonPress. Cannot resize this window.";
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
					actionIsValid = true;
					break;
				}

				if (actionIsValid)
				{
					std::stringstream ss;
					ss << " ACTION=RESIZE Calling ResizeWindow procedure.";
					LogText (xbutton->window,
					         0,
					         xbutton->subwindow,
					         xbutton->root,
					         xbutton->x_root,
					         xbutton->y_root,
					         fnheight,
					         ss.str(),
					         dpy,
					         dbgwin,
					         dbggc);

					ResizeWindow (dpy,
					              scrno,
					              xbutton->subwindow,
					              wallgc,
					              hand_cursor,
					              xbutton->x_root,
					              xbutton->y_root,
					              dbgwin,
					              dbggc,
					              fnheight);
				}

				XUngrabPointer (dpy, CurrentTime);

				{
					/* Announce Ungrab Pointer */
					std::stringstream ss;
					ss << " Btn=" << xbutton->button;
					ss << " Pointer ungrabbed. ACTION=RESIZE ended.";
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
			else if (xbutton->window == menu[4]) // Raise
			{
				// hide the menu
				for (int i=0; i < menusz; ++i)
				{
					XUnmapWindow (dpy, menu[i]);
				}

				/* Follow the pattern and comments from MOVE. */
				/* There've been a bit of struggle to get this correctly.
				   I must grab the root window!
				   The owner event must be True so we get on every grabbed
				   event the correct window ID where the mouse action happened.
				   We can than decide if to move/resize/iconify/etc the
				   wall+debug windows of the win manager or not.
				*/
				XGrabPointer (dpy,
				              rootwin,        // grab window (must grab root!)
				              True,           // owner events (must be True!)
				              ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
				              GrabModeAsync,  // pointer mode
				              GrabModeAsync,  // keyboard mode
				              None,           // confine the cursor to
				              hand_cursor,
				              CurrentTime);


				{
					/* Announce Grabbed Pointer */
					std::stringstream ss;
					ss << " Btn=" << xbutton->button;
					ss << " Pointer grabbed. ACTION=RAISE started.";
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



				bool actionIsValid = false;
				while (1)
				{
					XNextEvent (dpy, &event);

					{
						std::string info;
						GetEventInfo (&event, info);
						LogText (0,0,0,0,0,0,
						         fnheight,
						         info,
						         dpy,
						         dbgwin,
						         dbggc);
					}

					/* Discard all (motion) events until next ButtonPress. */
					if (event.type != ButtonPress)
						continue;

					xbutton = &(event.xbutton);

					/* Follow the pattern and comments from MOVE. */
					/* Now this is SOMETHING!!
					   When mouse moves over the wall and debug windows their
					   IDs are at xbutton->window.
					   When mouse moves over other windows their IDs are at
					   xbutton->subwindow.
					*/
					if (xbutton->button != 1 ||
					    xbutton->window == wallwin ||
					    xbutton->window == dbgwin)
					{
						std::stringstream ss;
						ss << " Btn=" << xbutton->button;
						ss << " ButtonPress. Cannot raise this window.";
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
					actionIsValid = true;
					break;
				}

				if (actionIsValid)
				{
					std::stringstream ss;
					ss << " ACTION=RAISE Calling XRaiseWindow.";
					LogText (xbutton->window,
					         0,
					         xbutton->subwindow,
					         xbutton->root,
					         xbutton->x_root,
					         xbutton->y_root,
					         fnheight,
					         ss.str(),
					         dpy,
					         dbgwin,
					         dbggc);

					XRaiseWindow (dpy, xbutton->subwindow);
				}

				XUngrabPointer (dpy, CurrentTime);

				{
					/* Announce Ungrab Pointer */
					std::stringstream ss;
					ss << " Btn=" << xbutton->button;
					ss << " Pointer ungrabbed. ACTION=RAISE ended.";
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
	ss << std::hex << " R:0x" << root;
	ss << std::hex << " P:0x" << parent;
	ss << std::hex << " W:0x" << window;
	ss << std::hex << " S:0x" << subwindow;
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
	XEvent event;
	while (1)
	{
		XNextEvent (dpy, &event);

		/* In the grabbed events our window
		   has the ID set as xmotion->subwindow.
		*/
		if (event.type == ButtonRelease)
		{
			XButtonEvent* xbutton = &(event.xbutton);
			{
				LogText (xbutton->window,
				         0, // parent
				         xbutton->subwindow,
				         xbutton->root,
				         xbutton->x_root,
				         xbutton->y_root,
				         fnheight,
				         " ButtonRelease",
				         dpy,
				         dbgwin,
				         dbggc);
			}

			break;
		}

		if (event.type == MotionNotify)
		{
			XMotionEvent* xmotion = &(event.xmotion);

			{
				LogText (xmotion->window,
				         0, // parent
				         xmotion->subwindow,
				         xmotion->root,
				         xmotion->x_root,
				         xmotion->y_root,
				         fnheight,
				         " MotionNotify",
				         dpy,
				         dbgwin,
				         dbggc);
			}

			/* No matter if the events are comming with different
			   windows ID, we keep the motion going until a release occurs.
			   The only thing that matters here are the pointer coordinates.
			*/
			XMoveWindow(dpy,
			            win,
			            xmotion->x_root,
			            xmotion->y_root);
		}
	}
}


void ResizeWindow (Display* dpy,          // default display
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
	/* Get the attributes of the window in cause. */
	XWindowAttributes winattr;
	XGetWindowAttributes (dpy, win, &winattr);


	XEvent event;
	while (1)
	{
		XNextEvent (dpy, &event);

		/* In the grabbed events our window
		   has the ID set as xmotion->subwindow.
		*/
		if (event.type == ButtonRelease)
		{
			XButtonEvent* xbutton = &(event.xbutton);
			{
				LogText (xbutton->window,
				         0, // parent
				         xbutton->subwindow,
				         xbutton->root,
				         xbutton->x_root,
				         xbutton->y_root,
				         fnheight,
				         " ButtonRelease",
				         dpy,
				         dbgwin,
				         dbggc);
			}

			break;
		}

		if (event.type == MotionNotify)
		{
			XMotionEvent* xmotion = &(event.xmotion);

			{
				LogText (xmotion->window,
				         0, // parent
				         xmotion->subwindow,
				         xmotion->root,
				         xmotion->x_root,
				         xmotion->y_root,
				         fnheight,
				         " MotionNotify",
				         dpy,
				         dbgwin,
				         dbggc);
			}

			/* No matter if the events are comming with different
			   windows ID, we keep the motion going until a release occurs.
			   The only thing that matters here are the pointer coordinates.
			*/
			if (xmotion->x_root < winattr.x + 100 ||
			    xmotion->y_root < winattr.y + 100)
				continue;

			int width = xmotion->x_root - winattr.x;
			int height = xmotion->y_root - winattr.y;

			XMoveResizeWindow (dpy,
			                   win,
			                   winattr.x,
			                   winattr.y,
			                   width,
			                   height);
		}
	}
}

void GetEventInfo (XEvent* event, std::string& info)
{
	switch (event->type)
	{
	case KeyPress: info="KeyPress"; break;
	case KeyRelease: info = "KeyRelease"; break;
	case ButtonPress:
	{
		std::stringstream ss;
		ss << " ButtonPress Btn=" << event->xbutton.button;
		ss << std::hex << " R:0x" << event->xbutton.root;
		ss << std::hex << " P:0x" << 0;
		ss << std::hex << " W:0x" << event->xbutton.window;
		ss << std::hex << " S:0x" << event->xbutton.subwindow;
		info = ss.str();
	}
	break;
	case ButtonRelease:
	{
		std::stringstream ss;
		ss << " ButtonRelease Btn=" << event->xbutton.button;
		ss << std::hex << " R:0x" << event->xbutton.root;
		ss << std::hex << " P:0x" << 0;
		ss << std::hex << " W:0x" << event->xbutton.window;
		ss << std::hex << " S:0x" << event->xbutton.subwindow;
		info = ss.str();
	}
	break;
	case MotionNotify:
	{
		std::stringstream ss;
		ss << " MotionNotify ";
		ss << std::hex << " R:0x" << event->xmotion.root;
		ss << std::hex << " P:0x" << 0;
		ss << std::hex << " W:0x" << event->xmotion.window;
		ss << std::hex << " S:0x" << event->xmotion.subwindow;
		info = ss.str();
	}
	break;
	case EnterNotify: info = "EnterNotify"; break;
	case LeaveNotify: info = "LeaveNotify"; break;
	case FocusIn: info = "FocusIn"; break;
	case FocusOut: info = "FocusOut"; break;
	case KeymapNotify: info = "KeymapNotify"; break;
	case Expose: info = "Expose"; break;
	case GraphicsExpose: info = "GraphicsExpose"; break;
	case NoExpose: info = "NoExpose"; break;
	case VisibilityNotify: info = "VisibilityNotify"; break;
	case CreateNotify: info = "CreateNotify"; break;
	case DestroyNotify: info = "DestroyNotify"; break;
	case UnmapNotify: info = "UnmapNotify"; break;
	case MapNotify: info = "MapNotify"; break;
	case MapRequest: info = "MapRequest"; break;
	case ReparentNotify: info = "ReparentNotify"; break;
	case ConfigureNotify: info = "ConfigureNotify"; break;
	case ConfigureRequest: info = "ConfigureRequest"; break;
	case GravityNotify: info = "GravityNotify"; break;
	case ResizeRequest: info = "ResizeRequest"; break;
	case CirculateNotify: info = "CirculateNotify"; break;
	case CirculateRequest: info = "CirculateRequest"; break;
	case PropertyNotify: info = "PropertyNotify"; break;
	case SelectionClear: info = "SelectionClear"; break;
	case SelectionRequest: info = "SelectionRequest"; break;
	case SelectionNotify: info = "SelectionNotify"; break;
	case ColormapNotify: info = "ColormapNotify"; break;
	case ClientMessage: info = "ClientMessage"; break;
	case MappingNotify: info = "MappingNotify"; break;
	case GenericEvent: info = "GenericEvent"; break;
	default: info = "Default"; break;
	}
}
