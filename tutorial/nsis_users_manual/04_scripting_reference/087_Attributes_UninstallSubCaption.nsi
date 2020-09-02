; UninstallSubCaption page_number subcaption
;
; Sets the default subcaptions for the uninstaller pages
;       0=": Confirmation"
;       1=": Uninstalling Files"
;       2=": Completed"

UninstallSubCaption 0 ": Confirmare"
UninstallSubCaption 1 ": Eliminare fisiere"
UninstallSubCaption 2 ": Eliminare completa"

InstallDir "$DOCUMENTS\87_attributes_UninstallSubCaption"

Section
    SetOutPath $INSTDIR
    WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

Section Uninstall
    Delete "$INSTDIR\uninstall.exe"
    RMDir $INSTDIR
SectionEnd