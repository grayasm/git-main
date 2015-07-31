/*
 * Cap. 7.5.3 Using XAllocColorPlanes
 * Exmaple 7-8  Using XAllocColorPlanes to allocate colorcells for DirectColor
 *
 * DirectColor class of XVisualInfo means we have read-write access to Colormap
 *
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	Display* dpy = XOpenDisplay(NULL);
	if(!dpy) return -1;

	int scrno = DefaultScreen(dpy);
	int scrwidth = DisplayWidth(dpy, scrno);
	int scrheight = DisplayHeight(dpy, scrno);
	int depth_def = DefaultDepth(dpy, scrno);
	Colormap clrmap_def = DefaultColormap(dpy, scrno);


	int x = 10;
	int y = 10;
	int winwidth = scrwidth / 3;
	int winheight = scrheight * 3 / 4 ;
	int winborder = 1;


	/* To make this sample work, we need to get a visual info with class
	   DirectColor that has RW access to Colormap colors.

	   Usefull as example for XAllocColorPlanes.
	*/
	const int PIXELS = 256;
	int contig = False;                 // Noncontiguous planes
	unsigned long pixels[PIXELS];       // Return of pixel values
	unsigned int ncolors = PIXELS;      // Independent pixel values allocate
	XColor xcolors[2048];               // PIXELS * 2 ^ maxplanes
	unsigned int nreds = 3, ngreens = 3, nblues = 2;  // Number of planes
	                                    // to allocate for each primary
	unsigned long red_mask, green_mask, blue_mask;
	Status status;

	while((status = XAllocColorPlanes(dpy,
	                                  clrmap_def,
	                                  contig,
	                                  pixels,
	                                  ncolors,
	                                  nreds,
	                                  ngreens,
	                                  nblues,
	                                  &red_mask,
	                                  &green_mask,
	                                  &blue_mask)) == 0)
	{
		/* Make contig False if it was True;
		   reduce value of ncolors;
		   reduce value of nreds, ngreens,nblues;
		   try allocating new map;
		   break when give up;
		*/
		break;
	}

	if(status == 0)
	{
		printf("%s: cannot allocate requested colorcells\n", argv[0]);
		exit(-1);
	}

	/* Define desired colors. */
	while((status = XStoreColors(dpy,
	                             clrmap_def,
	                             xcolors,
	                             ncolors)) == 0)
	{
		printf("%s: cannot store colors\n", argv[0]);
		exit(-1);
	}


	Window win = XCreateSimpleWindow(dpy,
	                                 RootWindow(dpy, scrno),
	                                 x, y,
	                                 winwidth, winheight,
	                                 winborder,
	                                 BlackPixel(dpy, scrno),
	                                 WhitePixel(dpy, scrno));


	char* title = (char*)"color - allocate colorcells for overlay plane";
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

	XMapWindow(dpy, win);


	XGCValues gcvalues;
	gcvalues.line_width = 1;
	gcvalues.foreground = xcolors[0].pixel;
	gcvalues.background = WhitePixel(dpy, scrno);
	gcvalues.font = XLoadFont(dpy, "fixed");
	unsigned long gcmask = GCLineWidth | GCForeground | GCBackground | GCFont;

	GC gc = XCreateGC(dpy,
	                  win,
	                  gcmask,
	                  &gcvalues);



	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);
		if(event.type == Expose &&
		   event.xexpose.count == 0)
		{
			XDrawString(dpy, win, gc, 20, 20, "TEXT", 4);
			XFillRectangle(dpy, win, gc, 40, 40, winwidth-80, winheight-80);
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


	XFreeGC(dpy, gc);
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}
