/*
 * key2 example
 *
 *      XLookupString - to convert XKeyEvent* into character buffer
 *      XK_KP_1 - reading keysym code (see keysymdef.h for defined values)
 *      mapping codes to a limited range (LATIN_1  , etc)
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>


void printKeyEvent(XKeyEvent* xkey);

int main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	Display* dpy = XOpenDisplay(NULL);
	if(!dpy) return -1;

	int scrno = DefaultScreen(dpy);
	int scrwidth = DisplayWidth(dpy, scrno);
	int scrheight = DisplayHeight(dpy, scrno);


	int x = 10;
	int y = 10;
	int winwidth = scrwidth / 5;
	int winheight = scrheight / 6 ;
	int winborder = 1;


	Window win = XCreateSimpleWindow(dpy,
	                                 RootWindow(dpy, scrno),
	                                 x, y,
	                                 winwidth, winheight,
	                                 winborder,
	                                 BlackPixel(dpy, scrno),
	                                 WhitePixel(dpy, scrno));


	/* X.h
	   line: 150 to 175   Event definitions;
	*/
	long event_mask = KeyPressMask | ButtonPressMask;
	XSelectInput(dpy, win, event_mask);

	XMapWindow(dpy, win);


	// Process key events
	XEvent event;
	while (1)
	{
		XNextEvent(dpy, &event);

		if (event.type == KeyPress)
		{
			XKeyEvent* xkey = &(event.xkey);
			printKeyEvent(xkey);
		}

		if (event.type == ButtonPress)
			break;
	}


	// exit clean
	XUnmapWindow(dpy, win);
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}


void printKeyEvent(XKeyEvent* xkey)
{

	char buff[100];
	KeySym keysym;
	XComposeStatus status;
	int ret = XLookupString (xkey,
	                         buff,
	                         100,
	                         &keysym,
	                         &status);

	std::stringstream ss;
	ss << "char=";
	if (strlen(buff) != 0)
		ss << buff;
	ss << " keysym=U+" << std::uppercase << std::setfill('0') << std::setw(4)
	   << keysym << " ";

	// list KeySym values (not all) in the order of appearance in X11/keysymdef.h
	switch (keysym)
	{
	case XK_BackSpace:       ss << "XK_BackSpace"; break;
	case XK_Tab:             ss << "XK_Tab"; break;
	case XK_Linefeed:        ss << "XK_Linefeed"; break;
	case XK_Clear:           ss << "XK_Clear"; break;
	case XK_Return:          ss << "XK_Return"; break;
	case XK_Pause:           ss << "XK_Pause"; break;
	case XK_Scroll_Lock:     ss << "XK_Scroll_Lock"; break;
	case XK_Sys_Req:         ss << "XK_Sys_Req"; break;
	case XK_Escape:          ss << "XK_Escape"; break;
	case XK_Delete:          ss << "XK_Delete"; break;

    /* Cursor control & motion */

	case XK_Home:          ss << "XK_Home"; break;
	case XK_Left:          ss << "XK_Left"; break;
	case XK_Up:            ss << "XK_Up"; break;
	case XK_Right:         ss << "XK_Right"; break;
	case XK_Down:          ss << "XK_Down"; break;
//  case XK_Prior:         ss << "XK_Prior"; break;  --duplicate of XK_Page_Up
	case XK_Page_Up:       ss << "XK_Page_Up"; break;
//	case XK_Next:          ss << "XK_Next"; break;   --duplicate of XK_Page_Down
	case XK_Page_Down:     ss << "XK_Page_Down"; break;
	case XK_End:           ss << "XK_End"; break;
	case XK_Begin:         ss << "XK_Begin"; break;


    /* Misc functions */

	case XK_Select:          ss << "XK_Select"; break;
	case XK_Print:           ss << "XK_Print"; break;
	case XK_Execute:         ss << "XK_Execute"; break;
	case XK_Insert:          ss << "XK_Insert"; break;
	case XK_Undo:            ss << "XK_Undo"; break;
	case XK_Redo:            ss << "XK_Redo"; break;
	case XK_Menu:            ss << "XK_Menu"; break;
	case XK_Find:            ss << "XK_Find"; break;
	case XK_Cancel:          ss << "XK_Cancel"; break;
	case XK_Help:            ss << "XK_Help"; break;
	case XK_Break:           ss << "XK_Break"; break;
	case XK_Mode_switch:     ss << "XK_Mode_switch"; break;
//	case XK_script_switch:   ss << "XK_script_switch"; break; --duplicate
	case XK_Num_Lock:        ss << "XK_Num_Lock"; break;

    /* Keypad functions, keypad numbers cleverly chosen to map to ASCII */

	case XK_KP_Space:        ss << "XK_KP_Space"; break;
	case XK_KP_Tab:          ss << "XK_KP_Tab"; break;
	case XK_KP_Enter:        ss << "XK_KP_Enter"; break;
	case XK_KP_F1:           ss << "XK_KP_F1"; break;
	case XK_KP_F2:           ss << "XK_KP_F2"; break;
	case XK_KP_F3:           ss << "XK_KP_F3"; break;
	case XK_KP_F4:           ss << "XK_KP_F4"; break;
	case XK_KP_Home:         ss << "XK_KP_Home"; break;
	case XK_KP_Left:         ss << "XK_KP_Left"; break;
	case XK_KP_Up:           ss << "XK_KP_Up"; break;
	case XK_KP_Right:        ss << "XK_KP_Right"; break;
	case XK_KP_Down:         ss << "XK_KP_Down"; break;
//	case XK_KP_Prior:        ss << "XK_KP_Prior"; break; --duplicate
	case XK_KP_Page_Up:      ss << "XK_KP_Page_Up"; break;
//	case XK_KP_Next:         ss << "XK_KP_Next"; break;  --duplicate
	case XK_KP_Page_Down:    ss << "XK_KP_Page_Down"; break;
	case XK_KP_End:          ss << "XK_KP_End"; break;
	case XK_KP_Begin:        ss << "XK_KP_Begin"; break;
	case XK_KP_Insert:       ss << "XK_KP_Insert"; break;
	case XK_KP_Delete:       ss << "XK_KP_Delete"; break;
	case XK_KP_Equal:        ss << "XK_KP_Equal"; break;
	case XK_KP_Multiply:     ss << "XK_KP_Multiply"; break;
	case XK_KP_Add:          ss << "XK_KP_Add"; break;
	case XK_KP_Separator:    ss << "XK_KP_Separator"; break;
	case XK_KP_Subtract:     ss << "XK_KP_Subtract"; break;
	case XK_KP_Decimal:      ss << "XK_KP_Decimal"; break;
	case XK_KP_Divide:       ss << "XK_KP_Divide"; break;

	case XK_KP_0: ss << "XK_KP_0"; break;
	case XK_KP_1: ss << "XK_KP_1"; break;
	case XK_KP_2: ss << "XK_KP_2"; break;
	case XK_KP_3: ss << "XK_KP_3"; break;
	case XK_KP_4: ss << "XK_KP_4"; break;
	case XK_KP_5: ss << "XK_KP_5"; break;
	case XK_KP_6: ss << "XK_KP_6"; break;
	case XK_KP_7: ss << "XK_KP_7"; break;
	case XK_KP_8: ss << "XK_KP_8"; break;
	case XK_KP_9: ss << "XK_KP_9"; break;

    /*
     * Auxiliary functions; note the duplicate definitions for left and right
     * function keys;  Sun keyboards and a few other manufacturers have such
     * function key groups on the left and/or right sides of the keyboard.
     * We've not found a keyboard with more than 35 function keys total.
     */

	case XK_F1:  ss << "XK_F1"; break;
	case XK_F2:  ss << "XK_F2"; break;
	case XK_F3:  ss << "XK_F3"; break;
	case XK_F4:  ss << "XK_F4"; break;
	case XK_F5:  ss << "XK_F5"; break;
	case XK_F6:  ss << "XK_F6"; break;
	case XK_F7:  ss << "XK_F7"; break;
	case XK_F8:  ss << "XK_F8"; break;
	case XK_F9:  ss << "XK_F9"; break;
	case XK_F10: ss << "XK_F10"; break;
	case XK_F11: ss << "XK_F11"; break;
//	case XK_L1:  ss << "XK_L1"; break;
	case XK_F12: ss << "XK_F12"; break;
//	case XK_L2:  ss << "XK_L2"; break;
	case XK_F13: ss << "XK_F13"; break;
//	case XK_L3:  ss << "XK_L3"; break;
	case XK_F14: ss << "XK_F14"; break;
//	case XK_L4:  ss << "XK_L4"; break;
	case XK_F15: ss << "XK_F15"; break;
//	case XK_L5:  ss << "XK_L5"; break;
	case XK_F16: ss << "XK_F16"; break;
//	case XK_L6:  ss << "XK_L6"; break;
	case XK_F17: ss << "XK_F17"; break;
//	case XK_L7:  ss << "XK_L7"; break;
	case XK_F18: ss << "XK_F18"; break;
//	case XK_L8:  ss << "XK_L8"; break;
	case XK_F19: ss << "XK_F19"; break;
//	case XK_L9:  ss << "XK_L9"; break;
	case XK_F20: ss << "XK_F20"; break;
//	case XK_L10: ss << "XK_L10"; break;
	case XK_F21: ss << "XK_F21"; break;
//	case XK_R1:  ss << "XK_R1"; break;
	case XK_F22: ss << "XK_F22"; break;
//	case XK_R2:  ss << "XK_R2"; break;
	case XK_F23: ss << "XK_F23"; break;
//	case XK_R3:  ss << "XK_R3"; break;
	case XK_F24: ss << "XK_F24"; break;
//	case XK_R4:  ss << "XK_R4"; break;
	case XK_F25: ss << "XK_F25"; break;
//	case XK_R5:  ss << "XK_R5"; break;
	case XK_F26: ss << "XK_F26"; break;
//	case XK_R6:  ss << "XK_R6"; break;
	case XK_F27: ss << "XK_F27"; break;
//	case XK_R7:  ss << "XK_R7"; break;
	case XK_F28: ss << "XK_F28"; break;
//	case XK_R8:  ss << "XK_R8"; break;
	case XK_F29: ss << "XK_F29"; break;
//	case XK_R9:  ss << "XK_R9"; break;
	case XK_F30: ss << "XK_F30"; break;
//	case XK_R10: ss << "XK_R10"; break;
	case XK_F31: ss << "XK_F31"; break;
//	case XK_R11: ss << "XK_R11"; break;
	case XK_F32: ss << "XK_F32"; break;
//	case XK_R12: ss << "XK_R12"; break;
	case XK_F33: ss << "XK_F33"; break;
//	case XK_R13: ss << "XK_R13"; break;
	case XK_F34: ss << "XK_F34"; break;
//	case XK_R14: ss << "XK_R14"; break;
	case XK_F35: ss << "XK_F35"; break;
//	case XK_R15: ss << "XK_R15"; break;

    /* Modifiers */

	case XK_Shift_L:    ss << "XK_Shift_L"; break;
	case XK_Shift_R:    ss << "XK_Shift_R"; break;
	case XK_Control_L:  ss << "XK_Control_L"; break;
	case XK_Control_R:  ss << "XK_Control_R"; break;
	case XK_Caps_Lock:  ss << "XK_Caps_Lock"; break;
	case XK_Shift_Lock: ss << "XK_Shift_Lock"; break;

	case XK_Meta_L:    ss << "XK_Meta_L"; break;
	case XK_Meta_R:    ss << "XK_Meta_R"; break;
	case XK_Alt_L:     ss << "XK_Alt_L"; break;
	case XK_Alt_R:     ss << "XK_Alt_R"; break;
	case XK_Super_L:   ss << "XK_Super_L"; break;
	case XK_Super_R:   ss << "XK_Super_R"; break;
	case XK_Hyper_L:   ss << "XK_Hyper_L"; break;
	case XK_Hyper_R:   ss << "XK_Hyper_R"; break;


    /*
     * Latin 1
     * (ISO/IEC 8859-1 = Unicode U+0020..U+00FF)
     * Byte 3 = 0
     */
#ifdef XK_LATIN1
	case XK_space:          ss << " XK_space"; break;
	case XK_exclam:         ss << "XK_exclam"; break;
	case XK_quotedbl:       ss << "XK_quotedbl"; break;
	case XK_numbersign:     ss << "XK_numbersign"; break;
	case XK_dollar:         ss << "XK_dollar"; break;
	case XK_percent:        ss << "XK_percent"; break;
	case XK_ampersand:      ss << "XK_ampersand"; break;
	case XK_apostrophe:     ss << "XK_apostrophe"; break;
//	case XK_quoteright:     ss << "XK_quoteright"; break;
	case XK_parenleft:      ss << "XK_parenleft"; break;
	case XK_parenright:     ss << "XK_parenright"; break;
	case XK_asterisk:       ss << "XK_asterisk"; break;
	case XK_plus:           ss << "XK_plus"; break;
	case XK_comma:          ss << "XK_comma"; break;
	case XK_minus:          ss << "XK_minus"; break;
	case XK_period:         ss << "XK_period"; break;
	case XK_slash:          ss << "XK_slash"; break;
	case XK_0:              ss << "XK_0"; break;
	case XK_1:              ss << "XK_1"; break;
	case XK_2:              ss << "XK_2"; break;
	case XK_3:              ss << "XK_3"; break;
	case XK_4:              ss << "XK_4"; break;
	case XK_5:              ss << "XK_5"; break;
	case XK_6:              ss << "XK_6"; break;
	case XK_7:              ss << "XK_7"; break;
	case XK_8:              ss << "XK_8"; break;
	case XK_9:              ss << "XK_9"; break;
	case XK_colon:          ss << "XK_colon"; break;
	case XK_semicolon:      ss << "XK_semicolon"; break;
	case XK_less:           ss << "XK_less"; break;
	case XK_equal:          ss << "XK_equal"; break;
	case XK_greater:        ss << "XK_greater"; break;
	case XK_question:       ss << "XK_question"; break;
	case XK_at:             ss << "XK_at"; break;
	case XK_A:              ss << "XK_A"; break;
	case XK_B:              ss << "XK_B"; break;
	case XK_C:              ss << "XK_C"; break;
	case XK_D:              ss << "XK_D"; break;
	case XK_E:              ss << "XK_E"; break;
	case XK_F:              ss << "XK_F"; break;
	case XK_G:              ss << "XK_G"; break;
	case XK_H:              ss << "XK_H"; break;
	case XK_I:              ss << "XK_I"; break;
	case XK_J:              ss << "XK_J"; break;
	case XK_K:              ss << "XK_K"; break;
	case XK_L:              ss << "XK_L"; break;
	case XK_M:              ss << "XK_M"; break;
	case XK_N:              ss << "XK_N"; break;
	case XK_O:              ss << "XK_O"; break;
	case XK_P:              ss << "XK_P"; break;
	case XK_Q:              ss << "XK_Q"; break;
	case XK_R:              ss << "XK_R"; break;
	case XK_S:              ss << "XK_S"; break;
	case XK_T:              ss << "XK_T"; break;
	case XK_U:              ss << "XK_U"; break;
	case XK_V:              ss << "XK_V"; break;
	case XK_W:              ss << "XK_W"; break;
	case XK_X:              ss << "XK_X"; break;
	case XK_Y:              ss << "XK_Y"; break;
	case XK_Z:              ss << "XK_Z"; break;
	case XK_bracketleft:    ss << "XK_bracketleft"; break;
	case XK_backslash:      ss << "XK_backslash"; break;
	case XK_bracketright:   ss << "XK_bracketright"; break;
	case XK_asciicircum:    ss << "XK_asciicircum"; break;
	case XK_underscore:     ss << "XK_underscore"; break;
	case XK_grave:          ss << "XK_grave"; break;
//	case XK_quoteleft:      ss << "XK_quoteleft"; break;
	case XK_a:              ss << "XK_a"; break;
	case XK_b:              ss << "XK_b"; break;
	case XK_c:              ss << "XK_c"; break;
	case XK_d:              ss << "XK_d"; break;
	case XK_e:              ss << "XK_e"; break;
	case XK_f:              ss << "XK_f"; break;
	case XK_g:              ss << "XK_g"; break;
	case XK_h:              ss << "XK_h"; break;
	case XK_i:              ss << "XK_i"; break;
	case XK_j:              ss << "XK_j"; break;
	case XK_k:              ss << "XK_k"; break;
	case XK_l:              ss << "XK_l"; break;
	case XK_m:              ss << "XK_m"; break;
	case XK_n:              ss << "XK_n"; break;
	case XK_o:              ss << "XK_o"; break;
	case XK_p:              ss << "XK_p"; break;
	case XK_q:              ss << "XK_q"; break;
	case XK_r:              ss << "XK_r"; break;
	case XK_s:              ss << "XK_s"; break;
	case XK_t:              ss << "XK_t"; break;
	case XK_u:              ss << "XK_u"; break;
	case XK_v:              ss << "XK_v"; break;
	case XK_w:              ss << "XK_w"; break;
	case XK_x:              ss << "XK_x"; break;
	case XK_y:              ss << "XK_y"; break;
	case XK_z:              ss << "XK_z"; break;
	case XK_braceleft:      ss << "XK_braceleft"; break;
	case XK_bar:            ss << "XK_bar"; break;
	case XK_braceright:     ss << "XK_braceright"; break;
	case XK_asciitilde:     ss << "XK_asciitilde"; break;

	case XK_nobreakspace:   ss << "XK_nobreakspace"; break;
	case XK_exclamdown:     ss << "XK_exclamdown"; break;
	case XK_cent:           ss << "XK_cent"; break;
	case XK_sterling:       ss << "XK_sterling"; break;
	case XK_currency:       ss << "XK_currency"; break;
	case XK_yen:            ss << "XK_yen"; break;
	case XK_brokenbar:      ss << "XK_brokenbar"; break;
	case XK_section:        ss << "XK_section"; break;
	case XK_diaeresis:      ss << "XK_diaeresis"; break;
	case XK_copyright:      ss << "XK_copyright"; break;
	case XK_ordfeminine:    ss << "XK_ordfeminine"; break;
	case XK_guillemotleft:  ss << "XK_guillemotleft"; break;
	case XK_notsign:        ss << "XK_notsign"; break;
	case XK_hyphen:         ss << "XK_hyphen"; break;
	case XK_registered:     ss << "XK_registered"; break;
	case XK_macron:         ss << "XK_macron"; break;
	case XK_degree:         ss << "XK_degree"; break;
	case XK_plusminus:      ss << "XK_plusminus"; break;
	case XK_twosuperior:    ss << "XK_twosuperior"; break;
	case XK_threesuperior:  ss << "XK_threesuperior"; break;
	case XK_acute:          ss << "XK_acute"; break;
	case XK_mu:             ss << "XK_mu"; break;
	case XK_paragraph:      ss << "XK_paragraph"; break;
	case XK_periodcentered: ss << "XK_periodcentered"; break;
	case XK_cedilla:        ss << "XK_cedilla"; break;
	case XK_onesuperior:    ss << "XK_onesuperior"; break;
	case XK_masculine:      ss << "XK_masculine"; break;
	case XK_guillemotright: ss << "XK_guillemotright"; break;
	case XK_onequarter:     ss << "XK_onequarter"; break;
	case XK_onehalf:        ss << "XK_onehalf"; break;
	case XK_threequarters:  ss << "XK_threequarters"; break;
	case XK_questiondown:   ss << "XK_questiondown"; break;
	case XK_Agrave:         ss << "XK_Agrave"; break;
	case XK_Aacute:         ss << "XK_Aacute"; break;
	case XK_Acircumflex:    ss << "XK_Acircumflex"; break;
	case XK_Atilde:         ss << "XK_Atilde"; break;
	case XK_Adiaeresis:     ss << "XK_Adiaeresis"; break;
	case XK_Aring:          ss << "XK_Aring"; break;
	case XK_AE:             ss << "XK_AE"; break;
	case XK_Ccedilla:       ss << "XK_Ccedilla"; break;
	case XK_Egrave:         ss << "XK_Egrave"; break;
	case XK_Eacute:         ss << "XK_Eacute"; break;
	case XK_Ecircumflex:    ss << "XK_Ecircumflex"; break;
	case XK_Ediaeresis:     ss << "XK_Ediaeresis"; break;
	case XK_Igrave:         ss << "XK_Igrave"; break;
	case XK_Iacute:         ss << "XK_Iacute"; break;
	case XK_Icircumflex:    ss << "XK_Icircumflex"; break;
	case XK_Idiaeresis:     ss << "XK_Idiaeresis"; break;
	case XK_ETH:            ss << "XK_ETH"; break;
//	case XK_Eth:            ss << "XK_Eth"; break;
	case XK_Ntilde:         ss << "XK_Ntilde"; break;
	case XK_Ograve:         ss << "XK_Ograve"; break;
	case XK_Oacute:         ss << "XK_Oacute"; break;
	case XK_Ocircumflex:    ss << "XK_Ocircumflex"; break;
	case XK_Otilde:         ss << "XK_Otilde"; break;
	case XK_Odiaeresis:     ss << "XK_Odiaeresis"; break;
	case XK_multiply:       ss << "XK_multiply"; break;
	case XK_Oslash:         ss << "XK_Oslash"; break;
//	case XK_Ooblique:       ss << "XK_Ooblique"; break;
	case XK_Ugrave:         ss << "XK_Ugrave"; break;
	case XK_Uacute:         ss << "XK_Uacute"; break;
	case XK_Ucircumflex:    ss << "XK_Ucircumflex"; break;
	case XK_Udiaeresis:     ss << "XK_Udiaeresis"; break;
	case XK_Yacute:         ss << "XK_Yacute"; break;
	case XK_THORN:          ss << "XK_THORN"; break;
//	case XK_Thorn:          ss << "XK_Thorn"; break;
	case XK_ssharp:         ss << "XK_ssharp"; break;
	case XK_agrave:         ss << "XK_agrave"; break;
	case XK_aacute:         ss << "XK_aacute"; break;
	case XK_acircumflex:    ss << "XK_acircumflex"; break;
	case XK_atilde:         ss << "XK_atilde"; break;
	case XK_adiaeresis:     ss << "XK_adiaeresis"; break;
	case XK_aring:          ss << "XK_aring"; break;
	case XK_ae:             ss << "XK_ae"; break;
	case XK_ccedilla:       ss << "XK_ccedilla"; break;
	case XK_egrave:         ss << "XK_egrave"; break;
	case XK_eacute:         ss << "XK_eacute"; break;
	case XK_ecircumflex:    ss << "XK_ecircumflex"; break;
	case XK_ediaeresis:     ss << "XK_ediaeresis"; break;
	case XK_igrave:         ss << "XK_igrave"; break;
	case XK_iacute:         ss << "XK_iacute"; break;
	case XK_icircumflex:    ss << "XK_icircumflex"; break;
	case XK_idiaeresis:     ss << "XK_idiaeresis"; break;
	case XK_eth:            ss << "XK_eth"; break;
	case XK_ntilde:         ss << "XK_ntilde"; break;
	case XK_ograve:         ss << "XK_ograve"; break;
	case XK_oacute:         ss << "XK_oacute"; break;
	case XK_ocircumflex:    ss << "XK_ocircumflex"; break;
	case XK_otilde:         ss << "XK_otilde"; break;
	case XK_odiaeresis:     ss << "XK_odiaeresis"; break;
	case XK_division:       ss << "XK_division"; break;
	case XK_oslash:         ss << "XK_oslash"; break;
//	case XK_ooblique:       ss << "XK_ooblique"; break;
	case XK_ugrave:         ss << "XK_ugrave"; break;
	case XK_uacute:         ss << "XK_uacute"; break;
	case XK_ucircumflex:    ss << "XK_ucircumflex"; break;
	case XK_udiaeresis:     ss << "XK_udiaeresis"; break;
	case XK_yacute:         ss << "XK_yacute"; break;
	case XK_thorn:          ss << "XK_thorn"; break;
	case XK_ydiaeresis:     ss << "XK_ydiaeresis"; break;
#endif /* XK_LATIN1 */

	default: ss << "Undefined ??"; break;
	}

	printf("\n%s", ss.str().c_str());
} // printXEvent()
