# .onGUIInit (install callback)
;   * it is called just before the first page is loaded and the installer
;     dialog is shown, allowing you to tweak the user interface

!include "WinMessages.nsh"

Function .onGUIInit
    # 1028 is the id of the branding text control
    GetDlgItem $R0 $HWNDPARENT 1028
    CreateFont $R1 "Tahoma" 8 700
    SendMessage $R0 ${WM_SETFONT} $R1 0
    # Set background color to white and text color to red
    SetCtlColors $R0 FFFFFF FF0000
FunctionEnd

Section
SectionEnd
