/*
 * Copyright 1989 O'Reilly and Associates, Inc.
 * Copyright 1988 Stellar Computer, Inc.
 * See ../Copyright for complete rights and liability information.
 */
/*
 * X Version 11 Integer Programmer's Calculator
 * Written by Alan Greenspan, modified slightly by Adrian Nye.
 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <X11/cursorfont.h>

#include <stdio.h>

#ifdef SysV
#include <termio.h>
#else
#include <sgtty.h>
#include <sys/ttychars.h>
#endif SysV

#include <ctype.h>
#include <pwd.h>

#include "basecalc.h"

/*
 * Programmer's calculator with 
 * number base conversions
 */
main (argc, argv)
int argc;
register char *argv[];
{
    /* so we can use the resource manager data merging functions */
    XrmInitialize();

    /* parse command line first so we can open display, store any
     * options in a database  */
    parseOpenDisp (&argc, argv);

    /* get server defaults, program defaults, .Xdefaults, command 
     * line, etc. and merge them */
    mergeDatabases();

    /* extract values from database for use */
    extractOpts ();

    /* load font, make pixmaps, set up arrays of windows */
    initCalc ();

    /* get keyboard settings for interrupt, delete, etc. */
    initTty ();

    /* make a standard cursor */
    makeCursor ();

    /* set standard properties, create and map windows */
    makeWindows (argc, argv);

    /* get events */
    takeEvents ();

    /* bow out gracefully */
    XCloseDisplay(display);
    exit (1);
}


static char *getHomeDir( dest )
char *dest;
{
    int uid;
    extern char *getenv();
    extern int getuid();
    extern struct passwd *getpwuid();
    struct passwd *pw;
    register char *ptr;

    if ((ptr = getenv("HOME")) != NULL) {
        (void) strcpy(dest, ptr);

    } else {
        if ((ptr = getenv("USER")) != NULL) {
            pw = getpwnam(ptr);
        } else {
            uid = getuid();
            pw = getpwuid(uid);
        }
        if (pw) {
            (void) strcpy(dest, pw->pw_dir);
        } else {
            *dest = '\0';
        }
    }
    return dest;
}


/*
 * Get program's and user's defaults
 */
mergeDatabases()
{
    XrmDatabase homeDB, serverDB, applicationDB;

    char filenamebuf[1024];
    char *filename = &filenamebuf[0];
    char *environment;
    char *classname = "Basecalc";
    char name[255];

    (void) strcpy(name, "/usr/lib/X11/app-defaults/");
    (void) strcat(name, classname);
    /* get application defaults file, if any */
    applicationDB = XrmGetFileDatabase(name);
    (void) XrmMergeDatabases(applicationDB, &rDB);

    /* MERGE server defaults, these are created by xrdb, loaded as a
     * property of the root window when the server initializes, and
     * loaded into the display structure on XOpenDisplay.  If not defined,
         * use .Xdefaults  */
    if (XResourceManagerString(display) != NULL) {
        serverDB = XrmGetStringDatabase(XResourceManagerString(display));
    } else {
        /* Open .Xdefaults file and merge into existing data base */
        (void) getHomeDir(filename);
        (void) strcat(filename, "/.Xdefaults");

        serverDB = XrmGetFileDatabase(filename);
    }
    XrmMergeDatabases(serverDB, &rDB);

    /* Open XENVIRONMENT file, or if not defined, the ~/.Xdefaults,
         * and merge into existing data base */
    if ((environment = getenv("XENVIRONMENT")) == NULL) {
        int len;
        environment = getHomeDir(filename);
        (void) strcat(environment, "/.Xdefaults-");
        len = strlen(environment);
        (void) gethostname(environment + len, 1024 - len);
    }
    homeDB = XrmGetFileDatabase(environment);
    XrmMergeDatabases(homeDB, &rDB);

    /* command line takes precedence over everything */
    XrmMergeDatabases(commandlineDB, &rDB);
}


/*
 * Get command line options
 */
