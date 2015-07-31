/*
 *  Cap. 7.8.4  Creating and using a Standard Colormap
 *  Example 7-12  Code to create and use XA_RGB_BEST_MAP
 *
 *
 */


// Code fails with error:
/*
  RGB_BEST_MAP colormap property not set.
  X Error of failed request:  BadColor (invalid Colormap parameter)
  Major opcode of failed request:  1 (X_CreateWindow)
  Resource id in failed request:  0x85d4cab0
  Serial number of failed request:  8
  Current serial number in output stream:  12
  [mihk@localhost: 7_Color]$

 */


#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

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


	const int USE_DEFAULT_COLORMAP = 1;
	const int USE_STANDARD_COLORMAP = 0;
	XStandardColormap* best_map_info;
	XColor* exact_defs;
	XSetWindowAttributes attrib;
	unsigned long attribmask;
	int i,j,k,l;
	int ncells;
	XVisualInfo* vlist, vinfo_template, *v;
	int num_vis;
	int count;
	Visual* visual;
	int strategy = USE_STANDARD_COLORMAP;
	unsigned long fgpixel, bgpixel;


	visual = DefaultVisual(dpy, scrno);
	if(XGetRGBColormaps(dpy,
	                    RootWindow(dpy, scrno),
	                    &best_map_info,
	                    &count,
	                    XA_RGB_BEST_MAP) == 0)
	{
		printf("%s: RGB_BEST_MAP colormap property not set.\n", argv[0]);

		/* Give up standard colormaps; use one of the
		   basic color strategies
		*/
	}
	else if(best_map_info->colormap)
	{
		/* Someone else created the map we need; make sure
		   it's valid, then we'll use it below.
		*/

		if(best_map_info->red_max == 0)
		{
			printf("%s: RGB_BEST_MAP colormap property is set\n", argv[0]);
			printf("but is missing data.\n");
			strategy = USE_DEFAULT_COLORMAP;
		}
		else
		{
			printf("stnd colormap ID: %d\n", best_map_info->colormap);
			attrib.colormap = best_map_info->colormap;
		}
	}
	else if(best_map_info->visualid == 0)
	{
		printf("%s: standard colormap property is set\n", argv[0]);
		printf("but is missing data.\n");

		/* Some systems define the property but don't
		   place any data in them; this is a server bug,
		   but we'll check for it anyway.
		   Fall back on a basic color strategy
		*/
		strategy = USE_DEFAULT_COLORMAP;
	}
	else
	{
		/* Got information, but the described colormap
		   has not been created yet; create it and
		   allocate all cells read/write.
		   XCreateColormap requires a visual argument
		   (pointer to a Visual structure); however, the
		   XStandardColormap structure returns a VisualID,
		   which might not be the default visual;
		   Converting between these 2 is painful.
		*/

		vlist = XGetVisualInfo(dpy,
		                       VisualNoMask,
		                       &vinfo_template,
		                       &num_vis);
		for(v = vlist; v < vlist + num_vis; ++v)
		{
			if(v->visualid == best_map_info->visualid)
			{
				visual = v->visual;
				break;
			}
		}

		best_map_info->colormap = XCreateColormap(dpy,
		                                          RootWindow(dpy, scrno),
		                                          visual,
		                                          AllocAll);

		if(best_map_info->colormap == DefaultColormap(dpy, scrno))
		{
			printf("%s: hardware colormap is immutable\n", argv[0]);
			printf("cannot create new colormap\n");
		}
		attrib.colormap = best_map_info->colormap;
		ncells = best_map_info->base_pixel +
			((best_map_info->red_max + 1) *
			 (best_map_info->green_max + 1) *
			 (best_map_info->blue_max + 1));
		exact_defs = (XColor*) ::calloc(sizeof(XColor), ncells);

		/* Permute the levels of red, green and blue. */
		l = best_map_info->base_pixel;
		for(i = 0; i < best_map_info->blue_max; ++i)
		{
			for(j = 0; j < best_map_info->blue_max; ++j)
			{
				for(k = 0; k < best_map_info->blue_max; ++k)
				{
					exact_defs[l].red = 0xffff * k / best_map_info->red_max;
					exact_defs[l].green=0xffff * j / best_map_info->green_max;
					exact_defs[l].blue =0xffff * i / best_map_info->blue_max;
					++l;
				}
			}
		}

		XStoreColors(dpy,
		             best_map_info->colormap,
		             exact_defs,
		             ncells);

		/* If to be used in a window not created with the default visual,
		   must create the window first and use instead of RootWidow in
		   this call; here we assume the default visual.
		*/

		XSetRGBColormaps(dpy,
		                 RootWindow(dpy, scrno),
		                 best_map_info,
		                 count,
		                 XA_RGB_BEST_MAP);
	}

	if(strategy == USE_STANDARD_COLORMAP)
	{
		/* We must not have called get_colors above,
		   must be using standard colormaps strategy.
		   Note that we act like we have already allocated pixel
		   values, even though actually another client did.
		*/

		bgpixel = best_map_info->base_pixel +
			(best_map_info->red_max * best_map_info->red_mult) +
			(best_map_info->green_max * best_map_info->green_mult) +
			(best_map_info->blue_max * best_map_info->blue_mult);
		attribmask = CWBackPixel | CWColormap;
		fgpixel = (best_map_info->green_max * best_map_info->green_mult / 2) +
			best_map_info->base_pixel;
	}

	Window win = XCreateWindow(dpy,
	                           RootWindow(dpy, scrno),
	                           x, y,
	                           winwidth, winheight,
	                           winborder,
	                           DefaultDepth(dpy, scrno),
	                           InputOutput,
	                           visual,
	                           attribmask,
	                           &attrib);



	char* title = (char*)"color - code to match visuals";
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
