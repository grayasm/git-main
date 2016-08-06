/*
 * key1 example
 *
 *      Select KeyPressMask to get keyboards events.
 *      Convert event into XKeyEvent.
 *      Use XLookupString to get a char* representation of the event and the
 *          associated KeySym id integer for the pressed key.
 *      Map keysym to a key code from X11/keysymdef.h and decide how this
 *          affects the text buffer.
 *      Use XDrawString to display the text buffer, one line at a time.
 *          Track 'Enter' or equivalent 'Return' key code to break the line.
 *          Track ConfigureNotify or window resize to redraw/reformat the text.
 *
 *      The sample would have been too big and take too much time to implement:
 *          cursor position in the buffer and tracking PAD (left,right,arrows)
 *          cursor pixmap for the window and its current position
 *          tab with 2/4/8 space characters
 *          other keys
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <string>


int main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	Display* dpy = XOpenDisplay(NULL);
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
	long event_mask = KeyPressMask |
		              StructureNotifyMask;

	/* Select all events for our top window. */
	XSelectInput(dpy, win, event_mask);


	/* Select a nice font */
	Font font;
	int fontret = 0;
	XFontStruct* fontinfos;
	char** fontlist = XListFontsWithInfo(dpy,
	                                     "*",
	                                     700,         // maxnames
	                                     &fontret,    // actual_count_return
	                                     &fontinfos); // info_return
	if(fontlist == NULL)
		return -1;

	// Font details
	int fsz =0, ascent=0, descent=0, lbearing=0, rbearing=0;
	XFontStruct* fontinfo = 0;
	for(int i=0; i < fontret; ++i)
	{
		XFontStruct* fs = &(fontinfos[i]);
		XCharStruct* cs = &(fs->max_bounds);
		fsz = cs->ascent + cs->descent;
		if(fsz < 14 || fsz > 16)
			continue;
		const char* fname = fontlist[i];
		// -medium-  -normal-  -r-
		if(strstr(fname, "-medium-") == 0 ||
		   strstr(fname, "-normal-") == 0 ||
		   strstr(fname, "-r-") == 0)
			continue;

		// found a Font
		font = XLoadFont(dpy, fname);        // load in the X server
		ascent = cs->ascent;
		descent = cs->descent;
		lbearing = cs->lbearing;
		rbearing = cs->rbearing;
		fontinfo = fs;
		break;
	}

	if(ascent == 0)
		return -1;

	// create a GC
	XGCValues gcvalues;
	gcvalues.line_width = 1;
	gcvalues.foreground = BlackPixel(dpy, scrno);
	gcvalues.background = WhitePixel(dpy, scrno);
	gcvalues.font = font;
	unsigned long gcmask = GCLineWidth | GCForeground | GCBackground | GCFont;

	GC gc = XCreateGC(dpy,
	                  win,
	                  gcmask,
	                  &gcvalues);

	XMapWindow(dpy, win);



	// Position in text buffer
	std::string text;
	int col = 0;
	int row = 0;
	int chars = (int) text.size();
	int chars_per_line = (int) floor(winwidth / rbearing);
	int total_lines = (int) ceil(chars / chars_per_line);


	// Process key events
	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);

		if (event.type == ConfigureNotify)
		{
			XConfigureEvent* xconfigure = &(event.xconfigure);
			x = xconfigure->x;
			y = xconfigure->y;
			winwidth = xconfigure->width;
			winheight = xconfigure->height;
		}

		if (event.type == KeyPress)
		{
			XKeyEvent* key = &(event.xkey);
			char buff[100];
			KeySym keysym;
			XComposeStatus status;
			int ret = XLookupString (key,
			                         buff,
			                         100,
			                         &keysym,
			                         &status);

			// X11/keysymdef.h     has all keysym codes, now process only a few

			// cursor changing position (not implemented)
			if (keysym == XK_Home)
			{
				col = 0; row = 0;
			}
			else if (keysym == XK_Left)
			{
				(row > 0 ? --row :
				 (col > 0 ? --col : 0));
			}
			else if (keysym == XK_Up)
			{
				(col > 0 ? --col : 0);
			}
			else if (keysym == XK_Right)
			{
				++row;
			}
			else if (keysym == XK_Down)
			{
				++col;
			}
			else if (keysym == XK_Prior)
			{
				(row > 0 ? --row :
				 (col > 0 ? --col : 0));
			}
			else if (keysym == XK_Page_Up)
			{
				(col > 10 ? col -= 10 : col = 0);
			}
			else if (keysym == XK_Next)
			{
				++row;
			}
			else if (keysym == XK_Page_Down)
			{
				col += 10;
			}
			else if (keysym == XK_End)
			{
				col = 0; row = 0;
			}
			else if (keysym == XK_Begin)
			{
				col = 0; row = 0;
			}

			// text modifiers
			else if (keysym == XK_BackSpace)
			{
				size_t sz = text.size();
				if (sz > 0)
					text.resize(sz - 1);
			}
			else if (keysym == XK_Tab){}
			else if (keysym == XK_Linefeed){}
			else if (keysym == XK_Clear){}
			else if (keysym == XK_Return)
			{
				text += '\n';
			}

			// append buffer to existing text
			else if (XK_space <= keysym && keysym <= XK_asciitilde)
			{
				text += buff;
			}

			// recalculate text parameters
			chars = (int) text.size();
			chars_per_line = (int) floor(winwidth / rbearing);
			total_lines = (int) ceil((float)chars / (float)chars_per_line);

			// avoid text mangling
			XClearWindow(dpy, win);


			// draw text
			int curr_line = 0; // < total_lines
			for (int c=0; c < text.size(); /*no incr*/)
			{
				// buffer smaller than 1 line of screen text
				int chars_to_display = chars_per_line;
				if (c + chars_to_display > chars)
					chars_to_display = chars - c;

				// break line on 'Enter'
				size_t ret = text.find('\n', c);
				if (ret != std::string::npos)
				{
					if (chars_to_display > (ret - c + 1))
						chars_to_display = (ret - c + 1);
				}

				if (chars_to_display > 0)
				{
					// new line is consumed to allow consistent curr_line increment
					// but it is not displayed (not a graph)
					std::string substr = text.substr(c, chars_to_display);
					if (substr[substr.size() - 1] == '\n')
						substr.resize(substr.size() - 1);

					if (!substr.empty())
					{
						XDrawString (dpy,
						             win,
						             gc,
						             0,
						             (curr_line + 1) * fsz,
						             substr.c_str(),
						             substr.size());
					}
				}

				c += chars_to_display;
				++curr_line;
			}
		} //KeyPress
	}

	return 0;
}
