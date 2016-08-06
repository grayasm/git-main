Introduction
------------

1) display= keyboard + pointing device (mouse) + n>=1 screens

2) X server= local program that controls your display
     - allow access to the display by multiple clients (local or remote)
     - interprets network messages from clients
     - passes user input to clients by sending network messages
     - does 2D drawing for the clients
     - maintain display resources/IDs (fonts,contexts,cursors,etc)

3) window manager= is given special authority, manages screen layout,appearance,
       style of interaction

4) events= X client must be ready to repspond to many different events that can
       occur at any time; keypress, mouse click/move, window move/resize/overlap

5) extensions= vendors can add features to Xlib/X (client+server side code)
     - MIT's Shape extension for non-rectangular windows
     - X Input extension for input devices other than keyboard and mouse
     - PEX 3D graphic extension


All clients except the window manager are called applications.
Toolkits: allows to create widgets, user OOP paradigm
     - Xt Toolkit is X11 official one, originally from Digital + MIT
     - Interviews Toolkit from Standford University
     - Motif widget toolkit and GUI from Digital + HP
     - OPEN LOOK GUI and specification from SUN

