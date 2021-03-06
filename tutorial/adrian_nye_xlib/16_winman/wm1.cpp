/*
  Copyright 1989 O'Reilly and Associates, Inc.

  The X Consortium, and any party obtaining a copy of these files from
  the X Consortium, directly or indirectly, is granted, free of charge, a
  full and unrestricted irrevocable, world-wide, paid up, royalty-free,
  nonexclusive right and license to deal in this software and
  documentation files (the "Software"), including without limitation the
  rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons who receive
  copies from any such party to do so.  This license includes without
  limitation a license to do the foregoing actions under any patents of
  the party supplying this software to the X Consortium.
*/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/Xos.h>
#include <X11/cursorfont.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "bitmaps/focus_frame_bi"


static const char* event_names[] =
{
	"",
	"",
	"KeyPress",
	"KeyRelease",
	"ButtonPress",
	"ButtonRelease",
	"MotionNotify",
	"EnterNotify",
	"LeaveNotify",
	"FocusIn",
	"FocusOut",
	"KeymapNotify",
	"Expose",
	"GraphicsExpose",
	"NoExpose",
	"VisibilityNotify",
	"CreateNotify",
	"DestroyNotify",
	"UnmapNotify",
	"MapNotify",
	"MapRequest",
	"ReparentNotify",
	"ConfigureNotify",
	"ConfigureRequest",
	"GravityNotify",
	"ResizeRequest",
	"CirculateNotify",
	"CirculateRequest",
	"PropertyNotify",
	"SelectionClear",
	"SelectionRequest",
	"SelectionNotify",
	"ColormapNotify",
	"ClientMessage",
	"MappingNotify"
};


typedef struct WindowList_t
{
	struct WindowList_t *next;
	Window window;
	Window icon;
	Bool own;
	char *icon_name;
} WindowListRec, *WindowList;

WindowList Icons = NULL;

void paint_pane(Window window, Window panes[], GC ngc, GC rgc, int mode);
int  execute(const char* s);
void move_resize(Window menuwin,Cursor hand_cursor,Bool move_or_resize);
void draw_focus_frame();
Window focus(Window menuwin) ;
void iconify(Window menuwin);
void raise_lower(Window menuwin, Bool raise_or_lower);
void circdn(Window menuwin);
void circup(Window menuwin);
void draw_box(GC gc, int left,int top,int  right, int bottom);
void undraw_box(GC gc, int left,int top, int right, int bottom);
Bool isIcon(Window win, int x, int y, Window* assoc, char* icon_name, Bool makeicon);
Window makeIcon(Window window, int x, int y, char* icon_name_return);
void removeIcon(Window window);
const char* getIconName(Window window);
Window finishIcon(Window window, Window icon, Bool own, char* icon_name);



#define MAX_CHOICE 10
#define DRAW 1
#define ERASE 0
#define RAISE 1
#define LOWER 0
#define MOVE 1
#define RESIZE 0
#define NONE 100
#define NOTDEFINED 0
#define BLACK  1
#define WHITE  0

Window focus_window;
Window inverted_pane = NONE;

static const char *menu_label[] =
{
	"Raise",
	"Lower",
	"Move",
	"Resize",
	"CirculateDn",
	"CirculateUp",
	"(De)Iconify",
	"Kybrd Focus",
	"New Xterm",
	"Exit",
};


Display *dpy;
int screen_num;
XFontStruct *font_info;
char icon_name[50];


