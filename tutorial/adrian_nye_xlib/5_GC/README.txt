        1. The Graphic Context specifies the appearance of the drawing,
           and influences how the grahpic primitives are drawn.
           The width, style, color, cap, join, filling, font, clipping, etc

           These characteristics are set to the parameters of struct XGCValues.
           This is passed to XCreateGC(dpy,win,values,mask) together with
                 the mask value to indicate which parameter is set.

        member                   mask                       default
        --------------------------------------------------------------
        function                 GCFunction                 GXcopy
        plane_mask               GCPlaneMask                all 1
        foreground               GCForeground               0
        background               GCBackground               1
        line_width               GCLineWidth                0
        line_style               GCLineStyle                LineSolid
        cap_style                GCCapStyle                 CapButt
        join_style               GCJoinStyle                JoinMiter
        fill_style               GCFillStyle                FillSolid
        fill_rule                GCFillRule                 EvenOddRule
        arc_mode                 GCArcMode                  ArcPieSlice
        tile                     GCTile                     pixmap filled with foreground
        stipple                  GCStipple                  pixmap filled with 1
        ts_x_origin              GCTileStipXOrigin          0
        ts_y_origin              GCTileStipYOrigin          0
        font                     GCFont                     implementation dependent
        subwindow_mode           GCSubwindowMode            ClipByChildren
        graphics_exposure        GCGraphicsExposures        True
        clip_x_origin            GCClipXOrigin              0
        clip_y_origin            GCClipYOrigin              0
        clip_mask                GCClipMask                 None
        dash_offset              GCDashOffset               0
        dashes                   GCDashList                 4
