# un.onUninstSuccess (uninstall callback)
;
; This callback is called when the uninstall was successful, right before
; the install window closes (which may be after the user clicks 'close' button).

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


Function un.onUninstSuccess
    MessageBox MB_OK "Uninstall succeeded!"
FunctionEnd