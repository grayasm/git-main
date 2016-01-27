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
hierarchy: ->GtkWidget->GtkContainer->GtkBin->GtkButton->GtkToggleButton->
            ->GtkCheckButton->GtkRadioButton
hold: a label widget with a discrete circular toggle to the side.
ctor: gtk_radio_button_new  gtk_radio_button_new_from_widget
api: gtkradiobutton.h
behavior: radio buttons are grouped togheter in a group where only 1 radio
          button is selected and others will be deselected. The group forbids
          selecting multiple radio buttons at once.


GtkEntry:
-----------
hierarchy: ->GtkWidget->GtkEntry->
hold: is a single line free-form text entry widget.
ctor: gtk_entry_new
api: gtkentry.h
behavior: implemented in a general manner, so that it can be molded to fit
          many types of solutions: text entry, password entry and even numbers.


GtkSpinButton:
-------------
hierarchy: ->GtkWidget->GtkEntry->GtkSpinButton
hold: a number selection widget that is capable of handling integers and float.
ctor: gtk_spin_button_new
api: gtkspinbutton.h
behavior: it allows the user to select an integer or floating point number by
          incrementing or decrementing with the up or down arrows. The user
          can still type in a value with the keyboard, and it will be displayed
          as the nearest acceptable value if it is out of range.


GtkScale, GtkHScale, GtkVScale:
------------------------------
hierarchy: ->GtkWidget->GtkRange->GtkScale->GtkHScale,GtkVScale
hold: a horizontal/vertical slider widget for selecting a value from a range
ctor: gtk_hscale_new, gtk_vscale_new
api: gtkhscale.h  gtkvscale.h
behavior: the widget is called a scale and allows you to provide a horizontal
          or vertical slider that can choose an integer or a floating-point
          number. It is different from GtkSpinButton in only that restricts
          the user from entering values, since the value is chosen by moving
          the slider.


Widget Styles:
--------------
GtkStyle* style; is a member of GtkWidget struct.
See gtkstyle.h for the format.

typedef struct
{
   GdkColor fg[5];         /* The foreground color for most widgets. */
   GdkColor bg[5];         /* The background color for most widgets. */
   GdkColor light[5];      /* Lighter colors used for creating widget shadows. */ 
   GdkColor dark[5];       /* Darker colors used for creating widget shadows. */
   GdkColor mid[5];        /* The color midway between light and dark. */
   GdkColor text[5];       /* The text color for most text widgets. */
   GdkColor base[5];       /* The background color used for text-editing widgets. */
   GdkColor text_aa[5];    /* Used for anti-aliased text colors. */
   GdkColor black, white;  /* Colors that represent "Black" and "White". */

   PangoFontDescription *font_desc; /* The default text font. */

   gint xthickness, ythickness;  /* Thickness of lines. */

   GdkPixmap *bg_pixmap[5];      /* Background image to use for a widget. */

   /* Graphics contexts that hold drawing properties for each color and state. */
   GdkGC *fg_gc [5], *bg_gc [5], *light_gc[5], *dark_gc[5], *mid_gc[5], *text_gc[5],
         *base_gc[5], *text_aa_gc[5];
   GdkGC *black_gc, *white_gc;
} GtkStyle;

Resource Files:
---------------
The .gtkrc (RC file) resource file allows the user to define styles for widget
types or individual widgets which can be changed to fit the user's preferences.
These are usually stored in the user's home directory along with other
application data, so that the user has permissions to alter the settings.
Load rc file with:    void gtk_rc_parse (const gchar* filename);

style "widgets"
{

   xthickness = 2
   ythickness = 2

   fg[ACTIVE]      = "#FFFFFF"
   fg[SELECTED]    = "#003366"
   fg[NORMAL]      = "#CCCCCC"
   fg[PRELIGHT]    = "#FFFFFF"
   fg[INSENSITIVE] = "#999999"

   bg[ACTIVE]      = "#003366"
   bg[SELECTED]    = "#FFFFFF"
   bg[NORMAL]      = "#666666"
   bg[PRELIGHT]    = "#003366"
   bg[INSENSITIVE] = "#666666"
}

style "labels" = "widgets" {
   font_name = "Sans Bold 14"
}

style "buttons" = "widgets" {
   GtkButton::inner-border = { 10, 10, 10, 10 }
}

style "checks" = "buttons" {
   GtkCheckButton::indicator-size = 25
}

class "GtkWindow"      style "widgets"
class "GtkLabel"       style "labels"
class "GtkCheckButton" style "checks"
class "Gtk*Button"     style "buttons"



GtkColorButton:
--------------
hierarchy: ->GtkWidget->GtkContainer->GtkBin->GtkButton->GtkColorButton
hold: a button widget that displays itself the picked color
ctor: gtk_color_button_new
api: gtkcolorbutton.h
behavior: pressed displays a dialog to select a specific color. These colors
          can be specified as six-digit hexadecimal values or the RGB value.
          The color button itself displays the selected color in a rectangular
          block set as the child widget of the button.


GtkFileChooserButton:
---------------------
hierarchy: ->GtkWidget->GtkContainer->GtkBox->GtkFileChooserButton
hold: a button widget to launch a file selection dialog.
ctor: gtk_file_chooser_button_new
api: gtkfilechooserbutton.h
behavior: an easy method to ask users to choose a file or a folder. It
          implements the GtkFileChooser interface. When the button is clicked
          an instance of GtkFileChooserDialog is opened that allows the user
          to browse and select one file or one folder, depending on the type
          of button you created.


-----------
hierarchy:
hold:
ctor:
api:
behavior:
