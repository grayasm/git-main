; ClearErrors 
;
; Clears the error flag.


InstallDir $DOCUMENTS\MyApp

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    ; sets the error flag if file does not exist
    GetFileTime "$INSTDIR\150_Instruction_ClearErrors.nsi" $1 $0

    ClearErrors
    IfErrors 0 +2
        MessageBox MB_OK "this message box will never show"
SectionEnd