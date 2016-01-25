Chapter 4 Basic Widgets
-----------------------
 * we will see widgets designed to facilitate user interaction:
   stock buttons, toggle buttons, check buttons, radio buttons
   color selection buttons, file chooser buttons, font selection buttons
   text entries and number selection buttons

GtkButton:
-----------
hierarchy: ->GtkWidget->GtkContainer->GtkBin->GtkButton
hold: can hold any valid child widget, most used GtkLabel
ctor: gtk_button_new
api: gtkbutton.h
behavior: is generally used to trigger a callback function that is called
          when the button is pressed. There are also stock buttons (see
          gtk_button_new_from_stock, and GTK_STOCK_CLOSE, GTK_STOCK_COPY, etc).


GtkToggleButton:
----------------
hierarchy: ->GtkWidget->GtkContainer->GtkBin->GtkButton->GtkToggleButton
hold: a widget that retain its state (pressed, unpressed).
ctor: gtk_toggle_button_new
api: gtktogglebutton.h
behavior: is a GtkButton which will remain "pressed-in" when clicked. Clicking
          again will cause the toggle button to return to its normal state.


GtkCheckButton:
---------------
hierarchy: ->GtkWidget->GtkContainer->GtkBin->GtkButton->GtkToggleButton->GtkCheckButton
hold: a widget with a discrete toggle button (the check box)
ctor: gtk_check_button_new
api: gtkcheckbutton.h
behavior: places a discrete toggle button next to a widget (usually a GtkLabel)
          The important signal "toggled" is also inherited from GtkToggleButton.


GtkRadioButton:
---------------
hierarchy:
hold:
ctor:
api:
behavior:

-----------
hierarchy:
hold:
ctor:
api:
behavior:
