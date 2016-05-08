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
  GdkColor light[5];
  GdkColor dark[5];
  GdkColor mid[5];
  GdkColor text[5];
  GdkColor base[5];
  GdkColor text_aa[5];      <Halfway between text/base>

  GdkColor black;
  GdkColor white;
  PangoFontDescription *font_desc;

  gint xthickness;
  gint ythickness;
*/



#include <gtk/gtk.h>
#include <cstdio>  // tmpnam
#include <cstring> // strlen


void save_as (GtkMenuItem* menuitem, gpointer data);
void quit (GtkMenuItem* menuitem, gpointer data);

#define NUM_ENTRIES 3
GtkActionEntry entries[]=
{
	{ "File", NULL, "_File", NULL, NULL, NULL },
	{ "SaveAs", GTK_STOCK_SAVE_AS, NULL, NULL, "SaveAs", G_CALLBACK (save_as)},
	{ "Quit", GTK_STOCK_QUIT, NULL, NULL, "Quit", G_CALLBACK(quit)}
};

struct RCstyle
{
	GtkWidget* wgGtkWidget; GString* rcGtkWidget;
	GtkWidget* wgGtkButton; GString* rcGtkButton;
};

struct Widgets
{
	GtkWidget* window;
	GtkWidget* wgcombobox;
	GtkWidget* w[11][6];
	GtkWidget* table_bn;
	RCstyle*   rcstyle;
};



void colorbn_init (Widgets*);
void colorbn_set  (GtkColorButton*, gpointer);
void wgcombobox_changed (GtkComboBox*, gpointer);
void write_rcGtkWidget (FILE* fp, Widgets* ws);
void write_rcGtkButton (FILE* fp, Widgets* ws);

const char* rcfile=NULL;



