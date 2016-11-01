#include <gtk/gtk.h>
#include <cstdio>  // tmpnam
#include <cstring> // strlen
#include <cstdlib> // exit
#include <cctype>  // tolower


void menu_saveas (GtkMenuItem* menuitem, gpointer data);
void menu_quit (GtkMenuItem* menuitem, gpointer data);

#define NUM_ENTRIES 3
GtkActionEntry entries[]=
{
	{ "File", NULL, "_File", NULL, NULL, NULL },
	{ "SaveAs", GTK_STOCK_SAVE_AS, NULL, NULL, "SaveAs", G_CALLBACK (menu_saveas)},
	{ "Quit", GTK_STOCK_QUIT, NULL, NULL, "Quit", G_CALLBACK(menu_quit)}
};


struct AppData
{
	const char* rcfile=NULL;
	GtkWidget* window;
	GtkWidget* vbox;
	// ----- GtkWidget -----
	GtkWidget* widget_0_clrbn[4][5];
	GtkWidget* widget_0_fn_bn;
	GtkWidget* widget_0_spinbn_xth;
	GtkWidget* widget_0_spinbn_yth;
	GtkWidget* widget_0_pixbn[5];
	GString*   widget_0_pixmap[5];
	GtkWidget* widget_0_spinbn_cursorar;
	GtkWidget* widget_0_clrbn_cursorclr;
	GtkWidget* widget_0_spinbn_drawb[4];
	GtkWidget* widget_0_entry_focuslp;
	GtkWidget* widget_0_spinbn_focuslw;
	GtkWidget* widget_0_spinbn_focusp;
	GtkWidget* widget_0_chkbn_interiorf;
	GtkWidget* widget_0_clrbn_linkclr;
	GtkWidget* widget_0_spinbn_scrollahl;
	GtkWidget* widget_0_spinbn_scrollavl;
	GtkWidget* widget_0_clrbn_secondarycurclr;
	GtkWidget* widget_0_spinbn_separatorh;
	GtkWidget* widget_0_spinbn_separatorw;
	GtkWidget* widget_0_clrbn_visitedlnkclr;
	GtkWidget* widget_0_chkbn_wides;
	GString*   widget_0_style_txt;

	// ----- GtkButton -----
	GtkWidget* widget_1_clrbn[4][5];
	GtkWidget* widget_1_fn_bn;
	GtkWidget* widget_1_spinbn_xth;
	GtkWidget* widget_1_spinbn_yth;
	GtkWidget* widget_1_spinbn_childdx;
	GtkWidget* widget_1_spinbn_childdy;
	GtkWidget* widget_1_spinbn_defaultb[4];
	GtkWidget* widget_1_spinbn_defaultob[4];
	GtkWidget* widget_1_chkbn_displacef;
	GtkWidget* widget_1_spinbn_images;
	GtkWidget* widget_1_spinbn_innerb[4];
	GString*   widget_1_style_txt;

	// ----- GtkCheckButton -----
	GtkWidget* widget_2_clrbn[4][5];
	GtkWidget* widget_2_fn_bn;
	GtkWidget* widget_2_spinbn_xth;
	GtkWidget* widget_2_spinbn_yth;
	GtkWidget* widget_2_spinbn_indicatorsz;
	GtkWidget* widget_2_spinbn_indicatorsp;
	GString*   widget_2_style_txt;

	// ----- GtkButtonBox -----
	GtkWidget* widget_3_spinbn_childipx;
	GtkWidget* widget_3_spinbn_childipy;
	GtkWidget* widget_3_spinbn_childmh;
	GtkWidget* widget_3_spinbn_childmw;
	GString*   widget_3_style_txt;

	// ----- GtkComboBox -----
	GtkWidget* widget_4_clrbn[4][5];
	GtkWidget* widget_4_fn_bn;
	GtkWidget* widget_4_spinbn_xth;
	GtkWidget* widget_4_spinbn_yth;
	GtkWidget* widget_4_chkbn_appearsal;
	GtkWidget* widget_4_spinbn_arrowsz;
	GtkWidget* widget_4_cbbox_shadowt;
	GString*   widget_4_style_txt;

	// ----- GtkEntry -----
	GtkWidget* widget_5_clrbn[4][5];
	GtkWidget* widget_5_fn_bn;
	GtkWidget* widget_5_spinbn_xth;
	GtkWidget* widget_5_spinbn_yth;
	GtkWidget* widget_5_chkbn_iconp;
	GtkWidget* widget_5_spinbn_innerb[4];
	GtkWidget* widget_5_spinbn_invisiblec;
	GtkWidget* widget_5_spinbn_progressb[4];
	GtkWidget* widget_5_chkbn_stateh;
	GString*   widget_5_style_txt;

	// ----- GtkExpander -----
	GtkWidget* widget_6_clrbn[4][5];
	GtkWidget* widget_6_fn_bn;
	GtkWidget* widget_6_spinbn_xth;
	GtkWidget* widget_6_spinbn_yth;
	GtkWidget* widget_6_spinbn_expandersz;
	GtkWidget* widget_6_spinbn_expandersp;
	GString*   widget_6_style_txt;

	// ----- GtkScrollbar -----
	GtkWidget* widget_7_chkbn_fixedsl;
	GtkWidget* widget_7_chkbn_hasbs;
	GtkWidget* widget_7_chkbn_hasfs;
	GtkWidget* widget_7_chkbn_hassbs;
	GtkWidget* widget_7_chkbn_hassfs;
	GtkWidget* widget_7_spinbn_minsl;
	GString*   widget_7_style_txt;

	// ----- GtkArrow -----
	GtkWidget* widget_8_spinbn_arrowsc;
	GString*   widget_8_style_txt;

	// ----- GtkProgressBar -----
	GtkWidget* widget_9_clrbn[4][5];
	GtkWidget* widget_9_fn_bn;
	GtkWidget* widget_9_spinbn_xth;
	GtkWidget* widget_9_spinbn_yth;
	GtkWidget* widget_9_spinbn_minhzbarh;
	GtkWidget* widget_9_spinbn_minhzbarw;
	GtkWidget* widget_9_spinbn_minvtbarh;
	GtkWidget* widget_9_spinbn_minvtbarw;
	GtkWidget* widget_9_spinbn_xs;
	GtkWidget* widget_9_spinbn_ys;
	GString*   widget_9_style_txt;

	// ----- GtkSpinButton -----
	GtkWidget* widget_10_cbbox_shadowt;
	GString*   widget_10_style_txt;

	// ----- GtkStatusbar -----
	GtkWidget* widget_11_clrbn[4][5];
	GtkWidget* widget_11_fn_bn;
	GtkWidget* widget_11_spinbn_xth;
	GtkWidget* widget_11_spinbn_yth;
	GtkWidget* widget_11_cbbox_shadowt;
	GString*   widget_11_style_txt;

	// ----- GtkToolbar -----
	GtkWidget* widget_12_clrbn[4][5];
	GtkWidget* widget_12_fn_bn;
	GtkWidget* widget_12_spinbn_xth;
	GtkWidget* widget_12_spinbn_yth;
	GtkWidget* widget_12_cbbox_buttonr;
	GtkWidget* widget_12_spinbn_internalp;
	GtkWidget* widget_12_spinbn_maxce;
	GtkWidget* widget_12_cbbox_shadowt;
	GtkWidget* widget_12_spinbn_spacesz;
	GtkWidget* widget_12_cbbox_spacest;
	GString*   widget_12_style_txt;

	// ----- GtkToolButton -----
	GtkWidget* widget_13_clrbn[4][5];
	GtkWidget* widget_13_fn_bn;
	GtkWidget* widget_13_spinbn_xth;
	GtkWidget* widget_13_spinbn_yth;
	GtkWidget* widget_13_spinbn_iconsp;
	GString*   widget_13_style_txt;

	// ----- GtkMenu -----
	GtkWidget* widget_14_clrbn[4][5];
	GtkWidget* widget_14_fn_bn;
	GtkWidget* widget_14_spinbn_xth;
	GtkWidget* widget_14_spinbn_yth;
	GtkWidget* widget_14_cbbox_arrowp;
	GtkWidget* widget_14_spinbn_arrowsc;
	GtkWidget* widget_14_chkbn_doublea;
	GtkWidget* widget_14_spinbn_horizontaloff;
	GtkWidget* widget_14_spinbn_horizontalpadd;
	GtkWidget* widget_14_spinbn_verticaloff;
	GtkWidget* widget_14_spinbn_verticalpadd;
	GString*   widget_14_style_txt;

	// ----- GtkMenuBar -----
	GtkWidget* widget_15_clrbn[4][5];
	GtkWidget* widget_15_fn_bn;
	GtkWidget* widget_15_spinbn_xth;
	GtkWidget* widget_15_spinbn_yth;
	GtkWidget* widget_15_spinbn_internalp;
	GtkWidget* widget_15_cbbox_shadowt;
	GString*   widget_15_style_txt;

	// ----- GtkMenuItem -----
	GtkWidget* widget_16_clrbn[4][5];
	GtkWidget* widget_16_fn_bn;
	GtkWidget* widget_16_spinbn_xth;
	GtkWidget* widget_16_spinbn_yth;
	GtkWidget* widget_16_spinbn_arrowsc;
	GtkWidget* widget_16_spinbn_arrowsp;
	GtkWidget* widget_16_spinbn_horizontalpadd;
	GtkWidget* widget_16_cbbox_selectedst;
	GtkWidget* widget_16_spinbn_togglesp;
	GtkWidget* widget_16_spinbn_widthc;
	GString*   widget_16_style_txt;

	// ----- GtkCheckMenuItem -----
	GtkWidget* widget_17_spinbn_indicatorsz;
	GString*   widget_17_style_txt;

	// ----- GtkTextView -----
	GtkWidget* widget_18_clrbn[4][5];
	GtkWidget* widget_18_fn_bn;
	GtkWidget* widget_18_spinbn_xth;
	GtkWidget* widget_18_spinbn_yth;
	GtkWidget* widget_18_clrbn_errorundclr;
	GString*   widget_18_style_txt;

	// ----- GtkTreeView -----
	GtkWidget* widget_19_clrbn[4][5];
	GtkWidget* widget_19_fn_bn;
	GtkWidget* widget_19_spinbn_xth;
	GtkWidget* widget_19_spinbn_yth;
	GtkWidget* widget_19_chkbn_allowr;
	GtkWidget* widget_19_clrbn_evenrowclr;
	GtkWidget* widget_19_spinbn_expandersz;
	GtkWidget* widget_19_entry_gridlnpatt;
	GtkWidget* widget_19_spinbn_gridlnw;
	GtkWidget* widget_19_spinbn_horizontalsep;
	GtkWidget* widget_19_chkbn_indentexp;
	GtkWidget* widget_19_clrbn_oddrowclr;
	GtkWidget* widget_19_chkbn_rowenddet;
	GtkWidget* widget_19_entry_treelnpatt;
	GtkWidget* widget_19_spinbn_treelnw;
	GtkWidget* widget_19_spinbn_verticalsep;
	GString*   widget_19_style_txt;

	// ----- GtkIconView -----
	GtkWidget* widget_20_clrbn[4][5];
	GtkWidget* widget_20_fn_bn;
	GtkWidget* widget_20_spinbn_xth;
	GtkWidget* widget_20_spinbn_yth;
	GtkWidget* widget_20_spinbn_selectionboxa;
	GtkWidget* widget_20_clrbn_selectionboxclr;
	GString*   widget_20_style_txt;

	// ----- GtkAssistant -----
	GtkWidget* widget_21_clrbn[4][5];
	GtkWidget* widget_21_fn_bn;
	GtkWidget* widget_21_spinbn_xth;
	GtkWidget* widget_21_spinbn_yth;
	GtkWidget* widget_21_spinbn_contentpadd;
	GtkWidget* widget_21_spinbn_headerpadd;
	GString*   widget_21_style_txt;

	// ----- GtkDialog -----
	GtkWidget* widget_22_clrbn[4][5];
	GtkWidget* widget_22_fn_bn;
	GtkWidget* widget_22_spinbn_xth;
	GtkWidget* widget_22_spinbn_yth;
	GtkWidget* widget_22_spinbn_actionab;
	GtkWidget* widget_22_spinbn_buttonsp;
	GtkWidget* widget_22_spinbn_contentab;
	GtkWidget* widget_22_spinbn_contentas;
	GString*   widget_22_style_txt;

	// ----- GtkMessageDialog -----
	GtkWidget* widget_23_clrbn[4][5];
	GtkWidget* widget_23_fn_bn;
	GtkWidget* widget_23_spinbn_xth;
	GtkWidget* widget_23_spinbn_yth;
	GtkWidget* widget_23_spinbn_messageb;
	GtkWidget* widget_23_chkbn_usesep;
	GString*   widget_23_style_txt;

	// ----- GtkNotebook -----
	GtkWidget* widget_24_clrbn[4][5];
	GtkWidget* widget_24_fn_bn;
	GtkWidget* widget_24_spinbn_xth;
	GtkWidget* widget_24_spinbn_yth;
	GtkWidget* widget_24_spinbn_arrowsp;
	GtkWidget* widget_24_chkbn_hasbs;
	GtkWidget* widget_24_chkbn_hasfs;
	GtkWidget* widget_24_chkbn_hassbs;
	GtkWidget* widget_24_chkbn_hassfs;
	GtkWidget* widget_24_spinbn_tabcurv;
	GtkWidget* widget_24_spinbn_tabover;
	GString*   widget_24_style_txt;

	// ----- GtkPaned -----
	GtkWidget* widget_25_spinbn_handlesz;
	GString*   widget_25_style_txt;

	// ----- GtkRange -----
	GtkWidget* widget_26_chkbn_activatesld;
	GtkWidget* widget_26_spinbn_arrowdx;
	GtkWidget* widget_26_spinbn_arrowdy;
	GtkWidget* widget_26_spinbn_arrowsc;
	GtkWidget* widget_26_spinbn_sliderw;
	GtkWidget* widget_26_chkbn_stepperpd;
	GtkWidget* widget_26_spinbn_steppersz;
	GtkWidget* widget_26_spinbn_steppersp;
	GtkWidget* widget_26_spinbn_troughb;
	GtkWidget* widget_26_chkbn_throughsdet;
	GtkWidget* widget_26_chkbn_throughustep;
	GString*   widget_26_style_txt;

	// ----- GtkScale -----
	GtkWidget* widget_27_spinbn_sliderl;
	GtkWidget* widget_27_spinbn_valuesp;
	GString*   widget_27_style_txt;

	// ----- GtkScrolledWindow -----
	GtkWidget* widget_28_clrbn[4][5];
	GtkWidget* widget_28_fn_bn;
	GtkWidget* widget_28_spinbn_xth;
	GtkWidget* widget_28_spinbn_yth;
	GtkWidget* widget_28_spinbn_scrollbarsp;
	GtkWidget* widget_28_chkbn_scrollbarswb;
	GString*   widget_28_style_txt;
};
AppData* app;


// GtkWidget sytle methods and callbacks
void cb_color_set (GtkColorButton*, gpointer);
void cb_font_set (GtkFontButton*, gpointer);
void cb_spinbn_value_changed (GtkSpinButton*, gpointer);
void cb_0_pixbn_clicked (GtkButton*, gpointer); // for bg_pixmap but broken.
void cb_entry_activate(GtkEntry*,  gpointer);
void cb_chkbn_clicked (GtkButton*, gpointer);
void cb_cbbox_changed (GtkComboBox*, gpointer);


// Main application RC methods
void write_rc_for_gtkwidget();
void write_rc_for_gtkbutton();
void write_rc_for_gtkcheckbutton();
void write_rc_for_gtkbuttonbox();
void write_rc_for_gtkcombobox();
void write_rc_for_gtkentry();
void write_rc_for_gtkexpander();
void write_rc_for_gtkscrollbar();
void write_rc_for_gtkarrow();
void write_rc_for_gtkprogressbar();
void write_rc_for_gtkspinbutton();
void write_rc_for_gtkstatusbar();
void write_rc_for_gtktoolbar();
void write_rc_for_gtktoolbutton();
void write_rc_for_gtkmenu();
void write_rc_for_gtkmenubar();
void write_rc_for_gtkmenuitem();
void write_rc_for_gtkcheckmenuitem();
void write_rc_for_gtktextview();
void write_rc_for_gtktreeview();
void write_rc_for_gtkiconview();
void write_rc_for_gtkassistant();
void write_rc_for_gtkdialog();
void write_rc_for_gtkmessagedialog();
void write_rc_for_gtknotebook();
void write_rc_for_gtkpaned();
void write_rc_for_gtkrange();
void write_rc_for_gtkscale();
void write_rc_for_gtkscrolledwindow();
void write_rc_for_all();

// Main application UI methods
void ui_create_gtkwidget();
void ui_update_gtkwidget();
void ui_delete_gtkwidget();
void ui_create_gtkbutton();
void ui_update_gtkbutton();
void ui_delete_gtkbutton();
void ui_create_gtkcheckbutton();
void ui_update_gtkcheckbutton();
void ui_delete_gtkcheckbutton();
void ui_create_gtkbuttonbox();
void ui_update_gtkbuttonbox();
void ui_delete_gtkbuttonbox();
void ui_create_gtkcombobox();
void ui_update_gtkcombobox();
void ui_delete_gtkcombobox();
void ui_create_gtkentry();
void ui_update_gtkentry();
void ui_delete_gtkentry();
void ui_create_gtkexpander();
void ui_update_gtkexpander();
void ui_delete_gtkexpander();
void ui_create_gtkscrollbar();
void ui_update_gtkscrollbar();
void ui_delete_gtkscrollbar();
void ui_create_gtkarrow();
void ui_update_gtkarrow();
void ui_delete_gtkarrow();
void ui_create_gtkprogressbar();
void ui_update_gtkprogressbar();
void ui_delete_gtkprogressbar();
void ui_create_gtkspinbutton();
void ui_update_gtkspinbutton();
void ui_delete_gtkspinbutton();
void ui_create_gtkstatusbar();
void ui_update_gtkstatusbar();
void ui_delete_gtkstatusbar();
void ui_create_gtktoolbar();
void ui_update_gtktoolbar();
void ui_delete_gtktoolbar();
void ui_create_gtktoolbutton();
void ui_update_gtktoolbutton();
void ui_delete_gtktoolbutton();
void ui_create_gtkmenu();
void ui_update_gtkmenu();
void ui_delete_gtkmenu();
void ui_create_gtkmenubar();
void ui_update_gtkmenubar();
void ui_delete_gtkmenubar();
void ui_create_gtkmenuitem();
void ui_update_gtkmenuitem();
void ui_delete_gtkmenuitem();
void ui_create_gtkcheckmenuitem();
void ui_update_gtkcheckmenuitem();
void ui_delete_gtkcheckmenuitem();
void ui_create_gtktextview();
void ui_update_gtktextview();
void ui_delete_gtktextview();
void ui_create_gtktreeview();
void ui_update_gtktreeview();
void ui_delete_gtktreeview();
void ui_create_gtkiconview();
void ui_update_gtkiconview();
void ui_delete_gtkiconview();
void ui_create_gtkassistant();
void ui_update_gtkassistant();
void ui_delete_gtkassistant();
void ui_create_gtkdialog();
void ui_update_gtkdialog();
void ui_delete_gtkdialog();
void ui_create_gtkmessagedialog();
void ui_update_gtkmessagedialog();
void ui_delete_gtkmessagedialog();
void ui_create_gtknotebook();
void ui_update_gtknotebook();
void ui_delete_gtknotebook();
void ui_create_gtkpaned();
void ui_update_gtkpaned();
void ui_delete_gtkpaned();
void ui_create_gtkrange();
void ui_update_gtkrange();
void ui_delete_gtkrange();
void ui_create_gtkscale();
void ui_update_gtkscale();
void ui_delete_gtkscale();
void ui_create_gtkscrolledwindow();
void ui_update_gtkscrolledwindow();
void ui_delete_gtkscrolledwindow();


int main (int argc, char** argv)
{
	app = g_slice_new(AppData);
	if (app == NULL)
	{
		g_print ("Cannot allocate memory.\n");
		return -1;
	}

	// Temporary rc file
	app->rcfile = tmpnam(NULL);
	FILE* fp = fopen (app->rcfile, "w");
	if (fp == NULL)
	{
		g_print ("cannot write to: %s\n", app->rcfile);
		return -1;
	}

	const char* content = "# gtk2-style output";
	fwrite (content, sizeof(char), strlen(content), fp);
	fclose (fp);

	// Init & apply style from external file
	gtk_rc_add_default_file (app->rcfile);
	gtk_init (&argc, &argv);


	// Main window
	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	app->window = window;
	gtk_window_set_title (GTK_WINDOW(window), "gtk2-styles");
	gtk_window_set_default_size (GTK_WINDOW(window), 500, 600);
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
	gtk_action_group_add_actions (magroup,
	                              entries,
	                              NUM_ENTRIES,
	                              NULL);


	// Scrolled window
	GtkWidget* scrolled_win = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled_win),
	                                GTK_POLICY_AUTOMATIC,
	                                GTK_POLICY_AUTOMATIC);


	// Setup the main window
	GtkWidget* pvbox = gtk_vbox_new (FALSE, 0); // parent vbox
	gtk_box_pack_start (GTK_BOX(pvbox),
	                    menubar,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	gtk_box_pack_start (GTK_BOX(pvbox), scrolled_win, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER(window), pvbox);
	app->vbox = gtk_vbox_new (FALSE, 0);
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW(scrolled_win),
	                                       app->vbox);

	// Create UI for each widget
	ui_create_gtkwidget ();
	ui_create_gtkbutton ();
	ui_create_gtkcheckbutton ();
	ui_create_gtkbuttonbox ();
	ui_create_gtkcombobox ();
	ui_create_gtkentry ();
	ui_create_gtkexpander ();
	ui_create_gtkscrollbar ();
	ui_create_gtkarrow ();
	ui_create_gtkprogressbar ();
	ui_create_gtkspinbutton ();
	ui_create_gtkstatusbar ();
	ui_create_gtktoolbar ();
	ui_create_gtktoolbutton ();
	ui_create_gtkmenu ();
	ui_create_gtkmenubar ();
	ui_create_gtkmenuitem ();
	ui_create_gtkcheckmenuitem ();
	ui_create_gtktextview ();
	ui_create_gtktreeview ();
	ui_create_gtkiconview ();
	ui_create_gtkassistant ();
	ui_create_gtkdialog ();
	ui_create_gtkmessagedialog ();
	ui_create_gtknotebook ();
	ui_create_gtkpaned ();
	ui_create_gtkrange ();
	ui_create_gtkscale ();
	ui_create_gtkscrolledwindow ();


	// Visibility
	gtk_widget_show_all (window);
	gtk_main ();


	// Delete resources other than UI
	ui_delete_gtkwidget ();
	ui_delete_gtkbutton ();
	ui_delete_gtkcheckbutton ();
	ui_delete_gtkbuttonbox ();
	ui_delete_gtkcombobox ();
	ui_delete_gtkentry ();
	ui_delete_gtkexpander ();
	ui_delete_gtkscrollbar ();
	ui_delete_gtkarrow ();
	ui_delete_gtkprogressbar ();
	ui_delete_gtkspinbutton ();
	ui_delete_gtkstatusbar ();
	ui_delete_gtktoolbar ();
	ui_delete_gtktoolbutton ();
	ui_delete_gtkmenu ();
	ui_delete_gtkmenubar ();
	ui_delete_gtkmenuitem ();
	ui_delete_gtkcheckmenuitem ();
	ui_delete_gtktextview ();
	ui_delete_gtktreeview ();
	ui_delete_gtkiconview ();
	ui_delete_gtkassistant ();
	ui_delete_gtkdialog ();
	ui_delete_gtkmessagedialog ();
	ui_delete_gtknotebook ();
	ui_delete_gtkpaned ();
	ui_delete_gtkrange ();
	ui_delete_gtkscale ();
	ui_delete_gtkscrolledwindow ();


	// Clean up
	unlink (app->rcfile);
	g_slice_free(AppData, app);

	return 0;
}

void menu_saveas (GtkMenuItem* menuitem, gpointer data)
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

void menu_quit (GtkMenuItem* menuitem, gpointer data)
{
	gtk_main_quit ();
}

// ----- GtkWidget style methods and callbacks -----
//
void cb_color_set (GtkColorButton*, gpointer papp)
{
	write_rc_for_all ();
}

void cb_font_set (GtkFontButton*, gpointer)
{
	write_rc_for_all ();
}

void cb_spinbn_value_changed (GtkSpinButton*, gpointer)
{
	write_rc_for_all ();
}

void cb_0_pixbn_clicked (GtkButton* bn, gpointer)
{
	GtkWidget* dialog = NULL;
	dialog = gtk_file_chooser_dialog_new ("Select a pixmap file",
	                                      NULL, //parent_window,
	                                      GTK_FILE_CHOOSER_ACTION_OPEN,
	                                      GTK_STOCK_CANCEL,
	                                      GTK_RESPONSE_CANCEL,
	                                      GTK_STOCK_OPEN,
	                                      GTK_RESPONSE_ACCEPT,
	                                      NULL);
	gtk_file_chooser_set_select_multiple (GTK_FILE_CHOOSER(dialog), FALSE);
	gtk_file_chooser_set_create_folders (GTK_FILE_CHOOSER(dialog), FALSE);

	GtkFileFilter* xpmfilter = gtk_file_filter_new ();
	gtk_file_filter_set_name    (xpmfilter, "*.xpm");
	gtk_file_filter_add_pattern (xpmfilter, "*.xpm");
	gtk_file_chooser_add_filter (GTK_FILE_CHOOSER(dialog), xpmfilter);
	GtkFileFilter* allfilter = gtk_file_filter_new ();
	gtk_file_filter_set_name    (allfilter, "*.*");
	gtk_file_filter_add_pattern (allfilter, "*.*");
	gtk_file_chooser_add_filter (GTK_FILE_CHOOSER(dialog), allfilter);

	gboolean bwrite_rc = false;

	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
	{
		char *filename = NULL;
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		g_print ("Pixmap file: %s\n", filename);
		size_t len = strlen(filename);
		const gchar* ext = strstr (filename, ".xpm");
		if (ext != 0)
		{
			const char* filebeg = &(filename[len]);
			while (--filebeg != filename && *filebeg != '/');
			if (*filebeg == '/') ++filebeg;

			const gint TABLE_0_COL = 6;
			for (int j=1; j<TABLE_0_COL; ++j)
				if (GTK_WIDGET(bn) == app->widget_0_pixbn[j-1])
				{
					GString* newstr =
						g_string_assign (app->widget_0_pixmap[j-1], filebeg);
					app->widget_0_pixmap[j-1] = newstr; // modified GString*
					g_print ("copied .xpm = %s\n", filebeg);
					gtk_button_set_label (GTK_BUTTON (app->widget_0_pixbn[j-1]),
					                      "set");

					// update ui
					bwrite_rc = true;
				}
		}
		else // a different extension cancels previous pixmap
		{
			const gint TABLE_0_COL = 6;
			for (int j=1; j<TABLE_0_COL; ++j)
				if (GTK_WIDGET(bn) == app->widget_0_pixbn[j-1])
				{
					size_t len = strlen (app->widget_0_pixmap[j-1]->str);
					if (len > 0)
					{
						GString* newstr =
							g_string_erase (app->widget_0_pixmap[j-1], 0, -1);
						app->widget_0_pixmap[j-1] = newstr;
						g_print ("reset bp_pixmap[%d]\n", j-1);
						gtk_button_set_label (
							GTK_BUTTON(app->widget_0_pixbn[j-1]),
							"null");

						// update ui
						bwrite_rc = true;
					}
				}
		}
		g_free (filename);
	}
	gtk_widget_destroy (dialog);

	if (bwrite_rc)
		write_rc_for_all ();
}

void cb_entry_activate(GtkEntry*,  gpointer)
{
	write_rc_for_all ();
}

void cb_chkbn_clicked (GtkButton*, gpointer)
{
	write_rc_for_all ();
}

void cb_cbbox_changed (GtkComboBox*, gpointer)
{
	write_rc_for_all ();
}


