#
#
#
        The entire source code of:
        "Chapter 13 - Putting it all together"
        is in source_code/chapter_13.

/*
https://developer.gnome.org/gtk-tutorial/stable/x477.html

GtkObject
  +GtkWidget
  | +GtkMisc
  | | +GtkLabel                   (yes)
  | | | `GtkAccelLabel
  | | +GtkArrow
  | | `GtkImage                   (yes)
  | +GtkContainer
  | | +GtkBin
  | | | +GtkAlignment
  | | | +GtkFrame                 (yes)
  | | | | `GtkAspectFrame         (yes)
  | | | +GtkButton                (yes)
  | | | | +GtkToggleButton        (yes)
  | | | | | `GtkCheckButton       (yes)
  | | | | |   `GtkRadioButton     (yes)
  | | | | `GtkOptionMenu          (yes)
  | | | +GtkItem
  | | | | +GtkMenuItem            (yes)
  | | | |   +GtkCheckMenuItem     (yes)
  | | | |   | `GtkRadioMenuItem   (yes)
  | | | |   +GtkImageMenuItem     (yes)
  | | | |   +GtkSeparatorMenuItem (yes)
  | | | |   `GtkTearoffMenuItem   (yes)
  | | | +GtkWindow                      (yes)
  | | | | +GtkDialog                    (yes)
  | | | | | +GtkColorSelectionDialog    (yes)
  | | | | | +GtkFileSelection           (yes)
  | | | | | +GtkFontSelectionDialog     (yes)
  | | | | | +GtkInputDialog             (yes)
  | | | | | `GtkMessageDialog           (yes)
  | | | | `GtkPlug
  | | | +GtkEventBox              (yes)
  | | | +GtkHandleBox             (yes)
  | | | +GtkScrolledWindow
  | | | `GtkViewport
  | | +GtkBox
  | | | +GtkButtonBox
  | | | | +GtkHButtonBox
  | | | | `GtkVButtonBox
  | | | +GtkVBox
  | | | | +GtkColorSelection      (yes)
  | | | | +GtkFontSelection       (yes)
  | | | | `GtkGammaCurve          (yes)
  | | | `GtkHBox
  | | |   +GtkCombo               (yes)
  | | |   `GtkStatusbar           (yes)
  | | +GtkFixed
  | | +GtkPaned
  | | | +GtkHPaned
  | | | `GtkVPaned
  | | +GtkLayout
  | | +GtkMenuShell
  | | | +GtkMenuBar               (yes)
  | | | `GtkMenu                  (yes)
  | | +GtkNotebook                (yes)
  | | +GtkSocket
  | | +GtkTable
  | | +GtkTextView
  | | +GtkToolbar                 (yes)
  | | `GtkTreeView
  | +GtkCalendar
  | +GtkDrawingArea
  | | `GtkCurve
  | +GtkEditable
  | | +GtkEntry
  | |   `GtkSpinButton
  | +GtkRuler
  | | +GtkHRuler
  | | `GtkVRuler
  | +GtkRange
  | | +GtkScale
  | | | +GtkHScale
  | | | `GtkVScale
  | | `GtkScrollbar
  | |   +GtkHScrollbar
  | |   `GtkVScrollbar
  | +GtkSeparator
  | | +GtkHSeparator
  | | `GtkVSeparator
  | +GtkInvisible
  | +GtkPreview
  | `GtkProgressBar
  +GtkAdjustment
  +GtkCellRenderer
  | +GtkCellRendererPixbuf
  | +GtkCellRendererText
  | +GtkCellRendererToggle
  +GtkItemFactory
  +GtkTooltips
  `GtkTreeViewColumn
 */

/* Widget states
typedef enum
{
  GTK_STATE_NORMAL,
  GTK_STATE_ACTIVE,
  GTK_STATE_PRELIGHT,
  GTK_STATE_SELECTED,
  GTK_STATE_INSENSITIVE
} GtkStateType;

struct _GtkStyle
{
  GdkColor fg[5];     // 1 color for each GtkStateType
..


struct _GdkColor
{
  guint32 pixel;
  guint16 red;
  guint16 green;
  guint16 blue;
};
*/

/*
  GdkColor fg[5];
  GdkColor bg[5];
  GdkColor light[5];       //not parsed by gtk_rc_parse and friends
  GdkColor dark[5];        //not parsed ..
  GdkColor mid[5];         //not parsed ..
  GdkColor text[5];
  GdkColor base[5];
  GdkColor text_aa[5];     //not parsed .., <Halfway between text/base>

  GdkColor black;          //not parsed
  GdkColor white;          //not parsed
  PangoFontDescription *font_desc;

  gint xthickness;
  gint ythickness;
*/