int main (int argc, char** argv)
{
	// Temporary rc file
	rcfile = tmpnam(NULL);
	FILE* fp = fopen (rcfile, "w+");
	if (fp == NULL)
	{
		g_print ("cannot write to: %s\n", rcfile);
		return -1;
	}

	const char* content = "# gtk2-style output";
	fwrite (content, sizeof(char), strlen(content), fp);
	fclose (fp);

	// Init & apply style from external file
	gtk_rc_add_default_file (rcfile);

	gtk_init (&argc, &argv);


	// Main window
	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	g_signal_connect (G_OBJECT(window),
	                  "destroy",
	                  G_CALLBACK(gtk_main_quit),
	                  0);


	// Application Menu
	GtkActionGroup* magroup = gtk_action_group_new ("MainActionGroup");
	gtk_action_group_add_actions (magroup, entries, NUM_ENTRIES, NULL);

	GtkUIManager* uimanager = gtk_ui_manager_new ();
	gtk_ui_manager_insert_action_group (uimanager, magroup, 0);
	gtk_ui_manager_add_ui_from_file (uimanager, "menu.ui", NULL);

	GtkWidget* menubar = gtk_ui_manager_get_widget (uimanager, "/MenuBar");

	// Combobox with widgets names
	GtkWidget* wgcombobox = gtk_combo_box_new_text ();
	gtk_combo_box_append_text (GTK_COMBO_BOX(wgcombobox), "widgets");
	gtk_combo_box_append_text (GTK_COMBO_BOX(wgcombobox), "button");
	gtk_combo_box_set_active (GTK_COMBO_BOX(wgcombobox), 0);


	// Widgets to set theme colors
	GtkWidget* table = gtk_table_new (11, 6, true);
	GtkWidget* fglbl      = gtk_label_new ("foreground");
	GtkWidget* bglbl      = gtk_label_new ("background");
	GtkWidget* lightlbl   = gtk_label_new ("light     ");
	GtkWidget* darklbl    = gtk_label_new ("dark      ");
	GtkWidget* midlbl     = gtk_label_new ("mid       ");
	GtkWidget* textlbl    = gtk_label_new ("text      ");
	GtkWidget* baselbl    = gtk_label_new ("base      ");
	GtkWidget* text_aalbl = gtk_label_new ("text_aa   ");
	GtkWidget* blacklbl   = gtk_label_new ("black     ");
	GtkWidget* whitelbl   = gtk_label_new ("white     ");

	GtkWidget* normallbl     = gtk_label_new ("normal");
	GtkWidget* activelbl     = gtk_label_new ("active");
	GtkWidget* prelightlbl   = gtk_label_new ("prelight");
	GtkWidget* selectedlbl   = gtk_label_new ("selected");
	GtkWidget* insensitivelbl= gtk_label_new ("insensitive");

	GtkTable* table_ = GTK_TABLE(table);
	gtk_table_attach (table_, fglbl,0,1,1,2,GTK_SHRINK,GTK_SHRINK,0, 0);
	gtk_table_attach (table_, bglbl,0,1,2,3,GTK_SHRINK,GTK_SHRINK,0, 0);
	gtk_table_attach (table_, lightlbl,0,1,3,4,GTK_SHRINK,GTK_SHRINK,0, 0);
	gtk_table_attach (table_, darklbl,0,1,4,5,GTK_SHRINK,GTK_SHRINK,0, 0);
	gtk_table_attach (table_, midlbl,0,1,5,6,GTK_SHRINK,GTK_SHRINK,0, 0);
	gtk_table_attach (table_, textlbl,0,1,6,7,GTK_SHRINK,GTK_SHRINK,0, 0);
	gtk_table_attach (table_, baselbl,0,1,7,8,GTK_SHRINK,GTK_SHRINK,0, 0);
	gtk_table_attach (table_, text_aalbl,0,1,8,9,GTK_SHRINK,GTK_SHRINK,0, 0);
	gtk_table_attach (table_, blacklbl,0,1,9,10,GTK_SHRINK,GTK_SHRINK,0, 0);
	gtk_table_attach (table_, whitelbl,0,1,10,11,GTK_SHRINK,GTK_SHRINK,0, 0);


	gtk_table_attach (table_, normallbl,1,2,0,1,GTK_SHRINK,GTK_SHRINK,0,0);
	gtk_table_attach (table_, activelbl,2,3,0,1,GTK_SHRINK,GTK_SHRINK,0,0);
	gtk_table_attach (table_, prelightlbl,3,4,0,1,GTK_SHRINK,GTK_SHRINK,0,0);
	gtk_table_attach (table_, selectedlbl,4,5,0,1,GTK_SHRINK,GTK_SHRINK,0,0);
	gtk_table_attach (table_, insensitivelbl,5,6,0,1,GTK_SHRINK,GTK_SHRINK,0,0);


#define FORi(a) for(gint i=0; i < a; ++i)
	GtkWidget* fgclrbn[5];    FORi(5) fgclrbn[i] = gtk_color_button_new();
	GtkWidget* bgclrbn[5];    FORi(5) bgclrbn[i] = gtk_color_button_new();
	GtkWidget* lightclrbn[5]; FORi(5) lightclrbn[i] = gtk_color_button_new();
	GtkWidget* darkclrbn[5];  FORi(5) darkclrbn[i] = gtk_color_button_new();
	GtkWidget* midclrbn[5];   FORi(5) midclrbn[i] = gtk_color_button_new();
	GtkWidget* textclrbn[5];  FORi(5) textclrbn[i] = gtk_color_button_new();
	GtkWidget* baseclrbn[5];  FORi(5) baseclrbn[i] = gtk_color_button_new();
	GtkWidget* txtaaclrbn[5]; FORi(5) txtaaclrbn[i] = gtk_color_button_new();
	GtkWidget* blackclrbn;             blackclrbn = gtk_color_button_new();
	GtkWidget* whiteclrbn;             whiteclrbn = gtk_color_button_new();

	FORi(5) gtk_table_attach (table_,fgclrbn[i],i+1,i+2,1,2,GTK_SHRINK,GTK_SHRINK,0,0);
	FORi(5) gtk_table_attach (table_,bgclrbn[i],i+1,i+2,2,3,GTK_SHRINK,GTK_SHRINK,0,0);
	FORi(5) gtk_table_attach (table_,lightclrbn[i],i+1,i+2,3,4,GTK_SHRINK,GTK_SHRINK,0,0);
	FORi(5) gtk_table_attach (table_,darkclrbn[i],i+1,i+2,4,5,GTK_SHRINK,GTK_SHRINK,0,0);
	FORi(5) gtk_table_attach (table_,midclrbn[i],i+1,i+2,5,6,GTK_SHRINK,GTK_SHRINK,0,0);
	FORi(5) gtk_table_attach (table_,textclrbn[i],i+1,i+2,6,7,GTK_SHRINK,GTK_SHRINK,0,0);
	FORi(5) gtk_table_attach (table_,baseclrbn[i],i+1,i+2,7,8,GTK_SHRINK,GTK_SHRINK,0,0);
	FORi(5) gtk_table_attach (table_,txtaaclrbn[i],i+1,i+2,8,9,GTK_SHRINK,GTK_SHRINK,0,0);
	gtk_table_attach (table_,blackclrbn,1,2,9,10,GTK_SHRINK,GTK_SHRINK,0,0);
	gtk_table_attach (table_,whiteclrbn,1,2,10,11,GTK_SHRINK,GTK_SHRINK,0,0);


	// Widgets for button style
	GtkWidget* table_bn = gtk_table_new (5, 1, TRUE);
	GtkWidget* bn_ok = gtk_button_new_from_stock (GTK_STOCK_OK);
	GtkWidget* bn_cancel = gtk_button_new_from_stock (GTK_STOCK_CANCEL);
	GtkWidget* bn_apply = gtk_button_new_from_stock (GTK_STOCK_APPLY);
	GtkWidget* bn_copy = gtk_button_new_from_stock (GTK_STOCK_COPY);
	GtkWidget* bn_media_play = gtk_button_new_from_stock (GTK_STOCK_MEDIA_PLAY);
	gtk_button_set_relief (GTK_BUTTON(bn_ok), GTK_RELIEF_NORMAL);
	gtk_button_set_relief (GTK_BUTTON(bn_cancel), GTK_RELIEF_HALF);
	gtk_button_set_relief (GTK_BUTTON(bn_apply), GTK_RELIEF_NONE);
	gtk_widget_set_sensitive (bn_copy, FALSE);
	GtkTable* table_bn_ = GTK_TABLE(table_bn);
	gtk_table_attach (table_bn_,bn_ok,        0,1,0,1,GTK_SHRINK,GTK_SHRINK,0,0);
	gtk_table_attach (table_bn_,bn_cancel,    0,1,1,2,GTK_SHRINK,GTK_SHRINK,0,0);
	gtk_table_attach (table_bn_,bn_apply,     0,1,2,3,GTK_SHRINK,GTK_SHRINK,0,0);
	gtk_table_attach (table_bn_,bn_copy,      0,1,3,4,GTK_SHRINK,GTK_SHRINK,0,0);
	gtk_table_attach (table_bn_,bn_media_play,0,1,4,5,GTK_SHRINK,GTK_SHRINK,0,0);


	// Packaging
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	gtk_box_pack_start (GTK_BOX(vbox), menubar, false, false, 0);
	gtk_box_pack_start (GTK_BOX(vbox), wgcombobox, false, false, 0);
	GtkWidget* hbox = gtk_hbox_new (FALSE, 0);
	gtk_box_pack_start (GTK_BOX(vbox), hbox, false, false, 0);
	GtkWidget* vboxl = gtk_vbox_new (FALSE, 0);
	GtkWidget* vboxr = gtk_vbox_new (FALSE, 0);
	gtk_box_pack_start (GTK_BOX(hbox), vboxl, false, false, 0);
	gtk_box_pack_start (GTK_BOX(hbox), vboxr, false, false, 0);
	gtk_container_add (GTK_CONTAINER(window), vbox);

	gtk_box_pack_start (GTK_BOX(vboxl), table, false, false, 0);
	gtk_box_pack_start (GTK_BOX(vboxr), table_bn, false, false, 0);



	// Connecting
	Widgets* ws = g_slice_new (Widgets);
	ws->window = window;
	ws->wgcombobox = wgcombobox;
	ws->w[0][0] = NULL;
	ws->w[1][0] = fglbl;
	ws->w[2][0] = bglbl;
	ws->w[3][0] = lightlbl;
	ws->w[4][0] = darklbl;
	ws->w[5][0] = midlbl;
	ws->w[6][0] = textlbl;
	ws->w[7][0] = baselbl;
	ws->w[8][0] = text_aalbl;
	ws->w[9][0] = blacklbl;
	ws->w[10][0]= whitelbl;

	ws->w[0][1] = normallbl;
	ws->w[0][2] = activelbl;
	ws->w[0][3] = prelightlbl;
	ws->w[0][4] = selectedlbl;
	ws->w[0][5] = insensitivelbl;

	FORi(5) ws->w[1][i+1] = fgclrbn[i];
	FORi(5) ws->w[2][i+1] = bgclrbn[i];
	FORi(5) ws->w[3][i+1] = lightclrbn[i];
	FORi(5) ws->w[4][i+1] = darkclrbn[i];
	FORi(5) ws->w[5][i+1] = midclrbn[i];
	FORi(5) ws->w[6][i+1] = textclrbn[i];
	FORi(5) ws->w[7][i+1] = baseclrbn[i];
	FORi(5) ws->w[8][i+1] = txtaaclrbn[i];
	ws->w[9][1] = blackclrbn;
	FORi(4) ws->w[9][2+i] = NULL;
	ws->w[10][1] = whiteclrbn;
	FORi(4) ws->w[10][2+i] = NULL;

	ws->table_bn = table_bn;

	RCstyle* rcstyle = g_slice_new (RCstyle);
	rcstyle->wgGtkWidget = window;
	rcstyle->rcGtkWidget = g_string_new (NULL);
	rcstyle->wgGtkButton = bn_ok;
	rcstyle->rcGtkButton = g_string_new (NULL);
	ws->rcstyle = rcstyle;


	g_signal_connect (G_OBJECT(ws->wgcombobox),
	                  "changed",
	                  G_CALLBACK(wgcombobox_changed),
	                  ws);

#define FORij(a,b) for(gint i=0; i<a; ++i) for(gint j=0; j<b; ++j)
	FORij(9,5) g_signal_connect (G_OBJECT(ws->w[i+1][j+1]),
	                             "color-set",
	                             G_CALLBACK(colorbn_set),
	                             ws);

	g_signal_connect (G_OBJECT(ws->w[9][1]),
	                  "color-set",
	                  G_CALLBACK(colorbn_set),
	                  ws);
	g_signal_connect (G_OBJECT(ws->w[10][1]),
	                  "color-set",
	                  G_CALLBACK(colorbn_set),
	                  ws);

	colorbn_init (ws);
	gtk_action_group_add_actions (magroup,
	                              entries,
	                              NUM_ENTRIES,
	                              ws);


	// Visibility
	gtk_widget_show_all (window);
	gtk_widget_hide (table_bn);
	gtk_main ();


	// Clean up
	unlink (rcfile);
	g_string_free (rcstyle->rcGtkWidget, TRUE);
	g_string_free (rcstyle->rcGtkButton, TRUE);
	g_slice_free (RCstyle, rcstyle);
	g_slice_free (Widgets, ws);

	return 0;
}

