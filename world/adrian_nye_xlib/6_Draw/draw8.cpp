/*
 *    XListFonts
 *
 *    Ask installed fonts and draw their names in the window.
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>



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
	int winwidth = scrwidth / 3;
	int winheight = scrheight / 2;
	int winborder = 1;

	Window win = XCreateSimpleWindow(dpy,
	                                 RootWindow(dpy, scrno),
	                                 x, y,
	                                 winwidth, winheight,
	                                 winborder,
	                                 BlackPixel(dpy, scrno),
	                                 WhitePixel(dpy, scrno));


	char* title = (char*)"draw8 - XListFonts";
	XTextProperty titleprop;
	XStringListToTextProperty(&title, 1, &titleprop);
	XSetWMProperties(dpy,
	                 win,
	                 &titleprop,
	                 NULL,
	                 argv,
	                 argc,
	                 NULL,
	                 NULL,
	                 NULL);

	XSelectInput(dpy,
	             win,
	             ExposureMask |
	             KeyPressMask |
	             ButtonPressMask |
	             StructureNotifyMask);


	/* Create GC without Font.
	   We wil set all fonts 1 at a time and draw a string with it. */
	XGCValues gcvalues;
	gcvalues.line_width = 1;
	gcvalues.foreground = BlackPixel(dpy, scrno);
	gcvalues.background = WhitePixel(dpy, scrno);
	unsigned long gcmask = GCLineWidth | GCForeground | GCBackground;

	GC gc = XCreateGC(dpy,
	                  win,
	                  gcmask,
	                  &gcvalues);

	XMapWindow(dpy, win);


	/* Ask what fonts are installed. */
	const int MAXFONTS = 50;
	Font fonts[MAXFONTS];
	int fontret = 0;
	char** fontlist = XListFonts(dpy,
	                             "*",
	                             MAXFONTS,   // maxnames
	                             &fontret);  // actual_count_return

	const int fontcount = std::min(MAXFONTS, fontret);


	/* Fonts are stored in the server, shared among programs, never duplicated,
	   and alive as long as a program uses them. When a Font is not referenced
	   anymore it is discarded.
	*/
	for(int i=0; i < fontcount; ++i)
		fonts[i] = XLoadFont(dpy, fontlist[i]);



	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);
		if(event.type == Expose &&
		   event.xexpose.count == 0)
		{
			XClearWindow(dpy, win);


			/* Draw current font name. The vertical displacement is
			   not calculated. Hopefully 20 pixels are enough. */

			for(int i=0; i < fontcount; ++i)
			{
				const char* fontname = fontlist[i];

				XSetFont(dpy,
				         gc,
				         fonts[i]);

				XDrawString(dpy,
				            win,
				            gc,
				            50, i*20,
				            fontname,
				            strlen(fontname));
			}
		}



		if(event.type == ConfigureNotify)
		{
			if(event.xconfigure.window == win)
			{
				x = event.xconfigure.x;
				y = event.xconfigure.y;
				winwidth = event.xconfigure.width;
				winheight = event.xconfigure.height;
			}
		}
	}

	return 0;
}