int main(int argc, char** argv)
{
    Window menuwin;
    Window panes[MAX_CHOICE];
    int menu_width, menu_height, x = 0, y = 0, border_width = 4;
    int winindex;
    int cursor_shape;
    Cursor cursor, hand_cursor;
    const char *font_name = "9x15";
    int direction, ascent, descent;
    int char_count;
    const char *string;
    XCharStruct overall;
    Bool owner_events;
    int pointer_mode;
    int keyboard_mode;
    Window confine_to;
    GC gc, rgc;
    int pane_height;
    Window assoc_win;
    XEvent event;
    unsigned int button;


    dpy = XOpenDisplay(NULL);
    if (dpy == NULL)
    {
	    printf("\nCannot connect to X server %s\n", XDisplayName(NULL));
	    exit(-1);
    }

    screen_num = DefaultScreen(dpy);

    /* Access font */
    font_info = XLoadQueryFont(dpy,font_name);

    if (font_info == NULL)
    {
        printf("\nCannot open font %s\n", font_name);
        exit(-1);
    }

    string = menu_label[6];
    char_count = strlen(string);

    /* determine the extent of each menu pane based
     * on the font size */
    XTextExtents(font_info,
                 string,
                 char_count,
                 &direction,
                 &ascent,
                 &descent,
                 &overall);

    menu_width = overall.width + 4;
    pane_height = overall.ascent + overall.descent + 4;
    menu_height = pane_height * MAX_CHOICE;

    /* place the window in upper right corner*/
    x = DisplayWidth(dpy,screen_num) - menu_width - (2*border_width);
    y = 0;   /* appears at top */

    /* create opaque window */
    menuwin = XCreateSimpleWindow(dpy,
                                  RootWindow(dpy, screen_num),
                                  x,
                                  y,
                                  menu_width,
                                  menu_height,
                                  border_width,
                                  BlackPixel(dpy,screen_num),
                                  WhitePixel(dpy,screen_num));

    /* create the choice windows for the text */
    for (winindex = 0; winindex < MAX_CHOICE; winindex++)
    {
	    panes[winindex] = XCreateSimpleWindow(dpy,
	                                          menuwin,
	                                          0,
	                                          menu_height / MAX_CHOICE * winindex,
	                                          menu_width,
	                                          pane_height,
	                                          border_width = 1,
	                                          BlackPixel(dpy,screen_num),
	                                          WhitePixel(dpy,screen_num));

	    XSelectInput(dpy,
	                 panes[winindex],
	                 ButtonPressMask | ButtonReleaseMask | ExposureMask);
    }

    XSelectInput (dpy,
                  RootWindow(dpy, screen_num),
                  SubstructureNotifyMask);

    /* these don't appear until parent (menuwin) is mapped */
    XMapSubwindows(dpy,menuwin);

    /* create the cursor for the menu */
    cursor = XCreateFontCursor(dpy, XC_left_ptr);
    hand_cursor = XCreateFontCursor(dpy, XC_hand2);

    XDefineCursor(dpy, menuwin, cursor);

    focus_window = RootWindow(dpy, screen_num);

    /* Create two Graphics Contexts for inverting panes (white on
     * black).  We invert the panes by changing the background
     * pixel, clearing the window, and using the GC with the
     * contrasting color to redraw the text.  Another way is
     * using XCopyArea.  The default is to generate GraphicsExpose
     * and NoExpose events to indicate whether the source area
     * was obscured.  Since the logical function is GXinvert
     * the destination is also the source.   Therefore if other
     * windows are obscuring parts of the exposed pane, the
     * wrong area will be inverted.  Therefore we would need to
     * handle GraphicsExpose and NoExpose events.  We'll do it the
     * easier way. */

    gc = XCreateGC(dpy,
                   RootWindow(dpy, screen_num),
                   0,
                   NULL);

    XSetForeground(dpy,
                   gc,
                   BlackPixel(dpy, screen_num));

    rgc = XCreateGC(dpy,
                    RootWindow(dpy, screen_num),
                    0,
                    NULL);

    XSetForeground(dpy,
                   rgc,
                   WhitePixel(dpy, screen_num));

    /* map the menu window (and its subwindows) to the screen_num */
    XMapWindow(dpy, menuwin);

    /* Force child processes to disinherit the TCP file descriptor.
      * This helps the shell command (creating new xterm) forked and
     * exec'ed from the menu to work properly.  */
    if ((fcntl(ConnectionNumber(dpy), F_SETFD, 1)) == -1)
        printf("\nChild cannot disinherit TCP fd");

    /* loop getting events on the menu window and icons */
    while (1)
    {
	    /* wait for an event */
	    XNextEvent(dpy, &event);

	    /* if expose, draw text in pane if it is pane */
        switch (event.type)
        {
        case Expose:
        {
	        if (isIcon(event.xexpose.window,
	                   event.xexpose.x,
	                   event.xexpose.y,
	                   &assoc_win,
	                   icon_name,
	                   False))
	        {
		        XDrawString(dpy,
		                    event.xexpose.window,
		                    gc,
		                    2,
		                    ascent + 2,
		                    icon_name,
		                    strlen(icon_name));
	        }
            else /* it's a pane, might be inverted */
            {
	            if (inverted_pane == event.xexpose.window)
	            {
		            paint_pane(event.xexpose.window,
		                       panes,
		                       gc,
		                       rgc,
		                       BLACK);
	            }
	            else
	            {
	                paint_pane(event.xexpose.window,
	                           panes,
	                           gc,
	                           rgc,
	                           WHITE);
	            }
            }
        } // Expose
        break;
        case ButtonPress:
        {
            paint_pane(event.xbutton.window,
                       panes,
                       gc,
                       rgc,
                       BLACK);

            button = event.xbutton.button;
            inverted_pane = event.xbutton.window;

            /* get the matching ButtonRelease on same button */
            while (1)
            {
                /* get rid of other presses */
                while (XCheckTypedEvent(dpy,
                                        ButtonPress,
                                        &event))
                    ;
                /* wait for release; if on correct button exit */
                XMaskEvent(dpy,
                           ButtonReleaseMask,
                           &event);

                if (event.xbutton.button == button)
                {
                    /* get rid of other releases */
                    while (XCheckTypedEvent(dpy,
                                            ButtonRelease,
                                            &event))
                        ;
                    break;
                }
            }

            /* all events are sent to the grabbing
             * window regardless of
             * whether this is True or False.
             * owner_events only affects the distribution of
             * events when the pointer is within this
             * application's windows. */
            owner_events = True;

            /* we don't want pointer or keyboard events
             * frozen in the server */
            pointer_mode = GrabModeAsync;
            keyboard_mode = GrabModeAsync;

            /* we don't want to confine the cursor */
            confine_to = None;
            XGrabPointer(dpy,
                         menuwin,
                         owner_events,
                         ButtonPressMask | ButtonReleaseMask,
                         pointer_mode,
                         keyboard_mode,
                         confine_to,
                         hand_cursor,
                         CurrentTime);


            /* if press and release occured in same window,
             * do command, if not, do nothing */
            if (inverted_pane == event.xbutton.window)
            {
                /* convert window ID to
                 * window array index  */
                for (winindex = 0; inverted_pane != panes[winindex]; winindex++) 
                    ;
                switch (winindex)
                {
                case 0:
                    raise_lower(menuwin, RAISE);
                    break;
                case 1:
                    raise_lower(menuwin, LOWER);
                    break;
                case 2:
                    move_resize(menuwin, hand_cursor, MOVE);
                    break;
                case 3:
                    move_resize(menuwin, hand_cursor, RESIZE);
                    break;
                case 4:
                    circup(menuwin);
                    break;
                case 5:
                    circdn(menuwin);
                    break;
                case 6:
                    iconify(menuwin);
                    break;
                case 7:
                    focus_window = focus(menuwin);
                    break;
                case 8:
                    execute("xterm&");
                    break;

                case 9: /* exit */
                    XSetInputFocus(dpy,
                                   RootWindow(dpy,screen_num),
                                   RevertToPointerRoot,
                                   CurrentTime);

                    /* turn all icons back into windows */
                    /* must clear focus highlights */
                    XClearWindow(dpy,
                                 RootWindow(dpy, screen_num));

                    /* need to change focus border
                     * width back here */

                    XFlush(dpy);
                    XCloseDisplay(dpy);
                    exit(1);

                default:
                    printf("\nSomething went wrong\n");
                    break;
                } /* end switch */
            } /* end if */

            /* Invert Back Here (logical function is invert) */
            paint_pane(event.xexpose.window,
                       panes,
                       gc,
                       rgc,
                       WHITE);

            inverted_pane = NONE;
            draw_focus_frame();
            XUngrabPointer(dpy, CurrentTime);
            XFlush(dpy);
        }
        break;
        case DestroyNotify:
        {
            /* window we have iconified has died, remove its icon.
             * Don't need to remove window from save set
             * because that is done automatically */
            removeIcon(event.xdestroywindow.window);
        }
        break;
        case CirculateNotify:
        case ConfigureNotify:
        case UnmapNotify:
            /* all these uncover areas of screen_num */
            draw_focus_frame();
            break;
        case CreateNotify:
        case GravityNotify:
        case MapNotify:
        case ReparentNotify:
            /* don't need these but get them anyway
             * since we need DestroyNotify and UnmapNotify
             */
            break;
        case ButtonRelease:
            /* throw these way, they are spurious here */
            break;
        case MotionNotify:
            /* throw these way, they are spurious here */
            break;
        default:
            printf("\nGot unexpected %s event.\n", event_names[event.type]);
        } /* end switch */
    } /* end menu loop (while) */

    return 0;
} /* end main */


