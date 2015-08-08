     Cap.8 Events

     Events are central to X server.
     An event reports:
     a) user input or information from other clients
     b) notifying other clients (e.g. pasting text into other client)
     c) notifying window manager (e.g. layout of the window)

     Event handling in 3 steps:
     1) select the events for a window (XSelectInput)
     2) map the window (XMapWindow)
     3) run the events loop (XNextEvent)

     There are 30 different events structures, all having XAnyEvent members.
     typedef struct {
             int type;
             unsigned long serial;
             Bool send_event;
             Display* display;
             Window* window;
     } XAnyEvent;

     type  : KeyPress,MotionNotify,FocusIn,Expose,DestroyNotify,ConfigureNotify,etc
     serial: last protocol req. processed by server, for use in debugging.
     send_event: False->sent from the server, True->from another client.
     display: connection to the server
     window : window that selected and received the event


     Union XEvent contains all event structures:
     typedef union _XEvent {
                   int             type;    <- indicate the type of the event
                   XAnyEvent       xany;    ? use the event indicated by type
                   XExposeEvent    xexpose; ?
                   XKeyEvent       xkey;
                   XButtonEvent    xbutton;
                   XConfigureEvent xconfigure;

      This is a list of the event-handling routines and their differences.
      In these routines you pass a pointer to XEvent structure to be filled.

      XNextEvent
      XMaskEvent
      XCheckMaskEvent
      XWindowEvent
      XCheckWindowEvent
      XIfEvent
      XCheckIfEvent
      XPeekEvent
      XPeekIfEvent
      XCheckTypedEvent
      XCheckTypedWindowEvent
      XEventsQueued
      XPending
      XPutBackEvent
      XGetMotionEvents
      XQLength

      The methods above they search for an event. If Xlib event queue is empty
      then it flushes the commands buffer and waits. Some methods return
      immediately True or False (Check). Some methods use a predicate (If).
      Some methods only peek at the events in the queue, they do not remove
      them (Peek)

      Selecting Events
      XSelectInput sets the event_mask attribute of a window.
      event_mask can also be set with XChangeWindowAttributes or XCreateWindow.

      Event mask symbol                   Circumstances
      _________________                   _____________
      NoEventMask                         No events
      KeyPressMask                        Keyboard down
      KeyReleaseMask                      Keyboard up
      ButtonPressMask                     Pointer button down
      ButtonReleaseMask                   Pointer button up
      EnterWindowMask                     Pointer window entry
      LeaveWindowMask                     Pointer window leave
      PointerMotionMask                   All pointer motion
      PointerMotionHintMask               Fewer pointer motion
      Button1MotionMask                   Pointer motion while button 1 down
      Button2MotionMask                                               2
      Button3MotionMask                                               3
      Button4MotionMask                                               4
      Button5MotionMask                                               5
      ButtonMotionMask                    Pointer motion while any button down
      KeymapStateMask                     Any keyb. state change on EnterNotify, LeaveNotify
      ExposureMask                        Any exposure (except {Graphics,No}Expose
      VisibilityChangeMask                Any change in visibility
      StructureNotifyMask                 Any change in window configuration
      ResizeRedirectMask                  Redirect resize of this window
      SubstructureNotifyMask              Notify about reconfiguration of children
      FocusChangeMask                     Any change in keyboard focus
      PropertyChangeMask                  Any change in property
      ColormapChangeMask                  Any change in colormap
      OwnerGrabButtonMask                 Modifies handling of pointer events


      Keyboard Focus Window:
      The keyboard focus is set to a window with XSetInputFocus().
      The current focus can be read with XGetInputFocus().
      Can set the focus window when the mouse enter the top-level window, as
      long as it is set back to the root window when the pointer leaves again.

      Keyboard and Pointer Grabbing:
      direct : XGrabPointer(), XGrabKeyboard()
      passive: XGrabButton(),  XGrabKey  (useful in implementing menus)
      Can confine the pointer to any window within the grabing client.

      KeyPress and KeyRelease:
      privides a keycode server dependent and should not be used.
      Use: XLookupString() to translate keycode into portable symbol (keysym)
      which represents the symbol of the cap of the key, and into as ASCII
      character string.
      There is a special provision for a special Compose key available on some
      keyboards to type characters for languages other than English.