// ----- Main application RC methods -----
//
void write_rc_for_gtkwidget()
{
	if (app->widget_0_style_txt == NULL) exit(-1);
	app->widget_0_style_txt = g_string_set_size (app->widget_0_style_txt, 0);

	const gchar* gtkstyle="gtkwidget";
	g_string_append_printf (app->widget_0_style_txt,
	                        "style \"%s\"\n{\n",
	                        gtkstyle);

	// ----- style begin -----
	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {"NORMAL",
	                         "ACTIVE",
	                         "PRELIGHT",
	                         "SELECTED",
	                         "INSENSITIVE"};
	for (gint i=0; i<4; ++i)
	{
		for (gint j=0; j<5; ++j)
		{
			GdkColor clr;
			gtk_color_button_get_color (
				GTK_COLOR_BUTTON(app->widget_0_clrbn[i][j]),
				&clr);

			g_string_append_printf (app->widget_0_style_txt,
			                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
			                        style[i],
			                        state[j],
			                        (clr.red * 255 / 65535),
			                        (clr.green * 255 / 65535),
			                        (clr.blue * 255 / 65535));
		}
		g_string_append_printf (app->widget_0_style_txt, "%s", "\n");
	}

	for (int j=0; j<5; ++j)
	{
		if (strlen(app->widget_0_pixmap[j]->str) > 0)
		{
			g_string_append_printf (app->widget_0_style_txt,
			                        "\tbg_pixmap[%s] = \"%s\"\n",
			                        state[j],
			                        app->widget_0_pixmap[j]->str);
		}
	}

	const gchar* font_name = gtk_font_button_get_font_name(
                            GTK_FONT_BUTTON(app->widget_0_fn_bn));
	g_string_append_printf (app->widget_0_style_txt,
	                        "\n\tfont_name = \"%s\"\n",
	                        font_name);

	gint xthickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_0_spinbn_xth));
	gint ythickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_0_spinbn_yth));
	g_string_append_printf (app->widget_0_style_txt,
	                        "\n\txthickness = %d\n",
	                        xthickness);
	g_string_append_printf (app->widget_0_style_txt,
	                        "\tythickness = %d\n",
	                        ythickness);

	/*  When written outside style brackets the parser aborts with warning:
	    /tmp/fileNnGs:85 error: unexpected character ':', expected character '='
	 */
	gdouble cursorar = gtk_spin_button_get_value(
                            GTK_SPIN_BUTTON(app->widget_0_spinbn_cursorar));
	g_string_append_printf (app->widget_0_style_txt,
	                        "\n\tGtkWidget::cursor-aspect-ratio = %.2f\n",
	                        cursorar);

	GdkColor cursorclr;
	gtk_color_button_get_color (
		GTK_COLOR_BUTTON(app->widget_0_clrbn_cursorclr), &cursorclr);
	g_string_append_printf (app->widget_0_style_txt,
	                        "\tGtkWidget::cursor-color = \"#%02X%02X%02X\"\n",
	                        (cursorclr.red * 255 / 65535),
	                        (cursorclr.green * 255 / 65535),
	                        (cursorclr.blue * 255 / 65535));

	gint drawb_left   = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_0_spinbn_drawb[0]));
	gint drawb_right  = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_0_spinbn_drawb[1]));
	gint drawb_top    = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_0_spinbn_drawb[2]));
	gint drawb_bottom = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_0_spinbn_drawb[3]));

	g_string_append_printf (app->widget_0_style_txt,
	                        "\tGtkWidget::draw-border = {%d, %d, %d, %d}\n",
	                        drawb_left,
	                        drawb_right,
	                        drawb_top,
	                        drawb_bottom);

	const gchar* focuslp = gtk_entry_get_text (
                            GTK_ENTRY(app->widget_0_entry_focuslp));
	g_string_append_printf (app->widget_0_style_txt,
	                        "\tGtkWidget::focus-line-pattern = \"%s\"\n",
	                        focuslp);

	gint focuslw = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_0_spinbn_focuslw));
	g_string_append_printf (app->widget_0_style_txt,
	                        "\tGtkWidget::focus-line-width = %d\n",
	                        focuslw);

	gint focusp = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_0_spinbn_focusp));
	g_string_append_printf (app->widget_0_style_txt,
	                        "\tGtkWidget::focus-padding = %d\n",
	                        focusp);

	gboolean interiorf = gtk_toggle_button_get_active (
                            GTK_TOGGLE_BUTTON(app->widget_0_chkbn_interiorf));
	g_string_append_printf (app->widget_0_style_txt,
	                        "\tGtkWidget::interior-focus = %d\n",
	                        interiorf == true ? 1 : 0);

	GdkColor linkclr;
	gtk_color_button_get_color (
                            GTK_COLOR_BUTTON(app->widget_0_clrbn_linkclr),
                            &linkclr);
	g_string_append_printf (app->widget_0_style_txt,
	                        "\tGtkWidget::link-color = \"#%02X%02X%02X\"\n",
	                        (linkclr.red * 255 / 65535),
	                        (linkclr.green * 255 / 65535),
	                        (linkclr.blue * 255 / 65535));

	gint scrollahl = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_0_spinbn_scrollahl));
	g_string_append_printf (app->widget_0_style_txt,
	                        "\tGtkWidget::scroll-arrow-hlength = %d\n",
	                        scrollahl);

	gint scrollavl = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_0_spinbn_scrollavl));
	g_string_append_printf (app->widget_0_style_txt,
	                        "\tGtkWidget::scroll-arrow-vlength = %d\n",
	                        scrollavl);

	GdkColor secondarycurclr;
	gtk_color_button_get_color (
                          GTK_COLOR_BUTTON(app->widget_0_clrbn_secondarycurclr),
                            &secondarycurclr);
	g_string_append_printf (app->widget_0_style_txt,
	                "\tGtkWidget::secondary-cursor-color = \"#%02X%02X%02X\"\n",
	                        (secondarycurclr.red * 255 / 65535),
	                        (secondarycurclr.green * 255 / 65535),
	                        (secondarycurclr.blue * 255 / 65535));

	gint separatorh = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_0_spinbn_separatorh));
	g_string_append_printf (app->widget_0_style_txt,
	                        "\tGtkWidget::separator-height = %d\n",
	                        separatorh);

	gint separatorw = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_0_spinbn_separatorw));
	g_string_append_printf (app->widget_0_style_txt,
	                        "\tGtkWidget::separator-width = %d\n",
	                        separatorw);

	GdkColor visitedlnkclr;
	gtk_color_button_get_color (
		GTK_COLOR_BUTTON(app->widget_0_clrbn_visitedlnkclr),
		&visitedlnkclr);
	g_string_append_printf (app->widget_0_style_txt,
                        "\tGtkWidget::visited-link-color = \"#%02X%02X%02X\"\n",
	                        (visitedlnkclr.red * 255 / 65535),
	                        (visitedlnkclr.green * 255 / 65535),
	                        (visitedlnkclr.blue * 255 / 65535));

	gboolean wides = gtk_toggle_button_get_active (
                              GTK_TOGGLE_BUTTON(app->widget_0_chkbn_wides));
	g_string_append_printf (app->widget_0_style_txt,
	                        "\tGtkWidget::wide-separators = %d\n",
	                        wides == true ? 1 : 0);

	// ----- style end   -----
	g_string_append_printf (app->widget_0_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_0_style_txt,
	                        "class \"GtkWidget\" style \"%s\"\n",
	                        gtkstyle);

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_0_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkbutton()
{
	if (app->widget_1_style_txt == NULL) exit(-1);
	app->widget_1_style_txt = g_string_set_size (app->widget_1_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtkbutton";
	g_string_append_printf (app->widget_1_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {"NORMAL",
	                         "ACTIVE",
	                         "PRELIGHT",
	                         "SELECTED",
	                         "INSENSITIVE"};
	for (gint i=0; i<4; ++i)
	{
		for (gint j=0; j<5; ++j)
		{
			GdkColor clr;
			gtk_color_button_get_color (
				GTK_COLOR_BUTTON(app->widget_1_clrbn[i][j]),
				&clr);

			g_string_append_printf (app->widget_1_style_txt,
			                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
			                        style[i],
			                        state[j],
			                        (clr.red * 255 / 65535),
			                        (clr.green * 255 / 65535),
			                        (clr.blue * 255 / 65535));
		}
		g_string_append_printf (app->widget_1_style_txt, "%s", "\n");
	}


	const gchar* font_name = gtk_font_button_get_font_name (
                            GTK_FONT_BUTTON(app->widget_1_fn_bn));
	g_string_append_printf (app->widget_1_style_txt,
	                        "\n\tfont_name = \"%s\"\n",
	                        font_name);

	gint xthickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_1_spinbn_xth));
	gint ythickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_1_spinbn_yth));
	g_string_append_printf (app->widget_1_style_txt,
	                        "\n\txthickness = %d\n",
	                        xthickness);
	g_string_append_printf (app->widget_1_style_txt,
	                        "\tythickness = %d\n",
	                        ythickness);


	gint childdx = gtk_spin_button_get_value_as_int(
                                 GTK_SPIN_BUTTON(app->widget_1_spinbn_childdx));
	gint childdy = gtk_spin_button_get_value_as_int(
                                 GTK_SPIN_BUTTON(app->widget_1_spinbn_childdy));
	g_string_append_printf (app->widget_1_style_txt,
	                        "\n\tGtkButton::child-displacement-x = %d\n",
	                        childdx);
	g_string_append_printf (app->widget_1_style_txt,
	                        "\tGtkButton::child-displacement-y = %d\n",
	                        childdy);

	gint defaultb_left   = gtk_spin_button_get_value_as_int(
                             GTK_SPIN_BUTTON(app->widget_1_spinbn_defaultb[0]));
	gint defaultb_right  = gtk_spin_button_get_value_as_int(
                             GTK_SPIN_BUTTON(app->widget_1_spinbn_defaultb[1]));
	gint defaultb_top    = gtk_spin_button_get_value_as_int(
                             GTK_SPIN_BUTTON(app->widget_1_spinbn_defaultb[2]));
	gint defaultb_bottom = gtk_spin_button_get_value_as_int(
                             GTK_SPIN_BUTTON(app->widget_1_spinbn_defaultb[3]));

	g_string_append_printf (app->widget_1_style_txt,
	                        "\tGtkButton::default-border = {%d, %d, %d, %d}\n",
	                        defaultb_left,
	                        defaultb_right,
	                        defaultb_top,
	                        defaultb_bottom);

	gint defaultob_left   = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_1_spinbn_defaultob[0]));
	gint defaultob_right  = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_1_spinbn_defaultob[1]));
	gint defaultob_top    = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_1_spinbn_defaultob[2]));
	gint defaultob_bottom = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_1_spinbn_defaultob[3]));

	g_string_append_printf (app->widget_1_style_txt,
                     "\tGtkButton::default-outside-border = {%d, %d, %d, %d}\n",
	                        defaultob_left,
	                        defaultob_right,
	                        defaultob_top,
	                        defaultob_bottom);

	gboolean displacef = gtk_toggle_button_get_active (
                            GTK_TOGGLE_BUTTON(app->widget_1_chkbn_displacef));
	g_string_append_printf (app->widget_1_style_txt,
	                        "\tGtkButton::displace-focus = %d\n",
	                        displacef == true ? 1 : 0);

	gint images = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_1_spinbn_images));
	g_string_append_printf (app->widget_1_style_txt,
	                        "\tGtkButton::image-spacing = %d\n",
	                        images);

	gint innerb_left   = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_1_spinbn_innerb[0]));
	gint innerb_right  = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_1_spinbn_innerb[1]));
	gint innerb_top    = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_1_spinbn_innerb[2]));
	gint innerb_bottom = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_1_spinbn_innerb[3]));

	g_string_append_printf (app->widget_1_style_txt,
	                        "\tGtkButton::inner-border = {%d, %d, %d, %d}\n",
	                        innerb_left,
	                        innerb_right,
	                        innerb_top,
	                        innerb_bottom);

	// ----- style end   -----

	g_string_append_printf (app->widget_1_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_1_style_txt,
	                        "class \"GtkButton\" style \"%s\"\n",
	                        gtkstyle);

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_1_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkcheckbutton()
{
	if (app->widget_2_style_txt == NULL) exit(-1);
	app->widget_2_style_txt = g_string_set_size (app->widget_2_style_txt, 0);

	const gchar* gtkparentstyle="gtkbutton";
	const gchar* gtkstyle="gtkcheckbutton";
	g_string_append_printf (app->widget_2_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {"NORMAL",
	                         "ACTIVE",
	                         "PRELIGHT",
	                         "SELECTED",
	                         "INSENSITIVE"};
	for (gint i=0; i<4; ++i)
	{
		for (gint j=0; j<5; ++j)
		{
			GdkColor clr;
			gtk_color_button_get_color (
				GTK_COLOR_BUTTON(app->widget_2_clrbn[i][j]),
				&clr);

			g_string_append_printf (app->widget_2_style_txt,
			                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
			                        style[i],
			                        state[j],
			                        (clr.red * 255 / 65535),
			                        (clr.green * 255 / 65535),
			                        (clr.blue * 255 / 65535));
		}
		g_string_append_printf (app->widget_2_style_txt, "%s", "\n");
	}


	const gchar* font_name = gtk_font_button_get_font_name (
                            GTK_FONT_BUTTON(app->widget_2_fn_bn));
	g_string_append_printf (app->widget_2_style_txt,
	                        "\n\tfont_name = \"%s\"\n",
	                        font_name);

	gint xthickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_2_spinbn_xth));
	gint ythickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_2_spinbn_yth));

	g_string_append_printf (app->widget_2_style_txt,
	                        "\n\txthickness = %d\n",
	                        xthickness);
	g_string_append_printf (app->widget_2_style_txt,
	                        "\tythickness = %d\n",
	                        ythickness);

	gint indicatorsz = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_2_spinbn_indicatorsz));
	g_string_append_printf (app->widget_2_style_txt,
	                        "\n\tGtkCheckButton::indicator-size = %d\n",
	                        indicatorsz);

	gint indicatorsp = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_2_spinbn_indicatorsp));
	g_string_append_printf (app->widget_2_style_txt,
	                        "\tGtkCheckButton::indicator-spacing = %d\n",
	                        indicatorsp);

	// ----- style end -----

	g_string_append_printf (app->widget_2_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_2_style_txt,
	                        "class \"GtkCheckButton\" style \"%s\"\n",
	                        gtkstyle);

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_2_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkbuttonbox()
{
	if (app->widget_3_style_txt == NULL) exit(-1);
	app->widget_3_style_txt = g_string_set_size (app->widget_3_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtkbuttonbox";
	g_string_append_printf (app->widget_3_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	gint childpx = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_3_spinbn_childipx));
	g_string_append_printf (app->widget_3_style_txt,
	                        "\tGtkButtonBox::child-internal-pad-x = %d\n",
	                        childpx);

	gint childpy = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_3_spinbn_childipy));
	g_string_append_printf (app->widget_3_style_txt,
	                        "\tGtkButtonBox::child-internal-pad-y = %d\n",
	                        childpy);

	gint childmh = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_3_spinbn_childmh));
	g_string_append_printf (app->widget_3_style_txt,
	                        "\tGtkButtonBox::child-min-height = %d\n",
	                        childmh);

	gint childmw = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_3_spinbn_childmw));
	g_string_append_printf (app->widget_3_style_txt,
	                        "\tGtkButtonBox::child-min-width = %d\n",
	                        childmw);

	// ----- style end -----
	g_string_append_printf (app->widget_3_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_3_style_txt,
	                        "class \"GtkButtonBox\" style \"%s\"\n",
	                        gtkstyle);

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_3_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkcombobox()
{
	if (app->widget_4_style_txt == NULL) exit(-1);
	app->widget_4_style_txt = g_string_set_size (app->widget_4_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtkcombobox";
	g_string_append_printf (app->widget_4_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {"NORMAL",
	                         "ACTIVE",
	                         "PRELIGHT",
	                         "SELECTED",
	                         "INSENSITIVE"};
	for (gint i=0; i<4; ++i)
	{
		for (gint j=0; j<5; ++j)
		{
			GdkColor clr;
			gtk_color_button_get_color (
				GTK_COLOR_BUTTON(app->widget_4_clrbn[i][j]),
				&clr);

			g_string_append_printf (app->widget_4_style_txt,
			                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
			                        style[i],
			                        state[j],
			                        (clr.red * 255 / 65535),
			                        (clr.green * 255 / 65535),
			                        (clr.blue * 255 / 65535));
		}
		g_string_append_printf (app->widget_4_style_txt, "%s", "\n");
	}


	const gchar* font_name = gtk_font_button_get_font_name (
                            GTK_FONT_BUTTON(app->widget_4_fn_bn));
	g_string_append_printf (app->widget_4_style_txt,
	                        "\n\tfont_name = \"%s\"\n",
	                        font_name);

	gint xthickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_4_spinbn_xth));
	gint ythickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_4_spinbn_yth));
	g_string_append_printf (app->widget_4_style_txt,
	                        "\n\txthickness = %d\n",
	                        xthickness);
	g_string_append_printf (app->widget_4_style_txt,
	                        "\tythickness = %d\n",
	                        ythickness);

	gboolean appearsal = gtk_toggle_button_get_active (
                            GTK_TOGGLE_BUTTON(app->widget_4_chkbn_appearsal));
	g_string_append_printf (app->widget_4_style_txt,
	                        "\n\tGtkComboBox::appears-as-list = %d\n",
	                        appearsal == true ? 1 : 0);

	gint arrowsz = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_4_spinbn_arrowsz));
	g_string_append_printf (app->widget_4_style_txt,
	                        "\tGtkComboBox::arrow-size = %d\n",
	                        arrowsz);

	gint shadowti = gtk_combo_box_get_active (
                           GTK_COMBO_BOX(app->widget_4_cbbox_shadowt));
	const gchar* shadowts = "GTK_SHADOW_NONE";
	if (shadowti == 1) shadowts = "GTK_SHADOW_IN";
	else if (shadowti == 2) shadowts = "GTK_SHADOW_OUT";
	else if (shadowti == 3) shadowts = "GTK_SHADOW_ETCHED_IN";
	else if (shadowti == 4) shadowts = "GTK_SHADOW_ETCHED_OUT";
	g_string_append_printf (app->widget_4_style_txt,
	                        "\tGtkComboBox::shadow-type = %s\n",
	                        shadowts);

	// ----- style end   -----

	g_string_append_printf (app->widget_4_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_4_style_txt,
	                        "class \"GtkComboBox\" style \"%s\"\n",
	                        gtkstyle);

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_4_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkentry()
{
	if (app->widget_5_style_txt == NULL) exit(-1);
	app->widget_5_style_txt = g_string_set_size (app->widget_5_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtkentry";
	g_string_append_printf (app->widget_5_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {"NORMAL",
	                         "ACTIVE",
	                         "PRELIGHT",
	                         "SELECTED",
	                         "INSENSITIVE"};
	for (gint i=0; i<4; ++i)
	{
		for (gint j=0; j<5; ++j)
		{
			GdkColor clr;
			gtk_color_button_get_color (
				GTK_COLOR_BUTTON(app->widget_5_clrbn[i][j]),
				&clr);

			g_string_append_printf (app->widget_5_style_txt,
			                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
			                        style[i],
			                        state[j],
			                        (clr.red * 255 / 65535),
			                        (clr.green * 255 / 65535),
			                        (clr.blue * 255 / 65535));
		}
		g_string_append_printf (app->widget_5_style_txt, "%s", "\n");
	}


	const gchar* font_name = gtk_font_button_get_font_name (
                            GTK_FONT_BUTTON(app->widget_5_fn_bn));
	g_string_append_printf (app->widget_5_style_txt,
	                        "\n\tfont_name = \"%s\"\n",
	                        font_name);

	gint xthickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_5_spinbn_xth));
	gint ythickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_5_spinbn_yth));
	g_string_append_printf (app->widget_5_style_txt,
	                        "\n\txthickness = %d\n",
	                        xthickness);
	g_string_append_printf (app->widget_5_style_txt,
	                        "\tythickness = %d\n",
	                        ythickness);

	gboolean iconp = gtk_toggle_button_get_active (
                            GTK_TOGGLE_BUTTON(app->widget_5_chkbn_iconp));
	g_string_append_printf (app->widget_5_style_txt,
	                        "\n\tGtkEntry::icon-prelight = %d\n",
	                        iconp == true ? 1 : 0);

	gint innerb_left   = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_5_spinbn_innerb[0]));
	gint innerb_right  = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_5_spinbn_innerb[1]));
	gint innerb_top    = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_5_spinbn_innerb[2]));
	gint innerb_bottom = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_5_spinbn_innerb[3]));
	g_string_append_printf (app->widget_5_style_txt,
	                        "\tGtkEntry::inner-border = {%d, %d, %d, %d}\n",
	                        innerb_left,
	                        innerb_right,
	                        innerb_top,
	                        innerb_bottom);

	gint invisiblec = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_5_spinbn_invisiblec));
	g_string_append_printf (app->widget_5_style_txt,
	                        "\tGtkEntry::invisible-char = %d\n",
	                        invisiblec);

	gint progressb_left   = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_5_spinbn_progressb[0]));
	gint progressb_right  = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_5_spinbn_progressb[1]));
	gint progressb_top    = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_5_spinbn_progressb[2]));
	gint progressb_bottom = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_5_spinbn_progressb[3]));
	g_string_append_printf (app->widget_5_style_txt,
                            "\tGtkEntry::progress-border = {%d, %d, %d, %d}\n",
	                        progressb_left,
	                        progressb_right,
	                        progressb_top,
	                        progressb_bottom);

	gboolean stateh = gtk_toggle_button_get_active (
                            GTK_TOGGLE_BUTTON(app->widget_5_chkbn_stateh));
	g_string_append_printf (app->widget_5_style_txt,
	                        "\tGtkEntry::state-hint = %d\n",
	                        stateh == true ? 1 : 0);

	// ----- style end   -----

	g_string_append_printf (app->widget_5_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_5_style_txt,
	                        "class \"GtkEntry\" style \"%s\"\n",
	                        gtkstyle);

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_5_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkexpander()
{
	if (app->widget_6_style_txt == NULL) exit(-1);
	app->widget_6_style_txt = g_string_set_size (app->widget_6_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtkexpander";
	g_string_append_printf (app->widget_6_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {"NORMAL",
	                         "ACTIVE",
	                         "PRELIGHT",
	                         "SELECTED",
	                         "INSENSITIVE"};
	for (gint i=0; i<4; ++i)
	{
		for (gint j=0; j<5; ++j)
		{
			GdkColor clr;
			gtk_color_button_get_color (
				GTK_COLOR_BUTTON(app->widget_6_clrbn[i][j]),
				&clr);

			g_string_append_printf (app->widget_6_style_txt,
			                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
			                        style[i],
			                        state[j],
			                        (clr.red * 255 / 65535),
			                        (clr.green * 255 / 65535),
			                        (clr.blue * 255 / 65535));
		}
		g_string_append_printf (app->widget_6_style_txt, "%s", "\n");
	}


	const gchar* font_name = gtk_font_button_get_font_name (
                            GTK_FONT_BUTTON(app->widget_6_fn_bn));
	g_string_append_printf (app->widget_6_style_txt,
	                        "\n\tfont_name = \"%s\"\n",
	                        font_name);

	gint xthickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_6_spinbn_xth));
	gint ythickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_6_spinbn_yth));
	g_string_append_printf (app->widget_6_style_txt,
	                        "\n\txthickness = %d\n",
	                        xthickness);
	g_string_append_printf (app->widget_6_style_txt,
	                        "\tythickness = %d\n",
	                        ythickness);

	gint expandersz = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_6_spinbn_expandersz));
	g_string_append_printf (app->widget_6_style_txt,
	                        "\n\tGtkExpander::expander-size = %d\n",
	                        expandersz);

	gint expandersp = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_6_spinbn_expandersp));
	g_string_append_printf (app->widget_6_style_txt,
	                        "\tGtkExpander::expander-spacing = %d\n",
	                        expandersp);

	// ----- style end -----

	g_string_append_printf (app->widget_6_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_6_style_txt,
	                        "class \"GtkExpander\" style \"%s\"\n",
	                        gtkstyle);

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_6_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkscrollbar()
{
	if (app->widget_7_style_txt == NULL) exit(-1);
	app->widget_7_style_txt = g_string_set_size (app->widget_7_style_txt, 0);

	const gchar* gtkparentstyle="gtkrange";
	const gchar* gtkstyle="gtkscrollbar";
	g_string_append_printf (app->widget_7_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	gboolean fixedsl = gtk_toggle_button_get_active (
                            GTK_TOGGLE_BUTTON(app->widget_7_chkbn_fixedsl));
	g_string_append_printf (app->widget_7_style_txt,
	                        "\tGtkScrollbar::fixed-slider-length = %d\n",
	                        fixedsl == true ? 1 : 0);

	gboolean hasbs = gtk_toggle_button_get_active (
                            GTK_TOGGLE_BUTTON(app->widget_7_chkbn_hasbs));
	g_string_append_printf (app->widget_7_style_txt,
	                        "\tGtkScrollbar::has-backward-stepper = %d\n",
	                        hasbs == true ? 1 : 0);

	gboolean hasfs = gtk_toggle_button_get_active (
                            GTK_TOGGLE_BUTTON(app->widget_7_chkbn_hasfs));
	g_string_append_printf (app->widget_7_style_txt,
	                        "\tGtkScrollbar::has-forward-stepper = %d\n",
	                        hasfs == true ? 1 : 0);

	gboolean hassbs = gtk_toggle_button_get_active (
                            GTK_TOGGLE_BUTTON(app->widget_7_chkbn_hassbs));
	g_string_append_printf (app->widget_7_style_txt,
	                    "\tGtkScrollbar::has-secondary-backward-stepper = %d\n",
	                        hassbs == true ? 1 : 0);

	gboolean hassfs = gtk_toggle_button_get_active (
                            GTK_TOGGLE_BUTTON(app->widget_7_chkbn_hassfs));
	g_string_append_printf (app->widget_7_style_txt,
	                    "\tGtkScrollbar::has-secondary-forward-stepper = %d\n",
	                        hassfs == true ? 1 : 0);

	gint minsl = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_7_spinbn_minsl));
	g_string_append_printf (app->widget_7_style_txt,
	                        "\tGtkScrollbar::min-slider-length = %d\n",
	                        minsl);

	// ----- style end -----

	g_string_append_printf (app->widget_7_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_7_style_txt,
	                        "class \"GtkScrollbar\" style \"%s\"\n",
	                        gtkstyle);

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_7_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkarrow()
{
	if (app->widget_8_style_txt == NULL) exit(-1);
	app->widget_8_style_txt = g_string_set_size (app->widget_8_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtkarrow";
	g_string_append_printf (app->widget_8_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	gdouble arrowsc = gtk_spin_button_get_value(
                            GTK_SPIN_BUTTON(app->widget_8_spinbn_arrowsc));
	g_string_append_printf (app->widget_8_style_txt,
	                        "\tGtkArrow::arrow-scaling = %0.2f\n",
	                        arrowsc);

	// ----- style end -----

	g_string_append_printf (app->widget_8_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_8_style_txt,
	                        "class \"GtkArrow\" style \"%s\"\n",
	                        gtkstyle);

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_8_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkprogressbar()
{
	if (app->widget_9_style_txt == NULL) exit(-1);
	app->widget_9_style_txt = g_string_set_size (app->widget_9_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtkprogressbar";
	g_string_append_printf (app->widget_9_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {"NORMAL",
	                         "ACTIVE",
	                         "PRELIGHT",
	                         "SELECTED",
	                         "INSENSITIVE"};
	for (gint i=0; i<4; ++i)
	{
		for (gint j=0; j<5; ++j)
		{
			GdkColor clr;
			gtk_color_button_get_color (
				GTK_COLOR_BUTTON(app->widget_9_clrbn[i][j]),
				&clr);

			g_string_append_printf (app->widget_9_style_txt,
			                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
			                        style[i],
			                        state[j],
			                        (clr.red * 255 / 65535),
			                        (clr.green * 255 / 65535),
			                        (clr.blue * 255 / 65535));
		}
		g_string_append_printf (app->widget_9_style_txt, "%s", "\n");
	}


	const gchar* font_name = gtk_font_button_get_font_name (
                            GTK_FONT_BUTTON(app->widget_9_fn_bn));
	g_string_append_printf (app->widget_9_style_txt,
	                        "\n\tfont_name = \"%s\"\n",
	                        font_name);

	gint xthickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_9_spinbn_xth));
	gint ythickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_9_spinbn_yth));
	g_string_append_printf (app->widget_9_style_txt,
	                        "\n\txthickness = %d\n",
	                        xthickness);
	g_string_append_printf (app->widget_9_style_txt,
	                        "\tythickness = %d\n",
	                        ythickness);

	gint minhzbarh = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_9_spinbn_minhzbarh));
	g_string_append_printf (app->widget_9_style_txt,
	                        "\tGtkprogressBar::min-horizontal-bar-height = %d\n",
	                        minhzbarh);

	gint minhzbarw = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_9_spinbn_minhzbarw));
	g_string_append_printf (app->widget_9_style_txt,
	                        "\tGtkprogressBar::min-horizontal-bar-width = %d\n",
	                        minhzbarw);

	gint minvtbarh = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_9_spinbn_minvtbarh));
	g_string_append_printf (app->widget_9_style_txt,
	                        "\tGtkprogressBar::min-vertical-bar-height = %d\n",
	                        minvtbarh);

	gint minvtbarw = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_9_spinbn_minvtbarw));
	g_string_append_printf (app->widget_9_style_txt,
	                        "\tGtkprogressBar::min-vertical-bar-width = %d\n",
	                        minvtbarw);

	gint xspacing = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_9_spinbn_xs));
	g_string_append_printf (app->widget_9_style_txt,
	                        "\tGtkprogressBar::xspacing = %d\n",
	                        xspacing);

	gint yspacing = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_9_spinbn_ys));
	g_string_append_printf (app->widget_9_style_txt,
	                        "\tGtkprogressBar::yspacing = %d\n",
	                        yspacing);

	// ----- style end   -----

	g_string_append_printf (app->widget_9_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_9_style_txt,
	                        "class \"GtkProgressBar\" style \"%s\"\n",
	                        gtkstyle);

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_9_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkspinbutton()
{
	if (app->widget_10_style_txt == NULL) exit(-1);
	app->widget_10_style_txt = g_string_set_size (app->widget_10_style_txt, 0);

	const gchar* gtkparentstyle="gtkentry";
	const gchar* gtkstyle="gtkspinbutton";
	g_string_append_printf (app->widget_10_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	gint shadowti = gtk_combo_box_get_active (
                           GTK_COMBO_BOX(app->widget_10_cbbox_shadowt));
	const gchar* shadowts = "GTK_SHADOW_NONE";
	if (shadowti == 1) shadowts = "GTK_SHADOW_IN";
	else if (shadowti == 2) shadowts = "GTK_SHADOW_OUT";
	else if (shadowti == 3) shadowts = "GTK_SHADOW_ETCHED_IN";
	else if (shadowti == 4) shadowts = "GTK_SHADOW_ETCHED_OUT";
	g_string_append_printf (app->widget_10_style_txt,
	                        "\tGtkSpinButton::shadow-type = %s\n",
	                        shadowts);

	// ----- style end -----

	g_string_append_printf (app->widget_10_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_10_style_txt,
	                        "class \"GtkSpinButton\" style \"%s\"\n",
	                        gtkstyle);

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_10_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkstatusbar()
{
	if (app->widget_11_style_txt == NULL) exit(-1);
	app->widget_11_style_txt = g_string_set_size (app->widget_11_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtkstatusbar";
	g_string_append_printf (app->widget_11_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {"NORMAL",
	                         "ACTIVE",
	                         "PRELIGHT",
	                         "SELECTED",
	                         "INSENSITIVE"};
	for (gint i=0; i<4; ++i)
	{
		for (gint j=0; j<5; ++j)
		{
			GdkColor clr;
			gtk_color_button_get_color (
				GTK_COLOR_BUTTON(app->widget_11_clrbn[i][j]),
				&clr);

			g_string_append_printf (app->widget_11_style_txt,
			                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
			                        style[i],
			                        state[j],
			                        (clr.red * 255 / 65535),
			                        (clr.green * 255 / 65535),
			                        (clr.blue * 255 / 65535));
		}
		g_string_append_printf (app->widget_11_style_txt, "%s", "\n");
	}


	const gchar* font_name = gtk_font_button_get_font_name (
                            GTK_FONT_BUTTON(app->widget_11_fn_bn));
	g_string_append_printf (app->widget_11_style_txt,
	                        "\n\tfont_name = \"%s\"\n",
	                        font_name);

	gint xthickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_11_spinbn_xth));
	gint ythickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_11_spinbn_yth));
	g_string_append_printf (app->widget_11_style_txt,
	                        "\n\txthickness = %d\n",
	                        xthickness);
	g_string_append_printf (app->widget_11_style_txt,
	                        "\tythickness = %d\n",
	                        ythickness);

	gint shadowti = gtk_combo_box_get_active (
                           GTK_COMBO_BOX(app->widget_11_cbbox_shadowt));
	const gchar* shadowts = "GTK_SHADOW_NONE";
	if (shadowti == 1) shadowts = "GTK_SHADOW_IN";
	else if (shadowti == 2) shadowts = "GTK_SHADOW_OUT";
	else if (shadowti == 3) shadowts = "GTK_SHADOW_ETCHED_IN";
	else if (shadowti == 4) shadowts = "GTK_SHADOW_ETCHED_OUT";
	g_string_append_printf (app->widget_11_style_txt,
	                        "\n\tGtkStatusBar::shadow-type = %s\n",
	                        shadowts);

	// ----- style end   -----

	g_string_append_printf (app->widget_11_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_11_style_txt,
	                        "class \"GtkStatusBar\" style \"%s\"\n",
	                        gtkstyle);

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_11_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtktoolbar()
{
	if (app->widget_12_style_txt == NULL) exit(-1);
	app->widget_12_style_txt = g_string_set_size (app->widget_12_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtktoolbar";
	g_string_append_printf (app->widget_12_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {"NORMAL",
	                         "ACTIVE",
	                         "PRELIGHT",
	                         "SELECTED",
	                         "INSENSITIVE"};
	for (gint i=0; i<4; ++i)
	{
		for (gint j=0; j<5; ++j)
		{
			GdkColor clr;
			gtk_color_button_get_color (
				GTK_COLOR_BUTTON(app->widget_12_clrbn[i][j]),
				&clr);

			g_string_append_printf (app->widget_12_style_txt,
			                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
			                        style[i],
			                        state[j],
			                        (clr.red * 255 / 65535),
			                        (clr.green * 255 / 65535),
			                        (clr.blue * 255 / 65535));
		}
		g_string_append_printf (app->widget_12_style_txt, "%s", "\n");
	}


	const gchar* font_name = gtk_font_button_get_font_name (
                            GTK_FONT_BUTTON(app->widget_12_fn_bn));
	g_string_append_printf (app->widget_12_style_txt,
	                        "\n\tfont_name = \"%s\"\n",
	                        font_name);

	gint xthickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_12_spinbn_xth));
	gint ythickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_12_spinbn_yth));
	g_string_append_printf (app->widget_12_style_txt,
	                        "\n\txthickness = %d\n",
	                        xthickness);
	g_string_append_printf (app->widget_12_style_txt,
	                        "\tythickness = %d\n",
	                        ythickness);

	gint buttonri = gtk_combo_box_get_active (
                           GTK_COMBO_BOX(app->widget_12_cbbox_buttonr));
	const gchar* buttonrs = "GTK_RELIEF_NORMAL";
	if (buttonri == 1) buttonrs = "GTK_RELIEF_HALF";
	else if (buttonri == 2) buttonrs = "GTK_RELIEF_NONE";
	g_string_append_printf (app->widget_12_style_txt,
	                        "\n\tGtkReliefStyle::button-relief = %s\n",
	                        buttonrs);

	gint internalp = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_12_spinbn_internalp));
	g_string_append_printf (app->widget_12_style_txt,
	                        "\tGtkToolbar::internal-padding = %d\n",
	                        internalp);

	gint maxce = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_12_spinbn_maxce));
	g_string_append_printf (app->widget_12_style_txt,
	                        "\tGtkToolbar::max-child-expand = %d\n",
	                        maxce);

	gint shadowti = gtk_combo_box_get_active (
                           GTK_COMBO_BOX(app->widget_12_cbbox_shadowt));
	const gchar* shadowts = "GTK_SHADOW_NONE";
	if (shadowti == 1) shadowts = "GTK_SHADOW_IN";
	else if (shadowti == 2) shadowts = "GTK_SHADOW_OUT";
	else if (shadowti == 3) shadowts = "GTK_SHADOW_ETCHED_IN";
	else if (shadowti == 4) shadowts = "GTK_SHADOW_ETCHED_OUT";
	g_string_append_printf (app->widget_12_style_txt,
	                        "\tGtkToolbar::shadow-type = %s\n",
	                        shadowts);

	gint spacesz = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_12_spinbn_spacesz));
	g_string_append_printf (app->widget_12_style_txt,
	                        "\tGtkToolbar::space-size = %d\n",
	                        spacesz);

	gint spacesti = gtk_combo_box_get_active (
                           GTK_COMBO_BOX(app->widget_12_cbbox_spacest));
	const gchar* spacests = "GTK_TOOLBAR_SPACE_EMPTY";
	if (spacesti == 1) spacests = "GTK_TOOLBAR_SPACE_LINE";
	g_string_append_printf (app->widget_12_style_txt,
	                        "\tGtkToolbar::space-style = %s\n",
	                        spacests);

	// ----- style end -----

	g_string_append_printf (app->widget_12_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_12_style_txt,
	                        "class \"GtkToolbar\" style \"%s\"\n",
	                        gtkstyle);

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_12_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtktoolbutton()
{
	if (app->widget_13_style_txt == NULL) exit(-1);
	app->widget_13_style_txt = g_string_set_size (app->widget_13_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtktoolbutton";
	g_string_append_printf (app->widget_13_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {"NORMAL",
	                         "ACTIVE",
	                         "PRELIGHT",
	                         "SELECTED",
	                         "INSENSITIVE"};
	for (gint i=0; i<4; ++i)
	{
		for (gint j=0; j<5; ++j)
		{
			GdkColor clr;
			gtk_color_button_get_color (
				GTK_COLOR_BUTTON(app->widget_13_clrbn[i][j]),
				&clr);

			g_string_append_printf (app->widget_13_style_txt,
			                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
			                        style[i],
			                        state[j],
			                        (clr.red * 255 / 65535),
			                        (clr.green * 255 / 65535),
			                        (clr.blue * 255 / 65535));
		}
		g_string_append_printf (app->widget_13_style_txt, "%s", "\n");
	}


	const gchar* font_name = gtk_font_button_get_font_name (
                            GTK_FONT_BUTTON(app->widget_13_fn_bn));
	g_string_append_printf (app->widget_13_style_txt,
	                        "\n\tfont_name = \"%s\"\n",
	                        font_name);

	gint xthickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_13_spinbn_xth));
	gint ythickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_13_spinbn_yth));
	g_string_append_printf (app->widget_13_style_txt,
	                        "\n\txthickness = %d\n",
	                        xthickness);
	g_string_append_printf (app->widget_13_style_txt,
	                        "\tythickness = %d\n",
	                        ythickness);

	gint iconsp = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_13_spinbn_iconsp));
	g_string_append_printf (app->widget_13_style_txt,
	                        "\n\tGtkToolButton::icon-spacing = %d\n",
	                        iconsp);

	// ----- style end   -----

	g_string_append_printf (app->widget_13_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_13_style_txt,
	                        "class \"GtkToolButton\" style \"%s\"\n",
	                        gtkstyle);

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_13_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkmenu()
{
	if (app->widget_14_style_txt == NULL) exit(-1);
	app->widget_14_style_txt = g_string_set_size (app->widget_14_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtkmenu";
	g_string_append_printf (app->widget_14_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {"NORMAL",
	                         "ACTIVE",
	                         "PRELIGHT",
	                         "SELECTED",
	                         "INSENSITIVE"};
	for (gint i=0; i<4; ++i)
	{
		for (gint j=0; j<5; ++j)
		{
			GdkColor clr;
			gtk_color_button_get_color (
				GTK_COLOR_BUTTON(app->widget_14_clrbn[i][j]),
				&clr);

			g_string_append_printf (app->widget_14_style_txt,
			                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
			                        style[i],
			                        state[j],
			                        (clr.red * 255 / 65535),
			                        (clr.green * 255 / 65535),
			                        (clr.blue * 255 / 65535));
		}
		g_string_append_printf (app->widget_14_style_txt, "%s", "\n");
	}


	const gchar* font_name = gtk_font_button_get_font_name (
                            GTK_FONT_BUTTON(app->widget_14_fn_bn));
	g_string_append_printf (app->widget_14_style_txt,
	                        "\n\tfont_name = \"%s\"\n",
	                        font_name);

	gint xthickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_14_spinbn_xth));
	gint ythickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_14_spinbn_yth));
	g_string_append_printf (app->widget_14_style_txt,
	                        "\n\txthickness = %d\n",
	                        xthickness);
	g_string_append_printf (app->widget_14_style_txt,
	                        "\tythickness = %d\n",
	                        ythickness);

	gint arrowpi = gtk_combo_box_get_active (
                           GTK_COMBO_BOX(app->widget_14_cbbox_arrowp));
	const gchar* arrowps = "GTK_ARROWS_BOTH";
	if (arrowpi == 1) arrowps = "GTK_ARROWS_START";
	else if (arrowpi == 2) arrowps = "GTK_ARROWS_END";
	g_string_append_printf (app->widget_14_style_txt,
	                        "\n\tGtkMenu::arrow-placement = %s\n",
	                        arrowps);

	gdouble arrowsc = gtk_spin_button_get_value(
                            GTK_SPIN_BUTTON(app->widget_14_spinbn_arrowsc));
	g_string_append_printf (app->widget_14_style_txt,
	                        "\tGtkMenu::arrow-scaling = %.02f\n",
	                        arrowsc);

	gboolean doublea = gtk_toggle_button_get_active (
                            GTK_TOGGLE_BUTTON(app->widget_14_chkbn_doublea));
	g_string_append_printf (app->widget_14_style_txt,
	                        "\tGtkMenu::double-arrows = %d\n",
	                        doublea == true ? 1 : 0);

	gint horizontaloff = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_14_spinbn_horizontaloff));
	g_string_append_printf (app->widget_14_style_txt,
	                        "\tGtkMenu::horizontal-offset = %d\n",
	                        horizontaloff);

	gint horizontalpadd = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_14_spinbn_horizontalpadd));
	g_string_append_printf (app->widget_14_style_txt,
	                        "\tGtkMenu::horizontal-padding = %d\n",
	                        horizontalpadd);

	gint verticaloff = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_14_spinbn_verticaloff));
	g_string_append_printf (app->widget_14_style_txt,
	                        "\tGtkMenu::vertical-offset = %d\n",
	                        verticaloff);

	gint verticalpadd = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_14_spinbn_verticalpadd));
	g_string_append_printf (app->widget_14_style_txt,
	                        "\tGtkMenu::vertical-padding = %d\n",
	                        verticalpadd);

	// ----- style end -----

	g_string_append_printf (app->widget_14_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_14_style_txt,
	                        "class \"GtkMenu\" style \"%s\"\n",
	                        gtkstyle);

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_14_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkmenubar()
{
	if (app->widget_15_style_txt == NULL) exit(-1);
	app->widget_15_style_txt = g_string_set_size (app->widget_15_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtkmenubar";
	g_string_append_printf (app->widget_15_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {"NORMAL",
	                         "ACTIVE",
	                         "PRELIGHT",
	                         "SELECTED",
	                         "INSENSITIVE"};
	for (gint i=0; i<4; ++i)
	{
		for (gint j=0; j<5; ++j)
		{
			GdkColor clr;
			gtk_color_button_get_color (
				GTK_COLOR_BUTTON(app->widget_15_clrbn[i][j]),
				&clr);

			g_string_append_printf (app->widget_15_style_txt,
			                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
			                        style[i],
			                        state[j],
			                        (clr.red * 255 / 65535),
			                        (clr.green * 255 / 65535),
			                        (clr.blue * 255 / 65535));
		}
		g_string_append_printf (app->widget_15_style_txt, "%s", "\n");
	}


	const gchar* font_name = gtk_font_button_get_font_name (
                            GTK_FONT_BUTTON(app->widget_15_fn_bn));
	g_string_append_printf (app->widget_15_style_txt,
	                        "\n\tfont_name = \"%s\"\n",
	                        font_name);

	gint xthickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_15_spinbn_xth));
	gint ythickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_15_spinbn_yth));
	g_string_append_printf (app->widget_15_style_txt,
	                        "\n\txthickness = %d\n",
	                        xthickness);
	g_string_append_printf (app->widget_15_style_txt,
	                        "\tythickness = %d\n",
	                        ythickness);

	gint internalp = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_15_spinbn_internalp));
	g_string_append_printf (app->widget_15_style_txt,
	                        "\n\tGtkMenuBar::internal-padding = %d\n",
	                        internalp);

	gint shadowti = gtk_combo_box_get_active (
                            GTK_COMBO_BOX(app->widget_15_cbbox_shadowt));
	const gchar* shadowts = "GTK_SHADOW_NONE";
	if (shadowti == 1) shadowts = "GTK_SHADOW_IN";
	else if (shadowti == 2) shadowts = "GTK_SHADOW_OUT";
	else if (shadowti == 3) shadowts = "GTK_SHADOW_ETCHED_IN";
	else if (shadowti == 4) shadowts = "GTK_SHADOW_ETCHED_OUT";
	g_string_append_printf (app->widget_15_style_txt,
	                        "\tGtkMenuBar::shadow-type = %s\n",
	                        shadowts);

	// ----- style end -----

	g_string_append_printf (app->widget_15_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_15_style_txt,
	                        "class \"GtkMenuBar\" style \"%s\"\n",
	                        gtkstyle);

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_15_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkmenuitem()
{
	if (app->widget_16_style_txt == NULL) exit(-1);
	app->widget_16_style_txt = g_string_set_size (app->widget_16_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtkmenuitem";
	g_string_append_printf (app->widget_16_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {"NORMAL",
	                         "ACTIVE",
	                         "PRELIGHT",
	                         "SELECTED",
	                         "INSENSITIVE"};
	for (gint i=0; i<4; ++i)
	{
		for (gint j=0; j<5; ++j)
		{
			GdkColor clr;
			gtk_color_button_get_color (
				GTK_COLOR_BUTTON(app->widget_16_clrbn[i][j]),
				&clr);

			g_string_append_printf (app->widget_16_style_txt,
			                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
			                        style[i],
			                        state[j],
			                        (clr.red * 255 / 65535),
			                        (clr.green * 255 / 65535),
			                        (clr.blue * 255 / 65535));
		}
		g_string_append_printf (app->widget_16_style_txt, "%s", "\n");
	}


	const gchar* font_name = gtk_font_button_get_font_name (
                            GTK_FONT_BUTTON(app->widget_16_fn_bn));
	g_string_append_printf (app->widget_16_style_txt,
	                        "\n\tfont_name = \"%s\"\n",
	                        font_name);

	gint xthickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_16_spinbn_xth));
	gint ythickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_16_spinbn_yth));
	g_string_append_printf (app->widget_16_style_txt,
	                        "\n\txthickness = %d\n",
	                        xthickness);
	g_string_append_printf (app->widget_16_style_txt,
	                        "\tythickness = %d\n",
	                        ythickness);

	gdouble arrowsc = gtk_spin_button_get_value(
                            GTK_SPIN_BUTTON(app->widget_16_spinbn_arrowsc));
	g_string_append_printf (app->widget_16_style_txt,
	                        "\n\tGtkMenuItem::arrow-scaling = %.02f\n",
	                        arrowsc);

	gint arrowsp = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_16_spinbn_arrowsp));
	g_string_append_printf (app->widget_16_style_txt,
	                        "\tGtkMenuItem::arrow-spacing = %d\n",
	                        arrowsp);

	gint horizontalpadd = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_16_spinbn_horizontalpadd));
	g_string_append_printf (app->widget_16_style_txt,
	                        "\tGtkMenuItem::horizontal-padding = %d\n",
	                        horizontalpadd);

	gint shadowti = gtk_combo_box_get_active (
                           GTK_COMBO_BOX(app->widget_16_cbbox_selectedst));
	const gchar* shadowts = "GTK_SHADOW_NONE";
	if (shadowti == 1) shadowts = "GTK_SHADOW_IN";
	else if (shadowti == 2) shadowts = "GTK_SHADOW_OUT";
	else if (shadowti == 3) shadowts = "GTK_SHADOW_ETCHED_IN";
	else if (shadowti == 4) shadowts = "GTK_SHADOW_ETCHED_OUT";
	g_string_append_printf (app->widget_16_style_txt,
	                        "\tGtkMenuItem::selected-shadow-type = %s\n",
	                        shadowts);

	gint togglesp = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_16_spinbn_togglesp));
	g_string_append_printf (app->widget_16_style_txt,
	                        "\tGtkMenuItem::toggle-spacing = %d\n",
	                        togglesp);

	gint widthc = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_16_spinbn_widthc));
	g_string_append_printf (app->widget_16_style_txt,
	                        "\tGtkMenuItem::width-chars = %d\n",
	                        widthc);

	// ----- style end   -----

	g_string_append_printf (app->widget_16_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_16_style_txt,
	                        "class \"GtkMenuItem\" style \"%s\"\n",
	                        gtkstyle);

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_16_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkcheckmenuitem()
{
	if (app->widget_17_style_txt == NULL) exit(-1);
	app->widget_17_style_txt = g_string_set_size (app->widget_17_style_txt, 0);

	const gchar* gtkparentstyle="gtkmenuitem";
	const gchar* gtkstyle="gtkcheckmenuitem";
	g_string_append_printf (app->widget_17_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	gint indicatorsz = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_17_spinbn_indicatorsz));
	g_string_append_printf (app->widget_17_style_txt,
	                        "\tGtkCheckMenuItem::indicator-size = %d\n",
	                        indicatorsz);

	// ----- style end -----

	g_string_append_printf (app->widget_17_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_17_style_txt,
	                        "class \"GtkCheckMenuItem\" style \"%s\"\n",
	                        gtkstyle);

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_17_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtktextview()
{
	if (app->widget_18_style_txt == NULL) exit(-1);
	app->widget_18_style_txt = g_string_set_size (app->widget_18_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtktextview";
	g_string_append_printf (app->widget_18_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {"NORMAL",
	                         "ACTIVE",
	                         "PRELIGHT",
	                         "SELECTED",
	                         "INSENSITIVE"};
	for (gint i=0; i<4; ++i)
	{
		for (gint j=0; j<5; ++j)
		{
			GdkColor clr;
			gtk_color_button_get_color (
				GTK_COLOR_BUTTON(app->widget_18_clrbn[i][j]),
				&clr);

			g_string_append_printf (app->widget_18_style_txt,
			                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
			                        style[i],
			                        state[j],
			                        (clr.red * 255 / 65535),
			                        (clr.green * 255 / 65535),
			                        (clr.blue * 255 / 65535));
		}
		g_string_append_printf (app->widget_18_style_txt, "%s", "\n");
	}


	const gchar* font_name = gtk_font_button_get_font_name (
                            GTK_FONT_BUTTON(app->widget_18_fn_bn));
	g_string_append_printf (app->widget_18_style_txt,
	                        "\n\tfont_name = \"%s\"\n",
	                        font_name);

	gint xthickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_18_spinbn_xth));
	gint ythickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_18_spinbn_yth));
	g_string_append_printf (app->widget_18_style_txt,
	                        "\n\txthickness = %d\n",
	                        xthickness);
	g_string_append_printf (app->widget_18_style_txt,
	                        "\tythickness = %d\n",
	                        ythickness);

	GdkColor errorundclr;
	gtk_color_button_get_color (
                            GTK_COLOR_BUTTON(app->widget_18_clrbn_errorundclr),
                            &errorundclr);
	g_string_append_printf (app->widget_18_style_txt,
	                        "\n\t%s = \"#%02X%02X%02X\"\n",
	                        "GtkTextView::error-underline-color",
	                        (errorundclr.red * 255 / 65535),
	                        (errorundclr.green * 255 / 65535),
	                        (errorundclr.blue * 255 / 65535));

	// ----- style end   -----

	g_string_append_printf (app->widget_18_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_18_style_txt,
	                        "class \"GtkTextView\" style \"%s\"\n",
	                        gtkstyle);

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_18_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtktreeview()
{
	if (app->widget_19_style_txt == NULL) exit(-1);
	app->widget_19_style_txt = g_string_set_size (app->widget_19_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtktreeview";
	g_string_append_printf (app->widget_19_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {"NORMAL",
	                         "ACTIVE",
	                         "PRELIGHT",
	                         "SELECTED",
	                         "INSENSITIVE"};
	for (gint i=0; i<4; ++i)
	{
		for (gint j=0; j<5; ++j)
		{
			GdkColor clr;
			gtk_color_button_get_color (
				GTK_COLOR_BUTTON(app->widget_19_clrbn[i][j]),
				&clr);

			g_string_append_printf (app->widget_19_style_txt,
			                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
			                        style[i],
			                        state[j],
			                        (clr.red * 255 / 65535),
			                        (clr.green * 255 / 65535),
			                        (clr.blue * 255 / 65535));
		}
		g_string_append_printf (app->widget_19_style_txt, "%s", "\n");
	}


	const gchar* font_name = gtk_font_button_get_font_name (
                            GTK_FONT_BUTTON(app->widget_19_fn_bn));
	g_string_append_printf (app->widget_19_style_txt,
	                        "\n\tfont_name = \"%s\"\n",
	                        font_name);

	gint xthickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_19_spinbn_xth));
	gint ythickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_19_spinbn_yth));
	g_string_append_printf (app->widget_19_style_txt,
	                        "\n\txthickness = %d\n",
	                        xthickness);
	g_string_append_printf (app->widget_19_style_txt,
	                        "\tythickness = %d\n",
	                        ythickness);

	gboolean allowr = gtk_toggle_button_get_active (
                            GTK_TOGGLE_BUTTON(app->widget_19_chkbn_allowr));
	g_string_append_printf (app->widget_19_style_txt,
	                        "\n\tGtkTreeView::allow-rules = %d\n",
	                        allowr == true ? 1 : 0);

	GdkColor evenrowclr;
	gtk_color_button_get_color (
                            GTK_COLOR_BUTTON(app->widget_19_clrbn_evenrowclr),
                            &evenrowclr);
	g_string_append_printf (app->widget_19_style_txt,
	                        "\n\t%s = \"#%02X%02X%02X\"\n",
	                        "GtkTreeView::even-row-color",
	                        (evenrowclr.red * 255 / 65535),
	                        (evenrowclr.green * 255 / 65535),
	                        (evenrowclr.blue * 255 / 65535));

	gint expandersz = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_19_spinbn_expandersz));
	g_string_append_printf (app->widget_19_style_txt,
	                        "\tGtkTreeView::expander-size = %d\n",
	                        expandersz);

	const gchar* gridlnpatt = gtk_entry_get_text (
                            GTK_ENTRY(app->widget_19_entry_gridlnpatt));
	g_string_append_printf (app->widget_19_style_txt,
	                        "\tGtkTreeView::grid-line-pattern = \"%s\"\n",
	                        gridlnpatt);

	gint gridlnw = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_19_spinbn_gridlnw));
	g_string_append_printf (app->widget_19_style_txt,
	                        "\tGtkTreeView::grid-line-width = %d\n",
	                        gridlnw);

	gint horizontalsep = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_19_spinbn_horizontalsep));
	g_string_append_printf (app->widget_19_style_txt,
	                        "\tGtkTreeView::horizontal-separator = %d\n",
	                        horizontalsep);

	gboolean indentexp = gtk_toggle_button_get_active (
                            GTK_TOGGLE_BUTTON(app->widget_19_chkbn_indentexp));
	g_string_append_printf (app->widget_19_style_txt,
	                        "\tGtkTreeView::indent-expanders = %d\n",
	                        indentexp == true ? 1 : 0);

	GdkColor oddrowclr;
	gtk_color_button_get_color (
                            GTK_COLOR_BUTTON(app->widget_19_clrbn_oddrowclr),
                            &oddrowclr);
	g_string_append_printf (app->widget_19_style_txt,
	                        "\t%s = \"#%02X%02X%02X\"\n",
	                        "GtkTreeView::odd-row-color",
	                        (oddrowclr.red * 255 / 65535),
	                        (oddrowclr.green * 255 / 65535),
	                        (oddrowclr.blue * 255 / 65535));

	gboolean rowenddet = gtk_toggle_button_get_active (
                            GTK_TOGGLE_BUTTON(app->widget_19_chkbn_rowenddet));
	g_string_append_printf (app->widget_19_style_txt,
	                        "\tGtkTreeView::row-ending-details = %d\n",
	                        rowenddet == true ? 1 : 0);

	const gchar* treelnpatt = gtk_entry_get_text (
                            GTK_ENTRY(app->widget_19_entry_treelnpatt));
	g_string_append_printf (app->widget_19_style_txt,
	                        "\tGtkTreeView::tree-line-pattern = \"%s\"\n",
	                        treelnpatt);

	gint treelnw = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_19_spinbn_treelnw));
	g_string_append_printf (app->widget_19_style_txt,
	                        "\tGtkTreeView::tree-line-width = %d\n",
	                        treelnw);

	gint verticalsep = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_19_spinbn_verticalsep));
	g_string_append_printf (app->widget_19_style_txt,
	                        "\tGtkTreeView::vertical-separator = %d\n",
	                        verticalsep);

	// ----- style end -----

	g_string_append_printf (app->widget_19_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_19_style_txt,
	                        "class \"GtkTreeView\" style \"%s\"\n",
	                        gtkstyle);

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_19_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkiconview()
{
	if (app->widget_20_style_txt == NULL) exit(-1);
	app->widget_20_style_txt = g_string_set_size (app->widget_20_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtkiconview";
	g_string_append_printf (app->widget_20_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {"NORMAL",
	                         "ACTIVE",
	                         "PRELIGHT",
	                         "SELECTED",
	                         "INSENSITIVE"};
	for (gint i=0; i<4; ++i)
	{
		for (gint j=0; j<5; ++j)
		{
			GdkColor clr;
			gtk_color_button_get_color (
				GTK_COLOR_BUTTON(app->widget_20_clrbn[i][j]),
				&clr);

			g_string_append_printf (app->widget_20_style_txt,
			                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
			                        style[i],
			                        state[j],
			                        (clr.red * 255 / 65535),
			                        (clr.green * 255 / 65535),
			                        (clr.blue * 255 / 65535));
		}
		g_string_append_printf (app->widget_20_style_txt, "%s", "\n");
	}


	const gchar* font_name = gtk_font_button_get_font_name (
                            GTK_FONT_BUTTON(app->widget_20_fn_bn));
	g_string_append_printf (app->widget_20_style_txt,
	                        "\n\tfont_name = \"%s\"\n",
	                        font_name);

	gint xthickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_20_spinbn_xth));
	gint ythickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_20_spinbn_yth));
	g_string_append_printf (app->widget_20_style_txt,
	                        "\n\txthickness = %d\n",
	                        xthickness);
	g_string_append_printf (app->widget_20_style_txt,
	                        "\tythickness = %d\n",
	                        ythickness);

	gint selectionboxa = gtk_spin_button_get_value_as_int(
                          GTK_SPIN_BUTTON(app->widget_20_spinbn_selectionboxa));
	g_string_append_printf (app->widget_20_style_txt,
	                        "\n\tGtkIconView::selection-box-alpha = %d\n",
	                        selectionboxa);

	GdkColor selectionboxclr;
	gtk_color_button_get_color (
                         GTK_COLOR_BUTTON(app->widget_20_clrbn_selectionboxclr),
                            &selectionboxclr);
	g_string_append_printf (app->widget_20_style_txt,
	                        "\t%s = \"#%02X%02X%02X\"\n",
	                        "GtkIconView::selection-box-color",
	                        (selectionboxclr.red * 255 / 65535),
	                        (selectionboxclr.green * 255 / 65535),
	                        (selectionboxclr.blue * 255 / 65535));

	// ----- style end -----

	g_string_append_printf (app->widget_20_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_20_style_txt,
	                        "class \"GtkIconView\" style \"%s\"\n",
	                        gtkstyle);

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_20_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkassistant()
{
	if (app->widget_21_style_txt == NULL) exit(-1);
	app->widget_21_style_txt = g_string_set_size (app->widget_21_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtkassistant";
	g_string_append_printf (app->widget_21_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {"NORMAL",
	                         "ACTIVE",
	                         "PRELIGHT",
	                         "SELECTED",
	                         "INSENSITIVE"};
	for (gint i=0; i<4; ++i)
	{
		for (gint j=0; j<5; ++j)
		{
			GdkColor clr;
			gtk_color_button_get_color (
				GTK_COLOR_BUTTON(app->widget_21_clrbn[i][j]),
				&clr);

			g_string_append_printf (app->widget_21_style_txt,
			                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
			                        style[i],
			                        state[j],
			                        (clr.red * 255 / 65535),
			                        (clr.green * 255 / 65535),
			                        (clr.blue * 255 / 65535));
		}
		g_string_append_printf (app->widget_21_style_txt, "%s", "\n");
	}


	const gchar* font_name = gtk_font_button_get_font_name (
                            GTK_FONT_BUTTON(app->widget_21_fn_bn));
	g_string_append_printf (app->widget_21_style_txt,
	                        "\n\tfont_name = \"%s\"\n",
	                        font_name);

	gint xthickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_21_spinbn_xth));
	gint ythickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_21_spinbn_yth));
	g_string_append_printf (app->widget_21_style_txt,
	                        "\n\txthickness = %d\n",
	                        xthickness);
	g_string_append_printf (app->widget_21_style_txt,
	                        "\tythickness = %d\n",
	                        ythickness);

	gint contentpadd = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_21_spinbn_contentpadd));
	g_string_append_printf (app->widget_21_style_txt,
	                        "\n\tGtkAssistant::content-padding = %d\n",
	                        contentpadd);

	gint headerpadd = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_21_spinbn_headerpadd));
	g_string_append_printf (app->widget_21_style_txt,
	                        "\tGtkAssistant::header-padding = %d\n",
	                        headerpadd);

	// ----- style end   -----

	g_string_append_printf (app->widget_21_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_21_style_txt,
	                        "class \"GtkAssistant\" style \"%s\"\n",
	                        gtkstyle);

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_21_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkdialog()
{
	if (app->widget_22_style_txt == NULL) exit(-1);
	app->widget_22_style_txt = g_string_set_size (app->widget_22_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtkdialog";
	g_string_append_printf (app->widget_22_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {"NORMAL",
	                         "ACTIVE",
	                         "PRELIGHT",
	                         "SELECTED",
	                         "INSENSITIVE"};
	for (gint i=0; i<4; ++i)
	{
		for (gint j=0; j<5; ++j)
		{
			GdkColor clr;
			gtk_color_button_get_color (
				GTK_COLOR_BUTTON(app->widget_22_clrbn[i][j]),
				&clr);

			g_string_append_printf (app->widget_22_style_txt,
			                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
			                        style[i],
			                        state[j],
			                        (clr.red * 255 / 65535),
			                        (clr.green * 255 / 65535),
			                        (clr.blue * 255 / 65535));
		}
		g_string_append_printf (app->widget_22_style_txt, "%s", "\n");
	}


	const gchar* font_name = gtk_font_button_get_font_name (
                            GTK_FONT_BUTTON(app->widget_22_fn_bn));
	g_string_append_printf (app->widget_22_style_txt,
	                        "\n\tfont_name = \"%s\"\n",
	                        font_name);

	gint xthickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_22_spinbn_xth));
	gint ythickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_22_spinbn_yth));
	g_string_append_printf (app->widget_22_style_txt,
	                        "\n\txthickness = %d\n",
	                        xthickness);
	g_string_append_printf (app->widget_22_style_txt,
	                        "\tythickness = %d\n",
	                        ythickness);

	// ----- style end   -----

	g_string_append_printf (app->widget_22_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_22_style_txt,
	                        "class \"GtkDialog\" style \"%s\"\n",
	                        gtkstyle);

	// ----- properties begin -----
	/*
	GtkWidget* widget_22_spinbn_actionab; "action-area-border" gint >= 0 default=5
	GtkWidget* widget_22_spinbn_buttonsp; "button-spacing" gint >= 0 default=6
	GtkWidget* widget_22_spinbn_contentab; "content-area-border" gint >= 0 default=2
	GtkWidget* widget_22_spinbn_contentas; "content-area-spacing" gint >= 0 default=0
	*/

	// ----- properties end -----

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_22_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkmessagedialog()
{
	if (app->widget_23_style_txt == NULL) exit(-1);
	app->widget_23_style_txt = g_string_set_size (app->widget_23_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtkmessagedialog";
	g_string_append_printf (app->widget_23_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {"NORMAL",
	                         "ACTIVE",
	                         "PRELIGHT",
	                         "SELECTED",
	                         "INSENSITIVE"};
	for (gint i=0; i<4; ++i)
	{
		for (gint j=0; j<5; ++j)
		{
			GdkColor clr;
			gtk_color_button_get_color (
				GTK_COLOR_BUTTON(app->widget_23_clrbn[i][j]),
				&clr);

			g_string_append_printf (app->widget_23_style_txt,
			                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
			                        style[i],
			                        state[j],
			                        (clr.red * 255 / 65535),
			                        (clr.green * 255 / 65535),
			                        (clr.blue * 255 / 65535));
		}
		g_string_append_printf (app->widget_23_style_txt, "%s", "\n");
	}


	const gchar* font_name = gtk_font_button_get_font_name (
                            GTK_FONT_BUTTON(app->widget_23_fn_bn));
	g_string_append_printf (app->widget_23_style_txt,
	                        "\n\tfont_name = \"%s\"\n",
	                        font_name);

	gint xthickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_23_spinbn_xth));
	gint ythickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_23_spinbn_yth));
	g_string_append_printf (app->widget_23_style_txt,
	                        "\n\txthickness = %d\n",
	                        xthickness);
	g_string_append_printf (app->widget_23_style_txt,
	                        "\tythickness = %d\n",
	                        ythickness);

	// ----- style end   -----

	g_string_append_printf (app->widget_23_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_23_style_txt,
	                        "class \"GtkMessageDialog\" style \"%s\"\n",
	                        gtkstyle);

	// ----- properties begin -----
	/*
	GtkWidget* widget_23_spinbn_messageb; "message-border" gint >= 0 default=12
	GtkWidget* widget_23_chkbn_usesep; "use-separator" gboolean default=FALSE , deprecated in 2.22
	*/

	// ----- properties end -----

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_23_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtknotebook()
{
	if (app->widget_24_style_txt == NULL) exit(-1);
	app->widget_24_style_txt = g_string_set_size (app->widget_24_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtknotebook";
	g_string_append_printf (app->widget_24_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {"NORMAL",
	                         "ACTIVE",
	                         "PRELIGHT",
	                         "SELECTED",
	                         "INSENSITIVE"};
	for (gint i=0; i<4; ++i)
	{
		for (gint j=0; j<5; ++j)
		{
			GdkColor clr;
			gtk_color_button_get_color (
				GTK_COLOR_BUTTON(app->widget_24_clrbn[i][j]),
				&clr);

			g_string_append_printf (app->widget_24_style_txt,
			                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
			                        style[i],
			                        state[j],
			                        (clr.red * 255 / 65535),
			                        (clr.green * 255 / 65535),
			                        (clr.blue * 255 / 65535));
		}
		g_string_append_printf (app->widget_24_style_txt, "%s", "\n");
	}


	const gchar* font_name = gtk_font_button_get_font_name (
                            GTK_FONT_BUTTON(app->widget_24_fn_bn));
	g_string_append_printf (app->widget_24_style_txt,
	                        "\n\tfont_name = \"%s\"\n",
	                        font_name);

	gint xthickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_24_spinbn_xth));
	gint ythickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_24_spinbn_yth));
	g_string_append_printf (app->widget_24_style_txt,
	                        "\n\txthickness = %d\n",
	                        xthickness);
	g_string_append_printf (app->widget_24_style_txt,
	                        "\tythickness = %d\n",
	                        ythickness);

	// ----- style end   -----

	g_string_append_printf (app->widget_24_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_24_style_txt,
	                        "class \"GtkNotebook\" style \"%s\"\n",
	                        gtkstyle);

	// ----- properties begin -----
	/*
	GtkWidget* widget_24_spinbn_arrowsp; "arrow-spacing" gint >= 0 default=0
	GtkWidget* widget_24_chkbn_hasbs; "has-backward-stepper" gboolean default=TRUE
	GtkWidget* widget_24_chkbn_hasfs; "has-forward-stepper" gboolean default=TRUE
	GtkWidget* widget_24_chkbn_hassbs; "has-secondary-backward-stepper" gboolean default=FALSE
	GtkWidget* widget_24_chkbn_hassfs; "has-secondary-forward-stepper" gboolean defalt=FALSE
	GtkWidget* widget_24_spinbn_tabcurv; "tab-curvature" gint >= 0 default=1
	GtkWidget* widget_24_spinbn_tabover; "tab-overlap" gint (didn's specify) default=2 (size of tab overalp area)
	*/

	// ----- properties end -----

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_24_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkpaned()
{
	if (app->widget_25_style_txt == NULL) exit(-1);
	app->widget_25_style_txt = g_string_set_size (app->widget_25_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtkpaned";
	g_string_append_printf (app->widget_25_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- no style -----

	g_string_append_printf (app->widget_25_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_25_style_txt,
	                        "class \"GtkPaned\" style \"%s\"\n",
	                        gtkstyle);

	// ----- properties begin -----
	// GtkWidget* widget_25_spinbn_handlesz; "handle-size" gint >= 0 default=5

	// ----- properties end -----

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_25_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkrange()
{
	if (app->widget_26_style_txt == NULL) exit(-1);
	app->widget_26_style_txt = g_string_set_size (app->widget_26_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtkrange";
	g_string_append_printf (app->widget_26_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- no style -----

	g_string_append_printf (app->widget_26_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_26_style_txt,
	                        "class \"GtkRange\" style \"%s\"\n",
	                        gtkstyle);

	// ----- properties begin -----
	/*
	GtkWidget* widget_26_chkbn_activatesld; "activate-slider" gboolean default=FALSE , deprecated in 2.22
	GtkWidget* widget_26_spinbn_arrowdx; "arrow-displacement-x" gint (didn't specify) default=0  (how far in x dir to move the arrow when button is pressed)
	GtkWidget* widget_26_spinbn_arrowdy; "arrow-displacement-y" gint (didn't specify) default=0  (similar in y)
	GtkWidget* widget_26_spinbn_arrowsc; "arrow-scaling" gfloat [0,1] default=0.5
	GtkWidget* widget_26_spinbn_sliderw; "slider-width" gint >= 0 default=14
	GtkWidget* widget_26_chkbn_stepperpd; "stepper-position-details" gboolean default=FALSE , deprecated in 2.22
	GtkWidget* widget_26_spinbn_steppersz; "stepper-size" gint >= 0 default=14
	GtkWidget* widget_26_spinbn_steppersp; "stepper-spacing" gint >= 0 default=0
	GtkWidget* widget_26_spinbn_troughb; "through-border" gint >= 0 default=1
	GtkWidget* widget_26_chkbn_throughsdet; "through-size-details" gboolean default=FALSE , deprecated in 2.22
	GtkWidget* widget_26_chkbn_throughustep; "through-under-steppers" gboolean default=TRUE
	*/

	// ----- properties end -----

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_26_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkscale()
{
	if (app->widget_27_style_txt == NULL) exit(-1);
	app->widget_27_style_txt = g_string_set_size (app->widget_27_style_txt, 0);

	const gchar* gtkparentstyle="gtkrange";
	const gchar* gtkstyle="gtkscale";
	g_string_append_printf (app->widget_27_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- no style -----

	g_string_append_printf (app->widget_27_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_27_style_txt,
	                        "class \"GtkScale\" style \"%s\"\n",
	                        gtkstyle);

	// ----- properties begin -----
	/*
	GtkWidget* widget_27_spinbn_sliderl; "slider-length" gint >= 0 default=31
	GtkWidget* widget_27_spinbn_valuesp; "value-spacing" gint >= 0 defalt=2
	*/

	// ----- properties end -----

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_27_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkscrolledwindow()
{
	if (app->widget_28_style_txt == NULL) exit(-1);
	app->widget_28_style_txt = g_string_set_size (app->widget_28_style_txt, 0);

	const gchar* gtkparentstyle="gtkwidget";
	const gchar* gtkstyle="gtkscrolledwindow";
	g_string_append_printf (app->widget_28_style_txt,
	                        "style \"%s\" = \"%s\"\n{\n",
	                        gtkstyle,
	                        gtkparentstyle);

	// ----- style begin -----
	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {"NORMAL",
	                         "ACTIVE",
	                         "PRELIGHT",
	                         "SELECTED",
	                         "INSENSITIVE"};
	for (gint i=0; i<4; ++i)
	{
		for (gint j=0; j<5; ++j)
		{
			GdkColor clr;
			gtk_color_button_get_color (
				GTK_COLOR_BUTTON(app->widget_28_clrbn[i][j]),
				&clr);

			g_string_append_printf (app->widget_28_style_txt,
			                        "\t%s[%s] = \"#%02X%02X%02X\"\n",
			                        style[i],
			                        state[j],
			                        (clr.red * 255 / 65535),
			                        (clr.green * 255 / 65535),
			                        (clr.blue * 255 / 65535));
		}
		g_string_append_printf (app->widget_28_style_txt, "%s", "\n");
	}


	const gchar* font_name = gtk_font_button_get_font_name (
                            GTK_FONT_BUTTON(app->widget_28_fn_bn));
	g_string_append_printf (app->widget_28_style_txt,
	                        "\n\tfont_name = \"%s\"\n",
	                        font_name);

	gint xthickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_28_spinbn_xth));
	gint ythickness = gtk_spin_button_get_value_as_int(
                            GTK_SPIN_BUTTON(app->widget_28_spinbn_yth));
	g_string_append_printf (app->widget_28_style_txt,
	                        "\n\txthickness = %d\n",
	                        xthickness);
	g_string_append_printf (app->widget_28_style_txt,
	                        "\tythickness = %d\n",
	                        ythickness);

	// ----- style end -----

	g_string_append_printf (app->widget_28_style_txt,"%s\n", "}");
	g_string_append_printf (app->widget_28_style_txt,
	                        "class \"GtkScrolledWindow\" style \"%s\"\n",
	                        gtkstyle);

	// ----- properties begin -----
	/*
	GtkWidget* widget_28_spinbn_scrollbarsp; "scrollbar-spacing" gint >= 0 default=3
	GtkWidget* widget_28_chkbn_scrollbarswb; "scollbars-within-bevel" gboolean default=FALSE
	*/

	// ----- properties end -----

	FILE* fp = fopen (app->rcfile, "a");
	if (fp == NULL) exit (-1);
	fprintf (fp, "\n%s", app->widget_28_style_txt->str);
	fclose (fp);
}

void write_rc_for_all()
{
	// clear file content
	FILE* fp = fopen (app->rcfile, "w");
	if (fp == NULL) exit (-1);
	fclose (fp);

	write_rc_for_gtkwidget ();
	write_rc_for_gtkbutton ();
	write_rc_for_gtkcheckbutton();
	write_rc_for_gtkbuttonbox();
	write_rc_for_gtkcombobox();
	write_rc_for_gtkentry();
	write_rc_for_gtkexpander();
	write_rc_for_gtkscrollbar();
	write_rc_for_gtkarrow();
	write_rc_for_gtkprogressbar();
	write_rc_for_gtkspinbutton();
	write_rc_for_gtkstatusbar();
	write_rc_for_gtktoolbar();
	write_rc_for_gtktoolbutton();
	write_rc_for_gtkmenu();
	write_rc_for_gtkmenubar();
	write_rc_for_gtkmenuitem();
	write_rc_for_gtkcheckmenuitem();
	write_rc_for_gtktextview();
	write_rc_for_gtktreeview();
	write_rc_for_gtkiconview();
	write_rc_for_gtkassistant();
	write_rc_for_gtkdialog();
	write_rc_for_gtkmessagedialog();
	write_rc_for_gtknotebook();
	write_rc_for_gtkpaned();
	write_rc_for_gtkrange();
	write_rc_for_gtkscale();
	write_rc_for_gtkscrolledwindow();

	gtk_rc_reparse_all ();
}


// ----- Main application UI methods -----
//
void ui_create_gtkwidget()
{
	// First table holds the color buttons and labels on top and left side.
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	const gint TABLE_0_ROW = 6; // 1 header, 4 colors, 1 pixmap
	const gint TABLE_0_COL = 6;
	GtkWidget* table_0 = gtk_table_new (TABLE_0_ROW, TABLE_0_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_0,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* expander = gtk_expander_new ("GtkWidget");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding




	// Set the labels on the left side.
	const gchar* rows_txt[TABLE_0_ROW] = {
		"", "fg", "bg", "text", "base", "bg_pixmap"
	};
	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		GtkWidget* label = gtk_label_new (rows_txt[i]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  0, 1,    // left, right
		                  i, i+1,  // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);   // x,y padding
	}

	// Set the labels on the top.
	const gchar* cols_txt[TABLE_0_COL] = {
		"", "NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	for (gint j=1; j<TABLE_0_COL; ++j)
	{
		GtkWidget* label = gtk_label_new (cols_txt[j]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
	}

	// Set the color buttons ( exclude bg_pixmap here)
	/* fg[NORMAL]   = "#747474"  , also ACTIVE,PRELIGHT,SELECTED,INSENSITIVE
	   bg[NORMAL]   = "#DCDAD5"  , idem
	   text[NORMAL] = "#000000"  , idem
	   base[NORMAL] = "#FFFFFF"  , idem
	*/
	GtkStyle* style = gtk_widget_get_style (app->window);
	for (gint i=1; i<TABLE_0_ROW - 1; ++i)
	{
		for (gint j=1; j<TABLE_0_COL; ++j)
		{
			GdkColor* clr;
			if (i == 1)      clr = &(style->fg[j-1]);
			else if (i == 2) clr = &(style->bg[j-1]);
			else if (i == 3) clr = &(style->text[j-1]);
			else if (i == 4) clr = &(style->base[j-1]);
			else exit(-1);
			app->widget_0_clrbn[i-1][j-1] = gtk_color_button_new_with_color (clr);
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_0_clrbn[i-1][j-1],
			                  j, j+1, // left, right
			                  i, i+1, // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);  // x,y padding
			g_signal_connect (G_OBJECT(app->widget_0_clrbn[i-1][j-1]),
			                  "color-set",
			                  G_CALLBACK(cb_color_set),
			                  NULL);
		}
	}


	// Set bg_pixmap: an image to use as the background of widget in its 5 states
	for (gint i=5; i<6; ++i)
	{
		for (gint j=1; j<TABLE_0_COL; ++j)
		{
			gchar label[5];
			strcpy(label, style->bg_pixmap[j-1] == NULL ? "null" : "set");

			app->widget_0_pixbn[j-1] = gtk_button_new_with_label (label);
			app->widget_0_pixmap[j-1] = g_string_new ("");
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_0_pixbn[j-1],
			                  j, j+1,   // left, right
			                  i, i+1,   // top, bottom
			                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
			                  0, 0);    // x,y padding
			g_signal_connect (G_OBJECT(app->widget_0_pixbn[j-1]),
			                  "clicked",
			                  G_CALLBACK(cb_0_pixbn_clicked),
			                  NULL);
		}
	}

	// New table for: font desc, thickness, cursor-aspect-ratio, cursor-color

	// font_desc    font_name="FreeSans 11"
	GtkWidget* table_1 = gtk_table_new (5, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* font_desc_lbl = gtk_label_new ("font_desc");
	char* font_name = pango_font_description_to_string (style->font_desc);
	app->widget_0_fn_bn = gtk_font_button_new_with_font (font_name);
	g_free (font_name);
	gtk_table_attach (GTK_TABLE(table_1),
	                  font_desc_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_0_fn_bn,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_0_fn_bn),
	                  "font-set",
	                  G_CALLBACK(cb_font_set),
	                  NULL);

	// xthickness = 2
	GtkWidget* xthickness_lbl = gtk_label_new ("xthickness");
	app->widget_0_spinbn_xth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_0_spinbn_xth),
	                           (gdouble)style->xthickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  xthickness_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_0_spinbn_xth,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_0_spinbn_xth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// ythickness = 2
	GtkWidget* ythickness_lbl = gtk_label_new ("ythickness");
	app->widget_0_spinbn_yth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_0_spinbn_yth),
	                           (gdouble)style->ythickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  ythickness_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_0_spinbn_yth,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_0_spinbn_yth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// GtkWidget::cursor-aspect-ratio = 0.04 (default) float [0.0, 1.0]
	GtkWidget* cursorar_lbl = gtk_label_new ("cursor-aspect-ratio");
	app->widget_0_spinbn_cursorar =
		gtk_spin_button_new_with_range (0.0, 1.0, 0.01);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_0_spinbn_cursorar),
	                           (gdouble)0.04); // use default
	gtk_table_attach (GTK_TABLE(table_1),
	                  cursorar_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_0_spinbn_cursorar,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_0_spinbn_cursorar),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);


	// GtkWidget::cursor-color = "#000000" GdkColor
	GdkColor cursorclr;
	gdk_color_parse ("#000000", &cursorclr);
	app->widget_0_clrbn_cursorclr = gtk_color_button_new_with_color (&cursorclr);
	GtkWidget* cursorclr_lbl = gtk_label_new ("cursor-color");
	gtk_table_attach (GTK_TABLE(table_1),
	                  cursorclr_lbl,
	                  0, 1,   // left, right
	                  4, 5,   // top, bottom,
	                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_0_clrbn_cursorclr,
	                  1, 2,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_0_clrbn_cursorclr),
	                  "color-set",
	                  G_CALLBACK(cb_color_set),
	                  NULL);

	// New table for: GtkWidget::draw-border = { 1, 1, 1, 1 }
	const gint TABLE_1_COL = 5;
	GtkWidget* table_2 = gtk_table_new (1, 5, TRUE); // row, col, homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_2,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* drawb_lbl = gtk_label_new ("draw-border");
	gtk_table_attach (GTK_TABLE(table_2),
	                  drawb_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding

	for (int j=1; j < TABLE_1_COL; ++j)
	{
		app->widget_0_spinbn_drawb[j-1] =
			gtk_spin_button_new_with_range (0,10,1);
		gtk_spin_button_set_value (
                               GTK_SPIN_BUTTON(app->widget_0_spinbn_drawb[j-1]),
                               1); // use default 1
		gtk_table_attach (GTK_TABLE(table_2),
		                  app->widget_0_spinbn_drawb[j-1],
		                  j, j+1,  // left, right
		                  0, 1,    // top, bottom
		                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
		                  0, 0);   // x,y padding
		g_signal_connect (G_OBJECT(app->widget_0_spinbn_drawb[j-1]),
		                    "value-changed",
		                    G_CALLBACK(cb_spinbn_value_changed),
		                    NULL);
	}


	// New table for 12 more widgets of type GtkWidget::___ = ___
	const gint TABLE_3_ROW = 12;
	const gint TABLE_3_COL = 2;
	GtkWidget* table_3 = gtk_table_new (TABLE_3_ROW, TABLE_3_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_3,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	// focus-line-pattern   char*      \001\001
	GtkWidget* focuslp_lbl = gtk_label_new ("focus-line-pattern");
	gtk_table_attach (GTK_TABLE(table_3),
	                  focuslp_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_0_entry_focuslp = gtk_entry_new ();
	gtk_entry_set_text (GTK_ENTRY(app->widget_0_entry_focuslp), "\\001\\001");
	gtk_table_attach (GTK_TABLE(table_3),
	                  app->widget_0_entry_focuslp,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_0_entry_focuslp),
	                  "activate",
	                  G_CALLBACK(cb_entry_activate),
	                  NULL);

	// focus-line-width     gint       >=0   def:1
	GtkWidget* focuslw_lbl = gtk_label_new ("focus-line-width");
	gtk_table_attach (GTK_TABLE(table_3),
	                  focuslw_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_0_spinbn_focuslw = gtk_spin_button_new_with_range(0, 10, 1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_0_spinbn_focuslw),
	                           1); // default=1
	gtk_table_attach (GTK_TABLE(table_3),
	                  app->widget_0_spinbn_focuslw,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_0_spinbn_focuslw),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// focus-padding        gint       >=0   def:1
	GtkWidget* focusp_lbl = gtk_label_new ("focus-padding");
	gtk_table_attach (GTK_TABLE(table_3),
	                  focusp_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_0_spinbn_focusp = gtk_spin_button_new_with_range(0, 10, 1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_0_spinbn_focusp),
	                           1); // default=1
	gtk_table_attach (GTK_TABLE(table_3),
	                  app->widget_0_spinbn_focusp,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_0_spinbn_focusp),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// interior-focus       gboolean         def:TRUE
	GtkWidget* interiorf_lbl = gtk_label_new ("interior-focus");
	gtk_table_attach (GTK_TABLE(table_3),
	                  interiorf_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_0_chkbn_interiorf = gtk_check_button_new ();
	gtk_table_attach (GTK_TABLE(table_3),
	                  app->widget_0_chkbn_interiorf,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_0_chkbn_interiorf),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// link-color           GdkColor         def:did't say->blue
	GtkWidget* linkclr_lbl = gtk_label_new ("link-color");
	gtk_table_attach (GTK_TABLE(table_3),
	                  linkclr_lbl,
	                  0, 1,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	GdkColor linkclr;
	gdk_color_parse ("#0000FF", &linkclr);
	app->widget_0_clrbn_linkclr = gtk_color_button_new_with_color (&linkclr);
	gtk_table_attach (GTK_TABLE(table_3),
	                  app->widget_0_clrbn_linkclr,
	                  1, 2,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_0_clrbn_linkclr),
	                  "color-set",
	                  G_CALLBACK(cb_color_set),
	                  NULL);

	// scroll-arrow-hlength gint       >=1   def:16
	GtkWidget* scrollahl_lbl = gtk_label_new ("scroll-arrow-hlength");
	gtk_table_attach (GTK_TABLE(table_3),
	                  scrollahl_lbl,
	                  0, 1,   // left, right
	                  5, 6,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_0_spinbn_scrollahl = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_0_spinbn_scrollahl),
	                           16); // use default 16
	gtk_table_attach (GTK_TABLE(table_3),
	                  app->widget_0_spinbn_scrollahl,
	                  1, 2,  // left, right
	                  5, 6,  // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	g_signal_connect (G_OBJECT(app->widget_0_spinbn_scrollahl),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// scroll-arrow-vlength gint       >=1   def:16
	GtkWidget* scrollavl_lbl = gtk_label_new ("scroll-arrow-vlength");
	gtk_table_attach (GTK_TABLE(table_3),
	                  scrollavl_lbl,
	                  0, 1,   // left, right
	                  6, 7,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_0_spinbn_scrollavl = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_0_spinbn_scrollavl),
	                           16); // use default 16
	gtk_table_attach (GTK_TABLE(table_3),
	                  app->widget_0_spinbn_scrollavl,
	                  1, 2,  // left, right
	                  6, 7,  // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	g_signal_connect (G_OBJECT(app->widget_0_spinbn_scrollavl),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// secondary-cursor-color GdkColor  (left->right, right->left edit)
	GtkWidget* secondarycurclr_lbl = gtk_label_new ("secondary-cursor-color");
	gtk_table_attach (GTK_TABLE(table_3),
	                  secondarycurclr_lbl,
	                  0, 1,   // left, right
	                  7, 8,   // top, bottom,
	                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
	                  0, 0);  // x,y padding
	GdkColor secondarycurclr;
	gdk_color_parse ("#FF0000", &secondarycurclr); // red?
	app->widget_0_clrbn_secondarycurclr =
		gtk_color_button_new_with_color (&secondarycurclr);
	gtk_table_attach (GTK_TABLE(table_3),
	                  app->widget_0_clrbn_secondarycurclr,
	                  1, 2,   // left, right
	                  7, 8,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_0_clrbn_secondarycurclr),
	                  "color-set",
	                  G_CALLBACK(cb_color_set),
	                  NULL);


	// separator-height     gint       >=0   def:0 (if wide-separators is on)
	GtkWidget* separatorh_lbl = gtk_label_new ("separator-height");
	gtk_table_attach (GTK_TABLE(table_3),
	                  separatorh_lbl,
	                  0, 1,   // left, right
	                  8, 9,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_0_spinbn_separatorh = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_0_spinbn_separatorh),
	                           0); // use default 0
	gtk_table_attach (GTK_TABLE(table_3),
	                  app->widget_0_spinbn_separatorh,
	                  1, 2,  // left, right
	                  8, 9,  // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	g_signal_connect (G_OBJECT(app->widget_0_spinbn_separatorh),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);


	// separator-width      gint       >=0   def:0 (if wide-separators is on)
	GtkWidget* separatorw_lbl = gtk_label_new ("separator-width");
	gtk_table_attach (GTK_TABLE(table_3),
	                  separatorw_lbl,
	                  0, 1,   // left, right
	                  9, 10,  // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_0_spinbn_separatorw = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_0_spinbn_separatorw),
	                           0); // use default 0
	gtk_table_attach (GTK_TABLE(table_3),
	                  app->widget_0_spinbn_separatorw,
	                  1, 2,   // left, right
	                  9, 10,  // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_0_spinbn_separatorw),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// visited-link-color   GdkColor
	GtkWidget* visitedlnkclr_lbl = gtk_label_new ("visited-link-color");
	gtk_table_attach (GTK_TABLE(table_3),
	                  visitedlnkclr_lbl,
	                  0, 1,    // left, right
	                  10, 11,  // top, bottom,
	                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
	                  0, 0);   // x,y padding
	GdkColor visitedlnkclr;
	gdk_color_parse ("#009696", &visitedlnkclr); // light blue
	app->widget_0_clrbn_visitedlnkclr =
		gtk_color_button_new_with_color (&visitedlnkclr);
	gtk_table_attach (GTK_TABLE(table_3),
	                  app->widget_0_clrbn_visitedlnkclr,
	                  1, 2,    // left, right
	                  10, 11,  // top, bottom
	                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
	                  0, 0);   // x,y padding
	g_signal_connect (G_OBJECT(app->widget_0_clrbn_visitedlnkclr),
	                  "color-set",
	                  G_CALLBACK(cb_color_set),
	                  NULL);

	// wide-separators      gboolean   def:FALSE (draw sep using box not lines)
	GtkWidget* wides_lbl = gtk_label_new ("wide-separators");
	gtk_table_attach (GTK_TABLE(table_3),
	                  wides_lbl,
	                  0, 1,    // left, right
	                  11, 12,  // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	app->widget_0_chkbn_wides = gtk_check_button_new ();
	gtk_table_attach (GTK_TABLE(table_3),
	                  app->widget_0_chkbn_wides,
	                  1, 2,    // left, right
	                  11, 12,  // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	g_signal_connect (G_OBJECT(app->widget_0_chkbn_wides),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);


	// retain the style as text to write it into rc file at any time.
	app->widget_0_style_txt = g_string_new ("#rc style for class GtkWidget");
}

void ui_update_gtkwidget()
{
}

void ui_delete_gtkwidget()
{
	if (app == NULL) exit(-1);
	const gint TABLE_0_COL = 6;
	for (int j=1; j<TABLE_0_COL; ++j)
	{
		g_string_free (app->widget_0_pixmap[j-1], TRUE);
	}
	g_string_free (app->widget_0_style_txt, TRUE);
}

void ui_create_gtkbutton()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkButton");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	// Create few sample buttons to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (4, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* bn_withlabel[3] = {NULL, NULL, NULL};
	const gchar* bn_withlabel_lbl[3] = { "Normal Button",
	                                     "No Action",
	                                     "Button with a label" };
	for (gint i=0; i < 3; ++i)
	{
		bn_withlabel[i] = gtk_button_new_with_label (bn_withlabel_lbl[i]);
		gtk_table_attach (GTK_TABLE(table_sample),
		                  bn_withlabel[i],
		                  i, i+1,    // left, right
		                  0, 1,      // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);     // x,y padding
	}


	GtkWidget* bn_relief[3] = {NULL, NULL, NULL};
	const gchar* bn_relief_lbl[3] = { "GTK_RELIEF_NORMAL",
	                                  "GTK_RELIEF_HALF",
	                                  "GTK_RELIEF_NONE" };
	GtkReliefStyle bn_relief_st[3] = { GTK_RELIEF_NORMAL,
	                                   GTK_RELIEF_HALF,
	                                   GTK_RELIEF_NONE };
	for (gint i=0; i < 3; ++i)
	{
		bn_relief[i] = gtk_button_new_with_label (bn_relief_lbl[i]);
		gtk_button_set_relief (GTK_BUTTON(bn_relief[i]), bn_relief_st[i]);
		gtk_table_attach (GTK_TABLE(table_sample),
		                  bn_relief[i],
		                  i, i+1,    // left, right
		                  1, 2,      // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);     // x,y padding
	}

	GtkWidget* bn_stock[2][3] = { {NULL, NULL, NULL},
	                              {NULL, NULL, NULL}};
	const gchar* bn_stock_id[2][3] =
		{ {GTK_STOCK_ABOUT, GTK_STOCK_APPLY, GTK_STOCK_CDROM},
		  {GTK_STOCK_PAGE_SETUP, GTK_STOCK_CONNECT, GTK_STOCK_EXECUTE} };

	for (gint i=0; i < 2; ++i)
		for(gint j=0; j < 3; ++j)
		{
			bn_stock[i][j] = gtk_button_new_from_stock (bn_stock_id[i][j]);
			gtk_table_attach (GTK_TABLE(table_sample),
			                  bn_stock[i][j],
			                  j, j+1,     // left, right
			                  2+i, 3+i,   // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);      // x,y padding
		}



	// Set the labels on the left side.
	const gint TABLE_0_ROW = 5; // 1 header, 4 colors
	const gint TABLE_0_COL = 6;
	GtkWidget* table_0 = gtk_table_new (TABLE_0_ROW, TABLE_0_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_0,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	const gchar* rows_txt[TABLE_0_ROW] = { "", "fg", "bg", "text", "base" };

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		GtkWidget* label = gtk_label_new (rows_txt[i]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  0, 1,    // left, right
		                  i, i+1,  // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);   // x,y padding
	}

	// Set the labels on the top.
	const gchar* cols_txt[TABLE_0_COL] = {
		"", "NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	for (gint j=1; j<TABLE_0_COL; ++j)
	{
		GtkWidget* label = gtk_label_new (cols_txt[j]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
	}

	// Set the color buttons
	/* fg[NORMAL] = "#747474"  , also ACTIVE,PRELIGHT,SELECTED,INSENSITIVE
	   bg[NORMAL] = "#DCDAD5"  , idem
	   text[NORMAL] = "#000000", idem
	   base[NORMAL] = "#FFFFFF", idem
	 */
	GtkStyle* style = gtk_widget_get_style (app->window);

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		for (gint j=1; j<TABLE_0_COL; ++j)
		{
			GdkColor* clr;
			if (i == 1)      clr = &(style->fg[j-1]);
			else if (i == 2) clr = &(style->bg[j-1]);
			else if (i == 3) clr = &(style->text[j-1]);
			else if (i == 4) clr = &(style->base[j-1]);
			else exit(-1);
			app->widget_1_clrbn[i-1][j-1] =
				gtk_color_button_new_with_color (clr);
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_1_clrbn[i-1][j-1],
			                  j, j+1, // left, right
			                  i, i+1, // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);  // x,y padding
			g_signal_connect (G_OBJECT(app->widget_1_clrbn[i-1][j-1]),
			                  "color-set",
			                  G_CALLBACK(cb_color_set),
			                  NULL);
		}
	}

	// New table for 5 pairs of 2 (label + widget)

	// font_desc    font_name="FreeSans 11"
	GtkWidget* table_1 = gtk_table_new (5, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expanding
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* font_desc_lbl = gtk_label_new ("font_desc");
	char* font_name = pango_font_description_to_string (style->font_desc);
	app->widget_1_fn_bn = gtk_font_button_new_with_font (font_name);
	g_free (font_name);
	gtk_table_attach (GTK_TABLE(table_1),
	                  font_desc_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_1_fn_bn,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_1_fn_bn),
	                  "font-set",
	                  G_CALLBACK(cb_font_set),
	                  NULL);

	// xthickness = 1
	GtkWidget* xthickness_lbl = gtk_label_new ("xthickness");
	app->widget_1_spinbn_xth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_1_spinbn_xth),
	                           (gdouble)style->xthickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  xthickness_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_1_spinbn_xth,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_1_spinbn_xth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// ythickness = 1
	GtkWidget* ythickness_lbl = gtk_label_new ("ythickness");
	app->widget_1_spinbn_yth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_1_spinbn_yth),
	                           (gdouble)style->ythickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  ythickness_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_1_spinbn_yth,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_1_spinbn_yth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// GtkButton::child-displacement-x  gint
	GtkWidget* childdx_lbl = gtk_label_new("child-displacement-x");
	app->widget_1_spinbn_childdx = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_1_spinbn_childdx),
	                           1);
	gtk_table_attach (GTK_TABLE(table_1),
	                  childdx_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,   // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_1_spinbn_childdx,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,   // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_1_spinbn_childdx),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// GtkButton::child-displacement-y  gint
	GtkWidget* childdy_lbl = gtk_label_new("child-displacement-y");
	app->widget_1_spinbn_childdy = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_1_spinbn_childdy),
	                           1);
	gtk_table_attach (GTK_TABLE(table_1),
	                  childdy_lbl,
	                  0, 1,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,   // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_1_spinbn_childdy,
	                  1, 2,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,   // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_1_spinbn_childdy),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// New table 5 x 5
	// 1st row = 5
	// 2nd row = 5
	// 3rd row = 2
	// 4th row = 2
	// 5th row = 5

	// GtkButton::default-border        GtkBorder = {1, 1, 1, 1}
	const gint TABLE_2_COL = 5;
	GtkWidget* table_2 = gtk_table_new (5, 5, FALSE); // row, col, homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_2,
	                    FALSE,   // expanding
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* defaultb_lbl = gtk_label_new ("default-border");
	gtk_table_attach (GTK_TABLE(table_2),
	                  defaultb_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding

	for (int j=1; j < TABLE_2_COL; ++j)
	{
		app->widget_1_spinbn_defaultb[j-1] =
			gtk_spin_button_new_with_range(0, 10, 1);
		gtk_spin_button_set_value (
                            GTK_SPIN_BUTTON(app->widget_1_spinbn_defaultb[j-1]),
                            1); // use default
		gtk_table_attach (GTK_TABLE(table_2),
		                  app->widget_1_spinbn_defaultb[j-1],
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
		g_signal_connect (G_OBJECT(app->widget_1_spinbn_defaultb[j-1]),
		                  "value-changed",
		                  G_CALLBACK(cb_spinbn_value_changed),
		                  NULL);
	}


	// GtkButton::default-outside-border GtkBorder= {1, 1, 1, 1}
	GtkWidget* defaultob_lbl = gtk_label_new ("default-outside-border");
	gtk_table_attach (GTK_TABLE(table_2),
	                  defaultob_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding

	for (int j=1; j < TABLE_2_COL; ++j)
	{
		app->widget_1_spinbn_defaultob[j-1] =
			gtk_spin_button_new_with_range(0, 10, 1);
		gtk_spin_button_set_value (
                          GTK_SPIN_BUTTON(app->widget_1_spinbn_defaultob[j-1]),
                          1); // use default
		gtk_table_attach (GTK_TABLE(table_2),
		                  app->widget_1_spinbn_defaultob[j-1],
		                  j, j+1,   // left, right
		                  1, 2,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
		g_signal_connect (G_OBJECT(app->widget_1_spinbn_defaultob[j-1]),
		                  "value-changed",
		                  G_CALLBACK(cb_spinbn_value_changed),
		                  NULL);
	}


	// GtkButton::displace-focus        gboolean = 1 or 0
	GtkWidget* displacef_lbl = gtk_label_new ("displace-focus");
	gtk_table_attach (GTK_TABLE(table_2),
	                  displacef_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
	                  0, 0);  // x,y padding

	app->widget_1_chkbn_displacef = gtk_check_button_new ();
	gtk_table_attach (GTK_TABLE(table_2),
	                  app->widget_1_chkbn_displacef,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_1_chkbn_displacef),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// GtkButton::image-spacing         gint
	GtkWidget* images_lbl = gtk_label_new ("image-spacing");
	gtk_table_attach (GTK_TABLE(table_2),
	                  images_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_1_spinbn_images = gtk_spin_button_new_with_range(0, 10, 1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_1_spinbn_images),
	                           1); // default=1
	gtk_table_attach (GTK_TABLE(table_2),
	                  app->widget_1_spinbn_images,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_1_spinbn_images),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);


	// GtkButton::inner-border          GtkBorder = {1, 1, 1, 1}
	GtkWidget* innerb_lbl = gtk_label_new ("inner-border");
	gtk_table_attach (GTK_TABLE(table_2),
	                  innerb_lbl,
	                  0, 1,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding

	for (int j=1; j < TABLE_2_COL; ++j)
	{
		app->widget_1_spinbn_innerb[j-1] =
			gtk_spin_button_new_with_range(0, 10, 1);
		gtk_spin_button_set_value (
                            GTK_SPIN_BUTTON(app->widget_1_spinbn_innerb[j-1]),
                            1); // use default
		gtk_table_attach (GTK_TABLE(table_2),
		                  app->widget_1_spinbn_innerb[j-1],
		                  j, j+1,   // left, right
		                  4, 5,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
		g_signal_connect (G_OBJECT(app->widget_1_spinbn_innerb[j-1]),
		                  "value-changed",
		                  G_CALLBACK(cb_spinbn_value_changed),
		                  NULL);
	}

	// retain the style as text to write it into rc file at any time
	app->widget_1_style_txt = g_string_new ("#rc style for class GtkButton");
}

void ui_update_gtkbutton()
{
}

void ui_delete_gtkbutton()
{
}

void ui_create_gtkcheckbutton()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkCheckButton");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (1, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	GtkWidget* ckbn_withlabel[3];
	ckbn_withlabel[0] = gtk_check_button_new_with_label("Check Button");
	ckbn_withlabel[1] = gtk_check_button_new_with_mnemonic ("With _Mnemonic");
	ckbn_withlabel[2] = gtk_check_button_new_with_label("Check Me!");

	for (gint i=0; i < 3; ++i)
	{
		gtk_table_attach (GTK_TABLE(table_sample),
		                  ckbn_withlabel[i],
		                  i, i+1,    // left, right
		                  0, 1,      // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);     // x,y padding
	}


	// create 3 radio buttons
	GtkWidget* rdbn_withlabel[3];
	rdbn_withlabel[0] = gtk_radio_button_new_with_label(NULL, "radio 1");
	rdbn_withlabel[1] = gtk_radio_button_new_with_label_from_widget(
		                                    GTK_RADIO_BUTTON(rdbn_withlabel[0]),
		                                    "radio 2");
	rdbn_withlabel[2] = gtk_radio_button_new_with_label_from_widget(
		                                    GTK_RADIO_BUTTON(rdbn_withlabel[0]),
		                                    "radio 3");
	for (gint i=0; i < 3; ++i)
	{
		gtk_table_attach (GTK_TABLE(table_sample),
		                  rdbn_withlabel[i],
		                  i, i+1,    // left, right
		                  1, 2,      // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);     // x,y padding
	}




	// Set the labels on the left side.
	const gint TABLE_0_ROW = 5; // 1 header, 4 colors
	const gint TABLE_0_COL = 6;
	GtkWidget* table_0 = gtk_table_new (TABLE_0_ROW, TABLE_0_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_0,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	const gchar* rows_txt[TABLE_0_ROW] = { "", "fg", "bg", "text", "base" };

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		GtkWidget* label = gtk_label_new (rows_txt[i]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  0, 1,    // left, right
		                  i, i+1,  // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);   // x,y padding
	}

	// Set the labels on the top.
	const gchar* cols_txt[TABLE_0_COL] = {
		"", "NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	for (gint j=1; j<TABLE_0_COL; ++j)
	{
		GtkWidget* label = gtk_label_new (cols_txt[j]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
	}

	// Set the color buttons
	/* fg[NORMAL] = "#747474"  , also ACTIVE,PRELIGHT,SELECTED,INSENSITIVE
	   bg[NORMAL] = "#DCDAD5"  , idem
	   text[NORMAL] = "#000000", idem
	   base[NORMAL] = "#FFFFFF", idem
	 */
	GtkStyle* style = gtk_widget_get_style (app->window);

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		for (gint j=1; j<TABLE_0_COL; ++j)
		{
			GdkColor* clr;
			if (i == 1)      clr = &(style->fg[j-1]);
			else if (i == 2) clr = &(style->bg[j-1]);
			else if (i == 3) clr = &(style->text[j-1]);
			else if (i == 4) clr = &(style->base[j-1]);
			else exit(-1);
			app->widget_2_clrbn[i-1][j-1] =
				gtk_color_button_new_with_color (clr);
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_2_clrbn[i-1][j-1],
			                  j, j+1, // left, right
			                  i, i+1, // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);  // x,y padding
			g_signal_connect (G_OBJECT(app->widget_2_clrbn[i-1][j-1]),
			                  "color-set",
			                  G_CALLBACK(cb_color_set),
			                  NULL);
		}
	}


	// font_desc    font_name="FreeSans 11"
	GtkWidget* table_1 = gtk_table_new (5, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* font_desc_lbl = gtk_label_new ("font_desc");
	char* font_name = pango_font_description_to_string (style->font_desc);
	app->widget_2_fn_bn = gtk_font_button_new_with_font (font_name);
	g_free (font_name);
	gtk_table_attach (GTK_TABLE(table_1),
	                  font_desc_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_2_fn_bn,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_2_fn_bn),
	                  "font-set",
	                  G_CALLBACK(cb_font_set),
	                  NULL);

	// xthickness = 2
	GtkWidget* xthickness_lbl = gtk_label_new ("xthickness");
	app->widget_2_spinbn_xth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_2_spinbn_xth),
	                           (gdouble)style->xthickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  xthickness_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_2_spinbn_xth,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_2_spinbn_xth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// ythickness = 2
	GtkWidget* ythickness_lbl = gtk_label_new ("ythickness");
	app->widget_2_spinbn_yth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_2_spinbn_yth),
	                           (gdouble)style->ythickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  ythickness_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_2_spinbn_yth,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_2_spinbn_yth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);


	// "indicator-size" gint >= 0 default=13
	GtkWidget* indicatorsz_lbl = gtk_label_new("indicator-size");
	app->widget_2_spinbn_indicatorsz = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_2_spinbn_indicatorsz),
	                           13);
	gtk_table_attach (GTK_TABLE(table_1),
	                  indicatorsz_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,   // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_2_spinbn_indicatorsz,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,   // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_2_spinbn_indicatorsz),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "indicator-spacing" gint >=0 default=2
	GtkWidget* indicatorsp_lbl = gtk_label_new("indicator-spacing");
	app->widget_2_spinbn_indicatorsp = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_2_spinbn_indicatorsp),
	                           2);
	gtk_table_attach (GTK_TABLE(table_1),
	                  indicatorsp_lbl,
	                  0, 1,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,   // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_2_spinbn_indicatorsp,
	                  1, 2,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,   // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_2_spinbn_indicatorsp),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_2_style_txt = g_string_new ("#rc style for class GtkCheckButton");
}

void ui_update_gtkcheckbutton()
{

}

void ui_delete_gtkcheckbutton()
{
}

void ui_create_gtkbuttonbox()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkButtonBox");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	GtkWidget* lbl_horizontal = gtk_label_new("GtkHButtonBox");
	gtk_box_pack_start (GTK_BOX(vbox),
	                    lbl_horizontal,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	GtkWidget* bnbox_horizontal = gtk_hbutton_box_new ();
	gtk_box_pack_start (GTK_BOX(vbox),
	                    bnbox_horizontal,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	GtkWidget* bn_haligned[3];
	const gchar* bn_haligned_lbl[3] = { "_Buttons",
	                                    "_Horizontal",
	                                    "_Aligned"};
	for (gint i=0; i < 3; ++i)
	{
		bn_haligned[i] = gtk_button_new_with_mnemonic(bn_haligned_lbl[i]);
		gtk_box_pack_start (GTK_BOX(bnbox_horizontal),
		                    bn_haligned[i],
		                    FALSE,   // expand
		                    FALSE,   // fill
		                    0);      // padding
	}

	GtkWidget* lbl_vertical = gtk_label_new("GtkVButtonBox");
	gtk_box_pack_start (GTK_BOX(vbox),
	                    lbl_vertical,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	GtkWidget* bnbox_vertical = gtk_vbutton_box_new ();
	gtk_box_pack_start (GTK_BOX(vbox),
	                    bnbox_vertical,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	GtkWidget* bn_valigned[3];
	const gchar* bn_valigned_lbl[3] = { "_Buttons",
	                                    "_Vertical",
	                                    "_Aligned"};
	for (gint i=0; i < 3; ++i)
	{
		bn_valigned[i] = gtk_button_new_with_mnemonic(bn_valigned_lbl[i]);
		gtk_box_pack_start (GTK_BOX(bnbox_vertical),
		                    bn_valigned[i],
		                    FALSE,   // expand
		                    FALSE,   // fill
		                    0);      // padding
	}



	GtkWidget* table_1 = gtk_table_new (4, 2, TRUE); // row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	// "child-internal-pad-x" gint >= 0 default=4
	GtkWidget* childipx_lbl = gtk_label_new("child-internal-pad-x");
	app->widget_3_spinbn_childipx = gtk_spin_button_new_with_range (0,20,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_3_spinbn_childipx),
	                           4);
	gtk_table_attach (GTK_TABLE(table_1),
	                  childipx_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,   // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_3_spinbn_childipx,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,   // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_3_spinbn_childipx),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "child-internal-pad-y" gint >= 0 default=0
	GtkWidget* childipy_lbl = gtk_label_new("child-internal-pad-y");
	app->widget_3_spinbn_childipy = gtk_spin_button_new_with_range (0,20,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_3_spinbn_childipy),
	                           0);
	gtk_table_attach (GTK_TABLE(table_1),
	                  childipy_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,   // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_3_spinbn_childipy,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,   // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_3_spinbn_childipy),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "child-min-height" gint >= 0 default=27
	GtkWidget* childmh_lbl = gtk_label_new("child-min-height");
	app->widget_3_spinbn_childmh = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_3_spinbn_childmh),
	                           27);
	gtk_table_attach (GTK_TABLE(table_1),
	                  childmh_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,   // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_3_spinbn_childmh,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,   // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_3_spinbn_childmh),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "child-min-width" gint >= 0 default=85
	GtkWidget* childmw_lbl = gtk_label_new("child-min-width");
	app->widget_3_spinbn_childmw = gtk_spin_button_new_with_range (0,200,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_3_spinbn_childmw),
	                           85);
	gtk_table_attach (GTK_TABLE(table_1),
	                  childmw_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,   // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_3_spinbn_childmw,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,   // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_3_spinbn_childmw),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_3_style_txt = g_string_new ("#rc style for class GtkButtonBox");
}

void ui_update_gtkbuttonbox()
{
}

void ui_delete_gtkbuttonbox()
{
}

void ui_create_gtkcombobox()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkComboBox");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (1, 2, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	// http://stackoverflow.com/questions/16630528/trying-to-populate-a-gtkcombobox-with-model-in-c
	GtkListStore* liststore;
	GtkCellRenderer* column;
	GtkWidget* combo;

	liststore = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
	gtk_list_store_insert_with_values (liststore, NULL, -1,
	                                   0, "red",
	                                   1, "Don't install.",
	                                   -1);
	gtk_list_store_insert_with_values (liststore, NULL, -1,
	                                   0, "green",
	                                   1, "This user only.",
	                                   -1);
	gtk_list_store_insert_with_values (liststore, NULL, -1,
	                                   0, "yellow",
	                                   1, "All users.",
	                                   -1);
	combo = gtk_combo_box_new_with_model (GTK_TREE_MODEL(liststore));
	g_object_unref (liststore);
	column = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start (GTK_CELL_LAYOUT(combo), column, TRUE);
	gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT(combo), column,
	                                "cell-background", 0,
	                                "text", 1,
	                                NULL);
	gtk_combo_box_set_active (GTK_COMBO_BOX(combo), 1);
	gtk_table_attach (GTK_TABLE(table_sample),
	                  combo,
	                  0, 1,    // left, right
	                  0, 1,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,   // GtkAttachOptions
	                  0, 0);   // x,y padding

	// the second example from SO
	GtkWidget* combo2 = gtk_combo_box_text_new();
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo2), "Don't install.");
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo2), "This user only.");
    gtk_combo_box_append_text(GTK_COMBO_BOX(combo2), "All users");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo2), 1);

	gtk_table_attach (GTK_TABLE(table_sample),
	                  combo2,
	                  1, 2,    // left, right
	                  0, 1,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,   // GtkAttachOptions
	                  0, 0);   // x,y padding





	// Set the labels on the left side.
	const gint TABLE_0_ROW = 5; // 1 header, 4 colors
	const gint TABLE_0_COL = 6;
	GtkWidget* table_0 = gtk_table_new (TABLE_0_ROW, TABLE_0_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_0,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	const gchar* rows_txt[TABLE_0_ROW] = { "", "fg", "bg", "text", "base" };

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		GtkWidget* label = gtk_label_new (rows_txt[i]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  0, 1,    // left, right
		                  i, i+1,  // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);   // x,y padding
	}

	// Set the labels on the top.
	const gchar* cols_txt[TABLE_0_COL] = {
		"", "NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	for (gint j=1; j<TABLE_0_COL; ++j)
	{
		GtkWidget* label = gtk_label_new (cols_txt[j]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
	}

	// Set the color buttons
	/* fg[NORMAL] = "#747474"  , also ACTIVE,PRELIGHT,SELECTED,INSENSITIVE
	   bg[NORMAL] = "#DCDAD5"  , idem
	   text[NORMAL] = "#000000", idem
	   base[NORMAL] = "#FFFFFF", idem
	 */
	GtkStyle* style = gtk_widget_get_style (app->window);

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		for (gint j=1; j<TABLE_0_COL; ++j)
		{
			GdkColor* clr;
			if (i == 1)      clr = &(style->fg[j-1]);
			else if (i == 2) clr = &(style->bg[j-1]);
			else if (i == 3) clr = &(style->text[j-1]);
			else if (i == 4) clr = &(style->base[j-1]);
			else exit(-1);
			app->widget_4_clrbn[i-1][j-1] =
				gtk_color_button_new_with_color (clr);
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_4_clrbn[i-1][j-1],
			                  j, j+1, // left, right
			                  i, i+1, // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);  // x,y padding
			g_signal_connect (G_OBJECT(app->widget_4_clrbn[i-1][j-1]),
			                  "color-set",
			                  G_CALLBACK(cb_color_set),
			                  NULL);
		}
	}


	// font_desc    font_name="FreeSans 11"
	GtkWidget* table_1 = gtk_table_new (6, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* font_desc_lbl = gtk_label_new ("font_desc");
	char* font_name = pango_font_description_to_string (style->font_desc);
	app->widget_4_fn_bn = gtk_font_button_new_with_font (font_name);
	g_free (font_name);
	gtk_table_attach (GTK_TABLE(table_1),
	                  font_desc_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_4_fn_bn,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_4_fn_bn),
	                  "font-set",
	                  G_CALLBACK(cb_font_set),
	                  NULL);

	// xthickness = 2
	GtkWidget* xthickness_lbl = gtk_label_new ("xthickness");
	app->widget_4_spinbn_xth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_4_spinbn_xth),
	                           (gdouble)style->xthickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  xthickness_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_4_spinbn_xth,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_4_spinbn_xth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// ythickness = 2
	GtkWidget* ythickness_lbl = gtk_label_new ("ythickness");
	app->widget_4_spinbn_yth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_4_spinbn_yth),
	                           (gdouble)style->ythickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  ythickness_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_4_spinbn_yth,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_4_spinbn_yth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);


	// "appears-as-list" gboolean default=FALSE
	GtkWidget* appearsal_lbl = gtk_label_new ("appears-as-list");
	gtk_table_attach (GTK_TABLE(table_1),
	                  appearsal_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_4_chkbn_appearsal = gtk_check_button_new ();
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_4_chkbn_appearsal,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_4_chkbn_appearsal),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);


	// "arrow-size" gint >= 0 default=15
	GtkWidget* arrowsz_lbl = gtk_label_new ("arrow-size");
	app->widget_4_spinbn_arrowsz = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_4_spinbn_arrowsz),
	                           15);
	gtk_table_attach (GTK_TABLE(table_1),
	                  arrowsz_lbl,
	                  0, 1,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_4_spinbn_arrowsz,
	                  1, 2,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_4_spinbn_arrowsz),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "shadow-type" GtkShadowType default=GTK_SHADOW_NONE
	GtkWidget* shadowt_lbl = gtk_label_new ("shadow-type");
	app->widget_4_cbbox_shadowt = gtk_combo_box_text_new ();
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_4_cbbox_shadowt),
	                           "GTK_SHADOW_NONE");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_4_cbbox_shadowt),
	                           "GTK_SHADOW_IN");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_4_cbbox_shadowt),
	                           "GTK_SHADOW_OUT");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_4_cbbox_shadowt),
	                           "GTK_SHADOW_ETCHED_IN");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_4_cbbox_shadowt),
	                           "GTK_SHADOW_ETCHED_OUT");
    gtk_combo_box_set_active(GTK_COMBO_BOX(app->widget_4_cbbox_shadowt), 0);

	gtk_table_attach (GTK_TABLE(table_1),
	                  shadowt_lbl,
	                  0, 1,   // left, right
	                  5, 6,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_4_cbbox_shadowt,
	                  1, 2,   // left, right
	                  5, 6,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_4_cbbox_shadowt),
	                  "changed",
	                  G_CALLBACK(cb_cbbox_changed),
	                  NULL);


	// retain the style as text to write it into rc file at any time.
	app->widget_4_style_txt = g_string_new ("#rc style for class GtkComboBox");
}

