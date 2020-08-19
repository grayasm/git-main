# un.onUninstFailed (uninstall callback)
;
; This callback is called when the user hits the 'cancel' button after the
; uninstall has failed.

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
    Abort "Abort Uninstall, exit with Cancel"
SectionEnd


Function un.onUninstFailed
    MessageBox MB_OK "Uninstall failed!"
FunctionEnd