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
	// ----- GtkWidget section -----
	GtkWidget* widget_0_clr_bn[4][5];
	GtkWidget* widget_0_fn_bn;
	GtkWidget* widget_0_spinbn_xth;
	GtkWidget* widget_0_spinbn_yth;
	GtkWidget* widget_0_pixbn[5];
	GString*   widget_0_pixmap[5];
	GtkWidget* widget_0_spinbn_cursorar;
	GtkWidget* widget_0_clr_bn_cursorclr;
	GtkWidget* widget_0_spinbn_drawb[4];
	GtkWidget* widget_0_entry_focuslp;
	GtkWidget* widget_0_spinbn_focuslw;
	GtkWidget* widget_0_spinbn_focusp;
	GtkWidget* widget_0_chkbn_interiorf;
	GtkWidget* widget_0_clr_bn_linkclr;
	GtkWidget* widget_0_spinbn_scrollahl;
	GtkWidget* widget_0_spinbn_scrollavl;
	GtkWidget* widget_0_clr_bn_secondarycurclr;
	GtkWidget* widget_0_spinbn_separatorh;
	GtkWidget* widget_0_spinbn_separatorw;
	GtkWidget* widget_0_clr_bn_visitedlnkclr;
	GtkWidget* widget_0_chkbn_wides;
	GString*   widget_0_style_txt;
};
AppData* app;


// GtkWidget sytle methods and callbacks
void cb_0_color_set (GtkColorButton*, gpointer);
void cb_0_font_set (GtkFontButton*, gpointer);
void cb_0_value_changed (GtkSpinButton*, gpointer);
void cb_0_clicked (GtkButton*, gpointer);
void cb_0_activate(GtkEntry*,  gpointer);


// Main application RC methods
void write_rc_for_gtkwidget();
void write_rc_for_gtkbutton();
void write_rc_for_all();

// Main application UI methods
void ui_create_gtkwidget();
void ui_delete_gtkwidget();



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
	gtk_box_pack_start (GTK_BOX(pvbox), menubar, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX(pvbox), scrolled_win, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER(window), pvbox);
	app->vbox = gtk_vbox_new (FALSE, 0);
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW(scrolled_win),
	                                       app->vbox);

	// Create UI for each widget
	ui_create_gtkwidget ();




	// Visibility
	gtk_widget_show_all (window);
	gtk_main ();


	// Delete UI for each widget
	ui_delete_gtkwidget ();


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
void cb_0_color_set (GtkColorButton*, gpointer papp)
{
	write_rc_for_all ();
}

void cb_0_font_set (GtkFontButton*, gpointer)
{
	write_rc_for_all ();
}

void cb_0_value_changed (GtkSpinButton*, gpointer)
{
	write_rc_for_all ();
}

void cb_0_clicked (GtkButton* bn, gpointer)
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
				GTK_COLOR_BUTTON(app->widget_0_clr_bn[i][j]),
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
		GTK_COLOR_BUTTON(app->widget_0_clr_bn_cursorclr), &cursorclr);
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
}

void write_rc_for_all()
{
	FILE* fp = fopen (app->rcfile, "w+");
	if (fp == NULL) exit (-1);
	fclose (fp);

	write_rc_for_gtkwidget ();
	write_rc_for_gtkbutton ();
	gtk_rc_reparse_all ();
}