parseOpenDisp (argc, argv)
int *argc;
register char *argv[];
{

    XrmValue value;
    char *str_type[20];

    myDisplayName[0] = '\0';

    XrmParseCommand(&commandlineDB, opTable, opTableEntries,
            argv[0], argc, argv);

    /*
     * Check for any arguments left
     */
    if (*argc != 1) 
        Usage();

    /* get display now, because we need it to get other databases*/
    if (XrmGetResource(commandlineDB, "basecalc.display",
            "Basecalc.Display", str_type, &value) == True) {
        (void) strncpy(myDisplayName, value.addr, (int) value.size);
    }

    /*
     * Open display 
     */
    if (!(display = XOpenDisplay(myDisplayName))) {
        (void) fprintf(stderr, "%s: Can't open display '%s'\n",
                argv[0], XDisplayName(myDisplayName));
        exit(1);
    }

    screen_number = DefaultScreen(display);
    visual = DefaultVisual(display, screen_number);
    colormap = DefaultColormap(display, screen_number);
}


extractOpts()
{
    char *str_type[20];
    char buffer[20];
    long flags;
    XrmValue value;
    int x, y, width, height;
    XColor screen_def;

    /* get geometry (actually, this is currently ignored) */
    if (XrmGetResource(rDB, "basecalc.geometry", "Basecalc.Geometry",
            str_type, &value) == True) {
        (void) strncpy(Geostr, value.addr, (int) value.size);
    } else {
        Geostr[0] = NULL;
    }

    if (XrmGetResource(rDB, "basecalc.iconGeometry", "Basecalc.IconGeometry",
            str_type, &value) == True) {
        (void) strncpy(iconGeostr, value.addr, (int) value.size);
    } else {
        iconGeostr[0] = NULL;
    }

    if (XrmGetResource(rDB, "basecalc.unsigned", "Basecalc.Unsigned",
            str_type, &value) == True)
        if (strncmp(value.addr, "False", (int) value.size) ==
                0) 
            Unsigned = False;


    if (XrmGetResource(rDB, "basecalc.base", "Basecalc.Base",
            str_type, &value) == True) {
        (void) strncpy(buffer, value.addr, (int) value.size);
        buffer[value.size] = NULL;
        Base = atoi(buffer);
    } else 
        Base = 10;

    if (XrmGetResource(rDB, "basecalc.foreground", "Basecalc.Foreground",
            str_type, &value) == True) {
        (void) strncpy(buffer, value.addr, (int) value.size);
        if (XParseColor(display, colormap, buffer,  &screen_def) ==
                0)  {
            (void) fprintf(stderr, "basecalc: fg color specification %s invalid",
                    buffer);
            foreground = BlackPixel(display, screen_number);
        }  else {
            if ((visual->class == StaticGray) || (visual->class ==
                    GrayScale))

                foreground = BlackPixel(display,
                        screen_number);
            else if (XAllocColor(display, colormap,
                    &screen_def) == 0) {
                foreground = BlackPixel(display,
                        screen_number);
                (void) fprintf(stderr, "basecalc: couldn't allocate color: %s.\n",
                        buffer);
            } else
                foreground = screen_def.pixel;
        }
    } else {
        foreground = BlackPixel(display, screen_number);
    }

    if (XrmGetResource(rDB, "basecalc.background", "Basecalc.Background",
            str_type, &value) == True) {
        (void) strncpy(buffer, value.addr, (int) value.size);
        if (XParseColor(display, colormap, buffer,  &screen_def) ==
                0)  {
            (void) fprintf(stderr, "basecalc: bg color specification %s invalid",
                    buffer);
            background = WhitePixel(display, screen_number);
        }  else {
            if ((visual->class == StaticGray) || (visual->class ==
                    GrayScale))
                background = WhitePixel(display,
                        screen_number);
            else if (XAllocColor(display, colormap,
                    &screen_def) == 0) {
                background = WhitePixel(display,
                        screen_number);
                (void) fprintf(stderr, "basecalc: couldn't allocate color: %s.\n",
                        buffer);
            } else
                background = screen_def.pixel;
        }
    } else {
        background = WhitePixel(display, screen_number);
    }

    /* one last check to make sure the colors are different! */
    if (background == foreground) {
        background = WhitePixel(display, screen_number);
        foreground = BlackPixel(display, screen_number);
    }


    /*  Could add a command line option for initial state:
     *    iconOnly[0] = NULL; 
     */

    /*
     * Get window geometry info.
     */
    if (Geostr != NULL) {
        flags = XParseGeometry(Geostr,  &x, &y, &width,
                &height);
        if ((WidthValue | HeightValue) & flags)
            Usage ();
        if (XValue & flags) {
            if (XNegative & flags)
                x = DisplayWidth(display, screen_number) +
                                            x - sizehints.width;
            sizehints.flags |= USPosition;
            sizehints.x = x;
        }
        if (YValue & flags) {
            if (YNegative & flags)
                y = DisplayHeight(display, screen_number) +
                                            x - sizehints.width;
            sizehints.flags |= USPosition;
            sizehints.y = y;
        }
    }

    /*
     * Get icon geometry info.
     */
    if (iconGeostr != NULL) {
        iconGeostr[0] = '=';
        flags = XParseGeometry(iconGeostr,  &x, &y, &width,
                &height);
        if ((WidthValue | HeightValue) & flags)
            Usage ();
        if (XValue & flags) {
            if (XNegative & flags)
                x = DisplayWidth(display, screen_number) +
                                            x - iconsizehints.width;
            iconsizehints.flags |= USPosition;
            wmhints.flags |= IconPositionHint;
            wmhints.icon_x = x;
            iconsizehints.x = x;
        }
        if (YValue & flags) {
            if (YNegative & flags)
                y = DisplayHeight(display, screen_number) +
                                            x - iconsizehints.width;
            iconsizehints.flags |= USPosition;
            wmhints.flags |= IconPositionHint;
            wmhints.icon_y = y;
            iconsizehints.y = y;
        }
    }
}


