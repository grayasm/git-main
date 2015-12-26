    *** ===================================== ***
    *** Chapter 2 Your first GTK+ application ***
    *** ===================================== ***

    Concepts:

    1) The basic function calls required by all GTK+ applications
    2) How to compile GTK+ code with GCC
    3) The object-oriented nature of the GTK+ widget system
    4) What role signals, callbacks and events play in your applications
    5) How to alter textual styles with the Pango Text Markup Language
    6) Various other useful functions provided for the widgets presented here
    7) How to use GtkButton widget to make a clickable GtkLabel
    8) How to get and set properties of objects using GObject methods

    see:
    <gtkmain.h>         gtk_init, gtk_main
    <gtkwindow.h>       gtk_window_new
    <gtkenum.h>         GtkWindowType
    <gtkwidget.h>       gtk_widget_show

    hierarcy of GtkWindow:
    GObject -> GInitiallyUnowned -> GtkObject -> GtkWidget -> \
               GtkContainer -> GtkBin -> GtkWindow

    Casting GTK+ objects: GTK_OBJECT(), GTK_WIDGET(),
              GTK_CONTAINER(), GTK_BIN(), GTK_WINDOW()

    GTK+-2.x API reference: https://developer.gnome.org/gtk2/stable/

    see:
    pkg-config --cflags gtk+-2.0        expands to:
               -pthread
               -I/usr/include/gtk-2.0
               -I/usr/lib64/gtk-2.0/include
               -I/usr/include/atk-1.0
               -I/usr/include/cairo
               -I/usr/include/gdk-pixbuf-2.0
               -I/usr/include/pango-1.0
               -I/usr/include/glib-2.0
               -I/usr/lib64/glib-2.0/include
               -I/usr/include/pixman-1
               -I/usr/include/freetype2
               -I/usr/include/libpng15
               -I/usr/include/libdrm
               -I/usr/include/harfbuzz

    pkg-config --libs gtk+-2.0          expands to:
               -lgtk-x11-2.0
               -lgdk-x11-2.0
               -latk-1.0
               -lgio-2.0
               -lpangoft2-1.0
               -lpangocairo-1.0
               -lgdk_pixbuf-2.0
               -lcairo
               -lpango-1.0
               -lfontconfig
               -lgobject-2.0
               -lglib-2.0
               -lfreetype