void ui_update_gtkcombobox()
{
}

void ui_delete_gtkcombobox()
{
}

void ui_create_gtkentry()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkEntry");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (1, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	GtkWidget* entry[3];
	const gchar* entry_txt[] = { "no frame", "not editable", "i is invisible" };
	for (gint i = 0; i < 3; ++i)
	{
		entry[i] = gtk_entry_new();
		gtk_entry_set_text (GTK_ENTRY(entry[i]), entry_txt[i]);
		if (i == 0) gtk_entry_set_has_frame (GTK_ENTRY(entry[i]), false);
		if (i == 1) gtk_entry_set_editable (GTK_ENTRY(entry[i]), false);
		if (i == 2) gtk_entry_set_invisible_char (GTK_ENTRY(entry[i]), 'i');

		gtk_table_attach (GTK_TABLE(table_sample),
		                  entry[i],
		                  i, i+1,    // left, right
		                  0, 1,      // top, bottom
		                  GTK_EXPAND, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);     // x,y padding
	}





	// Set the labels on the left side.
	const gint TABLE_0_ROW = 5; // 1 header, 4 colors
	const gint TABLE_0_COL = 6;
	GtkWidget* table_0 = gtk_table_new (TABLE_0_ROW, TABLE_0_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_0,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	const gchar* rows_txt[TABLE_0_ROW] = { "", "fg", "bg", "text", "base" };

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		GtkWidget* label = gtk_label_new (rows_txt[i]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  0, 1,    // left, right
		                  i, i+1,  // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);   // x,y padding
	}

	// Set the labels on the top.
	const gchar* cols_txt[TABLE_0_COL] = {
		"", "NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	for (gint j=1; j<TABLE_0_COL; ++j)
	{
		GtkWidget* label = gtk_label_new (cols_txt[j]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
	}

	// Set the color buttons
	/* fg[NORMAL] = "#747474"  , also ACTIVE,PRELIGHT,SELECTED,INSENSITIVE
	   bg[NORMAL] = "#DCDAD5"  , idem
	   text[NORMAL] = "#000000", idem
	   base[NORMAL] = "#FFFFFF", idem
	 */
	GtkStyle* style = gtk_widget_get_style (app->window);

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		for (gint j=1; j<TABLE_0_COL; ++j)
		{
			GdkColor* clr;
			if (i == 1)      clr = &(style->fg[j-1]);
			else if (i == 2) clr = &(style->bg[j-1]);
			else if (i == 3) clr = &(style->text[j-1]);
			else if (i == 4) clr = &(style->base[j-1]);
			else exit(-1);
			app->widget_5_clrbn[i-1][j-1] =
				gtk_color_button_new_with_color (clr);
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_5_clrbn[i-1][j-1],
			                  j, j+1, // left, right
			                  i, i+1, // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);  // x,y padding
			g_signal_connect (G_OBJECT(app->widget_5_clrbn[i-1][j-1]),
			                  "color-set",
			                  G_CALLBACK(cb_color_set),
			                  NULL);
		}
	}


	// font_desc    font_name="FreeSans 11"
	GtkWidget* table_1 = gtk_table_new (4, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* font_desc_lbl = gtk_label_new ("font_desc");
	char* font_name = pango_font_description_to_string (style->font_desc);
	app->widget_5_fn_bn = gtk_font_button_new_with_font (font_name);
	g_free (font_name);
	gtk_table_attach (GTK_TABLE(table_1),
	                  font_desc_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_5_fn_bn,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_5_fn_bn),
	                  "font-set",
	                  G_CALLBACK(cb_font_set),
	                  NULL);

	// xthickness = 2
	GtkWidget* xthickness_lbl = gtk_label_new ("xthickness");
	app->widget_5_spinbn_xth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_5_spinbn_xth),
	                           (gdouble)style->xthickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  xthickness_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_5_spinbn_xth,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_5_spinbn_xth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// ythickness = 2
	GtkWidget* ythickness_lbl = gtk_label_new ("ythickness");
	app->widget_5_spinbn_yth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_5_spinbn_yth),
	                           (gdouble)style->ythickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  ythickness_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_5_spinbn_yth,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_5_spinbn_yth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);


	// "icon-prelight" gboolean default=TRUE
	GtkWidget* iconp_lbl = gtk_label_new ("icon-prelight");
	gtk_table_attach (GTK_TABLE(table_1),
	                  iconp_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_5_chkbn_iconp = gtk_check_button_new ();
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(app->widget_5_chkbn_iconp),
	                              TRUE);
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_5_chkbn_iconp,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_5_chkbn_iconp),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// new table 4x5
	// row 1: 5
	// row 2: 2
	// row 3: 5
	// row 4: 2

	GtkWidget* table_2 = gtk_table_new (4, 5, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_2,
	                    FALSE,    // expand
	                    FALSE,    // fill
	                    0);       // padding

	// "inner-border" GtkBorder = {1, 1, 1, 1}
	GtkWidget* innerb_lbl = gtk_label_new ("inner-border");
	gtk_table_attach (GTK_TABLE(table_2),
	                  innerb_lbl,
	                  0, 1,    // left, right
	                  0, 1,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,   // GtkAttachOptions
	                  0, 0);   // x, y padding

	for (gint j=1; j < 5; ++j)
	{
		app->widget_5_spinbn_innerb[j-1] =
			gtk_spin_button_new_with_range (0, 10, 1);
		gtk_spin_button_set_value (
			GTK_SPIN_BUTTON(app->widget_5_spinbn_innerb[j-1]),
			1);
		gtk_table_attach (GTK_TABLE(table_2),
		                  app->widget_5_spinbn_innerb[j-1],
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
		g_signal_connect (G_OBJECT(app->widget_5_spinbn_innerb[j-1]),
		                  "value-changed",
		                  G_CALLBACK(cb_spinbn_value_changed),
		                  NULL);
	}

	// "invisible-char" guint default=0 , used to mask entry in "password mode"
	GtkWidget* invisiblec_lbl = gtk_label_new ("invisible-char");
	app->widget_5_spinbn_invisiblec = gtk_spin_button_new_with_range (0,127,1); // ascii table
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_5_spinbn_invisiblec),
	                           0);
	gtk_table_attach (GTK_TABLE(table_2),
	                  invisiblec_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_2),
	                  app->widget_5_spinbn_invisiblec,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_5_spinbn_invisiblec),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "progress-border" GtkBorder = {1, 1, 1, 1}
	GtkWidget* progressb_lbl = gtk_label_new ("progress-border");
	gtk_table_attach (GTK_TABLE(table_2),
	                  progressb_lbl,
	                  0, 1,    // left, right
	                  2, 3,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,   // GtkAttachOptions
	                  0, 0);   // x, y padding

	for (gint j=1; j < 5; ++j)
	{
		app->widget_5_spinbn_progressb[j-1] =
			gtk_spin_button_new_with_range (0, 10, 1);
		gtk_spin_button_set_value (
			GTK_SPIN_BUTTON(app->widget_5_spinbn_progressb[j-1]),
			1);
		gtk_table_attach (GTK_TABLE(table_2),
		                  app->widget_5_spinbn_progressb[j-1],
		                  j, j+1,   // left, right
		                  2, 3,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
		g_signal_connect (G_OBJECT(app->widget_5_spinbn_progressb[j-1]),
		                  "value-changed",
		                  G_CALLBACK(cb_spinbn_value_changed),
		                  NULL);
	}

	// "state-hint" gboolean default=FALSE , deprecated since 2.22
	GtkWidget* stateh_lbl = gtk_label_new ("state-hint");
	gtk_table_attach (GTK_TABLE(table_2),
	                  stateh_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_5_chkbn_stateh = gtk_check_button_new ();
	gtk_table_attach (GTK_TABLE(table_2),
	                  app->widget_5_chkbn_stateh,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_5_chkbn_stateh),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_5_style_txt = g_string_new ("#rc style for class GtkEntry");
}

void ui_update_gtkentry()
{
}

void ui_delete_gtkentry()
{
}

void ui_create_gtkexpander()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkExpander");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (1, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	GtkWidget* exp_wgt[3];
	const gchar* exp_txt[] = {"1st expander", "2dn expander", "3rd expander"};
	for (gint i = 0; i < 3; ++i)
	{
		exp_wgt[i] = gtk_expander_new (exp_txt[i]);
		gtk_expander_set_expanded (GTK_EXPANDER(exp_wgt[i]), TRUE);
		GtkWidget* embed;
		if (i==0) embed = gtk_label_new ("Label");
		else if (i==1) embed = gtk_button_new_with_label ("Button");
		else if (i==2)
		{
			embed = gtk_entry_new ();
			gtk_entry_set_text (GTK_ENTRY(embed), "Entry");
		}
		gtk_container_add (GTK_CONTAINER(exp_wgt[i]), embed);
		gtk_table_attach (GTK_TABLE(table_sample),
		                  exp_wgt[i],
		                  i, i+1,    // left, right
		                  0, 1,      // top, bottom
		                  GTK_EXPAND, GTK_SHRINK,  // GtkAttachOptions
		                  0, 0);     // x,y padding
	}





	// Set the labels on the left side.
	const gint TABLE_0_ROW = 5; // 1 header, 4 colors
	const gint TABLE_0_COL = 6;
	GtkWidget* table_0 = gtk_table_new (TABLE_0_ROW, TABLE_0_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_0,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	const gchar* rows_txt[TABLE_0_ROW] = { "", "fg", "bg", "text", "base" };

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		GtkWidget* label = gtk_label_new (rows_txt[i]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  0, 1,    // left, right
		                  i, i+1,  // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);   // x,y padding
	}

	// Set the labels on the top.
	const gchar* cols_txt[TABLE_0_COL] = {
		"", "NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	for (gint j=1; j<TABLE_0_COL; ++j)
	{
		GtkWidget* label = gtk_label_new (cols_txt[j]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
	}

	// Set the color buttons
	/* fg[NORMAL] = "#747474"  , also ACTIVE,PRELIGHT,SELECTED,INSENSITIVE
	   bg[NORMAL] = "#DCDAD5"  , idem
	   text[NORMAL] = "#000000", idem
	   base[NORMAL] = "#FFFFFF", idem
	 */
	GtkStyle* style = gtk_widget_get_style (app->window);

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		for (gint j=1; j<TABLE_0_COL; ++j)
		{
			GdkColor* clr;
			if (i == 1)      clr = &(style->fg[j-1]);
			else if (i == 2) clr = &(style->bg[j-1]);
			else if (i == 3) clr = &(style->text[j-1]);
			else if (i == 4) clr = &(style->base[j-1]);
			else exit(-1);
			app->widget_6_clrbn[i-1][j-1] =
				gtk_color_button_new_with_color (clr);
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_6_clrbn[i-1][j-1],
			                  j, j+1, // left, right
			                  i, i+1, // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);  // x,y padding
			g_signal_connect (G_OBJECT(app->widget_6_clrbn[i-1][j-1]),
			                  "color-set",
			                  G_CALLBACK(cb_color_set),
			                  NULL);
		}
	}


	// font_desc    font_name="FreeSans 11"
	GtkWidget* table_1 = gtk_table_new (5, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* font_desc_lbl = gtk_label_new ("font_desc");
	char* font_name = pango_font_description_to_string (style->font_desc);
	app->widget_6_fn_bn = gtk_font_button_new_with_font (font_name);
	g_free (font_name);
	gtk_table_attach (GTK_TABLE(table_1),
	                  font_desc_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_6_fn_bn,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_6_fn_bn),
	                  "font-set",
	                  G_CALLBACK(cb_font_set),
	                  NULL);

	// xthickness = 2
	GtkWidget* xthickness_lbl = gtk_label_new ("xthickness");
	app->widget_6_spinbn_xth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_6_spinbn_xth),
	                           (gdouble)style->xthickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  xthickness_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_6_spinbn_xth,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_6_spinbn_xth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// ythickness = 2
	GtkWidget* ythickness_lbl = gtk_label_new ("ythickness");
	app->widget_6_spinbn_yth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_6_spinbn_yth),
	                           (gdouble)style->ythickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  ythickness_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_6_spinbn_yth,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_6_spinbn_yth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);


	// "expander-size" gint >=0 default=10
	GtkWidget* expandersz_lbl = gtk_label_new ("expander-size");
	app->widget_6_spinbn_expandersz = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_6_spinbn_expandersz),
	                           10);
	gtk_table_attach (GTK_TABLE(table_1),
	                  expandersz_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_6_spinbn_expandersz,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_6_spinbn_expandersz),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "expander-spacing" gint >= 0 default=2
	GtkWidget* expandersp_lbl = gtk_label_new ("expander-spacing");
	app->widget_6_spinbn_expandersp = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_6_spinbn_expandersp),
	                           2);
	gtk_table_attach (GTK_TABLE(table_1),
	                  expandersp_lbl,
	                  0, 1,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_6_spinbn_expandersp,
	                  1, 2,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_6_spinbn_expandersp),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_6_style_txt = g_string_new ("#rc style for class GtkExpander");
}