/*
 * Print message to stderr and exit
 */
Usage ()
{
    (void) fprintf (stderr, "%s: [-iconic] [-unsigned] [-hex|x|dec|oct|binary] [-display <display>] [-geometry <geometrystring>] [-iconGeometry <icongeometrystring>\n",
            calcName ? calcName : "basecalc");
    exit (1);
}


/*
 * Make a pixmap.
 */
Pixmap 
makePixmap(data, width, height)
char *data;
unsigned int width, height;
{
    Pixmap pid;

    pid = XCreatePixmapFromBitmapData(display, DefaultRootWindow(display),
            data, width, height, foreground, background, DefaultDepth(display,
            screen_number));
    return(pid);
}


/*
 * Initialize calculator options
 */
initCalc ()
{
    register int win;
    register int found = -1;
    XGCValues values;
    extern char lgray_bits[];

    if ((theFont = XLoadQueryFont (display, myFontName)) ==
            NULL) {
        (void) fprintf(stderr, "basecalc: can't open font %s\n",
                myFontName);
        exit(-1);
    }

    /*
     * Make the utility pixmaps.
     */
    grayPixmap = makePixmap(gray_bits, gray_width, gray_height);
    lgrayPixmap = makePixmap(lgray_bits, lgray_width, lgray_height);

    /*
     * Make the utility gc's.
     */
    values.font = theFont->fid;
    values.foreground = foreground;
    fgGC = XCreateGC(display, DefaultRootWindow(display),
            GCForeground | GCFont, &values);
    values.foreground = background;
    values.function = GXcopy;
    bgGC = XCreateGC(display, DefaultRootWindow(display),
            GCForeground | GCFont | GCFunction, &values);

    /*
     * Loop through buttons, setting disabled buttons
     * to Color Light Gray. Also, find the window
     * which corresponds to the starting dsplay base.
     * Also add ascent to y position of text.
     */
    for (win = 1; win < NBUTTONS; win++) {
        if (windata[win].type == WTYP_CONV &&  windata[win].value ==
                Base) {
            found = win;
        } else if (windata[win].type == WTYP_DIG &&  windata[win].value >=
                Base) {
            windata[win].color = disabledColor;
        } else if (windata[win].type == WTYP_SPEC && 
                windata[win].value == OPR_UNS) {
            if (Unsigned)
                windata[win].text = "U";
            else
                windata[win].text = "S";
            windata[win].color = pressedColor;
        } else
            windata[win].color = unpressedColor;
        windata[win].y += theFont->max_bounds.ascent;
    }
    windata[0].y += theFont->max_bounds.ascent;
    if (found >= 0) {
        Winbase = found;
        windata[found].color = pressedColor;
    } else {
        (void) fprintf(stderr, "basecalc: can't use base %d\n",
                Base);
        exit(-1);
    }
    windata[0].color = displayColor;
}


