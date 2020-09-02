; UninstallText text [subtext]
;
; Specifies the texts on the uninstaller confirm page.
;       text: Text above the controls
;       subtext: Text next to the uninstall location

UninstallText "Text above the control" "Text next to uninstall location"

InstallDir "$DOCUMENTS\88_attributes_UninstallText"

Section
    SetOutPath $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

Section Uninstall
    Delete "$INSTDIR\uninstall.exe"
    RMDir $INSTDIR
SectionEnd