void paint_pane(Window window, Window panes[], GC ngc, GC rgc, int mode)
{
    int win;
    int x = 2, y;
    GC gc;

    if (mode == BLACK)
    {
        XSetWindowBackground(dpy,
                             window,
                             BlackPixel(dpy, screen_num));
        gc = rgc;
    }
    else
    {
        XSetWindowBackground(dpy,
                             window,
                             WhitePixel(dpy, screen_num));
        gc = ngc;
    }

    /* clearing repaints the background */
    XClearWindow(dpy, window);

    /* find out index of window for label text */
    for (win = 0; window != panes[win]; win++)
        ;

    y = font_info->max_bounds.ascent;

    /* the string length is necessary because strings for
        XDrawString may not be NULL terminated */
    XDrawString(dpy,
                window,
                gc,
                x,
                y,
                menu_label[win],
                strlen( menu_label[win])); 
}

void circup(Window menuwin)
{
	XCirculateSubwindowsUp(dpy, RootWindow(dpy,screen_num));
	XRaiseWindow(dpy, menuwin);
}

void circdn(Window menuwin)
{
	XCirculateSubwindowsDown(dpy, RootWindow(dpy,screen_num));
	XRaiseWindow(dpy, menuwin);
}

void raise_lower(Window menuwin, Bool raise_or_lower)
{
    XEvent report;
    int root_x,root_y;
    Window child, root;
    int win_x, win_y;
    unsigned int mask;
    unsigned int button;

    /* wait for ButtonPress, find out which subwindow of root */
    XMaskEvent(dpy, ButtonPressMask, &report); 
    button = report.xbutton.button;
    XQueryPointer(dpy,
                  RootWindow(dpy,screen_num),
                  &root,
                  &child,
                  &root_x,
                  &root_y,
                  &win_x,
                  &win_y,
                  &mask);

    /* if not RootWindow, raise */
    if (child != (Window)NULL)
    {
        if (raise_or_lower == RAISE)
            XRaiseWindow(dpy, child);
        else
            XLowerWindow(dpy, child);

        /* make sure window manager can never be obscured */
        XRaiseWindow(dpy, menuwin);
    }

    /* wait for ButtonRelease before exiting */
    /* get the matching ButtonRelease on same button */
    while (1)
    {
        XMaskEvent(dpy,
                   ButtonReleaseMask,
                   &report);

        if (report.xbutton.button == button)
            break;
    }

    /* throw out any remaining events so we start fresh */
    while (XCheckMaskEvent(dpy,
                           ButtonReleaseMask | ButtonPressMask,
                           &report))
        ;
}

