; UninstallButtonText text
;
; Changes the text of the button that by default says "Uninstall" in the uninstaller.

UninstallButtonText "Eliminare program"

InstallDir "$DOCUMENTS\84_attributes_UninstallButtonText"

Section
    SetOutPath $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

Section Uninstall
    Delete "$INSTDIR\uninstall.exe"
    RMDir $INSTDIR
SectionEnd