/*
 * Get the user's tty special chars
 * This is currently 4.2 specific.
 */
initTty ()
{
    register struct KeyCode *KeyCodePtr;
    register int fd;
#ifdef SysV
    struct termio term;
#else
    struct sgttyb tty;
    struct tchars tchars;
    struct ltchars ltchars;
#endif SysV

    if (!isatty(0)) {
        if ((fd = open ("/dev/console", 0)) < 0)
            return;
    } else
        fd = 0;
#ifdef SysV
    (void) ioctl  (fd, TCGETA,   &term);
#else
    (void) ioctl  (fd, TIOCGETP, &tty);
    (void) ioctl  (fd, TIOCGETC, &tchars);
    (void) ioctl  (fd, TIOCGLTC, &ltchars);
#endif SysV
    if (fd)
        (void) close (fd);

    KeyCodePtr = KeyCodes;
#ifdef SysV
    KeyCodePtr++->kc_char = term.c_cc[VERASE];
    KeyCodePtr++;
    KeyCodePtr++->kc_char = term.c_cc[VKILL];
    KeyCodePtr->kc_char = term.c_cc[VINTR];
    QuitChar = term.c_cc[VQUIT];
#else
    KeyCodePtr++->kc_char = tty.sg_erase;
    KeyCodePtr++->kc_char = ltchars.t_werasc;
    KeyCodePtr++->kc_char = tty.sg_kill;
    KeyCodePtr->kc_char = tchars.t_intrc;
    QuitChar = tchars.t_quitc;
#endif SysV
}


/*
 * Make the cursor
 */
makeCursor ()
{
    theCursor = XCreateFontCursor (display, XC_hand1);
}


/*
 * Set up the selection of events
 */
selectEvents ()
{
    int win;

    XSelectInput (display, calcWin, KeyPressMask | KeyReleaseMask);
    XSelectInput (display, dispWin, ExposureMask);
    for (win = 1; win < NBUTTONS; win++)
        XSelectInput (display, Buttons[win].self,  ExposureMask
                |             ButtonPressMask | ButtonReleaseMask
                |             EnterWindowMask | LeaveWindowMask);
}


/*
 * Get events and process them
 */
takeEvents ()
{
    XEvent Event;
    register int win;
    register int Pressed = False;
    register int InWindow = False;
    char buffer[10];
    register char *KeyChars = buffer;
    register int WasKeyDown = False;
    unsigned i, nbytes;
    int old_color;

    while (1) {
        if (!WasKeyDown)
            XNextEvent (display, &Event);
        else
            Event.type = KeyRelease;

        /*
         * Map keyboard events
         * to Window Events
         */
        if (Event.type == KeyPress || Event.type == KeyRelease) {
            nbytes = XLookupString (&Event, buffer,
                    sizeof(buffer), NULL, NULL);
            if (Event.type == KeyPress) {
                Event.type = ButtonPress;
                WasKeyDown = 1;
            } else {
                for (i = 0; i < 60000; i++)
                    ;
                Event.type = ButtonRelease;
            }
            if ((Event.xbutton.window =  keyToWin (KeyChars,
                    nbytes)) == None) {
                WasKeyDown = 0;
                continue;
            }
        }
        for (win = 0; win < NBUTTONS; win++)
            if (Buttons[win].self == Event.xbutton.window)
                break;
        switch (Event.type) {
        case EnterNotify:
            old_color = windata[win].color;
            break;
        case ButtonPress:
            if (windata[win].color == disabledColor)
                break;
            Pressed = win;
            if (!WasKeyDown)
                InWindow = True;
            windata[win].color = pressedColor;
            drawButton (win, 0);
            break;
        case LeaveNotify:
            if (Pressed != win)
                break;
            InWindow = False;
            windata[win].color = old_color;
            drawButton (win, 0);
            break;
            /*
        case EnterNotify:
            if (Pressed != win)
                break;
            InWindow = True;
            windata[win].color = pressedColor;
            drawButton (win, 0);
            break;
        */
        case ButtonRelease:
            if (windata[win].color == disabledColor ||
                                    Pressed != win) {
                WasKeyDown = False;
                break;
            }
            Pressed = False;
            windata[win].color = unpressedColor;
            if (WasKeyDown || InWindow)
                winPressed (win);
            WasKeyDown = False;
            InWindow = False;
            drawButton (win, 0);
            break;
        case Expose:
            drawButton (win, 1);
            break;
        }
        XFlush(display);
    }
}


