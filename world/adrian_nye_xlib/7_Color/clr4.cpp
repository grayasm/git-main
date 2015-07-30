/*
 *    Colors:
 *      - allocating read-only colorcells
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


	int x = 10;
	int y = 10;
	int winwidth = scrwidth / 3;
	int winheight = scrheight * 3 / 4 ;
	int winborder = 1;

	/* Colors */
	const int MAX_COLORS = 3;
	int ncolors = 0;
	int colors[MAX_COLORS];

	/* This is just so we can print the visual class intelligibly. */
	static const char* visual_class[] = {
		"StaticGray",
		"GrayScale",
		"StaticColor",
		"PseudoColor",
		"TrueColor",
		"DirectColor"
	};

	static const char* name[] = {"Red", "Yellow", "Green"};

	/* Try to allocate colors for:
	   PseudoColor, TrueColor, DirectColor, StaticColor
	   Use black and white for:
	   StaticGray, GrayScale
	*/
	int default_depth = DefaultDepth(dpy, scrno);
	Visual* default_visual = DefaultVisual(dpy, scrno);
	Colormap default_cmap = DefaultColormap(dpy, scrno);
	unsigned long border_pixel = BlackPixel(dpy, scrno);
	unsigned long background_pixel = WhitePixel(dpy, scrno);
	unsigned long foreground_pixel = BlackPixel(dpy, scrno);
	const char* progname = argv[0];

	if(default_depth == 1)
	{
		/* Must be StaticGray, use black and white */
		border_pixel = BlackPixel(dpy, scrno);
		background_pixel = WhitePixel(dpy, scrno);
		foreground_pixel = BlackPixel(dpy, scrno);
	}
	else
	{
		int i=5;
		XVisualInfo visual_info;
		XColor exact_def;

		while(!XMatchVisualInfo(dpy,
		                        scrno,
		                        default_depth,
		                        /* visual class */ i--,
		                        &visual_info))
		{
		} // while
		printf("%s: found a %s class visual at default depth.\n",
		       progname, visual_class[++i]);

		if(i < StaticColor)
		{
			/* Color visual classes are 2 to 5.
			   No color visual available at default depth;
			   some applications might call XMatchVisualInfo
			   here to try for a GrayScale visual if they
			   can use gray to advantage, before giving up
			   and using black and white.
			*/
			border_pixel = BlackPixel(dpy, scrno);
			background_pixel = WhitePixel(dpy, scrno);
			foreground_pixel = BlackPixel(dpy, scrno);
		}
		else
		{
			/* Otherwise, got a color visual at default depth.
			   The visual we found is not necessarily the default
			   visual, and therefore it is not necessarily the one
			   we used to crate our window; however, we now know
			   for sure that color is supported, so the following
			   code will work (or fail in a controlled way).
			   Let's check just out of curiosity:
			*/
			if(visual_info.visual != default_visual)
			{
				printf("%s: %s class visual at default depth\n",
				       progname, visual_class[i]);
				printf("is not default visual! Continuing anyway ...\n");
			}
			for(i = 0; i < MAX_COLORS; i++)
			{
				printf("allocating %s\n", name[i]);
				if(!XParseColor(dpy,
				                default_cmap,
				                name[i],
				                &exact_def))
				{
					printf("%s: color name %s not in database",
					       progname, name[i]);
					exit(-1);
				}
				printf("The RGB values from the database are %d, %d, %d\n",
				       exact_def.red, exact_def.green, exact_def.blue);
				if(!XAllocColor(dpy,
				                default_cmap,
				                &exact_def))
				{
					printf("All colorcells allocated and\n");
					printf("no matching cell found.\n");
					exit(-1);
				}
				printf("The RGB values actually allocated are %d, %d, %d\n",
				       exact_def.red, exact_def.green, exact_def.blue);
				colors[i] = exact_def.pixel;
				ncolors++;
			}
			printf("%s: allocated %d read-only color cells\n",
			       progname, ncolors);
			border_pixel = colors[0];
			background_pixel = colors[1];
			foreground_pixel = colors[2];
		}
	}


	Window win = XCreateSimpleWindow(dpy,
	                                 RootWindow(dpy, scrno),
	                                 x, y,
	                                 winwidth, winheight,
	                                 winborder,
	                                 BlackPixel(dpy, scrno),
	                                 WhitePixel(dpy, scrno));


	char* title = (char*)"color - 7.4 Allocating read-only colorcells";
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
	gcvalues.foreground = foreground_pixel;
	gcvalues.background = background_pixel;
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
