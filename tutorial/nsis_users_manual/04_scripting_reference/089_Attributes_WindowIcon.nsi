; WindowIcon on | off
;
; Sets whether or not a XP visual style manifest will be added to the installer.

InstallDir "$DOCUMENTS\89_attributes_WindowIcon"

WindowIcon    on
Icon          "089_attributes_icon.ico"
UninstallIcon "089_attributes_icon.ico"

Section
    SetOutPath $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

Section Uninstall
    Delete "$INSTDIR\uninstall.exe"
    RMDir $INSTDIR
SectionEnd