void ui_update_gtkexpander()
{
}

void ui_delete_gtkexpander()
{
}

void ui_create_gtkscrollbar()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkScrollbar");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	// sample from SO
	// http://stackoverflow.com/questions/8403731/gtk-and-scrolling-text-view
	const gchar* text = "sample text";
	GtkTextTagTable* txttags = gtk_text_tag_table_new ();
	GtkTextBuffer* txtbuff = gtk_text_buffer_new (txttags);
	gtk_text_buffer_set_text (txtbuff, text, strlen(text));
	GtkWidget* txtview = gtk_text_view_new_with_buffer (txtbuff);
	GtkWidget* scrwin = gtk_scrolled_window_new (NULL, NULL);
	gtk_container_add (GTK_CONTAINER(scrwin), txtview);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    scrwin,
	                    FALSE,   // expanding
	                    FALSE,   // fill
	                    0);      // padding



	GtkWidget* table_1 = gtk_table_new (6, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	// "fixed-slider-length" gboolean default=FALSE
	GtkWidget* fixedsl_lbl = gtk_label_new ("fixed-slider-length");
	gtk_table_attach (GTK_TABLE(table_1),
	                  fixedsl_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_7_chkbn_fixedsl = gtk_check_button_new ();
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_7_chkbn_fixedsl,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_7_chkbn_fixedsl),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// "has-backward-stepper" gboolean default=TRUE
	GtkWidget* hasbs_lbl = gtk_label_new ("has-backward-stepper");
	gtk_table_attach (GTK_TABLE(table_1),
	                  hasbs_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_7_chkbn_hasbs = gtk_check_button_new ();
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_7_chkbn_hasbs,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_7_chkbn_hasbs),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// "has-forward-stepper" gboolean default=TRUE
	GtkWidget* hasfs_lbl = gtk_label_new ("has-forward-stepper");
	gtk_table_attach (GTK_TABLE(table_1),
	                  hasfs_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_7_chkbn_hasfs = gtk_check_button_new ();
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(app->widget_7_chkbn_hasfs),
	                           TRUE);
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_7_chkbn_hasfs,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_7_chkbn_hasfs),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// "has-secondary-backward-stepper" gboolean default=FALSE
	GtkWidget* hassbs_lbl = gtk_label_new ("has-secondary-backward-stepper");
	gtk_table_attach (GTK_TABLE(table_1),
	                  hassbs_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_7_chkbn_hassbs = gtk_check_button_new ();
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_7_chkbn_hassbs,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_7_chkbn_hassbs),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// "has-secondary-forward-stepper" gboolean default=FALSE
	GtkWidget* hassfs_lbl = gtk_label_new ("has-secondary-forward-stepper");
	gtk_table_attach (GTK_TABLE(table_1),
	                  hassfs_lbl,
	                  0, 1,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_7_chkbn_hassfs = gtk_check_button_new ();
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_7_chkbn_hassfs,
	                  1, 2,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_7_chkbn_hassfs),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// "min-slider-length" gint >= 0 default=21
	GtkWidget* minsl_lbl = gtk_label_new ("min-slider-length");
	app->widget_7_spinbn_minsl = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_7_spinbn_minsl),
	                           21);
	gtk_table_attach (GTK_TABLE(table_1),
	                  minsl_lbl,
	                  0, 1,   // left, right
	                  5, 6,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_7_spinbn_minsl,
	                  1, 2,   // left, right
	                  5, 6,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_7_spinbn_minsl),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_7_style_txt = g_string_new ("#rc style for class GtkScrollbar");
}