void iconify(Window menuwin)
{
    XEvent report;
    extern Window focus_window;
    Window assoc_win;
    int press_x,press_y;
    Window child;
    Window root;
    int win_x, win_y;
    unsigned int mask;
    unsigned int button;

    /* wait for ButtonPress, any win */
    XMaskEvent(dpy, ButtonPressMask, &report);
    button = report.xbutton.button;

    /* find out which subwindow the mouse was in */
    XQueryPointer(dpy,
                  RootWindow(dpy,screen_num),
                  &root,
                  &child,
                  &press_x,
                  &press_y,
                  &win_x,
                  &win_y,
                  &mask);

    /* Can't iconify rootwindow or menu window */
    if ((child == (Window)NULL) || (child == menuwin))
    {
        /* wait for ButtonRelease before exiting */
        while (1)
        {
            XMaskEvent(dpy,
                       ButtonReleaseMask,
                       &report);

            if (report.xbutton.button == button)
                break;
        }
        return;
    }

    /* returned value of isIcon not used here, but it is elsewhere in the code */
    isIcon(child, press_x, press_y, &assoc_win, icon_name, True);

    /* window selected is unmapped, whether it is icon
     * or main window.  Associated window is then mapped. */
    XUnmapWindow(dpy, child);
    XMapWindow(dpy, assoc_win);

    /* wait for ButtonRelease before exiting */
    /* get the matching ButtonRelease on same button */
    while (1)
    {
        XMaskEvent(dpy,
                   ButtonReleaseMask,
                   &report);

        if (report.xbutton.button == button)
            break;
    }

    /* throw out any remaining events so we start fresh for next op */
    while (XCheckMaskEvent(dpy,
                           ButtonReleaseMask | ButtonPressMask,
                           &report))
        ;
}

