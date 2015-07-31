/*
 *    Cap. 7.5.2  Allocating Read/Write Colorcells for Overlays
 *    Exaple 7-7. Using XAllocColorCells() to allocate read/write colorcells
 *                for overlay plane.
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
	int depth_def = DefaultDepth(dpy, scrno);
	Colormap clrmap_def = DefaultColormap(dpy, scrno);


	int x = 10;
	int y = 10;
	int winwidth = scrwidth / 3;
	int winheight = scrheight * 3 / 4 ;
	int winborder = 1;

	unsigned long fgpixel, bgpixel, overlaypixel_1, overlaypixel_2;
	unsigned long overlay_plane_mask;
	const int MAX_COLORS = 2;
	const int MAX_PLANES = 1;
	const int MAX_CELLS = 4;        // MAX_COLORS * 2 ^ MAX_PLANES


	const char* clrname[] = {"Red", "Yellow", "Green", "Green"};
	XColor xcolors[MAX_CELLS];
	int ncolors = 4;
	unsigned long plane_masks[MAX_PLANES];
	unsigned long colors[MAX_COLORS];
	XVisualInfo visual_info;





	if(depth_def == 1)
	{
		/*    Must be StaticGray, use black and white    */
		bgpixel = WhitePixel(dpy, scrno);
		fgpixel = BlackPixel(dpy, scrno);
		printf("At depth=1 -> 2 ^ 1 = 2 colors maximum; fg=black bg=white\n");
	}
	else
	{
		/*
		  Looking for a visual that has RW permission on colorcells
		  to overwrite colors in the Colormap.
		  PseudoColor, DirectColor


		  PseudoColor: pixel is the index in (RW) colormap (e.g. colormap is read-write)
		  |-> GrayScale: inherited, (RW) colormap is gray shade
		  |-> StaticColor: inherited, (RO) colormap has predifined colors
		      |-> StaticGray: inherited, colormap's colors (r==g==b) gray shades

		  DirectColor: pixel is split in R/B/G and used as indexes in (RW)colormap
		  |-> TrueColor: similar as above, (RO) colormap has predifined colors
		*/

		visual_info.visual = NULL;
		if(!XMatchVisualInfo(dpy,
		                     scrno,
		                     depth_def,
		                     PseudoColor,
		                     &visual_info))
		{
			if(!XMatchVisualInfo(dpy,
			                     scrno,
			                     depth_def,
			                     DirectColor,
			                     &visual_info))
			{
				/* NoPseudoColor or DirectColor visual available at default
				   depth; some applications might try for a GrayScale visual
				   here if they can use gray to advantage, before giving
				   up and using black and white.
				*/
				fgpixel = BlackPixel(dpy, scrno);
				bgpixel = WhitePixel(dpy, scrno);
				printf("Did not match any PseudoColor or DirectColor visual info;"
				       " fg=black bg=white\n");
			}
		}

		if(visual_info.visual != NULL)
		{
			/* Got PseudoColor or DirectColor visual at default depth.
			   The visual we found is not necessarily the default visual,
			   and therefore it is not necessarily the one we used to create
			   out window; however, we now know for sure that color is
			   supported, so the following code will work (or fail in a
			   controlled way)
			*/

			if(!XAllocColorCells(dpy,
			                     clrmap_def,
			                     False,
			                     plane_masks,
			                     1,
			                     colors,
			                     2))
			{
				/* Cannot get enough read/write cells to overlay.
				   Try at least to get three colors.
				*/

				if(!XAllocColorCells(dpy,
				                     clrmap_def,
				                     False,
				                     plane_masks,
				                     0,
				                     colors,
				                     3))
				{
					/* Cannot even get that.
					   Give up and use black and white.
					*/

					fgpixel = BlackPixel(dpy, scrno);
					bgpixel = WhitePixel(dpy, scrno);
					printf("Cannot allocate color cells; XAllocColorCells\n");
					ncolors = 0;
				}
			}
			else
			{
				ncolors = 3;
			}
		}
	}


	/*    Allocated 3 or 4 colorcells successfully.
	      Now set their colors --- 3 and 4 are set to the same RGB values.
	*/
	if(ncolors > 0)
	{
		for(int i=0; i < ncolors; ++i)
		{
			if(!XParseColor(dpy,
			                clrmap_def,
			                clrname[i],
			                &xcolors[i]))
			{
				printf("XParseColor: color name %s is not in database\n",
				       clrname[i]);
				exit(-1);
			}

			xcolors[i].flags = DoRed | DoGreen | DoBlue;
		}

		printf("got RGB values\n");
		/*    Set pixel values in struct to the allocated ones.    */
		xcolors[0].pixel = colors[0];
		xcolors[1].pixel = colors[1];
		xcolors[2].pixel = colors[0] | plane_masks[0];
		xcolors[3].pixel = colors[1] | plane_masks[0];

		/*    This sets the color of the red/write cells.    */
		XStoreColors(dpy,
		             clrmap_def,
		             xcolors,
		             ncolors);
		printf("stored colors\n");

		fgpixel = xcolors[1].pixel;
		bgpixel = xcolors[0].pixel;

		if(ncolors == 4)
		{
			overlaypixel_1 = xcolors[2].pixel;
			overlaypixel_2 = xcolors[3].pixel;
			overlay_plane_mask = plane_masks[0];
		}
		else
		{
			/* This must be used as a normal color, not overlay. */
			overlaypixel_1 = xcolors[2].pixel;
		}
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
	gcvalues.foreground = fgpixel;
	gcvalues.background = bgpixel;
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
