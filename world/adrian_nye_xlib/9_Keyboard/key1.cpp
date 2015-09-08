/*
 * 
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
		if(fsz < 12 || fsz > 14)
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
	int chars = (int) text.size(); // safety at boundary
	int chars_per_line = (int) floor(winwidth / rbearing);
	int total_lines = (int) ceil(chars / chars_per_line);

	// Process key events
	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);

		if (event.type == ConfigureNotify)
		{
			
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

			// cursor changing position
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

			// append buffer to existing text
			else if (XK_space <= keysym && keysym <= XK_asciitilde)
			{
				text += buff;
				chars = (int) text.size();
				chars_per_line = (int) floor(winwidth / rbearing);
				total_lines = (int) ceil((float)chars / (float)chars_per_line);
			}


			// draw text
			for (int i=0; i < total_lines; ++i)
			{
				int chars_to_display = chars_per_line;
				if (chars - (i+1)*chars_per_line < 0)
					chars_to_display = chars - i*chars_per_line;

				std::string substr = text.substr(i * chars_per_line,
				                                 chars_to_display);

				XDrawString (dpy,
				             win,
				             gc,
				             0,
				             (i+1) * fsz,
				             substr.c_str(),
				             substr.size());
			}
		}
	}

	return 0;
}
