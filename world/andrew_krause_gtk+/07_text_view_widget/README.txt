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
          GtkTextView to hold and display a GtkTextBuffer
          GtkTextBuffer is the buffer in UTF-8 encoding.
          Characters counts are offsets and byte counts are indexes. Dont'mix em
          GtkTextTag can apply an attribute to a range of text (much like html)
          GtkTextTagTable stores tags and it's associated to one or more GtkTextBuffer
          GtkTextIter is an iterator over GtkTextBuffer text. Iterators of deleted text are invalidated.
          GtkTextMark is a mark in text (line and column) and is not affected by text removal.


GtkTextView:
------------
hierarchy: ->GtkObject->GtkWidget->GtkContainer->GtkTextView
hold: a GtkTextBuffer
ctor: gtk_text_view_new
api: gtktextview.h
behavior:


GtkTextTag:
-----------
hierarchy: GObject->GtkTextTag
hold: a lot of text attributes: bg & fg color & stipple, justification,ident,etc
ctor: gtk_text_tag_new
api: gtktexttag.h
behavior: Tags should be in the GtkTextTable for a given GtkTextBuffer before
          using them with that buffer. A tag is much like a html tag applying
          color,identation and other styling to a text.


GtkTextTagTable:
----------------
hierarchy: GObject->GtkTextTagTable
hold: multiple GtkTextTag
ctor: gtk_text_tag_table_new
api: gtktexttagtable.h
behavior:


GtkTextIter:
------------
hierarchy: GBoxed->GtkTextIter
hold:
ctor:   gtk_text_buffer_get_iter_at_line_offset
        gtk_text_buffer_get_iter_at_line_index
        gtk_text_buffer_get_iter_at_offset
        gtk_text_buffer_get_iter_at_line
        gtk_text_buffer_get_start_iter
        gtk_text_buffer_get_end_iter
        gtk_text_buffer_get_bounds
        gtk_text_buffer_get_iter_at_mark
        gtk_text_buffer_get_iter_at_child_anchor
        and maybe others.
api: gtktextiter.h
behavior: the header contains methods to operate with a given iterator


GtkTextMark:
------------
hierarchy: GObject->GtkTextMark
hold: a position in the buffer preserved across buffer modifications
ctor: gtk_text_mark_new
api: gtktextmark.h
behavior:


PangoFontDescription:
---------------------
hierarchy: GBoxed->PangoFontDescription
hold:
ctor: pango_font_description_from_string
      pango_font_description_new
api: /usr/include/pango-1.0/pango/pango-font.h
behavior: https://developer.gnome.org/pango/stable/pango-Fonts.html


PangoLayout:
------------
hierarchy: GObject->PangoLayout
hold: one or more paragraphs of text
ctor: gtk_widget_create_pango_layout
      pango_layout_new
      and maybe others
api: /usr/include/pango-1.0/pango/pango-layout.h
behavior: https://developer.gnome.org/pango/stable/pango-Layout-Objects.html#PangoLayout-struct
          The PangoLayout structure represents and entire paragraph of text.
          It is initialized with a PangoContext, UTF-8 string and set of
          attributes for that string. Once that is done, the set of formatted
          lines can be extracted from the object, the layout can be rendered,
          and the conversion between logical character positions within the
          layout's text, and the physical position of the resulting glyphs
          can be made. See the figure/drawing from the link.

PangoTabArray:
--------------
hierarchy: GBoxed->PangoTabArray
hold: multiple tab stops (specified in pixels or Pango units).
ctor: pango_tab_array_new
      pango_tab_array_new_with_positions
      and maybe others.
api: /usr/include/pango-1.0/pango/pango-tabs.h
behavior:


GtkClipboard:
-------------
hierarchy:
hold:
ctor:
api:
behavior:
