/*
 *    10.1.2 Text representation in an Internationalized Application
 *
 *    Let's assume we have a resource with non-english text and we have to
 *    display messages from this resource.
 *    See int1.cpp for details about the text resource.
 *
 *    The shit is not working at all!!! Crap
 */


#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <nl_types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>



int main(int argc, char **argv)
{
	// X/Open Message Catalog
	printf("\nopen catalog: %s.msg\n", argv[0]);
	char catpath[250];
	strcpy(catpath, argv[0]);
	strcat(catpath, ".msg");

	nl_catd catd = catopen(catpath, 0);
	if(catd == (nl_catd)-1)
	{
		printf("Cannot open catalog\n");
		return 1;
	}


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
	long event_mask =
		ExposureMask |
		ButtonPressMask |
		StructureNotifyMask;

	/* Select all events for our top window. */
	XSelectInput(dpy, win, event_mask);


	/* Select a nice font */
	int fontret = 0;
	XFontStruct* fontinfos;
	char** fontlist = XListFontsWithInfo(dpy,
	                                     "*",
	                                     1200,        // maxnames
	                                     &fontret,    // actual_count_return
	                                     &fontinfos); // info_return
	if(fontlist == NULL)
		return -1;



	/*  R5 bases its new text output rutines on a new Xlib abstraction, XFontSet.
	    The new R5 functions use an XFontSet rather than an XFontStruct or a
	    font specified in a graphics context.
	    The drawing and measuring routines interpret text in the encoding of the
	    locale of the fontset, and correctly map wide or multi-byte characters
	    to the corresponding font gplyphs.
	*/

	/* 1=Latin  2=Russian  3=Japanese */
	int set = 2;
	Font     font;
	XFontSet fontSet;


	for(int i=0; i < fontret; ++i)
	{
		XFontStruct* fs = &(fontinfos[i]);
		XCharStruct* cs = &(fs->max_bounds);
		int fsz = cs->ascent + cs->descent;
		if(fsz < 12 || fsz > 14)
			continue;
		const char* fname = fontlist[i];
		// -medium-  -normal-  -r-
		if(strstr(fname, "-medium-") == 0 ||
		   strstr(fname, "-normal-") == 0 ||
		   strstr(fname, "-r-")      == 0)
			continue;

		printf("\n%s", fname);

		if(set == 1 && strstr(fname, "iso8859-1") != 0)
			; // allow
		else if(set == 2 && strstr(fname, "koi8-r") != 0)
			; // allow
		else
			continue;


		printf("\nFont: %s", fname);
		font = XLoadFont(dpy, fname);

		// $ localectl list-locales
		// setlocale(LC_ALL, "en_US.UTF-8");
		setlocale(LC_ALL, "ru_RU.koi8r");

		if (!XSupportsLocale())
			printf("\nX does not support the locale.");

		if (XSetLocaleModifiers("") == NULL)
			printf("\nX cannot set locale modifiers");


		char **missing_charsets;
		int num_missing_charsets;
		char *default_string;

		fontSet = XCreateFontSet(dpy,
		                         fname,
		                         &missing_charsets,
		                         &num_missing_charsets,
		                         &default_string);

		if (num_missing_charsets > 0)
		{
			printf("\nThe following charsets are missing:");
			for (int i=0; i < num_missing_charsets; ++i)
			{
				printf("\n%s", missing_charsets[i]);
			}
			XFreeStringList(missing_charsets);
			num_missing_charsets = 0;
		}

		break;
	}


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

	int id=1;
	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);

		if (event.type == Expose)
		{
			XExposeEvent* xexpose = &(event.xexpose);
			if (xexpose->count == 0)
			{
				XClearWindow(dpy, win);
				const char* msg = catgets(catd, set, id, "#translation error!");
				int len = strlen(msg);
				printf("\nset=%d  id=%d  [%d][%s]", set, id, len, msg);

				XmbDrawImageString(dpy, win, fontSet, gc, 50, 100, msg, len);
			}
		}

		if (event.type == ConfigureNotify)
		{
			XClearWindow(dpy, win);
			const char* msg = catgets(catd, set, id, "#translation error!");
			int len = strlen(msg);
			printf("\nset=%d  id=%d  [%d][%s]", set, id, len, msg);

			XmbDrawImageString(dpy, win, fontSet, gc, 50, 100, msg, len);
		}


		if (event.type == ButtonPress)
		{
			++id;
			if (id >= 4)
			{
				id = 1;
			}
		}
	}


	XFreeFontSet(dpy, fontSet);

	XUnmapWindow(dpy, win);
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	int ret = catclose(catd);
	printf("\n\tCatalog closed %s\n\n", (ret == 0 ? "OK" : "with error!"));

	return 0;
}