void ui_update_gtkscrollbar()
{
}

void ui_delete_gtkscrollbar()
{
}

void ui_create_gtkarrow()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkArrow");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (2, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	GtkWidget* spinbn[3];
	GtkWidget* spinlbl[3];
	const gchar* lbl_txt[] = {"value-x", "value-y", "value-z"};
	for (gint i = 0; i < 3; i++)
	{
		spinlbl[i] = gtk_label_new (lbl_txt[i]);
		spinbn[i] = gtk_spin_button_new_with_range (0, 10, 1);
		gtk_spin_button_set_value (GTK_SPIN_BUTTON(spinbn[i]), i+5);

		gtk_table_attach (GTK_TABLE(table_sample),
		                  spinlbl[i],
		                  i, i+1,    // left, right
		                  0, 1,      // top, bottom
		                  GTK_EXPAND, GTK_SHRINK,   // GtkAttachOptions
		                  0, 0);     // x,y padding
		gtk_table_attach (GTK_TABLE(table_sample),
		                  spinbn[i],
		                  i, i+1,    // left, right
		                  1, 2,      // top, bottom
		                  GTK_EXPAND, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);     // x,y padding
	}


	GtkWidget* table_1 = gtk_table_new (1, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	// "arrow-scaling" gfloat [0,1] default=0.7
	GtkWidget* arrowsc_lbl = gtk_label_new ("arrow-scaling");
	app->widget_8_spinbn_arrowsc = gtk_spin_button_new_with_range (0.0,1.0,0.1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_8_spinbn_arrowsc),
	                           0.7);
	gtk_table_attach (GTK_TABLE(table_1),
	                  arrowsc_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_8_spinbn_arrowsc,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_8_spinbn_arrowsc),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_8_style_txt = g_string_new ("#rc style for class GtkArrow");
}

void ui_update_gtkarrow()
{
}

void ui_delete_gtkarrow()
{
}

void ui_create_gtkprogressbar()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkProgressBar");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (1, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	GtkWidget* progress[3];
	for(gint i=0; i<3; ++i)
	{
		progress[i] = gtk_progress_bar_new();
		gchar text[200];
		sprintf(text, "%d%%", i*50);
		gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progress[i]), text);
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress[i]), i*0.5);
		                                                          // 0.0 -> 1.0

		gtk_table_attach (GTK_TABLE(table_sample),
		                  progress[i],
		                  i, i+1,   // left , right
		                  0, 1,     // top  , bottom
		                  GTK_EXPAND, GTK_SHRINK,   // GtkAttachOptions
		                  0, 0);    // x, y padding
	}




	// Set the labels on the left side.
	const gint TABLE_0_ROW = 5; // 1 header, 4 colors
	const gint TABLE_0_COL = 6;
	GtkWidget* table_0 = gtk_table_new (TABLE_0_ROW, TABLE_0_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_0,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	const gchar* rows_txt[TABLE_0_ROW] = { "", "fg", "bg", "text", "base" };

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		GtkWidget* label = gtk_label_new (rows_txt[i]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  0, 1,    // left, right
		                  i, i+1,  // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);   // x,y padding
	}

	// Set the labels on the top.
	const gchar* cols_txt[TABLE_0_COL] = {
		"", "NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	for (gint j=1; j<TABLE_0_COL; ++j)
	{
		GtkWidget* label = gtk_label_new (cols_txt[j]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
	}

	// Set the color buttons
	/* fg[NORMAL] = "#747474"  , also ACTIVE,PRELIGHT,SELECTED,INSENSITIVE
	   bg[NORMAL] = "#DCDAD5"  , idem
	   text[NORMAL] = "#000000", idem
	   base[NORMAL] = "#FFFFFF", idem
	 */
	GtkStyle* style = gtk_widget_get_style (app->window);

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		for (gint j=1; j<TABLE_0_COL; ++j)
		{
			GdkColor* clr;
			if (i == 1)      clr = &(style->fg[j-1]);
			else if (i == 2) clr = &(style->bg[j-1]);
			else if (i == 3) clr = &(style->text[j-1]);
			else if (i == 4) clr = &(style->base[j-1]);
			else exit(-1);
			app->widget_9_clrbn[i-1][j-1] =
				gtk_color_button_new_with_color (clr);
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_9_clrbn[i-1][j-1],
			                  j, j+1, // left, right
			                  i, i+1, // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);  // x,y padding
			g_signal_connect (G_OBJECT(app->widget_9_clrbn[i-1][j-1]),
			                  "color-set",
			                  G_CALLBACK(cb_color_set),
			                  NULL);
		}
	}


	// font_desc    font_name="FreeSans 11"
	GtkWidget* table_1 = gtk_table_new (9, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* font_desc_lbl = gtk_label_new ("font_desc");
	char* font_name = pango_font_description_to_string (style->font_desc);
	app->widget_9_fn_bn = gtk_font_button_new_with_font (font_name);
	g_free (font_name);
	gtk_table_attach (GTK_TABLE(table_1),
	                  font_desc_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_9_fn_bn,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_9_fn_bn),
	                  "font-set",
	                  G_CALLBACK(cb_font_set),
	                  NULL);

	// xthickness = 2
	GtkWidget* xthickness_lbl = gtk_label_new ("xthickness");
	app->widget_9_spinbn_xth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_9_spinbn_xth),
	                           (gdouble)style->xthickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  xthickness_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_9_spinbn_xth,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_9_spinbn_xth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// ythickness = 2
	GtkWidget* ythickness_lbl = gtk_label_new ("ythickness");
	app->widget_9_spinbn_yth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_9_spinbn_yth),
	                           (gdouble)style->ythickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  ythickness_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_9_spinbn_yth,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_9_spinbn_yth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);


	// "min-horizontal-bar-height" gint >= 1 default=20
	GtkWidget* minhzbarh_lbl = gtk_label_new ("min-horizontal-bar-height");
	app->widget_9_spinbn_minhzbarh = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_9_spinbn_minhzbarh),
	                           20);
	gtk_table_attach (GTK_TABLE(table_1),
	                  minhzbarh_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_9_spinbn_minhzbarh,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_9_spinbn_minhzbarh),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "min-horizontal-bar-width" gint >= 1 default=150
	GtkWidget* minhzbarw_lbl = gtk_label_new ("min-horizontal-bar-width");
	app->widget_9_spinbn_minhzbarw = gtk_spin_button_new_with_range (0,3000,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_9_spinbn_minhzbarw),
	                           150);
	gtk_table_attach (GTK_TABLE(table_1),
	                  minhzbarw_lbl,
	                  0, 1,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_9_spinbn_minhzbarw,
	                  1, 2,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_9_spinbn_minhzbarw),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "min-vertical-bar-height" gint >= 1 default=80
	GtkWidget* minvtbarh_lbl = gtk_label_new ("min-vertical-bar-height");
	app->widget_9_spinbn_minvtbarh = gtk_spin_button_new_with_range (0,2000,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_9_spinbn_minvtbarh),
	                           80);
	gtk_table_attach (GTK_TABLE(table_1),
	                  minvtbarh_lbl,
	                  0, 1,   // left, right
	                  5, 6,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_9_spinbn_minvtbarh,
	                  1, 2,   // left, right
	                  5, 6,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_9_spinbn_minvtbarh),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "min-vertical-bar-width" gint >= 1 default=22
	GtkWidget* minvtbarw_lbl = gtk_label_new ("min-vertical-bar-width");
	app->widget_9_spinbn_minvtbarw = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_9_spinbn_minvtbarw),
	                           22);
	gtk_table_attach (GTK_TABLE(table_1),
	                  minvtbarw_lbl,
	                  0, 1,   // left, right
	                  6, 7,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_9_spinbn_minvtbarw,
	                  1, 2,   // left, right
	                  6, 7,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_9_spinbn_minvtbarw),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "xspacing" gint >= 0 default=7
	GtkWidget* xs_lbl = gtk_label_new ("xspacing");
	app->widget_9_spinbn_xs = gtk_spin_button_new_with_range (0,50,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_9_spinbn_xs),
	                           7);
	gtk_table_attach (GTK_TABLE(table_1),
	                  xs_lbl,
	                  0, 1,   // left, right
	                  7, 8,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_9_spinbn_xs,
	                  1, 2,   // left, right
	                  7, 8,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_9_spinbn_xs),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "yspacing" gint >= 0 default=7
	GtkWidget* ys_lbl = gtk_label_new ("yspacing");
	app->widget_9_spinbn_ys = gtk_spin_button_new_with_range (0,50,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_9_spinbn_ys),
	                           7);
	gtk_table_attach (GTK_TABLE(table_1),
	                  ys_lbl,
	                  0, 1,   // left, right
	                  8, 9,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_9_spinbn_ys,
	                  1, 2,   // left, right
	                  8, 9,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_9_spinbn_ys),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_9_style_txt = g_string_new ("#rc style for class GtkProgressBar");
}

void ui_update_gtkprogressbar()
{
}

void ui_delete_gtkprogressbar()
{
}

void ui_create_gtkspinbutton()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkSpinButton");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (2, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	GtkWidget* spin_bn[3];
	GtkWidget* spin_lbl[3];

	for (gint i = 0; i < 3; ++i)
	{
		GtkObject* adjustment = gtk_adjustment_new ((gdouble)i*10, // value
		                                            0.0,           // lower
		                                            100.0,         // upper
		                                            1.0,           // step inc
		                                            10.0,          // page inc
		                                            10.0);         // page size
		spin_bn[i] = gtk_spin_button_new (GTK_ADJUSTMENT(adjustment),
		                                  1.0,
		                                  0);
		gchar text[100];
		sprintf(text, "GtkSpinButton:%d", i);
		spin_lbl[i] = gtk_label_new(text);
		gtk_table_attach (GTK_TABLE(table_sample),
		                  spin_bn[i],
		                  i, i+1,    // left,  right
		                  0, 1,      // top, bottom
		                  GTK_EXPAND, GTK_SHRINK,   // GtkAttachOptions
		                  0, 0);     // x, y padding

		gtk_table_attach (GTK_TABLE(table_sample),
		                  spin_lbl[i],
		                  i, i+1,    // left,  right
		                  1, 2,      // top, bottom
		                  GTK_EXPAND, GTK_SHRINK,   // GtkAttachOptions
		                  0, 0);     // x, y padding
	}


	GtkWidget* table_1 = gtk_table_new (1, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	// "shadow-type" GtkShadowType default=GTK_SHADOW_IN
	GtkWidget* shadowt_lbl = gtk_label_new ("shadow-type");
	app->widget_10_cbbox_shadowt = gtk_combo_box_text_new ();
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_10_cbbox_shadowt),
	                           "GTK_SHADOW_NONE");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_10_cbbox_shadowt),
	                           "GTK_SHADOW_IN");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_10_cbbox_shadowt),
	                           "GTK_SHADOW_OUT");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_10_cbbox_shadowt),
	                           "GTK_SHADOW_ETCHED_IN");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_10_cbbox_shadowt),
	                           "GTK_SHADOW_ETCHED_OUT");
    gtk_combo_box_set_active(GTK_COMBO_BOX(app->widget_10_cbbox_shadowt), 1);

	gtk_table_attach (GTK_TABLE(table_1),
	                  shadowt_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_10_cbbox_shadowt,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_10_cbbox_shadowt),
	                  "changed",
	                  G_CALLBACK(cb_cbbox_changed),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_10_style_txt = g_string_new ("#rc style for class GtkSpinButton");
}

void ui_update_gtkspinbutton()
{
}

void ui_delete_gtkspinbutton()
{
}

void ui_create_gtkstatusbar()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkStatusbar");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	// The statusbar attached to a table is not shown correctly.
	GtkWidget* statusbar = gtk_statusbar_new();
	guint uid = gtk_statusbar_get_context_id(GTK_STATUSBAR(statusbar),
	                                         "Statusbar example"); // context description

	gtk_statusbar_push (GTK_STATUSBAR(statusbar),
	                    uid,
	                    "Status bar sample message!");
	gtk_box_pack_start (GTK_BOX(vbox),
	                    statusbar,
	                    TRUE,  // expand
	                    TRUE,  // fill
	                    0);    // padding




	// Set the labels on the left side.
	const gint TABLE_0_ROW = 5; // 1 header, 4 colors
	const gint TABLE_0_COL = 6;
	GtkWidget* table_0 = gtk_table_new (TABLE_0_ROW, TABLE_0_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_0,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	const gchar* rows_txt[TABLE_0_ROW] = { "", "fg", "bg", "text", "base" };

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		GtkWidget* label = gtk_label_new (rows_txt[i]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  0, 1,    // left, right
		                  i, i+1,  // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);   // x,y padding
	}

	// Set the labels on the top.
	const gchar* cols_txt[TABLE_0_COL] = {
		"", "NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	for (gint j=1; j<TABLE_0_COL; ++j)
	{
		GtkWidget* label = gtk_label_new (cols_txt[j]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
	}

	// Set the color buttons
	/* fg[NORMAL] = "#747474"  , also ACTIVE,PRELIGHT,SELECTED,INSENSITIVE
	   bg[NORMAL] = "#DCDAD5"  , idem
	   text[NORMAL] = "#000000", idem
	   base[NORMAL] = "#FFFFFF", idem
	 */
	GtkStyle* style = gtk_widget_get_style (app->window);

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		for (gint j=1; j<TABLE_0_COL; ++j)
		{
			GdkColor* clr;
			if (i == 1)      clr = &(style->fg[j-1]);
			else if (i == 2) clr = &(style->bg[j-1]);
			else if (i == 3) clr = &(style->text[j-1]);
			else if (i == 4) clr = &(style->base[j-1]);
			else exit(-1);
			app->widget_11_clrbn[i-1][j-1] =
				gtk_color_button_new_with_color (clr);
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_11_clrbn[i-1][j-1],
			                  j, j+1, // left, right
			                  i, i+1, // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);  // x,y padding
			g_signal_connect (G_OBJECT(app->widget_11_clrbn[i-1][j-1]),
			                  "color-set",
			                  G_CALLBACK(cb_color_set),
			                  NULL);
		}
	}


	// font_desc    font_name="FreeSans 11"
	GtkWidget* table_1 = gtk_table_new (4, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* font_desc_lbl = gtk_label_new ("font_desc");
	char* font_name = pango_font_description_to_string (style->font_desc);
	app->widget_11_fn_bn = gtk_font_button_new_with_font (font_name);
	g_free (font_name);
	gtk_table_attach (GTK_TABLE(table_1),
	                  font_desc_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_11_fn_bn,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_11_fn_bn),
	                  "font-set",
	                  G_CALLBACK(cb_font_set),
	                  NULL);

	// xthickness = 2
	GtkWidget* xthickness_lbl = gtk_label_new ("xthickness");
	app->widget_11_spinbn_xth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_11_spinbn_xth),
	                           (gdouble)style->xthickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  xthickness_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_11_spinbn_xth,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_11_spinbn_xth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// ythickness = 2
	GtkWidget* ythickness_lbl = gtk_label_new ("ythickness");
	app->widget_11_spinbn_yth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_11_spinbn_yth),
	                           (gdouble)style->ythickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  ythickness_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_11_spinbn_yth,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_11_spinbn_yth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);



	// "shadow-type" GtkShadowType default=GTK_SHADOWN_IN
	GtkWidget* shadowt_lbl = gtk_label_new ("shadow-type");
	app->widget_11_cbbox_shadowt = gtk_combo_box_text_new ();
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_11_cbbox_shadowt),
	                           "GTK_SHADOW_NONE");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_11_cbbox_shadowt),
	                           "GTK_SHADOW_IN");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_11_cbbox_shadowt),
	                           "GTK_SHADOW_OUT");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_11_cbbox_shadowt),
	                           "GTK_SHADOW_ETCHED_IN");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_11_cbbox_shadowt),
	                           "GTK_SHADOW_ETCHED_OUT");
    gtk_combo_box_set_active(GTK_COMBO_BOX(app->widget_11_cbbox_shadowt), 1);

	gtk_table_attach (GTK_TABLE(table_1),
	                  shadowt_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_11_cbbox_shadowt,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_11_cbbox_shadowt),
	                  "changed",
	                  G_CALLBACK(cb_cbbox_changed),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_11_style_txt = g_string_new ("#rc style for class GtkStatusbar");
}

void ui_update_gtkstatusbar()
{
}

void ui_delete_gtkstatusbar()
{
}

