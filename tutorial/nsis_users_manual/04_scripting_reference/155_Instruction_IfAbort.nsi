; IfAbort  label_to_goto_if_abort  [label_to_goto_if_no_abort]
;
; Will "return" true if the installation has been aborted. 
; This can happen if the user chose abort on a file that failed to create 
; or overwrite or if the user aborted by hand. This function can only be called 
; from the leave function of the instfiles page.

Page instfiles "" "" instfilesLeave

Function instfilesLeave
  IfAbort 0 +2
    MessageBox MB_OK "user aborted"
FunctionEnd

InstallDir $DOCUMENTS\MyApp

Section
    SetOutPath $INSTDIR
    ; sets the error flag if file does not exist
    GetFileTime "$INSTDIR\155_Instruction_IfAbort.nsi" $1 $0

    IfErrors 0 +2
        Abort  "Abort due to GetFileTime error flag."
SectionEnd