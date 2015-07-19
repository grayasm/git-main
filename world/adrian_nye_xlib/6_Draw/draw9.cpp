/*
 *    XListFontsWithInfo, XFreeFontInfo
 *
 *    Ask installed fonts on the system.
 *    Iterate each font, set it, draw with it, and free all resource on exit.
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


	char* title = (char*)"draw9 - XListFontsWithInfo";
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
	const int MAXFONTS = 25;
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

			/* Printing XFontStruct for each Font. */
			for(int i=0; i < fontcount; ++i)
			{
				if(i > 0) y += 10; // vertical displacement for text

				XSetFont(dpy, gc, fonts[i]);

				XFontStruct* fi = &(fontinfos[i]);
				int fsz = fi->ascent + fi->descent;

				std::stringstream strm1, strm2, strm3, strm4;
				strm1 << fontlist[i];
				XDrawString(dpy, win, gc, 20, (y += fsz), strm1.str().c_str(), strm1.str().size());

				strm2 << " direction=" << fi->direction;
				strm2 << " min_char=" << fi->min_char_or_byte2;
				strm2 << " max_char=" << fi->max_char_or_byte2;
				strm2 << " min_byte=" << fi->min_byte1;
				strm2 << " max_byte=" << fi->max_byte1;
				strm2 << " all_exist=" << fi->all_chars_exist;
				strm2 << " def_char=" << fi->default_char;
				strm2 << " n prop=" << fi->n_properties;
				XFontProp* fp = fi->properties; // XFontProp array
				XCharStruct* minbs = &(fi->min_bounds);
				XCharStruct* maxbs = &(fi->max_bounds);
				XCharStruct* chari = fi->per_char; // XCharStruct array
				strm2 << " log. ascent=" << fi->ascent;
				strm2 << " log. descent=" << fi->descent;

				XDrawString(dpy, win, gc, 20, (y += fsz), strm2.str().c_str(), strm2.str().size());

				strm3 << " min bounds, lbearing:" << minbs->lbearing;
				strm3 << " rbearing:" << minbs->rbearing;
				strm3 << " width:" << minbs->width;
				strm3 << " ascent:" << minbs->ascent;
				strm3 << " descent:" << minbs->descent;
				XDrawString(dpy, win, gc, 20, (y += fsz), strm3.str().c_str(), strm3.str().size());

				strm4 << " max bounds, lbearing:" << maxbs->lbearing;
				strm4 << " rbearing:" << maxbs->rbearing;
				strm4 << " width:" << maxbs->width;
				strm4 << " ascent:" << maxbs->ascent;
				strm4 << " descent:" << maxbs->descent;
				XDrawString(dpy, win, gc, 20, (y += fsz), strm4.str().c_str(), strm4.str().size());
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