void ui_create_gtktoolbar()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkToolbar");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	// example from the book, cap.9 sample: toolbars.cpp
	GtkWidget* toolbar = gtk_toolbar_new ();
	GtkToolItem* cut  = gtk_tool_button_new_from_stock (GTK_STOCK_CUT);
	GtkToolItem* copy = gtk_tool_button_new_from_stock (GTK_STOCK_COPY);
	GtkToolItem* paste= gtk_tool_button_new_from_stock (GTK_STOCK_PASTE);
	GtkToolItem* selectall = gtk_tool_button_new_from_stock (GTK_STOCK_SELECT_ALL);
	GtkToolItem* separator = gtk_separator_tool_item_new ();

	gtk_toolbar_set_show_arrow (GTK_TOOLBAR(toolbar), TRUE);
	gtk_toolbar_set_style (GTK_TOOLBAR (toolbar), GTK_TOOLBAR_BOTH);

	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), cut, 0);
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), copy, 1);
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), paste, 2);
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), separator, 3);
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), selectall, 4);

	gtk_box_pack_start (GTK_BOX(vbox),
	                    toolbar,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding




	// Set the labels on the left side.
	const gint TABLE_0_ROW = 5; // 1 header, 4 colors
	const gint TABLE_0_COL = 6;
	GtkWidget* table_0 = gtk_table_new (TABLE_0_ROW, TABLE_0_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_0,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	const gchar* rows_txt[TABLE_0_ROW] = { "", "fg", "bg", "text", "base" };

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		GtkWidget* label = gtk_label_new (rows_txt[i]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  0, 1,    // left, right
		                  i, i+1,  // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);   // x,y padding
	}

	// Set the labels on the top.
	const gchar* cols_txt[TABLE_0_COL] = {
		"", "NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	for (gint j=1; j<TABLE_0_COL; ++j)
	{
		GtkWidget* label = gtk_label_new (cols_txt[j]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
	}

	// Set the color buttons
	/* fg[NORMAL] = "#747474"  , also ACTIVE,PRELIGHT,SELECTED,INSENSITIVE
	   bg[NORMAL] = "#DCDAD5"  , idem
	   text[NORMAL] = "#000000", idem
	   base[NORMAL] = "#FFFFFF", idem
	 */
	GtkStyle* style = gtk_widget_get_style (app->window);

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		for (gint j=1; j<TABLE_0_COL; ++j)
		{
			GdkColor* clr;
			if (i == 1)      clr = &(style->fg[j-1]);
			else if (i == 2) clr = &(style->bg[j-1]);
			else if (i == 3) clr = &(style->text[j-1]);
			else if (i == 4) clr = &(style->base[j-1]);
			else exit(-1);
			app->widget_12_clrbn[i-1][j-1] =
				gtk_color_button_new_with_color (clr);
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_12_clrbn[i-1][j-1],
			                  j, j+1, // left, right
			                  i, i+1, // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);  // x,y padding
			g_signal_connect (G_OBJECT(app->widget_12_clrbn[i-1][j-1]),
			                  "color-set",
			                  G_CALLBACK(cb_color_set),
			                  NULL);
		}
	}


	// font_desc    font_name="FreeSans 11"
	GtkWidget* table_1 = gtk_table_new (9, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* font_desc_lbl = gtk_label_new ("font_desc");
	char* font_name = pango_font_description_to_string (style->font_desc);
	app->widget_12_fn_bn = gtk_font_button_new_with_font (font_name);
	g_free (font_name);
	gtk_table_attach (GTK_TABLE(table_1),
	                  font_desc_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_12_fn_bn,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_12_fn_bn),
	                  "font-set",
	                  G_CALLBACK(cb_font_set),
	                  NULL);

	// xthickness = 2
	GtkWidget* xthickness_lbl = gtk_label_new ("xthickness");
	app->widget_12_spinbn_xth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_12_spinbn_xth),
	                           (gdouble)style->xthickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  xthickness_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_12_spinbn_xth,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_12_spinbn_xth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// ythickness = 2
	GtkWidget* ythickness_lbl = gtk_label_new ("ythickness");
	app->widget_12_spinbn_yth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_12_spinbn_yth),
	                           (gdouble)style->ythickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  ythickness_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_12_spinbn_yth,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_12_spinbn_yth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);


	// "button-relief" GtkReliefStyle default=GTK_RELIEF_NONE
	GtkWidget* buttonr_lbl = gtk_label_new ("button-relief");
	app->widget_12_cbbox_buttonr = gtk_combo_box_text_new ();
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_12_cbbox_buttonr),
	                           "GTK_SHADOW_NONE");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_12_cbbox_buttonr),
	                           "GTK_SHADOW_IN");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_12_cbbox_buttonr),
	                           "GTK_SHADOW_OUT");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_12_cbbox_buttonr),
	                           "GTK_SHADOW_ETCHED_IN");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_12_cbbox_buttonr),
	                           "GTK_SHADOW_ETCHED_OUT");
    gtk_combo_box_set_active(GTK_COMBO_BOX(app->widget_12_cbbox_buttonr), 0);

	gtk_table_attach (GTK_TABLE(table_1),
	                  buttonr_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_12_cbbox_buttonr,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_12_cbbox_buttonr),
	                  "changed",
	                  G_CALLBACK(cb_cbbox_changed),
	                  NULL);

	// "internal-padding" gint >= 0 default=0
	GtkWidget* internalp_lbl = gtk_label_new ("internal-padding");
	app->widget_12_spinbn_internalp = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_12_spinbn_internalp),
	                           0);
	gtk_table_attach (GTK_TABLE(table_1),
	                  internalp_lbl,
	                  0, 1,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_12_spinbn_internalp,
	                  1, 2,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_12_spinbn_internalp),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "max-child-expand" gint >= 0 default=2147483647
	GtkWidget* maxce_lbl = gtk_label_new ("max-child-expand");
	app->widget_12_spinbn_maxce = gtk_spin_button_new_with_range (0,2147483647,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_12_spinbn_maxce),
	                           2147483647);
	gtk_table_attach (GTK_TABLE(table_1),
	                  maxce_lbl,
	                  0, 1,   // left, right
	                  5, 6,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_12_spinbn_maxce,
	                  1, 2,   // left, right
	                  5, 6,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_12_spinbn_maxce),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "shadow-type" GtkShadowType default=GTK_SHADOW_OUT
	GtkWidget* shadowt_lbl = gtk_label_new ("shadow-type");
	app->widget_12_cbbox_shadowt = gtk_combo_box_text_new ();
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_12_cbbox_shadowt),
	                           "GTK_SHADOW_NONE");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_12_cbbox_shadowt),
	                           "GTK_SHADOW_IN");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_12_cbbox_shadowt),
	                           "GTK_SHADOW_OUT");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_12_cbbox_shadowt),
	                           "GTK_SHADOW_ETCHED_IN");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_12_cbbox_shadowt),
	                           "GTK_SHADOW_ETCHED_OUT");
    gtk_combo_box_set_active(GTK_COMBO_BOX(app->widget_12_cbbox_shadowt), 2);

	gtk_table_attach (GTK_TABLE(table_1),
	                  shadowt_lbl,
	                  0, 1,   // left, right
	                  6, 7,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_12_cbbox_shadowt,
	                  1, 2,   // left, right
	                  6, 7,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_12_cbbox_shadowt),
	                  "changed",
	                  G_CALLBACK(cb_cbbox_changed),
	                  NULL);

	// "space-size" gint >= 0 default=12
	GtkWidget* spacesz_lbl = gtk_label_new ("space-size");
	app->widget_12_spinbn_spacesz = gtk_spin_button_new_with_range (0,50,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_12_spinbn_spacesz),
	                           12);
	gtk_table_attach (GTK_TABLE(table_1),
	                  spacesz_lbl,
	                  0, 1,   // left, right
	                  7, 8,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_12_spinbn_spacesz,
	                  1, 2,   // left, right
	                  7, 8,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_12_spinbn_spacesz),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "space-style" GtkToolbarSpaceStyle default=GTK_TOOLBAR_SPACE_LINE
	GtkWidget* spacest_lbl = gtk_label_new ("space-style");
	app->widget_12_cbbox_spacest = gtk_combo_box_text_new ();
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_12_cbbox_spacest),
	                           "GTK_TOOLBAR_SPACE_EMPTY");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_12_cbbox_spacest),
	                           "GTK_TOOLBAR_SPACE_LINE");
    gtk_combo_box_set_active(GTK_COMBO_BOX(app->widget_12_cbbox_spacest), 1);

	gtk_table_attach (GTK_TABLE(table_1),
	                  spacest_lbl,
	                  0, 1,   // left, right
	                  8, 9,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_12_cbbox_spacest,
	                  1, 2,   // left, right
	                  8, 9,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_12_cbbox_spacest),
	                  "changed",
	                  G_CALLBACK(cb_cbbox_changed),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_12_style_txt = g_string_new ("#rc style for class GtkToolbar");
}

void ui_update_gtktoolbar()
{
}

void ui_delete_gtktoolbar()
{
}

void ui_create_gtktoolbutton()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkToolButton");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	// example from the book, cap.9 sample: toolbars.cpp
	GtkWidget* toolbar = gtk_toolbar_new ();
	GtkToolItem* cut  = gtk_tool_button_new_from_stock (GTK_STOCK_CUT);
	GtkToolItem* copy = gtk_tool_button_new_from_stock (GTK_STOCK_COPY);
	GtkToolItem* paste= gtk_tool_button_new_from_stock (GTK_STOCK_PASTE);
	GtkToolItem* selectall = gtk_tool_button_new_from_stock (GTK_STOCK_SELECT_ALL);
	GtkToolItem* separator = gtk_separator_tool_item_new ();

	gtk_toolbar_set_show_arrow (GTK_TOOLBAR(toolbar), TRUE);
	gtk_toolbar_set_style (GTK_TOOLBAR (toolbar), GTK_TOOLBAR_BOTH);

	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), cut, 0);
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), copy, 1);
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), paste, 2);
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), separator, 3);
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), selectall, 4);

	gtk_box_pack_start (GTK_BOX(vbox),
	                    toolbar,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding




	// Set the labels on the left side.
	const gint TABLE_0_ROW = 5; // 1 header, 4 colors
	const gint TABLE_0_COL = 6;
	GtkWidget* table_0 = gtk_table_new (TABLE_0_ROW, TABLE_0_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_0,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	const gchar* rows_txt[TABLE_0_ROW] = { "", "fg", "bg", "text", "base" };

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		GtkWidget* label = gtk_label_new (rows_txt[i]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  0, 1,    // left, right
		                  i, i+1,  // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);   // x,y padding
	}

	// Set the labels on the top.
	const gchar* cols_txt[TABLE_0_COL] = {
		"", "NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	for (gint j=1; j<TABLE_0_COL; ++j)
	{
		GtkWidget* label = gtk_label_new (cols_txt[j]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
	}

	// Set the color buttons
	/* fg[NORMAL] = "#747474"  , also ACTIVE,PRELIGHT,SELECTED,INSENSITIVE
	   bg[NORMAL] = "#DCDAD5"  , idem
	   text[NORMAL] = "#000000", idem
	   base[NORMAL] = "#FFFFFF", idem
	 */
	GtkStyle* style = gtk_widget_get_style (app->window);

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		for (gint j=1; j<TABLE_0_COL; ++j)
		{
			GdkColor* clr;
			if (i == 1)      clr = &(style->fg[j-1]);
			else if (i == 2) clr = &(style->bg[j-1]);
			else if (i == 3) clr = &(style->text[j-1]);
			else if (i == 4) clr = &(style->base[j-1]);
			else exit(-1);
			app->widget_13_clrbn[i-1][j-1] =
				gtk_color_button_new_with_color (clr);
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_13_clrbn[i-1][j-1],
			                  j, j+1, // left, right
			                  i, i+1, // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);  // x,y padding
			g_signal_connect (G_OBJECT(app->widget_13_clrbn[i-1][j-1]),
			                  "color-set",
			                  G_CALLBACK(cb_color_set),
			                  NULL);
		}
	}


	// font_desc    font_name="FreeSans 11"
	GtkWidget* table_1 = gtk_table_new (4, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* font_desc_lbl = gtk_label_new ("font_desc");
	char* font_name = pango_font_description_to_string (style->font_desc);
	app->widget_13_fn_bn = gtk_font_button_new_with_font (font_name);
	g_free (font_name);
	gtk_table_attach (GTK_TABLE(table_1),
	                  font_desc_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_13_fn_bn,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_13_fn_bn),
	                  "font-set",
	                  G_CALLBACK(cb_font_set),
	                  NULL);

	// xthickness = 2
	GtkWidget* xthickness_lbl = gtk_label_new ("xthickness");
	app->widget_13_spinbn_xth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_13_spinbn_xth),
	                           (gdouble)style->xthickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  xthickness_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_13_spinbn_xth,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_13_spinbn_xth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// ythickness = 2
	GtkWidget* ythickness_lbl = gtk_label_new ("ythickness");
	app->widget_13_spinbn_yth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_13_spinbn_yth),
	                           (gdouble)style->ythickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  ythickness_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_13_spinbn_yth,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_13_spinbn_yth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);


	// "icon-spacing" gint >= 0 default=3
	GtkWidget* iconsp_lbl = gtk_label_new ("icon-spacing");
	app->widget_13_spinbn_iconsp = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_13_spinbn_iconsp),
	                           3);
	gtk_table_attach (GTK_TABLE(table_1),
	                  iconsp_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_13_spinbn_iconsp,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_13_spinbn_iconsp),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_13_style_txt = g_string_new ("#rc style for class GtkToolButton");
}

void ui_update_gtktoolbutton()
{
}

void ui_delete_gtktoolbutton()
{
}

void ui_create_gtkmenu()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkMenu");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	//  GtkMenu sample, book cap.9 - menubars.cpp
	GtkAccelGroup* group = gtk_accel_group_new ();
	GtkWidget* menubar = gtk_menu_bar_new ();
	GtkWidget* file = gtk_menu_item_new_with_label ("File");
	GtkWidget* edit = gtk_menu_item_new_with_label ("Edit");
	GtkWidget* help = gtk_menu_item_new_with_label ("Help");

	GtkWidget* filemenu = gtk_menu_new ();
	GtkWidget* editmenu = gtk_menu_new ();
	GtkWidget* helpmenu = gtk_menu_new ();

	gtk_menu_item_set_submenu (GTK_MENU_ITEM(file), filemenu);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM(edit), editmenu);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM(help), helpmenu);

	gtk_menu_shell_append (GTK_MENU_SHELL(menubar), file);
	gtk_menu_shell_append (GTK_MENU_SHELL(menubar), edit);
	gtk_menu_shell_append (GTK_MENU_SHELL(menubar), help);

	GtkWidget* New = gtk_image_menu_item_new_from_stock (GTK_STOCK_NEW, group);
	GtkWidget* Open= gtk_image_menu_item_new_from_stock (GTK_STOCK_OPEN, group);
	gtk_menu_shell_append (GTK_MENU_SHELL(filemenu), New);
	gtk_menu_shell_append (GTK_MENU_SHELL(filemenu), Open);

	GtkWidget* Cut  = gtk_image_menu_item_new_from_stock (GTK_STOCK_CUT, group);
	GtkWidget* Copy = gtk_image_menu_item_new_from_stock (GTK_STOCK_COPY, group);
	GtkWidget* Paste= gtk_image_menu_item_new_from_stock (GTK_STOCK_PASTE, group);
	gtk_menu_shell_append (GTK_MENU_SHELL (editmenu), Cut);
	gtk_menu_shell_append (GTK_MENU_SHELL (editmenu), Copy);
	gtk_menu_shell_append (GTK_MENU_SHELL (editmenu), Paste);

	GtkWidget* contents = gtk_image_menu_item_new_from_stock (GTK_STOCK_HELP, group);
	GtkWidget* about = gtk_image_menu_item_new_from_stock (GTK_STOCK_ABOUT, group);
	gtk_menu_shell_append (GTK_MENU_SHELL (helpmenu), contents);
	gtk_menu_shell_append (GTK_MENU_SHELL (helpmenu), about);

	gtk_box_pack_start (GTK_BOX(vbox),
	                    menubar,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding



	// Set the labels on the left side.
	const gint TABLE_0_ROW = 5; // 1 header, 4 colors
	const gint TABLE_0_COL = 6;
	GtkWidget* table_0 = gtk_table_new (TABLE_0_ROW, TABLE_0_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_0,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	const gchar* rows_txt[TABLE_0_ROW] = { "", "fg", "bg", "text", "base" };

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		GtkWidget* label = gtk_label_new (rows_txt[i]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  0, 1,    // left, right
		                  i, i+1,  // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);   // x,y padding
	}

	// Set the labels on the top.
	const gchar* cols_txt[TABLE_0_COL] = {
		"", "NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	for (gint j=1; j<TABLE_0_COL; ++j)
	{
		GtkWidget* label = gtk_label_new (cols_txt[j]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
	}

	// Set the color buttons
	/* fg[NORMAL] = "#747474"  , also ACTIVE,PRELIGHT,SELECTED,INSENSITIVE
	   bg[NORMAL] = "#DCDAD5"  , idem
	   text[NORMAL] = "#000000", idem
	   base[NORMAL] = "#FFFFFF", idem
	 */
	GtkStyle* style = gtk_widget_get_style (app->window);

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		for (gint j=1; j<TABLE_0_COL; ++j)
		{
			GdkColor* clr;
			if (i == 1)      clr = &(style->fg[j-1]);
			else if (i == 2) clr = &(style->bg[j-1]);
			else if (i == 3) clr = &(style->text[j-1]);
			else if (i == 4) clr = &(style->base[j-1]);
			else exit(-1);
			app->widget_14_clrbn[i-1][j-1] =
				gtk_color_button_new_with_color (clr);
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_14_clrbn[i-1][j-1],
			                  j, j+1, // left, right
			                  i, i+1, // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);  // x,y padding
			g_signal_connect (G_OBJECT(app->widget_14_clrbn[i-1][j-1]),
			                  "color-set",
			                  G_CALLBACK(cb_color_set),
			                  NULL);
		}
	}


	// font_desc    font_name="FreeSans 11"
	GtkWidget* table_1 = gtk_table_new (10, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* font_desc_lbl = gtk_label_new ("font_desc");
	char* font_name = pango_font_description_to_string (style->font_desc);
	app->widget_14_fn_bn = gtk_font_button_new_with_font (font_name);
	g_free (font_name);
	gtk_table_attach (GTK_TABLE(table_1),
	                  font_desc_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_14_fn_bn,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_14_fn_bn),
	                  "font-set",
	                  G_CALLBACK(cb_font_set),
	                  NULL);

	// xthickness = 2
	GtkWidget* xthickness_lbl = gtk_label_new ("xthickness");
	app->widget_14_spinbn_xth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_14_spinbn_xth),
	                           (gdouble)style->xthickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  xthickness_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_14_spinbn_xth,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_14_spinbn_xth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// ythickness = 2
	GtkWidget* ythickness_lbl = gtk_label_new ("ythickness");
	app->widget_14_spinbn_yth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_14_spinbn_yth),
	                           (gdouble)style->ythickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  ythickness_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_14_spinbn_yth,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_14_spinbn_yth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);


	// "arrow-placement" GtkArrowPlacement default=GTK_ARROWS_BOTH
	GtkWidget* arrowp_lbl = gtk_label_new ("arrow-placement");
	app->widget_14_cbbox_arrowp = gtk_combo_box_text_new ();
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_14_cbbox_arrowp),
	                           "GTK_ARROWS_BOTH");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_14_cbbox_arrowp),
	                           "GTK_ARROWS_START");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_14_cbbox_arrowp),
	                           "GTK_ARROWS_END");

    gtk_combo_box_set_active(GTK_COMBO_BOX(app->widget_14_cbbox_arrowp), 0);

	gtk_table_attach (GTK_TABLE(table_1),
	                  arrowp_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_14_cbbox_arrowp,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_14_cbbox_arrowp),
	                  "changed",
	                  G_CALLBACK(cb_cbbox_changed),
	                  NULL);

	// "arrow-scaling" gfloat [0,1] default=0.7
	GtkWidget* arrowsc_lbl = gtk_label_new ("arrow-scaling");
	app->widget_14_spinbn_arrowsc = gtk_spin_button_new_with_range (0.0,1.0,0.1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_14_spinbn_arrowsc),
	                           0.7);
	gtk_table_attach (GTK_TABLE(table_1),
	                  arrowsc_lbl,
	                  0, 1,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_14_spinbn_arrowsc,
	                  1, 2,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_14_spinbn_arrowsc),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "double-arrows" gboolean default=TRUE
	GtkWidget* doublea_lbl = gtk_label_new ("double-arrows");
	gtk_table_attach (GTK_TABLE(table_1),
	                  doublea_lbl,
	                  0, 1,   // left, right
	                  5, 6,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_14_chkbn_doublea = gtk_check_button_new ();
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(app->widget_14_chkbn_doublea),
	                           TRUE);
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_14_chkbn_doublea,
	                  1, 2,   // left, right
	                  5, 6,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_14_chkbn_doublea),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// "horizontal-offset" gint (didn't specify) default=-2 (submenu hz off in pix)
	GtkWidget* horizontaloff_lbl = gtk_label_new ("horizontal-offset");
	app->widget_14_spinbn_horizontaloff = gtk_spin_button_new_with_range (-10,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_14_spinbn_horizontaloff),
	                           -2);
	gtk_table_attach (GTK_TABLE(table_1),
	                  horizontaloff_lbl,
	                  0, 1,   // left, right
	                  6, 7,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_14_spinbn_horizontaloff,
	                  1, 2,   // left, right
	                  6, 7,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_14_spinbn_horizontaloff),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "horizontal-padding" gint >= 0 default=0
	GtkWidget* horizontalpadd_lbl = gtk_label_new ("horizontal-padding");
	app->widget_14_spinbn_horizontalpadd = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_14_spinbn_horizontalpadd),
	                           0);
	gtk_table_attach (GTK_TABLE(table_1),
	                  horizontalpadd_lbl,
	                  0, 1,   // left, right
	                  7, 8,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_14_spinbn_horizontalpadd,
	                  1, 2,   // left, right
	                  7, 8,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_14_spinbn_horizontalpadd),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "vertical-offset" gint (didn't specify) default=0 (submenu vt off in pix)
	GtkWidget* verticaloff_lbl = gtk_label_new ("vertical-offset");
	app->widget_14_spinbn_verticaloff = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_14_spinbn_verticaloff),
	                           0);
	gtk_table_attach (GTK_TABLE(table_1),
	                  verticaloff_lbl,
	                  0, 1,   // left, right
	                  8, 9,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_14_spinbn_verticaloff,
	                  1, 2,   // left, right
	                  8, 9,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_14_spinbn_verticaloff),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "vertical-padding" gint >= 0 default=1
	GtkWidget* verticalpadd_lbl = gtk_label_new ("vertical-padding");
	app->widget_14_spinbn_verticalpadd = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_14_spinbn_verticaloff),
	                           0);
	gtk_table_attach (GTK_TABLE(table_1),
	                  verticalpadd_lbl,
	                  0, 1,    // left, right
	                  9, 10,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_14_spinbn_verticalpadd,
	                  1, 2,    // left, right
	                  9, 10,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	g_signal_connect (G_OBJECT(app->widget_14_spinbn_verticalpadd),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_14_style_txt = g_string_new ("#rc style for class GtkMenu");
}

void ui_update_gtkmenu()
{
}

void ui_delete_gtkmenu()
{
}

void ui_create_gtkmenubar()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkMenuBar");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	/*  This sample menu is from book, cap.9 - uimanager.cpp
	    I changed the callbacks to NULL for Open, Save, etc.
	    Sample menu entries:
	 */
	const gint SMNUM_ENTRIES = 13;
	GtkActionEntry smentries[]=
		{
			{ "File", NULL, "_File", NULL, NULL, NULL },
			{ "Open", GTK_STOCK_OPEN, NULL, NULL, "Open an existing file", NULL},
			{ "Save", GTK_STOCK_SAVE, NULL, NULL, "Save the doc to a file", NULL},
			{ "Quit", GTK_STOCK_QUIT, NULL, NULL, "Quit the application",  NULL},
			{ "Edit", NULL, "_Edit", NULL, NULL, NULL},
			{ "Cut", GTK_STOCK_CUT, NULL, NULL, "Cut to clipboard", NULL},
			{ "Copy", GTK_STOCK_COPY, NULL, NULL, "Copy to clipboard", NULL},
			{ "Paste", GTK_STOCK_PASTE, NULL, NULL, "Paste from clipboard", NULL},
			{ "SelectAll", GTK_STOCK_SELECT_ALL, NULL, NULL, "Select all", NULL},
			{ "Deselect", NULL, "_Deselect", "<control>d", "Deselect all", NULL},
			{ "Help", NULL, "_Help", NULL, NULL, NULL},
			{ "Contents", GTK_STOCK_HELP, NULL, NULL, "Get help", NULL},
			{ "About", GTK_STOCK_ABOUT, NULL, NULL, "More info", NULL}
		};

	GtkActionGroup* sagroup = gtk_action_group_new ("SampleActionGroup");
	gtk_action_group_add_actions (sagroup, smentries, SMNUM_ENTRIES, NULL);
	GtkUIManager* uimanager = gtk_ui_manager_new ();
	gtk_ui_manager_insert_action_group (uimanager, sagroup, 0);
	gtk_ui_manager_add_ui_from_file (uimanager, "samplemenu.ui", NULL);
	GtkWidget* menubar = gtk_ui_manager_get_widget (uimanager, "/MenuBar");
	gtk_action_group_add_actions (sagroup,
	                              smentries,
	                              SMNUM_ENTRIES,
	                              NULL);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    menubar,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding



	// Set the labels on the left side.
	const gint TABLE_0_ROW = 5; // 1 header, 4 colors
	const gint TABLE_0_COL = 6;
	GtkWidget* table_0 = gtk_table_new (TABLE_0_ROW, TABLE_0_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_0,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	const gchar* rows_txt[TABLE_0_ROW] = { "", "fg", "bg", "text", "base" };

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		GtkWidget* label = gtk_label_new (rows_txt[i]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  0, 1,    // left, right
		                  i, i+1,  // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);   // x,y padding
	}

	// Set the labels on the top.
	const gchar* cols_txt[TABLE_0_COL] = {
		"", "NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	for (gint j=1; j<TABLE_0_COL; ++j)
	{
		GtkWidget* label = gtk_label_new (cols_txt[j]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
	}

	// Set the color buttons
	/* fg[NORMAL] = "#747474"  , also ACTIVE,PRELIGHT,SELECTED,INSENSITIVE
	   bg[NORMAL] = "#DCDAD5"  , idem
	   text[NORMAL] = "#000000", idem
	   base[NORMAL] = "#FFFFFF", idem
	 */
	GtkStyle* style = gtk_widget_get_style (app->window);

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		for (gint j=1; j<TABLE_0_COL; ++j)
		{
			GdkColor* clr;
			if (i == 1)      clr = &(style->fg[j-1]);
			else if (i == 2) clr = &(style->bg[j-1]);
			else if (i == 3) clr = &(style->text[j-1]);
			else if (i == 4) clr = &(style->base[j-1]);
			else exit(-1);
			app->widget_15_clrbn[i-1][j-1] =
				gtk_color_button_new_with_color (clr);
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_15_clrbn[i-1][j-1],
			                  j, j+1, // left, right
			                  i, i+1, // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);  // x,y padding
			g_signal_connect (G_OBJECT(app->widget_15_clrbn[i-1][j-1]),
			                  "color-set",
			                  G_CALLBACK(cb_color_set),
			                  NULL);
		}
	}


	// font_desc    font_name="FreeSans 11"
	GtkWidget* table_1 = gtk_table_new (5, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* font_desc_lbl = gtk_label_new ("font_desc");
	char* font_name = pango_font_description_to_string (style->font_desc);
	app->widget_15_fn_bn = gtk_font_button_new_with_font (font_name);
	g_free (font_name);
	gtk_table_attach (GTK_TABLE(table_1),
	                  font_desc_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_15_fn_bn,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_15_fn_bn),
	                  "font-set",
	                  G_CALLBACK(cb_font_set),
	                  NULL);

	// xthickness = 2
	GtkWidget* xthickness_lbl = gtk_label_new ("xthickness");
	app->widget_15_spinbn_xth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_15_spinbn_xth),
	                           (gdouble)style->xthickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  xthickness_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_15_spinbn_xth,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_15_spinbn_xth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// ythickness = 2
	GtkWidget* ythickness_lbl = gtk_label_new ("ythickness");
	app->widget_15_spinbn_yth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_15_spinbn_yth),
	                           (gdouble)style->ythickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  ythickness_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_15_spinbn_yth,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_15_spinbn_yth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);


	// "internal-padding" gint >=0 default=1
	GtkWidget* internalp_lbl = gtk_label_new ("internal-padding");
	app->widget_15_spinbn_internalp = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_15_spinbn_internalp),
	                           1);
	gtk_table_attach (GTK_TABLE(table_1),
	                  internalp_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_15_spinbn_internalp,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_15_spinbn_internalp),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "shadow-type" GtkShadowType default=GTK_SHADOW_OUT
	GtkWidget* shadowt_lbl = gtk_label_new ("shadow-type");
	app->widget_15_cbbox_shadowt = gtk_combo_box_text_new ();
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_15_cbbox_shadowt),
	                           "GTK_SHADOW_NONE");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_15_cbbox_shadowt),
	                           "GTK_SHADOW_IN");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_15_cbbox_shadowt),
	                           "GTK_SHADOW_OUT");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_15_cbbox_shadowt),
	                           "GTK_SHADOW_ETCHED_IN");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_15_cbbox_shadowt),
	                           "GTK_SHADOW_ETCHED_OUT");
    gtk_combo_box_set_active(GTK_COMBO_BOX(app->widget_15_cbbox_shadowt), 2);

	gtk_table_attach (GTK_TABLE(table_1),
	                  shadowt_lbl,
	                  0, 1,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_15_cbbox_shadowt,
	                  1, 2,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_15_cbbox_shadowt),
	                  "changed",
	                  G_CALLBACK(cb_cbbox_changed),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_15_style_txt = g_string_new ("#rc style for class GtkMenuBar");
}

void ui_update_gtkmenubar()
{
}

void ui_delete_gtkmenubar()
{
}

void ui_create_gtkmenuitem()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkMenuItem");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	//  GtkMenuItem sample, book cap.9 - menubars.cpp
	GtkAccelGroup* group = gtk_accel_group_new ();
	GtkWidget* menubar = gtk_menu_bar_new ();
	GtkWidget* file = gtk_menu_item_new_with_label ("File");
	GtkWidget* edit = gtk_menu_item_new_with_label ("Edit");
	GtkWidget* help = gtk_menu_item_new_with_label ("Help");

	GtkWidget* filemenu = gtk_menu_new ();
	GtkWidget* editmenu = gtk_menu_new ();
	GtkWidget* helpmenu = gtk_menu_new ();

	gtk_menu_item_set_submenu (GTK_MENU_ITEM(file), filemenu);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM(edit), editmenu);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM(help), helpmenu);

	gtk_menu_shell_append (GTK_MENU_SHELL(menubar), file);
	gtk_menu_shell_append (GTK_MENU_SHELL(menubar), edit);
	gtk_menu_shell_append (GTK_MENU_SHELL(menubar), help);

	GtkWidget* New = gtk_image_menu_item_new_from_stock (GTK_STOCK_NEW, group);
	GtkWidget* Open= gtk_image_menu_item_new_from_stock (GTK_STOCK_OPEN, group);
	gtk_menu_shell_append (GTK_MENU_SHELL(filemenu), New);
	gtk_menu_shell_append (GTK_MENU_SHELL(filemenu), Open);

	GtkWidget* Cut  = gtk_image_menu_item_new_from_stock (GTK_STOCK_CUT, group);
	GtkWidget* Copy = gtk_image_menu_item_new_from_stock (GTK_STOCK_COPY, group);
	GtkWidget* Paste= gtk_image_menu_item_new_from_stock (GTK_STOCK_PASTE, group);
	gtk_menu_shell_append (GTK_MENU_SHELL (editmenu), Cut);
	gtk_menu_shell_append (GTK_MENU_SHELL (editmenu), Copy);
	gtk_menu_shell_append (GTK_MENU_SHELL (editmenu), Paste);

	GtkWidget* contents = gtk_image_menu_item_new_from_stock (GTK_STOCK_HELP, group);
	GtkWidget* about = gtk_image_menu_item_new_from_stock (GTK_STOCK_ABOUT, group);
	gtk_menu_shell_append (GTK_MENU_SHELL (helpmenu), contents);
	gtk_menu_shell_append (GTK_MENU_SHELL (helpmenu), about);

	gtk_box_pack_start (GTK_BOX(vbox),
	                    menubar,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding




	// Set the labels on the left side.
	const gint TABLE_0_ROW = 5; // 1 header, 4 colors
	const gint TABLE_0_COL = 6;
	GtkWidget* table_0 = gtk_table_new (TABLE_0_ROW, TABLE_0_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_0,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	const gchar* rows_txt[TABLE_0_ROW] = { "", "fg", "bg", "text", "base" };

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		GtkWidget* label = gtk_label_new (rows_txt[i]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  0, 1,    // left, right
		                  i, i+1,  // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);   // x,y padding
	}

	// Set the labels on the top.
	const gchar* cols_txt[TABLE_0_COL] = {
		"", "NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	for (gint j=1; j<TABLE_0_COL; ++j)
	{
		GtkWidget* label = gtk_label_new (cols_txt[j]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
	}

	// Set the color buttons
	/* fg[NORMAL] = "#747474"  , also ACTIVE,PRELIGHT,SELECTED,INSENSITIVE
	   bg[NORMAL] = "#DCDAD5"  , idem
	   text[NORMAL] = "#000000", idem
	   base[NORMAL] = "#FFFFFF", idem
	 */
	GtkStyle* style = gtk_widget_get_style (app->window);

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		for (gint j=1; j<TABLE_0_COL; ++j)
		{
			GdkColor* clr;
			if (i == 1)      clr = &(style->fg[j-1]);
			else if (i == 2) clr = &(style->bg[j-1]);
			else if (i == 3) clr = &(style->text[j-1]);
			else if (i == 4) clr = &(style->base[j-1]);
			else exit(-1);
			app->widget_16_clrbn[i-1][j-1] =
				gtk_color_button_new_with_color (clr);
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_16_clrbn[i-1][j-1],
			                  j, j+1, // left, right
			                  i, i+1, // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);  // x,y padding
			g_signal_connect (G_OBJECT(app->widget_16_clrbn[i-1][j-1]),
			                  "color-set",
			                  G_CALLBACK(cb_color_set),
			                  NULL);
		}
	}


	// font_desc    font_name="FreeSans 11"
	GtkWidget* table_1 = gtk_table_new (9, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* font_desc_lbl = gtk_label_new ("font_desc");
	char* font_name = pango_font_description_to_string (style->font_desc);
	app->widget_16_fn_bn = gtk_font_button_new_with_font (font_name);
	g_free (font_name);
	gtk_table_attach (GTK_TABLE(table_1),
	                  font_desc_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_16_fn_bn,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_16_fn_bn),
	                  "font-set",
	                  G_CALLBACK(cb_font_set),
	                  NULL);

	// xthickness = 2
	GtkWidget* xthickness_lbl = gtk_label_new ("xthickness");
	app->widget_16_spinbn_xth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_16_spinbn_xth),
	                           (gdouble)style->xthickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  xthickness_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_16_spinbn_xth,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_16_spinbn_xth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// ythickness = 2
	GtkWidget* ythickness_lbl = gtk_label_new ("ythickness");
	app->widget_16_spinbn_yth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_16_spinbn_yth),
	                           (gdouble)style->ythickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  ythickness_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_16_spinbn_yth,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_16_spinbn_yth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "arrow-scaling" gfloat [0,2] default=0.8
	GtkWidget* arrowsc_lbl = gtk_label_new ("arrow-scaling");
	app->widget_16_spinbn_arrowsc = gtk_spin_button_new_with_range (0,2,0.1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_16_spinbn_arrowsc),
	                           0.8);
	gtk_table_attach (GTK_TABLE(table_1),
	                  arrowsc_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_16_spinbn_arrowsc,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_16_spinbn_arrowsc),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "arrow-spacing" gint >=0 default=10
	GtkWidget* arrowsp_lbl = gtk_label_new ("arrow-spacing");
	app->widget_16_spinbn_arrowsp = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_16_spinbn_arrowsp),
	                           10);
	gtk_table_attach (GTK_TABLE(table_1),
	                  arrowsp_lbl,
	                  0, 1,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_16_spinbn_arrowsp,
	                  1, 2,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_16_spinbn_arrowsp),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "horizontal-padding" gint >=0 default=3
	GtkWidget* horizontalpadd_lbl = gtk_label_new ("horizontal-padding");
	app->widget_16_spinbn_horizontalpadd = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_16_spinbn_horizontalpadd),
	                           3);
	gtk_table_attach (GTK_TABLE(table_1),
	                  horizontalpadd_lbl,
	                  0, 1,   // left, right
	                  5, 6,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_16_spinbn_horizontalpadd,
	                  1, 2,   // left, right
	                  5, 6,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_16_spinbn_horizontalpadd),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "selected-shadow-type" GtkShadowType default=GTK_SHADOW_NONE
	GtkWidget* selectedst_lbl = gtk_label_new ("selected-shadow-type");
	app->widget_16_cbbox_selectedst = gtk_combo_box_text_new ();
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_16_cbbox_selectedst),
	                           "GTK_SHADOW_NONE");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_16_cbbox_selectedst),
	                           "GTK_SHADOW_IN");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_16_cbbox_selectedst),
	                           "GTK_SHADOW_OUT");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_16_cbbox_selectedst),
	                           "GTK_SHADOW_ETCHED_IN");
	gtk_combo_box_append_text (GTK_COMBO_BOX(app->widget_16_cbbox_selectedst),
	                           "GTK_SHADOW_ETCHED_OUT");
    gtk_combo_box_set_active(GTK_COMBO_BOX(app->widget_16_cbbox_selectedst), 0);

	gtk_table_attach (GTK_TABLE(table_1),
	                  selectedst_lbl,
	                  0, 1,   // left, right
	                  6, 7,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_16_cbbox_selectedst,
	                  1, 2,   // left, right
	                  6, 7,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_16_cbbox_selectedst),
	                  "changed",
	                  G_CALLBACK(cb_cbbox_changed),
	                  NULL);

	// "toggle-spacing" gint >=0 default=5
	GtkWidget* togglesp_lbl = gtk_label_new ("toggle-spacing");
	app->widget_16_spinbn_togglesp = gtk_spin_button_new_with_range (0,50,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_16_spinbn_togglesp),
	                           5);
	gtk_table_attach (GTK_TABLE(table_1),
	                  togglesp_lbl,
	                  0, 1,   // left, right
	                  7, 8,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_16_spinbn_togglesp,
	                  1, 2,   // left, right
	                  7, 8,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_16_spinbn_togglesp),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "width-chars" gint >=0 default=12
	GtkWidget* widthc_lbl = gtk_label_new ("width-chars");
	app->widget_16_spinbn_widthc = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_16_spinbn_widthc),
	                           12);
	gtk_table_attach (GTK_TABLE(table_1),
	                  widthc_lbl,
	                  0, 1,   // left, right
	                  8, 9,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_16_spinbn_widthc,
	                  1, 2,   // left, right
	                  8, 9,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_16_spinbn_widthc),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_16_style_txt = g_string_new ("#rc style for class GtkMenuItem");
}

void ui_update_gtkmenuitem()
{
}

void ui_delete_gtkmenuitem()
{
}

