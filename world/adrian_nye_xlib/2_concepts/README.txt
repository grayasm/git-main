.
.
The X Protocol:
    - specifies what information is transferred between the server <-> Xlib
    - types of packets: requests, replies, events and errors
      Request: Xlib -> server (e.g. draw a line, change item color, etc)
      Reply  : server -> Xlib (as response to Request)
      Event  : server -> Xlib (device action, side effect of previous request, etc)
      Error  : server -> Xlib (request was invalid)

Buffering:
    - Xlib saves up requests instead of sending them to the server immediately,
      so the client program can continue running instead of waiting to gain
      access to the network after every Xlib call.
    - Xlib sends the buffer to the server in 3 conditions:
      1) application calls Xlib to wait for an event that's not in the queue
      2) Xlib calls that get information require a reply before it can continue
      3) the client would like to flush the buffer manually when no user events are expected
    - X server sends the events to Xlib as soon as the network allows. It does not
      queue them or group them (except under rare conditions).

Resources:
    - X server maintains all data structures as resources (window,pixmap,colormap,
      cursor,font or graphic context)
    - the client allocates the resource ID, server maintains it, client manipulates
      a resource only if it knows the ID, client can query the server for infos.

Properties and Atoms:
    - clients can communicate arbitrary data with each other through properties
    - Property { String name, Atom ID }; name="WM_COLORMAP_WINDOWS", ID is unique number

Window Manager:
    - is just another client written with Xlib, with special responsabilities to
      mediate competing demands for the physical resources of a display
    - communication between clients and window manager occurs through properties
      known as hints, not necessarly honored by the window manager
    - substructure redirection=size, position, overlapping order of the children
      of a window. Requests to change these are canceled by the server and an
      event is sent to window manager to decide on these.
      2 significant implications for applications:
      a) application cannot assume that window position/size was respected in reality
      b) mapping of a top-level window is decided by window manager which decides
         on the configuration and maps the window to itself which implies the
         window is not visible immediately. Application must know when the window
         is visible before drawing anything into it. There is an event for this.
    - it can start and kill applications aka session management.

X Windows:
    - a windows has always a parent and is contained within the parent limits.
    - cannot display output outside itself and cannot receive input while pointer
      is outside itself unless a grab or keyboard focus is in effect.
    - every window fits in a hierarchy setup by its children, its parent, its parent's
      parent, and so on. The very first window, the only one that has no parent
      is called the root window and fills the entire screen.
    - the root window is created by the X server as it starts up.
