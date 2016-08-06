/*    Cap. 6  Drawing Graphics and Text.
 *
 *    Scaling graphics
 *
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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
	int winwidth = scrwidth /2;
	int winheight = scrheight / 1.5;

	int winborder = 1;

	Window win = XCreateSimpleWindow(dpy,
	                                 RootWindow(dpy, scrno),
	                                 x, y,
	                                 winwidth, winheight,
	                                 winborder,
	                                 BlackPixel(dpy, scrno),
	                                 WhitePixel(dpy, scrno));


	char* title = (char*)"draw4 - Scaling graphics";
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



	Font fixed = XLoadFont(dpy, "fixed");
	XGCValues gcvalues;
	gcvalues.line_width = 1;
	gcvalues.foreground = BlackPixel(dpy, scrno);
	gcvalues.background = WhitePixel(dpy, scrno);
	gcvalues.font = fixed;
	unsigned long gcmask = GCLineWidth | GCForeground | GCBackground | GCFont;

	GC gc = XCreateGC(dpy,
	                  win,
	                  gcmask,
	                  &gcvalues);

	XMapWindow(dpy, win);

	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);
		if(event.type == Expose &&
		   event.xexpose.count == 0)
		{
			XClearWindow(dpy,
			             win);

			float wratio = DisplayWidth(dpy, scrno)/DisplayWidthMM(dpy, scrno);
			float hratio = DisplayHeight(dpy,scrno)/DisplayHeightMM(dpy, scrno);

			int wlen10 = 100 /*10cm*/ * wratio;
			int hlen10 = 100          * hratio;

			int rx = 20;
			int ry = 20;

			XRectangle rect = {rx, ry, wlen10, hlen10};
			XDrawRectangles(dpy,
			                win,
			                gc,
			                &rect,
			                1);

			char msg0[200], msg1[200], msg2[200], msg3[200], msg4[200];
			sprintf(msg0, "Scaling graphics uses ratio aspect calculated as");
			sprintf(msg1, "width  ratio = DisplayWidth / DisplayWidthMM");
			sprintf(msg2, "height ratio = DisplayHeight / DisplayHeightMM");
			sprintf(msg3, "ratio= %.2f - %.2f  pixels / mm", wratio, hratio);
			sprintf(msg4, "W10cm= %d  H10cm= %d    pixels", wlen10, hlen10);

			XDrawString(dpy, win, gc, rx + 20, ry + 50, msg0, strlen(msg0));
			XDrawString(dpy, win, gc, rx + 20, ry + 70, msg1, strlen(msg1));
			XDrawString(dpy, win, gc, rx + 20, ry + 90, msg2, strlen(msg2));
			XDrawString(dpy, win, gc, rx + 20, ry + 110, msg3, strlen(msg3));
			XDrawString(dpy, win, gc, rx + 20, ry + 130, msg4, strlen(msg4));
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
	}

	return 0;
}
