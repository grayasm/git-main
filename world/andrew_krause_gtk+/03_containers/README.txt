GtkContainer:
-------------
hierarchy: GObject->GInitiallyUnowned->GtkWidget->GtkContainer
hold: 2 types of containers, (a) decorators and (b) layout
ctor:
api: gtkcontainer.h
behavior: 2 types of containers derive from GtkContainer
          ->GtkWidget->GtkContainer->GtkBin-> decorators
          ->GtkWidget->GtkContainer-> layout containers (all the others)

          All classes deriving from GtkBin can contain only 1 widget and are
          decorating it, and all the others at the same level with GtkBin
          are layout containers and they are used to arrange multiple widgets.


GtkBox, GtkHBox, GtkVBox:
-------------------------
hierarchy: ->GtkWidget->GtkContainer->GtkBox->GtkHBox,GtkVBox
hold: it is a container that packs multiple children in a one-dimensional area.
ctor: gtk_hbox_new  gtk_vbox_new
api: gtkbox.h  gtkhbox.h  gtkvbox.h
behavior: it packs the widgets horizontally or vertically from the start or end
          position, homogeneous or not, equally spaced or not, filling cells
          with padding or not.

GtkPaned, GtkHPaned, GtkVPaned:
-------------------------------
hierarchy: ->GtkWidget->GtkContainer->GtkPaned->GtkHPaned,GtkVPaned
hold: it is a container widget with 2 children arranged horizontally/vertically.
ctor: gtk_hpaned_new  gtk_vpaned_new
api: gtkpaned.h  gtkhpaned.h  gtkvpaned.h
behavior: it places a vertical bar between its 2 children for resizing.
          moving the bar one widget will shrink while the other expands.
          it is possible to move it so that one child is completely hidden.


GtkTable:
---------
hierarchy: ->GtkWidget->GtkContainer->GtkTable
hold: 1 or more widgets aligned in rows and columns horizontally and vertically
ctor: gtk_table_new
api: gtktable.h
behavior: for each object attached specify l,r,t,bottom indicating the row or
          column where to attach the object. Allows spacing, padding and
          resizing.


GtkFixed:
---------
hierarchy: ->GtkWidget->GtkContainer->GtkFixed
hold: it is a fixed container and holds 1 or more widgets displaced by the pixel
ctor: gtk_fixed_new
api: gtkfixed.h
behavior: it contains more widgets displaced as requested


GtkExpander:
------------
hierarchy: ->GtkContainer->GtkBin->GtkExpander
hold: as all containers derived from GtkBin, it cannot hold more than 1 widget.
ctor: gtk_expander_new
api: gtkexpander.h
behavior: it contains a mark (+ or >) with a lable + mnemonic and expands and
          colapses another widget vertically.


GtkHandleBox:
-------------
hierarchy: ->GtkWidget->GtkContainer->GtkBin->GtkHandleBox
hold: a child that can be removed from the parent window by dragging it with mouse.
ctor: gtk_handle_box_new
api: gtkhandlebox.h
behavior: it is a bin widget which displays its child and a handle that the user
          can drag to tear off a separate "float window" containing the child
          widget. A thin "ghost" is drawn in the original location of the
          handlebox. By draggin the separate window back to its original location
          it can be reattached when aligned along one of the "snap edges"


GtkNotebook:
------------
hierarchy: ->GtkWidget->GtkContainer->GtkNotebook
hold: organizes its children in a number of pages with tabs for easy switch
ctor: gtk_notebook_new
api: gtknotebook.h
behavior: a container whose children are pages that can be switched between
          using tab labels along one edge. Among its options are:
          -which edge the tabs appear
          -if too many tabs should it be made bigger or add scrolling arrows
          -if there will be a popup menu for switching pages


GtkEventBox:
------------
hierarchy: ->GtkWidget->GtkContainer->GtkBin->GtkEventBox
hold: only 1 widget and processes the events for it
ctor: gtk_event_box_new
api: gtkeventbox.h
behavior: various widgets including GtkLabel do not respond to GDK events,
          because they do not have and associated GDK window. To fix this,
          GTK+ provides a container widget called GtkEventBox.
          Event boxes catch events for the child widget by providing a
          GDK window for the object.
