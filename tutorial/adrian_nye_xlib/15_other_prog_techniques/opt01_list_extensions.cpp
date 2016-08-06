// copied from youtube.com/watch?v=2l7ixRE3OCw
// X Security - It's worse than it looks, min: 38:59
#include <X11/Xlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	Display* dpy = XOpenDisplay (NULL);
	int nextensions = 0, i = 0;
	char** p, **extensionList = XListExtensions (dpy, &nextensions);
	for(p = extensionList; nextensions; nextensions--, p++)
	{
		i++;
		printf ("extension %d: %s\n", i, *p);
	}
	return 0;
}