/*
     * Make the calculator windows
     */
makeWindows (argc, argv)
int argc;
char *argv[];
{
    register int i;
    XSetWindowAttributes attributes;
    char *window_name = "Programmer's Calculator";
    char *icon_name = "basecalc";

    /*
     * Define the border and background for the main window.
     * - Black border and a patterned background.
     */
    attributes.border_pixel = foreground;
    attributes.background_pixmap = grayPixmap;
    /*
     * Create the main window (calculator frame) as a 
     * child of the Root Window
     */
    attributes.cursor = theCursor;
    calcWin = XCreateWindow(display, DefaultRootWindow(display),
            sizehints.x, sizehints.y, sizehints.width, sizehints.height,
            1, DefaultDepth(display, screen_number), InputOutput,
            CopyFromParent, CWBorderPixel | CWBackPixmap | CWCursor,
            &attributes);
#ifdef X11R3
    XSetStandardProperties (display, calcWin, window_name,
            icon_name, NULL, argv, argc, &sizehints);
#endif

    /*
     * Create the icon window and associate it with the calculator
     */
    iconPixmap = makePixmap(icon_bits, icon_width, icon_height);
    attributes.border_pixel = foreground;
    attributes.background_pixmap = iconPixmap;
    iconWin = XCreateWindow(display, DefaultRootWindow(display),
            iconsizehints.x, iconsizehints.y, iconsizehints.width,
            iconsizehints.height, 1, DefaultDepth(display, screen_number),
            InputOutput, CopyFromParent, CWBorderPixel | CWBackPixmap,
            &attributes);
    wmhints.icon_window = iconWin;
    wmhints.initial_state = iconOnly ? IconicState : NormalState;
    wmhints.input = True;
    wmhints.flags |= InputHint | StateHint | IconWindowHint;
#ifdef X11R3
    XSetWMHints(display, calcWin, &wmhints);
#else
    {
        XClassHint class_hints;

        /* format of the window name and icon name 
     * arguments has changed in R4 */
        XTextProperty windowName, iconName;

        /* These calls store window_name and icon_name into
     * XTextProperty structures and set their other 
     * fields properly. */
        if (XStringListToTextProperty(&window_name, 1,
                &windowName) == 0) {
            (void) fprintf( stderr, "%s: structure allocation for windowName failed.\n",
                                    argv[0]);
            exit(-1);
        }

        if (XStringListToTextProperty(&icon_name, 1, &iconName) ==
                0) {
            (void) fprintf( stderr, "%s: structure allocation for iconName failed.\n",
                                    argv[0]);
            exit(-1);
        }

        class_hints.res_name = argv[0];
        class_hints.res_class = "Basicwin";

        XSetWMProperties(display, calcWin, &windowName,
                &iconName,  argv, argc, &sizehints, &wmhints,
                            &class_hints);
    }
#endif

    /*
     * Create the buttons as subwindows. 
     */
    attributes.background_pixmap = lgrayPixmap;
    attributes.border_pixel = foreground;
    for (i = 0; i < NBUTTONS; i++)
        switch (windata[i].color) {
        case WHITE:
            Buttons[i].self = XCreateSimpleWindow(display,
                    calcWin, Buttons[i].x, Buttons[i].y,
                    Buttons[i].width, Buttons[i].height,
                    1, foreground, background);
            break;
        case BLACK:
            Buttons[i].self = XCreateSimpleWindow(display,
                    calcWin, Buttons[i].x, Buttons[i].y,
                    Buttons[i].width, Buttons[i].height,
                    1, background, foreground);
            break;
        case LIGHTGRAY:
            Buttons[i].self = XCreateWindow(display,
                    calcWin, Buttons[i].x, Buttons[i].y,
                    Buttons[i].width, Buttons[i].height,
                    1, CopyFromParent, InputOutput, CopyFromParent,
                                    CWBorderPixel | CWBackPixmap,
                    &attributes);
            break;
        }

    /*
     * The display window is distinguished
     */
    dispWin = Buttons[0].self;

    /*
     * Initialize event catching.
     */
    selectEvents ();

    /*
     * Map the calculator and sub-windows.
     */
    XMapSubwindows(display, calcWin);
    XMapWindow(display, calcWin);
}