Window focus(Window menuwin)
{
    XEvent report;
    int x,y;
    Window child;
    Window root;
    Window assoc_win;
    extern Window focus_window;
    int win_x, win_y;
    unsigned int mask;
    unsigned int button;
    XWindowAttributes win_attr;
    static int old_width;
    static Window old_focus;
    int status;


    /* wait for ButtonPress, any win */
    XMaskEvent(dpy, ButtonPressMask, &report);
    button = report.xbutton.button;


    /* find out which subwindow the mouse was in */
    XQueryPointer(dpy,
                  RootWindow(dpy,screen_num),
                  &root,
                  &child,
                  &x,
                  &y,
                  &win_x,
                  &win_y,
                  &mask);


    if ((child == menuwin) ||
        (child == (Window)NULL) ||
        (isIcon(child, x, y, &assoc_win, icon_name, True)))
    {
        focus_window = RootWindow(dpy, screen_num);
    }
    else
    {
        focus_window = child;
    }

    if (focus_window != old_focus) /* if focus changed */
    {
        /* if not first time set, set border back */
	    if  (old_focus != (Window)NULL)
            XSetWindowBorderWidth(dpy, old_focus, old_width);

        XSetInputFocus(dpy,
                       focus_window,
                       RevertToPointerRoot,
                       CurrentTime);

        if (focus_window != RootWindow(dpy, screen_num))
        {
            /* get current border width and add one */
            if (!(status = XGetWindowAttributes(dpy, focus_window, &win_attr)))
                printf("\nCan't get attributes for focus window\n");

            XSetWindowBorderWidth(dpy,
                                  focus_window,
                                  win_attr.border_width + 1);

            /* keep record so we can change it back */
            old_width = win_attr.border_width;
        }
    }

    /* get the matching ButtonRelease on same button */
    while (1)
    {
        XMaskEvent(dpy, ButtonReleaseMask, &report);
        if (report.xbutton.button == button)
            break;
    }

    /* throw out any remaining events so we start fresh for next op */
    while (XCheckMaskEvent(dpy,
                           ButtonReleaseMask | ButtonPressMask,
                           &report))
        ;

    old_focus = focus_window;
    return(focus_window);
}

void draw_focus_frame()
{
    XWindowAttributes win_attr;
    int frame_width = 4;
    Pixmap focus_tile;
    GC gc;
    int foreground = BlackPixel(dpy, screen_num);
    int background = WhitePixel(dpy, screen_num);
    extern Window focus_window;
    Bool first_time = True;

    if (first_time)
    {
        /* make Bitmap from bitmap data */
        focus_tile = XCreatePixmapFromBitmapData(dpy,
                                                 RootWindow(dpy,screen_num),
                                                 focus_frame_bi_bits,
                                                 focus_frame_bi_width,
                                                 focus_frame_bi_height,
                                                 foreground,
                                                 background,
                                                 DefaultDepth(dpy, screen_num));

        /* Create Graphics Context */
        gc = XCreateGC(dpy, RootWindow(dpy,screen_num), 0, NULL);
        XSetFillStyle(dpy, gc, FillTiled);
        XSetTile(dpy, gc, focus_tile);
        first_time = False;
    }

    /* get rid of old frames */
    XClearWindow(dpy, RootWindow(dpy,screen_num));

    /* if focus is RootWindow, no frame drawn */
    if (focus_window == RootWindow(dpy,screen_num)) return;

    /* get dimensions and position of focus_window*/
    XGetWindowAttributes(dpy, focus_window, &win_attr);

    XFillRectangle(dpy,
                   RootWindow(dpy,screen_num),
                   gc,
                   win_attr.x - frame_width,
                   win_attr.y - frame_width,
                   win_attr.width + 2 * (win_attr.border_width + frame_width),
                   win_attr.height + 2 * (win_attr.border_width + frame_width));
}

