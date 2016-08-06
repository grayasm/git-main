    Cap.7 - Color

    - difficult due to portability to different types of displays
    - color for background and border of a window
    - color for cursor
    - foreground and background for GC
    - distinguish between physical and logical layers through color
    - fine gradations of color to represent real-world data

    7.1 - Terms and concepts
    - most color screens are based on RGB color model
    - 1 pixel is made up of 3 phosphors (red,green,blue) sensitive to a
      separate electronic beam; when fully illuminated, the pixel appears white
    - each pixel is defined by a value (4,8 or 24 planes or bits)
      this value is an index into a colormap named colorcell
      each colorcell defines a color by 3 x 16 bits for each R,B,G
    - the range of colors possible on the screen is a function of the number
      of bits available in the colormap for RGB specification
      If eight bits are available for each primary then the range of possible
      colors is 256 ^ 3 = 16 million colors
    - the number of different colors that can be displayed at any one time is a
      function of the number of planes.
      A  4-plane could index 2 ^ 4  colorcells = 16 distinct colors
      A  8-plane could index 2 ^ 8  colorcells = 256 distinct colors
      A 24-plane could index 2 ^ 24 colorcells = over 16 millions distinct colors
    - a client allocates a color by asking the server access to a colorcell in
      a colormap and is returned a pixel value.

    7.2 - Naming and specification
    - X server provides a color database that translates string (e.g. "yellow")
      into RGB values; encourages colorcell sharing.
    - because same RGB value can generate different colors on different hardware
      X server implementors made possible to change the RGB for each color name
      = gamma correction
    - when no gamma correction database is provided the problem is resolved by
      X Color Management System or Xcms; it is a client-side color database.
    - a device dependent color is specified as RGB:<red>/<green>/<blue>
      where <red>,<green>,<blue> are floating point numbers between 0.0 and 1.0
    - "color space" terminology is a device independent color specification
       that follow the same syntax; for color spaces see <X11/Xcms.h>

      CIEXYZ:<X>/<Y>/<Z>
      CIEuvY:<u>/<v>/<Y>         (e.g. 0.0 <= u <= 0.6)
      CIExyY:<x>/<y>/<Y>
      CIELab:<L>/<a>/<b>
      CIELuv:<L>/<u>/<v>
      TekHVC:<H>/<V>/<C>         (e.g. 0.0 <= H angle <= 360.0)

`   - in dexadecimal format the RBG can be specified as:
    #RGB               ( 4 bits each of red, green and blue)
    #RRGGBB            ( 8 bits
    #RRRGGGBBB         (12 bits
    #RRRRGGGGBBBB      (16 bits

    7.3 Display hardware
    - mid-range color screen have only 1 harware colormap
    - high performance color displays have 24 planes (bits per pixel) which is
      common; can screen every discernible color at the same time; thus the
      colormap is read-only which has own advantages;
    - structure of type Visual : implements the characteristics of a virtual
      colormap;
    - DefaultDepth() and DisplayPlanes() cannot tell if screen is monochrome or
      color; use instead XMatchVisualInfo() or XGetVisualInfo() and check
      struct XVisualInfo.class member;

    7.5 Allocating shared colors
    - XAllocColor : returns the index of a colorcell in the colormap
    - XQueryColor : what RGB values are in each colorcell; cannot say if the
                    colorcell is read-only or read-write;
