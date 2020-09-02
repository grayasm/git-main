; UninstallIcon [path\]icon.ico
;
; Sets the icon of the uninstaller.

InstallDir "$DOCUMENTS\86_attributes_UninstallIcon"

UninstallIcon "86_attributes_icon.ico"

Section
    SetOutPath $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

Section Uninstall
    Delete "$INSTDIR\uninstall.exe"
    RMDir $INSTDIR
SectionEnd