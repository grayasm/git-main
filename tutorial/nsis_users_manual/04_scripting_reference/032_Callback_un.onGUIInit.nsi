# un.onGUIInit (uninstall callback)
;
; This callback is called just before the first page is loaded and the
; uninstaller dialog is shown, allowing you to tweak the user interface

!include "WinMessages.nsh"

InstallDir "$PROGRAMFILES64\MyApp"

Page license
Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

Section Uninstall
    delete "$INSTDIR\uninstall.exe"
    rmDir $INSTDIR
SectionEnd


Function un.onGUIInit
    # 1028 is the id of the branding text control
    GetDlgItem $R0 $HWNDPARENT 1028
    CreateFont $R1 "Tahoma" 8 700
    SendMessage $R0 ${WM_SETFONT} $R1 0
    # Set background color to white and text color to red
    SetCtlColors $R0 FFFFFF FF0000
FunctionEnd