void move_resize(Window menuwin,Cursor hand_cursor,Bool move_or_resize)
{
    XEvent report;
    XWindowAttributes win_attr;
    int press_x, press_y, release_x, release_y, move_x, move_y;
    static int box_drawn = False;
    int left, right, top, bottom;
    Window root, child;
    Window win_to_configure;
    int win_x, win_y;
    unsigned int mask;
    unsigned int pressed_button;
    XSizeHints size_hints;
    Bool min_size, increment;
    unsigned int width, height;
    int temp_size;
    static GC gc;
    static int first_time = True;

    if (first_time)
    {
	    gc = XCreateGC(dpy, RootWindow(dpy,screen_num), 0, NULL);
	    XSetSubwindowMode(dpy, gc, IncludeInferiors);
	    XSetForeground(dpy, gc, BlackPixel(dpy, screen_num));
	    XSetFunction(dpy, gc, GXxor);
	    first_time = False;
    }

    /* wait for ButtonPress choosing window to configure */
    XMaskEvent(dpy, ButtonPressMask, &report);
    pressed_button = report.xbutton.button;

    /* which child of root was press in? */
    XQueryPointer(dpy,
                  RootWindow(dpy,screen_num),
                  &root,
                  &child,
                  &press_x,
                  &press_y,
                  &win_x,
                  &win_y,
                  &mask);

    win_to_configure = child;

    if (win_to_configure == (Window)NULL  ||
        (win_to_configure == menuwin && move_or_resize == RESIZE))
    {
        /* if in RootWindow or resizing menuwin get
         * release event and get out */
        while (XCheckMaskEvent(dpy,
                               ButtonReleaseMask | ButtonPressMask,
                               &report))
            ;
        return;
    }

    /* button press was in a valid subwindow of root */

    /* get original position and size of window */
    XGetWindowAttributes(dpy,
                         win_to_configure,
                         &win_attr);

    /* get size hints for the window */
    XGetNormalHints(dpy,
                    win_to_configure,
                    &size_hints);

    if (size_hints.flags && PMinSize)
        min_size = True;

    if (size_hints.flags && PResizeInc)
        increment = True;

     /* now we need pointer motion events. */
    XChangeActivePointerGrab(dpy,
                             PointerMotionHintMask | ButtonMotionMask |
                             ButtonReleaseMask | OwnerGrabButtonMask,
                             hand_cursor,
                             CurrentTime);

    /* don't allow other dpy operations during move,
     * because Xor won't work properly otherwise */
    XGrabServer(dpy);

    /* move outline of window until button release */
    while  (1)
    {
        XNextEvent(dpy, &report);
        switch (report.type)
        {
            case ButtonRelease:
            {
                 if (report.xbutton.button == pressed_button) {
                    if (box_drawn)
                        undraw_box(gc, left, top, right, bottom);

                    XUngrabServer(dpy);

                    /* get final window position */
                    XQueryPointer(dpy,
                                  RootWindow(dpy,screen_num),
                                  &root,
                                  &child, &release_x,
                                  &release_y,
                                  &win_x,
                                  &win_y,
                                  &mask);

                    /* move or resize window */
                    if (move_or_resize == MOVE)
	                    XMoveWindow(dpy,
	                                win_to_configure,
	                                win_attr.x + (release_x - press_x),
	                                win_attr.y + (release_y - press_y));
                    else
	                    XResizeWindow(dpy,
	                                  win_to_configure,
	                                  right - left,
	                                  bottom - top);

                    XRaiseWindow(dpy, win_to_configure);
                    XFlush(dpy);
                    box_drawn = False;
                    while (XCheckMaskEvent(dpy,
                                           ButtonReleaseMask | ButtonPressMask,
                                           &report))
	                    ;
                    return;
                }
            }
            break;

            case MotionNotify:
            {
                if (box_drawn == True)
                    undraw_box(gc, left, top, right, bottom);

                /* can get rid of all MotionNotify events in queue,
                 * since otherwise the round-trip  delays caused by
                 * XQueryPointer may cause a backlog
                 * of MotionNotify events, which will cause additional
                * wasted XQueryPointer calls. */
                while (XCheckTypedEvent(dpy,
                                        MotionNotify,
                                        &report));

                /* get current mouse position */
                XQueryPointer(dpy,
                              RootWindow(dpy,screen_num),
                              &root,
                              &child,
                              &move_x,
                              &move_y,
                              &win_x,
                              &win_y,
                              &mask);

                if (move_or_resize == MOVE)
                {
	                left = move_x - press_x + win_attr.x;
	                top = move_y - press_y + win_attr.y;
	                right = left + win_attr.width;
	                bottom = top + win_attr.height;
                }
                else
                {
	                if (move_x < win_attr.x) move_x = 0;
	                if (move_y < win_attr.y ) move_y = 0;
	                left = win_attr.x;
	                top = win_attr.y;
	                right = left + win_attr.width + move_x - press_x;
                           bottom = top + win_attr.height + move_y - press_y;

                    /* must adjust size according to size hints */
                    /* enforce minimum dimensions */
                    width = right - left;
                    height = bottom - top;

                    /* make sure dimension are increment of
                     * width_inc and height_inc and at least
                     * min_width and min_height */
                    for (temp_size = size_hints.min_width;
                         temp_size < width;
                         temp_size += size_hints.width_inc)
                        ;

                    for (temp_size = size_hints.min_height;
                         temp_size < height;
                         temp_size += size_hints.height_inc)
	                    ;

                    /* most applications (xterm inc.)
                     * pad their right and bottom
                     * dimensions by 2 pixels */
                    right = left + temp_size + 2;
                    bottom = top + temp_size + 2;
                }

                draw_box(gc, left, top, right, bottom);
                box_drawn = True;
            }
            break;
            default:
            {
                /* StructureNotify events shouldn't appear here,
                 * because of the ChangeActivePointerGrab
                 * call, but they do for some reason. */
                /* Anyway, it doesn't matter */
                printf("\nUnexpected event type %s\n", report.type);
            }
        } /* end switch */
    } /* end outer while */
} /* end move */

