; XPStyle on | off
;
; Sets whether or not a XP visual style manifest will be added to the installer.
; This manifest makes the installers controls use the new visual styles when 
; running on Windows XP and later.
; This affects the uninstaller too.

InstallDir "$DOCUMENTS\90_attributes_XPStyle"

Section
    SetOutPath $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

Section Uninstall
    Delete "$INSTDIR\uninstall.exe"
    RMDir $INSTDIR
SectionEnd