; IfErrors  jumpto_iferror  [jumpto_ifnoerror]
;
; Checks and clears the error flag, and if it is set, it will goto jumpto_iferror, 
; otherwise it will goto jumpto_ifnoerror. 
; The error flag is set by other instructions when a recoverable error
; (such as trying to delete a file that is in use) occurs.


Function ErrorHandler
    MessageBox MB_OK "ErrorHandler function!"
FunctionEnd

InstallDir $DOCUMENTS\MyApp

Page directory
Page instfiles

Section
    SetOutPath $INSTDIR
    ; sets the error flag if file does not exist
    GetFileTime "$INSTDIR\156_Instruction_IfErrors.nsi" $1 $0

    IfErrors 0 +2
        Call ErrorHandler
SectionEnd