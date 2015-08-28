 Chapter 9 The Keyboard and Pointer

 9.1 The Keyboard

 KeyPress and KeyRelease events are stored in XKeyEvent.
 typedef struct {
         int           type;
         unsigned      long serial;
         Bool          send_event;
         Display*      display;
         Window        window;         // "event" window reported in
         Window        root;           // root window event occured on
         Window        subwindow;      // child window
         Time          time;           // milliseconds
         int           x, y;           // coordinates in event window
         int           x_root, y_root; // coordinates relative to root
         unsigned int  state;          // key or button mask
         unsigned int  keycode;        // detail
         Bool          same_screen;    // same screen flag
 } XKeyEvent;
 typedef XKeyEvent XKeyPressedEvent;
 typedef XKeyEvent XKeyReleasedEvent;

    keycode is a number between 8 and 255 regardless of whether a key is pressed
    or released.
    Different brands of equipement may generate different keycodes for the same
    symbol, that is why the keycode without the state of the modifier keys
    does not provide enough information to interpret it. Instead one must use
    XLookupString() to translate key event into a keysym.

    A keysym is a defined constant that corresponds to the meaning of a key event.
    Example 9-2 Some sample keysym definitions

#define XK_Backspace        0xFF08  // Back space, back char, ...
#define XK_Left             0xFF51  // Move left, left arrow
#define XK_Undo             0xFF65  // Undo, oops
#define XK_Num_Lock         0xFF7F
#define XK_KP_Multiply      0xFFAA
#define XK_Shift_L          0xFFE1  // Left Shift
#define XK_space            0x020   // Space
#define XK_numbersign       0x023   // #
#define XK_3                0x033
#define XK_question         0x03f   // "?"
#define XK_A                0x041
#define XK_e                0x065

    The ASCII value for a particular keysym as returned by XKoopupString() can
    be changed by the client using XRebindKeysym(), and it can be a string of
    any length, not just a single character. The mapping would apply only to
    that client.

    If the keystroke is a modifier key the event can be ignored since the
    modifier status of events on other keys is already dealt with by
    XLookupString(). Though, XK_Delete or XK_Backspace would indicate that a
    character should be removed from the string.
    XComposeStatus argument of XLookupString() is legacy Compose key for typing
    other languages characters and it is now just a dummy.