void save_as (GtkMenuItem* menuitem, gpointer data)
{
	GtkWidget* dialog = NULL;
	dialog = gtk_file_chooser_dialog_new ("Save File",
	                                      NULL, //parent_window,
	                                      GTK_FILE_CHOOSER_ACTION_SAVE,
	                                      GTK_STOCK_CANCEL,
	                                      GTK_RESPONSE_CANCEL,
	                                      GTK_STOCK_SAVE,
	                                      GTK_RESPONSE_ACCEPT,
	                                      NULL);

	gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER(dialog),
	                                                TRUE);
	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
	{
		char *filename = NULL;
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		g_print ("Save as: %s\n", filename);
		g_free (filename);
	}
	gtk_widget_destroy (dialog);
}

void quit (GtkMenuItem* menuitem, gpointer data)
{
	gtk_main_quit ();
}

void colorbn_init(Widgets* ws)
{
	GtkComboBox* wgcombobox = GTK_COMBO_BOX(ws->wgcombobox);
	gint active = gtk_combo_box_get_active (wgcombobox);
	GtkWidget* wg = NULL;
	if (active == 0)      /*widgets*/ wg = ws->rcstyle->wgGtkWidget;
	else if (active == 1) /*button*/  wg = ws->rcstyle->wgGtkButton;
	g_print ("active=%d\n", active);

	GtkStyle* sty = gtk_widget_get_style (wg);

	for(gint i=0; i < 5; ++i)
	{
		gtk_color_button_set_color (GTK_COLOR_BUTTON(ws->w[1][i+1]), &(sty->fg[i]));
		gtk_color_button_set_color (GTK_COLOR_BUTTON(ws->w[2][i+1]), &(sty->bg[i]));
		gtk_color_button_set_color (GTK_COLOR_BUTTON(ws->w[3][i+1]), &(sty->light[i]));
		gtk_color_button_set_color (GTK_COLOR_BUTTON(ws->w[4][i+1]), &(sty->dark[i]));
		gtk_color_button_set_color (GTK_COLOR_BUTTON(ws->w[5][i+1]), &(sty->mid[i]));
		gtk_color_button_set_color (GTK_COLOR_BUTTON(ws->w[6][i+1]), &(sty->text[i]));
		gtk_color_button_set_color (GTK_COLOR_BUTTON(ws->w[7][i+1]), &(sty->base[i]));
		gtk_color_button_set_color (GTK_COLOR_BUTTON(ws->w[8][i+1]), &(sty->text_aa[i]));
	}

	gtk_color_button_set_color (GTK_COLOR_BUTTON(ws->w[9][1]), &(sty->black));
	gtk_color_button_set_color (GTK_COLOR_BUTTON(ws->w[10][1]), &(sty->white));
}

