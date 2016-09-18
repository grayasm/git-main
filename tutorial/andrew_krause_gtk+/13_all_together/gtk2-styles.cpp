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
	GtkWidget* widget_10_cmbbox_shadowt;
	GString*   widget_10_style_txt;

	// ----- GtkStatusbar -----
	GtkWidget* widget_11_clrbn[4][5];
	GtkWidget* widget_11_fn_bn;
	GtkWidget* widget_11_spinbn_xth;
	GtkWidget* widget_11_spinbn_yth;
	GtkWidget* widget_11_cmbbox_shadowt;
	GString*   widget_11_style_txt;

	// ----- GtkToolbar -----
	GtkWidget* widget_12_clrbn[4][5];
	GtkWidget* widget_12_fn_bn;
	GtkWidget* widget_12_spinbn_xth;
	GtkWidget* widget_12_spinbn_yth;
	GtkWidget* widget_12_cmbbox_buttonr;
	GtkWidget* widget_12_spinbn_internalp;
	GtkWidget* widget_12_spinbn_maxce;
	GtkWidget* widget_12_cmbbox_shadowt;
	GtkWidget* widget_12_spinbn_spacesz;
	GtkWidget* widget_12_cmbbox_spacest;
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
	GtkWidget* widget_14_cmbbox_arrowp;
	GtkWidget* widget_14_chkbn_arrowsc;
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
	GtkWidget* widget_15_cmbbox_shadowt;

	// ----- GtkMenuItem -----
	GtkWidget* widget_16_clrbn[4][5];
	GtkWidget* widget_16_fn_bn;
	GtkWidget* widget_16_spinbn_xth;
	GtkWidget* widget_16_spinbn_yth;
	GtkWidget* widget_16_spinbn_arrowsc;
	GtkWidget* widget_16_spinbn_arrowsp;
	GtkWidget* widget_16_spinbn_horizontalpadd;
	GtkWidget* widget_16_cmbbox_selectedst;
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
void cb_value_changed (GtkSpinButton*, gpointer);
void cb_0_pixbn_clicked (GtkButton*, gpointer); // for bg_pixmap but broken.
void cb_activate(GtkEntry*,  gpointer);
void cb_chkbn_clicked (GtkButton*, gpointer);


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
	FILE* fp = fopen (app->rcfile, "w+");
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

void cb_value_changed (GtkSpinButton*, gpointer)
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
						gtk_button_set_label (GTK_BUTTON(
							                      app->widget_0_pixbn[j-1]),
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

void cb_activate(GtkEntry*,  gpointer)
{
	write_rc_for_all ();
}

void cb_chkbn_clicked (GtkButton*, gpointer)
{
	write_rc_for_all ();
}


// ----- Main application RC methods -----
//
void write_rc_for_gtkwidget()
{
	if (app->widget_0_style_txt == NULL) exit(-1);
	app->widget_0_style_txt = g_string_set_size (app->widget_0_style_txt, 0);
	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {
		"NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	g_string_append_printf (app->widget_0_style_txt,
	                        "style \"%s\"\n{\n",
	                        "widgets");

	// ----- style begin -----
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
		g_string_append_printf (app->widget_0_style_txt,
		                        "%s", "\n");
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
	                        "\tGtkWidget::focus-line-patter = \"%s\"\n",
	                        focuslp);
	gint focuslw = gtk_spin_button_get_value_as_int(
                                 GTK_SPIN_BUTTON(app->widget_0_spinbn_focuslw));
	g_string_append_printf (app->widget_0_style_txt,
	                        "\tGtkWidget::focus-line-width = %d\n", focuslw);
	gint focusp = gtk_spin_button_get_value_as_int(
                                  GTK_SPIN_BUTTON(app->widget_0_spinbn_focusp));
	g_string_append_printf (app->widget_0_style_txt,
	                        "\tGtkWidget::focus-padding = %d\n", focusp);
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
	                        "widgets");
	FILE* fp = fopen (app->rcfile, "r+");
	if (fp == NULL) exit (-1);
	fprintf (fp, "%s", app->widget_0_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkbutton()
{
	if (app->widget_1_style_txt == NULL) exit(-1);
	app->widget_1_style_txt = g_string_set_size (app->widget_1_style_txt, 0);

	const gchar* style[4] = {"fg","bg","text","base"};
	const gchar* state[5] = {
		"NORMAL","ACTIVE","PRELIGHT","SELECTED","INSENSITIVE"
	};
	g_string_append_printf (app->widget_1_style_txt,
	                        "style \"%s\"\n{\n",
	                        "buttons");

	// ----- style begin -----
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
		g_string_append_printf (app->widget_1_style_txt,
		                        "%s", "\n");
	}


	const gchar* font_name = gtk_font_button_get_font_name(
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
	                        "buttons");
	FILE* fp = fopen (app->rcfile, "r+");
	if (fp == NULL) exit (-1);
	fseek (fp, 0, SEEK_END);
	fprintf (fp, "%s", app->widget_1_style_txt->str);
	fclose (fp);
}