/*
 * Draw a single button with its text
 */
drawButton (win, exposeEvent)
register int win;
{
    register char *string;
    register int x, y;
    struct windata *winp;
    char *measure;
    XSetWindowAttributes attributes;
    unsigned long valuemask;
    GC gc;

    winp = &windata[win];
    x = winp->x;
    y = winp->y;
    string = winp->text;

    switch (windata[win].color) {
    case WHITE:
        gc = fgGC;
        attributes.background_pixel = background;
        attributes.border_pixel = foreground;
        valuemask = CWBackPixel | CWBorderPixel;
        break;
    case BLACK:
        gc = bgGC;
        attributes.background_pixel = foreground;
        attributes.border_pixel = background;
        valuemask = CWBackPixel | CWBorderPixel;
        break;
    case LIGHTGRAY:
        gc = bgGC;
        attributes.background_pixmap = lgrayPixmap;
        attributes.border_pixel = foreground;
        valuemask = CWBackPixmap | CWBorderPixel;
        break;
    }
    if (!exposeEvent) {
        XChangeWindowAttributes(display, Buttons[win].self,
                valuemask, &attributes);
        XClearWindow(display, Buttons[win].self);
    }
    XDrawString (display, Buttons[win].self, gc, x, y, string,
            strlen (string));
    if (win == 0) {
        switch (Base) {
        case 10:
        case 8:
            measure = Octmeasure;
            break;
        default:
        case 16:
        case 2:
            measure = Hexmeasure;
            break;
        }
        XDrawString (display, dispWin, gc, 7, 6, measure,
                31);
    }
}


static unsigned int LastDisp = 1;
/*
 * Do the operation corresponding to a key press
 */
winPressed (win)
{
    register int type;

    type = windata[win].type;
    switch (type) {
    case WTYP_CONV:
        convButton (win);
        displayVal (LastDisp == 1 ? Value : Accum);
        break;
    case WTYP_DIG:
        digitButton (win);
        displayVal (Value);
        LastDisp = 1;
        break;
    case WTYP_OPER:
        if (operButton (win) == 0) {
            displayVal (Accum);
            LastDisp = 2;
        } else {
            displayVal (Value);
            LastDisp = 1;
        }
        break;
    case WTYP_SPEC:
        specButton (win);
        displayVal (LastDisp == 1 ? Value : Accum);
        LastDisp = 1;
    }
}


/*
 * Handle a conversion button
 */
convButton (win)
{
    register int i, NewBase, Diff, Digit;
    register int HiBase, LowBase;

    NewBase = windata[win].value;
    windata[Winbase].color = unpressedColor;
    drawButton (Winbase, 0);
    windata[win].color = pressedColor;

    Diff = NewBase - Base;
    if (Diff) {
        if (NewBase > Base) {
            LowBase = Base;
            HiBase = NewBase;
        } else {
            LowBase = NewBase;
            HiBase = Base;
        }
        for (i = 1; i < NBUTTONS; i++) {
            if (windata[i].type == WTYP_DIG) {
                Digit = windata[i].value;
                if (Digit >= LowBase && Digit <
                        HiBase) {
                    if (Diff < 0)
                        windata[i].color =
                                disabledColor;
                    else
                        windata[i].color =
                                unpressedColor;
                    drawButton (i, 0);
                }
            }
        }
    }
    Winbase = win;
    Base = NewBase;
}


/*
 * Handle a digit button
 */
digitButton (win)
{
    register unsigned long Temp;

    if (CalcReset) {
        CalcReset = 0;
        Accum = 0;
        Value = 0;
        LastOpt = OPR_ADD;
    }
    Digit = windata[win].value;
    if (Unsigned)
        Temp = (unsigned)Value * (unsigned)Base + Digit;
    else
        Temp = Value * Base + Digit;
    if ((unsigned)Temp / Base != (unsigned)Value) {    /* OverfLow? */
        /*
         * Flash the display since the character didn't register
         */
        windata[0].color =  (displayColor == WHITE) ?
                BLACK : WHITE;
        drawButton (0, 0);
        XFlush(display);
        Delay ();
        windata[0].color = displayColor;
        drawButton (0, 0);
        return;
    }
    Value = Temp;
}


