/*
 *    Colors: here we change the defined red,green,blue values for few pixel
 *            indexes in a Colormap.
 *
 *    The steps are:
 *    1) find a visual info that allows changing of colors (Read-Write)
 *       this can be identified by the class type: PseudoColor,DirectColor, etc
 *    2) create a new Colormap with all colorcells allocated; AllocAll
 *    3) store desired red,green,blue at the indexes we decide to; XStoreColors
 *    3) set pixels for GC; foreground and background
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_visual_info(XVisualInfo* vinfo);
void print_visual(Visual* visual);
const char*  class2string(int visualclass);


int main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	Display* dpy = XOpenDisplay(NULL);
	if(!dpy) return -1;

	int scrno = DefaultScreen(dpy);
	int scrwidth = DisplayWidth(dpy, scrno);
	int scrheight = DisplayHeight(dpy, scrno);
	int depth = DefaultDepth(dpy, scrno);
	Colormap clrmap_def = DefaultColormap(dpy, scrno);


	int x = 10;
	int y = 10;
	int winwidth = scrwidth / 3;
	int winheight = scrheight * 3 / 4 ;
	int winborder = 1;




	/*    Again here a description of the XVisualInfo.c_class or
	      Visual.c_class type.

	      PseudoColor: pixel is the index in (RW) colormap (e.g. colormap is read-write)
	      |-> GrayScale: inherited, (RW) colormap is gray shade
	      |-> StaticColor: inherited, (RO) colormap has predifined colors
	          |-> StaticGray: inherited, (R0) colormap's colors (r==g==b) gray shades

	      DirectColor: pixel is split in R/B/G and used as indexes in (RW)colormap
	      |-> TrueColor: similar as above, (RO) colormap has predifined colors

	*/


	/*    Search for a Visual (XVisualInfo->Visual) that allows changing the
	      values of the colorcells. See above (RW) Colormap.
	      From previous tests for a multicolor modern screen I get only
	      DirectColor and TrueColor classes with 24 and 32 bits per pixel.
	 */
	XVisualInfo vinfo_template;
	vinfo_template.screen = scrno;
	vinfo_template.depth = 24;
	vinfo_template.c_class = DirectColor;
	int nitems_return;
	long vinfo_mask = VisualScreenMask | VisualDepthMask | VisualClassMask;
	XVisualInfo* visuallist = XGetVisualInfo(dpy,
	                                         vinfo_mask,
	                                         &vinfo_template,
	                                         &nitems_return);
	printf("%d visuals found for screen=%d depth=%d class=DirectColor\n",
	       nitems_return,
	       scrno,
	       vinfo_template.depth);

	if(nitems_return == 0)
		return -1;

	print_visual_info(&(visuallist[0]));
	print_visual(visuallist[0].visual);

	Colormap clrmap = XCreateColormap(dpy,
	                                  RootWindow(dpy, scrno),
	                                  visuallist[0].visual,
	                                  AllocAll);

	/*    Before changing colors in the colormap let's do a colors check.    */
	printf("a new colormap is created based on the first visual\n");
	printf("checking 5 colors by predefined pixel value "
	       "(red,green,blue,white,black)\n");
	const int NUMCOLORS = 5;
	const int colors[NUMCOLORS]={0xff0000, 0x00ff00, 0x0000ff, 0xffffff, 0x0};

	for(int i=0; i < NUMCOLORS; ++i)
	{
		XColor clr;
		clr.pixel = colors[i];
		if(XQueryColor(dpy, clrmap, &clr))
		{
			printf("Colormap pixel=%x returns (%d,%d,%d)\n",
			       colors[i],
			       clr.red*255/65535,
			       clr.green*255/65535,
			       clr.blue*255/65535);
		}
	}


	/*    At run-time you will see that all 5 queries above will return (0,0,0)
	      Colormap depth is 24 which makes 16 mil colors returning (0,0,0).

	      I will set random colors for the ones above.
	 */
	::srand(time(NULL));
	XColor* clrs = (XColor*) ::calloc(sizeof(XColor), NUMCOLORS);
	for(int i=0; i < NUMCOLORS; ++i)
	{
		clrs[i].pixel = colors[i]; // {red,green,blue,white,black}

		// now decide a color for the pixel
		clrs[i].red = (::rand() % 65535);
		clrs[i].green = (::rand() % 65535);
		clrs[i].blue = (::rand() % 65535);
		clrs[i].flags = DoRed | DoGreen | DoBlue;
	}
	XStoreColors(dpy, clrmap, clrs, 256);
	free(clrs);


	printf("stored 5 random values for the predefined previous pixels\n");
	printf("check returned values for each pixel\n");
	for(int i=0; i < NUMCOLORS; ++i)
	{
		XColor clr;
		clr.pixel = colors[i];
		if(XQueryColor(dpy, clrmap, &clr))
		{
			printf("Colormap pixel=%x returns (%d,%d,%d)\n",
			       colors[i],
			       clr.red   * 255 / 65535,
			       clr.green * 255 / 65535,
			       clr.blue  * 255 / 65535);
		}
	}


	XInstallColormap(dpy, clrmap);
	XSetWindowAttributes winattr;
	winattr.colormap = clrmap;
	unsigned long valuemask = CWColormap;


	Window win = XCreateWindow(dpy,
	                           RootWindow(dpy, scrno),
	                           x, y,
	                           winwidth, winheight,
	                           winborder,
	                           vinfo_template.depth,
	                           InputOutput,
	                           visuallist[0].visual,
	                           valuemask,
	                           &winattr);
	XSetWindowColormap(dpy,
	                   win,
	                   clrmap);


	char* title = (char*)"color - Setting a colormap";
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


	/*    For the GC we set foreground=Red and background=White to a pixel
	      composed from existing Colormap indexes.
	*/
	printf("setting GC foreground to Red\n");
	XColor fgcolor;
	fgcolor.pixel = 0xff0000;
	XQueryColor(dpy, clrmap, &fgcolor);
	unsigned long fgpixel = 0;
	fgpixel |= ((fgcolor.red * 255 / 65535) << 16) & 0xff0000;
	fgpixel |= ((fgcolor.green*255 / 65535) <<  8) & 0x00ff00;
	fgpixel |= ((fgcolor.blue *255 / 65535) ) & 0x0000ff;
	printf("XQueryColor for pixel=%x returned (%d,%d,%d)\n",
	       fgcolor.pixel,
	       fgcolor.red, fgcolor.green, fgcolor.blue);




	printf("setting GC background to White\n");
	XColor bgcolor;
	bgcolor.pixel = 0xffffff;
	XQueryColor(dpy, clrmap, &bgcolor);
	unsigned long bgpixel = 0;
	bgpixel |= ((bgcolor.red * 255 / 65535) << 16) & 0xff0000;
	bgpixel |= ((bgcolor.green*255 / 65535) <<  8) & 0x00ff00;
	bgpixel |= ((bgcolor.blue *255 / 65535) ) & 0x0000ff;
	printf("XQueryColor for pixel=%x returned (%d,%d,%d)\n",
	       bgcolor.pixel,
	       bgcolor.red, bgcolor.green, bgcolor.blue);


	XGCValues gcvalues;
	gcvalues.line_width = 1;
	gcvalues.foreground = fgpixel;
	gcvalues.background = bgpixel;
	unsigned long gcmask = GCLineWidth | GCForeground | GCBackground;

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
			XClearWindow(dpy, win);

			const char* text = "Red index into Colormap returned this color";
			XDrawString(dpy, win, gc, 20, 20, text, strlen(text));
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



	XUninstallColormap(dpy, clrmap);
	XFreeColormap(dpy, clrmap);
	XFree(visuallist);
	XFreeGC(dpy, gc);
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}