#ifdef SYSV
#ifndef hpux
#define vfork() fork()
#endif /* hpux */
#endif /* SYSV */



/* the following procedure is a copy of the implementation of
 * system, modified to reset the handling of SIGINT, SIGQUIT,
 * and SIGHUP before exec-ing */
int execute(const char* s)
{
    int status, pid, w;
    // register int (*istat)(), (*qstat)();
    void (*istat)(int);
    void (*qstat)(int);

    if ((pid = vfork()) == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        signal(SIGHUP, SIG_DFL);
        execl("/bin/sh", "sh", "-c", s, 0);
        _exit(127);
    }

    istat = signal(SIGINT, SIG_IGN);
    qstat = signal(SIGQUIT, SIG_IGN);

    while ((w = ::wait(&status)) != pid && w != -1)
        ;
    if (w == -1)
        status = -1;
    signal(SIGINT, istat);
    signal(SIGQUIT, qstat);
    return(status);
}


void undraw_box(GC gc, int left,int top, int right, int bottom)
{
	draw_box(gc, left,top,right,bottom);
}

void draw_box(GC gc, int left,int top,int  right, int bottom)
{

	XSetForeground(dpy,
	               gc,
	               WhitePixel(dpy, screen_num) ^ BlackPixel(dpy, screen_num));

	XDrawRectangle(dpy,
	               RootWindow(dpy,screen_num),
	               gc,
	               left,
	               top,
	               right - left,
	               bottom - top);
}


Bool isIcon(Window win, int x, int y, Window* assoc, char* icon_name, Bool makeicon)
{
	WindowList win_list;
//	Window makeIcon();

    /* go through linked list of window-icon structures */
    for (win_list = Icons; win_list; win_list = win_list->next)
    {
	    if (win == win_list->icon)
	    { /* win is icon */
		    *assoc = win_list->window;
		    strcpy(icon_name, win_list->icon_name);
		    return(True);
	    }

	    if (win == win_list->window)
	    { /* win is main window */
		    *assoc = win_list->icon;
		    strcpy(icon_name, win_list->icon_name);
		    return(False);
	    }
    }

    /* window not in list means icon not created yet.
     * Create icon and add main window to save set
     * in case window manager dies */
    if (makeicon)
    {
	    *assoc = makeIcon(win, x, y, icon_name);
	    XAddToSaveSet(dpy, win);
    }
    return(False);
}


/* NOT NECESSARY DUE TO SAVE SET
this is called when the window manager exits gracefully 
 * to turn all icons back into windows
clearIcons()
{
	WindowList win_list;


	go through linked list of window-icon structures 
	for (win_list = Icons; win_list; win_list = win_list->next) {
		XUnmapWindow(dpy, win_list->icon);
		XMapWindow(dpy, win_list->window);
	}
}
*/

void removeIcon(Window window)
{
	WindowList win_list, win_list1;

	for (win_list = Icons; win_list; win_list = win_list->next)
	{
		if (win_list->window == window)
		{
			if (win_list->own)
				XDestroyWindow(dpy, win_list->icon);
			break;
		}
	}

	if (win_list)
	{
		if (win_list==Icons) Icons = Icons->next;
		else
		{
			for (win_list1 = Icons;
			     win_list1->next;
			     win_list1 = win_list1->next)
			{
				if (win_list1->next == win_list)
				{
					win_list1->next = win_list->next;
					break;
				}
			}
		}
	}
}

const char* getIconName(Window window)
{
    char *name;
    if (XGetIconName( dpy, window, &name ))
	    return name;
    if (XFetchName( dpy, window, &name ))
	    return name;
    return "Icon";
}

const char* getDefaultIconSize(Window window, int* icon_w, int* icon_h)
{
	/* Determine the size of the icon window.  */
	const char *icon_name;

	icon_name = getIconName(window);

	*icon_h = font_info->ascent + font_info->descent + 4;
	*icon_w = XTextWidth(font_info,
	                     icon_name,
	                     strlen(icon_name));

	return icon_name;
}