void write_rc_for_gtkcheckbutton()
{
}

void write_rc_for_gtkbuttonbox()
{
}

void write_rc_for_gtkcombobox()
{
}

void write_rc_for_gtkentry()
{
}

void write_rc_for_gtkexpander()
{
}

void write_rc_for_gtkscrollbar()
{
}

void write_rc_for_gtkarrow()
{
}

void write_rc_for_gtkprogressbar()
{
}

void write_rc_for_gtkspinbutton()
{
}

void write_rc_for_gtkstatusbar()
{
}

void write_rc_for_gtktoolbar()
{
}

void write_rc_for_gtktoolbutton()
{
}

void write_rc_for_gtkmenu()
{
}

void write_rc_for_gtkmenubar()
{
}

void write_rc_for_gtkmenuitem()
{
}

void write_rc_for_gtkcheckmenuitem()
{
}

void write_rc_for_gtktextview()
{
}

void write_rc_for_gtktreeview()
{
}

void write_rc_for_gtkiconview()
{
}

void write_rc_for_gtkassistant()
{
}

void write_rc_for_gtkdialog()
{
}

void write_rc_for_gtkmessagedialog()
{
}

void write_rc_for_gtknotebook()
{
}

void write_rc_for_gtkpaned()
{
}

void write_rc_for_gtkrange()
{
}

void write_rc_for_gtkscale()
{
}

void write_rc_for_gtkscrolledwindow()
{
}

