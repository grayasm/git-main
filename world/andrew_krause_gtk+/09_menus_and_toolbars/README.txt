Chapter 9 - Menus and Toolbars



GtkMenuShell:
--------------------
hierarchy: ->GtkWidget->GtkContainer->GtkMenuShell->{GtkMenu, GtkMenuBar}
hold: abstract base class for GtkMenu and a container of GtkMenuItem objects
ctor:
api:  gtkmenushell.h
behavior: is a container of GtkMenuItem objects arranged in a list which can
          be navigated, selected, and activated by the user to perform
          application functions. A GtkMenuItem can have a submenu associated
          with it, allowing for nasted hierarchical menus.

GtkMenu:
--------------------
hierarchy: ->GtkWidget->GtkContainer->GtkMenuShell->GtkMenu
hold: implements a drop down menu
ctor: gtk_menu_new
api:  gtkmenu.h
behavior:
        Implements a drop down menu consisting of a list of a GtkMenuItem.
        Can add a GtkMenuItem to the menu with:
       gtk_menu_shell_apend(), gtk_menu_shell_insert(), gtk_menu_shell_prepend()
        See: https://developer.gnome.org/gtk2/stable/GtkMenu.html
        for sample code.

GtkMenuItem:
--------------------
hierarchy: ->GtkWidget->GtkContainer->GtkBin->GtkItem->GtkMenuItem->
             {GtkCheckMenuItem,GtkImageMenuItem,GtkSeparatorMenuItem,
              GtkTearoffMenuItem}
hold: itself and derived widgets are the only valid widgets for menus.
ctor: gtk_menu_item_new, gtk_menu_item_new_with_label, etc.
api:  gtkmenuitem.h
behavior: As it derives from GtkBin it can hold any valid child widget,
          although only a few are really useful.
signals: "activate" and "activate-item"


GtkSeparatorMenuItem:
--------------------
hierarchy: ->GtkWidget->GtkContainer->GtkBin->GtkItem->GtkMenuItem->
             GtkSeparatorMenuItem
hold: a separator used to group items within a menu.
ctor: gtk_separator_menu_item_new
api:  gtkseparatormenuitem.h
behavior: It displays a horizontal line with a shadow to make it appear
          sunken into the interface.

GtkImageMenuItem:
-----------------
hierarchy: ->GtkWidget->GtkContainer->GtkBin->GtkItem->GtkMenuItem->
             GtkImageMenuItem
hold: is a menu item which has an icon next to the text label
ctor: gtk_image_menu_item_new    + _with_label,_with_mnemonic,_from_stock
api:  gtkimagemenuitem.h
behavior: Note that the user can disable display of menu icons, so make
          sure to still fill in the text label.


GtkCheckMenuItem:
-----------------
hierarchy: ->GtkWidget->GtkContainer->GtkBin->GtkItem->GtkMenuItem->
             GtkCheckMenuItem
hold: the state of a boolean value in a addition to a GtkMenuItem
ctor: gtk_check_menu_item_new  + _with_label,_with_mnemonic
api:  gtkcheckmenuitem.h
behavior: A check box indicating the state of the boolean value is displayed
          at the left side of the GtkMenuItem. Activating the GtkMenuItem
          toggles the value.

GtkRadioMenuItem:
-----------------
hierarchy: ->GtkWidget->GtkContainer->GtkBin->GtkItem->GtkMenuItem->
             GtkCheckMenuItem->GtkRadioMenuItem
hold: a check menu item that belongs to a group where only one item is selected.
ctor: gtk_radio_menu_item_new   + _with_label,_with_mnemonic,...
api:  gtkraiodmenuitem.h
behavior: See: https://developer.gnome.org/gtk2/stable/GtkRadioMenuItem.html
          for samples of code.


GtkAccelGroup:
--------------------
hierarchy: GtkObject->GtkAccelGroup
hold: a group of keyboard accelerators
ctor: gtk_accel_group_new
api:  gtkaccelgroup.h
behavior: the group is attached to a toplevel GtkWindow with
          gtk_window_add_accel_group().
          When using GtkItemFactory, GTK+ automatically sets up the accelerators
          for your menus in the item factory's GtkAccelGroup.
          Note that accelerators are different from mnemonics. Accelerators are
          shortcuts for activating a menu item; they appear alongside the menu
          item they're a shortcut for. Mnemonics are shortcuts for GUI elements
          such as text entries or buttons; they appear as underlined characters.
          Menu items can have both accelerators and mnemonics, of course.

GtkStatusBar:
-------------
hierarchy: ->GtkWidget->GtkContainer->GtkBox->GtkHBox->GtkStatusBar
hold: a stack of messages
ctor: gtk_statusbar_new
api:  gtkstatusbar.h
behavior: a statusbar maintains one stack of messages for display purposes,
          but allows multiple message producers to maintain sub-stacks of the
          messages they produced (via context ids).
          Add a message with gtk_statusbar_push().
          Remove a message from the top of the stack with gtk_statusbar_pop().
          Remove a message by its id with gtk_statusbar_remove().

GtkMenuBar:
-------------
hierarchy: ->GtkWidget->GtkContainer->GtkMenuShell->GtkMenuBar
hold: a standard bar which can hold many menu items.
ctor: gtk_menu_bar_new
api:  gtkmenubar.h
behavior: Contains one or many GtkMenuItem. Allows a shadow type to be set for
          aesthetic purposes.



GtkToolbar:
-----------
hierarchy: ->GtkWidget->GtkContainer->GtkToolbar
hold: can contain intances of subclass of GtkToolItem.
ctor: gtk_toolbar_new()
api:  gtktoolbar.h
behavior: holds a number of widgets in a horizontal of vertical row. It is meant
          to allow easy customization of a large number of widgets with very
          little trouble. Typically, toolbars hold tool buttons that can display
          an image along with a text string. However, toolbars are actually
          able to hold any type of widget.
          For more see: https://developer.gnome.org/gtk2/stable/GtkToolbar.html
Subclasses of type GtkToolItem that can be added to GtkToolbar:
 ->GtkWidget->GtkContainer->GtkBin->GtkToolItem:
   ->GtkToolButton:
        ->GtkMenuToolButton
        ->GtkToggleToolButton
             -> GtkRadioToolButton
   ->GtkSeparatorToolItem


GtkActionGroup:
--------------

GtkUIManager:
-------------


GtkIconSource: holds a GdkPixbuf or an image file. It is meant to hold one
               variant of an image. For example if have an image that will be
               displayed differently when it is enabled or disabled, you would
               need to have multiple icon sources, one for each state. You may
               need multiple icon sources for different icon sizes,languages,etc
GtkIconSet:    organizes multiple GtkIconSource objects for one stock image.
               In some cases, your icon set may have only one image.
GtkIconFactory: after all necessary icon sets are created, they are added to a
                GtkIconFactory, which is used to organize all of the stock items
                for a particular theme.
