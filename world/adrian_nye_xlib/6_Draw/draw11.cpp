/*
 *    Measuring the width of a text string.
 *    Drawing additional text relatively to original one.
 *
 *    XDrawImageString, XDrawString, XTextWidth
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


	char* title = (char*)"draw11 - XTextWidth";
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




	/* Select a nice font. */
	Font font;
	int fontret = 0;
	XFontStruct* fontinfos;
	char** fontlist = XListFontsWithInfo(dpy,
	                                     "*",
	                                     700,        // maxnames
	                                     &fontret,   // actual_count_return
	                                     &fontinfos);// info_return
	if(fontlist == NULL)
		return -1;


	int ascent=0, descent=0, lbearing=0, rbearing=0;
	XFontStruct* fontinfo = 0;
	for(int i=0; i < fontret; ++i)
	{
		XFontStruct* fs = &(fontinfos[i]);
		XCharStruct* cs = &(fs->max_bounds);
		int fsz = cs->ascent + cs->descent;
		if(fsz < 16 || fsz > 20)
			continue;
		const char* fname = fontlist[i];
		// -medium-  -normal-  -r-
		if(strstr(fname, "-medium-") == 0 ||
		   strstr(fname, "-normal-") == 0 ||
		   strstr(fname, "-r") == 0)
			continue;
		//found a Font
		font = XLoadFont(dpy, fname);    // load in the X server
		ascent = cs->ascent;
		descent= cs->descent;
		lbearing = cs->lbearing;
		rbearing = cs->rbearing;
		fontinfo = fs;
		break;
	}

	if(ascent == 0)
		return -1;


	XGCValues gcvalues;
	gcvalues.line_width = 1;
	gcvalues.foreground = BlackPixel(dpy, scrno);
	gcvalues.background = WhitePixel(dpy, scrno);
	gcvalues.font = font;   // equivalent of XSetFont
	unsigned long gcmask = GCLineWidth | GCForeground | GCBackground | GCFont;

	GC gc = XCreateGC(dpy,
	                  win,
	                  gcmask,
	                  &gcvalues);

	XMapWindow(dpy, win);


	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);
		if(event.type == Expose &&
		   event.xexpose.count == 0)
		{
			XClearWindow(dpy, win);

			const char* text = "extern int XDrawImageString(...)";
			XDrawImageString(dpy,
			                 win,
			                 gc,
			                 100, 100,
			                 text,
			                 strlen(text));

			/*    To mark on the screen/window where the string begins and ends
			      we need to measure the text width. */
			const char* beg ="begin ^";
			const char* end ="^ end";

			int begw = XTextWidth(fontinfo, beg, strlen(beg));
			XDrawImageString(dpy,
			                 win,
			                 gc,
			                 100-begw+lbearing, 100 + ascent + descent,
			                 beg,
			                 strlen(beg));

			int textw = XTextWidth(fontinfo, text, strlen(text));
			XDrawImageString(dpy,
			                 win,
			                 gc,
			                 100+textw-rbearing, 100 + ascent + descent,
			                 end,
			                 strlen(end));
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
	XUnloadFont(dpy, font);
	XFreeFontInfo(fontlist, fontinfos, fontret);

	XFreeGC(dpy, gc);
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}
