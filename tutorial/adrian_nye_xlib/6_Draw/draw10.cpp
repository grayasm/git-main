/*
 *    Select from all installed fonts on the system a Font that is appropriate
 *    for writing something on the screen.
 *    Font must be: normal, ascent+descent between 14,24  medium, -r- regular
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <string>
#include <sstream>


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


	char* title = (char*)"draw10 - select some nice fonts";
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
	const int MAXFONTS = 700;
	Font fonts[MAXFONTS];
	int fontret = 0;
	XFontStruct* fontinfos;
	char** fontlist = XListFontsWithInfo(dpy,
	                                     "*",
	                                     MAXFONTS,   // maxnames
	                                     &fontret,   // actual_count_return
	                                     &fontinfos);// info_return

	if(fontlist == NULL)
		return -1;

	const int fontcount = std::min(MAXFONTS, fontret);

	/* Load all fonts in the X server for now. */
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

			int y=50;

			/* Print only nice fonts. */
			const int wantmin = 14, wantmax = 20;
			for(int i=0; i < fontcount; ++i)
			{
				XFontStruct* fi = &(fontinfos[i]);
				int fsz = fi->ascent + fi->descent;

				if(fsz < wantmin || fsz > wantmax)
					continue;

				const char* fontname = fontlist[i];
				const char* medium = "-medium-";
				const char* normal = "-normal-";
				const char* regular = "-r-";
				const char* mono = "mono";

				if(strstr(fontname, medium) == 0)
					continue;

				if(strstr(fontname, normal) == 0)
					continue;


				if(strstr(fontname, regular) == 0)
					continue;

				//if(strstr(fontname, mono) == 0)
				//	continue;

				XSetFont(dpy, gc, fonts[i]);
				XDrawString(dpy, win, gc, 20, y, fontname, strlen(fontname));
				y += fsz;
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

		if(event.type == ButtonPress)
		{
			break;
		}
	}

	/* Exit */
	for(int i=0; i < fontcount; ++i)
		XUnloadFont(dpy, fonts[i]);
	XFreeFontInfo(fontlist, fontinfos, fontret);

	XFreeGC(dpy, gc);
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}