void write_rc_for_all()
{
	FILE* fp = fopen (app->rcfile, "w+");
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
	                  G_CALLBACK(cb_value_changed),
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
	                  G_CALLBACK(cb_value_changed),
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
	                  G_CALLBACK(cb_value_changed),
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
		                    G_CALLBACK(cb_value_changed),
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
	                  G_CALLBACK(cb_activate),
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
	                  G_CALLBACK(cb_value_changed),
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
	                  G_CALLBACK(cb_value_changed),
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
	                  G_CALLBACK(cb_value_changed),
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
	                  G_CALLBACK(cb_value_changed),
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
	                  G_CALLBACK(cb_value_changed),
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
	                  G_CALLBACK(cb_value_changed),
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
	                  G_CALLBACK(cb_value_changed),
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
	                  G_CALLBACK(cb_value_changed),
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
	                  G_CALLBACK(cb_value_changed),
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
	                  G_CALLBACK(cb_value_changed),
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
		                  G_CALLBACK(cb_value_changed),
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
		                  G_CALLBACK(cb_value_changed),
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
		                  G_CALLBACK(cb_value_changed),
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


	/*
	GtkWidget* widget_2_clrbn[4][5];
	GtkWidget* widget_2_fn_bn;
	GtkWidget* widget_2_spinbn_xth;
	GtkWidget* widget_2_spinbn_yth;
	GtkWidget* widget_2_spinbn_indicatorsz;
	GtkWidget* widget_2_spinbn_indicatorsp;
	GString*   widget_2_style_txt;
	*/
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

	/*
	GtkWidget* widget_3_spinbn_childipx;
	GtkWidget* widget_3_spinbn_childipy;
	GtkWidget* widget_3_spinbn_childmh;
	GtkWidget* widget_3_spinbn_childmw;
	GString*   widget_3_style_txt;
	*/
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

	/*
	  GtkWidget* widget_4_clrbn[4][5];
	  GtkWidget* widget_4_fn_bn;
	  GtkWidget* widget_4_spinbn_xth;
	  GtkWidget* widget_4_spinbn_yth;
	  GtkWidget* widget_4_chkbn_appearsal;
	  GtkWidget* widget_4_spinbn_arrowsz;
	  GtkWidget* widget_4_shadow_type;
	  GString*   widget_4_style_txt;
	*/
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
		                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
		                  0, 0);     // x,y padding
	}

	/*
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
	 */
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
		                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
		                  0, 0);     // x,y padding
	}


	/*
	  GtkWidget* widget_6_clrbn[4][5];
	  GtkWidget* widget_6_fn_bn;
	  GtkWidget* widget_6_spinbn_xth;
	  GtkWidget* widget_6_spinbn_yth;
	  GtkWidget* widget_6_spinbn_expandersz;
	  GtkWidget* widget_6_spinbn_expandersp;
	  GString*   widget_6_style_txt;
	 */
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


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (1, 1, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	// sample from SO
	// http://stackoverflow.com/questions/8403731/gtk-and-scrolling-text-view
	GtkWidget* txtview = gtk_text_view_new();
	GtkWidget* scrwin = gtk_scrolled_window_new (NULL, NULL);
	gtk_container_add (GTK_CONTAINER(scrwin), txtview);
	gtk_table_attach (GTK_TABLE(table_sample),
	                  scrwin,
	                  0, 1,    // left, right
	                  0, 1,    // top, bottom
	                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
	                  0, 0);     // x,y padding

	gtk_widget_set_size_request (scrwin, 400, 150);

	/*
	  GtkWidget* widget_7_chkbn_fixedsl;
	  GtkWidget* widget_7_chkbn_hasbs;
	  GtkWidget* widget_7_chkbn_hasfs;
	  GtkWidget* widget_7_chkbn_hassbs;
	  GtkWidget* widget_7_chkbn_hassfs;
	  GtkWidget* widget_7_spinbn_minsl;
	  GString*   widget_7_style_txt;
	 */
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
	GtkWidget* table_sample = gtk_table_new (4, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	/*
	  GtkWidget* widget_8_spinbn_arrowsc;
	  GString*   widget_8_style_txt;
	*/

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
	GtkWidget* table_sample = gtk_table_new (4, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	
	/*
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
	*/
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
	GtkWidget* table_sample = gtk_table_new (4, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	/*
	  GtkWidget* widget_10_cmbbox_shadowt;
	  GString*   widget_10_style_txt;
	 */

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


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (4, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	/*
	  GtkWidget* widget_11_clrbn[4][5];
	  GtkWidget* widget_11_fn_bn;
	  GtkWidget* widget_11_spinbn_xth;
	  GtkWidget* widget_11_spinbn_yth;
	  GtkWidget* widget_11_cmbbox_shadowt;
	  GString*   widget_11_style_txt;
	 */
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


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (4, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	/*
	  GtkWidget* widget_12_clrbn[4][5];
	  GtkWidget* widget_12_fn_bn;
	  GtkWidget* widget_12_spinbn_xth;
	  GtkWidget* widget_12_spinbn_yth;
	  GtkWidget* widget_12_cmbbox_buttonr;
	  GtkWidget* widget_12_spinbn_internalp;
	  GtkWidget* widget_12_spinbn_maxce;
	  GtkWidget* widget_12_cmbbox_shadowt;
	  GtkWidget* widget_12_spinbn_spacesz;
	  GtkWidget* widget_12_cmbbox_spacest;
	  GString*   widget_12_style_txt;
	 */

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


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (4, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	/*
	  GtkWidget* widget_13_clrbn[4][5];
	  GtkWidget* widget_13_fn_bn;
	  GtkWidget* widget_13_spinbn_xth;
	  GtkWidget* widget_13_spinbn_yth;
	  GtkWidget* widget_13_spinbn_iconsp;
	  GString*   widget_13_style_txt;
	 */

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


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (4, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	/*
	  GtkWidget* widget_14_clrbn[4][5];
	  GtkWidget* widget_14_fn_bn;
	  GtkWidget* widget_14_spinbn_xth;
	  GtkWidget* widget_14_spinbn_yth;
	  GtkWidget* widget_14_cmbbox_arrowp;
	  GtkWidget* widget_14_chkbn_arrowsc;
	  GtkWidget* widget_14_chkbn_doublea;
	  GtkWidget* widget_14_spinbn_horizontaloff;
	  GtkWidget* widget_14_spinbn_horizontalpadd;
	  GtkWidget* widget_14_spinbn_verticaloff;
	  GtkWidget* widget_14_spinbn_verticalpadd;
	  GString*   widget_14_style_txt;
	 */

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


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (4, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	/*
	  GtkWidget* widget_15_clrbn[4][5];
	  GtkWidget* widget_15_fn_bn;
	  GtkWidget* widget_15_spinbn_xth;
	  GtkWidget* widget_15_spinbn_yth;
	  GtkWidget* widget_15_spinbn_internalp;
	  GtkWidget* widget_15_cmbbox_shadowt;
	 */
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


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (4, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	/*
	  GtkWidget* widget_16_clrbn[4][5];
	  GtkWidget* widget_16_fn_bn;
	  GtkWidget* widget_16_spinbn_xth;
	  GtkWidget* widget_16_spinbn_yth;
	  GtkWidget* widget_16_spinbn_arrowsc;
	  GtkWidget* widget_16_spinbn_arrowsp;
	  GtkWidget* widget_16_spinbn_horizontalpadd;
	  GtkWidget* widget_16_cmbbox_selectedst;
	  GtkWidget* widget_16_spinbn_togglesp;
	  GtkWidget* widget_16_spinbn_widthc;
	  GString*   widget_16_style_txt;
	 */
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


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (4, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding

	/*
	  GtkWidget* widget_17_spinbn_indicatorsz;
	  GString*   widget_17_style_txt;
	 */

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


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (4, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	/*
	  GtkWidget* widget_18_clrbn[4][5];
	  GtkWidget* widget_18_fn_bn;
	  GtkWidget* widget_18_spinbn_xth;
	  GtkWidget* widget_18_spinbn_yth;
	  GtkWidget* widget_18_clrbn_errorundclr;
	  GString*   widget_18_style_txt;
	 */
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


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (4, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	/*
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
	 */
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


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (4, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding



	/*
	  GtkWidget* widget_20_clrbn[4][5];
	  GtkWidget* widget_20_fn_bn;
	  GtkWidget* widget_20_spinbn_xth;
	  GtkWidget* widget_20_spinbn_yth;
	  GtkWidget* widget_20_spinbn_selectionboxa;
	  GtkWidget* widget_20_clrbn_selectionboxclr;
	  GString*   widget_20_style_txt;
	 */

}

void ui_update_gtkiconview()
{
}

void ui_delete_gtkiconview()
{
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


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (4, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	/*
	  GtkWidget* widget_21_clrbn[4][5];
	  GtkWidget* widget_21_fn_bn;
	  GtkWidget* widget_21_spinbn_xth;
	  GtkWidget* widget_21_spinbn_yth;
	  GtkWidget* widget_21_spinbn_contentpadd;
	  GtkWidget* widget_21_spinbn_headerpadd;
	  GString*   widget_21_style_txt;
	 */
}

void ui_update_gtkassistant()
{
}

void ui_delete_gtkassistant()
{
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


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (4, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	/*
	  GtkWidget* widget_22_clrbn[4][5];
	  GtkWidget* widget_22_fn_bn;
	  GtkWidget* widget_22_spinbn_xth;
	  GtkWidget* widget_22_spinbn_yth;
	  GtkWidget* widget_22_spinbn_actionab;
	  GtkWidget* widget_22_spinbn_buttonsp;
	  GtkWidget* widget_22_spinbn_contentab;
	  GtkWidget* widget_22_spinbn_contentas;
	  GString*   widget_22_style_txt;
	 */
}

void ui_update_gtkdialog()
{
}

void ui_delete_gtkdialog()
{
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


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (4, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	/*
	  GtkWidget* widget_23_clrbn[4][5];
	  GtkWidget* widget_23_fn_bn;
	  GtkWidget* widget_23_spinbn_xth;
	  GtkWidget* widget_23_spinbn_yth;
	  GtkWidget* widget_23_spinbn_messageb;
	  GtkWidget* widget_23_chkbn_usesep;
	  GString*   widget_23_style_txt;
	 */
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


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (4, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	/*
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
	 */
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


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (4, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	/*
	  GtkWidget* widget_25_spinbn_handlesz;
	  GString*   widget_25_style_txt;
	 */
}

void ui_update_gtkpaned()
{
}

void ui_delete_gtkpaned()
{
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


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (4, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	/*
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
	 */
}

void ui_update_gtkrange()
{
}

void ui_delete_gtkrange()
{
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


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (4, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	/*
	  GtkWidget* widget_27_spinbn_sliderl;
	  GtkWidget* widget_27_spinbn_valuesp;
	  GString*   widget_27_style_txt;
	 */
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


	// Create few sample widgets to visualize theme changes
	GtkWidget* table_sample = gtk_table_new (4, 3, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox),
	                    table_sample,
	                    FALSE,   // expand
	                    FALSE,   // fill
	                    0);      // padding


	/*
	  GtkWidget* widget_28_clrbn[4][5];
	  GtkWidget* widget_28_fn_bn;
	  GtkWidget* widget_28_spinbn_xth;
	  GtkWidget* widget_28_spinbn_yth;
	  GtkWidget* widget_28_spinbn_scrollbarsp;
	  GtkWidget* widget_28_chkbn_scrollbarswb;
	  GString*   widget_28_style_txt;
	 */
}

void ui_update_gtkscrolledwindow()
{
}

void ui_delete_gtkscrolledwindow()
{
}
