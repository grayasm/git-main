# un.onInit (uninstall callback)
;
; This callback is called when the uninstaller is nearly finished initializing.
; If the un.onInit calls Abort, the uninstaller will quit instantly.

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


Function un.onInit
    MessageBox MB_YESNO "This will uninstall. Continue?" IDYES NoAbort
        Abort ; causes uninstaller to quit.
    NoAbort:
FunctionEnd