void ui_create_gtkcheckmenuitem()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkCheckMenuItem");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	GtkWidget* menubar = gtk_menu_bar_new ();

	GtkWidget* cycle  = gtk_menu_item_new_with_label ("Cycling");
	GtkWidget* focus  = gtk_menu_item_new_with_label ("Focus");
	GtkWidget* access = gtk_menu_item_new_with_label ("Accessibility");

	GtkWidget* cyclemenu  = gtk_menu_new ();
	GtkWidget* focusmenu  = gtk_menu_new ();
	GtkWidget* accessmenu = gtk_menu_new ();

	gtk_menu_item_set_submenu (GTK_MENU_ITEM(cycle),  cyclemenu);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM(focus),  focusmenu);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM(access), accessmenu);

	gtk_menu_shell_append (GTK_MENU_SHELL(menubar), cycle);
	gtk_menu_shell_append (GTK_MENU_SHELL(menubar), focus);
	gtk_menu_shell_append (GTK_MENU_SHELL(menubar), access);

	GtkWidget* ihwin = gtk_check_menu_item_new_with_label (
                                      "Include hidden (i.e. iconified windows");
	GtkWidget* ctwoawork= gtk_check_menu_item_new_with_label (
                                     "Cycle through windows on all workspaces");
	GtkWidget* dfaswwcyc = gtk_check_menu_item_new_with_label (
                            "Draw frame around selected windows while cycling");

	gtk_menu_shell_append (GTK_MENU_SHELL(cyclemenu), ihwin);
	gtk_menu_shell_append (GTK_MENU_SHELL(cyclemenu), ctwoawork);
	gtk_menu_shell_append (GTK_MENU_SHELL(cyclemenu), dfaswwcyc);

	GtkWidget* afsprev  = gtk_check_menu_item_new_with_label (
                                          "Activate focus stealing prevention");
	GtkWidget* hsifhint = gtk_check_menu_item_new_with_label (
                                          "Honor standard ICCCM focus hint");

	gtk_menu_shell_append (GTK_MENU_SHELL (focusmenu), afsprev);
	gtk_menu_shell_append (GTK_MENU_SHELL (focusmenu), hsifhint);

	GtkWidget* bwocwork = gtk_radio_menu_item_new_with_label(NULL,
                                           "Brind window on current workspace");
	GtkWidget* stwwork = gtk_radio_menu_item_new_with_label_from_widget (
                                            GTK_RADIO_MENU_ITEM(bwocwork),
                                            "Switch to window's workspace");
	GtkWidget* dnot = gtk_radio_menu_item_new_with_label_from_widget (
                                            GTK_RADIO_MENU_ITEM(bwocwork),
                                            "Do nothing");

	gtk_check_menu_item_set_active  (GTK_CHECK_MENU_ITEM(bwocwork), TRUE);
	gtk_menu_shell_append (GTK_MENU_SHELL (focusmenu), bwocwork);
	gtk_menu_shell_append (GTK_MENU_SHELL (focusmenu), stwwork);
	gtk_menu_shell_append (GTK_MENU_SHELL (focusmenu), dnot);


	GtkWidget* rwwambipress = gtk_check_menu_item_new_with_label (
                              "Raise windows when any mouse button is pressed");
	GtkWidget* hfowwmax = gtk_check_menu_item_new_with_label (
                              "Hide frame of windows when maximized");
	gtk_menu_shell_append (GTK_MENU_SHELL (accessmenu), rwwambipress);
	gtk_menu_shell_append (GTK_MENU_SHELL (accessmenu), hfowwmax);

	gtk_box_pack_start (GTK_BOX(vbox),
	                    menubar,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	GtkWidget* table_1 = gtk_table_new (1, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	// "indicator-size" gint >=0 default=13
	GtkWidget* indicatorsz_lbl = gtk_label_new ("indicator-size");
	app->widget_17_spinbn_indicatorsz = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_17_spinbn_indicatorsz),
	                           13);
	gtk_table_attach (GTK_TABLE(table_1),
	                  indicatorsz_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_17_spinbn_indicatorsz,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_17_spinbn_indicatorsz),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_17_style_txt = g_string_new ("#rc style for class GtkCheckMenuItem");
}

void ui_update_gtkcheckmenuitem()
{
}

void ui_delete_gtkcheckmenuitem()
{
}

void ui_create_gtktextview()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkTextView");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	PangoFontDescription* fd = pango_font_description_from_string(
                                                           "Monospace Bold 10");
	GtkWidget* textview = gtk_text_view_new ();
	gtk_widget_modify_font (textview, fd);

	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW(textview), GTK_WRAP_WORD);
	gtk_text_view_set_justification (GTK_TEXT_VIEW(textview), GTK_JUSTIFY_RIGHT);

	gtk_text_view_set_editable (GTK_TEXT_VIEW(textview), TRUE);
	gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW(textview), TRUE);

	gtk_text_view_set_pixels_above_lines (GTK_TEXT_VIEW (textview), 5);
	gtk_text_view_set_pixels_below_lines (GTK_TEXT_VIEW (textview), 5);
	gtk_text_view_set_pixels_inside_wrap (GTK_TEXT_VIEW (textview), 5);

	gtk_text_view_set_left_margin (GTK_TEXT_VIEW(textview), 10);
	gtk_text_view_set_right_margin (GTK_TEXT_VIEW(textview), 10);

	GtkTextBuffer* buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textview));
	gtk_text_buffer_set_text (buffer, "This is some text!\nChange me!", -1);

	GtkWidget* scrolled_win = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled_win),
	                                GTK_POLICY_AUTOMATIC,
	                                GTK_POLICY_ALWAYS);

	gtk_container_add (GTK_CONTAINER(scrolled_win), textview);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    scrolled_win,
	                    TRUE,
	                    TRUE,
	                    0);



	// Set the labels on the left side.
	const gint TABLE_0_ROW = 5; // 1 header, 4 colors
	const gint TABLE_0_COL = 6;
	GtkWidget* table_0 = gtk_table_new (TABLE_0_ROW, TABLE_0_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_0,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	const gchar* rows_txt[TABLE_0_ROW] = { "", "fg", "bg", "text", "base" };

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		GtkWidget* label = gtk_label_new (rows_txt[i]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  0, 1,    // left, right
		                  i, i+1,  // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);   // x,y padding
	}

	// Set the labels on the top.
	const gchar* cols_txt[TABLE_0_COL] = {
		"", "NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	for (gint j=1; j<TABLE_0_COL; ++j)
	{
		GtkWidget* label = gtk_label_new (cols_txt[j]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
	}

	// Set the color buttons
	/* fg[NORMAL] = "#747474"  , also ACTIVE,PRELIGHT,SELECTED,INSENSITIVE
	   bg[NORMAL] = "#DCDAD5"  , idem
	   text[NORMAL] = "#000000", idem
	   base[NORMAL] = "#FFFFFF", idem
	 */
	GtkStyle* style = gtk_widget_get_style (app->window);

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		for (gint j=1; j<TABLE_0_COL; ++j)
		{
			GdkColor* clr;
			if (i == 1)      clr = &(style->fg[j-1]);
			else if (i == 2) clr = &(style->bg[j-1]);
			else if (i == 3) clr = &(style->text[j-1]);
			else if (i == 4) clr = &(style->base[j-1]);
			else exit(-1);
			app->widget_18_clrbn[i-1][j-1] =
				gtk_color_button_new_with_color (clr);
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_18_clrbn[i-1][j-1],
			                  j, j+1, // left, right
			                  i, i+1, // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);  // x,y padding
			g_signal_connect (G_OBJECT(app->widget_18_clrbn[i-1][j-1]),
			                  "color-set",
			                  G_CALLBACK(cb_color_set),
			                  NULL);
		}
	}


	// font_desc    font_name="FreeSans 11"
	GtkWidget* table_1 = gtk_table_new (4, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* font_desc_lbl = gtk_label_new ("font_desc");
	char* font_name = pango_font_description_to_string (style->font_desc);
	app->widget_18_fn_bn = gtk_font_button_new_with_font (font_name);
	g_free (font_name);
	gtk_table_attach (GTK_TABLE(table_1),
	                  font_desc_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_18_fn_bn,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_18_fn_bn),
	                  "font-set",
	                  G_CALLBACK(cb_font_set),
	                  NULL);

	// xthickness = 2
	GtkWidget* xthickness_lbl = gtk_label_new ("xthickness");
	app->widget_18_spinbn_xth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_18_spinbn_xth),
	                           (gdouble)style->xthickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  xthickness_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_18_spinbn_xth,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_18_spinbn_xth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// ythickness = 2
	GtkWidget* ythickness_lbl = gtk_label_new ("ythickness");
	app->widget_18_spinbn_yth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_18_spinbn_yth),
	                           (gdouble)style->ythickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  ythickness_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_18_spinbn_yth,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_18_spinbn_yth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);


	// "error-underline-color" GdkColor (didn't specify range & default)
	GtkWidget* errorundclr_lbl = gtk_label_new ("error-underline-color");
	gtk_table_attach (GTK_TABLE(table_1),
	                  errorundclr_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	GdkColor clr;
	gdk_color_parse ("#ff0000", &clr);
	app->widget_18_clrbn_errorundclr = gtk_color_button_new_with_color (&clr);
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_18_clrbn_errorundclr,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_18_clrbn_errorundclr),
	                  "color-set",
	                  G_CALLBACK(cb_color_set),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_18_style_txt = g_string_new ("#rc style for class GtkTextView");
}

void ui_update_gtktextview()
{
}

void ui_delete_gtktextview()
{
}

void ui_create_gtktreeview()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkTreeView");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	// Based on cap 8_tree_view_widget, sample- treestore.cpp
	GtkWidget* treeview = gtk_tree_view_new ();
	GtkCellRenderer* renderer = gtk_cell_renderer_text_new ();
	GtkTreeViewColumn* column = gtk_tree_view_column_new_with_attributes (
                                         "Title",  // *title
                                         renderer, // *cell
                                         "text",   // , ...
                                         0,        // column index
                                         NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW(treeview), column);

	GtkTreeStore* store = gtk_tree_store_new (1, G_TYPE_STRING);
	GtkTreeIter iter, child[3];
	gtk_tree_store_append (store, &iter, NULL);
	gtk_tree_store_set (store,    // store
	                    &iter,    // iterator
	                    0,        // column index
	                    "iter",   // value
	                    -1);      // -1 -> end

	gtk_tree_store_append (store, &child[0], &iter);
	gtk_tree_store_set (store,
	                    &child[0],
	                    0,
	                    "child[0]",
	                    -1);

	gtk_tree_store_append (store, &child[1], &child[0]);
	gtk_tree_store_set (store,
	                    &child[1],
	                    0,
	                    "child[1]",
	                    -1);

	gtk_tree_store_append (store, &child[2], &child[1]);
	gtk_tree_store_set (store,
	                    &child[2],
	                    0,
	                    "child[2]",
	                    -1);

	gtk_tree_view_set_model (GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
	gtk_tree_view_expand_all (GTK_TREE_VIEW(treeview));
 	g_object_unref (store);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    treeview,
	                    TRUE,    // expand
	                    TRUE,    // fill
	                    0);      // padding




	// Set the labels on the left side.
	const gint TABLE_0_ROW = 5; // 1 header, 4 colors
	const gint TABLE_0_COL = 6;
	GtkWidget* table_0 = gtk_table_new (TABLE_0_ROW, TABLE_0_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_0,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	const gchar* rows_txt[TABLE_0_ROW] = { "", "fg", "bg", "text", "base" };

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		GtkWidget* label = gtk_label_new (rows_txt[i]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  0, 1,    // left, right
		                  i, i+1,  // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);   // x,y padding
	}

	// Set the labels on the top.
	const gchar* cols_txt[TABLE_0_COL] = {
		"", "NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	for (gint j=1; j<TABLE_0_COL; ++j)
	{
		GtkWidget* label = gtk_label_new (cols_txt[j]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
	}

	// Set the color buttons
	/* fg[NORMAL] = "#747474"  , also ACTIVE,PRELIGHT,SELECTED,INSENSITIVE
	   bg[NORMAL] = "#DCDAD5"  , idem
	   text[NORMAL] = "#000000", idem
	   base[NORMAL] = "#FFFFFF", idem
	 */
	GtkStyle* style = gtk_widget_get_style (app->window);

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		for (gint j=1; j<TABLE_0_COL; ++j)
		{
			GdkColor* clr;
			if (i == 1)      clr = &(style->fg[j-1]);
			else if (i == 2) clr = &(style->bg[j-1]);
			else if (i == 3) clr = &(style->text[j-1]);
			else if (i == 4) clr = &(style->base[j-1]);
			else exit(-1);
			app->widget_19_clrbn[i-1][j-1] =
				gtk_color_button_new_with_color (clr);
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_19_clrbn[i-1][j-1],
			                  j, j+1, // left, right
			                  i, i+1, // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);  // x,y padding
			g_signal_connect (G_OBJECT(app->widget_19_clrbn[i-1][j-1]),
			                  "color-set",
			                  G_CALLBACK(cb_color_set),
			                  NULL);
		}
	}


	// font_desc    font_name="FreeSans 11"
	GtkWidget* table_1 = gtk_table_new (15, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* font_desc_lbl = gtk_label_new ("font_desc");
	char* font_name = pango_font_description_to_string (style->font_desc);
	app->widget_19_fn_bn = gtk_font_button_new_with_font (font_name);
	g_free (font_name);
	gtk_table_attach (GTK_TABLE(table_1),
	                  font_desc_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_19_fn_bn,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_19_fn_bn),
	                  "font-set",
	                  G_CALLBACK(cb_font_set),
	                  NULL);

	// xthickness = 2
	GtkWidget* xthickness_lbl = gtk_label_new ("xthickness");
	app->widget_19_spinbn_xth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_19_spinbn_xth),
	                           (gdouble)style->xthickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  xthickness_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_19_spinbn_xth,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_19_spinbn_xth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// ythickness = 2
	GtkWidget* ythickness_lbl = gtk_label_new ("ythickness");
	app->widget_19_spinbn_yth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_19_spinbn_yth),
	                           (gdouble)style->ythickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  ythickness_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_19_spinbn_yth,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_19_spinbn_yth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);



	// "allow-rules" gboolean default=TRUE
	GtkWidget* allowr_lbl = gtk_label_new ("allow-rules");
	gtk_table_attach (GTK_TABLE(table_1),
	                  allowr_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_19_chkbn_allowr = gtk_check_button_new ();
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(app->widget_19_chkbn_allowr),
	                              TRUE);
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_19_chkbn_allowr,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_19_chkbn_allowr),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// "even-row-color" GdkColor (didn't specify range & default) (clr even rows)
	GtkWidget* evenrowclr_lbl = gtk_label_new ("even-row-color");
	gtk_table_attach (GTK_TABLE(table_1),
	                  evenrowclr_lbl,
	                  0, 1,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	GdkColor evenclr;
	gdk_color_parse ("#dcdcdc", &evenclr);
	app->widget_19_clrbn_evenrowclr = gtk_color_button_new_with_color (&evenclr);
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_19_clrbn_evenrowclr,
	                  1, 2,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_19_clrbn_evenrowclr),
	                  "color-set",
	                  G_CALLBACK(cb_color_set),
	                  NULL);

	// "expander-size" gint >=0 default=12
	GtkWidget* expandersz_lbl = gtk_label_new ("expander-size");
	app->widget_19_spinbn_expandersz = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_19_spinbn_expandersz),
	                           12);
	gtk_table_attach (GTK_TABLE(table_1),
	                  expandersz_lbl,
	                  0, 1,   // left, right
	                  5, 6,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_19_spinbn_expandersz,
	                  1, 2,   // left, right
	                  5, 6,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_19_spinbn_expandersz),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "grid-line-pattern" gchar* (didn't specify) default="\001\001"
	GtkWidget* gridlnpatt_lbl = gtk_label_new ("grid-line-pattern");
	gtk_table_attach (GTK_TABLE(table_1),
	                  gridlnpatt_lbl,
	                  0, 1,   // left, right
	                  6, 7,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_19_entry_gridlnpatt = gtk_entry_new ();
	gtk_entry_set_text (GTK_ENTRY(app->widget_19_entry_gridlnpatt), "\\001\\001");
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_19_entry_gridlnpatt,
	                  1, 2,   // left, right
	                  6, 7,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_19_entry_gridlnpatt),
	                  "activate",
	                  G_CALLBACK(cb_entry_activate),
	                  NULL);

	// "grid-line-width" gint >=0 default=1
	GtkWidget* gridlw_lbl = gtk_label_new ("grid-line-width");
	app->widget_19_spinbn_gridlnw = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_19_spinbn_gridlnw),
	                           1);
	gtk_table_attach (GTK_TABLE(table_1),
	                  gridlw_lbl,
	                  0, 1,   // left, right
	                  7, 8,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_19_spinbn_gridlnw,
	                  1, 2,   // left, right
	                  7, 8,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_19_spinbn_gridlnw),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "horizontal-separator" gint >=0 default=2
	GtkWidget* horizontalsep_lbl = gtk_label_new ("horizontal-separator");
	app->widget_19_spinbn_horizontalsep = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_19_spinbn_horizontalsep),
	                           2);
	gtk_table_attach (GTK_TABLE(table_1),
	                  horizontalsep_lbl,
	                  0, 1,   // left, right
	                  8, 9,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_19_spinbn_horizontalsep,
	                  1, 2,   // left, right
	                  8, 9,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_19_spinbn_horizontalsep),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "indent-expanders" gboolean default=TRUE
	GtkWidget* indentexp_lbl = gtk_label_new ("indent-expanders");
	gtk_table_attach (GTK_TABLE(table_1),
	                  indentexp_lbl,
	                  0, 1,    // left, right
	                  9, 10,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	app->widget_19_chkbn_indentexp = gtk_check_button_new ();
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(app->widget_19_chkbn_indentexp),
	                              TRUE);
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_19_chkbn_indentexp,
	                  1, 2,    // left, right
	                  9, 10,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	g_signal_connect (G_OBJECT(app->widget_19_chkbn_indentexp),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// "odd-row-color" GdkColor (didn't specify range & default) (clr odd rows)
	GtkWidget* oddrowclr_lbl = gtk_label_new ("odd-row-color");
	gtk_table_attach (GTK_TABLE(table_1),
	                  oddrowclr_lbl,
	                  0, 1,     // left, right
	                  10, 11,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);    // x,y padding
	GdkColor oddclr;
	gdk_color_parse ("#ffffff", &oddclr);
	app->widget_19_clrbn_oddrowclr = gtk_color_button_new_with_color (&oddclr);
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_19_clrbn_oddrowclr,
	                  1, 2,     // left, right
	                  10, 11,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);    // x,y padding
	g_signal_connect (G_OBJECT(app->widget_19_clrbn_oddrowclr),
	                  "color-set",
	                  G_CALLBACK(cb_color_set),
	                  NULL);

	// "row-ending-details" gboolean default=FALSE (deprecated 2.22)
	GtkWidget* rowenddet_lbl = gtk_label_new ("row-ending-details");
	gtk_table_attach (GTK_TABLE(table_1),
	                  rowenddet_lbl,
	                  0, 1,     // left, right
	                  11, 12,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);    // x,y padding
	app->widget_19_chkbn_rowenddet = gtk_check_button_new ();

	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_19_chkbn_rowenddet,
	                  1, 2,     // left, right
	                  11, 12,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);    // x,y padding
	g_signal_connect (G_OBJECT(app->widget_19_chkbn_rowenddet),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// "tree-line-pattern" gchar* (didn't specify) default="\001\001"
	GtkWidget* treelnpatt_lbl = gtk_label_new ("tree-line-pattern");
	gtk_table_attach (GTK_TABLE(table_1),
	                  treelnpatt_lbl,
	                  0, 1,     // left, right
	                  12, 13,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);    // x,y padding
	app->widget_19_entry_treelnpatt = gtk_entry_new ();
	gtk_entry_set_text (GTK_ENTRY(app->widget_19_entry_treelnpatt), "\\001\\001");
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_19_entry_treelnpatt,
	                  1, 2,     // left, right
	                  12, 13,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);    // x,y padding
	g_signal_connect (G_OBJECT(app->widget_19_entry_treelnpatt),
	                  "activate",
	                  G_CALLBACK(cb_entry_activate),
	                  NULL);

	// "tree-line-width" gint >= 0 default=1
	GtkWidget* treelnw_lbl = gtk_label_new ("tree-line-width");
	app->widget_19_spinbn_treelnw = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_19_spinbn_treelnw),
	                           1);
	gtk_table_attach (GTK_TABLE(table_1),
	                  treelnw_lbl,
	                  0, 1,     // left, right
	                  13, 14,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);    // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_19_spinbn_treelnw,
	                  1, 2,   // left, right
	                  13, 14,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_19_spinbn_treelnw),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "vertical-separator" gint >= 0 default=2
	GtkWidget* verticalsep_lbl = gtk_label_new ("vertical-separator");
	app->widget_19_spinbn_verticalsep = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_19_spinbn_verticalsep),
	                           2);
	gtk_table_attach (GTK_TABLE(table_1),
	                  verticalsep_lbl,
	                  0, 1,     // left, right
	                  14, 15,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);    // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_19_spinbn_verticalsep,
	                  1, 2,     // left, right
	                  14, 15,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);    // x,y padding
	g_signal_connect (G_OBJECT(app->widget_19_spinbn_verticalsep),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_19_style_txt = g_string_new ("#rc style for class GtkTreeView");
}

void ui_update_gtktreeview()
{
}

void ui_delete_gtktreeview()
{
}

void ui_create_gtkiconview()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkIconView");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	// Based on example from:
	// https://developer.gnome.org/gtk2/unstable/gtk-migrating-GtkIconView.html

	GtkWidget* iconview = gtk_icon_view_new ();
	GtkListStore* store = gtk_list_store_new (2,                // no of col.
	                                          GDK_TYPE_PIXBUF,  // , ...
	                                          G_TYPE_STRING);

	gtk_icon_view_set_pixbuf_column (GTK_ICON_VIEW (iconview), 0);
	gtk_icon_view_set_text_column (GTK_ICON_VIEW (iconview), 1);
	gtk_icon_view_set_model (GTK_ICON_VIEW (iconview), GTK_TREE_MODEL (store));

	GtkTreeIter iter;
	GdkPixbuf *pixbuf;

	// for iconview1.png -> iconview4.png repeat these from below.
	for (gint i = 1; i < 5; ++i)
	{
		gchar iconpath[100], iconname[100];
		sprintf(iconpath, "iconview%d.png", i);
		sprintf(iconname, "iconview%d.png", i);

		gtk_list_store_append (store, &iter);
		pixbuf = gdk_pixbuf_new_from_file (iconpath, NULL);
		gtk_list_store_set (store,    // store
		                    &iter,    // iterator
		                    0,        // column
		                    pixbuf,   // value
		                    1,        // column
		                    iconname, // value
		                    -1);      // -1 -> end
		g_object_unref (pixbuf);
	}

	gtk_box_pack_start (GTK_BOX(vbox),
	                    iconview,
	                    TRUE,   // expand
	                    TRUE,   // fill
	                    0);      // padding




	// Set the labels on the left side.
	const gint TABLE_0_ROW = 5; // 1 header, 4 colors
	const gint TABLE_0_COL = 6;
	GtkWidget* table_0 = gtk_table_new (TABLE_0_ROW, TABLE_0_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_0,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	const gchar* rows_txt[TABLE_0_ROW] = { "", "fg", "bg", "text", "base" };

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		GtkWidget* label = gtk_label_new (rows_txt[i]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  0, 1,    // left, right
		                  i, i+1,  // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);   // x,y padding
	}

	// Set the labels on the top.
	const gchar* cols_txt[TABLE_0_COL] = {
		"", "NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	for (gint j=1; j<TABLE_0_COL; ++j)
	{
		GtkWidget* label = gtk_label_new (cols_txt[j]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
	}

	// Set the color buttons
	/* fg[NORMAL] = "#747474"  , also ACTIVE,PRELIGHT,SELECTED,INSENSITIVE
	   bg[NORMAL] = "#DCDAD5"  , idem
	   text[NORMAL] = "#000000", idem
	   base[NORMAL] = "#FFFFFF", idem
	 */
	GtkStyle* style = gtk_widget_get_style (app->window);

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		for (gint j=1; j<TABLE_0_COL; ++j)
		{
			GdkColor* clr;
			if (i == 1)      clr = &(style->fg[j-1]);
			else if (i == 2) clr = &(style->bg[j-1]);
			else if (i == 3) clr = &(style->text[j-1]);
			else if (i == 4) clr = &(style->base[j-1]);
			else exit(-1);
			app->widget_20_clrbn[i-1][j-1] =
				gtk_color_button_new_with_color (clr);
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_20_clrbn[i-1][j-1],
			                  j, j+1, // left, right
			                  i, i+1, // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);  // x,y padding
			g_signal_connect (G_OBJECT(app->widget_20_clrbn[i-1][j-1]),
			                  "color-set",
			                  G_CALLBACK(cb_color_set),
			                  NULL);
		}
	}


	// font_desc    font_name="FreeSans 11"
	GtkWidget* table_1 = gtk_table_new (5, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* font_desc_lbl = gtk_label_new ("font_desc");
	char* font_name = pango_font_description_to_string (style->font_desc);
	app->widget_20_fn_bn = gtk_font_button_new_with_font (font_name);
	g_free (font_name);
	gtk_table_attach (GTK_TABLE(table_1),
	                  font_desc_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_20_fn_bn,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_20_fn_bn),
	                  "font-set",
	                  G_CALLBACK(cb_font_set),
	                  NULL);

	// xthickness = 2
	GtkWidget* xthickness_lbl = gtk_label_new ("xthickness");
	app->widget_20_spinbn_xth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_20_spinbn_xth),
	                           (gdouble)style->xthickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  xthickness_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_20_spinbn_xth,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_20_spinbn_xth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// ythickness = 2
	GtkWidget* ythickness_lbl = gtk_label_new ("ythickness");
	app->widget_20_spinbn_yth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_20_spinbn_yth),
	                           (gdouble)style->ythickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  ythickness_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_20_spinbn_yth,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_20_spinbn_yth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);



	// "selection-box-alpha" guchar (didn't specify) default=64 (opacity of sel box)
	GtkWidget* selectionboxa_lbl = gtk_label_new ("selection-box-alpha");
	app->widget_20_spinbn_selectionboxa = gtk_spin_button_new_with_range (0,255,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_20_spinbn_selectionboxa),
	                           64);
	gtk_table_attach (GTK_TABLE(table_1),
	                  selectionboxa_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_20_spinbn_selectionboxa,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_20_spinbn_selectionboxa),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "selection-box-color" GdkColor (didn't specify default)
	GtkWidget* selectionboxclr_lbl = gtk_label_new ("selection-box-color");
	gtk_table_attach (GTK_TABLE(table_1),
	                  selectionboxclr_lbl,
	                  0, 1,     // left, right
	                  4, 5,     // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);    // x,y padding
	GdkColor clr;
	gdk_color_parse ("#cdcdcd", &clr);
	app->widget_20_clrbn_selectionboxclr = gtk_color_button_new_with_color (&clr);
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_20_clrbn_selectionboxclr,
	                  1, 2,     // left, right
	                  4, 5,     // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);    // x,y padding
	g_signal_connect (G_OBJECT(app->widget_20_clrbn_selectionboxclr),
	                  "color-set",
	                  G_CALLBACK(cb_color_set),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_20_style_txt = g_string_new ("#rc style for class GtkIconView");
}

void ui_update_gtkiconview()
{
}

void ui_delete_gtkiconview()
{
}


void assistant_apply(GtkAssistant*, gpointer){ printf("clicked Apply\n"); }
void assistant_cancel(GtkAssistant*, gpointer){ printf("clicked Cancel\n"); }
void assistant_close(GtkAssistant*, gpointer) { printf("clicked Close\n"); }
void assistant_destroy() { printf("called Destroy\n"); }
void assistant_expander_activate (GtkExpander* ex, gpointer data)
{
	if (gtk_expander_get_expanded(ex) == FALSE)
		gtk_widget_show_all (GTK_WIDGET(data));
	else
		gtk_widget_hide (GTK_WIDGET(data));
}

void ui_create_gtkassistant()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkAssistant");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	/*  Based on 05_dialogs, sample - assistant2.cpp and assistant.cpp
	    GtkAssistant asserts & closes when the dialog is not standalone but
	    has a parent (i.e. packed in vbox).
	    The solution is to leave the assistant as a separate window for now.
	*/

	GtkWidget* assistant = gtk_assistant_new ();
	gtk_widget_set_size_request (assistant, 400, 300);
	gtk_window_set_title (GTK_WINDOW(assistant), "GtkAssistant sample");
	g_signal_connect (G_OBJECT(assistant), "destroy", G_CALLBACK(assistant_destroy), 0);
	g_signal_connect (G_OBJECT(assistant), "apply",   G_CALLBACK(assistant_apply), 0);
	g_signal_connect (G_OBJECT(assistant), "cancel",  G_CALLBACK(assistant_cancel), 0);
	g_signal_connect (G_OBJECT(assistant), "close",   G_CALLBACK(assistant_close), 0);

	GtkWidget* label = gtk_label_new ("Gtk label");
	gtk_assistant_append_page (GTK_ASSISTANT(assistant), label);
	gtk_assistant_set_page_title (GTK_ASSISTANT(assistant), label, "Page title");
	gtk_assistant_set_page_type (GTK_ASSISTANT(assistant), label, GTK_ASSISTANT_PAGE_CONFIRM);
	gtk_assistant_set_page_complete (GTK_ASSISTANT(assistant), label, TRUE);

	g_signal_connect (G_OBJECT(expander), "activate",
	                  G_CALLBACK(assistant_expander_activate),
	                  (gpointer)assistant);




	// Set the labels on the left side.
	const gint TABLE_0_ROW = 5; // 1 header, 4 colors
	const gint TABLE_0_COL = 6;
	GtkWidget* table_0 = gtk_table_new (TABLE_0_ROW, TABLE_0_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_0,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	const gchar* rows_txt[TABLE_0_ROW] = { "", "fg", "bg", "text", "base" };

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		GtkWidget* label = gtk_label_new (rows_txt[i]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  0, 1,    // left, right
		                  i, i+1,  // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);   // x,y padding
	}

	// Set the labels on the top.
	const gchar* cols_txt[TABLE_0_COL] = {
		"", "NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	for (gint j=1; j<TABLE_0_COL; ++j)
	{
		GtkWidget* label = gtk_label_new (cols_txt[j]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
	}

	// Set the color buttons
	/* fg[NORMAL] = "#747474"  , also ACTIVE,PRELIGHT,SELECTED,INSENSITIVE
	   bg[NORMAL] = "#DCDAD5"  , idem
	   text[NORMAL] = "#000000", idem
	   base[NORMAL] = "#FFFFFF", idem
	 */
	GtkStyle* style = gtk_widget_get_style (app->window);

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		for (gint j=1; j<TABLE_0_COL; ++j)
		{
			GdkColor* clr;
			if (i == 1)      clr = &(style->fg[j-1]);
			else if (i == 2) clr = &(style->bg[j-1]);
			else if (i == 3) clr = &(style->text[j-1]);
			else if (i == 4) clr = &(style->base[j-1]);
			else exit(-1);
			app->widget_21_clrbn[i-1][j-1] =
				gtk_color_button_new_with_color (clr);
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_21_clrbn[i-1][j-1],
			                  j, j+1, // left, right
			                  i, i+1, // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);  // x,y padding
			g_signal_connect (G_OBJECT(app->widget_21_clrbn[i-1][j-1]),
			                  "color-set",
			                  G_CALLBACK(cb_color_set),
			                  NULL);
		}
	}


	// font_desc    font_name="FreeSans 11"
	GtkWidget* table_1 = gtk_table_new (5, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* font_desc_lbl = gtk_label_new ("font_desc");
	char* font_name = pango_font_description_to_string (style->font_desc);
	app->widget_21_fn_bn = gtk_font_button_new_with_font (font_name);
	g_free (font_name);
	gtk_table_attach (GTK_TABLE(table_1),
	                  font_desc_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_21_fn_bn,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_21_fn_bn),
	                  "font-set",
	                  G_CALLBACK(cb_font_set),
	                  NULL);

	// xthickness = 2
	GtkWidget* xthickness_lbl = gtk_label_new ("xthickness");
	app->widget_21_spinbn_xth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_21_spinbn_xth),
	                           (gdouble)style->xthickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  xthickness_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_21_spinbn_xth,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_21_spinbn_xth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// ythickness = 2
	GtkWidget* ythickness_lbl = gtk_label_new ("ythickness");
	app->widget_21_spinbn_yth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_21_spinbn_yth),
	                           (gdouble)style->ythickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  ythickness_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_21_spinbn_yth,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_21_spinbn_yth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);


	// "content-padding" gint >= 0 default=1
	GtkWidget* contentpadd_lbl = gtk_label_new ("content-padding");
	app->widget_21_spinbn_contentpadd = gtk_spin_button_new_with_range (0,20,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_21_spinbn_contentpadd),
	                           1);
	gtk_table_attach (GTK_TABLE(table_1),
	                  contentpadd_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_21_spinbn_contentpadd,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_21_spinbn_contentpadd),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "header-padding" gint >= 0 default=6
	GtkWidget* headerpadd_lbl = gtk_label_new ("header-padding");
	app->widget_21_spinbn_headerpadd = gtk_spin_button_new_with_range (0,20,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_21_spinbn_headerpadd),
	                           6);
	gtk_table_attach (GTK_TABLE(table_1),
	                  headerpadd_lbl,
	                  0, 1,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_21_spinbn_headerpadd,
	                  1, 2,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_21_spinbn_headerpadd),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_21_style_txt = g_string_new ("#rc style for class GtkAssistant");
}

void ui_update_gtkassistant()
{
}

void ui_delete_gtkassistant()
{
}


/* Return FALSE to destroy the widget.
   Return TRUE to cancel a delete-event. This can be used to confirm
   quitting the application. */
gboolean dialog_delete_event (GtkWidget*, GdkEvent*, gpointer)
{
	printf("delete-event\n");
	return TRUE;
}

void dialog_expander_activate (GtkExpander* ex, gpointer data)
{
	if (gtk_expander_get_expanded(ex) == FALSE)
		gtk_widget_show_all (GTK_WIDGET(data));
	else
		gtk_widget_hide (GTK_WIDGET(data));
}

void ui_create_gtkdialog()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkDialog");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	/*
	  This modeless dialog sample is written from scratch based on gnome.org.
	  When setting a parent on the dialog the program closes with assertion:
	  Gtk-WARNING **: Can't set a parent on a toplevel widget!
	 */
	GtkWidget* dialog   = gtk_dialog_new ();
	gtk_window_set_title (GTK_WINDOW(dialog), "GtkDialog sample");
	gtk_widget_set_size_request (dialog, 300, 150);
	gtk_dialog_add_button (GTK_DIALOG(dialog), " OK ", 11000);
	gtk_dialog_add_button (GTK_DIALOG(dialog), " Cancel ", 11001);

	GtkWidget* hbox = gtk_dialog_get_action_area (GTK_DIALOG(dialog));
	GtkWidget* rndbn = gtk_button_new_with_label("h-boxed");
	gtk_box_pack_start (GTK_BOX(hbox), rndbn, FALSE, FALSE, 0);

	GtkWidget* vbox2 = gtk_dialog_get_content_area (GTK_DIALOG(dialog));
	GtkWidget* label = gtk_label_new ("sample label\non 2 rows");
	gtk_box_pack_start (GTK_BOX(vbox2), label, FALSE, FALSE, 0);

	gtk_window_set_modal (GTK_WINDOW(dialog), FALSE);
	g_signal_connect (G_OBJECT(dialog),
	                  "delete-event",
	                  G_CALLBACK(dialog_delete_event),
	                  0);

	g_signal_connect (G_OBJECT(expander), "activate",
	                  G_CALLBACK(dialog_expander_activate),
	                  (gpointer)dialog);




	// Set the labels on the left side.
	const gint TABLE_0_ROW = 5; // 1 header, 4 colors
	const gint TABLE_0_COL = 6;
	GtkWidget* table_0 = gtk_table_new (TABLE_0_ROW, TABLE_0_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_0,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	const gchar* rows_txt[TABLE_0_ROW] = { "", "fg", "bg", "text", "base" };

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		GtkWidget* label = gtk_label_new (rows_txt[i]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  0, 1,    // left, right
		                  i, i+1,  // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);   // x,y padding
	}

	// Set the labels on the top.
	const gchar* cols_txt[TABLE_0_COL] = {
		"", "NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	for (gint j=1; j<TABLE_0_COL; ++j)
	{
		GtkWidget* label = gtk_label_new (cols_txt[j]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
	}

	// Set the color buttons
	/* fg[NORMAL] = "#747474"  , also ACTIVE,PRELIGHT,SELECTED,INSENSITIVE
	   bg[NORMAL] = "#DCDAD5"  , idem
	   text[NORMAL] = "#000000", idem
	   base[NORMAL] = "#FFFFFF", idem
	 */
	GtkStyle* style = gtk_widget_get_style (app->window);

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		for (gint j=1; j<TABLE_0_COL; ++j)
		{
			GdkColor* clr;
			if (i == 1)      clr = &(style->fg[j-1]);
			else if (i == 2) clr = &(style->bg[j-1]);
			else if (i == 3) clr = &(style->text[j-1]);
			else if (i == 4) clr = &(style->base[j-1]);
			else exit(-1);
			app->widget_22_clrbn[i-1][j-1] =
				gtk_color_button_new_with_color (clr);
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_22_clrbn[i-1][j-1],
			                  j, j+1, // left, right
			                  i, i+1, // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);  // x,y padding
			g_signal_connect (G_OBJECT(app->widget_22_clrbn[i-1][j-1]),
			                  "color-set",
			                  G_CALLBACK(cb_color_set),
			                  NULL);
		}
	}


	// font_desc    font_name="FreeSans 11"
	GtkWidget* table_1 = gtk_table_new (7, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* font_desc_lbl = gtk_label_new ("font_desc");
	char* font_name = pango_font_description_to_string (style->font_desc);
	app->widget_22_fn_bn = gtk_font_button_new_with_font (font_name);
	g_free (font_name);
	gtk_table_attach (GTK_TABLE(table_1),
	                  font_desc_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_22_fn_bn,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_22_fn_bn),
	                  "font-set",
	                  G_CALLBACK(cb_font_set),
	                  NULL);

	// xthickness = 2
	GtkWidget* xthickness_lbl = gtk_label_new ("xthickness");
	app->widget_22_spinbn_xth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_22_spinbn_xth),
	                           (gdouble)style->xthickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  xthickness_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_22_spinbn_xth,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_22_spinbn_xth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// ythickness = 2
	GtkWidget* ythickness_lbl = gtk_label_new ("ythickness");
	app->widget_22_spinbn_yth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_22_spinbn_yth),
	                           (gdouble)style->ythickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  ythickness_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_22_spinbn_yth,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_22_spinbn_yth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);


	// "action-area-border" gint >= 0 default=5
	GtkWidget* actionab_lbl = gtk_label_new ("action-area-border");
	app->widget_22_spinbn_actionab = gtk_spin_button_new_with_range (0,20,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_22_spinbn_actionab),
	                           5);
	gtk_table_attach (GTK_TABLE(table_1),
	                  actionab_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_22_spinbn_actionab,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_22_spinbn_actionab),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "button-spacing" gint >= 0 default=6
	GtkWidget* buttonsp_lbl = gtk_label_new ("button-spacing");
	app->widget_22_spinbn_buttonsp = gtk_spin_button_new_with_range (0,20,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_22_spinbn_buttonsp),
	                           6);
	gtk_table_attach (GTK_TABLE(table_1),
	                  buttonsp_lbl,
	                  0, 1,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_22_spinbn_buttonsp,
	                  1, 2,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_22_spinbn_buttonsp),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "content-area-border" gint >= 0 default=2
	GtkWidget* contentab_lbl = gtk_label_new ("content-area-border");
	app->widget_22_spinbn_contentab = gtk_spin_button_new_with_range (0,20,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_22_spinbn_contentab),
	                           2);
	gtk_table_attach (GTK_TABLE(table_1),
	                  contentab_lbl,
	                  0, 1,   // left, right
	                  5, 6,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_22_spinbn_contentab,
	                  1, 2,   // left, right
	                  5, 6,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_22_spinbn_contentab),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "content-area-spacing" gint >= 0 default=0
	GtkWidget* contentas_lbl = gtk_label_new ("content-area-spacing");
	app->widget_22_spinbn_contentas = gtk_spin_button_new_with_range (0,20,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_22_spinbn_contentas),
	                           0);
	gtk_table_attach (GTK_TABLE(table_1),
	                  contentas_lbl,
	                  0, 1,   // left, right
	                  6, 7,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_22_spinbn_contentas,
	                  1, 2,   // left, right
	                  6, 7,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_22_spinbn_contentas),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_22_style_txt = g_string_new ("#rc style for class GtkDialog");
}

