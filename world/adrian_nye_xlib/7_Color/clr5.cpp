/*
 *    Cap. 7.5.1 Allocating Read/Write Colorcells for Dynamic Colors
 *    Exaple 7-5. Allocating read/write colorcells for dynamic colors
 *
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


	int x = 10;
	int y = 10;
	int winwidth = scrwidth / 3;
	int winheight = scrheight * 3 / 4 ;
	int winborder = 1;

	unsigned long border_pixel;
	unsigned long foreground_pixel;
	unsigned long background_pixel;
	const int MAX_COLORS = 3;
	const char* name[] = {"Red", "Yellow", "Green"};
	int default_depth = DefaultDepth(dpy, scrno);
	Visual* default_visual = DefaultVisual(dpy, scrno);
	Colormap default_cmap = DefaultColormap(dpy, scrno);

	if(default_depth == 1)
	{
		/*    Must be StaticGray, use black and white.    */
		border_pixel = BlackPixel(dpy, scrno);
		background_pixel = WhitePixel(dpy, scrno);
		foreground_pixel = BlackPixel(dpy, scrno);

		printf("default depth is 1, use StaticGray Colormap\n");
	}
	else
	{
		XVisualInfo visual_info;
		unsigned long plane_masks[1];
		int ncolors = MAX_COLORS;
		unsigned long colors[MAX_COLORS];
		XColor exact_defs[MAX_COLORS];


		if(!XMatchVisualInfo(dpy,
		                     scrno,
		                     default_depth,
		                     PseudoColor,
		                     &visual_info))
		{
			printf("XMatchVisualInfo(PseudoColor) is 0\n");

			if(!XMatchVisualInfo(dpy,
			                     scrno,
			                     default_depth,
			                     DirectColor,
			                     &visual_info))
			{
				/*    No PseudoColor visual available at default_depth;
				      some applications might try for a GrayScale
				      visual here if they can use gray to advantage,
				      before giving up and using black and white.
				*/
				border_pixel = BlackPixel(dpy, scrno);
				background_pixel = WhitePixel(dpy, scrno);
				foreground_pixel = BlackPixel(dpy, scrno);

				printf("XMatchVisualInfo(DirectColor) is 0\n");
			}
		}
		else
		{
			/*    Got PseudoColor or DirectColor visual at default_depth.
			      The visual we found is not necessarily the default
			      visual and therefore it is not necessarily the one
			      we used to create our window; however, we now know
			      for sure that color is supported, so the following
			      code will work (or fail in a controlled way).
			      Allocate as many cells as we can.
			*/

			while(1)
			{
				if(XAllocColorCells(dpy,
				                    default_cmap,
				                    False,
				                    plane_masks,
				                    /* nplanes */ 0,
				                    colors,
				                    ncolors))
					break;

				ncolors--;
				if(ncolors == 0)
				{
					printf("basic: couldn't allocate read/write colors\n");
					exit(-1);
				}
			} // while


			printf("basic: allocated %d read/write colors cells\n", ncolors);

			for(int i=0; i < ncolors; ++i)
			{
				if(!XParseColor(dpy,
				                default_cmap,
				                name[i],
				                &exact_defs[i]))
				{
					printf("basic: color name %s not in database", name[i]);
					exit(-1);
				}

				/*    Set pixel value in struct to the allocated one.    */
				exact_defs[i].pixel = colors[i];
				exact_defs[i].flags = DoRed | DoGreen | DoBlue;
			}

			/*    This sets the color of read/write cell.    */
			XStoreColors(dpy,
			             default_cmap,
			             exact_defs,
			             ncolors);
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


	char* title = (char*)"color - Allocating read-write colorcells"
		" for dynamic colors";
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