/*
 * Handle a special operator
 */
specButton (win)
{
    register int oper;

    oper = windata[win].value;

    switch (oper) {
    case OPR_CLRD:
        if (LastOpt == OPR_ASGN)
            break;
        Value = (unsigned)Value / Base;
        break;
    case OPR_CLRE:
        Value = 0;
        break;
    case OPR_CLRA:
        Accum = 0;
        Value = 0;
        LastOpt = OPR_ADD;
        break;
    case OPR_UNS:
        Unsigned = !Unsigned;
        windata[win].text = Unsigned ? "U" : "S";
        windata[win].color = pressedColor;
        drawButton (win, 0);
        break;
    }
}


/*
 * Handle an operator
 */
operButton (win)
{
    register int oper;

    oper = LastOpt;
    LastOpt = windata[win].value;

    CalcReset = 0;
    switch (LastOpt) {
    case OPR_NEG:
        Value = -Value;
        if ((LastOpt = oper) == OPR_ASGN)
            Accum = Value;
        return 1;
    case OPR_NOT:
        Value = ~Value;
        if ((LastOpt = oper) == OPR_ASGN)
            Accum = Value;
        return 1;
    }

    switch (oper) {
    case OPR_ADD:
        if (Unsigned)
            Accum = (unsigned)Accum + (unsigned)Value;
        else
            Accum += Value;
        break;
    case OPR_SUB:
        if (Unsigned)
            Accum = (unsigned)Accum - (unsigned)Value;
        else
            Accum -= Value;
        break;
    case OPR_MUL:
        if (Unsigned)
            Accum = (unsigned)Accum * (unsigned)Value;
        else
            Accum *= Value;
        break;
    case OPR_DIV:
        if (Value == 0)
            break;
        if (Unsigned)
            Accum = (unsigned)Accum / (unsigned)Value;
        else
            Accum /= Value;
        break;
    case OPR_MOD:
        if (Value == 0)
            break;
        if (Unsigned)
            Accum = (unsigned)Accum % (unsigned)Value;
        else
            Accum %= Value;
        break;
    case OPR_OR:
        Accum |= Value;
        break;
    case OPR_AND:
        Accum &= Value;
        break;
    case OPR_SHR:
        if (Unsigned)
            Accum = (unsigned)Accum >> (unsigned)Value;
        else
            Accum >>= Value;
        break;
    case OPR_SHL:
        if (Unsigned)
            Accum = (unsigned)Accum << (unsigned)Value;
        else
            Accum <<= Value;
        break;
    case OPR_XOR:
        Accum ^= Value;
        break;
    case OPR_ASGN:
        break;
    }
    if (LastOpt == OPR_ASGN) {
        Value = Accum;
        CalcReset = 1;
        return 1;
    }
    Value = 0;
    return 0;
}


/*
 * Display a number in the display window
 */
displayVal (number)
register long number;
{
    register char *Fmt;
    register char *cp;
    register int i;

    switch (Base) {
    case 16:
        Fmt = "%32x";
        break;
    case 10:
        Fmt = "%32d";
        break;
    case 8:
        Fmt = "%32o";
        break;
    case 2:
        Fmt = "%032b";
        break;
    }
    cp = windata[0].text;
    for (i = 32; --i >= 0; )
        *cp++ = ' ';
    *cp = '\0';
    Sprintf (windata[0].text, Fmt, number);
    drawButton (0, 0);
}


/*
 * Translate a key code to a corresponding window
 */
