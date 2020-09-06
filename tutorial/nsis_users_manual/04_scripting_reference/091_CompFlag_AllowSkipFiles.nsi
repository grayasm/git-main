; AllowSkipFiles on | off
;
; The user has the option to skip a file if SetOverwrite is 'on' (default)
; and the installer fails to open a file for writing when trying to extract it.
; If off is used, the ignore button will not be shown and the user has only
; the option to abort the installation.


RequestExecutionLevel user
AllowSkipFiles on
SetOverwrite on
    
InstallDir "$PROGRAMFILES64\Cannot-create-directory"

Section 1
    ; force error due to write protection
    SetOutPath $INSTDIR
    File 091_CompFlag_AllowSkipFiles.nsi
SectionEnd