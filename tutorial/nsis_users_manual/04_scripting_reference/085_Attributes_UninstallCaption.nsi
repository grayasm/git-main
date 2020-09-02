; UninstallCaption caption
;
; Sets what the titlebars of the uninstaller will display.
; By default it is '$(^Name) Uninstall'

UninstallCaption "UninstallCaption sample"

InstallDir "$DOCUMENTS\85_attributes_UninstallCaption"

Section
    SetOutPath $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

Section Uninstall
    Delete "$INSTDIR\uninstall.exe"
    RMDir $INSTDIR
SectionEnd