    Cap. 6 Drawing Graphics and Text

    Draw lines - XDrawPoint(s), XDrawLine(s), XDrawSegments
    Draw geometrical figures - XDrawRectangle(s), XDrawArc(s)
    Draw text -XDrawText, XDrawText16
    Max Objects - XMaxRequestSize
    Scaling graphics - screen: 9.5"x7.25"  640x480 pixels
                       screen: 13.5"x10.5" 1152x900 pixels
    Calculate screen ratio mm->pixels - DisplayHeight
                                        DisplayHeightMM
                                        DisplayWidth
                                        DisplayWidthMM
    Filling - XFillArc(s), XFillPolygon, XFillRectangle(s)
    Bitmaps, Pixmaps, Tiles, Stipples - XCreateBitmapFromData
                                        XCreatePixmapFromBitmapData
                                        XCreatePixmap
                                        XReadBitmapFile
                                        XCopyPlane
    XClearWindow, XClearArea, XCopyArea

    Fonts
    ----
    Font in X is a set of bitmaps.
    Font functions have 8bit and 16bit versions (ANSI, UNICODE).
    XListFonts, XListFontsWithInfo, XFreeFontNames
    XLoadFont, XSetFont, XQueryFont, XLoadQueryFont
    XDrawString, XDrawImageString
    XTextWidth, XTextExtents, XQueryTextExtents
    XFreeFontPath, XGetFontPath, XSetFontPath

    Regions
    -------
    XSetRegion, XCreateRegion, XPolygonRegion, XUnionRectWithRegion,
    XDestroyRegion
    XOffsetRegion, XShrinkRegion, XIntersectRegion, XUnionRegion, XSubtractRegion
    XXorRegion, XUnionRectWithRegion
    XEmptyRegion, XEqualRegion, XPointInRegion, XRectInRegion

    Images
    ------
    XGetImage, XPutImage, XCreateImage, XDestroyImage, XGetPixel, XPutPixel,..

    Cursors
    -------
    XDefineCursor, XQueryBestCursor, XCreateFontCursor,... *Cursor*
