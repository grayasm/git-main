; SetCtlColors  hwnd  [/BRANDING]  [text_color | SYSCLR:text_color_id]  [transparent | bg_color | SYSCLR:bg_color_id]
;
; Sets the text and background color of a static control, edit control, button or a dialog.
; text_color and bg_color don't accept variables. 
; Use GetDlgItem to get the handle (HWND) of the control. 
; To make the control transparent specify transparent as the background color value.
; Prefix the color value with SYSCLR: to specify a Windows COLOR_* constant. 
; You can also specify /BRANDING with or without text color and background color
; to make the control completely gray (or any other color you choose). 
; This is used by the branding text control in the MUI.


Page Components "" CmpntPageShow
Page InstFiles "" CmpntPageShow

Function CmpntPageShow
    FindWindow $1 "#32770" "" $HWNDPARENT
    GetDlgItem $0 $1 1006
    SetCtlColors $0 0xFF0000 0x00FF00 ; Red on Green
    GetDlgItem $0 $1 1022
    SetCtlColors $0 SYSCLR:23 SYSCLR:24 ; COLOR_INFOTEXT on COLOR_INFOBK
FunctionEnd

Section section1
    DetailPrint "Installing section1"
SectionEnd

Section section2
    DetailPrint "Installing section2"
SectionEnd