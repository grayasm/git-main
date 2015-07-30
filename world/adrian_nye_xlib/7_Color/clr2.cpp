/*
 *    Colors:
 *    Getting a sense of:
 *    struct:    Visual
 *    struct:    XVisualInfo
 *    method:    XGetVisualInfo
 *    method:    XMatchVisualInfo
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <stdio.h>
#include <stdlib.h>



const char* class2string(int);

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



	Window win = XCreateSimpleWindow(dpy,
	                                 RootWindow(dpy, scrno),
	                                 x, y,
	                                 winwidth, winheight,
	                                 winborder,
	                                 BlackPixel(dpy, scrno),
	                                 WhitePixel(dpy, scrno));


	char* title = (char*)"color ";
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

	/*    Asking the default Visual, and printf the members.   */
	Visual* visual = DefaultVisual(dpy, scrno);
	VisualID visualid = visual->visualid;
	int visualclass = visual->c_class;
	unsigned long red_mask   = visual->red_mask;
	unsigned long green_mask = visual->green_mask;
	unsigned long blue_mask = visual->blue_mask;
	int bits_per_rgb = visual->bits_per_rgb;
	int map_entries = visual->map_entries;

	printf("visual (ptr) = %x\n", visual);
	printf("visualid     = %d\n", visualid);
	printf("visual class = %d\n", visualclass);

	/*    class type is defined as follows:

	      PseudoColor: pixel is the index in (RW) colormap (e.g. colormap is read-write)
	      |-> GrayScale: inherited, (RW) colormap is gray shade
	      |-> StaticColor: inherited, (RO) colormap has predifined colors
	          |-> StaticGray: inherited, colormap's colors (r==g==b) gray shades

	      DirectColor: pixel is split in R/B/G and used as indexes in (RW)colormap
	      |-> TrueColor: similar as above, (RO) colormap has predifined colors

	*/
	switch(visualclass)
	{
	case StaticGray: printf("visual class = StaticGray\n"); break;
	case StaticColor: printf("visual class = StaticColor\n"); break;
	case TrueColor: printf("visual class = TrueColor\n"); break;
	case GrayScale: printf("visual class = GrayScale\n"); break;
	case PseudoColor: printf("visual class = PseudoColor\n"); break;
	case DirectColor: printf("visual class = DirectColor\n"); break;
	default: printf("visual class = Unidentified\n"); break;
	}
	printf("red_mask     = %x\n", red_mask);
	printf("green_mask   = %x\n", green_mask);
	printf("blue_mask    = %x\n", blue_mask);
	printf("bits_per_rgb = %d\n", bits_per_rgb);
	printf("map_entries  = %d\n", map_entries);




	/*    XVisualInfo structure and related methods.

	      Ask all visuals for this screen with depth 8 (e.g. 2 ^ 8 = 256 colors)
	      Most probably these are gray shades. Let's see what comes out.
	 */
	XVisualInfo vinfo_template;
	vinfo_template.screen = scrno;
	vinfo_template.depth = 8;
	int nitems_return;
	long vinfo_mask = VisualScreenMask;
	/*                VisualNoMask
	                  VisualIDMask
	                  VisualScreenMask
	                  VisualDepthMask
	                  VisualClassMask
	                  VisualRedMaskMask
	                  VisualGreenMaskMask
	                  VisualBlueMaskMask
	                  VisualColormapSizeMask
	                  VisualBitsPerRGBMask
	                  VisualAllMask
	*/


	XVisualInfo* visuallist = XGetVisualInfo(dpy,
	                                         vinfo_mask,
	                                         &vinfo_template,
	                                         &nitems_return);

	printf("Visuals existing for this screen = %d\n", nitems_return);
	printf("Listing all XVisualInfo returned by XGetVisualInfo\n");

	for(int i=0; i < nitems_return; ++i)
	{
		XVisualInfo* vinfo = &(visuallist[i]);
		printf("%4d) depth=%3d class=%s\n",
		       i+1,
		       vinfo->depth,
		       class2string(vinfo->c_class));
	}

	XFree(visuallist);



	/*    XMatchVisualInfo

	      Can use this method with an iteration through
	      different depths and clases.
	 */
	printf("Using XMatchVisualInfo to guess a valid visual\n");

	for(int i=1; i <= 32; ++i) // depth [1,32]
	{
		int j[6] = { StaticGray, // class
		             StaticColor,
		             TrueColor,
		             GrayScale,
		             PseudoColor,
		             DirectColor };

		XVisualInfo  vinfo;
		for(int k=0; k < 6; ++k) // class [0,5]
		{
			if(XMatchVisualInfo(dpy,
			                    scrno,
			                    i,
			                    j[k],
			                    &vinfo))
			{
				printf("Match visual: depth=%d class=%s\n",
				       vinfo.depth,
				       class2string(vinfo.c_class));
			}
		}
	}


	/*    End of test.    */

	XGCValues gcvalues;
	gcvalues.line_width = 1;
	gcvalues.foreground = 0xff0000;
	gcvalues.background = 0x101010;
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


const char*  class2string(int visualclass)
{
	switch(visualclass)
	{
	case StaticGray: return "StaticGray";
	case StaticColor: return "StaticColor";
	case TrueColor: return "TrueColor";
	case GrayScale: return "GrayScale";
	case PseudoColor: return "PseudoColor";
	case DirectColor: return "DirectColor";
	default: return "visual class is undefined";
	}
}
