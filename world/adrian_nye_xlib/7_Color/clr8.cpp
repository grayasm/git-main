/*
 *   Cap. 7.6.2 Example of Choosing Visual
 *   Example 7-10 Code to match visuals
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


	Colormap clrmap;
	XSetWindowAttributes attributes;
	unsigned long valuemask;
	XVisualInfo vTemplate;
	XVisualInfo* visualList;
	int visualMatched = 0;


	/* Set up the XVisualInfo template so that it returns a list
	   of all the visuals of depth 24 defined on the current screen
	   by the X server
	*/

	vTemplate.screen = scrno;
	vTemplate.depth = 24;
	vTemplate.c_class = DirectColor;
	visualList = XGetVisualInfo(dpy,
	                            VisualScreenMask | VisualDepthMask | VisualClassMask,
	                            &vTemplate,
	                            &visualMatched);

	printf("%d visuals matched screen=%d depth=%d class=DirectColor\n",
	       visualMatched, scrno, vTemplate.depth);

	if(visualMatched == 0)
	{
		printf("no matching visuals\n");
		exit(-1);
	}

	/* Create a colormap for a window using the first of the
	   visuals in the list of XVisualinfo structs returned by
	   XGetVisualInfo
	*/
	clrmap = XCreateColormap(dpy,
	                         RootWindow(dpy, scrno),
	                         visualList[0].visual,
	                         AllocNone);

	/* Must specify colormap attribute if using nondefault visual */
	attributes.colormap = clrmap;
	valuemask |= CWColormap;

	Window win = XCreateWindow(dpy,
	                           RootWindow(dpy, scrno),
	                           x, y,
	                           winwidth, winheight,
	                           winborder,
	                           vTemplate.depth,
	                           InputOutput,
	                           visualList[0].visual,
	                           valuemask,
	                           &attributes);
	XSetWindowColormap(dpy, win, clrmap);

	/* All done with visual information; free it */
	XFree(visualList);


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
	gcvalues.foreground = 0xff0000;
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