void ui_update_gtkdialog()
{
}

void ui_delete_gtkdialog()
{
}


/* Return FALSE to destroy the widget.
   Return TRUE to cancel a delete-event. This can be used to confirm
   quitting the application. */
gboolean msgdialog_delete_event (GtkWidget*, GdkEvent*, gpointer)
{
	printf("delete-event\n");
	return TRUE;
}

void msgdialog_expander_activate (GtkExpander* ex, gpointer data)
{
	if (gtk_expander_get_expanded(ex) == FALSE)
		gtk_widget_show_all (GTK_WIDGET(data));
	else
		gtk_widget_hide (GTK_WIDGET(data));
}

void ui_create_gtkmessagedialog()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkMessageDialog");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	/*
	  This modeless message dialog sample is based on gnome.org
	  Didn't bother to try setting a parent on GtkMessageDialog.
	  Most probably will assert, so followed the above dialog sample.
	 */
	GtkWidget* msgdialog = gtk_message_dialog_new (
                               GTK_WINDOW(app->window), // parent
                               GTK_DIALOG_DESTROY_WITH_PARENT,
                               GTK_MESSAGE_INFO,
                               GTK_BUTTONS_OK_CANCEL,
                               "Sample message\n"
                               "on 2 rows."
                               );
	gtk_window_set_title (GTK_WINDOW(msgdialog), "GtkMessageDialog sample");
	gtk_widget_set_size_request (msgdialog, 300, 150);

	gtk_window_set_modal (GTK_WINDOW(msgdialog), FALSE);
	g_signal_connect (G_OBJECT(msgdialog),
	                  "delete-event",
	                  G_CALLBACK(msgdialog_delete_event),
	                  0);

	g_signal_connect (G_OBJECT(expander), "activate",
	                  G_CALLBACK(msgdialog_expander_activate),
	                  (gpointer)msgdialog);





	// Set the labels on the left side.
	const gint TABLE_0_ROW = 5; // 1 header, 4 colors
	const gint TABLE_0_COL = 6;
	GtkWidget* table_0 = gtk_table_new (TABLE_0_ROW, TABLE_0_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_0,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	const gchar* rows_txt[TABLE_0_ROW] = { "", "fg", "bg", "text", "base" };

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		GtkWidget* label = gtk_label_new (rows_txt[i]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  0, 1,    // left, right
		                  i, i+1,  // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);   // x,y padding
	}

	// Set the labels on the top.
	const gchar* cols_txt[TABLE_0_COL] = {
		"", "NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	for (gint j=1; j<TABLE_0_COL; ++j)
	{
		GtkWidget* label = gtk_label_new (cols_txt[j]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
	}

	// Set the color buttons
	/* fg[NORMAL] = "#747474"  , also ACTIVE,PRELIGHT,SELECTED,INSENSITIVE
	   bg[NORMAL] = "#DCDAD5"  , idem
	   text[NORMAL] = "#000000", idem
	   base[NORMAL] = "#FFFFFF", idem
	 */
	GtkStyle* style = gtk_widget_get_style (app->window);

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		for (gint j=1; j<TABLE_0_COL; ++j)
		{
			GdkColor* clr;
			if (i == 1)      clr = &(style->fg[j-1]);
			else if (i == 2) clr = &(style->bg[j-1]);
			else if (i == 3) clr = &(style->text[j-1]);
			else if (i == 4) clr = &(style->base[j-1]);
			else exit(-1);
			app->widget_23_clrbn[i-1][j-1] =
				gtk_color_button_new_with_color (clr);
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_23_clrbn[i-1][j-1],
			                  j, j+1, // left, right
			                  i, i+1, // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);  // x,y padding
			g_signal_connect (G_OBJECT(app->widget_23_clrbn[i-1][j-1]),
			                  "color-set",
			                  G_CALLBACK(cb_color_set),
			                  NULL);
		}
	}


	// font_desc    font_name="FreeSans 11"
	GtkWidget* table_1 = gtk_table_new (5, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* font_desc_lbl = gtk_label_new ("font_desc");
	char* font_name = pango_font_description_to_string (style->font_desc);
	app->widget_23_fn_bn = gtk_font_button_new_with_font (font_name);
	g_free (font_name);
	gtk_table_attach (GTK_TABLE(table_1),
	                  font_desc_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_23_fn_bn,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_23_fn_bn),
	                  "font-set",
	                  G_CALLBACK(cb_font_set),
	                  NULL);

	// xthickness = 2
	GtkWidget* xthickness_lbl = gtk_label_new ("xthickness");
	app->widget_23_spinbn_xth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_23_spinbn_xth),
	                           (gdouble)style->xthickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  xthickness_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_23_spinbn_xth,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_23_spinbn_xth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// ythickness = 2
	GtkWidget* ythickness_lbl = gtk_label_new ("ythickness");
	app->widget_23_spinbn_yth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_23_spinbn_yth),
	                           (gdouble)style->ythickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  ythickness_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_23_spinbn_yth,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_23_spinbn_yth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);


	// "message-border" gint >= 0 default=12
	GtkWidget* mesageb_lbl = gtk_label_new ("message-border");
	app->widget_23_spinbn_messageb = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_23_spinbn_messageb),
	                           12);
	gtk_table_attach (GTK_TABLE(table_1),
	                  mesageb_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_23_spinbn_messageb,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_23_spinbn_messageb),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "use-separator" gboolean default=FALSE , deprecated in 2.22
	GtkWidget* usesep_lbl = gtk_label_new ("use-separator");
	gtk_table_attach (GTK_TABLE(table_1),
	                  usesep_lbl,
	                  0, 1,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_23_chkbn_usesep = gtk_check_button_new ();

	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_23_chkbn_usesep,
	                  1, 2,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_23_chkbn_usesep),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_23_style_txt = g_string_new ("#rc style for class GtkMessageDialog");
}

void ui_update_gtkmessagedialog()
{
}

void ui_delete_gtkmessagedialog()
{
}

void ui_create_gtknotebook()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkNotebook");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	/*
	  GtkNotebook sample is based on 03_containers - notebooks.cpp
	 */
	GtkWidget* notebook = gtk_notebook_new ();
	GtkWidget* label1 = gtk_label_new ("Page One");
	GtkWidget* label2 = gtk_label_new ("Page Two");
	GtkWidget* child1 = gtk_label_new ("Go to page 2 to find the answer.");
	GtkWidget* child2 = gtk_label_new ("Go to page 1 to find the answer.");

	gtk_notebook_append_page (GTK_NOTEBOOK(notebook), child1, label1);
	gtk_notebook_append_page (GTK_NOTEBOOK(notebook), child2, label2);
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK(notebook), GTK_POS_BOTTOM);

	gtk_box_pack_start (GTK_BOX(vbox),
	                    notebook,
	                    TRUE,   // expand
	                    TRUE,   // fill
	                    0);     // padding




	// Set the labels on the left side.
	const gint TABLE_0_ROW = 5; // 1 header, 4 colors
	const gint TABLE_0_COL = 6;
	GtkWidget* table_0 = gtk_table_new (TABLE_0_ROW, TABLE_0_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_0,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	const gchar* rows_txt[TABLE_0_ROW] = { "", "fg", "bg", "text", "base" };

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		GtkWidget* label = gtk_label_new (rows_txt[i]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  0, 1,    // left, right
		                  i, i+1,  // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);   // x,y padding
	}

	// Set the labels on the top.
	const gchar* cols_txt[TABLE_0_COL] = {
		"", "NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	for (gint j=1; j<TABLE_0_COL; ++j)
	{
		GtkWidget* label = gtk_label_new (cols_txt[j]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
	}

	// Set the color buttons
	/* fg[NORMAL] = "#747474"  , also ACTIVE,PRELIGHT,SELECTED,INSENSITIVE
	   bg[NORMAL] = "#DCDAD5"  , idem
	   text[NORMAL] = "#000000", idem
	   base[NORMAL] = "#FFFFFF", idem
	 */
	GtkStyle* style = gtk_widget_get_style (app->window);

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		for (gint j=1; j<TABLE_0_COL; ++j)
		{
			GdkColor* clr;
			if (i == 1)      clr = &(style->fg[j-1]);
			else if (i == 2) clr = &(style->bg[j-1]);
			else if (i == 3) clr = &(style->text[j-1]);
			else if (i == 4) clr = &(style->base[j-1]);
			else exit(-1);
			app->widget_24_clrbn[i-1][j-1] =
				gtk_color_button_new_with_color (clr);
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_24_clrbn[i-1][j-1],
			                  j, j+1, // left, right
			                  i, i+1, // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);  // x,y padding
			g_signal_connect (G_OBJECT(app->widget_24_clrbn[i-1][j-1]),
			                  "color-set",
			                  G_CALLBACK(cb_color_set),
			                  NULL);
		}
	}


	// font_desc    font_name="FreeSans 11"
	GtkWidget* table_1 = gtk_table_new (10, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* font_desc_lbl = gtk_label_new ("font_desc");
	char* font_name = pango_font_description_to_string (style->font_desc);
	app->widget_24_fn_bn = gtk_font_button_new_with_font (font_name);
	g_free (font_name);
	gtk_table_attach (GTK_TABLE(table_1),
	                  font_desc_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_24_fn_bn,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_24_fn_bn),
	                  "font-set",
	                  G_CALLBACK(cb_font_set),
	                  NULL);

	// xthickness = 2
	GtkWidget* xthickness_lbl = gtk_label_new ("xthickness");
	app->widget_24_spinbn_xth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_24_spinbn_xth),
	                           (gdouble)style->xthickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  xthickness_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_24_spinbn_xth,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_24_spinbn_xth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// ythickness = 2
	GtkWidget* ythickness_lbl = gtk_label_new ("ythickness");
	app->widget_24_spinbn_yth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_24_spinbn_yth),
	                           (gdouble)style->ythickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  ythickness_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_24_spinbn_yth,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_24_spinbn_yth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "arrow-spacing" gint >= 0 default=0
	GtkWidget* arrowsp_lbl = gtk_label_new ("arrow-spacing");
	app->widget_24_spinbn_arrowsp = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_24_spinbn_arrowsp),
	                           0);
	gtk_table_attach (GTK_TABLE(table_1),
	                  arrowsp_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_24_spinbn_arrowsp,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_24_spinbn_arrowsp),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "has-backward-stepper" gboolean default=TRUE
	GtkWidget* hasbs_lbl = gtk_label_new ("has-backward-stepper");
	gtk_table_attach (GTK_TABLE(table_1),
	                  hasbs_lbl,
	                  0, 1,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_24_chkbn_hasbs = gtk_check_button_new ();
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(app->widget_24_chkbn_hasbs),
	                              TRUE);

	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_24_chkbn_hasbs,
	                  1, 2,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_24_chkbn_hasbs),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// "has-forward-stepper" gboolean default=TRUE
	GtkWidget* hasfs_lbl = gtk_label_new ("has-forward-stepper");
	gtk_table_attach (GTK_TABLE(table_1),
	                  hasfs_lbl,
	                  0, 1,   // left, right
	                  5, 6,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_24_chkbn_hasfs = gtk_check_button_new ();
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(app->widget_24_chkbn_hasfs),
	                              TRUE);

	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_24_chkbn_hasfs,
	                  1, 2,   // left, right
	                  5, 6,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_24_chkbn_hasfs),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// "has-secondary-backward-stepper" gboolean default=FALSE
	GtkWidget* hassbs_lbl = gtk_label_new ("has-secondary-backward-stepper");
	gtk_table_attach (GTK_TABLE(table_1),
	                  hassbs_lbl,
	                  0, 1,   // left, right
	                  6, 7,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_24_chkbn_hassbs = gtk_check_button_new ();

	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_24_chkbn_hassbs,
	                  1, 2,   // left, right
	                  6, 7,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_24_chkbn_hassbs),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// "has-secondary-forward-stepper" gboolean defalt=FALSE
	GtkWidget* hassfs_lbl = gtk_label_new ("has-secondary-forward-stepper");
	gtk_table_attach (GTK_TABLE(table_1),
	                  hassfs_lbl,
	                  0, 1,   // left, right
	                  7, 8,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_24_chkbn_hassfs = gtk_check_button_new ();

	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_24_chkbn_hassfs,
	                  1, 2,   // left, right
	                  7, 8,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_24_chkbn_hassfs),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// "tab-curvature" gint >= 0 default=1
	GtkWidget* tabcurv_lbl = gtk_label_new ("tab-curvature");
	app->widget_24_spinbn_tabcurv = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_24_spinbn_tabcurv),
	                           1);
	gtk_table_attach (GTK_TABLE(table_1),
	                  tabcurv_lbl,
	                  0, 1,   // left, right
	                  8, 9,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_24_spinbn_tabcurv,
	                  1, 2,   // left, right
	                  8, 9,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_24_spinbn_tabcurv),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "tab-overlap" gint (didn's specify) default=2 (size of tab overalp area)
	GtkWidget* tabover_lbl = gtk_label_new ("tab-overlap");
	app->widget_24_spinbn_tabover = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_24_spinbn_tabover),
	                           2);
	gtk_table_attach (GTK_TABLE(table_1),
	                  tabover_lbl,
	                  0, 1,    // left, right
	                  9, 10,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_24_spinbn_tabover,
	                  1, 2,    // left, right
	                  9, 10,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	g_signal_connect (G_OBJECT(app->widget_24_spinbn_tabover),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_24_style_txt = g_string_new ("#rc style for class GtkNotebook");
}

void ui_update_gtknotebook()
{
}

void ui_delete_gtknotebook()
{
}

void ui_create_gtkpaned()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkPaned");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	/*
	  GtkPaned sample is based on 03_containers - panes.cpp
	 */
	GtkWidget* hpaned = gtk_hpaned_new ();
	GtkWidget* hbn1 = gtk_button_new_with_label ("Resize");
	GtkWidget* hbn2 = gtk_button_new_with_label ("Me!");
	gtk_paned_add1 (GTK_PANED(hpaned), hbn1);
	gtk_paned_add2 (GTK_PANED(hpaned), hbn2);

	GtkWidget* vpaned = gtk_vpaned_new ();
	GtkWidget* vbn1 = gtk_button_new_with_label ("Resize");
	GtkWidget* vbn2 = gtk_button_new_with_label ("Me!");
	gtk_paned_add1 (GTK_PANED(vpaned), vbn1);
	gtk_paned_add2 (GTK_PANED(vpaned), vbn2);

	GtkWidget* hbox = gtk_hbox_new (TRUE, 10);
	gtk_box_pack_start (GTK_BOX(hbox), hpaned, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX(hbox), vpaned, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX(vbox), hbox, TRUE, TRUE, 0);



	GtkWidget* table_1 = gtk_table_new (1, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	// "handle-size" gint >= 0 default=5
	GtkWidget* handlesz_lbl = gtk_label_new ("handle-size");
	app->widget_25_spinbn_handlesz = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_25_spinbn_handlesz),
	                           5);
	gtk_table_attach (GTK_TABLE(table_1),
	                  handlesz_lbl,
	                  0, 1,    // left, right
	                  0, 1,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_25_spinbn_handlesz,
	                  1, 2,    // left, right
	                  0, 1,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	g_signal_connect (G_OBJECT(app->widget_25_spinbn_handlesz),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_25_style_txt = g_string_new ("#rc style for class GtkPaned");
}

void ui_update_gtkpaned()
{
}

void ui_delete_gtkpaned()
{
}

typedef struct
{
	GtkWidget *spin;      // GtkSpinButton
	GtkWidget *scale;     // GtkHScale
	GtkWidget *check;     // GtkCheckButton
} range_widgets;

void range_value_changed (GtkWidget *widget, range_widgets *w)
{
	gdouble val1 = gtk_spin_button_get_value (GTK_SPIN_BUTTON (w->spin));
	gdouble val2 = gtk_range_get_value (GTK_RANGE (w->scale));

	/* Synchronize the widget's value based upon the type of "widget". */
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (w->check)) &&
	    val1 != val2)
	{
		if (GTK_IS_SPIN_BUTTON (widget))
			gtk_range_set_value (GTK_RANGE (w->scale), val1);
		else
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (w->spin), val2);
	}
}

void ui_create_gtkrange()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkRange");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	/*
	  GtkRange is based on exercises/exercise4-2.c
	 */
	GtkAdjustment* adj1 =
		GTK_ADJUSTMENT (gtk_adjustment_new (0.5, 0.0, 1.0, 0.01, 0.02, 0.02));
	GtkAdjustment* adj2 =
		GTK_ADJUSTMENT (gtk_adjustment_new (0.5, 0.0, 1.02, 0.01, 0.02, 0.02));

	range_widgets* w = (range_widgets*) g_malloc (sizeof(range_widgets));
	w->spin = gtk_spin_button_new (adj1, 0.01, 2);
	w->scale = gtk_hscale_new (adj2);
	w->check = gtk_check_button_new_with_label ("Synchronize Spin and Scale");

	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (w->check), TRUE);
	gtk_scale_set_digits (GTK_SCALE (w->scale), 2);
	gtk_scale_set_value_pos (GTK_SCALE (w->scale), GTK_POS_RIGHT);

	g_signal_connect (G_OBJECT (w->spin),
	                  "value_changed",
	                  G_CALLBACK (range_value_changed),
	                  (gpointer) w);
	g_signal_connect (G_OBJECT (w->scale),
	                  "value_changed",
	                  G_CALLBACK (range_value_changed),
	                  (gpointer) w);

	GtkWidget* vbox2 = gtk_vbox_new (FALSE, 5);
	gtk_box_pack_start (GTK_BOX (vbox2), w->spin, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox2), w->scale, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox2), w->check, FALSE, TRUE, 0);

	gtk_box_pack_start (GTK_BOX(vbox), vbox2, FALSE, TRUE, 0);



	GtkWidget* table_1 = gtk_table_new (11, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	// "activate-slider" gboolean default=FALSE , deprecated in 2.22
	GtkWidget* activatesld_lbl = gtk_label_new ("activate-slider");
	gtk_table_attach (GTK_TABLE(table_1),
	                  activatesld_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_26_chkbn_activatesld = gtk_check_button_new ();

	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_26_chkbn_activatesld,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_26_chkbn_activatesld),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// "arrow-displacement-x" gint (didn't specify) default=0  (how far in x dir to move the arrow when button is pressed)
	GtkWidget* arrowdx_lbl = gtk_label_new ("arrow-displacement-x");
	app->widget_26_spinbn_arrowdx = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_26_spinbn_arrowdx),
	                           0);
	gtk_table_attach (GTK_TABLE(table_1),
	                  arrowdx_lbl,
	                  0, 1,    // left, right
	                  1, 2,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_26_spinbn_arrowdx,
	                  1, 2,    // left, right
	                  1, 2,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	g_signal_connect (G_OBJECT(app->widget_26_spinbn_arrowdx),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "arrow-displacement-y" gint (didn't specify) default=0  (similar in y)
	GtkWidget* arrowdy_lbl = gtk_label_new ("arrow-displacement-y");
	app->widget_26_spinbn_arrowdy = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_26_spinbn_arrowdy),
	                           0);
	gtk_table_attach (GTK_TABLE(table_1),
	                  arrowdy_lbl,
	                  0, 1,    // left, right
	                  2, 3,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_26_spinbn_arrowdy,
	                  1, 2,    // left, right
	                  2, 3,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	g_signal_connect (G_OBJECT(app->widget_26_spinbn_arrowdy),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "arrow-scaling" gfloat [0,1] default=0.5
	GtkWidget* arrowsc_lbl = gtk_label_new ("arrow-scaling");
	app->widget_26_spinbn_arrowsc = gtk_spin_button_new_with_range (0.0,1.0,0.1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_26_spinbn_arrowsc),
	                           0.5);
	gtk_table_attach (GTK_TABLE(table_1),
	                  arrowsc_lbl,
	                  0, 1,    // left, right
	                  3, 4,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_26_spinbn_arrowsc,
	                  1, 2,    // left, right
	                  3, 4,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	g_signal_connect (G_OBJECT(app->widget_26_spinbn_arrowsc),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "slider-width" gint >= 0 default=14
	GtkWidget* sliderw_lbl = gtk_label_new ("slider-width");
	app->widget_26_spinbn_sliderw = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_26_spinbn_sliderw),
	                           14);
	gtk_table_attach (GTK_TABLE(table_1),
	                  sliderw_lbl,
	                  0, 1,    // left, right
	                  4, 5,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_26_spinbn_sliderw,
	                  1, 2,    // left, right
	                  4, 5,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	g_signal_connect (G_OBJECT(app->widget_26_spinbn_sliderw),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "stepper-position-details" gboolean default=FALSE , deprecated in 2.22
	GtkWidget* stepperpd_lbl = gtk_label_new ("stepper-position-details");
	gtk_table_attach (GTK_TABLE(table_1),
	                  stepperpd_lbl,
	                  0, 1,   // left, right
	                  5, 6,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_26_chkbn_stepperpd = gtk_check_button_new ();

	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_26_chkbn_stepperpd,
	                  1, 2,   // left, right
	                  5, 6,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_26_chkbn_stepperpd),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// "stepper-size" gint >= 0 default=14
	GtkWidget* steppersz_lbl = gtk_label_new ("stepper-size");
	app->widget_26_spinbn_steppersz = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_26_spinbn_steppersz),
	                           14);
	gtk_table_attach (GTK_TABLE(table_1),
	                  steppersz_lbl,
	                  0, 1,    // left, right
	                  6, 7,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_26_spinbn_steppersz,
	                  1, 2,    // left, right
	                  6, 7,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	g_signal_connect (G_OBJECT(app->widget_26_spinbn_steppersz),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "stepper-spacing" gint >= 0 default=0
	GtkWidget* steppersp_lbl = gtk_label_new ("stepper-spacing");
	app->widget_26_spinbn_steppersp = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_26_spinbn_steppersp),
	                           0);
	gtk_table_attach (GTK_TABLE(table_1),
	                  steppersp_lbl,
	                  0, 1,    // left, right
	                  7, 8,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_26_spinbn_steppersp,
	                  1, 2,    // left, right
	                  7, 8,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	g_signal_connect (G_OBJECT(app->widget_26_spinbn_steppersp),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "through-border" gint >= 0 default=1
	GtkWidget* throughb_lbl = gtk_label_new ("through-border");
	app->widget_26_spinbn_troughb = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_26_spinbn_troughb),
	                           1);
	gtk_table_attach (GTK_TABLE(table_1),
	                  throughb_lbl,
	                  0, 1,    // left, right
	                  8, 9,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_26_spinbn_troughb,
	                  1, 2,    // left, right
	                  8, 9,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	g_signal_connect (G_OBJECT(app->widget_26_spinbn_troughb),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "through-size-details" gboolean default=FALSE , deprecated in 2.22
	GtkWidget* throughsdet_lbl = gtk_label_new ("through-size-details");
	gtk_table_attach (GTK_TABLE(table_1),
	                  throughsdet_lbl,
	                  0, 1,    // left, right
	                  9, 10,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	app->widget_26_chkbn_throughsdet = gtk_check_button_new ();

	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_26_chkbn_throughsdet,
	                  1, 2,    // left, right
	                  9, 10,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	g_signal_connect (G_OBJECT(app->widget_26_chkbn_throughsdet),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// "through-under-steppers" gboolean default=TRUE
	GtkWidget* throughustep_lbl = gtk_label_new ("through-under-steppers");
	gtk_table_attach (GTK_TABLE(table_1),
	                  throughustep_lbl,
	                  0, 1,     // left, right
	                  10, 11,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);    // x,y padding
	app->widget_26_chkbn_throughustep = gtk_check_button_new ();

	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_26_chkbn_throughustep,
	                  1, 2,     // left, right
	                  10, 11,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);    // x,y padding
	g_signal_connect (G_OBJECT(app->widget_26_chkbn_throughustep),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_26_style_txt = g_string_new ("#rc style for class GtkRange");
}

void ui_update_gtkrange()
{
}

void ui_delete_gtkrange()
{
}


typedef struct
{
	GtkWidget *spin;      // GtkSpinButton
	GtkWidget *scale;     // GtkHScale
	GtkWidget *check;     // GtkCheckButton
} scale_widgets;

void scale_value_changed (GtkWidget *widget, scale_widgets *w)
{
	gdouble val1 = gtk_spin_button_get_value (GTK_SPIN_BUTTON (w->spin));
	gdouble val2 = gtk_range_get_value (GTK_RANGE (w->scale));

	/* Synchronize the widget's value based upon the type of "widget". */
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (w->check)) &&
	    val1 != val2)
	{
		if (GTK_IS_SPIN_BUTTON (widget))
			gtk_range_set_value (GTK_RANGE (w->scale), val1);
		else
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (w->spin), val2);
	}
}

void ui_create_gtkscale()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkScale");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	/*
	  GtkScale is based on exercises/exercise4-2.c
	 */
	GtkAdjustment* adj1 =
		GTK_ADJUSTMENT (gtk_adjustment_new (0.5, 0.0, 1.0, 0.01, 0.02, 0.02));
	GtkAdjustment* adj2 =
		GTK_ADJUSTMENT (gtk_adjustment_new (0.5, 0.0, 1.02, 0.01, 0.02, 0.02));

	scale_widgets* w = (scale_widgets*) g_malloc (sizeof(scale_widgets));
	w->spin = gtk_spin_button_new (adj1, 0.01, 2);
	w->scale = gtk_hscale_new (adj2);
	w->check = gtk_check_button_new_with_label ("Synchronize Spin and Scale");

	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (w->check), TRUE);
	gtk_scale_set_digits (GTK_SCALE (w->scale), 2);
	gtk_scale_set_value_pos (GTK_SCALE (w->scale), GTK_POS_RIGHT);

	g_signal_connect (G_OBJECT (w->spin),
	                  "value_changed",
	                  G_CALLBACK (scale_value_changed),
	                  (gpointer) w);
	g_signal_connect (G_OBJECT (w->scale),
	                  "value_changed",
	                  G_CALLBACK (scale_value_changed),
	                  (gpointer) w);

	GtkWidget* vbox2 = gtk_vbox_new (FALSE, 5);
	gtk_box_pack_start (GTK_BOX (vbox2), w->spin, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox2), w->scale, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox2), w->check, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX(vbox), vbox2, FALSE, TRUE, 0);



	GtkWidget* table_1 = gtk_table_new (2, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	// "slider-length" gint >= 0 default=31
	GtkWidget* sliderl_lbl = gtk_label_new ("slider-length");
	app->widget_27_spinbn_sliderl = gtk_spin_button_new_with_range (0,100,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_27_spinbn_sliderl),
	                           31);
	gtk_table_attach (GTK_TABLE(table_1),
	                  sliderl_lbl,
	                  0, 1,    // left, right
	                  0, 1,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_27_spinbn_sliderl,
	                  1, 2,    // left, right
	                  0, 1,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	g_signal_connect (G_OBJECT(app->widget_27_spinbn_sliderl),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "value-spacing" gint >= 0 defalt=2
	GtkWidget* valuesp_lbl = gtk_label_new ("value-spacing");
	app->widget_27_spinbn_valuesp = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_27_spinbn_valuesp),
	                           2);
	gtk_table_attach (GTK_TABLE(table_1),
	                  valuesp_lbl,
	                  0, 1,    // left, right
	                  1, 2,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_27_spinbn_valuesp,
	                  1, 2,    // left, right
	                  1, 2,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	g_signal_connect (G_OBJECT(app->widget_27_spinbn_valuesp),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_27_style_txt = g_string_new ("#rc style for class GtkScale");
}

void ui_update_gtkscale()
{
}

void ui_delete_gtkscale()
{
}

void ui_create_gtkscrolledwindow()
{
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkScrolledWindow");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), FALSE);
	gtk_box_pack_start (GTK_BOX(app->vbox),
	                    expander,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	// sample from SO
	// http://stackoverflow.com/questions/8403731/gtk-and-scrolling-text-view
	const gchar* text = "sample text";
	GtkTextTagTable* txttags = gtk_text_tag_table_new ();
	GtkTextBuffer* txtbuff = gtk_text_buffer_new (txttags);
	gtk_text_buffer_set_text (txtbuff, text, strlen(text));
	GtkWidget* txtview = gtk_text_view_new_with_buffer (txtbuff);
	GtkWidget* scrwin = gtk_scrolled_window_new (NULL, NULL);
	gtk_container_add (GTK_CONTAINER(scrwin), txtview);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    scrwin,
	                    FALSE,   // expanding
	                    FALSE,   // fill
	                    0);      // padding



	// Set the labels on the left side.
	const gint TABLE_0_ROW = 5; // 1 header, 4 colors
	const gint TABLE_0_COL = 6;
	GtkWidget* table_0 = gtk_table_new (TABLE_0_ROW, TABLE_0_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_0,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	const gchar* rows_txt[TABLE_0_ROW] = { "", "fg", "bg", "text", "base" };

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		GtkWidget* label = gtk_label_new (rows_txt[i]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  0, 1,    // left, right
		                  i, i+1,  // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);   // x,y padding
	}

	// Set the labels on the top.
	const gchar* cols_txt[TABLE_0_COL] = {
		"", "NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	for (gint j=1; j<TABLE_0_COL; ++j)
	{
		GtkWidget* label = gtk_label_new (cols_txt[j]);
		gtk_table_attach (GTK_TABLE(table_0),
		                  label,
		                  j, j+1,   // left, right
		                  0, 1,     // top, bottom
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);    // x,y padding
	}

	// Set the color buttons
	/* fg[NORMAL] = "#747474"  , also ACTIVE,PRELIGHT,SELECTED,INSENSITIVE
	   bg[NORMAL] = "#DCDAD5"  , idem
	   text[NORMAL] = "#000000", idem
	   base[NORMAL] = "#FFFFFF", idem
	 */
	GtkStyle* style = gtk_widget_get_style (app->window);

	for (gint i=1; i<TABLE_0_ROW; ++i)
	{
		for (gint j=1; j<TABLE_0_COL; ++j)
		{
			GdkColor* clr;
			if (i == 1)      clr = &(style->fg[j-1]);
			else if (i == 2) clr = &(style->bg[j-1]);
			else if (i == 3) clr = &(style->text[j-1]);
			else if (i == 4) clr = &(style->base[j-1]);
			else exit(-1);
			app->widget_28_clrbn[i-1][j-1] =
				gtk_color_button_new_with_color (clr);
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_28_clrbn[i-1][j-1],
			                  j, j+1, // left, right
			                  i, i+1, // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);  // x,y padding
			g_signal_connect (G_OBJECT(app->widget_28_clrbn[i-1][j-1]),
			                  "color-set",
			                  G_CALLBACK(cb_color_set),
			                  NULL);
		}
	}


	// font_desc    font_name="FreeSans 11"
	GtkWidget* table_1 = gtk_table_new (5, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_1,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding
	GtkWidget* font_desc_lbl = gtk_label_new ("font_desc");
	char* font_name = pango_font_description_to_string (style->font_desc);
	app->widget_28_fn_bn = gtk_font_button_new_with_font (font_name);
	g_free (font_name);
	gtk_table_attach (GTK_TABLE(table_1),
	                  font_desc_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_28_fn_bn,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_28_fn_bn),
	                  "font-set",
	                  G_CALLBACK(cb_font_set),
	                  NULL);

	// xthickness = 2
	GtkWidget* xthickness_lbl = gtk_label_new ("xthickness");
	app->widget_28_spinbn_xth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_28_spinbn_xth),
	                           (gdouble)style->xthickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  xthickness_lbl,
	                  0, 1,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_28_spinbn_xth,
	                  1, 2,   // left, right
	                  1, 2,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_28_spinbn_xth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// ythickness = 2
	GtkWidget* ythickness_lbl = gtk_label_new ("ythickness");
	app->widget_28_spinbn_yth = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_28_spinbn_yth),
	                           (gdouble)style->ythickness);
	gtk_table_attach (GTK_TABLE(table_1),
	                  ythickness_lbl,
	                  0, 1,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_28_spinbn_yth,
	                  1, 2,   // left, right
	                  2, 3,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_28_spinbn_yth),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "scrollbar-spacing" gint >= 0 default=3
	GtkWidget* scrollbarsp_lbl = gtk_label_new ("scrollbar-spacing");
	app->widget_28_spinbn_scrollbarsp = gtk_spin_button_new_with_range (0,10,1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(app->widget_28_spinbn_scrollbarsp),
	                           3);
	gtk_table_attach (GTK_TABLE(table_1),
	                  scrollbarsp_lbl,
	                  0, 1,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_28_spinbn_scrollbarsp,
	                  1, 2,   // left, right
	                  3, 4,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_28_spinbn_scrollbarsp),
	                  "value-changed",
	                  G_CALLBACK(cb_spinbn_value_changed),
	                  NULL);

	// "scollbars-within-bevel" gboolean default=FALSE
	GtkWidget* scrollbarswb_lbl = gtk_label_new ("scollbars-within-bevel");
	gtk_table_attach (GTK_TABLE(table_1),
	                  scrollbarswb_lbl,
	                  0, 1,    // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	app->widget_28_chkbn_scrollbarswb = gtk_check_button_new ();

	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_28_chkbn_scrollbarswb,
	                  1, 2,    // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);   // x,y padding
	g_signal_connect (G_OBJECT(app->widget_28_chkbn_scrollbarswb),
	                  "clicked",
	                  G_CALLBACK(cb_chkbn_clicked),
	                  NULL);

	// retain the style as text to write it into rc file at any time.
	app->widget_28_style_txt = g_string_new ("#rc style for class GtkScrolledWindow");
}

void ui_update_gtkscrolledwindow()
{
}

void ui_delete_gtkscrolledwindow()
{
}