// ----- Main application UI methods -----
//
void ui_create_gtkwidget()
{
	/*  Create the UI elements to set
	    class GtkWidget's style and properties.
	*/

	// First table holds the color buttons and labels on top and left side.
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	const gint TABLE_0_ROW = 6; // 1 header, 4 colors, 1 pixmap
	const gint TABLE_0_COL = 6;
	GtkWidget* table_0 = gtk_table_new (TABLE_0_ROW, TABLE_0_COL, TRUE);
	gtk_box_pack_start (GTK_BOX(vbox), table_0, FALSE, FALSE, 0);
	GtkWidget* expander = gtk_expander_new ("GtkWidget");
	gtk_container_add (GTK_CONTAINER(expander), vbox);
	gtk_expander_set_expanded (GTK_EXPANDER(expander), TRUE);
	gtk_box_pack_start (GTK_BOX(app->vbox), expander, TRUE, TRUE, 0);

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
			app->widget_0_clr_bn[i-1][j-1] = gtk_color_button_new_with_color (clr);
			gtk_table_attach (GTK_TABLE(table_0),
			                  app->widget_0_clr_bn[i-1][j-1],
			                  j, j+1, // left, right
			                  i, i+1, // top, bottom
			                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
			                  0, 0);  // x,y padding
			g_signal_connect (G_OBJECT(app->widget_0_clr_bn[i-1][j-1]),
			                  "color-set",
			                  G_CALLBACK(cb_0_color_set),
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
			                  G_CALLBACK(cb_0_clicked),
			                  NULL);
		}
	}

	// New table for: font desc, thickness, cursor-aspect-ratio, cursor-color
	GtkWidget* table_1 = gtk_table_new (5, 2, TRUE); //row,col,homo
	gtk_box_pack_start (GTK_BOX(vbox), table_1, FALSE, FALSE, 0);
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
	                  G_CALLBACK(cb_0_font_set),
	                  NULL);

	// add thickness to table
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
	                  G_CALLBACK(cb_0_value_changed),
	                  NULL);

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
	                  G_CALLBACK(cb_0_value_changed),
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
	                  G_CALLBACK(cb_0_value_changed),
	                  NULL);


	// GtkWidget::cursor-color = "#000000" GdkColor
	GdkColor cursorclr;
	gdk_color_parse ("#000000", &cursorclr);
	app->widget_0_clr_bn_cursorclr = gtk_color_button_new_with_color (&cursorclr);
	GtkWidget* cursorclr_lbl = gtk_label_new ("cursor-color");
	gtk_table_attach (GTK_TABLE(table_1),
	                  cursorclr_lbl,
	                  0, 1,   // left, right
	                  4, 5,   // top, bottom,
	                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
	                  0, 0);  // x,y padding
	gtk_table_attach (GTK_TABLE(table_1),
	                  app->widget_0_clr_bn_cursorclr,
	                  1, 2,   // left, right
	                  4, 5,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK, // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_0_clr_bn_cursorclr),
	                  "color-set",
	                  G_CALLBACK(cb_0_color_set),
	                  NULL);

	// New table for: GtkWidget::draw-border = { 1, 1, 1, 1 }
	const gint TABLE_1_COL = 5;
	GtkWidget* table_2 = gtk_table_new (1, 5, TRUE); // row, col, homo
	gtk_box_pack_start (GTK_BOX(vbox), table_2, FALSE, FALSE, 0);
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
		                    G_CALLBACK(cb_0_value_changed),
		                    NULL);
	}


	// New table for 12 more widgets.
	const gint TABLE_3_ROW = 12;
	const gint TABLE_3_COL = 2;
	GtkWidget* table_3 = gtk_table_new (12, 2, TRUE); // row, col, homo
	gtk_box_pack_start (GTK_BOX(vbox), table_3, FALSE, FALSE, 0);

	// focus-line-pattern   char*      \001\001
	GtkWidget* focuslp_lbl = gtk_label_new ("focus-line-pattern");
	gtk_table_attach (GTK_TABLE(table_3),
	                  focuslp_lbl,
	                  0, 1,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	app->widget_0_entry_focuslp = gtk_entry_new ();
	gtk_entry_set_text (app->widget_0_entry_focuslp, "\001\001");
	gtk_table_attach (GTK_TABLE(table_3),
	                  app->widget_0_entry_focuslp,
	                  1, 2,   // left, right
	                  0, 1,   // top, bottom
	                  GTK_SHRINK, GTK_SHRINK,  // GtkAttachOptions
	                  0, 0);  // x,y padding
	g_signal_connect (G_OBJECT(app->widget_0_entry_focuslp),
	                  "activate",
	                  G_CALLBACK(cb_0_activate),
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
	                  G_CALLBACK(cb_0_value_changed),
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
	                  G_CALLBACK(cb_0_value_changed),
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
	


	// link-color           GdkColor         def:did't say->blue
	// scroll-arrow-hlength gint       >=1   def:16
	// scroll-arrow-vlength gint       >=1   def:16
	// secondary-cursor-color GdkColor  (left->right, right->left edit)
	// separator-height     gint       >=0   def:0 (if wide-separators is on)
	// separator-width      gint       >=0   def:0 (if wide-separators is on)
	// visited-link-color   GdkColor
	// wide-separators      gboolean   def:FALSE (draw sep using box not lines)


	// retain the style as text to write it into rc file at any time.
	app->widget_0_style_txt = g_string_new ("#rc style for class GtkWidget");
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