keyToWin (str, n)
register char *str;
register unsigned n;
{
    register int value = -1;
    register struct KeyCode *KeyCodePtr;
    register char ch;
    register int i;

    if (n > (unsigned) 0) {
        ch = *str;
        if (islower(ch) && isxdigit(ch))
            value = 10 + ch - 'a';
        else if (isdigit(ch))
            value = ch - '0';
        if (value >= 0) {
            for (i = 1; i < NBUTTONS; i++)
                if (windata[i].type == WTYP_DIG &&
                                            windata[i].value ==
                        value)
                    return Buttons[i].self;
        } else {
            /*
             * Do some translations - these should be driven
             * from the user's terminal erase, kill, etc
             */
            switch (ch) {
            case 'U':
                if (Unsigned)
                    return - 1;
                str = "S";
                n = 1;
                break;
            case 'S':
                if (!Unsigned)
                    return - 1;
                str = "U";
                n = 1;
                break;
            case '\r':
            case '\n':
                str = "=";
                n = 1;
                break;
            default:
                if (ch == QuitChar) {
                    XCloseDisplay(display);
                    exit (1);
                }
                KeyCodePtr = KeyCodes;
                while ((n = KeyCodePtr->kc_len) >
                        (unsigned) 0) {
                    if (ch == KeyCodePtr->kc_char) {
                        str = KeyCodePtr->kc_func;
                        break;
                    }
                    KeyCodePtr++;
                }
                if (n == 0)
                    n = 1;
                break;
            }
            for (i = 1; i < NBUTTONS; i++) {
                if (windata[i].type != WTYP_DIG &&
                                            strncmp (windata[i].text,
                        str, (int) n) == 0)
                    return Buttons[i].self;
            }
        }
    }
    return None;
}


/*
 * Specialized version of C Library sprintf.
 *
 * %u %d %o %x %b (binary) are recognized.
 * %0W... - where 0 means pad with zeros otherwise blanks
 *       - if W, the minimum field width is larger than
 *      - the number
 */
Sprintf(cp, fmt, x1)
register char *cp;
register char *fmt;
unsigned x1;
{
    register int c, b, sign;
    register char *s;
    register unsigned short fw;
    char *printInBase();
    char pad;

    while ((c = *fmt++) != '%') {
        if (c == '\0') {
            *cp = c;
            return;   /* to displayVal */
        }
        *cp++ = c;
    }
    c = *fmt++;
    if (c == '0') {
        pad = '0';
        c = *fmt++;
    } else
        pad = ' ';

    /*
     * Calculate minimum field width
     */
    fw = 0;
    while (c >= '0' && c <= '9') {
        fw = fw * 10 + (c - '0');
        c = *fmt++;
    }
    sign = 0;
    switch (c) {
    case 'x':
        b = 16;
        break;
    case 'd':
        if (!Unsigned)
            sign = 1;
        /*  falls through into 'u' case */
    case 'u':
        b = 10;
        break;
    case 'o':
        b = 8;
        break;
    case 'b':
        b = 2;
        break;
    default:
        /*
         * Unknown format
         */
        b = 0;
        break;
    }
    if (b)
        cp = printInBase (cp, x1, b, fw, pad, sign);
}


/*
 * Print a number n in base b into string cp.
 * Minimum field width = fw, pad character = pad
 */
char *
printInBase (cp, n, b, fw, pad, sign)
register char *cp;
register long n;
register b;
register int fw, pad;
{
    register i, nd, c;
    int flag;
    int plmax;
    char d[33];

    c = 1;
    if (sign)
        flag = n < 0;
    else
        flag = 0;
    if (flag)
        n = (-n);
    if (b == 2)
        plmax = 32;
    else if (b == 8)
        plmax = 11;
    else if (b == 10)
        plmax = 10;
    else if (b == 16)
        plmax = 8;
    if (b == 10) {
        if (flag == 0)
            sign = 0;
        flag = 0;
    }
    for (i = 0; i < plmax; i++) {
        if (flag == 0)
            nd = (unsigned)n % b;
        else
            nd = n % b;
        if (flag) {
            nd = (b - 1) - nd + c;
            if (nd >= b) {
                nd -= b;
                c = 1;
            } else
                c = 0;
        }
        d[i] = nd;
        if (flag == 0)
            n = (unsigned)n / b;
        else
            n = n / b;
        if ((n == 0) && (flag == 0))
            break;
    }
    if (i == plmax)
        i--;
    if (sign) {
        fw--;
        if (pad == '0')
            *cp++ = '-';
    }
    if (fw > i + 1) {
        for (fw -= i + 1; fw > 0; fw--)
            *cp++ = pad;
    }
    if (sign && pad != '0')
        *cp++ = '-';
    for (; i >= 0; i--)
        *cp++ = "0123456789ABCDEF"[d[i]];
    *cp = '\0';
    return cp;
}


/*
 * Delay a little while
 */
Delay ()
{
    long tic;

    for (tic = 0; tic < 50000; tic++)
        ;
}