void print_visual_info(XVisualInfo* vinfo)
{
	printf("---print_visual_info---\n");
	printf("visual*   = %x\n", vinfo->visual);
	printf("visual id = %d\n", vinfo->visualid);
	printf("screen    = %d\n", vinfo->screen);
	printf("depth     = %d\n", vinfo->depth);
	printf("class     = %s\n", class2string(vinfo->c_class));
	printf("red mask  = %x\n", vinfo->red_mask);
	printf("green mask= %x\n", vinfo->green_mask);
	printf("blue mask = %x\n", vinfo->blue_mask);
	printf("clrmap sz = %d\n", vinfo->colormap_size);
	printf("bits/rgb  = %d\n", vinfo->bits_per_rgb);
}

void print_visual(Visual* visual)
{
	printf("---print_visual---\n");
	printf("ext_data   = %x\n", visual->ext_data);
	printf("visual id  = %d\n", visual->visualid);
	printf("class      = %s\n", class2string(visual->c_class));
	printf("red mask   = %x\n", visual->red_mask);
	printf("green mask = %x\n", visual->green_mask);
	printf("blue mask  = %x\n", visual->blue_mask);
	printf("bits/rgb   = %d\n", visual->bits_per_rgb);
	printf("map entries= %d\n", visual->map_entries);
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