void colorbn_set (GtkColorButton* bn, gpointer pws)
{
	// A color has changed in the pannel
	Widgets* ws = (Widgets*)pws;
	GtkWidget* wbn = (GtkWidget*) bn;
	int row = 0;
	int col = 0;

	for (int i=1; i<9; ++i)
	{
		for (int j=1; j<6; ++j)
		{
			if (ws->w[i][j] == wbn)
			{
				row = i;
				col = j;
				//break;
				i = 10;
				j = 7;
			}
		}
	}

	if (row == 0 && col == 0)
	{
		g_print ("cannot find the associated button\n");
		return;
	}

	FILE* fp = fopen(rcfile, "w");
	if (fp == NULL)
	{
		g_print ("cannot write to file: %s\n", rcfile);
		return;
	}

	write_rcGtkWidget (fp, ws);
	write_rcGtkButton (fp, ws);

	fclose (fp);

	gtk_rc_reparse_all ();
}

void wgcombobox_changed (GtkComboBox*, gpointer pws)
{
	Widgets* ws = (Widgets*)pws;
	gint active = gtk_combo_box_get_active (GTK_COMBO_BOX(ws->wgcombobox));

	if (active == 0)      /*widgets*/
	{
		gtk_widget_hide (ws->table_bn);
	}
	else if (active == 1) /*button */
	{
		gtk_widget_show_all (ws->table_bn);
	}

	colorbn_init (ws);
}


