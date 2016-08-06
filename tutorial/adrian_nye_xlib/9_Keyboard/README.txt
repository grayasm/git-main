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
    Example 9-2 Some sample keysym definitions.
    See:

    /usr/include/X11/keysym.h
    /usr/include/X11/keysymdef.h

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

    You can prepare 2 or more text items for XDrawText to display overstrike
    char and use the delta member to move the second character back over the first.
    You can use different font for each text in case the desired accent is missing.

    9.1.2 Keyboard Mappings
    There are several translations between pressing a key and its interpretation.
    1st mapping is server dependent and cannot be modified.
    2nd mapping, keycode to keysym can be modified by client but is server wide.
    3rd mapping, keysym  to string is local to client.


    9.1.2.2 The Modifiers Keys
    Although the Shift is present on all keyboards and Control on most, the
    remaining modifier keys are not standardized.
    xmodmap:  up to 4 keys per modifier, (keycodes in parentheses):

    shift       Shift_L (0x32),  Shift_R (0x3e)
    lock        Caps_Lock (0x42)
    control     Control_L (0x25),  Control_R (0x69)
    mod1        Alt_L (0x40),  Alt_R (0x6c),  Meta_L (0xcd)
    mod2        Num_Lock (0x4d)
    mod3
    mod4        Super_L (0x85),  Super_R (0x86),  Super_L (0xce),  Hyper_L (0xcf)
    mod5        ISO_Level3_Shift (0x5c),  Mode_switch (0xcb)

    9.1.2.3 Keycode to Keysym
    The mapping table is stored in the Display.
    XChangeKeyboardMapping() will change a key mapping for all clients.
    All clients receive MappingNotify event and must call XRefreshKeyboardMapping
    to get the new mapping table.
    Usefull to switch between different keyboards layouts like QWERTY <-> DVORAK

    English language keyboards are pretty standards but they differ in the offer
    of the function keys. There are 2 approaches: ENGRAVING and COMMON.
    ENGRAVING: assign different keysym to Del,DEL and Delete
    COMMON   : assign 1 key to Del,DEL and Delete to merge all Delete functionality
               to 1 keysym, and to make it easy to write portable applications.

    9.3 The Pointer.
    9.2.1 Tracking Pointer Motion
    - process every motion event (may lag behind current position)
    - get final position after mouse movement XQueryPointer()
    - reading motion history buffer with XGetMotionEvents() between 2 times
      useful for undoing or respoding to exposure events in drawing applications

    Select OwnerGrabButtonMask to receive ButtonRelease even if the mouse was
    released over another window.
    For drawing or dragging scrollbars use PointerMotionHintMask which is a
    modifier. It does not select events by itself. Track mouse motion between:
    EnterNotify->ButtonPress->MotionNotify->ButtonRelease->LeaveNotify.

    If motion history exists on the server XDisplayMotionBufferSize() display>0
    than all selected events are placed in XTimeCoord by XGetMotionEvents()
    and a pointer to the list is returned.

    9.2.3 Changing the Pointer Button Mapping
    To simulate buttons 4,5 with a 3 buttons mounse a mapping of pointer
    buttons must be done via XSetPointerMapping(), XGetPointerMapping().

    9.2.4 Moving the Pointer
    XWarpPointer() moves the pointer to a relative or global position.
    It should be minimized as it confuses the user.

    9.3 Border Crossing and Keyboard Focus Change Events
    LeaveNotify,EnterNotify - pointer crosses window border.
    FocusIn, FocusOut - keyboard focus changes.

    9.4 Grabbing the Keyboard and Pointer
    XGrabKeyboard(), XGrabPointer(), XGrabButton(), XGrabKey() - on request.
    XUngrabButton(), XUngrabKey(), XUngrabKeyboard(), XUngrabPointer()
    When you grab a device, no other application can receive input from that
    device. Do it only when necessary!!
    Change conditions of an active pointer grab with XChangeActivePointerGrab().

    9.4.1 GrabModeAsync - grabed events are sent immediately
          GrabModeSync - grabed events are queued, until XAllowEvents() or an
          ungrab request.

    9.5 Keyboard Preferences
    XGetKeyboardControl(), XChangeKeyboardControl() - set all preferences at
                                                      once, also possible per
                                                      key.
    XAutoRepeatOff(), XAutoRepeatOn() - global autorepeat but not per key.

    9.6 Pointer Preferences
    XGetPointerControl(), XChangePointerControl()
