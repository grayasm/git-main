/*
 * key3 example
 *
 *       Keysym macros, e.g. IsKeypadKey().
 *       XKeysymToString()  - convert keysym to char*
 *       XLookupKeysym()    - convert event to keysym
 *       XGetKeyboardMapping- convert keycode into keysym
 *       XStringToKeysym    - convert char* into keysym
 *
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>


Display* dpy = NULL;
void printKeyEvent(XKeyEvent* xkey);

int main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	dpy = XOpenDisplay(NULL);
	if(!dpy) return -1;

	int scrno = DefaultScreen(dpy);
	int scrwidth = DisplayWidth(dpy, scrno);
	int scrheight = DisplayHeight(dpy, scrno);


	int x = 10;
	int y = 10;
	int winwidth = scrwidth / 5;
	int winheight = scrheight / 6 ;
	int winborder = 1;


	Window win = XCreateSimpleWindow(dpy,
	                                 RootWindow(dpy, scrno),
	                                 x, y,
	                                 winwidth, winheight,
	                                 winborder,
	                                 BlackPixel(dpy, scrno),
	                                 WhitePixel(dpy, scrno));


	/* X.h
	   line: 150 to 175   Event definitions;
	*/
	long event_mask = KeyPressMask | ButtonPressMask;
	XSelectInput(dpy, win, event_mask);

	XMapWindow(dpy, win);


	// Process key events
	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);

		if (event.type == KeyPress)
		{
			XKeyEvent* xkey = &(event.xkey);
			printKeyEvent(xkey);
		}

		if (event.type == ButtonPress)
			break;
	}


	// exit clean
	XUnmapWindow(dpy, win);
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}


void printKeyEvent(XKeyEvent* xkey)
{

	char buff[100];
	KeySym keysym;
	XComposeStatus status;
	int ret = XLookupString (xkey,
	                         buff,
	                         100,
	                         &keysym,
	                         &status);

	std::stringstream ss;
	ss << "char=";
	if (strlen(buff) != 0)
		ss << buff;
	ss << " keysym=U+" << std::uppercase << std::setfill('0') << std::setw(4)
	   << keysym << " ";

	/* Xutil.h line:239 - Keysym macros, used on Keysyms to test for classes
	   of symbols.*/
	if (IsKeypadKey(keysym))        ss << " KeyPad";
	if (IsPrivateKeypadKey(keysym)) ss << " PrivateKeyPad";
	if (IsCursorKey(keysym))        ss << " Cursor";
	if (IsPFKey(keysym))            ss << " PF";
	if (IsFunctionKey(keysym))      ss << " Function";
	if (IsMiscFunctionKey(keysym))  ss << " MiscFunction";
	if (IsModifierKey(keysym))      ss << " Modifier";

	// keysym -> char*
	const char* str = XKeysymToString(keysym);
	ss << " " << str;

	// event -> keysym
	KeySym keysym2 = XLookupKeysym(xkey, 0);
	if (keysym2 != keysym) ss << " XLookupKeysym-error";

	// keycode -> keysym
	int keysyms_per_keycode_return[10];
	KeySym* keysym3 = XGetKeyboardMapping(dpy,
	                                      xkey->keycode,
	                                      1,
	                                      keysyms_per_keycode_return);
	if (keysyms_per_keycode_return == 0) ss << " XGetKeyboardMapping-error";
	else if (*keysym3 != keysym) ss << " XGetKeyboardMapping-error";

	// char* to keysym
	KeySym keysym4 = XStringToKeysym(str);
	if (keysym4 != keysym) ss << " XStringToKeysym-error";


	// lower to upper sym
	KeySym keysym_lower, keysym_upper;
	XConvertCase (keysym,
	              &keysym_lower,
	              &keysym_upper);
	const char* str_lower = XKeysymToString(keysym_lower);
	const char* str_upper = XKeysymToString(keysym_upper);
	ss << " " << str_lower;
	ss << " " << str_upper;

	int min_keycodes_return, max_keycodes_return;
	XDisplayKeycodes(dpy, &min_keycodes_return, &max_keycodes_return);
	if (min_keycodes_return < 8 ||
	    max_keycodes_return > 255)
		ss << " XDisplayKeycodes-error";

	printf("\n%s", ss.str().c_str());
} // printXEvent()