void write_rcGtkWidget(FILE* fp, Widgets* ws)
{
	GtkComboBox* wgcombobox = GTK_COMBO_BOX(ws->wgcombobox);
	gint active = gtk_combo_box_get_active (wgcombobox);

	// "widgets" is selected, take the style from the pannel
	if (active == 0)
	{
		GString* rcGtkWidget = ws->rcstyle->rcGtkWidget;
		rcGtkWidget = g_string_set_size (rcGtkWidget, 0);

		const char* color[]={"fg","bg","light","dark","mid","text","base","text_aa"};
		const char* state[]={"NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"};
		const char* black = "black";
		const char* white = "white";

		g_string_append_printf (rcGtkWidget, "%s\n", "style \"widgets\"");
		g_string_append_printf (rcGtkWidget, "%s\n", "{");

		GdkColor clr;
		for (int i=1; i < 9; ++i)
		{
			for (int j=1; j < 6; ++j)
			{
				gtk_color_button_get_color(GTK_COLOR_BUTTON(ws->w[i][j]), &clr);
				if (clr.red == 0 && clr.green == 0 && clr.blue == 0)
					continue;
				g_string_append_printf (rcGtkWidget,
				                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
				                        color[i-1],
				                        state[j-1],
				                        (clr.red * 255)/65535,
				                        (clr.green * 255)/65535,
				                        (clr.blue * 255)/65535);
			}
		}
		gtk_color_button_get_color (GTK_COLOR_BUTTON(ws->w[9][1]), &clr);
		if (clr.red != 0 || clr.green != 0 || clr.blue != 0)
			g_string_append_printf (rcGtkWidget,
			                        "\t%s = \"#%02X%02X%02X\"\n",
			                        black,
			                        (clr.red * 255)/65535,
			                        (clr.green * 255)/65535,
			                        (clr.blue * 255)/65535);
		gtk_color_button_get_color (GTK_COLOR_BUTTON(ws->w[10][1]), &clr);
		if (clr.red != 65535 || clr.green != 65535 || clr.blue != 65535)
			g_string_append_printf (rcGtkWidget,
			                        "\t%s = \"#%02X%02X%02X\"\n",
			                        white,
			                        (clr.red * 255)/65535,
			                        (clr.green * 255)/65535,
			                        (clr.blue * 255)/65535);
		g_string_append_printf (rcGtkWidget, "%s\n", "}");
		g_string_append_printf (rcGtkWidget, "%s\n", "\n");
		g_string_append_printf (rcGtkWidget, "%s\n",
		                        "class \"GtkWidget\" style \"widgets\"\n\n");

		fprintf (fp, "%s", rcGtkWidget->str);
	}
	// another widget name is selected, use saved style.
	else
	{
		GString* rcGtkWidget = ws->rcstyle->rcGtkWidget;
		if (rcGtkWidget->len > 0)
			fprintf (fp, "%s", rcGtkWidget->str);
	}
}


