/*
 *    Colors:
 *       Colormap type is XID   (e.g. unsigned long, a tag stored in X server)
 *       struct XSetWindowAttributes.colormap is Colormap assoc. to the window
 *       To list all installed Colormaps :
 *       Colormap* XListInstalledColormaps(dpy, win, (int*)&num_return);
 *
 *       In this program we use XQueryColor to get from the DefaultColormap()
 *       a color. We provide 0xff0011 or any other color as pixel and get the
 *       unsigned short red,green,blue corresponding values in range [0,65535]
 *
 *       We compare the returned color with the ammount of red,green,blue we
 *       set in the pixel and see if they match. If so, it means the hardware
 *       supports all possible color combinations.
 *       At a glance: 256 * 256 * 256 = 16,777,216 colors
 *                             2 ^ 24 = 16,777,216 colors
 *
 *       So if the DefaultDepth() or bits per pixel is 24 then the screen
 *       supports 16 mil colors, enough to display all possible colors.
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


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


	char* title = (char*)"color - XQueryColor";
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
	gcvalues.foreground = BlackPixel(dpy, scrno);
	gcvalues.background = WhitePixel(dpy, scrno);
	unsigned long gcmask = GCLineWidth | GCForeground | GCBackground;

	GC gc = XCreateGC(dpy,
	                  win,
	                  gcmask,
	                  &gcvalues);


	/*    Test Colormap functions    */
	int num_return;
	Colormap* clrmaps = XListInstalledColormaps(dpy,
	                                            win,
	                                            &num_return);
	printf("XListInstalledColormaps has found %d %s\n",
	       num_return, (num_return > 1 ? "colormaps" : "colormap"));

	Colormap clrmap_def = DefaultColormap(dpy, scrno);
	for(int i=0; i < num_return; ++i)
	{
		printf("colormap tag = %d ", clrmaps[i]);
		if(clrmaps[i] == clrmap_def)
		{
			printf(" [DefaultColormap]\n");
		}
		else
		{
			printf("\n");
		}
	}
	/*    How many bits per pixels are in the colormap ?
	      The terminology uses "planes", but here is a short calculation:

	      2 ^ 2  = 4 colors
	      2 ^ 4  = 16 colors
	      2 ^ 8  = 256 colors
	      2 ^ 16 = 65535 colors
	      2 ^ 24 = 16777216 colors
	      2 ^ 32 = 4294967296 colors
	*/
	unsigned long depth = DefaultDepth(dpy, scrno);
	printf("default depth is: %d\n", depth);
	double numOfColors = ::pow(2, depth);
	printf("this screen supports 2 ^ %d = %.0f colors\n",
	       depth, numOfColors);


	/*    We request for a given RGB the hardware RGB from installed Colormap.
	      Then if we compare the 2 values we see if they are equal or not.
	      If not equal it means
	      a) the hardware supports less color combinations than possible
	      b) some gamma correction is involved (don't know yet).
	*/
	printf("searching for differences between hardware and real colors values\n");
	printf("this may take a while, you can interrupt this process at any time\n");
	unsigned long clrdiff = 0;
	double clrCount = 0;
	int rgb = 0;
	XColor color;

	for(int red = 0; red < 256; ++red)
	{
		for(int green = 0; green < 256; ++green)
		{
			for(int blue = 0; blue < 256; ++blue, ++clrCount)
			{
				rgb = 0x000000;
				rgb |= (red << 16) & 0xff0000;
				rgb |= (green << 8) & 0x00ff00;
				rgb |= blue & 0x0000ff;

				color.pixel = rgb;

				/*    XQueryColor takes the pixel value and returns the
				      red,green,blue values in range [0,65535]
				*/

				if(!XQueryColor(dpy,
				                clrmap_def,
				                &color))
				{
					printf("XQueryColor error at (%d,%d,%d)\n",
					       red, green, blue);
					++clrdiff;
					continue;
				}


				int rred   = color.red   * 255 / 65535;
				int rgreen = color.green * 255 / 65535;
				int rblue  = color.blue  * 255 / 65535;

				if(rred != red || rgreen != green || rblue != blue)
				{
					printf("Hardware (%d,%d,%d) mismatch for Real (%d,%d,%d)"
					       " ***********************************************\n",
					       rred, rgreen, rblue,
					       red, green, blue);
					++clrdiff;
				}


				/*    Update user with some progress. In virtual environment
				      this program takes a lot of time.
				*/

				if((int)(numOfColors - clrCount) % 50000 == 0)
				{
					printf("%.0f colors left to query at (%d,%d,%d)"
					       " - have found %d different colors in hardware's Colormap\n",
					       numOfColors - clrCount, rred, rgreen, rblue,
					       clrdiff);
				}
			}
		}
	}
	printf("%d colors are approximated by hardware\n\n", clrdiff);


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