Window makeIcon(Window window, int x, int y, char* icon_name_return)
{
	int icon_x, icon_y;	/* Icon U. L. X and Y coordinates. */
	int icon_w, icon_h;	/* Icon width and height. */
	int icon_bdr;	/* Icon border width. */
	int depth;	/* for XGetGeometry */
	Window root;	/* for XGetGeometry */
	XSetWindowAttributes icon_attrib;	/* for icon creation */
	unsigned long icon_attrib_mask;
	XWMHints *wmhints;	/* see if icon position provided */
//	XWMHints *XGetWMHints();
//	Window finishIcon();
	const char *icon_name;

	/*
	* Process window manager hints.
	* If icon window hint exists, use it directly
	* If icon pixmap hint exists, get its size
	* otherwise, get default size.
	* If icon position hint exists, use it
	* otherwise, use the position passed (current mouse position)
	*/
	if (wmhints = XGetWMHints(dpy, window))
	{
		if (wmhints->flags & IconWindowHint)
		{
			/* icon window was passed; use it as is */
			return finishIcon(window,
			                  wmhints->icon_window,
			                  False,
			                  (char*)icon_name);
		}
		else if (wmhints->flags&IconPixmapHint)
		{
			/* Pixmap was passed.
			   Determine size of icon
			   Window from pixmap. Only
			   icon_w and icon_h are significant.
			*/
			if (!XGetGeometry(dpy,
			                  wmhints->icon_pixmap,
			                  &root,
			                  &icon_x,
			                  &icon_y,
			                  (unsigned int*)&icon_w,
			                  (unsigned int*)&icon_h,
			                  (unsigned int*)&icon_bdr,
			                  (unsigned int*)&depth))
			{
				printf("\nClient passed invalid icon pixmap." );
				return (Window) NULL;
			}
			else
			{
				icon_attrib.background_pixmap = wmhints->icon_pixmap;
				icon_attrib_mask = CWBorderPixel | CWBackPixmap;
			}
		}
		/* else no window or pixmap passed */
		else
		{
			icon_name = getDefaultIconSize(window, &icon_w, &icon_h);
			icon_attrib_mask = CWBorderPixel | CWBackPixel;
			icon_attrib.background_pixel =
				(unsigned long) WhitePixel(dpy,screen_num);
		}
	}
	/* else no hints at all exist */
	else
	{
		icon_name = getDefaultIconSize(window, &icon_w, &icon_h);
		icon_attrib_mask = CWBorderPixel | CWBackPixel;
	}
	/* Pad sizes. */
	icon_w += 2;
	icon_h += 2;

	strcpy(icon_name_return, icon_name);

	/* Set the icon border attributes.  */
	icon_bdr = 2;
	icon_attrib.border_pixel =
		(unsigned long) BlackPixel(dpy,screen_num);


	/* If icon position hint exists, get it.
	   This also checks to see if wmhints is NULL,
	   which it will be if WMHints were never set at all
	*/
	if (wmhints && (wmhints->flags&IconPositionHint))
	{
		icon_x = wmhints->icon_x;
		icon_y = wmhints->icon_y;
	}
	else
	{
		/* put it where the mouse was */
		icon_x = x;
		icon_y = y;
	}

	/* Create the icon window.  */
	return  finishIcon(window,
	                   XCreateWindow(dpy,
	                                 RootWindow(dpy, screen_num),
	                                 icon_x,
	                                 icon_y,
	                                 icon_w,
	                                 icon_h,
	                                 icon_bdr,
	                                 0,
	                                 CopyFromParent,
	                                 CopyFromParent,
	                                 icon_attrib_mask,
	                                 &icon_attrib),
	                   True,
	                   (char*)icon_name);
}


Window finishIcon(Window window, Window icon, Bool own, char* icon_name)
{
	WindowList win_list;
	Cursor ManCursor;


	/* if icon window didn't get created, return failure */
	if (icon == (Window) NULL)
		return (Window)NULL;

	/* Use the man cursor whenever the mouse is in the icon window. */
	ManCursor = XCreateFontCursor(dpy, XC_man);
	XDefineCursor(dpy, icon, ManCursor);

	 /* Select events for the icon window */
	XSelectInput(dpy, icon, ExposureMask);

	/* Set the event window's icon window to be the new icon window. */
	win_list = (WindowList) malloc(sizeof(WindowListRec));
	win_list->window = window;
	win_list->icon = icon;
	win_list->own = own;
	win_list->icon_name = icon_name;
	win_list->next = Icons;
	Icons = win_list;

	return(icon);
}