void write_rcGtkButton(FILE* fp, Widgets* ws)
{
	GtkComboBox* wgcombobox = GTK_COMBO_BOX(ws->wgcombobox);
	gint active = gtk_combo_box_get_active (wgcombobox);

	// "button" is selected, take the style from the pannel
	if (active == 1)
	{
		GString* rcGtkButton = ws->rcstyle->rcGtkButton;
		rcGtkButton = g_string_set_size (rcGtkButton, 0);

		const char* color[]={"fg","bg","light","dark","mid","text","base","text_aa"};
		const char* state[]={"NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"};
		const char* black = "black";
		const char* white = "white";

		g_string_append_printf (rcGtkButton, "%s\n", "style \"button\"");
		g_string_append_printf (rcGtkButton, "%s\n", "{");

		GdkColor clr;
		for (int i=1; i < 9; ++i)
		{
			for (int j=1; j < 6; ++j)
			{
				GdkColor clr;
				gtk_color_button_get_color(GTK_COLOR_BUTTON(ws->w[i][j]), &clr);
				if (clr.red == 0 && clr.green == 0 && clr.blue == 0)
					continue;
				// unexpected character '[', expected character ':'
				if (i-1 == 2 || i-1 == 3 || i-1 )
					continue;
				g_string_append_printf (rcGtkButton,
				                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
				                        color[i-1],
				                        state[j-1],
				                        (clr.red * 255)/65535,
				                        (clr.green * 255)/65535,
				                        (clr.blue * 255)/65535);
			}
		}
		gtk_color_button_get_color (GTK_COLOR_BUTTON(ws->w[9][1]), &clr);
		if (clr.red != 0 || clr.green != 0 || clr.blue != 0)
			g_string_append_printf (rcGtkButton,
			                        "\t%s = \"#%02X%02X%02X\"\n",
			                        black,
			                        (clr.red * 255)/65535,
			                        (clr.green * 255)/65535,
			                        (clr.blue * 255)/65535);
		gtk_color_button_get_color (GTK_COLOR_BUTTON(ws->w[10][1]), &clr);
		if (clr.red != 65535 || clr.green != 65535 || clr.blue != 65535)
			g_string_append_printf (rcGtkButton,
			                        "\t%s = \"#%02X%02X%02X\"\n",
			                        white,
			                        (clr.red * 255)/65535,
			                        (clr.green * 255)/65535,
			                        (clr.blue * 255)/65535);
		g_string_append_printf (rcGtkButton, "%s\n", "}");
		g_string_append_printf (rcGtkButton, "%s\n", "\n");
		g_string_append_printf (rcGtkButton, "%s\n",
		                        "class \"GtkButton\" style \"button\"\n\n");

		fprintf (fp, "%s", rcGtkButton->str);
	}
	// another widget name is selected, use saved style.
	else
	{
		GString* rcGtkButton = ws->rcstyle->rcGtkButton;
		if (rcGtkButton->len > 0)
			fprintf (fp, "%s", rcGtkButton->str);
	}
}
