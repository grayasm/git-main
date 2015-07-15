Cap3. basicwin program

This chapter describes the source code of 'basicwin' program.
The basic steps that were taken in this program are as follows:

    1. Open connection to server - XOpenDisplay.
    2. Make sure connection succeeded, print error and exit if not.
    3. Get display dimensions - DisplayWidth
    4. Calculate desired size of window and create window - XCreateSimpleWindow.
    5. Create pixmap for icon - XCreateBitmapFromData.
    6. Initialize XSizeHint structure - PPosition | PSize | PMinSize.
    7. Set standard properties for window manager - XSetWMProperties.
    8. Select desired event types - XSelectInput.
    9. Map window - XMapWindow.
    10. Set up event gathering loop - XNextEvent.
    11. If event is of type Expose, draw contents of window - event.type.
    12. If event is of type ConfigureNotify, recalculate dimensions of window.
    13. If event is ButtonPress or KeyPress, close the display and exit.
