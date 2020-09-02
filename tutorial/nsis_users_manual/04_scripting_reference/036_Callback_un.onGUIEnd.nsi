# un.onGUIEnd (uninstall callback)
;
; This callback is called right after the uninstaller window closes.
; Use it to free any user interface related plug-ins if needed.

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


Function un.onGUIEnd
    MessageBox MB_OK "Release UI plug-ins!"
FunctionEnd