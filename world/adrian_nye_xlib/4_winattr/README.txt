Cap. 4 Window Attributes.

Window attributes can be set with structure XSetWindowAttributes.
typedef struct {
        Pixmap background_pixmap;
        unsigned long background_pixel;
        Pixmap border_pixmap;
        unsigned long border_pixel;
        int bit_gravity;
        int win_gravity;
        int backing_store;
        unsigned long backing_planes;
        unsigned long backing_pixel;
        Bool save_under;
        long event_mask;
        long do_not_propagate_mask;
        Bool override_redirect;
        Colormap colormap;
        Cursor cursor;
} XSetWindowAttributes;

This structure can be set with 2 methods:
     XCreateWindow
     XChangeWindowAttributes

Both methods receive a value mask to indicate which parameters have been set.
The mask can be one of:
    CWBackPixmap, CWBackPixel, CWBorderPixmap, CWBorderPixel,
    CWBitGravity, CWWinGravity,
    CWBackingStore, CWBackingPlanes, CWBackingPixel,
    CWOverrideRedirect,
    CWSaveUnder,
    CWEventMask, CWDontPropagate,
    CWColormap,
    CWCursor.

Some of these paramters can be set directly with separate routines.
     XSetWindowBackgroundPixmap
     XSetWindowBackground
     XSetWindowBorderPixmap
     XSetWindowBorder
     XSelectInput
     XSetWindowColormap
     XDefineCursor, XUndefineCursor

For possible values for each parameter we can look up man XSetWindowAttributes.
