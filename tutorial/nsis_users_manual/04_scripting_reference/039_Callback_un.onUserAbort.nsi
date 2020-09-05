# un.onUserAbort (uninstall callback)
;
; This callback is called when the user hits the 'cancel' button, and the
; uninstall hasn't already failed. If this function calls Abort, the 
; install will not be aborted.


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


Function un.onUserAbort
    MessageBox MB_YESNO "Abort uninstall?" IDYES NoCancelAbort
        Abort ; causes uninstaller to not quit.
    NoCancelAbort:
FunctionEnd