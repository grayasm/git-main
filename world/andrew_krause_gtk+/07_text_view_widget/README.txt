Chapter 7 - The TEXT VIEW Widget

GtkScrolledWindow:
-----------------
hierarchy: ->GtkWidget->GtkContainer->GtkBin->GtkScrolledWindow
hold: a single child widget, adds scrollbars to it and optionally draws a frame
ctor: gtk_scrolled_window_new
api: gtkscrolledwindow.h
behavior: The scrolled window is simply a container with scrollbars. Neither
          the container nor the scrollbars perform any action by themselves.
          Scrolling is handled by the child widget, which is why the child
          must already have native scrolling support to work correctly with
          the GtkScrolledWindow widget.
          When you add a child widget that has scrolling support, a function
          is called to add adjustments for each axis. Nothing will be done
          unless the child widget has scrolling support, which is why a viewport
          is required by most widgets. When the scrollbar is clicked and
          dragged by the user, the value in the adjustment changes, which causes
          the "value-changed" signal to be emitted. This action will also cause
          the child widget to render itself accordingly.
          Because the GtkViewport widget did not have any scrollbars of its own
          it relied completely on the adjustments to define its current position
          on the screen. The scrollbars are used in the GtkScrolledWindow widget
          as an easy mechanism for adjusting the current value of the
          adjustment.

GtkViewport:
------------
hierarchy: ->GtkWidget->GtkContainer->GtkBin->GtkViewport
hold:
ctor: gtk_viewport_new
api: gtkviewport.h
behavior: After you set up a scrolled window, you should add a child widget for
          it to be of any use. There are 2 possible ways to do this, and the
          method is chosen based on the type of child widget. If you are using:
          GtkTextView, GtkTreeView, GtkIconView, GtkViewport, GtkLayout
          widget, you should use the default gtk_container_add (), since all 5
          include native scrolling support. All other widgets do not have native
          scrolling support and gtk_scrolled_window_add_with_viewport () should
          be used.


GtkTextBuffer:
--------------
hierarchy: GObject->GtkTextBuffer
hold: current state of the content within a text view (a rich document)
ctor: gtk_text_buffer_new
api: gtktextbuffer.h
behavior: https://developer.gnome.org/gtk2/stable/TextWidget.html
          GtkTextView cand display the buffer.
          GtkTextBuffer is the buffer in UTF-8 encoding.
          Characters counts are offsets and byte counts are indexes. Dont'mix em
          GtkTextTag can apply an attribute to a range of text (much like html)
          GtkTextTagTable stores tags and it's associated to one or more GtkTextBuffer
          GtkTextIter is an iterator over GtkTextBuffer text. Iterators of deleted text are invalidated.
          GtkTextMark is a mark in text (line and column) and is not affected by text removal.
