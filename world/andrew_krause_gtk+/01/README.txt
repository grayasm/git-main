        *** =============================== ***
        *** Foundations of GTK+ Development ***
        *** =============================== ***
            Cap. 1 GETTING STARTED
        *** =============================== ***

        GTK+ is an object-oriented API in C for graphical application development.
        GLib is a supporting library called GObject.
        Cairo is a 2-D vector graphics rendering library.

        Standard GObject Data Types
        G_TYPE_NONE      void           C void
        G_TYPE_CHAR      gchar          C char
        G_TYPE_INT       gint           C int     G_MININT <= val <= G_MAXINT
        G_TYPE_LONG      glong          C long    G_MINLONG <= val <= G_MAXLONG
        G_TYPE_BOOLEAN   gboolean                 TRUE or FALSE
        G_TYPE_ENUM      GEnumClass     C enum
        G_TYPE_FLAGS     GFlagsClass              bit field (boolean flags)
        G_TYPE_FLOAT     gfloat         C float   -G_MAXFLOAT <= val <= G_MAXFLOAT
        G_TYPE_DOUBLE    gdouble        C double  -G_MAXDOUBLE <= val <= G_MAXDOUBLE
        G_TYPE_STRING    gchar*         C char*   NULL-terminated
        G_TYPE_POINTER   gpointer       C void*
        G_TYPE_VALUE     GValue                   A Variant
        G_TYPE_OBJECT    GObject                  A Widget

        GDK is a Xlib wrapper for low-level image drawing and window functions.
        GdkPixbuf is a library for client side image manipulation functions.
                * depends on Libart for 2-D drawing (packaged with GNOME)
                * depends on GkdRGB library for rendering/drawing.

        Pango is a text and font output library in conjunction with Cairo and Xft.
                * uses FreeType and fontconfig for client-side fonts.

        ATK is Accessibility Toolkit library for widgets with a built-in method
                of handling accessibility issues considering users disabilities.

        GTK+ bindings:
                * Gtkmm is the official set of C++ bindings.
                * PyGTK provides Python bindings for the GTK+ libraries.
                * Gtk2-perl is the Perl toolkit.
                * PHP-Gtk is the PHP language bindings.
                * Java-Gnome provides essential libraries for Java.
                * Gtk# provides bindings for C#

